#ifndef LIST_COMMAND_H
#define LIST_COMMAND_H

#include <QSharedPointer>

#include <MVVM/Commands/AbstractCommand.h>

class ListCommand : public AbstractCommand{
    Q_OBJECT
    Q_PROPERTY(AbstractCommand *command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    ListCommand(QObject *parent = 0):AbstractCommand(parent){}
    ListCommand(const QSharedPointer<AbstractCommand> &newCommand, QObject *parent = 0);

    void execute() Q_DECL_OVERRIDE;
    bool canExecute() const Q_DECL_OVERRIDE;
    AbstractCommand* command() const;
    void setCommand(AbstractCommand *newCommand);
    void setCommand(const QSharedPointer<AbstractCommand> &newCommand);
    QString text() const;
    void setText(const QString &newValue);
signals:
    void commandChanged();
    void textChanged();
private:
    QSharedPointer<AbstractCommand> cmd;
    QString txt;
};

#endif // LIST_COMMAND_H
