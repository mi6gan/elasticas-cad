//Commands for Undo/Redo System;
//
//Task: functional addition;
//
//Includes: Custom Graphics Items
//
//Dependencies: C2D Custom Graphics Items
//

#ifndef C2DCOMMANDS_H
#define C2DCOMMANDS_H

#include <QUndoCommand>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

#include <C2DViewport.h>
#include <C2DSceneItems.h>

class C2DScene;

class AddPoint : public QUndoCommand
{
public:
    AddPoint( QPointF P0,
              C2DLayer* Layer,
              C2DScene *graphicsScene,
              QGraphicsItemGroup * group,
              QUndoCommand *parent);

    void undo();
    void redo();
    PointItem *item() const;

private:
    PointItem *myItem;
    C2DLayer* myLayer;
    QPointF Pos;
    C2DScene * myScene;
};

class AddLine : public QUndoCommand
{
public:
    AddLine(PointItem *P0,
            PointItem  *P1,
            C2DLayer* Layer,
            C2DScene *graphicsScene,
            QGraphicsItemGroup * group,
            QUndoCommand *parent);

    void undo();
    void redo();

private:
    LineItem * myItem;
    PointItem * Pos0, * Pos1;
    C2DLayer * myLayer;
    C2DScene * myScene;
};

class AddCircle : public QUndoCommand
{
public:
    AddCircle(PointItem * P0,
              double R,
              C2DLayer * Layer,
              C2DScene * graphicsScene,
              QGraphicsItemGroup * group,
              QUndoCommand *parent);

    void undo();
    void redo();
    PointItem * item() const;

private:
    CircleItem * myItem;
    PointItem * center;
    double Radius;
    C2DScene * myScene;
};

class AddArc : public QUndoCommand
{
public:
    AddArc(PointItem * P0,
           PointItem * P1,
           PointItem * P2,
           C2DLayer * Layer,
           C2DScene *graphicsScene,
           QGraphicsItemGroup * group,
           QUndoCommand *parent);

    void undo();
    void redo();

private:
    ArcItem *myItem;
    PointItem *center,*start,*end;
    C2DScene *myScene;
};


class AddSingleSpline : public QUndoCommand
{
public:
    AddSingleSpline(PointItem * P0,
                    QPointF & P1,
                    QPointF & P2,
                    PointItem * P3,
                    C2DLayer * Layer,
                    C2DScene *graphicsScene,
                    QGraphicsItemGroup * group,
                    QUndoCommand *parent);

    void undo();
    void redo();

private:
    SplineItem *myItem;
    PointItem *start,*end;
    QPointF *startGuide,*endGuide;
    C2DScene *myScene;
};

class MovePoint : public QUndoCommand
{
public:
    MovePoint(QPointF translation,
              QList<QGraphicsItem*> points,
              C2DScene *graphicsScene,
              QUndoCommand *parent);

    void undo();
    void redo();

private:
    QList<QGraphicsItem*> Points;
    QPointF Translation;
    C2DScene *myScene;
};

#endif // C2DCOMMANDS_H
