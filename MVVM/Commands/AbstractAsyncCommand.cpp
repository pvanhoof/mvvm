#include "AbstractAsyncCommand.h"

/* Example:
 * QFuture<void*> AnAsyncCommand::executeAsync()
 * {
 *     QSharedPointer<QFutureInterface<void*>> fut = start();
 *     QFutureWatcher<void*>* watcher = new QFutureWatcher<void*>(this);
 *     connect(watcher, &QFutureWatcher<void*>::progressValueChanged, this, [=]{
 *         progress(fut, watcher->progressValue(), watcher->progressMaximum());
 *     });
 *     connect(watcher, &QFutureWatcher<void*>::finished, this, [=]{
 *         voud* result=watcher->result();
 *         finish(fut, result);
 *         watcher->deleteLater();
 *     });
 *     watcher->setFuture(m_asyncSrc->performAsync());
 *     return fut->future();
 * } */

AbstractAsyncCommand::AbstractAsyncCommand(QObject *parent)
    :AbstractCommand(parent)
{
    m_futures.push_back(QSharedPointer<QFutureInterface<void*>>(new QFutureInterface<void*>));
}

QSharedPointer<QFutureInterface<void*>> AbstractAsyncCommand::start()
{
   QSharedPointer<QFutureInterface<void*>> fut = m_futures.last();
   m_futures.push_back(QSharedPointer<QFutureInterface<void*>>(new QFutureInterface<void*>));
   fut->reportStarted();
   return fut;
}

void AbstractAsyncCommand::execute()
{
    executeAsync();
}

void AbstractAsyncCommand::finish(QSharedPointer<QFutureInterface<void*>> fut, void* result)
{
    if (m_futures.contains(fut))
        m_futures.removeAll(fut);
    emit executeFinished(result);
    fut->reportFinished(&result);
}

void AbstractAsyncCommand::progress(QSharedPointer<QFutureInterface<void*>> fut, int value, int total)
{
   if (m_futures.contains(fut)) {
       fut->setProgressRange(0, total);
       fut->setProgressValue(value);
       emit executeProgressed (value, total);
   }
}
