#include <QDebug>
#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <MVVM/Commands/RelayCommand.h>

#include "viewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<ViewModel>("Example", 1, 0, "ViewModel");

    engine.addImportPath("qrc:/");
    engine.addImportPath(QMLDIR);
    engine.addPluginPath(SODIR);

    engine.load(QUrl(QStringLiteral("qrc:/Example.qml")));
    return app.exec();
}
