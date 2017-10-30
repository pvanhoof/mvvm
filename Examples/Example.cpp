#include <QDebug>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MVVM/Commands/RelayCommand.h>

#include "viewmodel.h"
#include "examplelistclass.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<ExampleListClass>("Example", 1, 0,
                                                 "ExampleListClass", "");
    qmlRegisterType<ViewModel>("Example", 1, 0, "ViewModel");

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");
    engine.addImportPath(QMLDIR);
    engine.addPluginPath(SODIR);

    engine.load(QUrl(QStringLiteral("qrc:/Example.qml")));
    return app.exec();
}
