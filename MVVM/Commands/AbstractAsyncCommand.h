#ifndef ABSTRACTASYNCCOMMAND_H
#define ABSTRACTASYNCCOMMAND_H

#include <QFuture>
#include <QSharedPointer>

#include <MVVM/Commands/AbstractCommand.h>

class AbstractAsyncCommand : public AbstractCommand {
    Q_OBJECT
public:
    AbstractAsyncCommand(QObject *parent=0);

    Q_INVOKABLE virtual QFuture<void*> executeAsync() = 0;
    virtual void execute() Q_DECL_OVERRIDE;
signals:
    void executeFinished(void* result);
    void executeProgressed(int value, int maximum);
protected:
    QSharedPointer<QFutureInterface<void*>> start();
    void progress(QSharedPointer<QFutureInterface<void*>> fut, int value, int total);
    void finish(QSharedPointer<QFutureInterface<void*>> fut, void* result);
private:
    QVector<QSharedPointer<QFutureInterface<void*>>> m_futures;
};
#endif
