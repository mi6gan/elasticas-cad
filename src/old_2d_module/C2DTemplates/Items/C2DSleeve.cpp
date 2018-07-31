#include "C2DSleeve.h"

// Мои функции тут
QPointF mirrorpoint( QPointF mypoint, QLineF myline)
{
    QLineF myline2(mypoint,mypoint+QPointF(1,0));
    QPointF mypoint2;
    myline2.setAngle(myline.angle()+90.0f);
    myline2.intersect(myline,&mypoint2);
    return Unicus::rPoint(mypoint,mypoint2,180);

}
QPointF splinepointony( QPainterPath spline , double yy,double n)
{
    double shag,persent=0.5f;

    if (spline.pointAtPercent(0).y()>spline.pointAtPercent(1).y())
        shag = -0.5f;
    else
        shag = 0.5f;


    for ( int i = 1; i < 200; i = i + 1 )
    {
        if ((  (spline.pointAtPercent( persent ).y() - yy)  <=  n)&&
                (  (spline.pointAtPercent( persent ).y() - yy)  >=  -n))
        {
            return spline.pointAtPercent( persent );
        }
        shag = shag/2;

        if ( spline.pointAtPercent( persent ).y() <  yy)
        {
            persent = persent + shag;
        }
       else
        {
            persent = persent - shag;
        }


      //  qDebug()<< "persent = " <<persent<<"Ys "<<spline.pointAtPercent( persent ).y()<<"Y"<< yy<< shag<<" cycle N"<<i ;
    }
    return spline.pointAtPercent( persent );
}
QPointF splinepointonx( QPainterPath spline , double xx,double n)
{
    double shag,persent=0.5f;

    if (spline.pointAtPercent(0).x()>spline.pointAtPercent(1).x())
        shag = -0.5f;
    else
        shag = 0.5f;


    for ( int i = 1; i < 200; i = i + 1 )
    {
        if ((  (spline.pointAtPercent( persent ).x() - xx)  <=  n)&&
                (  (spline.pointAtPercent( persent ).x() - xx)  >=  -n))
        {
            return spline.pointAtPercent( persent );
        }
        shag = shag/2;

        if ( spline.pointAtPercent( persent ).x() <  xx)
        {
            persent = persent + shag;
        }
       else
        {
            persent = persent - shag;
        }


      //  qDebug()<< "persent = " <<persent<<"Ys "<<spline.pointAtPercent( persent ).y()<<"Y"<< yy<< shag<<" cycle N"<<i ;
    }
    return spline.pointAtPercent( persent );
}
double splinepersentonx( QPainterPath spline , double xx,double n)
{
    double shag,persent=0.5f;

    if (spline.pointAtPercent(0).x()>spline.pointAtPercent(1).x())
        shag = -0.5f;
    else
        shag = 0.5f;


    for ( int i = 1; i < 200; i = i + 1 )
    {
        if ((  (spline.pointAtPercent( persent ).x() - xx)  <=  n)&&
                (  (spline.pointAtPercent( persent ).x() - xx)  >=  -n))
        {
            return persent;
        }
        shag = shag/2;

        if ( spline.pointAtPercent( persent ).x() <  xx)
        {
            persent = persent + shag;
        }
       else
        {
            persent = persent - shag;
        }


      //  qDebug()<< "persent = " <<persent<<"Ys "<<spline.pointAtPercent( persent ).y()<<"Y"<< yy<< shag<<" cycle N"<<i ;
    }
    return persent;
}

C2DSleeve::C2DSleeve() : C2DItem()
{
    this->setPrefix( QString( "Sleeve" ) );
    this->requiredVariables();

    this->addDialog( new C2DSleeveDialog( QObject::trUtf8( "Рукав" ), this->prefix(), QObject::trUtf8( "Манекен" ),
                     QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), NULL ) );

//    qDebug() << "Dialog" << this->dialog;
}

void C2DSleeve::Update()
{
  //  this->getVariables();
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();
    //this->dialog->show();
}

void C2DSleeve::requiredVariables()
{
    this->addVariable( C2DVariable::set( "PTx", this->prefix() + "PTx", "Not described",
                       C2DVariable::Metrics, C2DVariable::General ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix() + "PTy", "Not described",
                       C2DVariable::Metrics, C2DVariable::General ) );
///////////ЗНАЧЕНИЯ ИЗ ДИАЛОГА
    this->addVariable( C2DVariable::set( "Type", this->prefix() + "Type", "Not described",
                       C2DVariable::Unitless, C2DVariable::General ) );
    this->addVariable( C2DVariable::set( "3K0", this->prefix() + "Shovpos", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 ,0.01f ) );

}

void C2DSleeve::setVariables()
{

    H( "Width" ) = 125.7f;//Ширина проймы
    H( "Height" ) = 147.8f;//Высота оката

    H( "SleeveType" ) = D("Type") + 1;//Тип рукава

    H("a+b+c+d" ) = 439.7f;
    H("H" ) = 0.07f;

    double Ppos= (LD("H")*LD("a+b+c+d"));//Ппос = Дпр*Н
    H("Ppos" ) = Ppos;


    H( "K344" ) = 0.65f;//Коэфициент для рассчета нахождения точки 344 : 341-444=K344 * (341-343)
    H( "gamma" ) = 93.0f;//Угол гамма из точки 332

    H( "alpha" ) = 3.0f;//Угол  из точки 333 к оси OY
    H( "betta" ) = 0.0f;//Угол  из точки 355 к оси OY

    H( "Drlok" ) = 329.6f;//Др.лок
    H( "Drzap" ) = 578.5f;//Др.зап
    H( "P" ) = 10.0f;//П - по модели
    H( "Py" ) = 0.00f;//Пy - Припуск на уработку 1.5 - 2%./100
    H( "Shrn" ) = 110.00f;//Ширина рукава внизу

    H("First") = false;
    H("Second") = false;
    H("Third") = false;
    if ( LI( "SleeveType" ) == 1 )
        H( "First" ) = true;
    if ( LI( "SleeveType" ) == 2 )
        H( "Second" ) = true;
    if ( LI( "SleeveType" ) == 3 )
        H( "Third" ) = true;
    //else
    //    H( "Condition 1" ) =false );
    ////////////////////Значения по умолчанию
    H( "shov5" ) = false;
    H( "shov4" ) = false;
    H( "shov3" ) = false;
    H( "shov2" ) = false;
    H( "shov1" ) = false;
    ///////////////////

    ///*ПАРАМЕТРЫ ДЛЯ ТРЕТЬЕГО ТИПА РУКАВА
    H( "3K0" ) = D( "3K0" );//0.10f;//коэффициент положения шва

}


void C2DSleeve::UpdatePoints()
{
    double Splinekoff=0.5f;
    P.clear();
    P["P0"] = QPointF( 200.0f, 500.0f );

    P["341"] = P["P0"];

    P["331"] = P["341"] - QPointF( ( LD("Width")*0.6f ) , 0.0f ) ;
    P["13"]  = P["331"] + QPointF( 0.0f, LD("Height"));
    P["332"] = P["331"] + QPointF( 0.0f , ( LD("Width") * 0.6f ) );


    P["Sv331"] = P["332"] + QPointF( 0.0f, - QLineF( P["331"], P["332"] ).length() * Splinekoff );
    P["Sh341"] = P["341"] + QPointF( - QLineF( P["331"], P["341"] ).length() * 0.4, 0.0f );

    P["351"] = P["P0"] + QPointF( ( LD("Width")*0.4f ) , 0.0f );
    P["352"] = P["351"] + QPointF( 0.0f , ( LD("Width")*0.4f ));
    P["354"] = P["351"] + QPointF(LD("Ppos")*0.25f ,0.0f);

    P["Sv351"] = P["352"] + QPointF( 0.0f, - QLineF( P["351"], P["352"] ).length() * Splinekoff );
    P["Sh351"] = P["341"] + QPointF( QLineF( P["351"], P["341"] ).length() * Splinekoff, 0.0f );
    P["Sh351'"] = P["341"] + QPointF( QLineF( P["354"], P["341"] ).length()*0.3f, 0.0f );

    P["342"] = P["341"] + QPointF( 0.0f, ( LD("Width") * 0.6f ) );
    P["343"] = P["341"] + QPointF( 0.0f, ( LD("Width") * 0.4f ) );
    P["344"] = P["341"] + QPointF( 0.0f, QLineF(P["343"],P["341"]).length()* LD("K344") );

    // Тут нахожу точки пересечения прямой 345-353 со сплайнами 1 и 4(левый и правый нижние)

    QPainterPath Spline341p332, Spline352p341;
    Spline341p332.moveTo( P["332"] );
    Spline341p332.cubicTo( P["Sv331"], P["Sh341"], P["341"] );

    double y = P["344"].y();
    P["345"]=QPointF( splinepointony(Spline341p332,y,0.01f).x(),y );

    Spline352p341.moveTo( P["352"] );
    Spline352p341.cubicTo( P["Sv351"], P["Sh351"], P["341"]);

    P["353"]=QPointF(splinepointony(Spline352p341,y,0.01f).x(),y);


    P["151"] = P["354"] + QPointF(0.0f , LD("Height"));
    //Точки для нижних сплайнов

        QLineF myline(P["345"],Unicus::rPoint( P["342"], P["345"], -90.0f));
        myline.setLength(QLineF( P["331"], P["341"] ).length() * (Splinekoff/4));

        P["345spline"] = myline.p2();


        myline.setPoints(P["353"],Unicus::rPoint( P["343"], P["353"], 90.0f));
        myline.setLength(QLineF(  P["351"], P["341"] ).length() * (Splinekoff/4));

        P["353spline"] = myline.p2();


    // Нахожу косательные к точкам 345 и 353
    P["332kos"] = Unicus::rPoint( P["342"], P["345"], 90.0f);
    P["353kos"] = Unicus::rPoint( P["343"], P["353"], -90.0f);

    //поворачиваю прямую 332-13 на угол гамма
    P["332'0"]  = Unicus::rPoint( P["13"], P["332"], LD("gamma"));

    //Нахожу точки пересечения прямых. Точки 332' и 355

    QLineF line1(P["345"],P["332kos"]), line2(P["332"],P["332'0"]);
    QPointF intersectionPoint;
    QPointF* p;
    p=&intersectionPoint;
    line1.intersect(line2, p);
    P["332'"] = intersectionPoint;
    line1.setPoints(P["353"],P["353kos"]);
    line2.setPoints(P["354"],P["151"]);
    line1.intersect(line2, p);
    P["355"] = intersectionPoint;

    //Нахожу точку 332'' , 14

    P["332''"]= Unicus::rPoint( P["332"],P["332'"], 180.0f);
    line1.setPoints(P["345"],P["332'"]);
    line2.setPoints(P["13"],P["151"]);
    line1.intersect(line2, p);
    //P["14"] = Unicus::rPoint( intersectionPoint, P["13"], 180.0f);
    line1 = QLineF(P["13"],P["151"]);
    line1.setLength(line1.length()/2);
    P["14"] = line1.p2();

    //Нахожу точки 141,142,145
    line1.setPoints(P["355"],P["14"]);
    line1.setLength(line1.length()/2);
    P["142"]=line1.p2();
    //P["141"]=QPointF( P["142"].x(),P["14"].y());
    line1.setPoints(P["353"],P["355"]);
    line2.setPoints(P["355"],P["151"]);
    line2.setAngle(line2.angle()+line1.angleTo(line2));
    line1.setPoints(P["14"],P["151"]);
    line2.intersect(line1,p);
    P["141"]=intersectionPoint;
    ////
    line1.setPoints(P["14"],P["141"]);
    line1.setLength(line1.length()*Splinekoff);
    P["141hor"]=line1.p2();
    line1.setPoints(P["355"],P["141"]);
    line1.setLength(line1.length()*0.8);
    P["141vert"]=line1.p2();
    ////
    line1.setPoints(P["332''"],P["14"]);
    line1.setLength(line1.length()/2);
    P["145"]=line1.p2();
   // P["144"]=QPointF( P["145"].x(),P["14"].y());

    //Нахожу точку 131 ,334
    line1.setPoints(P["332''"],P["332'"]);
    line1.setLength(line1.length()/2);
    P["334"]=line1.p2();
    line2=Unicus::rLine(line1,P["334"],90.0f);
    line1.setPoints(P["345"],P["332'"]);
    line2.intersect(line1, p);
    P["131"]=intersectionPoint;


    //132,333
    line1.setPoints(P["14"],P["151"]);
    line2.setPoints(P["334"],P["131"]);
    line2.intersect(line1,p);
    P["132"]=intersectionPoint;
    line1.setPoints(P["341"],P["331"]);
    line2.intersect(line1,p);
    P["333"]=intersectionPoint;
    //////144
    line1.setPoints(P["345"],P["131"]);
    line2.setPoints(P["131"],P["132"]);
    line2.setAngle(line2.angle()+line1.angleTo(line2));
    line1.setPoints(P["14"],P["151"]);
    line2.intersect(line1,p);
    P["144"]=intersectionPoint;
    //////
    line1.setPoints(P["131"],P["144"]);
    line1.setLength(line1.length()*0.7);
    P["144vert"]=line1.p2();
    /////////////////////////ПОСТРОЕНИЕ ШАБЛОНА ВНЕШНЕГО ВИДА РУКАВА
    line1.setP1(P["333"]);
    line1.setAngle(90.0f-LD("alpha"));
    line1.setLength( (LD("Drlok")+LD("P")+(LD("Py")*LD("Drlok"))) - QLineF(P["132"],P["333"]).length() );
    P["43"]= line1.p2();
    line1.setLength( (LD("Drzap")+LD("P")+(LD("Py")*LD("Drlok"))) - QLineF(P["132"],P["333"]).length() );
    P["93"]= line1.p2();
    line2.setP1(P["355"]);
    line2.setAngle(90.0f-LD("betta"));
    line2.setLength(1.0f);

    double myangle;
    myangle = line1.angle();line1.setLength(1.0f);
    line1.setP1(P["93"]);
    line1.setAngle(myangle);
    line1 = Unicus::rLine(line1,P["93"],90.0f);
    line2.intersect(line1,p);
    P["95"]=intersectionPoint;

    line1 = QLineF(P["95"],P["93"]);
    line1.setLength(LD("Shrn"));
    P["931"]=line1.p2();
    line1.setLength(line1.length()/2);
    P["94"]=line1.p2();
    line1 = QLineF(P["93"],P["931"]);
    line1.setLength(line1.length()/2);
    P["932"]=line1.p2();

    line1.setP1(P["43"]);
    line1.setAngle(line2.angle()-90.0f);
    line2.intersect(line1,p);
    P["45"]=intersectionPoint;
    //P["45"]=P["45"]+QPointF(10,0);
    line1=QLineF(P["43"],P["45"]);
    line2=QLineF(P["333"],P["932"]);
    line2.intersect(line1,p);
    P["431"]=intersectionPoint;

    line2=QLineF(P["43"],P["931"]);
    line1.setP1(P["94"]);line1.setLength(1.0f);
    line1.setAngle(line2.angle()+90.0f);
    line1.intersect(line2,p);
    P["933"]= intersectionPoint;

    line2=QLineF(P["95"],P["45"]);
    line1=QLineF(P["933"],P["94"]);
    line1.intersect(line2,p);
    P["951"]= intersectionPoint;

    QPointF deltapoint = QPointF(10.0f,5.0f);
    P["941"]=P["94"]+deltapoint;//так же 10, 5 используется для нахождения P["3K2"}

    line2=QLineF(P["941"],P["341"]);
    line1=QLineF(P["45"],P["43"]);
    line1.intersect(line2,p);
    P["44'"]= intersectionPoint;
    line1 = QLineF(P["43"],P["44'"]);
    line1.setLength(line1.length()-7.0f);
    P["44"]=line1.p2();

    line1= QLineF(P["355"],QPointF(P["355"].x(),P["355"].y()-1.0f));
    line2= QLineF(P["45"],P["43"]);
    line2.intersect(line1,p);
    P["451"]=intersectionPoint;
    P["451"] = P["451"] - QPointF(10,0);
////////////////////////////ОДНОШОВНЫЙ РУКАВ
//    P["341''"]= Unicus::rPoint( P["341"],P["132"],90.0f);

        line1 = QLineF(P["355"],P["451"]);
        line2.setPoints(P["341"],P["341"]+QPointF(1,0));
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["357"]=intersectionPoint;
        P["341'"]= Unicus::rPoint(P["341"],intersectionPoint,180.0f);
        ///Точка для сплайна 341'
        myline.setPoints(P["353"],Unicus::rPoint( P["343"], P["353"], 90.0f));
        myline.setLength(QLineF(  P["351"], P["341"] ).length() * (Splinekoff/4));

        line2.setP1( P["353"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["353'"] = Unicus::rPoint(P["353"], intersectionPoint, 180.0f);

        line2.setP1( myline.p2() );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["353'spline"] = Unicus::rPoint( myline.p2(), intersectionPoint, 180.0f);
        myline = QLineF( P["341'"],P["341"] );
        myline.setLength(QLineF( P["351"], P["341"] ).length() * Splinekoff);
        double prir = 0.3f, prir2 = 0.5f , prir3 = 20.0f; //Приращения 341',941',34
        P["341'spline"] = myline.p2()+QPointF(0.0f,prir);


        ////////
        line1 = QLineF(P["451"],Unicus::rPoint(P["44"],P["451"],180.0f));
        line1.setAngle(0.0f);
        P["44'"]= line1.p2();

        line1 = QLineF(P["44'"],P["341'"]);
        line1.setLength(line1.length()+prir);
        P["341'p"] = line1.p2();

        line1 = QLineF(P["451"],P["951"]);
        line2.setP1( P["941"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["941'"]= Unicus::rPoint(P["941"],intersectionPoint,180.0f);

        line1 = QLineF(P["44'"],P["941'"]);
        line1.setLength(line1.length()+prir2);
        P["941'p"] = line1.p2();

        //Левая часть . Точка 341''
        line1 = QLineF(P["132"],P["333"]);
        line2.setP1( P["341"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);

        P["341''"]= Unicus::rPoint(P["341"],intersectionPoint,180.0f);
        ///Точка для сплайна 341'
        myline.setPoints(P["345"],Unicus::rPoint( P["342"], P["345"], -90.0f));
        myline.setLength(QLineF( P["331"], P["341"] ).length() * (Splinekoff/4));

        line2.setP1( P["345"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["345'"] = Unicus::rPoint(P["345"], intersectionPoint, 180.0f);

        line2.setP1( myline.p2() );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);

        P["345'spline"] = Unicus::rPoint( myline.p2(), intersectionPoint, 180.0f);
        myline = QLineF( P["341''"],P["341"] );
        myline.setLength(QLineF( P["331"], P["341"] ).length() * Splinekoff);
        P["341''spline"] = myline.p2()+QPointF(0.0f,prir);
        ///////
        line1 = QLineF(P["333"],P["43"]);
        line2.setP1( P["44"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["44'''"]= Unicus::rPoint(P["44"],intersectionPoint,180.0f);

        line1 = QLineF(P["44'''"],P["341''"]);
        line1.setLength(line1.length()+prir);
        P["341''p"] = line1.p2();

        line1 = QLineF(P["43"],P["933"]);
        line2.setP1( P["44"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["44''"]= Unicus::rPoint(P["44"],intersectionPoint,180.0f);

        line2.setP1( P["941"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["941''"]= Unicus::rPoint(P["941"],intersectionPoint,180.0f);

        line1 = QLineF(P["44''"],P["941''"]);
        line1.setLength(line1.length()+prir2);
        P["941''p"] = line1.p2();

        myline = QLineF(P["44'''"],P["44''"]);
        myline.setLength(myline.length()/2);
        myline = QLineF(P["43"],myline.p2());
        myline.setLength(prir3);
        P["43p"]= myline.p2();

        line1 = QLineF(P["933"],P["941"]);
        line2 = QLineF(P["941''"],P["933"]);
        line1.setAngle( ((line1.angle()+line2.angle())/2) );
        line1.setLength(line1.length()*0.2);
        P["933r"]=line1.p2();
        line1.setLength(line2.length()*0.2);
        P["933l"] = Unicus::rPoint( line1.p2(),line1.p1(),180.0f);

        line1 = QLineF(P["951"],P["941'"]);
        line2 = QLineF(P["933"],P["951"]);
        line1.setAngle( ((line1.angle()+line2.angle())/2) );
        line1.setLength(line1.length()*0.2);
        P["951r"]=line1.p2();
        line1.setLength(line2.length()*0.2);
        P["951l"] = Unicus::rPoint( line1.p2(),line1.p1(),180.0f);

        P["941''r"] = P["941''"] + QPointF( (P["933"].x()-P["941''"].x()) *0.35f,(P["933"].y()-P["941''"].y()) *0.35f);
        P["941'l"] = P["941'"] + QPointF( (P["951"].x()-P["941'"].x()) *0.35f,(P["951"].y()-P["941'"].y()) *0.35f);


        line1 = QLineF(P["14"],P["14"]-QPointF(0.0f,1.0f));

        if ((P["933"].x() < P["14"].x())&&((P["951"].x() > P["14"].x())))
            line2 = QLineF(P["933"],P["951"]);
        else
            if (P["933"].x() > P["14"].x())
            line2 = QLineF(P["941''"],P["933"]);
        else
            line2 = QLineF(P["951"],P["941'"]);

        line1.intersect(line2,p);
                 P["14vertical"]=intersectionPoint;

        line1 = QLineF(P["131"],P["345'"]);
        line1.setLength(line1.length()*0.40f);
        P["signA"] = line1.p2();

        line2 = QLineF(P["355"],P["353'"]);
        line2.setLength(line2.length()*0.40f);
        P["signD"] = line2.p2();

        line1 = QLineF(P["44'"],P["341'"]);
        line2 = QLineF(P["941'"],P["44'"]);
        line1.setAngle( ((line1.angle()+line2.angle())/2) );
        line1.setLength(line1.length()*0.2);
        P["44'v"]=line1.p2();
        line1.setLength(line2.length()*0.2);
        P["44'n"] = Unicus::rPoint( line1.p2(),line1.p1(),180.0f);



        this->sign( Sync( attr( SYNC_NAME, QString( "Front1" ) ),
                          attr( SYNC_TYPE, C2DSync::Sign ),
                          attr( SYNC_LIST, MakeList( "44'" ) ),
                          LM->thick_solid(),
                          attr( SYNC_SIGN_DUAL, false ),
                          attr( SYNC_SIGN_ANGLE, 180.0f ) ), LB( "First" ) );

        this->sign( Sync( attr( SYNC_NAME, QString( "Front2" ) ),
                          attr( SYNC_TYPE, C2DSync::Sign ),
                          attr( SYNC_LIST, MakeList( "14" ) ),
                          LM->thick_solid(),
                          attr( SYNC_SIGN_DUAL, false ),
                          attr( SYNC_SIGN_ANGLE, -90.0f ) ), LB( "First" ) );

        this->sign( Sync( attr( SYNC_NAME, QString( "FrontA" ) ),
                          attr( SYNC_TYPE, C2DSync::Sign ),
                          attr( SYNC_LIST, MakeList( "signA" ) ),
                          LM->thick_solid(),
                          attr( SYNC_SIGN_DUAL, false ),
                          attr( SYNC_SIGN_ANGLE, -line1.angle()+90 ) ), LB( "First" ) );

        this->sign( Sync( attr( SYNC_NAME, QString( "FrontD" ) ),
                          attr( SYNC_TYPE, C2DSync::Sign ),
                          attr( SYNC_LIST, MakeList( "signD" ) ),
                          LM->thick_solid(),
                          attr( SYNC_SIGN_DUAL, false ),
                          attr( SYNC_SIGN_ANGLE, line1.angle()+90.0f ) ), LB( "First" ) );



        double weight1=30.0f,weight4=25.0f,weight9=20.0f,length1n=25,length3v=10,length3n=40,length4v=50,length4n=50,length9v=60;
        line1 = QLineF(P["131"],P["333"]);
        line2.setP1( P["341"] );line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        myline = QLineF( intersectionPoint,P["341"]);
        myline.setLength(weight1/2);
        P["339"]=myline.p2();
        P["339'"]= Unicus::rPoint(P["339"],P["333"],180.0f);
        line2.setP1(myline.p2());
        line2.setAngle(line1.angle());
        line2.intersect( QLineF(P["131"],P["345"]),p);
        P["139"]=intersectionPoint;

        line2.setP1(P["139"]);line2.setLength(1.0f);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["139'"]= Unicus::rPoint(P["139"],intersectionPoint,180.0f);

        line1 = QLineF(P["139"],P["339"]);
        line1.setLength(length1n);
        P["139n"]=line1.p2();
        line1 = QLineF(P["139'"],P["339'"]);
        line1.setLength(length1n);
        P["139n'"]=line1.p2();

        /*line1 = QLineF(P["333"],P["43"]);
        line2.setP1(P["333"]);
        line2.setAngle(line1.angle()-90.0f);
        line2.setLength((weight1-(weight1*0.10f))/2);
        P["339"]=line2.p2();
        myline.setP1(line2.p2());
        myline.setAngle(line1.angle());
        myline.setLength( length3n );
        P["339n"]=myline.p2();
        myline.setAngle(line1.angle()+180.0f);
        myline.setLength( length3v );
        P["339v"]=myline.p2();
/////////////
        P["339'"]= Unicus::rPoint(P["339"],P["333"],180.0f);

        myline.setP1(P["339'"]);
        myline.setAngle(line1.angle());
        myline.setLength( length3n );
        P["339n'"]=myline.p2();
        myline.setAngle(line1.angle()+180.0f);
        myline.setLength( length3v );
        P["339v'"]=myline.p2();*/
//////////////////
        line1 = QLineF(P["43"],P["933"]);
        line1.setAngle( (((line1.angle()+ QLineF(P["333"],P["43"]).angle())/2)) );

       // line1 = QLineF(P["43"],P["933"]);
        line2.setP1(P["43"]);
        line2.setAngle(line1.angle()-90.0f);
        line2.setLength(weight4/2);
        P["439"]=line2.p2();

        myline.setP1(line2.p2());
        myline.setAngle(line1.angle());
        myline.setLength( length4n );
        P["439n"]=myline.p2();
        myline.setAngle(line1.angle()+180.0f);
        myline.setLength( length4v );
        P["439v"]=myline.p2();
        //
        P["439'"]= Unicus::rPoint(P["439"],P["43"],180.0f);

        myline.setP1(P["439'"]);
        myline.setAngle(line1.angle());
        myline.setLength( length4n );
        P["439n'"]=myline.p2();
        myline.setAngle(line1.angle()+180.0f);
        myline.setLength( length4v );
        P["439v'"]=myline.p2();


        line1 = QLineF(P["933"],P["43"]);
        line2.setP1(P["933"]);
        line2.setAngle(line1.angle()+90.0f);
        line2.setLength(weight9/2);
        P["939"]=line2.p2();

        myline.setP1(line2.p2());
        myline.setAngle(line1.angle());
        myline.setLength( length9v );
        P["939v"]=myline.p2();
        //
        P["939'"]= Unicus::rPoint(P["939"],P["933"],180.0f);
        myline.setP1(P["939'"]);
        myline.setAngle(line1.angle());
        myline.setLength( length9v );
        P["939v'"]=myline.p2();

        //P["356"] = P["352"]-QPointF(20.0f,0.0f);
//Правые сплайнырукава
        double spline357n=30.0f,spline451v=30.0f,spline451n=30.0f,spline951v=40.0f;
        P["356"] = QPointF(splinepointonx(Spline352p341, P["352"].x()-20.0f  ,0.05f));

        line1 = QLineF(P["355"],P["951"]);
        line2.setP1(P["356"]);
        line2.setAngle(line1.angle()+90.0f);
        line2.intersect(line1,p);
        P["357-sec"]=intersectionPoint;
        QPointF p357m356 = (P["357-sec"] - P["356"]);
        line1 = QLineF(P["357-sec"],P["451"]);
        //line1.setP1(P["357-sec"]);
        line1.setLength(spline357n);
        P["357n"]= line1.p2();
        P["356'"]= P["357-sec"]+p357m356;
        P["356n"]= P["357n"]-p357m356;
        P["356n'"]= P["357n"]+p357m356;

        P["453"]=P["451"] - p357m356;
        P["453'"]=P["451"] + p357m356;

        line2 = QLineF(P["451"],P["951"]);
        line2.setAngle( (((line1.angle()+line2.angle())/2)) );
      //  P["999"]=line2.p2();
        line2.setLength(spline451n);
        P["451n"]=line2.p2();
        P["453n"]=P["451n"] - p357m356;
        P["453n'"]=P["451n"] + p357m356;

        line2 = Unicus::rLine(line2,line2.p1(),180.0f);
        line2.setLength(spline451v);
        P["451v"]=line2.p2();
        P["453v"]=P["451v"] - p357m356;
        P["453v'"]=P["451v"] + p357m356;

        line1 = QLineF(P["951"],P["451"]);
        line1.setLength(spline951v);
        P["951v"]=line1.p2();
        P["952"]=P["951"] - p357m356;
        P["952'"]=P["951"] + p357m356;
        P["952v"]=P["951v"] - p357m356;
        P["952v'"]=P["951v"] + p357m356;

        //РАССЧЕТ ДЛЯ СПЛАЙНОВ 355-356-341
        line1 = QLineF(P["356"],P["355"]);
        line2 = QLineF(P["341"],P["356"]);
        line1.setAngle( ((line1.angle()+line2.angle())/2) );
        line1.setLength(line1.length()*0.45);
        P["-2"]= line1.p2();
        line1.setLength(line2.length()*0.45);
        P["-4"] = Unicus::rPoint(line1.p2(),line1.p1(),180.0f);

        line1 = QLineF(P["355"], P["353"]);
        line1.setLength(line1.length()*0.3);
        P["-1"]=line1.p2();

        line1 = QLineF(P["341"], QPointF(P["356"].x(),P["341"].y()));
        line1.setLength(line1.length()*0.3);
        P["-3"]=line1.p2();
//зеркальные точки

        line1 = QLineF(P["355"],P["357-sec"]);
        line2 = QLineF(P["355"],P["-2"]);
        line2.setAngle(line1.angle() + line1.angle() - line2.angle());
        P["-2'"]=line2.p2();

        line2 = QLineF(P["355"],P["-1"]);
        line2.setAngle(line1.angle() + line1.angle() - line2.angle());
        P["-1'"]=line2.p2();

        ///Рассчет сплайна 939-951-952'
        line1 = QLineF(P["939'"],P["939v'"]);
        line1.setLength(QLineF(P["939'"],P["951"]).length()*0.5);
        line1.setAngle(line1.angle()+90.0f);
        P["939'r"]=line1.p2();
        line1 = QLineF(P["952'"],P["952v'"]);
        line1.setLength(QLineF(P["952'"],P["951"]).length()*0.5);
        line1.setAngle(line1.angle()-90.0f);
        P["952'l"]=line1.p2();

    if(LB( "Second" )==true)
    {
        line1 = QLineF(P["951"],P["952'"]);
        line2 = QLineF(P["939'"],P["951"]);
        line1.setAngle( ((line1.angle()+line2.angle())/2) );
        line1.setLength(line1.length()*0.1);
        P["951r"]= line1.p2();
        line1.setLength(line2.length()*0.1);
        P["951l"] = Unicus::rPoint(line1.p2(),line1.p1(),180.0f);
    }
     ///Рассчет сплайна 939-952
     line1 = QLineF(P["952"],P["952v"]);
     line1.setLength(QLineF(P["939"],P["952"]).length()*0.5);
     line1.setAngle(line1.angle()-90.0f);
     P["952l"]=line1.p2();
     line1 = QLineF(P["939"],P["939v"]);
     line1.setLength(QLineF(P["939"],P["952"]).length()*0.5);
     line1.setAngle(line1.angle()+90.0f);
     P["939r"]=line1.p2();

     line1 =QLineF(P["453"],P["453v"]);

     this->sign( Sync( attr( SYNC_NAME, QString( "Front1" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "453" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -line1.angle()+90 ) ), LB( "Second" ) );



     this->sign(  Sync( attr( SYNC_NAME, QString( "Front2" ) ),
                        attr( SYNC_TYPE, C2DSync::Sign ),
                        attr( SYNC_LIST, MakeList( "453'" ) ),
                        LM->thick_solid(),
                        attr( SYNC_SIGN_DUAL, false ),
                        attr( SYNC_SIGN_ANGLE, -line1.angle()+90 ) ), LB( "Second" ) );


     line1 =QLineF(P["439"],P["439v"]);
     this->sign( Sync( attr( SYNC_NAME, QString( "FrontA" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "439" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -line1.angle()-90 ) ), LB( "Second" ) );

     this->sign( Sync( attr( SYNC_NAME, QString( "FrontD" ) ),
                       attr( SYNC_TYPE, C2DSync::Sign ),
                       attr( SYNC_LIST, MakeList( "439'" ) ),
                       LM->thick_solid(),
                       attr( SYNC_SIGN_DUAL, false ),
                       attr( SYNC_SIGN_ANGLE, -line1.angle()-90.0f ) ), LB( "Second" ) );


    if(LB( "Third" )==true)
    {
        line1.setPoints(P["355"],P["353"]);
        line1.setAngle( line1.angle()-3.0f );
        line1.setLength(QLineF(P["341"],P["355"]).length()*0.7);
        P["355d"] = line1.p2();

        QPainterPath mirrorspline;


        double persent,templength = (P["355"].x()-P["131"].x())*LD("3K0");
        P["3K0"]=P["333"]+QPointF(templength,0);
        templength = templength + P["131"].x();
        if(templength>P["341"].x()+1)
        {
            H( "shov1" ) = true;
            mirrorspline.moveTo( P["341"] );
            mirrorspline.cubicTo( P["Sh351'"], P["355d"], P["355"] );
            persent = splinepersentonx(mirrorspline, templength ,0.05f);
            P["P341"] = mirrorspline.pointAtPercent(persent);
            if(P["P341"]!=P["355"])
                line1.setPoints( P["P341"],
                     P["P341"] + QPointF( mirrorspline.length()*(1-persent),0 ) );
            line1.setAngle(mirrorspline.angleAtPercent(persent));
            line1.setLength(line1.length()*0.4f);
            P["P341u"]=line1.p2();
            line2.setPoints(P["355"],P["353"]);
            line2.setAngle(line2.angle()+3);
            line2.setLength(line1.length());
            P["P355d"]=line2.p2();

            line1.setAngle(line1.angle()+180);
            line1.setLength(mirrorspline.length()*(persent)*0.3);
            P["P341d"]=line1.p2();
            line2.setPoints(P["341"],P["341"]+QPointF(1,0));
            line2.setLength(line1.length());
            P["341s"]=line2.p2();

        }
        else if( (templength<=P["341"].x()+1) &&
                 (templength>=P["341"].x()-1) )
        {
            H( "shov2" ) = true;
          //  P["341"]=P["341"];
          //  P["P341u"]=P["Sh351'"];
          //  P["P355d"]=P["355d"];
        }else if( (templength<P["341"].x()-1) &&
                 (templength>P["345"].x()+1) )
        {
            H( "shov3" ) = true;
            mirrorspline.moveTo( P["341"] );
            mirrorspline.cubicTo( P["Sh341"], P["345spline"], P["345"] );
            persent = splinepersentonx(mirrorspline, templength ,0.05f);
            P["P341"] = mirrorspline.pointAtPercent(persent);
            line1.setPoints( P["P341"],
                     P["P341"] + QPointF( mirrorspline.length()*(1-persent),0 ) );
            line1.setAngle(mirrorspline.angleAtPercent(persent));
            line1.setLength(line1.length()*0.37f);
            P["P341u"]=line1.p2();
            line2.setPoints(P["345"],P["131"]);
            line2.setAngle(line2.angle()+180);
            line2.setLength(line1.length());
            P["P345d"]=line2.p2();

            line1.setAngle(line1.angle()+180);
            line1.setLength(mirrorspline.length()*(persent)*0.4);
            P["P341d"]=line1.p2();
            line2.setPoints(P["341"],P["341"]-QPointF(1,0));
            line2.setLength(line1.length());
            P["341s"]=line2.p2();
        }else if( (templength<=P["345"].x()+1) &&
                  (templength>=P["345"].x()-1) )
        {
            H( "shov4" ) = true;
        }else if( (templength<P["345"].x()-1))
        {
            H( "shov5" ) = true;
            QLineF(P["131"],P["345"]).intersect(QLineF(P["3K0"],P["3K0"]+QPointF(0,1)),p);
            P["P341"]=intersectionPoint;
        }

        line1 = QLineF(P["355"],P["45"]);
        line1.setAngle(line1.angle()+3);
        line2.setPoints(P["43"],P["45"]);
        line2.intersect(line1,p);
        P["451-sec"]=intersectionPoint;
        P["451-sec"]=P["451-sec"]-QPointF(5,0);
        line1.setPoints(P["355"],P["451-sec"]);
        line2.setPoints(P["131"],P["333"]);
        if(LB("shov1"))
        {
            P["341'"] = mirrorpoint( P["P341"],line1 );
            P["341'l"] = mirrorpoint( P["P341u"],line1 );
            P["355'd"] = mirrorpoint( P["P355d"],line1 );

            P["341-"] = mirrorpoint( P["P341"],line2 );
            P["341-r"] = mirrorpoint( P["P341d"],line2 );
            P["341''l"] = mirrorpoint( P["341s"],line2 );
            P["341''"] = mirrorpoint( P["341"],line2 );

            P["345''"] = mirrorpoint( P["345"],line2 );
            P["345''d"]= mirrorpoint( P["345spline"],line2 );
            P["341''r"]= mirrorpoint( P["Sh341"],line2 );

            P["left"] = P["341-"];
            P["right"] = P["341'"];

        }else if(LB("shov2"))
        {
            P["341'"] = mirrorpoint( P["341"],line1 );
            P["341'l"] = mirrorpoint( P["Sh351'"],line1 );
            P["355'd"] = mirrorpoint( P["355d"],line1 );

            P["341''"] = mirrorpoint( P["341"],line2 );
            P["341''r"] = mirrorpoint( P["Sh341"],line2 );
            P["345''d"]= mirrorpoint( P["345spline"],line2 );
            P["345''"]= mirrorpoint( P["345"],line2 );
            P["right"] = P["341'"];
            P["left"] = P["341''"];

        }else if(LB("shov3"))
        {
            P["341'"] = mirrorpoint( P["341"],line1 );
            P["341'l"] = mirrorpoint( P["Sh351'"],line1 );
            P["355'd"] = mirrorpoint( P["355d"],line1 );
            P["341'r"] = mirrorpoint( P["341s"],line1 );
            P["341-"] = mirrorpoint( P["P341"],line1 );
            P["341-l"] = mirrorpoint( P["P341d"],line1 );

            P["341''"] = mirrorpoint( P["P341"],line2 );
            P["341''r"] = mirrorpoint( P["P341u"],line2 );
            P["345''d"]= mirrorpoint( P["P345d"],line2 );
            P["345''"]= mirrorpoint( P["345"],line2 );
            P["right"] = P["341-"];
            P["left"] = P["341''"];

        }else if(LB( "shov4" ))
        {
            P["341'"] = mirrorpoint( P["341"],line1 );
            P["341'l"] = mirrorpoint( P["Sh351'"],line1 );
            P["355'd"] = mirrorpoint( P["355d"],line1 );

            P["341'r"] = mirrorpoint( P["Sh341"],line1 );
            P["345'd"]= mirrorpoint( P["345spline"],line1 );
            P["345'"]= mirrorpoint( P["345"],line1 );


            P["345''"]= mirrorpoint( P["345"],line2 );
            P["right"] = P["345'"];
            P["left"] = P["345''"];
        }else if(LB( "shov5" ))
        {
            P["341'"] = mirrorpoint( P["341"],line1 );
            P["341'l"] = mirrorpoint( P["Sh351'"],line1 );
            P["355'd"] = mirrorpoint( P["355d"],line1 );

            P["341'r"] = mirrorpoint( P["Sh341"],line1 );
            P["345'd"] = mirrorpoint( P["345spline"],line1 );
            P["345'"] = mirrorpoint( P["345"],line1 );
            P["345'u"] = mirrorpoint( P["P341"],line1 );

            P["345''"] = mirrorpoint( P["P341"],line2 );
            P["right"] = P["345'u"];
            P["left"] = P["345''"];
        }
        myline.setPoints(P["3K0"],P["3K0"]-QPointF(0,1));
        myline.setAngle(QLineF(P["341"],P["44"]).angle());
        myline.intersect(QLineF(P["43"],P["451"]),p);
        P["3K1"] = intersectionPoint;

        myline.setPoints(P["3K1"],P["3K1"]-QPointF(0,1));
        myline.setAngle(QLineF(P["44"],P["941"]).angle());
        myline.intersect(QLineF(P["951"],P["941"]),p);
        P["3K2"] = intersectionPoint;
/******************************************************************************
*******************************************************************************
******************************************************************************/
    //line1 - 357; line2 - 333

        P["c_right"] = mirrorpoint( P["3K1"],line1 );
        P["c_left"] = mirrorpoint( P["3K1"],line2 );

        line2.setPoints(P["43"],P["933"]);
        P["b_right"] = mirrorpoint( P["3K2"],QLineF(P["451-sec"],P["951"]) );
        P["cb_left"] = mirrorpoint( P["44"],line2 );
        P["b_left"] = mirrorpoint( P["3K2"],line2 );

        templength = QLineF(P["43"],P["c_left"]).angle() - QLineF(P["43"],P["cb_left"]).angle();
        P["b_left"] = Unicus::rPoint(P["b_left"],P["43"],-templength);
        P["b_left-r"] = Unicus::rPoint(P["933"],P["43"],-templength);


        Unicus::console( "shov1---->", LD( "shov1" ) );
        Unicus::console( "shov2---->", LD( "shov2" ) );
        Unicus::console( "shov3---->", LD( "shov3" ) );
        Unicus::console( "shov4---->", LD( "shov4" ) );
        Unicus::console( "shov5---->", LD( "shov5" ) );
    }

}

void C2DSleeve::DrawOnWidget()
{
    qDebug() << "Point: "  << P["Sv331"];

    this->line ( Sync( attr( SYNC_NAME, QString( "43-131" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "131" ) ),
                       LM->thick_solid() ), LB("First") );

  //  this->point( MakeSync( "332''", Sync::Point, MakeList( "332''" ), LM->bold_solid() ), true );
    //this->point( MakeSync( "333", Sync::Point, MakeList( "333" ), LM->bold_solid() ), true );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-341-345" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341", "Sh341", "345spline", "345" ) ),
                        LM->thick_dashed() ), LB( "Second" )||LB( "Third" ) );
    //this->spline( Sync( attr( SYNC_NAME, QString( "S-341-353" ) ),
    //                    attr( SYNC_TYPE, C2DSync::Spline ),
    //                  attr( SYNC_LIST, MakeList( "341", "Sh351", "353spline", "353" ) ),
    //                    LM->bold_solid() ), LB( "Second" ) );


    this->spline(  Sync( attr( SYNC_NAME, QString( "S-355-14" ) ),
                         attr( SYNC_TYPE, C2DSync::Spline ),
                         attr( SYNC_LIST, MakeList( "355", "141vert", "141hor", "14" ) ),
                         LM->bold_solid() ), LB("First")||LB("Second")||LB( "Third" ) );


    this->spline(  Sync( attr( SYNC_NAME, QString( "S-332''-14" ) ),
                         attr( SYNC_TYPE, C2DSync::Spline ),
                         attr( SYNC_LIST, MakeList( "14", "144", "144vert", "131" ) ),
                         LM->bold_solid() ), LB("First")||LB("Second")||LB( "Third" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "345-131" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "131", "345" ) ),
                       LM->bold_solid() ), LB( "Third" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "43-44'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "44'" ) ),
                       LM->thick_solid() ), LB("First") );

  //  this->line ( MakeSync( "94-933", Sync::Line, MakeList( "94", "933" ), LM->thick_solid() ), LB("First") );
    this->line ( Sync( attr( SYNC_NAME, QString( "43-931" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "933" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "355-451" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "355", "451" ) ),
                       LM->thick_solid() ), LB("First") );


    this->line ( Sync( attr( SYNC_NAME, QString( "451-951" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "451", "951" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "355-353'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "355", "353'" ) ),
                       LM->bold_solid() ), LB("First") );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-353'-341'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "353'", "353'spline", "341'spline", "341'p" ) ),
                        LM->thick_solid() ), LB( "First" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "131-345'" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "131", "345'" ) ),
                       LM->bold_solid() ), LB("First") );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-345'-341''" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "345'", "345'spline", "341''spline", "341''p" ) ),
                        LM->thick_solid() ), LB( "First" ) );


    this->line ( Sync( attr( SYNC_NAME, QString( "341''-44'''" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "341''p", "44'''" ) ),
                       LM->bold_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "44'''-43p" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43p", "44'''" ) ),
                       LM->bold_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "44''-43p" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43p", "44''" ) ),
                       LM->bold_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "44''-941''" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "44''", "941''" ) ),
                       LM->bold_solid() ), LB("First") );

  //  this->line ( MakeSync( "933-941''", Sync::Line, MakeList( "933", "941''" ), LM->thick_solid() ), LB( "First" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "357-341'p" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "357", "341'p" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "357-333" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "357", "333" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "341''p-333" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "341''p", "333" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "43-44''" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "44''" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "43-44'''" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "44'''" ) ),
                       LM->thick_solid() ), LB("First") );

    this->line ( Sync( attr( SYNC_NAME, QString( "14-14vertical" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "14", "14vertical" ) ),
                       LM->thick_solid() ), LB("First") );

    //bottom spline
    this->spline( Sync( attr( SYNC_NAME, QString( "S-941''-933" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "941''", "941''r", "933l", "933" ) ),
                                LM->bold_solid() ), LB( "First" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-933-951" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "933", "933r", "951l", "951" ) ),
                                LM->bold_solid() ), LB( "First" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-951-941'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "951", "951r", "941'l", "941'" ) ),
                                LM->bold_solid() ), LB( "First" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-341'p-44'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "341'p", "44'v", "44'v", "44'" ) ),
                                LM->bold_solid() ), LB( "First" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-44'-941'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "44'", "44'n", "44'n", "941'" ) ),
                                LM->bold_solid() ), LB( "First" ) );




    this->spline( Sync( attr( SYNC_NAME, QString( "S-139-439" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "139", "139n", "439v", "439" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-139'-439'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "139'", "139n'", "439v'", "439'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    //
    this->spline( Sync( attr( SYNC_NAME, QString( "S-439-939" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "439", "439n", "939v", "939" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-439'-939'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "439'", "439n'", "939v'", "939'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );




    this->spline( Sync( attr( SYNC_NAME, QString( "S-356-453" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "356", "356n", "453v", "453" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-453-952" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "453", "453n", "952v", "952" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-356'-453'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "356'", "356n'", "453v'", "453'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-453'-952'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "453'", "453n'", "952v'", "952'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "345-139" ) ),
                                attr( SYNC_TYPE, C2DSync::Line ),
                                attr( SYNC_LIST, MakeList( "345", "139" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "131-139'" ) ),
                                attr( SYNC_TYPE, C2DSync::Line ),
                                attr( SYNC_LIST, MakeList( "131", "139'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "951-939'" ) ),
                                attr( SYNC_TYPE, C2DSync::Line ),
                                attr( SYNC_LIST, MakeList( "951", "939'" ) ),
                                LM->thick_solid() ), LB( "Second" ) );

  //  this->line ( MakeSync( "939-952", Sync::Line, MakeList( "939", "952" ), LM->thick_solid() ), LB( "Second" ) );
   // this->line ( MakeSync( "952'-952", Sync::Line, MakeList( "952'", "952" ), LM->thick_solid() ), LB( "Second" ) );


 //   356-353 353-355

    //this->spline( Sync( attr( SYNC_NAME, QString( "S-355-356" ) ),
    //                            attr( SYNC_TYPE, C2DSync::Spline ),
    //                            attr( SYNC_LIST, MakeList( "355", "-1", "-2", "356" ) ),
    //                            LM->bold_solid() ), LB( "Third" ) );
    this->spline( Sync( attr( SYNC_NAME, QString( "S-355-356'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "355", "-1'", "-2'", "356'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-341-356" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "341", "-3", "-4", "356" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

 //   this->line ( MakeSync( "939-95112", Sync::Line, MakeList( "-1'", "-1" ), LM->thick_solid() ), LB( "Second" ) );
 //   this->line ( MakeSync( "939-951122", Sync::Line, MakeList( "-2'", "-2" ), LM->thick_solid() ), LB( "Second" ) );
//    this->point( MakeSync( "952'l", Sync::Point, MakeList( "952'l" ), LM->bold_solid() ), LB( "Second" ) );
//    this->point( MakeSync( "951l", Sync::Point, MakeList( "951l" ), LM->bold_solid() ), LB( "Second" ) );
//    this->point( MakeSync( "951r", Sync::Point, MakeList( "951r" ), LM->bold_solid() ), LB( "Second" ) );
//    this->point( MakeSync( "939'r", Sync::Point, MakeList( "939'r" ), LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-952'-951" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "952'", "952'l", "951r", "951" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-951-939'" ) ),
                                attr( SYNC_TYPE, C2DSync::Spline ),
                                attr( SYNC_LIST, MakeList( "951", "951l", "939'r", "939'" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "952-939" ) ),
                                attr( SYNC_TYPE, C2DSync::Line ),
                                attr( SYNC_LIST, MakeList( "952", "939" ) ),
                                LM->bold_solid() ), LB( "Second" ) );

  //   this->spline( MakeSync( "S-939-952", Sync::Spline,
  //                          MakeList( "939", "939r", "952l", "952" ),
  //                                  LM->bold_solid() ), LB( "Second" ) );

    //this->point( MakeSync( "952l", Sync::Point, MakeList( "952l" ), LM->bold_solid() ), LB( "Second" ) );
    //this->point( MakeSync( "939r", Sync::Point, MakeList( "939r" ), LM->bold_solid() ), LB( "Second" ) );

/*3-ya PART**********************
********************************/
//    this->point( Sync( attr( SYNC_NAME, QString( "341''M" ) ),
//                       attr( SYNC_TYPE, C2DSync::Point ),
//                       attr( SYNC_LIST, MakeList( "341''" ) ),
//                       LM->bold_solid() ), true );
//    this->line ( Sync( attr( SYNC_NAME, QString( "353-355" ) ),
//                       attr( SYNC_TYPE, C2DSync::Line ),
//                       attr( SYNC_LIST, MakeList( "353", "355" ) ),
//                       LM->bold_solid() ), LB( "Third" ) );
    this->spline( Sync( attr( SYNC_NAME, QString( "S-341-355" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341", "Sh351'", "355d", "355" ) ),
                        LM->thick_dashed() ), LB( "Third" ) );


    this->spline( Sync( attr( SYNC_NAME, QString( "S-P341-P355" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "P341", "P341u", "P355d", "355" ) ),
                        LM->thick_solid() ), LB( "shov1" ) );
    this->spline( Sync( attr( SYNC_NAME, QString( "S-341-P341" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "P341", "P341d", "341s", "341" ) ),
                        LM->thick_solid() ), LB( "shov1" )||LB( "shov3" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-P341-P345" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "P341", "P341u", "P345d", "345" ) ),
                        LM->thick_solid() ), LB( "shov3" ) );
//////////////////////
    this->spline( Sync( attr( SYNC_NAME, QString( "S-341'-355" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341'", "341'l", "355'd", "355" ) ),
         LM->thick_solid() ), LB( "shov1" )||LB( "shov2" )||LB("shov3")||LB( "shov4" )||LB( "shov5" ) );
    this->spline( Sync( attr( SYNC_NAME, QString( "S-341''-341-" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341-", "341-r", "341''l", "341''" ) ),
                        LM->thick_solid() ), LB( "shov1" ) );
    this->spline( Sync( attr( SYNC_NAME, QString( "S341''-345''" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341''", "341''r", "345''d", "345''" ) ),
                        LM->thick_solid() ), LB( "shov1" )||LB( "shov2" )||LB("shov3") );

    this->line ( Sync( attr( SYNC_NAME, QString( "345''-131" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "345''", "131" ) ),
                       LM->bold_solid() ), LB( "shov1" )||LB( "shov2" )||LB("shov3")||LB( "shov4" )||LB( "shov5" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S341'-341-" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341-", "341-l", "341'r", "341'" ) ),
                        LM->thick_solid() ), LB( "shov3" ) );

    this->spline( Sync( attr( SYNC_NAME, QString( "S-341'-345'" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "341'", "341'r", "345'd", "345'" ) ),
                        LM->thick_solid() ), LB( "shov4" )||LB( "shov5" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "345'-345'u" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "345'", "345'u" ) ),
                       LM->bold_solid() ), LB( "shov5" ) );
//////////////////////////////////////////////////////////
    this->line ( Sync( attr( SYNC_NAME, QString( "right-c_right" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "right", "c_right" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "b_right-c_right" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "b_right", "c_right" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "951-b_right" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "951", "b_right" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "3K2-951" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "3K2", "951" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "3K2-933" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "3K2", "933" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "43-933" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "933" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "43-b_left-r" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "43", "b_left-r" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "b_left-b_left-r" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "b_left", "b_left-r" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "b_left-c_left" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "b_left", "c_left" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "left-c_left" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "left", "c_left" ) ),
                       LM->thick_solid() ), LB( "Third" ) );

    this->line ( Sync( attr( SYNC_NAME, QString( "3K0-3K1" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "3K0", "3K1" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "3K2-3K1" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "3K2", "3K1" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    this->line ( Sync( attr( SYNC_NAME, QString( "451-sec-355" ) ),
                       attr( SYNC_TYPE, C2DSync::Line ),
                       attr( SYNC_LIST, MakeList( "451-sec", "355" ) ),
                       LM->thick_solid() ), LB( "Third" ) );
    //////////////////////////////////////////////
    this->point( Sync( attr( SYNC_NAME, QString( "941" ) ),
                        attr( SYNC_TYPE, C2DSync::Point ),
                        attr( SYNC_LIST, MakeList( "941" ) ),
                        LM->thick_solid() ), LB( "First" ) );
    this->point( Sync( attr( SYNC_NAME, QString( "45" ) ),
                        attr( SYNC_TYPE, C2DSync::Point ),
                        attr( SYNC_LIST, MakeList( "45" ) ),
                        LM->thick_solid() ), LB( "First" ) );
    this->line( Sync( attr( SYNC_NAME, QString( "44-941" ) ),
                        attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "941","44" ) ),
                        LM->thick_solid() ), LB( "First" ) );


}
