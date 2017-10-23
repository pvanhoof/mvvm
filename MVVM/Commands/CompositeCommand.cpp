#include <QtQml>

#include "CompositeCommand.h"

CompositeCommand::CompositeCommand(QList<QSharedPointer<AbstractCommand> > cmds, QObject *parent)
    : AbstractCommand (parent)
    , cmds (cmds)
{
    foreach (const QSharedPointer<AbstractCommand> &cmd, cmds) {
        connect(cmd.data(), &AbstractCommand::canExecuteChanged,
                this, &CompositeCommand::onCanExecuteChanged);
    }
}

void CompositeCommand::execute()
{
    foreach (const QSharedPointer<AbstractCommand> &cmd, cmds) {
        cmd->execute();
    }
}

CompositeCommand::~CompositeCommand()
{
    foreach (const QSharedPointer<AbstractCommand> &cmd, cmds) {
        disconnect(cmd.data(), &AbstractCommand::canExecuteChanged,
                   this, &CompositeCommand::onCanExecuteChanged);
    }
}

bool CompositeCommand::canExecute() const
{
    foreach (const QSharedPointer<AbstractCommand>& cmd, cmds) {
        if (!cmd->canExecute())
            return false;
    }
    return true;
}

void CompositeCommand::onCanExecuteChanged(bool canExecute)
{
    bool newstate = canExecute;
    bool origstate = !canExecute;
    foreach (const QSharedPointer<AbstractCommand> &cmd, cmds) {
        if (cmd.data()!=sender()) {
            newstate &= cmd->canExecute();
            origstate &= cmd->canExecute();
        }
    }
    if (newstate != origstate)
        emit canExecuteChanged(newstate);
}

void CompositeCommand::add(const QSharedPointer<AbstractCommand>& cmd)
{
    bool origCanExecute = canExecute();
    connect(cmd.data(), &AbstractCommand::canExecuteChanged,
            this, &CompositeCommand::onCanExecuteChanged);
    cmds.append(cmd);
    bool newCanExecute = canExecute();
    if(origCanExecute != newCanExecute)
        emit canExecuteChanged(newCanExecute);
    emit commandsChanged();
}

void CompositeCommand::add(AbstractCommand *cmd)
{
    bool origCanExecute = canExecute();
    connect(cmd, &AbstractCommand::canExecuteChanged,
            this, &CompositeCommand::onCanExecuteChanged);
    QQmlEngine::setObjectOwnership ( cmd, QQmlEngine::CppOwnership );
    cmds.append(QSharedPointer<AbstractCommand>(cmd));
    bool newCanExecute = canExecute();
    if(origCanExecute != newCanExecute)
        emit canExecuteChanged(newCanExecute);
    emit commandsChanged();
}

void CompositeCommand::remove(const QSharedPointer<AbstractCommand> &cmd)
{
    bool origCanExecute = canExecute();
    disconnect(cmd.data(), &AbstractCommand::canExecuteChanged,
               this, &CompositeCommand::onCanExecuteChanged);
    bool newCanExecute = canExecute();
    cmds.removeAll(cmd);
    if(origCanExecute != newCanExecute)
        emit canExecuteChanged(newCanExecute);
    emit commandsChanged();
}

void CompositeCommand::clearCommands()
{
    cmds.clear();
    emit commandsChanged();
}

QQmlListProperty<AbstractCommand> CompositeCommand::commands()
{
    return QQmlListProperty<AbstractCommand>(this, this,
                                             &CompositeCommand::appendCommand,
                                             &CompositeCommand::commandCount,
                                             &CompositeCommand::command,
                                             &CompositeCommand::clearCommands);
}

void CompositeCommand::appendCommand(QQmlListProperty<AbstractCommand> *lst, AbstractCommand *cmd)
{
    reinterpret_cast<CompositeCommand *>(lst->data)->add(cmd);
}

int CompositeCommand::commandCount(QQmlListProperty<AbstractCommand> *lst)
{
    return reinterpret_cast<CompositeCommand *>(lst->data)->cmds.count();
}

AbstractCommand* CompositeCommand::command(QQmlListProperty<AbstractCommand> *lst, int idx)
{
    return reinterpret_cast<CompositeCommand *>(lst->data)->cmds.at(idx).data();
}

void CompositeCommand::clearCommands(QQmlListProperty<AbstractCommand> *lst)
{
    reinterpret_cast<CompositeCommand *>(lst->data)->clearCommands();
}
