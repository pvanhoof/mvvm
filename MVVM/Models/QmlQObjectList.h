#ifndef QMLQOBJECTLIST_H
#define QMLQOBJECTLIST_H

#define DECLARE_QML_QOBJECT_LIST(type, name, owner, prop) \
QQmlListProperty<type> name(){ \
   return QQmlListProperty<type>( \
               this, 0,&owner::count ## type ## For ## name ## List, \
               &owner::at ## type ## For ## name ## List); \
} \
static int count ## type ## For ## name ## List(QQmlListProperty<type>*property){ \
   owner *m = qobject_cast<owner *>(property->object); \
   return m->prop.size(); \
} \
static type *at ## type ## For ## name ## List( \
        QQmlListProperty<type>*property, int index){ \
   owner *m = qobject_cast<owner *>(property->object); \
   return m->prop[index]; \
}

#endif // QMLQOBJECTLIST_H
