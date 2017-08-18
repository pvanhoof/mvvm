#include <QtQml>

#include "CommandProxy.h"

CommandProxy::CommandProxy(QObject *parent)
    :   AbstractCommand(parent)
{
    QQmlEngine::setObjectOwnership (this, QQmlEngine::JavaScriptOwnership);
}

CommandProxy::CommandProxy(const CommandProxy &other)
    :   AbstractCommand(nullptr)
    ,   cmd (other.cmd)
{
    QQmlEngine::setObjectOwnership (this, QQmlEngine::JavaScriptOwnership);
    connect(cmd.data(), &AbstractCommand::canExecuteChanged,
             this, &AbstractCommand::canExecuteChanged);
}

CommandProxy::CommandProxy(QSharedPointer<AbstractCommand> &proxied, QObject *parent)
    : AbstractCommand(parent)
    , cmd (proxied)
{
    QQmlEngine::setObjectOwnership (this, QQmlEngine::JavaScriptOwnership);
    connect(proxied.data(), &AbstractCommand::canExecuteChanged,
            this, &AbstractCommand::canExecuteChanged);
}

void CommandProxy::execute()
{
    cmd->execute();
}

bool CommandProxy::canExecute() const
{
    return cmd->canExecute();
}

CommandProxy &CommandProxy::operator=(const CommandProxy &other)
{
    disconnect(cmd.data(), &AbstractCommand::canExecuteChanged,
               this, &AbstractCommand::canExecuteChanged);
    cmd = other.cmd;
    connect(cmd.data(), &AbstractCommand::canExecuteChanged,
            this, &AbstractCommand::canExecuteChanged);
    return *this;
}
