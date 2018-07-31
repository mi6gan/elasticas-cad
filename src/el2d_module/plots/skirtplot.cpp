#include "skirtplot.h"
#define LD(A) 10.0f*V[QString("StraightSkirt:")+A].toDouble()
#define D(A) 10.0f*V[QString("StraightSkirt:")+A].toDouble()
#define I(A) V[QString("StraightSkirt:")+A].toInt()
#define B(A) V[QString("StraightSkirt:")+A].toBool()
#define PP(A) P[A]->pos()
#define T(A) 10.0f*V[QString("Woman:")+A].toDouble()
#define PointOnRay(center,angle,ray_length) QPointF( ( center.x() + ray_length * cos( angle * M_PI / 180.0f ) ), ( center.y() + ray_length * sin( angle * M_PI / 180.0f ) ) )
#define rLine( line, center, angle) QLineF( rPoint( line.p1(), center , angle ), rPoint( line.p2(), center , angle ) )

const QPointF rPoint( const QPointF &point, const QPointF &center, double angle )
{
    // Angle [ deg ]

    QPointF T1( point.x() - center.x(), point.y() - center.y() );
    return QPointF( ( center.x() + T1.x() * cos( angle * M_PI / 180.0f )
                                 + T1.y() * ( -sin( angle * M_PI / 180.0f ) ) ),
                    ( center.y() + T1.x() * sin( angle * M_PI / 180.0f )
                                 + T1.y() * cos( angle * M_PI / 180.0f ) ) );
}

const QLineF uNormal( QLineF line, bool right_pair )
{
    double k;
    if ( right_pair )
        k =  1;
    else
        k = -1;

    line = rLine( line, line.p1(), k * 90.0f );

    QLineF l;
    l.setP2( QPointF( ( line.dx() ),
                      ( line.dy() ) ) );
    l.setP1( QPointF( 0.0f, 0.0f ) );

    return l;
}
SkirtPlot::SkirtPlot(QGraphicsScene* scene):Plot(scene)
{
    const QString pnames[]={"P0","View:Center","P91","P94","P97","P51","P54",
                            "P57","P41","P47","P47a","P420","P460","PT1","PT2",
                            "P-C-001","P-C-002", "P941","P941a","SG3","SG4",
                            "P54a","SG0","P9411","SG5","P9411a","SG1","P9412",
                            "SG6","P9412a","SG2","NarrowStartLeft","NarrowStartRight",
                            "V:L:TT","V:L:RT","V:L:LT","V:L:LB","V:L:RB",
                            "V:R:TT","V:R:LT","V:R:RT","V:R:RB","V:R:LB",
                            "V:S:L:TT","V:S:L:LB","V:S:L:LT","V:S:L:RB",
                            "V:S:L:RT","V:S:R:TT","V:S:R:RB","V:S:R:RT",
                            "V:S:R:LB","V:S:R:LT", "SideDart1TopPosition",
                            "SideDart1Position","SideDart1SplineBottom",
                            "SideDart1Right","SideDart1SplineRight",
                            "SideDart1Left","SideDart1SplineLeft",
                            "SideDart1ConnectionLeft","SideDart1ConnectionRight",
                            "BackDart1TopPosition","BackDart1Position",
                            "BackDart1SplineBottom","BackDart1Right",
                            "BackDart1SplineRight","BackDart1Left",
                            "BackDart1SplineLeft","BackDart1ConnectionLeft",
                            "BackDart1ConnectionRight","BackDart2TopPosition",
                            "BackDart2Position","BackDart2SplineBottom",
                            "BackDart2Right","BackDart2SplineRight",
                            "BackDart2Left","BackDart2SplineLeft",
                            "BackDart2ConnectionLeft","BackDart2ConnectionRight",
                            "BackDart3TopPosition","BackDart3Position",
                            "BackDart3SplineBottom","BackDart3Right",
                            "BackDart3SplineRight","BackDart3Left",
                            "BackDart3SplineLeft","BackDart3ConnectionLeft",
                            "BackDart3ConnectionRight","FrontDart1TopPosition",
                            "FrontDart1Position","FrontDart1SplineBottom",
                            "FrontDart1Right","FrontDart1SplineRight",
                            "FrontDart1Left","FrontDart1SplineLeft",
                            "FrontDart1ConnectionLeft","FrontDart1ConnectionRight",
                            "FrontDart2TopPosition","FrontDart2Position",
                            "FrontDart2SplineBottom","FrontDart2Right",
                            "FrontDart2SplineRight","FrontDart2Left",
                            "FrontDart2SplineLeft","FrontDart2ConnectionLeft",
                            "FrontDart2ConnectionRight","FrontDart3TopPosition",
                            "FrontDart3Position","FrontDart3SplineBottom",
                            "FrontDart3Right","FrontDart3SplineRight",
                            "FrontDart3Left","FrontDart3SplineLeft",
                            "FrontDart3ConnectionLeft","FrontDart3ConnectionRight",NULL
                           };


    Vertex* v;
    for(int i=0;pnames[i]!=NULL;i++)
    {
        v=new Vertex(this,QPointF());
        //new Label(this,v,pnames[i],true);
        P[pnames[i]]=v;
    }

    //Border * b;
    //C2DLayer * layer;

    // Base shape: lines

    new Line(this,P["P51"],P["P54"]); new Line(this,P["P54"],P["P57"]);

    new Line(this,P["P41"],P["P47a"]); new Line(this,P["P41"],P["P51"]);

    new Line(this,P["V:L:TT"],P["V:L:RT"]); new Line(this,P["V:L:RT"],P["V:L:LT"]);
    new Line(this,P["V:L:LT"],P["V:L:LB"]); new Line(this,P["V:L:LB"],P["V:L:RB"]);
    new Line(this,P["V:L:RB"],P["V:L:RT"]); new Line(this,P["V:L:TT"],P["V:L:RB"]);
    new Line(this,P["P57"],P["P47"]);
    new BezierCurve3(this,P["P41"],P["P420"],P["P460"],P["P47"]);
/*

    // Darts: side
    DartItem * sd1 = this->dart( Sync( attr( SYNC_NAME, "SideDart-001" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "P54", "SideDart1Left", "SideDart1Right" ) ),
                                       LM->bold_solid() ), C2DItem::LB( "SideDart1" ) );
    if ( sd1 )
        sd1->setKK( 10.0f );

    // Darts: front
    DartItem * fd1 = this->dart( Sync( attr( SYNC_NAME, "FrontDart-001" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "FrontDart1Position", "FrontDart1Left", "FrontDart1Right" ) ),
                                       LM->bold_solid() ), LB( "FrontDart1" ) );


    DartItem * fd2 = this->dart( Sync( attr( SYNC_NAME, "FrontDart-002" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "FrontDart2Position", "FrontDart2Left", "FrontDart2Right" ) ),
                                       LM->bold_solid() ), LB( "FrontDart2" ) );

    DartItem * fd3 = this->dart( Sync( attr( SYNC_NAME, "FrontDart-003" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "FrontDart3Position", "FrontDart3Left", "FrontDart3Right" ) ),
                                       LM->bold_solid() ), LB( "FrontDart3" ) );

    if ( fd1 ) fd1->setKK( 2.5f );
    if ( fd2 ) fd2->setKK( 2.5f );
    if ( fd3 ) fd3->setKK( 2.5f );


    // Darts: back
    DartItem * bd1 = this->dart( Sync( attr( SYNC_NAME, "BackDart-001" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "BackDart1Position", "BackDart1Left", "BackDart1Right" ) ),
                                       LM->bold_solid() ), LB( "BackDart1" ) );

    DartItem * bd2 = this->dart( Sync( attr( SYNC_NAME, "BackDart-002" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "BackDart2Position", "BackDart2Left", "BackDart2Right" ) ),
                                       LM->bold_solid() ), LB( "BackDart2" ) );

    DartItem * bd3 = this->dart( Sync( attr( SYNC_NAME, "BackDart-003" ),
                                       attr( SYNC_TYPE, C2DSync::Dart  ),
                                       attr( SYNC_TYPE, MakeList( "BackDart3Position", "BackDart3Left", "BackDart3Right" ) ),
                                       LM->bold_solid() ), LB( "BackDart3" ) );

    if ( bd1 ) bd1->setKK( 0.0f );
    if ( bd2 ) bd2->setKK( 0.0f );
    if ( bd3 ) bd3->setKK( 0.0f );

*/
    // Darts: connections

    new BezierCurve3(this,P["P41"],P["P-C-001"],P["BackDart1ConnectionLeft"],P["BackDart1Left"]);
    new BezierCurve3(this,P["BackDart1Right"],P["BackDart1ConnectionRight"],
                     P["BackDart2ConnectionLeft"],P["BackDart2Left" ]);
    new BezierCurve3(this,P["BackDart2Right"],P["BackDart2ConnectionRight"],
                     P["BackDart3ConnectionLeft"],P["BackDart3Left"]);
    new BezierCurve3(this,P["P47"],P["P-C-002"],
                     P["FrontDart1ConnectionRight"],P["FrontDart1Right"]);
    new BezierCurve3(this,P["FrontDart1Left"],P["FrontDart1ConnectionLeft"],
                     P["FrontDart2ConnectionRight"],P["FrontDart2Right"]);
    new BezierCurve3(this,P["FrontDart2Left"],P["FrontDart2ConnectionLeft"],
                     P["FrontDart3ConnectionRight"],P["FrontDart3Right"]);
    new BezierCurve3(this,P["BackDart1Right"],P["BackDart1ConnectionRight"],
                     P["SideDart1ConnectionLeft"],P["SideDart1Left"]);
    new BezierCurve3(this,P["BackDart2Right"],P["BackDart2ConnectionRight"],
                     P["SideDart1ConnectionLeft"],P["SideDart1Left"]);
    new BezierCurve3(this,P["BackDart3Right"],P["BackDart3ConnectionRight"],
                     P["SideDart1ConnectionLeft"],P["SideDart1Left"]);
    new BezierCurve3(this,P["FrontDart1Left"],P["FrontDart1ConnectionLeft"],
                     P["SideDart1ConnectionRight"], P["SideDart1Right"]);
    new BezierCurve3(this,P["FrontDart2Left"],P["FrontDart2ConnectionLeft"],
                     P["SideDart1ConnectionRight"],P["SideDart1Right"]);
    new BezierCurve3(this,P["FrontDart3Left"],P["FrontDart3ConnectionLeft"],
                     P["SideDart1ConnectionRight"],P["SideDart1Right"]);
    /*
    this->sign( Sync( attr( SYNC_NAME, "VB" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "P54" ) ),
                      this->LM->bold_solid(),
                      attr( SYNC_SIGN_DUAL, true ),
                      attr( SYNC_SIGN_ANGLE, 0.0f ) ),
                      C2DItem::LB( "SideDart1" ) );

    this->sign( Sync( attr( SYNC_NAME, "FrontCut" ),
                      attr( SYNC_TYPE, C2DSync::Sign ),
                      attr( SYNC_LIST, MakeList( "P-FC-1" ) ),
                      LM->thick_solid(),
                      attr( SYNC_SIGN_DUAL, false ),
                      attr( SYNC_SIGN_ANGLE, 0.0f ) ), LB( "FrontCut" ) );

    this->sign(  Sync( attr( SYNC_NAME, "BackCut" ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "P-BC-1" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, 0.0f ) ), LB( "BackCut" ) );
    */
}

void SkirtPlot::update()
{
    //print new Line(this,P["P51"],P["P54"]); new Line(this,P["P54"],P["P57"]);
    const Elasticas::CommonData & V=Elasticas::Core::Instance()->commonVariables();
    QPointF TempPoint;
    QLineF TempLine;
    double T1=T("T1"),T16=T("T16"),T19=T("T19");
    double LibVersion = 0.9f;
    double Material=0.0f;
    double K25=0.0f;
    double K26=50.0f;
    double Tx = 1.0f + D( "PTx" );
    double Ty = 1.0f + D( "PTy" );
    double Width = T19 / 2.0f + D( "P19" );
    double HeightLeft =   D( "A1" );
    double HeightCenter = D( "A1" ) + ( T( "T25" ) - T( "T7" ) + K25 );
    double HeightRight =  D( "A1" ) + ( T( "T26" ) - T( "T7" ) + K26 );
    double Hipline = D( "A1" ) - D( "T86" );
    double HiplineWidth = ( 0.5f * ( T19 - D( "T18" ) ) +
                              ( D( "P19" ) - D( "P18" ) ) ) * Tx;
    bool SideDart1=true;
    bool FrontDart0=( I("FrontDartsCount")>0);
    bool FrontDart1=( I("FrontDartsCount")>1);
    bool FrontDart2=( I("FrontDartsCount")>2);
    bool BackDart0=( I("BackDartsCount")>0);
    bool BackDart1=( I("BackDartsCount")>1);
    bool BackDart2=( I("BackDartsCount")>2);
    int fvtn=I("FrontVentTypeNum");
    bool FrontSeam_Vent=(fvtn==1)&&B("VP"), FrontSeam_Sign=(fvtn==2)&&B("VP");
    bool SideSeam_Vent=(fvtn==1)&&B("VB"), SideSeam_Sign=(fvtn==2)&&B("VB");
    bool BackSeam_Vent=(fvtn==1)&&B("VZ"), BackSeam_Sign=(fvtn==2)&&B("VZ");
    bool Narrow_Negative=D( "A3" ) < 0 && B("Narrow");
    bool Narrow=D( "A3" ) >= 0 && B("Narrow");



    P[ "P0" ]->setPos(QPointF( 0.0f , 0.0f ));

    P[ "View:Center" ]->setPos(P[ "P0" ]->pos() + QPointF( Width / 2.0f - D( "A2" ), D( "A1" ) / 2.0f ));

    //Main circuit
    P[ "P91"  ]->setPos( PP( "P0" ));
    P[ "P94"  ]->setPos(PP( "P0" ) + QPointF( ( Width / 2.0f ) - D( "A2" ), 0.0f ));
    P[ "P97"  ]->setPos(PP( "P0"  ) + QPointF( Width, 0.0f ));
    P[ "P51"  ]->setPos(PP( "P0"  ) + QPointF( 0.0f, D( "A1" ) - ( T( "T7" ) - D( "T86" ) ) ));
    P[ "P54"  ]->setPos(PP( "P0"  ) + QPointF( ( Width / 2.0f ) - D( "A2" ),
                                        D( "A1" ) - ( T( "T7" ) - D( "T86" ) ) ));
    P[ "P57"  ]->setPos(PP( "P0"  ) + QPointF( Width, D( "A1" ) - ( T( "T7" ) - D( "T86" ) ) ));
    P[ "P41"  ]->setPos(PP( "P0"  ) + QPointF( 0.0f, D( "A1" ) ));
    P[ "P47"  ]->setPos(PP( "P0"  ) + QPointF( Width, HeightCenter ));
    P[ "P47a" ]->setPos(PP( "P0"  ) + QPointF( Width, D( "A1" ) ));
    P[ "P420" ]->setPos(PP( "P41" ) + QPointF( 0.1f * HiplineWidth, 0.0f ));
    P[ "P460" ]->setPos(PP( "P47" ) + QPointF( -0.1 * HiplineWidth, 0.0f ));

    P[ "PT1" ]->setPos(PP( "P0" ) + QPointF( 20.0f, D( "A1" ) / 3.0f ));
    P[ "PT2" ]->setPos(PP( "P0" ) + QPointF( Width - 10.0f, D( "A1" ) / 3.0f ));

    P[ "P-C-001" ]->setPos( PP( "P41" ) + QPointF(  10.0f, 0.0f ));
    P[ "P-C-002" ]->setPos( PP( "P47" ) + QPointF( -10.0f, 0.0f ));

    // Narrow
    P[ "P941"  ]->setPos( PP( "P0"    ) + QPointF(  D( "A3" ) / 2.0f, 0.0f  ));
    P[ "P941"  ]->setPos( PP( "P0"    ) + QPointF(  D( "A3" ) / 2.0f, 0.0f  ));
    P[ "P941a" ]->setPos( PP( "P97"   ) + QPointF( -D( "A3" ) / 2.0f, 0.0f ));
    P[ "SG3"   ]->setPos( PP( "P941"  ) + QPointF(  QLineF( PP( "P0"  ), PP( "P941"  ) ).length() * 3.0f, 0.0f ));
    P[ "SG4"   ]->setPos( PP( "P941a" ) + QPointF( -QLineF( PP( "P97" ), PP( "P941a" ) ).length() * 3.0f, 0.0f ));
    P[ "P54a"  ]->setPos( PP( "P54"   ) + QPointF( 0.0f, -D( "A4" ) ));

    P[ "SG0" ]->setPos( P[ "P54a" ]->pos() + QPointF( 0.0f, -1.0f ));

    if ( Narrow )
    {
        TempLine.setPoints(PP("P54a"),PP("P94")+QPointF( -D("A3"),0));
        TempLine.intersect(QLineF(PP("P941"),PP("P941")+QPointF(0,-1)),&TempPoint);
        TempLine.setP1(TempPoint);
        TempLine.setLength(QLineF(TempPoint,PP("P941")).length());
        P["P9411"]->setPos(TempLine.p2());
        TempLine=TempLine.normalVector();
        P["SG5"]->setPos(PP("P9411")+QPointF(-abs(TempLine.dx())*0.02,abs(TempLine.dy())*0.02));

        TempLine=QLineF(TempPoint,PP("P54a"));
        TempLine.setLength(TempLine.length()-30);
        P["P9411a"]->setPos(TempLine.p2());
        TempLine.setLength(TempLine.length()+10);
        P["SG1"]->setPos(TempLine.p2());

        TempLine.setPoints(PP("P54a"),PP("P94")+QPointF(D("A3"),0));
        TempLine.intersect(QLineF(PP("P941a"),PP("P941a")+QPointF(0,-1)),&TempPoint);
        TempLine.setP1(TempPoint);
        TempLine.setLength(QLineF(TempPoint,PP("P941a")).length());
        P["P9412"]->setPos(TempLine.p2());
        TempLine=TempLine.normalVector();
        P["SG6"]->setPos(PP("P9412")+QPointF(abs(TempLine.dx())*0.02,abs(TempLine.dy())*0.02));

        TempLine=QLineF(TempPoint,PP("P54a"));
        TempLine.setLength(TempLine.length()-30);
        P["P9412a"]->setPos(TempLine.p2());
        TempLine.setLength(TempLine.length()+10);
        P["SG2"]->setPos(TempLine.p2());

        P["P54a"]->setPos(PP("P54")+QPointF(0,-D("A4")*0.9));

        TempLine.setPoints(PP("P9411a"),PP("P9411") );
        TempLine.translate(-TempLine.normalVector().unitVector().dx()*40,
                           TempLine.normalVector().unitVector().dy()*40);
        QLineF TempLine2(PP("P54a"),PP("P54") );
        TempLine2.translate(-TempLine2.normalVector().unitVector().dx()*40,
                            TempLine2.normalVector().unitVector().dy()*40);
        TempLine.intersect(TempLine2,&TempPoint);
        P["NarrowStartLeft"]->setPos(TempPoint);
        QLineF(PP("P9412a"),PP("P9412") ).normalVector().intersect(
                QLineF(PP("P54a"),PP("P54") ).normalVector(),&TempPoint);
        P["NarrowStartRight"]->setPos(TempPoint);
    }


    if ( Narrow_Negative )
    {
        double length=QLineF(PP("P54a"),PP("P94")).length();// = Unicus::dPointPoint( PP("P54a"), PP("P94") );!!!
        double angle=abs( D("A3") ) / length * 180.0f / M_PI;

        P["P941"]->setPos(PP("P94") + QPointF( D("A3"), 0.0f ));
        P["P941a"]->setPos(PP("P94") + QPointF( -D("A3"), 0.0f ));
        P["SG3"]->setPos(PP("P941") + QPointF( -QLineF( PP("P94"), PP("P941")).length() * 0.3f, 0.0f ));
        P["SG4"]->setPos(PP("P941a") + QPointF( QLineF( PP("P94"), PP("P941a") ).length() * 0.3f, 0.0f ));

        P["P9411"]->setPos(PointOnRay( PP("P54a"), ( angle ) - 90.0f , length ));
        P["P9412"]->setPos(PointOnRay( PP("P54a"), ( -angle ) - 90.0f, length ));

        TempLine = QLineF( PP("P9411"), PP("P54a") );
        TempLine.setLength( TempLine.length() - 30.0f );
        P["P9411a"]->setPos( TempLine.p2() );
        TempLine.setLength( TempLine.length() + 10.0f );
        P["SG1"]->setPos( TempLine.p2() );

        TempLine = QLineF( PP("P9412"), PP("P54a") );
        TempLine.setLength( TempLine.length() - 30.0f );
        P["P9412a"]->setPos( TempLine.p2() );
        TempLine.setLength( TempLine.length() + 10.0f );
        P["SG2"]->setPos( TempLine.p2() );

        TempLine = uNormal( QLineF( PP("P9411"), PP("P9411a") ), true );
        P["SG6"]->setPos(PP("P9411") + TempLine.pointAt( 0.1f ));
        TempLine = uNormal( QLineF( PP("P9412"), PP("P9412a") ), false );
        P["SG5"]->setPos(PP("P9412") + TempLine.pointAt( 0.1f ));

        P["P54a"]->setPos(PP("P54")+QPointF(0,-D("A4")*0.9f));

        TempLine.setPoints(PP("P9411a"),PP("P9411") );
        TempLine.translate(-TempLine.normalVector().unitVector().dx()*40,
                           TempLine.normalVector().unitVector().dy()*40);
        QLineF TempLine2(PP("P54a"),PP("P54") );
        TempLine2.translate(-TempLine2.normalVector().unitVector().dx()*40,
                            TempLine2.normalVector().unitVector().dy()*40);
        TempLine.intersect(TempLine2,&TempPoint);
        P["NarrowStartLeft"]->setPos(TempPoint);
        QLineF(PP("P9412a"),PP("P9412") ).normalVector().intersect(
                QLineF(PP("P54a"),PP("P54") ).normalVector(),&TempPoint);
        P["NarrowStartRight"]->setPos(TempPoint);
    }

    //Vent is at the Back seam
    P["V:L:TT"]->setPos(PP("P51") );
    P["V:L:RT"]->setPos(PP("P0") + QPointF( 0.0f, D( "BackVentHeight" ) ));
    P["V:L:LT"]->setPos(PP("P0") + QPointF( -D( "BackVentWidth" ), D( "BackVentHeight" ) ));
    P["V:L:LB"]->setPos(PP("P0") + QPointF( -D( "BackVentWidth" ),0.0f ));
    P["V:L:RB"]->setPos(PP("P0") );
    //Vent is at the Front seam
    P["V:R:TT"]->setPos(PP("P57") );
    P["V:R:LT"]->setPos(PP("P97") + QPointF( 0.0f, D( "FrontVentHeight" ) ));
    P["V:R:RT"]->setPos(PP("P97") + QPointF( D( "FrontVentWidth" ), D( "FrontVentHeight" ) ));
    P["V:R:RB"]->setPos(PP("P97") + QPointF( D( "FrontVentWidth" ), 0.0f ));
    P["V:R:LB"]->setPos(PP("P97") );

    //Vent is at the Side seam
    if ( Narrow || Narrow_Negative )
    {
        P["V:S:L:TT"]->setPos(PP("P9411a") );
        P["V:S:L:LB"]->setPos(PP("P9411") );
        QLineF temp = QLineF( PP("P9411"), PP("P9411a") ).unitVector();
        temp.setLength( D("SideVentHeight") );
        P["V:S:L:LT"]->setPos(temp.p2());
        temp = temp.unitVector();
        //temp = Unicus::uNormal( temp , false ).translated( PP("P9411") ); !!!
        temp.setLength( D("SideVentWidth") );
        P["V:S:L:RB"]->setPos(temp.p2());
        P["V:S:L:RT"]->setPos(PP("V:S:L:RB") + QPointF( PP("V:S:L:LT").x() - PP("V:S:L:LB").x(),
                                                 PP("V:S:L:LT").y() - PP("V:S:L:LB").y() ));

        P["V:S:R:TT"]->setPos(PP("P9412a"));
        P["V:S:R:RB"]->setPos(PP("P9412"));
        temp = QLineF( PP("P9412"), PP("P9412a") ).unitVector();
        temp.setLength(D("SideVentHeight"));
        P["V:S:R:RT"]->setPos(temp.p2());
        temp = temp.unitVector();
        temp=uNormal( temp , true ).translated( PP("P9412") );
        temp.setLength( D("SideVentWidth") );
        P["V:S:R:LB"]->setPos(temp.p2());
        P["V:S:R:LT"]->setPos(PP("V:S:R:LB") + QPointF( PP("V:S:R:RT").x() - PP("V:S:R:RB").x(),
                                                 PP("V:S:R:RT").y() - PP("V:S:R:RB").y() ));
    }
    else
    {
        P["V:S:L:TT"]->setPos(PP("P54") );
        P["V:S:L:LT"]->setPos(PP("P94")+QPointF(0,D("SideVentHeight")));
        P["V:S:L:RT"]->setPos(PP("P94")+QPointF(D("SideVentWidth"), D("SideVentHeight")));
        P["V:S:L:RB"]->setPos(PP("P94")+QPointF(D("SideVentWidth"),0));
        P["V:S:L:LB"]->setPos(PP("P94") );

        P["V:S:R:TT"]->setPos(PP("P54") );
        P["V:S:R:RT"]->setPos(PP("P94")+QPointF(0,D("SideVentHeight")));
        P["V:S:R:LT"]->setPos(PP("P94")+QPointF(-D("SideVentWidth"), D("SideVentHeight")));
        P["V:S:R:LB"]->setPos(PP("P94")+QPointF(-D("SideVentWidth"),0));
        P["V:S:R:RB"]->setPos(PP("P94") );
    }


    //
    //Clasp
    //

    //New Darts
    P[ "SideDart1TopPosition" ]->setPos(PP( "P94" ) + QPointF( 0.0f, HeightCenter ));

    P[ "SideDart1Position" ]->setPos(PP( "SideDart1TopPosition" ) + QPointF( 0.0f, -D( "SideDart1Height" ) ));

    P[ "SideDart1SplineBottom" ]->setPos(PP( "SideDart1Position" ) + QPointF( 0.0f, 10.0f ));

    P[ "SideDart1Right" ]->setPos(PP( "SideDart1TopPosition" ) + QPointF( D("SideDart1Spread") / 2.0f, 0.0f ));

    P[ "SideDart1SplineRight" ]->setPos(
            rLine( QLineF( PP( "SideDart1Right" ), PP( "SideDart1Position" ) ),
                           PP( "SideDart1Right" ), -10.0f ).pointAt( 0.1f ));

    P[ "SideDart1Left" ]->setPos(PP( "SideDart1TopPosition" ) + QPointF( -D( "SideDart1Spread" ) / 2.0f, 0.0f ));

    P[ "SideDart1SplineLeft" ]->setPos(
            rLine( QLineF( PP( "SideDart1Left" ), PP( "SideDart1Position" ) ),
                           PP( "SideDart1Left" ), 10.0f ).pointAt( 0.1f ));

    P[ "SideDart1ConnectionLeft" ]->setPos(
            rPoint( PP( "SideDart1SplineLeft" ), PP( "SideDart1Left" ), -90.0f));

    P[ "SideDart1ConnectionRight" ]->setPos(
            rPoint( PP( "SideDart1SplineRight" ), PP( "SideDart1Right" ), 90.0f ));

    P["BackDart1TopPosition"]->setPos(PP("P41")+BackDartTopPosition(D("BackDart1Width"), PP( "P94" )+QPointF(0,HeightCenter), PP("P41") ));
    P["BackDart1Position"]->setPos(PP("BackDart1TopPosition")+QPointF(0,-D("BackDart1Height")));
    P["BackDart1SplineBottom"]->setPos(PP("BackDart1Position")+QPointF(0,10));
    P["BackDart1Right"]->setPos(PP("BackDart1TopPosition")+QPointF(D("BackDart1Spread")/2,0));
    P["BackDart1SplineRight"]->setPos(rLine(QLineF(PP("BackDart1Right"),PP("BackDart1Position")),PP("BackDart1Right"),-10).pointAt(0.1));
    P["BackDart1Left"]->setPos(PP("BackDart1TopPosition")+QPointF(-D("BackDart1Spread")/2,0));
    P["BackDart1SplineLeft"]->setPos(rLine(QLineF(PP("BackDart1Left"),PP("BackDart1Position")),PP("BackDart1Left"),10).pointAt(0.1));
    P["BackDart1ConnectionLeft"]->setPos(rPoint(PP("BackDart1SplineLeft"),PP("BackDart1Left"), -90));
    P["BackDart1ConnectionRight"]->setPos(rPoint(PP("BackDart1SplineRight"),PP("BackDart1Right"), 90));

    P["BackDart2TopPosition"]->setPos(PP("P41")+BackDartTopPosition(D("BackDart2Width"), PP("P94")+QPointF(0,HeightCenter), PP("P41")));
    P["BackDart2Position"]->setPos(PP("BackDart2TopPosition")+QPointF(0,-D("BackDart2Height")));
    P["BackDart2SplineBottom"]->setPos(PP("BackDart2Position")+QPointF(0,10));
    P["BackDart2Right"]->setPos(PP("BackDart2TopPosition")+QPointF(D("BackDart2Spread")/2,0));
    P["BackDart2SplineRight"]->setPos(rLine(QLineF(PP("BackDart2Right"),PP("BackDart2Position")),PP("BackDart2Right"),-10).pointAt(0.1));
    P["BackDart2Left"]->setPos(PP("BackDart2TopPosition")+QPointF(-D("BackDart2Spread")/2,0));
    P["BackDart2SplineLeft"]->setPos(rLine(QLineF(PP("BackDart2Left"),PP("BackDart2Position")),PP("BackDart2Left"),10).pointAt(0.1));
    P["BackDart2ConnectionLeft"]->setPos(rPoint(PP("BackDart2SplineLeft"),PP("BackDart2Left"), -90));
    P["BackDart2ConnectionRight"]->setPos(rPoint(PP("BackDart2SplineRight"),PP("BackDart2Right"), 90));

    P["BackDart3TopPosition"]->setPos(PP("P41")+BackDartTopPosition(D("BackDart3Width"), PP("P94")+QPointF(0,HeightCenter), PP("P41")));
    P["BackDart3Position"]->setPos(PP("BackDart3TopPosition")+QPointF(0,-D("BackDart3Height")));
    P["BackDart3SplineBottom"]->setPos(PP("BackDart3Position")+QPointF(0,10));
    P["BackDart3Right"]->setPos(PP("BackDart3TopPosition")+QPointF(D("BackDart3Spread")/2,0));
    P["BackDart3SplineRight"]->setPos(rLine(QLineF(PP("BackDart3Right"),PP("BackDart3Position")),PP("BackDart3Right"),-10).pointAt(0.1));
    P["BackDart3Left"]->setPos(PP("BackDart3TopPosition")+QPointF(-D("BackDart3Spread")/2,0));
    P["BackDart3SplineLeft"]->setPos(rLine(QLineF(PP("BackDart3Left"),PP("BackDart3Position")),PP("BackDart3Left"),10).pointAt(0.1));
    P["BackDart3ConnectionLeft"]->setPos(rPoint(PP("BackDart3SplineLeft"),PP("BackDart3Left"), -90));
    P["BackDart3ConnectionRight"]->setPos(rPoint(PP("BackDart3SplineRight"),PP("BackDart3Right"), 90));

    P["FrontDart1TopPosition"]->setPos(PP("P41")+FrontDartTopPosition(D("FrontDart1Width"), PP("P94")+QPointF(0,HeightCenter), PP("P47")));
    P["FrontDart1Position"]->setPos(PP("FrontDart1TopPosition")+QPointF(0,-D("FrontDart1Height")));
    P["FrontDart1SplineBottom"]->setPos(PP("FrontDart1Position")+QPointF(0,10));
    P["FrontDart1Right"]->setPos(PP("FrontDart1TopPosition")+QPointF(D("FrontDart1Spread")/2,0));
    P["FrontDart1SplineRight"]->setPos(rLine(QLineF(PP("FrontDart1Right"),PP("FrontDart1Position")),PP("FrontDart1Right"),-10).pointAt(0.1));
    P["FrontDart1Left"]->setPos(PP("FrontDart1TopPosition")+QPointF(-D("FrontDart1Spread")/2,0));
    P["FrontDart1SplineLeft"]->setPos(rLine(QLineF(PP("FrontDart1Left"),PP("FrontDart1Position")),PP("FrontDart1Left"),10).pointAt(0.1));
    P["FrontDart1ConnectionLeft"]->setPos(rPoint(PP("FrontDart1SplineLeft"),PP("FrontDart1Left"), -90));
    P["FrontDart1ConnectionRight"]->setPos(rPoint(PP("FrontDart1SplineRight"),PP("FrontDart1Right"), 90));

    P["FrontDart2TopPosition"]->setPos(PP("P41")+FrontDartTopPosition(D("FrontDart2Width"), PP("P94")+QPointF(0,HeightCenter), PP("P47")));
    P["FrontDart2Position"]->setPos(PP("FrontDart2TopPosition")+QPointF(0,-D("FrontDart2Height")));
    P["FrontDart2SplineBottom"]->setPos(PP("FrontDart2Position")+QPointF(0,10));
    P["FrontDart2Right"]->setPos(PP("FrontDart2TopPosition")+QPointF(D("FrontDart2Spread")/2,0));
    P["FrontDart2SplineRight"]->setPos(rLine(QLineF(PP("FrontDart2Right"),PP("FrontDart2Position")),PP("FrontDart2Right"),-10).pointAt(0.1));
    P["FrontDart2Left"]->setPos(PP("FrontDart2TopPosition")+QPointF(-D("FrontDart2Spread")/2,0));
    P["FrontDart2SplineLeft"]->setPos(rLine(QLineF(PP("FrontDart2Left"),PP("FrontDart2Position")),PP("FrontDart2Left"),10).pointAt(0.1));
    P["FrontDart2ConnectionLeft"]->setPos(rPoint(PP("FrontDart2SplineLeft"),PP("FrontDart2Left"), -90));
    P["FrontDart2ConnectionRight"]->setPos(rPoint(PP("FrontDart2SplineRight"),PP("FrontDart2Right"), 90));

    P["FrontDart3TopPosition"]->setPos(PP("P41")+FrontDartTopPosition(D("FrontDart3Width"), PP("P94")+QPointF(0,HeightCenter), PP("P47")));
    P["FrontDart3Position"]->setPos(PP("FrontDart3TopPosition")+QPointF(0,-D("FrontDart3Height")));
    P["FrontDart3SplineBottom"]->setPos(PP("FrontDart3Position")+QPointF(0,10));
    P["FrontDart3Right"]->setPos(PP("FrontDart3TopPosition")+QPointF(D("FrontDart3Spread")/2,0));
    P["FrontDart3SplineRight"]->setPos(rLine(QLineF(PP("FrontDart3Right"),PP("FrontDart3Position")),PP("FrontDart3Right"),-10).pointAt(0.1));
    P["FrontDart3Left"]->setPos(PP("FrontDart3TopPosition")+QPointF(-D("FrontDart3Spread")/2,0));
    P["FrontDart3SplineLeft"]->setPos(rLine(QLineF(PP("FrontDart3Left"),PP("FrontDart3Position")),PP("FrontDart3Left"),10).pointAt(0.1));
    P["FrontDart3ConnectionLeft"]->setPos(rPoint(PP("FrontDart3SplineLeft"),PP("FrontDart3Left"), -90));
    P["FrontDart3ConnectionRight"]->setPos(rPoint(PP("FrontDart3SplineRight"),PP("FrontDart3Right"), 90));
    Plot::update();
}

QPointF SkirtPlot::FrontDartTopPosition( double width, const QPointF & SideDartTop, const QPointF & RightPoint )
{
    const Elasticas::CommonData & V=Elasticas::Core::Instance()->commonVariables();
    double Width = T("T19") / 2.0f + D( "P19" );
    double dx = RightPoint.x()  - SideDartTop.x();
    double dy = SideDartTop.y() - RightPoint.y();
    double k = width - Width / 2.0f;
    return QPointF( -( Width - width ), dy * ( 1.0f - k / dx ) );
}

QPointF SkirtPlot::BackDartTopPosition( double width, const QPointF & SideDartTop, const QPointF & LeftPoint )
{
    double dx = SideDartTop.x() - LeftPoint.x();
    double dy = SideDartTop.y() - LeftPoint.y();
    return QPointF( width, dy * width / dx);
}
