#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H

#include <QObject>

class AbstractCommand : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool canExecute READ canExecute NOTIFY canExecuteChanged)
public:
    AbstractCommand(QObject *parent = 0):QObject(parent){}
    Q_INVOKABLE virtual void execute() = 0;
    virtual bool canExecute() const = 0;
signals:
    void canExecuteChanged(bool canExecute);
};

#endif // ABSTRACT_COMMAND_H
