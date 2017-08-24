#include "RelayCommand.h"

bool RelayCommand::canExecute() const
{
    return canExecuteDelegate();
}

void RelayCommand::evaluateCanExecute()
{
    emit canExecuteChanged( canExecute() );
}

void RelayCommand::execute()
{
    executeDelegate();
}



