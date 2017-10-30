#ifndef EXAMPLELISTCLASS_H
#define EXAMPLELISTCLASS_H

#include <QObject>

class ExampleListClass: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
public:
    ExampleListClass(const QString& title, QObject *parent=0)
        : QObject(parent)
        , ptitle(title){ }

    const QString title() const { return ptitle; }
    void setTitle(const QString& title) {
        ptitle = title; emit titleChanged();
    }

signals:
    void titleChanged();

private:
    QString ptitle;
};

#endif // EXAMPLELISTCLASS_H
