#ifndef ASYNCHELLOCOMMAND_H
#define ASYNCHELLOCOMMAND_H

#include <QThreadPool>
#include <QRunnable>

#include <MVVM/Commands/AbstractAsyncCommand.h>

class AsyncHelloCommand: public AbstractAsyncCommand
{
    Q_OBJECT
public:
    AsyncHelloCommand(QObject *parent=0);
    bool canExecute() const Q_DECL_OVERRIDE { return true; }
    QFuture<void*> executeAsync() Q_DECL_OVERRIDE;
private:
    void* executeAsyncTaskFunc();
    QSharedPointer<QFutureInterface<void*>> current;
    QMutex mutex;
};

#endif // ASYNCHELLOCOMMAND_H
