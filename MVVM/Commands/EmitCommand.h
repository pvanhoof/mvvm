#ifndef EMIT_COMMAND_H
#define EMIT_COMMAND_H

#include <MVVM/Commands/AbstractCommand.h>

class EmitCommand : public AbstractCommand {
    Q_OBJECT
    Q_PROPERTY(bool canExecute READ canExecute WRITE setCanExecute NOTIFY privateCanExecuteChanged)
public:
    EmitCommand(QObject *parent=0):AbstractCommand(parent){}

    void execute() Q_DECL_OVERRIDE;
    bool canExecute() const Q_DECL_OVERRIDE;
public slots:
    void setCanExecute(bool canExecute);
signals:
    void executes();
    void privateCanExecuteChanged();
private:
    bool canExe = false;
};

#endif // EMIT_COMMAND_H
