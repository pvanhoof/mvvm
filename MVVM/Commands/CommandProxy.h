#ifndef COMMAND_PROXY_H
#define COMMAND_PROXY_H

#include <QSharedPointer>

#include <MVVM/Commands/AbstractCommand.h>

class CommandProxy:public AbstractCommand {
    Q_OBJECT
public:
    CommandProxy(QObject *parent = 0);
    CommandProxy(const CommandProxy &other);
    CommandProxy(QSharedPointer<AbstractCommand> &cmd, QObject *parent = 0);
    CommandProxy &operator=(const CommandProxy &other);
    void execute() Q_DECL_OVERRIDE;
    bool canExecute() const Q_DECL_OVERRIDE;
private:
    QSharedPointer<AbstractCommand> cmd;
};

Q_DECLARE_METATYPE(CommandProxy)

#endif // COMMAND_PROXY_H
