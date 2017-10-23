#include <QtQml>

#include "ListCommand.h"

ListCommand::ListCommand(const QSharedPointer<AbstractCommand> &newCommand, QObject *parent)
    :AbstractCommand(parent)
{
    setCommand(newCommand);
}

bool ListCommand::canExecute() const
{
    if(!cmd.isNull())
        return cmd->canExecute();
    return false;
}

void ListCommand::execute()
{
    if(!cmd.isNull())
        cmd->execute();
}

AbstractCommand* ListCommand::command() const
{
    return cmd.data();
}

void ListCommand::setCommand(const QSharedPointer<AbstractCommand> &newCommand)
{
    if(cmd.data() != newCommand) {
        cmd = newCommand;
        emit commandChanged();
        if(newCommand != nullptr)
            connect(cmd.data(), &AbstractCommand::canExecuteChanged,
                     this, &AbstractCommand::canExecuteChanged);
        emit canExecuteChanged(cmd->canExecute());
    }
}

void ListCommand::setCommand(AbstractCommand *newCommand)
{
    if(cmd.data() != newCommand) {
        cmd.reset(newCommand);
        QQmlEngine::setObjectOwnership (newCommand, QQmlEngine::CppOwnership);
        emit commandChanged();
        if(newCommand != nullptr)
            connect(cmd.data(), &AbstractCommand::canExecuteChanged,
                     this, &AbstractCommand::canExecuteChanged);
        emit canExecuteChanged(cmd->canExecute());
    }
}

QString ListCommand::text() const
{
    return txt;
}

void ListCommand::setText(const QString &newValue)
{
    if(txt != newValue) {
        txt = newValue;
        emit textChanged();
    }
}
