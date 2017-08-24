#include <QtQml>

#include <QAbstractListModel>

#include <MVVM/MvvmPlugin.h>

#include <MVVM/Commands/AbstractCommand.h>
#include <MVVM/Commands/CommandProxy.h>
#include <MVVM/Commands/CompositeCommand.h>
#include <MVVM/Commands/RelayCommand.h>
#include <MVVM/Commands/EmitCommand.h>
#include <MVVM/Commands/ListCommand.h>

#include <MVVM/Models/CommandListModel.h>

void MvvmPlugin::registerTypes(const char* uri)
{
    qmlRegisterType<QAbstractListModel>();

    qmlRegisterUncreatableType<AbstractCommand>(uri, 1,0, "AbstractCommand", "uncreatable");

    qmlRegisterType<CommandProxy>(uri, 1,0, "CommandProxy");
    qmlRegisterType<CompositeCommand>(uri, 1,0, "CompositeCommand");
    qmlRegisterUncreatableType<RelayCommand>(uri, 1,0, "DelegateCommand", "uncreatable");
    qmlRegisterType<EmitCommand>(uri, 1,0, "EmitCommand");
    qmlRegisterType<ListCommand>(uri, 1,0, "ListCommand");

    qmlRegisterType<CommandListModel>(uri, 1,0, "CommandListModel");
}
