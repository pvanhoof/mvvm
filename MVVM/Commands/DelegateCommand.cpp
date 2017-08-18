#include "DelegateCommand.h"

bool DelegateCommand::canExecute() const
{
    return canExecuteDelegate();
}

void DelegateCommand::evaluateCanExecute()
{
    emit canExecuteChanged( canExecute() );
}

void DelegateCommand::execute()
{
    executeDelegate();
}



