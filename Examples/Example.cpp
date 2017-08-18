#include <QDebug>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MVVM/Commands/DelegateCommand.h>


DelegateCommand* lambdaCommand = 0;

static QObject* singleton_provider (QQmlEngine *, QJSEngine *)
{
   if (lambdaCommand == 0) {
       lambdaCommand = new  DelegateCommand ( [&] { qWarning() << "Lambda"; },
               [&] { return true; } );
   }
   return lambdaCommand;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<DelegateCommand>("Example", 1, 0, "LambdaCommand", singleton_provider);

    engine.addImportPath(QMLDIR);
    engine.addPluginPath(SODIR);

    engine.load(QUrl(QStringLiteral("qrc:/Example.qml")));
    bool ret = app.exec();
    //delete lambdaCommand;
    return ret;
}
