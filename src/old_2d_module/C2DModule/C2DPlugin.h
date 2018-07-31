#ifndef C2DPLUGIN_H
#define C2DPLUGIN_H

#ifdef Q_WS_WIN
#define EXPORTSPEC __declspec(dllexport)
#else
#define EXPORTSPEC
#endif

#include <QAction>
#include <QString>
#include <QPointF>
#include <QMouseEvent>

class C2DPlugin
{

public:
    C2DPlugin();

    const QAction * action() const;

    C2DPlugin * plugin();

    void init();

protected:
    virtual void MousePressHandler( QMouseEvent * e ) = 0;
    virtual void MouseMoveHandler( QMouseEvent * e ) = 0;
    virtual void MouseReleaseHandler( QMouseEvent * e ) = 0;
};

#endif // C2DPLUGIN_H
