#include "CommandListModel.h"

QQmlListProperty<ListCommand> CommandListModel::commands()
{
    return QQmlListProperty<ListCommand>(this, this,
                                         &CommandListModel::appendCommand,
                                         &CommandListModel::commandCount,
                                         &CommandListModel::command,
                                         &CommandListModel::clearCommands);
}

void CommandListModel::appendCommand(ListCommand *command)
{
    cmds.append( command );
    emit commandsChanged();
}

int CommandListModel::commandCount() const
{
    return cmds.count();
}

ListCommand *CommandListModel::command(int idx) const
{
    return cmds.at(idx);
}

void CommandListModel::clearCommands()
{
    cmds.clear();
    emit commandsChanged();
}

void CommandListModel::appendCommand(QQmlListProperty<ListCommand> *lst, ListCommand *cmd)
{
    reinterpret_cast<CommandListModel *>(lst->data)->appendCommand(cmd);
}

int CommandListModel::commandCount(QQmlListProperty<ListCommand> *lst)
{
    return reinterpret_cast<CommandListModel *>(lst->data)->commandCount();
}

ListCommand *CommandListModel::command(QQmlListProperty<ListCommand> *lst, int idx)
{
    return reinterpret_cast<CommandListModel *>(lst->data)->command(idx);
}

void CommandListModel::clearCommands(QQmlListProperty<ListCommand> *lst)
{
    reinterpret_cast<CommandListModel *>(lst->data)->clearCommands();
}
