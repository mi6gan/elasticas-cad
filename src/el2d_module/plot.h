#undef PLOTCLASSNAME
#define PLOTCLASSNAME Plot
#ifndef PLOT_H
#define PLOT_H
#include <QtGui>
#include <QtCore>
class Plot
{
public:    
    enum UpdateMode {LazyUpdate,ImmediateUpdate};
    class Object;
    class Vertex
    {
        friend class Plot::Object;
        friend class Plot;
        QPointF position;
        //QGraphicsEllipseItem* ellipse;
        QList<Plot::Object*> objects;
        void updateObjects();
    protected:
        Plot* owner;
    public:
    /**
      Adds new vertex to a plot.
      \param owner a plot that owns the vertex
      \param pos position of the vertex
    */
    Vertex(Plot* owner,const QPointF & pos);
    //void setRadius(double radius);
    void setPos(const QPointF & pos);
    //void setBrush(const QBrush & brush);
    //void setPen(const QPen & pen);
    //void setVisible(bool visible);
    //double radius();
    QPointF pos();
    //bool isVisible();
    virtual ~Vertex();
    };
    /**
      This class is a base of all plot objects that take as parameters vertices of type Plot::Vertex.
      Any vertex added by Object::addVertex() causes a call of Object::build() when changes its position.
      You can determine your own object based on this class by defining your build(), setPen() and setBrush() methods.
    */
    class Object
    {
    public:
        enum Style {CommonStyle,OwnStyle};
    private:
        friend class Plot::Vertex;
        friend class Plot;
        bool need_to_build;
        bool need_to_delete;
        enum Object::Style style;
    protected:
        Plot* owner;
        QList<Plot::Vertex*> vertices;
        /**
          Adds a vertex the object depends on.
        */
        void addVertex(Plot::Vertex* vertex);
        virtual void build()=0;
        virtual void setPen(const QPen & pen)=0;
        virtual void setBrush(const QBrush & brush)=0;
        virtual void setVisible(bool visible)=0;
    public:
        /**
          Adds new object to a plot.
          \param owner a plot that owns the object
          \param style sets behaviour of brush and pen.
                 If Object::CommonStyle is set brush and pen is controlled by plot of the object.
                 If Object::OwnStyle is set object's brush and pen are independent of plot.
        */
        Object(Plot* owner,enum Object::Style style=CommonStyle);
        void update();
        virtual ~Object();
    };
    friend class Plot::Vertex;
    friend class Plot::Object;
private:
    QBrush cbrush;
    QPen cpen;
    QList<Plot::Vertex*> vertices;
    QList<Plot::Object*> objects;
    QGraphicsScene* scene;
    UpdateMode update_mode;
    bool visible;
public:
    Plot(QGraphicsScene* scene);
    virtual void update();
    QGraphicsScene* graphicsScene();
    void setUpdateMode(const Plot::UpdateMode & update_mode);
    const Plot::UpdateMode & updateMode();
    void setBrush(const QBrush & brush);
    void setPen(const QPen & pen);
    void setVisible(bool visible);
    const QPen & pen();
    const QBrush & brush();
    ~Plot();
};

class PathObject: public Plot::Object
{
protected:
    QGraphicsPathItem* item;
public:
    PathObject(Plot* owner,enum Object::Style style=Plot::Object::CommonStyle);
    virtual void setPen(const QPen &pen);
    virtual void setBrush(const QBrush &brush);
    virtual void setVisible(bool visible);
    ~PathObject();
};

class Line:public PathObject
{
public:
    Line(Plot* owner,Plot::Vertex* p1, Plot::Vertex* p2,enum Object::Style style=Plot::Object::CommonStyle);
    virtual void build();
};

class BezierCurve3: public PathObject
{
public:
    BezierCurve3(Plot* owner,Plot::Vertex* p1, Plot::Vertex* p2,Plot::Vertex* p3,Plot::Vertex* p4,enum Object::Style style=Plot::Object::CommonStyle);
    virtual void build();
};

class Label:public PathObject
{
public:
    Label(Plot* owner,Plot::Vertex* p,const QString & text,bool cross=false,enum Object::Style style=Plot::Object::CommonStyle);
    virtual void build();
};
#endif // PLOT_H
