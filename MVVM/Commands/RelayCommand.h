#ifndef DELEGATE_COMMAND_H
#define DELEGATE_COMMAND_H

#include <functional>

#include <QSharedPointer>

#include <MVVM/Commands/AbstractCommand.h>

class RelayCommand : public AbstractCommand
{
    Q_OBJECT
public:
    RelayCommand(std::function<void()> executeDelegatep,
                    std::function<bool()> canExecuteDelegatep,
                    QObject *parent = 0)
    : AbstractCommand(parent)
    , executeDelegate(executeDelegatep)
    , canExecuteDelegate(canExecuteDelegatep) {}

    void execute() Q_DECL_OVERRIDE;
    bool canExecute() const Q_DECL_OVERRIDE;
public slots:
    void evaluateCanExecute();
private:
    std::function<void()> executeDelegate;
    std::function<bool()> canExecuteDelegate;
};


#endif // DELEGATE_COMMAND_H
