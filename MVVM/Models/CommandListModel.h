#ifndef COMMANDLISTMODEL_H
#define COMMANDLISTMODEL_H

#include <QObject>
#include <QQmlListProperty>

#include <MVVM/Commands/ListCommand.h>

class CommandListModel:public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ListCommand> commands READ commands NOTIFY commandsChanged )
    Q_CLASSINFO("DefaultProperty", "commands")
public:
    CommandListModel(QObject *parent = 0):QObject(parent){}
    void clearCommands();
    int commandCount() const;
    QQmlListProperty<ListCommand> commands();
    void appendCommand(ListCommand *command);
    ListCommand* command(int idx) const;
signals:
    void commandsChanged();
private:
    static void appendCommand(QQmlListProperty<ListCommand> *lst, ListCommand *cmd);
    static ListCommand* command(QQmlListProperty<ListCommand> *lst, int idx);
    static void clearCommands(QQmlListProperty<ListCommand> *lst);
    static int commandCount(QQmlListProperty<ListCommand> *lst);

    QList<ListCommand* > cmds;
};

#endif // COMMANDLISTMODEL_H
