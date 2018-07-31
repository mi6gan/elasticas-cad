#include "C2DViewport.h"

C2DScene::C2DScene( QWidget * parent )
    : QGraphicsScene( parent )
{
    this->setSceneRect( -2000, -2000, 4000, 4000 );

#if defined( C2D_UNDO )
    Stack = new QUndoStack;
#endif

    this->LayerManager = new C2DLayerManager( this );

    Origin * rootAxes = new Origin( this->LayerManager->thick_solid(), NULL, this );

    C.insert( QString( "Primary" ), NULL );
    C.insert( QString( "Secondary" ), NULL );

//    C2DTool * marker = new C2DMarker( QString( "Marker" ),
//                                      Qt::lightGray,
//                                      this->LayerManager->thick_solid(),
//                                      NULL, this );

//    this->tools.insert( marker->name(), marker );

    this->Ruller      = NULL;
    this->Selection   = NULL;
    this->AngleRuller = NULL;

    angle = false;
}

void C2DScene::setItems( QHash< QString, C2DItem * > items )
{
    QHashIterator< QString, C2DItem * >  i( items );

    while( i.hasNext() )
    {
        i.next();

        i.value()->setLayerManager( this->LayerManager );
        i.value()->setScene( this );
        this->addItem( i.value() );
        this->C.insert( i.key(), i.value() );
    }
}

C2DScene::~C2DScene()
{
    C.remove( "Primary" );
    C.remove( "Secondary" );

    if ( !C.isEmpty() )
        foreach ( C2DItem * item, C )
            delete item;

    C.clear();

    this->removeTools();

#if defined( C2D_UNDO )
    delete Stack;
#endif
}

void C2DScene::removeTools()
{
    foreach ( C2DTool * t, this->tools )
        t->drop();

    if ( this->isRuller() )
        this->killRuller();

    if ( this->Selection )
        this->killSelection();

    if ( this->AngleRuller)
    {
        this->removeItem( this->AngleRuller );
        delete this->AngleRuller;
        this->AngleRuller = NULL;
    }
}

C2DItem * C2DScene::UpdateCurrentObject()
{
    QObject::disconnect( this, SLOT( DialogUpdate() ) );

    const Elasticas::CommonData & var = Elasticas::Core::Instance()->CommonVariables();
    QString item =  var.value("SkirtType").toString();

    C2DItem * cp = C.value( "Primary" );

    if ( C.contains( item ) )
        if ( cp != C.value( item ) )
            this->HideCurrentObject();

    if ( C.contains( item ) && ( C.value( item ) != NULL ) )
    {
        qDebug() << "Item update;";

        QHash< QString, QVariant > values;
        QList< C2DExchange * > list;
        QList< C2DVariable * > variables;

        const Elasticas::CommonData & var = Elasticas::Core::Instance()->CommonVariables();

        list.append( C.value( item ) );

        foreach ( C2DItem * child_item, C.value( item )->children() )
            list.append( child_item );

        foreach ( C2DItemDialog * item_dialog, C.value( item )->dialogs() )
            list.append( item_dialog );

        qDebug() << "Exchange list: " << list << "\n\n";

        for ( int i = 0; i < list.count(); i++ )
        {
            values.clear();
            variables.clear();

            variables = list.at( i )->variableList();

            qDebug() << "Exchange variables: " << variables << "\n\n";

            for ( int ind = 0; ind < variables.count(); ind++ )
                if ( var.contains( variables.at( ind )->common_name() ) )
                    values.insert( variables.at( ind )->common_name(),
                                   var.value( variables.at( ind )->common_name() ) );

            qDebug() << "Exchange hash: " << values << "\n\n";

            list.at( i )->updateVariables( values );
        }

        C.value( item )->Update();
        C.value( item )->setVisible( true );

//        if ( C.value( item )->getDialog() )
//            QObject::connect( C.value( item )->getDialog(), SIGNAL( UpdateNeeded() ),
//                              this, SLOT( DialogUpdate() ) );
    }

    C.insert( "Primary", C.value( item ) );

    return C.value( "Primary" );
}

void C2DScene::DialogUpdate()
{
    if ( C.value( "Primary" ) )
        C.value( "Primary" )->Update();

    this->update();
}

void C2DScene::HideCurrentObject()
{
    if ( C.value( "Primary" ) != NULL ) C.value( "Primary" )->hide();
    if ( C.value( "Secondary" ) != NULL ) C.value( "Secondary" )->hide();
}

void C2DScene::AddCmd( int type, QPointF P0, QPointF P1, QPointF P2)
{
    try
    {
    switch ( type )
    {
    case ( POINT_ITEM ):
#if defined( C2D_UNDO )
        QUndoCommand * addPoint;
        addPoint = new AddPoint(P0, LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(addPoint);
#else
        PointItem * item;
        item = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                              LayerManager->CurrentLayer(), C.value("Primary"), this );
        item->setPos( P0 );
#endif
        break;

    case ( LINE_ITEM ):
        #if defined( C2D_UNDO )
        Stack->beginMacro("Add line");
        AddPoint * startPoint;
        AddPoint * endPoint;
        startPoint = new AddPoint(P0, LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(startPoint);
        endPoint = new AddPoint(P1, LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(endPoint);
        AddLine *addLine;
        addLine = new AddLine(startPoint->item(),endPoint->item(), LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(addLine);
        Stack->endMacro();
        #else
        PointItem * line_start, * line_end;

        line_start = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                    LayerManager->CurrentLayer(), C.value("Primary"), this );
        line_start->setPos( P0 );

        line_end   = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                    LayerManager->CurrentLayer(), C.value("Primary"), this );
        line_end->setPos( P1 );

        LineItem * line;
        line = new LineItem( QString( "%1 %2" ).arg( "Line" ).arg( this->items().count() + 1 ),
                             LayerManager->CurrentLayer(), C.value("Primary"), this );
        line->setStartPoint( line_start );
        line->setEndPoint( line_end );
        #endif
        break;
    case ( CIRCLE_ITEM ):
        #if defined( C2D_UNDO )
        Stack->beginMacro("Add circle");
        AddPoint *center;
        center = new AddPoint(P0, LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(center);
        AddCircle *addCircle;
        addCircle = new AddCircle( center->item(),QLineF(P0,P1).length(), LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
        Stack->push(addCircle);
        Stack->endMacro();
        #else
        PointItem * circle_center;
        circle_center = new PointItem(  QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                        LayerManager->CurrentLayer(), C.value("Primary"), this );
        circle_center->setPos( P0 );
        CircleItem * circle;
        circle = new CircleItem(  QString( "%1 %2" ).arg( "Circle" ).arg( this->items().count() + 1 ),
                                  LayerManager->CurrentLayer(), C.value("Primary"), this );
        #endif
        break;
    case ( ARC_ITEM ):
        if ( true )
        {
        QLineF linef( P0,P2 );
        linef.setLength( QLineF( P0, P1 ).length() );

        #if defined( C2D_UNDO )

            Stack->beginMacro("Add arc");
            AddPoint *startArc;
            AddPoint *centerArc;
            AddPoint *endArc;
            AddArc   *addArc;
            centerArc = new AddPoint(P0, LayerManager->CurrentLayer(),  this,  C.value("Primary"), NULL);
            startArc = new AddPoint(P1, LayerManager->CurrentLayer(),  this,  C.value("Primary"), NULL);

            endArc = new AddPoint( linef.p2(), LayerManager->CurrentLayer(), this,  C.value("Primary"), NULL);
            Stack->push(startArc);
            Stack->push(centerArc);
            Stack->push(endArc);

            addArc = new AddArc(centerArc->item(),startArc->item(),endArc->item(), LayerManager->CurrentLayer(),  this,  C.value("Primary"), NULL);
            Stack->push(addArc);
            Stack->endMacro();

        #else
        PointItem * arc_center, * arc_start, * arc_end;

        arc_center = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                    LayerManager->CurrentLayer(), C.value("Primary"), this );
        arc_center->setPos( P0 );

        arc_start  = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                    LayerManager->CurrentLayer(), C.value("Primary"), this );
        arc_start->setPos( P1 );

        arc_end    = new PointItem( QString( "%1 %2" ).arg( "Point" ).arg( this->items().count() + 1 ),
                                    LayerManager->CurrentLayer(), C.value("Primary"), this );
        arc_end->setPos( linef.p2() );

        ArcItem * arc;
        arc = new ArcItem( QString( "%1 %2" ).arg( "Arc" ).arg( this->items().count() + 1 ),
                           LayerManager->CurrentLayer(), C.value("Primary"), this );
        #endif
        }
        break;
    case ( SPLINE_ITEM ):
        #if defined( C2D_UNDO )
        Stack->beginMacro("Add spline");
        Stack->endMacro();
        #else

        #endif
        break;
    }
}
    catch ( const char * e )
    {
        qDebug() << e;
    }
    catch ( QString * e )
    {
        qDebug() << e;
    }
}

void C2DScene::setSelectionArea(const QPainterPath & path, Qt::ItemSelectionMode mode)
{
    QGraphicsScene::setSelectionArea(path,mode);
}




//Graphics View implementation
C2DViewport::C2DViewport( QHash<QString, C2DItem *> items )
    : QGraphicsView(), TypedObject<C2DViewport>()
{
    this->scene = new C2DScene( this );
    this->setScene( this->scene );
    this->scene->setItems( items );

    this->properties = new C2DPropertiesDialog( this );

    this->setMouseTracking( true );
    this->setRenderHints( QPainter::Antialiasing |
                          QPainter::SmoothPixmapTransform );
    this->setTransformationAnchor( QGraphicsView::AnchorUnderMouse );
    this->setResizeAnchor( QGraphicsView::AnchorUnderMouse );
    this->setViewportUpdateMode( QGraphicsView::BoundingRectViewportUpdate );
    this->setMatrix( QMatrix( 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f ) );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setFocus();

    //The string below is for correct sizing in couple with elastiCas
    this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    this->setBackgroundBrush( QBrush( QColor( 0x88888888 ) ) );

    this->setMode( View );
    this->firstclick_flag = false;
    this->simpleSnap = false;
}

C2DViewport::~C2DViewport()
{
    delete this->scene;
}

void C2DViewport::resetGUI()
{
    this->mode = View;
    this->firstclick_flag = false;
    this->scene->clearSelection();

    if ( !this->points.empty() )
        this->points.clear();

    this->scene->removeTools();
}

void C2DViewport::setMode( const Mode & NewMode )
{
    this->resetGUI();
    switch ( NewMode )
    {
    case ( 0 ) :  qDebug() << "View";                   break;
    case ( 1 ) :  qDebug() << "Move";                   break;
    case ( 2 ) :  qDebug() << "Ruller";                 break;
    case ( 3 ) :  qDebug() << "Angle";                  break;
    case ( 4 ) :  qDebug() << "InsertPoint";            break;
    case ( 5 ) :  qDebug() << "InsertLine";             break;
    case ( 6 ) :  qDebug() << "InsertCircle";           break;
    case ( 7 ) :  qDebug() << "InsertArc";              break;
    case ( 8 ) :  qDebug() << "InsertSingleSpline";     break;
    default:      qDebug() << "View";                   break;
    }
    this->mode = NewMode;
}

void C2DViewport::PrintSheet()
{
    QPrinter p( QPrinter::ScreenResolution );
    QPrintPreviewDialog * d = new QPrintPreviewDialog( &p,  this );

    QPainter painter;

    if ( !painter.begin( &p ) )
        qWarning("failed to open file, is it writable?");

    painter.drawText( 10, 10, "Test" );

    painter.end();

    d->exec();
}

void C2DViewport::moveItem()
{
    if ( this->scene->selectedItems().count() != 0 )
        this->setMode( MoveItem );
}

void C2DViewport::addRuller()
{
    if ( this->scene->selectedItems().count() != 0 )
    {
        double length = 0;
        foreach ( QGraphicsItem * i, this->scene->selectedItems() )
        {
            QGraphicsPathItem * j = dynamic_cast< QGraphicsPathItem * > ( i );
            length += j->shape().length();
        }
        QMessageBox::information( NULL, tr("Length"), "The length is: " +
                                  QString( "%1" ).arg(length) + ";",
                                  QMessageBox::Ok );
        this->resetGUI();
    }
    else
    {
        this->resetGUI();
        this->setMode( Ruller );
    }
}

void C2DViewport::MesureAngle()
{
    qDebug()<<"Ruller";
//    double angle = 0;
}


void C2DViewport::ShowInfo()
{
    if ( this->scene->selectedItems().count() != 0 )
    {
        C2DAbstractItem * item = dynamic_cast< C2DAbstractItem * >
                                 ( this->scene->selectedItems().first() );

        QString type = item->getType();
        this->properties->addSection( QString( "General" ) );
        this->properties->addString( QString( "Name" ), QVariant( item->name() ) );
        this->properties->addString( QString( "Type" ), QVariant( type ) );

        this->properties->addSection( QString( "Properties" ) );

        if ( type == QString( "Line" ) )
        {
            this->properties->addString( QString( "Start" ),
                                         QVariant( QString ( "( %1, %2 )")
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(0.0f).x() )
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(0.0f).y() ) ) );

            this->properties->addString( QString("End"),
                                         QVariant( QString ( "( %1, %2 )" )
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(1.0f).x() )
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(1.0f).y() ) ) );

            this->properties->addString( QString("Length"),
                                         QVariant( item->length() ) );
            this->properties->addString( QString("Angle"),
                                         QVariant( dynamic_cast< LineItem * >
                                                   ( item )->angle() ) );
        }
        else
        {
            this->properties->addString( QString("Start"),
                                         QVariant( QString ( "( %1, %2 )")
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(0).x() )
                                         .arg( dynamic_cast< QGraphicsPathItem * >
                                               ( item )->shape().pointAtPercent(0).y() ) ) );

            this->properties->addString( QString("Shape length"), QVariant( item->length() ) );
        }

        if ( type == QString( "Point" ) )
            this->properties->addString( QString("Dependecies"),
                                   QVariant( dynamic_cast< PointItem * > ( item )->depenency() ) );
        if ( type == QString( "Circle" ) )
            this->properties->addString( QString("Radius"),
                                   QVariant( dynamic_cast< CircleItem * > ( item )->getRadius() ) );
        if ( type == QString( "Arc" ) )
            this->properties->addString( QString("Radius"),
                                   QVariant( dynamic_cast< ArcItem * > ( item )->getRadius() ) );
        if ( type == QString( "Arc" ) )
            this->properties->addString( QString("Start angle"),
                                   QVariant( dynamic_cast< ArcItem * > ( item )->startAngle() ) );
        if ( type == QString( "Arc" ) )
            this->properties->addString( QString("Overall angle"),
                                   QVariant( dynamic_cast< ArcItem * > ( item )->arcAngle() ) );
        this->properties->show();
    }
        this->resetGUI();
}

bool C2DViewport::event( QEvent * e )
{
    if ( ( e->type() == QEvent::Enter ) ||
         ( e->type() == QEvent::Leave ) )
            this->hover();

    return QGraphicsView::event( e );
}

void C2DViewport::mousePressEvent( QMouseEvent * e )
{
    if ( this->dragMode() != QGraphicsView::ScrollHandDrag )
    {
        try
        {
            QPointF CurrentPos;
            if ( e->modifiers() == Qt::ShiftModifier && !this->points.empty() && firstclick_flag )
            {
                if ( abs( this->points.at( 0 ).x() - this->mapToScene( e->pos() ).x() ) >
                     abs( this->points.at( 0 ).y() - this->mapToScene( e->pos() ).y() ) )
                    CurrentPos = points.at( 0 ) +
                                 QPointF( this->mapToScene( e->pos() ).x() -
                                          this->points.at( 0 ).x(), 0.0f );
                else
                    CurrentPos = points.at( 0 ) +
                                 QPointF( 0.0f, this->mapToScene( e->pos() ).y() -
                                                this->points.at( 0 ).y() );
            }
            else
                CurrentPos = this->mapToScene( e->pos() );

            switch ( this->mode )
            {
            case ( View ):
                if ( e->button() != Qt::LeftButton )
                    break;

                this->points.push_back( this->mapToScene( e->pos() ) );
                this->scene->setSelection( QRectF( points.at(0), points.at(0) ) );
                this->update();
                break;
            case ( InsertPoint ):
                this->scene->AddCmd( POINT_ITEM, this->mapToScene( e->pos() ) );
                this->resetGUI();
                break;
            case ( InsertLine ):
                if ( !firstclick_flag )
                {
                    this->points.push_back( CurrentPos );
                    this->scene->tool( "Marker" )->setValue( this->points.at( 0 ), true );
                    this->scene->tool( "Marker" )->setValue( this->points.at( 0 ), true );
                    this->firstclick_flag = true;
                }
                else
                {
                    this->scene->AddCmd( LINE_ITEM, this->points.at( 0 ), CurrentPos );
                    this->resetGUI();
                }
                break;
            case ( InsertCircle ):
                if ( !firstclick_flag )
                {
                    this->points.push_back( this->mapToScene( e->pos() ) );
                    this->scene->tool( "Marker" )->setValue( this->points.at(0), true );
                    this->firstclick_flag = true;
                }
                else
                {
                    this->scene->AddCmd( CIRCLE_ITEM, this->points.at(0), this->mapToScene( e->pos() ));
                    this->resetGUI();
                }
                break;

            case ( InsertArc ):
                if ( !firstclick_flag )
                {
                    this->points.push_back( this->mapToScene( e->pos() ) );
                    this->scene->tool( "Marker" )->setValue( this->points.at(0), true );
                    this->firstclick_flag = true;
                }
                else
                {
                    if ( this->points.count() == 1 )
                    {
                        this->scene->tool( "Marker" )->setValue( this->points.at(0) );
                        this->points.push_back( this->mapToScene( e->pos() ) );
                    }
                    else
                    {
                        this->scene->AddCmd( ARC_ITEM, this->points.at(0), this->points.at(1), this->mapToScene( e->pos() ) );
                        this->resetGUI();
                    }
                }
                break;
            case ( InsertSingleSpline ):
                break;

            case ( Ruller ):
                if ( this->scene->isRuller() ) this->scene->setRuller( CurrentPos );
                else
                {
                    this->scene->setRuller( CurrentPos );
                    QMessageBox::information(NULL,
                                             tr("Length"), "The length is: "
                                             + QString( "%1" ).arg( this->scene->RullerLength() ) + ";",
                                             QMessageBox::Ok );
                    this->resetGUI();
                }
                break;
                case ( Angle ):
        //        if ( !this->angle );
                break;
            case ( MoveItem ):
                if ( !firstclick_flag )
                {
                    this->points.push_back( CurrentPos );
                    this->scene->tool( "Marker" )->setValue( this->points.at(0), true );
                    this->firstclick_flag = true;
                }
                else
                {
                    #if defined( C2D_UNDO )
                    QUndoCommand * movePoint = new MovePoint( CurrentPos - this->points.at(0),
                                                              this->scene->selectedItems(), this->scene, NULL);
                    this->scene->Stack->push( movePoint );
                    #else
                    foreach ( QGraphicsItem * item, this->scene->selectedItems() )
                       item->translate( ( CurrentPos - this->points.at( 0 ) ).x(),
                                        ( CurrentPos - this->points.at( 0 ) ).y() );
                    #endif
                    this->resetGUI();
                }
                break;

            default:
                break;
            }
        }
        catch ( const char * e )
        {
            qDebug() << e;
        }
        catch ( QString * e )
        {
            qDebug() << e;
        }
    }
    QGraphicsView::mousePressEvent( e );
}

void C2DViewport::mouseMoveEvent( QMouseEvent * e )
{
    if ( this->dragMode() != QGraphicsView::ScrollHandDrag )
    {
    try
    {
    emit cursor( this->mapToScene( e->pos() ) );
//    if ( this->simpleSnap )
//    {
//        QPainterPath PathSmall, PathBig,Path;
//        // PathSmall.addEllipse(mouseEvent->scenePos(),50,50);
//        // PathBig.addEllipse(mouseEvent->scenePos(),70,70);
//        Path.moveTo( this->mapToScene( e->pos() ) );

//        PathSmall.addPath( PathBig );
//        Path.addPath( PathSmall );
//        HoverArea->setPath( Path );
    QPointF CurrentPos;
    if ( e->modifiers() == Qt::ShiftModifier && this->firstclick_flag )
    {
        if ( abs( this->points.at( 0 ).x() - this->mapToScene( e->pos() ).x() ) >
             abs( this->points.at( 0 ).y() - this->mapToScene( e->pos() ).y() ) )
            CurrentPos = this->points.at( 0 ) +
                         QPointF( this->mapToScene( e->pos() ).x() - this->points.at(0).x(), 0.0f );
        else
            CurrentPos = this->points.at( 0 ) +
                         QPointF( 0.0f, this->mapToScene( e->pos() ).y() - this->points.at(0).y() );
    }
    else
        CurrentPos = this->mapToScene( e->pos() );

    switch ( this->mode )
    {
    case ( View ):
        if ( this->scene->isSelection() )
        {
            if ( this->mapToScene( e->pos() ).x() - this->points.at(0).x() >= 0.0f )
                this->scene->setSelectionColor( Qt::yellow );
            else
                this->scene->setSelectionColor( Qt::blue );

            this->scene->setSelection( QRectF( this->points.at(0), this->mapToScene( e->pos() ) ) );
        }
        break;
    case ( MoveItem ):
            this->scene->tool( "Marker" )->setValue( this->points.at(0) );
            //this->scene->setMarker( QLineF( this->points.at(0), CurrentPos ) );
            this->update();
        break;
    case ( InsertLine ):
            if ( this->firstclick_flag )
            {
                this->scene->tool( "Marker" )->setValue( CurrentPos, false );
                this->update();
            }
        break;
    case ( InsertCircle ):
            if ( this->firstclick_flag )
            {
                this->scene->tool( "Marker" )->setValue( this->mapToScene( e->pos() ), true );
                this->update();
            }
        break;
    case ( InsertSingleSpline ):
        if ( this->firstclick_flag )
        {
            this->scene->tool( "Marker" )->setValue( this->mapToScene( e->pos() ), true );
            this->update();
        }
        break;
    case ( Ruller ):
        if ( this->firstclick_flag )
        {
            this->scene->setRuller( this->mapToScene( e->pos() ) );
            this->update();
        }
        break;
    default:
        break;
    }
}
    catch ( const char * e )
    {
        qDebug() << e;
    }
    catch ( QString * e )
    {
        qDebug() << e;
    }
    }

    QGraphicsView::mouseMoveEvent( e );
}

void C2DViewport::mouseReleaseEvent( QMouseEvent * e )
{
    if ( this->dragMode() != QGraphicsView::ScrollHandDrag )
    {
    try
    {
    switch ( this->mode )
    {
    case ( Angle ):
        break;
    case ( View ):
        if ( this->scene->isSelection() )
        {
            QPainterPath Path;

            Path.addRect( this->scene->SelectionRect() );

            foreach ( QGraphicsItem * item, this->scene->items(Path, Qt::IntersectsItemShape))
            {
                switch ( e->modifiers() )
                {
                case (Qt::AltModifier):
                    item->setSelected( false );
                    break;
                case (Qt::ShiftModifier):
                default:
                    item->setSelected( true );
                    break;
                }
            }
            //qDebug() <<  this->scene->selectedItems().count();
            this->scene->killSelection();
            points.clear();
        }
        break;
    case (MoveItem):
    case (InsertPoint):
    case (InsertLine):
    case (InsertCircle):
    case (InsertArc):
    case (InsertSingleSpline):
    case (Ruller):
        break;
    }
}
    catch ( const char * er )
    {
        qDebug() << er;
    }
    catch ( QString * er )
    {
        qDebug() << er;
    }
    }

    QGraphicsView::mouseReleaseEvent( e );
}

void C2DViewport::keyPressEvent( QKeyEvent * e )
{
//    qDebug() << e->key();
    switch ( e->key() )
    {
         case Qt::Key_G:
            this->setDragMode( QGraphicsView::ScrollHandDrag );
                break;
        case Qt::Key_H:
            this->setDragMode( QGraphicsView::RubberBandDrag );
                break;
        case Qt::Key_F3:
            //this->scene->SetSnap();
        case Qt::Key_F5:
            this->update();
            break;
        case Qt::Key_Equal:
            if ( e->modifiers() == Qt::ControlModifier )
                this->setMatrix( QMatrix( 1.1f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f ), true );
        break;
        case Qt::Key_Minus:
            if ( e->modifiers() == Qt::ControlModifier )
                this->setMatrix( QMatrix( 0.9f, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f ), true );
        break;
        case Qt::Key_Escape:
            this->resetGUI();
        default:
            break;
        return;
    }
}

void C2DViewport::wheelEvent( QWheelEvent * e )
{
    if ( e->delta() > 0.0f )
        this->setMatrix( QMatrix( 0.9f, 0.0f, 0.0f, 0.9f, 0.0f, 0.0f ), true );
    else
        this->setMatrix( QMatrix( 1.1f, 0.0f, 0.0f, 1.1f, 0.0f, 0.0f ), true );
}

void C2DViewport::sendVariables( C2DKernel * kernel )
{
    C2DItem * item = this->scene->UpdateCurrentObject();

    if ( item )
        kernel->saveSheet( item->prefix(), item->getSheetVariables() );
    else
        return;
}

void C2DViewport::exportItem( C2DKernel * kernel )
{
    C2DItem * item = this->scene->UpdateCurrentObject();

    if ( item )
        kernel->exportDXF( item->prefix(), item );
    else
        return;
}
C2DItem* c=NULL;
void C2DViewport::UpdateCurrentObject()
{
    qDebug() << "C2DViewport::UpdateCurrentObject();";
    if(c) c->setVisible(false);
    c = this->scene->UpdateCurrentObject();

    if ( c )
    {
        this->centerOn( c->getViewCenter() );
        //this->parentWidget()->setVisible(true);
    }
    else this->parentWidget()->setVisible(false);

    C2DViewport::update();

    qDebug() << "C2DViewport::UpdateCurrentObject()::end();";
}

void C2DViewport::HideCurrentObject()
{
    scene->HideCurrentObject();
}

C2DWidget::C2DWidget()
    : QWidget(), TypedObject<C2DWidget>()
{
    this->widget_kernel   = new C2DKernel;

    QList< C2DItemDialog * > dialog_list;
    QHash< QString, C2DItem * > items = this->widget_kernel->importItems();

    this->widget_viewport = new C2DViewport( items );

    foreach( C2DItem * i, items )
    {
        dialog_list = i->dialogs();

        qDebug() << "Dialogs: " << dialog_list;

        for ( int j = 0; j < dialog_list.count(); j++ )
            QObject::connect( dialog_list.at( j ), SIGNAL( UpdateNeeded() ),
                              this->widget_viewport, SLOT( UpdateCurrentObject() ) );

        dialog_list.clear();
    }

    this->widget_mouse = new QLabel( this );
    this->widget_mouse->setAlignment( Qt::AlignRight );
    this->widget_mouse->setMaximumHeight( 20 );
    this->widget_mouse->setContentsMargins( 0, 0, 0, 0 );

    this->widget_status = new QLabel( this );
    this->widget_status->setText( QObject::trUtf8( "Пусто" ) );
    this->widget_status->setAlignment( Qt::AlignLeft );
    this->widget_status->setMaximumHeight( 20 );
    this->widget_status->setContentsMargins( 0, 0, 0, 0 );

    this->widget_units.insert( QObject::trUtf8( "мм" ), 1.0f );
    this->widget_units.insert( QObject::trUtf8( "см" ), 0.1f );
    this->widget_units.insert( QObject::trUtf8( "м" ), 0.01f );

    this->widget_unit = QObject::trUtf8( "мм" );

    QGridLayout * l = new QGridLayout( this );
    l->addWidget( this->widget_viewport, 0, 0, 1, 2 );
    l->addWidget( this->widget_status, 1, 0 );
    l->addWidget( this->widget_mouse, 1, 1 );
    this->setLayout( l );


    this->connect( this->widget_viewport, SIGNAL( cursor( const QPointF & ) ),
                   this, SLOT( setCursorPos( const QPointF & ) ) );

    this->connect( this->widget_viewport, SIGNAL( hover() ),
                   this, SLOT( ViewportHovered() ) );

    this->kernelInitiationComplete();

    this->setCursorPos( QPointF( 0.0f, 0.0f ) );
}

C2DWidget::~C2DWidget()
{
    delete this->widget_mouse;
    delete this->widget_status;
    delete this->widget_kernel;
    delete this->widget_viewport;
}

QToolBar * C2DWidget::toolbar()
{
    this->widget_menu = new QMenu( this );

    QAction * action;

    QToolBar * toolbar = new QToolBar( QObject::trUtf8( "2D редактор" ), this );
    toolbar->setContentsMargins( 0, 0, 0, 0 );

    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/1.png" ),
                                         QObject::trUtf8( "Показать текущее изделие" ),
                                         this->view(), SLOT( UpdateCurrentObject() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/del.png" ),
                                         QObject::trUtf8( "Скрыть текущее изделие" ),
                                         this->view(), SLOT( HideCurrentObject() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/ruller.png" ),
                                         QObject::trUtf8( "Линейка" ),
                                         this->view(), SLOT( addRuller() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/info.png" ),
                                         QObject::trUtf8( "Данные о выделенных объектах" ),
                                         this->view(), SLOT( ShowInfo() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/print.png" ),
                                         QObject::trUtf8( "Напечатать отчет" ),
                                         this->view(), SLOT( PrintSheet() ) ) );

    toolbar->addSeparator();

    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/point.png" ),
                                         QObject::trUtf8( "Создать точку" ),
                                         this->view(), SLOT( insertPoint() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/line.png" ),
                                         QObject::trUtf8( "Создать линию" ),
                                         this->view(), SLOT( insertLine() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/circle.png" ),
                                         QObject::trUtf8( "Создать окружность" ),
                                         this->view(), SLOT( insertCircle() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/arc.png" ),
                                         QObject::trUtf8( "Создать сегмент окружности" ),
                                         this->view(), SLOT( insertArc() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/spline.png" ),
                                         QObject::trUtf8( "Создать сплайн" ),
                                         this->view(), SLOT( insertSingleSpline() ) ) );
    this->widget_menu->addAction( toolbar->addAction( QIcon( ":/Images/move.png" ),
                                         QObject::trUtf8( "Перенести" ),
                                         this->view(), SLOT( moveItem() ) ) );

    toolbar->addSeparator();

    this->widget_menu->addAction( toolbar->addAction( QObject::trUtf8( "Переменные" ),
                                         this, SLOT( Variables() ) ) );

    this->widget_menu->addAction( toolbar->addAction( QObject::trUtf8( "Экспорт в DXF" ),
                                         this, SLOT( ExportDXF() ) ) );

    //foreach ( C2DPlugin * plugin, this->widget->view() )

    toolbar->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    QObject::connect( this, SIGNAL( sendToSheet( C2DKernel * ) ),
                      this->view(), SLOT( sendVariables( C2DKernel * ) ) );
    QObject::connect( this, SIGNAL( sendToExport( C2DKernel * ) ),
                      this->view(), SLOT( exportItem( C2DKernel * ) ) );
    QObject::connect( this->widget_menu, SIGNAL( hovered( QAction * ) ),
                      this, SLOT( SetActionDescription( QAction * ) ) );

    return toolbar;
}

void C2DWidget::kernelInitiationComplete()
{

}

void C2DWidget::Variables()
{
    emit sendToSheet( this->widget_kernel );
}

void C2DWidget::ExportDXF()
{
    emit sendToExport( this->widget_kernel );
}


void C2DWidget::setCursorPos( const QPointF & p )
{
    this->widget_mouse->setText( QString( "Cursor: ( %1, %2 ) [%3];" )
                                .arg( p.x() * this->widget_units.value( this->widget_unit ) )
                                .arg( p.y() * this->widget_units.value( this->widget_unit ) )
                                .arg( this->widget_unit )  );
}

void C2DWidget::SetActionDescription( QAction * a )
{
    this->widget_status->setText( a->toolTip() );
}

void C2DWidget::ViewportHovered()
{
    this->widget_status->setText( QObject::trUtf8( "" ) );
}
