#ifndef MVVMPLUGIN_H
#define MVVMPLUGIN_H

#include <QQmlExtensionPlugin>

class MvvmPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.qt-project.Qt.QQmlExtensionInterface" )
public:
    MvvmPlugin() {}
    virtual ~MvvmPlugin() {}
    void registerTypes(const char* a_uri);
};

#endif // MVVMPLUGIN_H
