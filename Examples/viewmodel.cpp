#include "viewmodel.h"

void ViewModel::resetObjects( )
{
    foreach ( ExampleListClass *mobject, pobjects ) {
        mobject->deleteLater();
    }
    pobjects.clear();
    emit objectsChanged();
}

void ViewModel::appendObject( ExampleListClass *object )
{
    object->setParent( this );
    pobjects.append( object );
    emit objectsChanged();
}

void ViewModel::deleteObject( ExampleListClass *object )
{
    if (pobjects.contains( object )) {
        pobjects.removeOne( object );
        object->deleteLater();
        emit objectsChanged();
    }
}
