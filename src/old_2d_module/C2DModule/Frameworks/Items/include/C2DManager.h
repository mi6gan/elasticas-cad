#ifndef C2DMANAGER_H
#define C2DMANAGER_H

#include <QAction>
#include <QObject>

#include "C2DDialog.h"

class C2DManager: public QObject
{
    Q_OBJECT
public:
    C2DManager( const QString & name, QObject * parent );
    ~C2DManager();

    const QList< QAction * > getActions() const;

protected:
    C2DDialog * dialog;

    QList< QAction * > actions;

private slots:
    void invokeDialog();

private:
    virtual void setActions();

};

#endif //C2DMANAGER_H

