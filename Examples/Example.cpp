#include <QDebug>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MVVM/Commands/RelayCommand.h>


RelayCommand* lambdaCommand = 0;

static QObject* singleton_provider (QQmlEngine *, QJSEngine *)
{
   if (lambdaCommand == 0) {
       lambdaCommand = new  RelayCommand ( [&] { qWarning() << "Lambda"; },
               [&] { return true; } );
   }
   return lambdaCommand;
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<RelayCommand>("Example", 1, 0, "LambdaCommand", singleton_provider);

    engine.addImportPath(QMLDIR);
    engine.addPluginPath(SODIR);

    engine.load(QUrl(QStringLiteral("qrc:/Example.qml")));
    bool ret = app.exec();
    //delete lambdaCommand;
    return ret;
}
