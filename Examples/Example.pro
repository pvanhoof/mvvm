CONFIG += c++11 qt
QT += qml
TARGET = example
TEMPLATE = app
INCLUDEPATH += ..
SOURCES += Example.cpp \
    asynchellocommand.cpp \
    viewmodel.cpp
OTHER_FILES = ../qmldir .
unix {
    target.path = /usr/lib
    INSTALLS += target
}
DEFINES += SODIR=\\\"$$OUT_PWD/../MVVM/\\\"
DEFINES += QMLDIR=\\\"$$PWD/../MVVM\\\"
LIBS += -L$$OUT_PWD/../MVVM -lmvvmplugin
RESOURCES += qml.qrc

HEADERS += \
    viewmodel.h \
    asynchellocommand.h \
    examplelistclass.h
