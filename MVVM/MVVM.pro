CONFIG += c++11 qt plugin
QT += qml
TARGET = mvvmplugin
TEMPLATE = lib
INCLUDEPATH += ..
SOURCES += \
    Commands/CompositeCommand.cpp \
    Commands/ListCommand.cpp \
    Commands/EmitCommand.cpp \
    Commands/CommandProxy.cpp \
    Models/CommandListModel.cpp \
    MvvmPlugin.cpp \
    Commands/RelayCommand.cpp
HEADERS += \
    Commands/AbstractCommand.h \
    Commands/CompositeCommand.h \
    Commands/ListCommand.h \
    Commands/EmitCommand.h \
    Commands/CommandProxy.h \
    Models/CommandListModel.h \
    MvvmPlugin.h \
    Commands/RelayCommand.h
OTHER_FILES = be/codeminded/mvvm/qmldir Examples/*
unix {
    target.path = /usr/lib
    INSTALLS += target
}


