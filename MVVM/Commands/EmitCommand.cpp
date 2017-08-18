#include "EmitCommand.h"

void EmitCommand::setCanExecute(bool canExecute)
{
    if (canExe != canExecute) {
        canExe = canExecute;
        emit canExecuteChanged(canExe);
        emit privateCanExecuteChanged();
    }
}

bool EmitCommand::canExecute() const
{
    return canExe;
}

void EmitCommand::execute()
{
    emit executes();
}
