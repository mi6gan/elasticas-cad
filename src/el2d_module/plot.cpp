#include "plot.h"
Plot::Vertex::Vertex(Plot *owner,const QPointF & pos)
{
    this->owner=owner;
    //this->ellipse=owner->scene->addEllipse(-1,-1,2,2);
    this->owner->vertices.append(this);
    this->setPos(pos);
}

void Plot::Vertex::updateObjects()
{
    QListIterator<Plot::Object*> it(this->objects);
    while(it.hasNext())
    {
        if(this->owner->update_mode==Plot::LazyUpdate) it.next()->need_to_build=true;
        else it.next()->update();
    }
}


void Plot::Vertex::setPos(const QPointF & pos)
{
    if (this->pos()!=pos)
    {
        //this->ellipse->setPos(pos);
        this->position=pos;
        this->updateObjects();
    }
}
/*
void Plot::Vertex::setRadius(double radius)
{
    this->ellipse->setRect(-1,-1,radius,radius);
}

void Plot::Vertex::setBrush(const QBrush & brush)
{
    this->ellipse->setBrush(brush);
}

void Plot::Vertex::setPen(const QPen & pen)
{
    this->ellipse->setPen(pen);
}

void Plot::Vertex::setVisible(bool visible)
{
    this->ellipse->setVisible(visible);
}
*/
QPointF Plot::Vertex::pos()
{
    //return this->ellipse->pos();
    return this->position;
}

/*
double Plot::Vertex::radius()
{
    return this->ellipse->rect().width();
}

QPen Plot::Vertex::pen()
{
    return this->ellipse->pen();
}

QBrush Plot::Vertex::brush()
{
    return this->ellipse->brush();
}

bool Plot::Vertex::isVisible()
{
    return this->ellipse->isVisible();
}
*/
Plot::Vertex::~Vertex()
{
    QListIterator<Plot::Object*> it(this->objects);
    while(it.hasNext()) delete it.next();
    this->owner->vertices.removeAll(this);
    //this->owner->graphicsScene()->removeItem(ellipse);
}
//-----------------------
Plot::Object::Object(Plot* owner,enum Object::Style style)
{
    this->owner=owner;
    this->style=style;
    this->need_to_build=true;
    this->need_to_delete=false;
    this->owner->objects.append(this);
}

void Plot::Object::addVertex(Plot::Vertex* vertex)
{
    vertex->objects.append(this);
    vertices.append(vertex);
}

void Plot::Object::update()
{
    if(this->need_to_build)
    {
        if(this->style==Object::CommonStyle)
        {
            this->setPen(owner->pen());
            this->setBrush(owner->brush());
        }
        this->build();
    }
    this->need_to_build=false;
}

Plot::Object::~Object()
{
    QListIterator<Plot::Vertex*> it(vertices);
    while(it.hasNext()) it.next()->objects.removeAll(this);
    this->owner->objects.removeAll(this);
}

//-----------------------
Plot::Plot(QGraphicsScene *scene)
{
    this->scene=scene;
    this->update_mode=Plot::LazyUpdate;
    this->visible=true;
}

void Plot::update()
{
    QListIterator<Plot::Object*> it2(this->objects);
    while(it2.hasNext()) it2.next()->update();
}

QGraphicsScene* Plot::graphicsScene()
{
    return this->scene;
}

void Plot::setUpdateMode(const Plot::UpdateMode & update_mode)
{
    this->update_mode=update_mode;
}

const Plot::UpdateMode & Plot::updateMode()
{
    return this->update_mode;
}

void Plot::setBrush(const QBrush & brush)
{
    QListIterator<Plot::Object*> it1(this->objects);
    while(it1.hasNext())
    {
        Plot::Object* o=it1.next();
        if(o->style==Object::CommonStyle) o->setBrush(brush);
    }
    this->cbrush=brush;
}

void Plot::setPen(const QPen & pen)
{
    QListIterator<Plot::Object*> it1(this->objects);
    while(it1.hasNext())
    {
        Plot::Object* o=it1.next();
        if(o->style==Object::CommonStyle) o->setPen(pen);
    }
    this->cpen=pen;
}

void Plot::setVisible(bool visible)
{
    if(this->visible==visible) return;
    QListIterator<Plot::Object*> it1(this->objects);
    while(it1.hasNext()) it1.next()->setVisible(visible);
    this->visible=visible;
}

const QPen & Plot::pen()
{
    return this->cpen;
}

const QBrush & Plot::brush()
{
    return this->cbrush;
}

Plot::~Plot()
{
    while(this->vertices.count()) delete this->vertices.first();
    while(this->objects.count()) delete this->objects.first();
}
//----------------------
PathObject::PathObject(Plot* owner,enum Object::Style style):Plot::Object(owner,style)
{
    this->item=this->owner->graphicsScene()->addPath(QPainterPath());
}

void PathObject::setPen(const QPen & pen)
{
    this->item->setPen(pen);
}

void PathObject::setBrush(const QBrush & brush)
{
    this->item->setBrush(brush);
}

void PathObject::setVisible(bool visible)
{
    this->item->setVisible(visible);
}

PathObject::~PathObject()
{
    this->owner->graphicsScene()->removeItem(item);
}

//-----------------------

Line::Line(Plot *owner, Plot::Vertex* p1, Plot::Vertex* p2,enum Plot::Object::Style style):PathObject(owner,style)
{
    this->addVertex(p1);
    this->addVertex(p2);
    this->build();
}

void Line::Line::build()
{
    QPainterPath path;
    path.moveTo(vertices[0]->pos());
    path.lineTo(vertices[1]->pos());
    this->item->setPath(path);
}
//-----------------------

BezierCurve3::BezierCurve3(Plot* owner,Plot::Vertex* p1, Plot::Vertex* p2,Plot::Vertex* p3,Plot::Vertex* p4,enum Object::Style style):PathObject(owner,style)
{
    this->addVertex(p1); this->addVertex(p2);
    this->addVertex(p3); this->addVertex(p4);
}

void BezierCurve3::build()
{
    this->item->setBrush(QBrush(Qt::NoBrush));
    QPainterPath path;
    path.moveTo(vertices[0]->pos());
    path.cubicTo(vertices[1]->pos(),vertices[2]->pos(),vertices[3]->pos());
    this->item->setPath(path);
}

//-----------------------
Label::Label(Plot* owner,Plot::Vertex* p,const QString & text,bool cross,enum Object::Style style):PathObject(owner,style)
{
    this->addVertex(p);
    QPainterPath path;
    path.addText(0,0,QFont(),text);
    if(cross)
    {
        path.moveTo(-5,-5);
        path.lineTo(5,5);
        path.moveTo(-5,5);
        path.lineTo(5,-5);
    }
    this->item->setPath(path);
    this->build();
}

void Label::build()
{
    this->item->setPos(vertices[0]->pos());
}
