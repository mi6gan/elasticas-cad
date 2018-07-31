#include "C2DDress.h";
//начало рукава
void C2DDress::SleeveUpdate()//onUpdate
{
  //  this->getVariables();
    this->SleevesetVariables();
    this->SleeveUpdatePoints();
    this->SleeveDrawOnWidget();
    //this->dialog->show();

    //Unicus::console( "MY NAME IS ...", 2 );
}

void C2DDress::SleeverequiredVariables()//получаем значения из elaStiCas
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

    this->addVariable( C2DVariable::set( "Sleeve:H", this->prefix() + "Sleeve:H", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 1 ) );
    this->addVariable( C2DVariable::set( "T28",this->prefix() + "T28", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 10 ) );
    this->addVariable( C2DVariable::set( "PT28",this->prefix() + "PT28", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 10 ) );
    this->addVariable( C2DVariable::set( "Sleeve:Step65",this->prefix() + "Sleeve:Step65", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 1 ) );
    this->addVariable( C2DVariable::set( "Sleeve:Step87",this->prefix() + "Sleeve:Step87", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 1 ) );
    this->addVariable( C2DVariable::set( "Sleeve:Step93",this->prefix() + "Sleeve:Step93", "Not described",
                       C2DVariable::Unitless, C2DVariable::General,0 , 10 ) );
}

void C2DDress::SleevesetVariables()// обрабатываем, выставляем значения
{

    H( "Width" ) = sleevewidth;//Ширина проймы

    //H( "SleeveType" ) = D("Type") + 1;//Тип рукава
    H( "SleeveType" ) = 1;//Тип рукава
    // proima 6 кусков сплайна
    //[0] - 14' - 144
    //[1] - 144 - 332
    //[2] - 332 - 341
    //[3] - 341 - 352
    //[4] - 352 - 147
    //[5] - 147 - 14''


    H("a+b+c+d" ) = proima[0].length()+proima[1].length()+
                    proima[2].length()+proima[3].length()+
                    proima[4].length()+proima[5].length();
    H("H") = D("Sleeve:H");//0.07f;
    H("ShOK") = (D("T28")+D("PT28")) * 0.5;
    H("DOK") = LD("a+b+c+d") * ( 1 + LD("H") );

    H( "Height" ) = 0.885*LD("DOK")*sqrt( 0.25 - pow( (LD("ShOK")/LD("DOK")),2) );//Высота оката
    //H( "Height" ) = sleeve_VOK-15;
    //H( "Height" ) = D("T39") - 5;
    Unicus::console( "Sleeve:H---------->",LD("H") );
    Unicus::console( "Sleeve:a+b+c+d---------->",LD("a+b+c+d") );
    Unicus::console( "Sleeve:sleevewidth",LD( "Width" ) );
    Unicus::console( "Sleeve:ShOK",LD("ShOK") );

    Unicus::console( "Sleeve:Height---------->",LD("Height") );
    double Ppos = (LD("H")*LD("a+b+c+d"));//Ппос = Дпр*Н
    H("Ppos" ) = Ppos;
    Unicus::console( "Sleeve:Ppos",LD("Ppos") );
    Unicus::console( "Sleeve:DOK",LD("DOK") );

    H( "K344" ) = 0.65f;//Коэфициент для рассчета нахождения точки 344 : 341-444=K344 * (341-343)
    H( "gamma" ) = 93.0f;//Угол гамма из точки 332

    H( "alpha" ) = 3.0f;//Угол  из точки 333 к оси OY
    H( "betta" ) = 0.0f;//Угол  из точки 355 к оси OY
    //H( "b87" ) = D("Sleeve:Step87");

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


void C2DDress::SleeveUpdatePoints()//находим точки для построения рукава, по алгоритму
{
    QLineF l1,l2;QPointF p1;
    P["SP0"] = sleevestartpoint + QPointF( 100 + 2 * LD( "Width" ) ,0 ); // P["37"] + QPointF( 700.0f, 0.0f );
    P["S331"] = P["SP0"];
    P["S351"] = QPointF(P["35"].x()-P["33"].x()+P["S331"].x(),P["S331"].y());
    l1.setPoints( P["S331"],P["S351"] );
    l1.setLength(l1.length()*D("Sleeve:Step65"));
    Unicus::console( "S351L1",l1.length() );
    Unicus::console( "S351L1",D("Sleeve:Step65") );
    P["S341"] = l1.p2();
    P["S332"] = QPointF( P["S331"].x(),P["S331"].y()+l1.length() );
    P["S342"] = QPointF( P["S341"].x(),P["S341"].y()+l1.length() );
    l1.setPoints( P["S351"],P["S331"] );
    l1.setLength(l1.length()*(1-D("Sleeve:Step65")));
    P["S341-1"] = l1.p2();
    P["S352"] = P["S351"] + QPointF(0,l1.length());
    P["S343"] = P["S352"] + QPointF(-l1.length(),0);
    P["S333"] = P["S351"] - QPointF( LD("ShOK"),0 );
    drawline( "S333-S351","S333","S351",true,LM->thick_dashed() );
    P["S13"] = P["S333"] + QPointF(0,LD("Height"));
    drawline( "S333-S13","S333","S13",true,LM->thick_dashed() );
    l1.setPoints(P["S351"],P["S333"]);
    P["S14"] = P["S13"] + QPointF( l1.length()*0.45,0);
    P["S141"] = P["S13"] + QPointF( l1.length()*0.73,0);
    P["S15"] = QPointF( P["S351"].x(),P["S13"].y() );
    l1.setPoints( P["S15"],P["S141"] );
    l1.setAngle(l1.angle()+180);
    P["S141-1"] = l1.p2();
    drawline( "S141-1-S15","S141-1","S15",true,LM->thick_dashed() );
    drawline( "S141-S15","S141","S15",true,LM->thick_dashed() );
    drawline( "S14-S13","S14","S13",true,LM->thick_dashed() );
    l1 = QLineF(P["S141-1"],P["S343"]);
    P["S353"] = l1.pointAt(0.5);
    l1.setPoints( P["S353"],P["S343"] );
    P["S354"] = Unicus::CircCirc(P["S353"],l1.length(),P["S343"],QLineF(P["S343"],P["S341"]).length(),true);
    p1 = Unicus::CircCirc(P["S353"],l1.length(),P["S343"],QLineF(P["S343"],P["S341"]).length(),false);
    if( p1.x()>P["S354"].x() )
        P["S354"] = p1;
    P["S355"] = Unicus::circline( QLineF(P["S351"],P["S15"]),P["S353"],l1.length(),true );
    p1 =  Unicus::circline( QLineF(P["S351"],P["S15"]),P["S353"],l1.length(),false );
    if( p1.y()<P["S355"].y() )
        P["S355"] = p1;
    l1.setPoints( P["S141"],P["S355"] );
    l1.setLength( QLineF(P["S141"],P["S15"]).length() );
    P["S142"] = l1.p2();
    P["S143"] = QLineF(P["S14"],P["S141"]).pointAt(0.5);
    P["S131"] = QLineF(P["S13"],P["S333"]).pointAt(0.3);
    P["S344"] = QLineF(P["S131"],P["S342"]).pointAt(0.5);
    l1.setPoints( P["S342"],P["S344"] );
    P["S345"] = Unicus::CircCirc( P["S344"],l1.length(),P["S342"],QLineF(P["S342"],P["S341"]).length(),true );
    p1 = Unicus::CircCirc( P["S344"],l1.length(),P["S342"],QLineF(P["S342"],P["S341"]).length(),false );
    if( p1.y()<P["S345"].y() )
        P["S345"] = p1;
    l1.setPoints(P["S345"],P["S131"]);
    l2.setPoints( P["S15"],P["S13"] );
    l1.intersect(l2,&p1);
    P["S133-1"]=p1;
    l1.setPoints( P["S13"],P["S133-1"] );
    l1.setAngle(l1.angle()+180);
    P["S133"] = l1.p2();
    P["S134"] = QLineF(P["S133"],P["S131"]).pointAt(0.5);
    P["S144"] = QLineF(P["S133"],P["S14"]).pointAt(0.5);

    l1.setPoints( P["S333"],P["S333"]+QPointF(0,-1) );
    l1.setAngle(90-D("Sleeve:Step87"));
    l1.setLength( 680-QLineF(P["S13"],P["S333"]).length() );
    //Unicus::console( "QLineF(P[121],P[14]).length()",QLineF(P["121"],P["14"]).length() );
    //l1.setLength( QLineF(P["121"],P["14"]).length() );
    P["S93"] = l1.p2();
    l1.setLength( 453-QLineF(P["S13"],P["S333"]).length() );
    P["S43"] = l1.p2();
    l2.setPoints(P["S355"],P["S355"]+QPointF(1,1));
    l2.setAngle(l1.angle());
    l1.setPoints(P["S93"],P["S333"]);
    l1.setAngle( l1.angle()+90 );
    l1.intersect(l2,&p1);
    P["S95"] = p1;
    l1.setPoints(P["S43"],P["S43"]+QPointF(1,1));
    l1.setAngle( l2.angle()-90 );
    l1.intersect(l2,&p1);
    P["S45"] = p1;
    l1.setPoints(P["S45"],P["S43"]);
    if(D("Sleeve:Step93")==0)
        P["S451"] = P["S45"];
    else
    {
        l1.setLength( D("Sleeve:Step93") );
        P["S451"] = l1.p2();
    }
    l1.setPoints(P["S95"],P["S93"]);
    l1.setLength( D("T29")*0.5+D("PT29") );
    P["S931"] = l1.p2();
    P["S94"] = l1.pointAt(0.5);
    l1.setPoints( P["S43"],P["S931"] );
    l2.setPoints( P["S94"],P["S94"]+QPointF(1,1) );
    l2.setAngle( l1.angle()+90 );
    l1.intersect(l2,&p1);
    P["S933"] = p1;
    l1.setPoints( P["S933"],P["S94"] );
    l2.setPoints( P["S451"],P["S95"] );
    l1.intersect(l2,&p1);
    P["S951"] = p1;


    drawline( "S933-S43","S43","S933",true,LM->thick_yellow() );
    drawline( "S933-S951","S951","S933",true,LM->thick_yellow() );
    drawline( "S451-S951","S451","S951",true,LM->thick_yellow() );
    drawline( "S451-S355","S451","S355",true,LM->thick_yellow() );
    drawline( "S451-S45","S451","S45",true,LM->thick_dashed() );
    drawline( "S94-S931","S94","S931",true,LM->thick_dashed() );
    drawline( "S355-S95","S355","S95",true,LM->thick_dashed() );
    drawline( "S93-S95","S93","S95",true,LM->thick_dashed() );
    drawline( "S333-S93","S333","S93",true,LM->thick_dashed() );
    drawline( "S333-S43","S333","S43",true,LM->thick_solid() );
    drawline( "S45-S43","S45","S43",true,LM->thick_dashed() );
    drawline( "S131-S134","S131","S134",true,LM->thick_dashed() );
    drawline( "S144-S134","S144","S134",true,LM->thick_dashed() );
    drawline( "S133-S133-1","S133","S133-1",true,LM->thick_dashed() );
    drawline( "S344-S345","S344","S345",true,LM->thick_dashed() );
    drawline( "S131-S342","S342","S131",true,LM->thick_dashed() );
    drawline( "S13-S131","S13","S131",true,LM->thick_dashed() );
    drawline( "S142-S143","S142","S143",true,LM->thick_dashed() );
    drawline( "S142-S355","S142","S355",true,LM->thick_dashed() );
    drawline( "S141-1-S354","S141-1","S354",true,LM->thick_dashed() );
    drawline( "S141-1-S353","S141-1","S353",true,LM->thick_dashed() );
    drawline( "S343-S355","S343","S355",true,LM->thick_dashed() );


    QPainterPath arc341_332;
    arc341_332 = cGeometry::arc_round( P["S342"],P["S341"],90 );
    drawpath( "Sarc341-332",arc341_332,true,LM->thick_blue() );
    arc341_332 = cGeometry::arc_round( P["S343"],P["S341"],-90 );
    drawpath( "Sarc341-352",arc341_332,true,LM->thick_blue() );

    ///SHOV!!!
    l1.setPoints( P["S451"],P["S43"] );
    l1.setLength( QLineF(P["S351"],P["S341"]).length() );
    P["S441"] = l1.p2();
    l1.setPoints( P["S951"],P["S933"] );
    l1.setLength( QLineF(P["S351"],P["S341"]).length() );
    P["S941"] = l1.p2();
    l1.setPoints(P["S333"],P["S43"]);
    l2.setPoints(P["S341"],P["S341"]+QPointF(1,1));
    l2.setAngle(l1.angle()+90);
    l1.intersect(l2,&p1);
    P["S334"] = p1;
    l1.setPoints( P["S334"],P["S341"] );
    l1.setAngle(l1.angle()+180);
    P["S341-1"] = l1.p2();

    l1.setPoints(P["S334"],P["S341"]);
    l1.setAngle( l1.angle()+90 );
    l2.setPoints(P["S441"],P["S441"]+QPointF(1,1));
    l2.setAngle(l1.angle()+90);
    l1.intersect(l2,&p1);
    P["Smypoint"] = p1;
    l2.setPoints( P["Smypoint"],P["S441"] );
    l2.setAngle(l2.angle()+180);
    P["S441-1"] = l2.p2();

    P["S941-1"] = cGeometry::mirrorpoint( P["S941"],l1 );
    l2.setPoints(P["S941"],P["S933"]);
    l2.intersect(l1,&p1);
    P["S930"] = p1;
    P["S933-1"] = cGeometry::mirrorpoint( P["S933"],l1 );
    P["S345-1"] = cGeometry::mirrorpoint( P["S345"],l1 );

    P["S342-1"] = Unicus::CircCirc( P["S345-1"],QLineF(P["S342"],P["S345"]).length(),
                                    P["S341-1"],QLineF(P["S341"],P["S342"]).length(),true );
    p1 = Unicus::CircCirc( P["S345-1"],QLineF(P["S342"],P["S345"]).length(),
                                    P["S341-1"],QLineF(P["S341"],P["S342"]).length(),false );
    if( p1.y()>P["S342-1"].y() )
        P["S342-1"] = p1;

    l1.setPoints( P["S342-1"],P["S345-1"] );
    l2.setPoints( P["S342-1"],P["S341-1"] );
    arc341_332 = cGeometry::arc_round( P["S342-1"],P["S345-1"],l1.angleTo(l2) );
    drawpath( "SarcS342-1-345-13",arc341_332,true,LM->thick_blue() );

    l1.setPoints(P["S351"],P["S355"]);
    P["S341-2"] = cGeometry::mirrorpoint( P["S341"],l1 );
    l1.setPoints(P["S451"],P["S355"]);
    P["S441-2"] = cGeometry::mirrorpoint( P["S441"],l1 );
    l2.setPoints( P["S441"],P["S451"] );
    l1.setPoints( P["S441"],P["S441-2"] );
    l1.setLength( l2.length()*2 );
    P["S441-2"] = l1.p2();


    l1.setPoints(P["S451"],P["S951"]);
    P["S441-3"] = cGeometry::mirrorpoint( P["S441"],l1 );
    l1.setPoints( P["S441"],P["S441-3"] );
    l1.setLength( l2.length()*2 );
    P["S441-3"] = l1.p2();

    l1.setPoints(P["S451"],P["S951"]);
    P["S941-2"] = cGeometry::mirrorpoint( P["S941"],l1 );
    l1.setPoints(P["S351"],P["S355"]);
    P["S354-1"] = cGeometry::mirrorpoint( P["S354"],l1 );

    P["S343-1"] = Unicus::CircCirc( P["S354-1"],QLineF(P["S354"],P["S343"]).length(),
                                    P["S341-2"],QLineF(P["S341"],P["S343"]).length(),true );
    p1 = Unicus::CircCirc( P["S354-1"],QLineF(P["S354"],P["S343"]).length(),
                                    P["S341-2"],QLineF(P["S341"],P["S343"]).length(),false );
    if( p1.y()>P["S343-1"].y() )
        P["S343-1"] = p1;
    l1.setPoints( P["S343-1"],P["S354-1"] );
    l2.setPoints( P["S343-1"],P["S341-2"] );
    arc341_332 = cGeometry::arc_round( P["S343-1"],P["S341-2"],l2.angleTo(l1) );
    drawpath( "SarcS342-1-345-12",arc341_332,true,LM->thick_blue() );


    drawline( "S354-1-S343-1","S354-1","S343-1",true,LM->thick_dashed() );
    drawline( "S351-S341-2","S351","S341-2",true,LM->thick_dashed() );
    drawline( "S441-3-S341-2","S441-3","S341-2",true,LM->thick_solid() );
    drawline( "S441-3-S441-2","S441-3","S441-2",true,LM->thick_solid() );
    drawline( "S941-2-S441-2","S941-2","S441-2",true,LM->thick_solid() );
    drawline( "S441-3-S451","S441-3","S451",true,LM->thick_dashed() );
    drawline( "S451-S441-2","S451","S441-2",true,LM->thick_dashed() );
    drawline( "S941-2-S951","S941-2","S951",true,LM->thick_solid() );




    drawline( "S342-1-S345-1","S342-1","S345-1",true,LM->thick_dashed() );
    drawline( "S341-1-S345-1","S341-1","S345-1",true,LM->thick_dashed() );
    drawline( "S131-S345-1","S131","S345-1",true,LM->thick_dashed() );
    drawline( "S930-S933","S930","S933",true,LM->thick_dashed() );
    drawline( "S930-S933-1","S930","S933-1",true,LM->thick_dashed() );
    drawline( "S43-S933-1","S43","S933-1",true,LM->bold_solid() );
    drawline( "S941-1-S933-1","S941-1","S933-1",true,LM->bold_solid() );
    drawline( "S941-1-S441-1","S941-1","S441-1",true,LM->bold_solid() );
    drawline( "S341-1-S441-1","S341-1","S441-1",true,LM->bold_solid() );
    drawline( "S341-1-S334","S334","S341-1",true,LM->thick_dashed() );
    drawline( "S341-S334-","S334","S341",true,LM->thick_dashed() );
    drawline( "S441-S941","S441","S941",true,LM->thick_dashed() );
}

void C2DDress::SleeveDrawOnWidget()
{
    line( Sync( attr( SYNC_NAME,  QString( "S331-S351" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "S331", "S351" ) ),
                LM->thick_green() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "S341-S342" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "S341", "S342" ) ),
                LM->thick_dashed() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "S341-S342" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "S341", "S342" ) ),
                LM->thick_dashed() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "S331-S332" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "S331", "S332" ) ),
                LM->thick_dashed() ),
          true );
}
