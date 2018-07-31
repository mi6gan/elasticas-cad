#include "C2DCommands.h"

AddPoint::AddPoint(QPointF P0,
                   C2DLayer* Layer,
                   C2DScene *graphicsScene,
                   QGraphicsItemGroup * group,
                   QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    Pos = P0;
    myLayer=Layer;
    myItem = new PointItem( Pos, myLayer, group, NULL );
    setText(QObject::tr("Add point"));
}

void AddPoint::undo()
{
    myScene->removeItem(myItem);
}

void AddPoint::redo()
{
    myScene->addItem(myItem);
    myItem->setPos(Pos);
}

PointItem* AddPoint::item() const
{
    return myItem;
}

AddLine::AddLine(PointItem * P0,
                 PointItem * P1,
                 C2DLayer * Layer,
                 C2DScene * graphicsScene,
                 QGraphicsItemGroup * group,
                 QUndoCommand * parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    Pos0 = P0;
    Pos1 = P1;
    myItem = new LineItem( Pos0, Pos1, Layer, group, myScene );
    Pos0->setParent( myItem );
    Pos1->setParent( myItem );
    setText( QObject::tr("Add line") );
}

void AddLine::undo()
{
    myScene->removeItem(myItem);
    myScene->removeItem(Pos0);
    myScene->removeItem(Pos1);
}

void AddLine::redo()
{
    myScene->addItem(Pos0);
    myScene->addItem(Pos1);
    myScene->addItem(myItem);
    myScene->clearSelection();
}

AddCircle::AddCircle(PointItem * P0,
                     double R,
                     C2DLayer * Layer,
                     C2DScene * graphicsScene,
                     QGraphicsItemGroup * group,
                     QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    center = P0;
    Radius = R;
    myItem = new CircleItem(center,R, Layer, group,myScene);
    center->setParent(myItem);
    //myScene->addItem(myItem);
    myScene->update();
    setText(QObject::tr("Add circle"));
}

void AddCircle::undo()
{
    myScene->removeItem(myItem);
    myScene->removeItem(center);
    myScene->update();
}

void AddCircle::redo()
{
    myScene->addItem(myItem);
    myScene->addItem(center);
    myScene->clearSelection();
    myScene->update();
}

AddArc::AddArc( PointItem * P0,
                PointItem * P1,
                PointItem * P2,
                C2DLayer * Layer,
                C2DScene * graphicsScene,
                QGraphicsItemGroup * group,
                QUndoCommand * parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    center = P0;
    start = P1;
    end = P2;
    myItem = new ArcItem(center,start,end, Layer, group,myScene);
    center->setParent(myItem);
    start->setParent(myItem);
    end->setParent(myItem);
    //myScene->addItem(myItem);
    myScene->update();
    setText(QObject::tr("Add arc"));
}

void AddArc::undo()
{
    myScene->removeItem(myItem);
    myScene->removeItem(center);
    myScene->removeItem(start);
    myScene->removeItem(end);
    myScene->update();
}

void AddArc::redo()
{
    myScene->addItem(myItem);
    myScene->addItem(center);
    myScene->addItem(start);
    myScene->addItem(end);
    myScene->clearSelection();
    myScene->update();
}


AddSingleSpline::AddSingleSpline( PointItem * P0,
                                  QPointF & P1,
                                  QPointF & P2,
                                  PointItem * P3,
                                  C2DLayer * Layer,
                                  C2DScene * graphicsScene,
                                  QGraphicsItemGroup * group,
                                  QUndoCommand * parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    start = P0;
    *startGuide = P1;
    *endGuide = P2;
    end = P3;
    myItem = new SingleSplineItem(start,*startGuide,*endGuide,end, Layer, group,myScene);
    start->setParent(myItem);
    end->setParent(myItem);
   // myScene->addItem(myItem);
    myScene->update();
    setText(QObject::tr("Add spline"));
}

void AddSingleSpline::undo()
{
    myScene->removeItem(myItem);
    myScene->removeItem(start);
    myScene->removeItem(end);
    myScene->update();
}

void AddSingleSpline::redo()
{
    myScene->addItem(myItem);
    myScene->addItem(start);
    myScene->addItem(end);
    myScene->clearSelection();
    myScene->update();
}


MovePoint::MovePoint(QPointF translation,
                     QList<QGraphicsItem * > points,
                     C2DScene * graphicsScene,
                     QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myScene = graphicsScene;
    Translation = translation;
    Points = points;
 //   foreach (QGraphicsItem* item, Points)
 //   {
 //      item->translate(Translation.x(),Translation.y());
 //   }
 //   myScene->update();
    setText(QObject::tr("Move points"));
}

void MovePoint::undo()
{
    foreach (QGraphicsItem* item, Points)
    {
       item->translate(-Translation.x(),-Translation.y());
    }
    myScene->update();
}

void MovePoint::redo()
{
    foreach (QGraphicsItem* item, Points)
    {
       item->translate(Translation.x(),Translation.y());
    }
    myScene->clearSelection();
    myScene->update();
}
