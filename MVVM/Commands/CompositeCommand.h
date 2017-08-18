#ifndef COMPOSITE_COMMAND_H
#define COMPOSITE_COMMAND_H

#include <QSharedPointer>
#include <QQmlListProperty>

#include <MVVM/Commands/AbstractCommand.h>
#include <MVVM/Commands/ListCommand.h>

class CompositeCommand : public AbstractCommand {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<AbstractCommand> commands READ commands NOTIFY commandsChanged )
    Q_CLASSINFO("DefaultProperty", "commands")
public:
    CompositeCommand(QObject *parent = 0):AbstractCommand (parent) {}
    CompositeCommand(QList<QSharedPointer<AbstractCommand> > cmds, QObject *parent=0);
    ~CompositeCommand();
    void execute() Q_DECL_OVERRIDE;
    bool canExecute() const Q_DECL_OVERRIDE;
    void remove(const QSharedPointer<AbstractCommand> &cmd);
    void add(const QSharedPointer<AbstractCommand> &cmd);

    void add(AbstractCommand *cmd);
    void clearCommands();
    QQmlListProperty<AbstractCommand> commands();

signals:
    void commandsChanged();
private slots:
    void onCanExecuteChanged(bool canExecute);
private:
    QList<QSharedPointer<AbstractCommand> > cmds;
    static void appendCommand(QQmlListProperty<AbstractCommand> *lst, AbstractCommand *cmd);
    static AbstractCommand* command(QQmlListProperty<AbstractCommand> *lst, int idx);
    static void clearCommands(QQmlListProperty<AbstractCommand> *lst);
    static int commandCount(QQmlListProperty<AbstractCommand> *lst);
};

#endif // COMPOSITE_COMMAND_H
