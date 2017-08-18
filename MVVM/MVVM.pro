CONFIG += c++11 qt plugin
QT += qml
TARGET = mvvmplugin
TEMPLATE = lib
INCLUDEPATH += ..
SOURCES += \
    Commands/CompositeCommand.cpp \
    Commands/DelegateCommand.cpp \
    Commands/ListCommand.cpp \
    Commands/EmitCommand.cpp \
    Commands/CommandProxy.cpp \
    Models/CommandListModel.cpp \
    MvvmPlugin.cpp
HEADERS += \
    Commands/AbstractCommand.h \
    Commands/CompositeCommand.h \
    Commands/DelegateCommand.h \
    Commands/ListCommand.h \
    Commands/EmitCommand.h \
    Commands/CommandProxy.h \
    Models/CommandListModel.h \
    MvvmPlugin.h
OTHER_FILES = be/codeminded/mvvm/qmldir Examples/*
unix {
    target.path = /usr/lib
    INSTALLS += target
}


