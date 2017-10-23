#include "asynchellocommand.h"

#include <QtConcurrent/QtConcurrent>

AsyncHelloCommand::AsyncHelloCommand(QObject* parent)
    : AbstractAsyncCommand(parent) { }

void* AsyncHelloCommand::executeAsyncTaskFunc()
{
    for (int i=0; i<10; i++) {
        QThread::sleep(1);
        qDebug() << "Hello Async!";
        mutex.lock();
        progress(current, i, 10);
        mutex.unlock();
    }
    return nullptr;
}

QFuture<void*> AsyncHelloCommand::executeAsync()
{
    mutex.lock();
    current = start();
    QFutureWatcher<void*>* watcher = new QFutureWatcher<void*>(this);
    connect(watcher, &QFutureWatcher<void*>::progressValueChanged, this, [=]{
        mutex.lock();
        progress(current, watcher->progressValue(), watcher->progressMaximum());
        mutex.unlock();
    });
    connect(watcher, &QFutureWatcher<void*>::finished, this, [=]{
        void* result=watcher->result();
        mutex.lock();
        finish(current, result);
        mutex.unlock();
        watcher->deleteLater();
    });
    watcher->setFuture(QtConcurrent::run(this, &AsyncHelloCommand::executeAsyncTaskFunc));
    QFuture<void*> future = current->future();
    mutex.unlock();

    return future;
}
