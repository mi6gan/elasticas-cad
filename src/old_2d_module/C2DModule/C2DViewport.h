#ifndef C2DVIEWPORT_H
#define C2DVIEWPORT_H

#if defined( C2D_UNDO )
    #include <QUndoView>
    #include <QUndoStack>
    #include <QUndoCommand>

    #include <C2DCommands.h>
#endif


#if defined( C2D_DEBUG )
    #include <QDebug>
#endif


#include <QPrinter>
#include <QPrintPreviewDialog>

#include <QMenu>
#include <QLabel>
#include <QToolBar>
#include <QVariant>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVBoxLayout>

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

#include <math.h>

#include "C2DAbstractObject.h"

#include "C2DRuller.h"
#include "C2DPlugin.h"
#include "C2DKernel.h"

#include "Frameworks/Items/include/C2DItem.h"
#include "Frameworks/Items/include/C2DSceneItems.h"

#include "elcore/elcore.h"

class C2DScene: public QGraphicsScene
{
    Q_OBJECT
public:
    C2DScene( QWidget * parent = 0 );
   ~C2DScene();

#if defined( C2D_UNDO )
    QUndoStack * Stack;
#endif

    void setItems( QHash< QString, C2DItem * > items );

    void setSelectionArea(const QPainterPath & path, Qt::ItemSelectionMode mode);
    void HideCurrentObject();

    C2DItem       * UpdateCurrentObject();

    void AddCmd( int type, QPointF P0, QPointF P1 = QPointF(), QPointF P2 = QPointF() );

    inline C2DTool * tool( const QString & t )  {  return this->tools.value( t );  }

    inline const bool isTool( const QString & tool ) const
    {
        if ( this->tools.value( tool ) )
            return true;
        else
            return false;
    }

    inline void setTool( const QString & tool, const QVariant & value )
    {
        if ( this->isTool( tool ) )
            this->tools.value( tool )->setValue( value );
        else
        {
            qWarning( QString( "Tool %1 : tool isn't exist. ( Value to be set : %2 )")
                      .arg( tool )
                      .arg( value.toString() )
                      .toAscii() );
        }
    }

    inline void dropTool( const QString & tool )
    {
        this->tools.value( tool )->drop();
    }

    inline const bool isRuller() const
    {
        if ( this->Ruller )
            return true;
        else
            return false;
    }
    inline const double RullerLength() const
    {
        if ( this->isRuller() )
            return this->Ruller->Length();
        else
            return 0.0f;
    }
    inline void setRuller( const QPointF & point )
    {
        if ( !this->isRuller() )
        {
            this->Ruller = new C2DRuller( point, NULL, this );;
            this->Ruller->setPen( QPen( Qt::lightGray ) );
        }
        else
            this->Ruller->SetEndPoint( point );
    }
    inline void killRuller()
    {
        if ( this->isRuller() )
        {
            this->removeItem( this->Ruller );
            delete this->Ruller;
            this->Ruller = NULL;
        }
    }

    inline const bool isSelection() const
    {
        if ( this->Selection )
            return true;
        else
            return false;
    }
    inline const QRectF & SelectionRect() const
    {
        if ( this->isSelection() )
            this->Selection->rect();
    }
    inline void setSelection( QRectF rect )
    {
        if ( !this->isSelection() )
        {
            this->Selection = new QGraphicsRectItem( rect, NULL, this );
            this->Selection->setOpacity(0.3);
        }
        else
            this->Selection->setRect( rect );
    }
    inline void setSelectionColor( QColor color )
    {
        if ( this->isSelection() )
            this->Selection->setBrush( QBrush( color ) );
    }
    inline void killSelection()
    {
        if ( this->isSelection() )
        {
            this->removeItem( this->Selection );
            delete this->Selection;
            this->Selection = NULL;
        }
    }

public slots:
    void removeTools();


signals:
    void UpdateStatus();

private slots:
    void DialogUpdate();

private:
    bool angle;

    QHash<QString, C2DItem * > C;
    C2DLayerManager * LayerManager;

    //Temporary Items
    QHash< QString, C2DTool * > tools;

    QGraphicsRectItem * Selection;
    QGraphicsPathItem * HoverArea;
    C2DRuller * Ruller, * AngleRuller;

};

class C2DViewport : public QGraphicsView, public TypedObject<C2DViewport>
{
    Q_OBJECT
public:
    enum Mode     { View, MoveItem, Ruller, Angle,
                    InsertPoint, InsertLine, InsertCircle, InsertArc, InsertSingleSpline };
    enum ItemType { Point, Line, Circle, Arc, SingleSpline };

    C2DViewport( QHash< QString, C2DItem * > items );
    ~C2DViewport();

public slots:
    inline void insertPoint()         {  this->setMode( InsertPoint );         }
    inline void insertLine()          {  this->setMode( InsertLine );          }
    inline void insertCircle()        {  this->setMode( InsertCircle );        }
    inline void insertArc()           {  this->setMode( InsertArc );           }
    inline void insertSingleSpline()  {  this->setMode( InsertSingleSpline );  }

    void sendVariables( C2DKernel * kernel );
    void exportItem( C2DKernel * kernel );
    void UpdateCurrentObject();
    void HideCurrentObject();
    void MesureAngle();
    void PrintSheet();
    void addRuller();
    void moveItem();
    void ShowInfo();

signals:
    void cursor( const QPointF & p );
    void hover();

protected:
    bool event( QEvent * e );

    void mousePressEvent( QMouseEvent * e );
    void mouseMoveEvent( QMouseEvent * e );
    void mouseReleaseEvent( QMouseEvent * e );

    void wheelEvent( QWheelEvent * e );
    void keyPressEvent( QKeyEvent * e );

private:
    C2DPlugin * plugin;

    QList< C2DPlugin * > plugins;

    Mode mode;
    void setMode( const Mode & NewMode );

    bool simpleSnap;

    void resetGUI();

    QVector<QPointF> points;
    bool firstclick_flag;
    bool flag1;

    C2DPropertiesDialog * properties;
    C2DScene * scene;
};

class C2DWidget : public QWidget, public TypedObject<C2DWidget>
{
    Q_OBJECT
public:
    C2DWidget();
    ~C2DWidget();

    QToolBar * toolbar();
    inline C2DViewport * view()   const  {  return this->widget_viewport;  }
    inline C2DKernel   * kernel() const  {  return this->widget_kernel;    }

public slots:
    void SetActionDescription( QAction * a );

signals:
    void sendToSheet( C2DKernel * kernel );
    void sendToExport( C2DKernel * kernel );

protected:

private slots:
    void kernelInitiationComplete();
    void Variables();
    void ExportDXF();
//    void sendToKernel( C2DKernel * kernel );
    void setCursorPos( const QPointF & p );
    void ViewportHovered();

private:
    QString                  widget_unit;
    QHash< QString, double > widget_units;

    QMenu       * widget_menu;
    QLabel      * widget_mouse;
    QLabel      * widget_status;
    C2DKernel   * widget_kernel;
    C2DViewport * widget_viewport;
};

#endif // C2DVIEWPORT_H
