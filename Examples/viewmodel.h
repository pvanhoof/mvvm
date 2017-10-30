#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QDebug>
#include <QObject>
#include <QScopedPointer>
#include <QQmlListProperty>

#include <MVVM/Commands/AbstractCommand.h>
#include <MVVM/Commands/AbstractAsyncCommand.h>

#include <MVVM/Commands/CommandProxy.h>
#include <MVVM/Commands/CompositeCommand.h>
#include <MVVM/Commands/RelayCommand.h>
#include <MVVM/Models/CommandListModel.h>
#include <MVVM/Models/QmlQObjectList.h>


#include "asynchellocommand.h"
#include "examplelistclass.h"

class ViewModel: public QObject
{
    Q_OBJECT

    Q_PROPERTY(CommandProxy* helloCommand READ helloCommand CONSTANT)
    Q_PROPERTY(AbstractAsyncCommand* asyncHelloCommand READ asyncHelloCommand CONSTANT)

    Q_PROPERTY(const QList<ExampleListClass*> objects READ objects
                                             NOTIFY objectsChanged )
    Q_PROPERTY( QQmlListProperty<ExampleListClass> objectList READ objectList
                                             NOTIFY objectsChanged )
public:
    ViewModel(QObject *parent=0)
        : QObject(parent)
        , helloCmd(new CompositeCommand())
        , asyncCmd(new AsyncHelloCommand )
    {

        QSharedPointer<CompositeCommand> cCmd = helloCmd.dynamicCast<CompositeCommand>();
        cCmd->add( new RelayCommand ([=] {
            qWarning() << "Hello1 from C++ RelayCommand " << objects().length();
            appendObject(new ExampleListClass("Hello"));
        }, [=]{ return true; }));
        cCmd->add( new RelayCommand ([=] { qWarning() << "Hello2 from C++ RelayCommand"; },
                            [=]{ return true; }));
        proxyCmd = new CommandProxy (helloCmd);
    }

    CommandProxy* helloCommand() {
        return proxyCmd;
    }

    AbstractAsyncCommand* asyncHelloCommand() {
        return asyncCmd.data();
    }

    const QList<ExampleListClass*> objects ()
           { return pobjects; }
    Q_INVOKABLE void appendObject( ExampleListClass *object);
    Q_INVOKABLE void deleteObject( ExampleListClass *object);
    Q_INVOKABLE void resetObjects();

signals:
    void objectsChanged();

protected:
    DECLARE_QML_QOBJECT_LIST(ExampleListClass, objectList, ViewModel, pobjects)

private:
    QSharedPointer<AbstractCommand> helloCmd;
    QSharedPointer<AbstractAsyncCommand> asyncCmd;
    CommandProxy *proxyCmd;
    QList<ExampleListClass*> pobjects;
};

#endif // VIEWMODEL_H
