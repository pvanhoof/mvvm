#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QDebug>
#include <QObject>
#include <QScopedPointer>

#include <MVVM/Commands/CommandProxy.h>
#include <MVVM/Commands/CompositeCommand.h>
#include <MVVM/Commands/RelayCommand.h>
#include <MVVM/Models/CommandListModel.h>

class ViewModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(CommandProxy* helloCommand READ helloCommand CONSTANT)
public:
    ViewModel(QObject *parent=0):QObject(parent),
        helloCmd(new CompositeCommand()){

        QSharedPointer<CompositeCommand> cCmd = helloCmd.dynamicCast<CompositeCommand>();
        cCmd->add( new RelayCommand ([=] { qWarning() << "Hello1 from C++ RelayCommand"; },
                            [=]{ return true; }));
        cCmd->add( new RelayCommand ([=] { qWarning() << "Hello2 from C++ RelayCommand"; },
                            [=]{ return true; }));
        proxyCmd = new CommandProxy (helloCmd);
    }
    CommandProxy* helloCommand() {
        return proxyCmd;
    }
private:
    QSharedPointer<AbstractCommand> helloCmd;
    CommandProxy *proxyCmd;
};

#endif // VIEWMODEL_H
