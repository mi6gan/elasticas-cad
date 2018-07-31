#include "C2DDress.h";
QList< QPainterPath > gathertype1( double a1, QLineF ls, QPointF p,QPainterPath realpath )
{
    QList< QPainterPath > result;
    QPainterPath path;
    double a = realpath.toReversed().angleAtPercent(0);
    double a2 = ls.angle()-(a-ls.angle());
    C2DPath cp=C2DPath(realpath.toReversed(),180-a-a2 ,1);
    if(a1>cp.shape().length())
        a1 = cp.shape().length();
    a1 = a1/cp.shape().length();
    path = cp.myshape(p, a1,0.1 );
    result.append(path);
    return result;
}
QPainterPath  pregathertype2( QPainterPath p, QPainterPath add, double length, double a  )
{
    C2DPath cp;
    cp = C2DPath( add,a );
    if(length>add.length())
        length = add.length();
    p.connectPath( cp.myshape( p.pointAtPercent(1),length/add.length(),0.1 ) );
    return p;
}
QPainterPath  pregathertype3( QPainterPath p,double an, QPainterPath add, double length )
{
    C2DPath cp;
    cp = C2DPath( add,-(an-add.angleAtPercent(0)) );
    p.connectPath( cp.myshape( p.pointAtPercent(1),length/add.length(),0.1 ) );
    return p;
}
QList< QPainterPath > gathertype2( double a1, QLineF ls, QPointF p,QPainterPath realpath )
{
    QList< QPainterPath > result;
    QPainterPath path;
    double a = realpath.toReversed().angleAtPercent(0);
    double a2 = ls.angle()-(a-ls.angle());
    C2DPath cp=C2DPath(realpath.toReversed(),180-a-a2 ,1);
    if(a1>cp.shape().length())
        a1 = cp.shape().length();
    a1 = a1/cp.shape().length();
    path = cp.myshape(p, a1, 0.1 );

    result.append(path);
    return result;
}

QPainterPath linepath( QPointF p1, QPointF p2 )
{
    QPainterPath path;
    path.moveTo(p1);
    path.lineTo(p2);
    return path;
}
QLineF pathline( QPainterPath path )
{
    return QLineF(path.pointAtPercent(0),path.pointAtPercent(1));
}
QPainterPath C2DDress::addvorotpathplus( QPainterPath up,QPainterPath down, bool oneside, bool right )
{
    QLineF line1,line2;
    QPainterPath addru,addrd,addlu,addld;
    if(!oneside||right)
    {
        line1.setPoints( up.pointAtPercent(1),down.pointAtPercent(1) );
        line1.setAngle( line1.angle()-90 );
        line1.setLength( LD("A") );
        addru.moveTo(line1.p1());
        addru.lineTo(line1.p2());
        line2.setPoints( down.pointAtPercent(1),down.pointAtPercent(1)+QPointF(1,1) );
        line2.setAngle( line1.angle() );
        line2.setLength( line1.length() );
        addrd.moveTo(line2.p1());
        addrd.lineTo(line2.p2());
    }
    if(!oneside||!right)
    {
        line1.setPoints( up.pointAtPercent(0),down.pointAtPercent(0) );
        line1.setAngle( line1.angle()+90 );
        line1.setLength( LD("AL") );
        addlu.moveTo(line1.p2());
        addlu.lineTo(line1.p1());
        line2.setPoints( down.pointAtPercent(0),down.pointAtPercent(0)+QPointF(1,1) );
        line2.setAngle( line1.angle() );
        line2.setLength( line1.length() );
        addld.moveTo(line2.p2());
        addld.lineTo(line2.p1());
    }
    if(!oneside)
    {
        wide_collar_up = addlu;
        wide_collar_down = addld;
        wide_collar_up.connectPath( up );
        wide_collar_down.connectPath( down );
        wide_collar_up.connectPath( addru );
        wide_collar_down.connectPath( addrd );
        return addru.toReversed();
    }else if(!right)
    {
        wide_collar_up = addlu;
        wide_collar_down = addld;
        wide_collar_up.connectPath( up );
        wide_collar_down.connectPath( down );
        return addru.toReversed();
    }else
    {
        wide_collar_up = up;
        wide_collar_down = down;
        wide_collar_up.connectPath( addru );
        wide_collar_down.connectPath( addrd );
        return addru.toReversed();
    }
}

void C2DDress::CollarGetValues()
{

    this->addVariable( C2DVariable::set( "Arut", this->prefix() + "Arut", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "Ardt", this->prefix() + "Ardt", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "Alut", this->prefix() + "Alut", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "Aldt", this->prefix() + "Aldt", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->CollarGetDsgn();
}

void C2DDress::CollarGetDsgn()
{
    //"c0" "c0_a" "c0_b" "c0_cl" "c0_ct" "c0_a1" "c0_a2" "c0_a3"
    QString items[]={"c0","c1","c2","c3"};
    for( int i = 0; i<4; i++ )
    {
        this->addVariable( C2DVariable::set( "c"+QString::number(i), this->prefix() + "c" + QString::number(i), "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_a", this->prefix() + "c" + QString::number(i) + "_a", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_b", this->prefix() + "c" + QString::number(i) + "_b", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_cl", this->prefix() + "c" + QString::number(i) + "_cl", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_ct", this->prefix() + "c" + QString::number(i) + "_ct", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_a1", this->prefix() + "c" + QString::number(i) + "_a1", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_a2", this->prefix() + "c" + QString::number(i) + "_a2", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( "c"+QString::number(i)+"_a3", this->prefix() + "c" + QString::number(i) + "_a3", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    }
}

void C2DDress::MakeCollar()
{
    QLineF line1,line2;
    /////Обработка полученных значений
    H("A") = D("A");
    H("AL") = D("AL");
    if( D("vorot_planka") == 1 )
    {
        H("A") = 0;
        H("AL") = 0;
    }
    if( D("stoika_dsgn")==0 )
        H("AL") = LD("A");


    if( D("stoika_dsgn") == 2 )
        H("stoika_krai") = 0;
    else
        H("stoika_krai") = D("stoika_krai");
    vorot_add = false;
    if( LD("stoika_krai") == 0 )
    {
        H("A")=0;
        H("AL")=0;
        vorot_add = false;
    }
    else if( LD("stoika_krai") == 1 )
    {
        H("A")=-LD("A");
        H("AL")=-LD("AL");
        vorot_add = false;
    }
    else if( LD("stoika_krai") == 2 )
    {
        H("A")=LD("A");
        H("AL")=LD("AL");
        if( ( LD("is_clasp")==1 )||( LD("is_cut")==1 ) )
            vorot_add = true;
    }
    if( ( LD("is_clasp")==0 )&&( LD("is_cut")==0 ) )
    {
        H("A")=0;
        H("AL")=0;
        vorot_add = false;
    }
    Unicus::console( "D(vorot_dsgn)--->", D("vorot_dsgn") );
    ////razvod vorotnika
    if(D("vorot_dsgn")==0)
    {
        H("Pos1") = D("Pos1")/2;
        H("Pos2") = D("Pos2")/2;
        H("Pos1lev") = D("Pos1")/2;
        H("Pos2lev") = D("Pos2")/2;
    }else
    {
        H("Pos1lev") = D("Pos1lev");
        H("Pos2lev") = D("Pos2lev");
        H("Pos1") = D("Pos1");
        H("Pos2") = D("Pos2");
    }
    ////// конец обработки
    collarpart * spin, * spinm, * pol, * polm;
    collarpart p1 = collarpart(),p2 = collarpart(),p3 = collarpart(),p4 = collarpart();
    if(
            ( LD("is_cut") == 0 )   &&
            ( LD("is_clasp") == 0 ) &&
            ( LD("g_p_nomirror") == false ) &&
            ( D("vorot_dsgn") == 0 )
      )
    {
        simple = true;
        gorr = gorr + LD("Pos1");
        gorl = gorl + LD("Pos2");
        p1 = collarpart(gorl,D("v_r_sN"),
                        D("v_r_suL") ,
                        D("v_r_sdL"),
                        gorl+gorl);
        p2 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorr);
        p1.y1 = D("OYsp");
        p1.y2 = D("OYsh");
        p1.cos1 = D("OYspa");
        p1.cos2 = D("OYsha");
        p2.y2 = D("OYpo");
        p2.cos2 = D("OYpoa");
        p3.y2 = D("OYsh");
        p3.cos2 = D("OYsha");
        p4.cos2 = p1.cos1;
        spin = &p1;
        pol = &p2;
        spinm = &p1;
        polm = &p2;
        p3=0;
        p4=0;
        H("col_h1") = D("H3");
        H("col_h2") = D("H2");
        H("col_h3") = D("H1");
    }else
    {
        simple = false;
        if( ( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0 ) )
        {
            if( LD("clasp_location") == 0 ) //  спинка
            {
                p1 = collarpart(gorl + zipper + colclasptype,D("v_r_sN"),
                                D("v_r_suL"),
                                D("v_r_sdL"),
                                (gorl + zipper + colclasptype)+(gorlm - zipper + colclasptype));
                p2 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p3 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p4 = collarpart(gorlm - zipper + colclasptype,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),
                                (gorl + zipper + colclasptype)+(gorlm - zipper + colclasptype));
                p1.y1 = D("OYsp");
                p1.y2 = D("OYsh");
                p1.cos1 = -D("OYspa");
                p1.cos2 = D("OYsha");
                p2.y2 = D("OYpo");
                p2.cos2 = D("OYpoa");
                p3.y2 = D("OYsh");
                p3.cos2 = -D("OYsha");
                p4.cos2 = -p1.cos1;
                spin = &p1;
                pol = &p2;
                spinm = &p4;
                polm = &p3;
                H("col_h1") = D("H3");
                H("col_h2") = D("H2");
                H("col_h3") = D("H1");
                if( D("vorot_dsgn") == 0 )
                    H("col_h4") = D("H2");
                else
                    H("col_h4") = D("H2lev");
                if( D("vorot_dsgn") == 0 )
                    H("col_h5") = D("H3");
                else
                    H("col_h5") = D("H3lev");
            }
            else if( LD("clasp_location") == 1 ) //  полочка
            {
                p1 = collarpart(gorrm-zipper+colclasptype,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),
                                (gorrm-zipper+colclasptype)+(gorr+zipper+colclasptype));
                p2 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p3 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p4 = collarpart(gorr+zipper+colclasptype,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),
                                (gorrm-zipper+colclasptype)+(gorr+zipper+colclasptype));
                p1.y1 = D("OYpo");
                p1.y2 = D("OYsh");
                p1.cos1 = -D("OYpoa");
                p1.cos2 = -D("OYsha");
                p2.y2 = D("OYsp");
                p2.cos2 = D("OYspa");
                p3.y2 = D("OYsh");
                p3.cos2 = D("OYsha");
                p4.cos2 = -p1.cos1;
                spin = &p3;
                pol = &p4;
                spinm = &p2;
                polm = &p1;
                if( D("vorot_dsgn") == 0 )
                    H("col_h1") = D("H1");
                else
                    H("col_h1") = D("H1lev");
                if( D("vorot_dsgn") == 0 )
                    H("col_h2") = D("H2");
                else
                    H("col_h2") = D("H2lev");
                H("col_h3") = D("H3");
                H("col_h4") = D("H2");
                H("col_h5") = D("H1");
            }
            else
            {
                p1 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p2 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p3 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorrm+gorr);
                p4 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorrm+gorr);
                p1.y1 = D("OYsh");
                p1.y2 = D("OYsp");
                p1.cos1 = -D("OYsha");
                p1.cos2 = D("OYspa");
                p2.y2 = D("OYsh");
                p2.cos2 = D("OYsha");
                p3.y2 = D("OYpo");
                p3.cos2 = D("OYpoa");
                p4.cos2 = p1.cos1;
                spin = &p2;
                pol = &p3;
                spinm = &p1;
                polm = &p4;
                if( D("vorot_dsgn") == 0 )
                    H("col_h1") = D("H2");
                else
                    H("col_h1") = D("H2lev");
                H("col_h2") = D("H3");
                H("col_h3") = D("H2");
                H("col_h4") = D("H1");
                if( D("vorot_dsgn") == 0 )
                    H("col_h5") = D("H2");
                else
                    H("col_h5") = D("H2lev");
            }
        }else if( LD("is_cut") == 1 )
        {
            if( LD("cut_location") == 0 ) //  спинка
            {
                p1 = collarpart(gorl + cut,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),(gorl + cut)+(gorlm - cut));
                p2 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p3 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p4 = collarpart(gorlm - cut,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),(gorl + cut)+(gorlm - cut));
                p1.y1 = D("OYsp");
                p1.y2 = D("OYsh");
                p1.cos1 = -D("OYspa");
                p1.cos2 = D("OYsha");
                p2.y2 = D("OYpo");
                p2.cos2 = D("OYpoa");
                p3.y2 = D("OYsh");
                p3.cos2 = -D("OYsha");
                p4.cos2 = -p1.cos1;
                spin = &p1;
                pol = &p2;
                spinm = &p4;
                polm = &p3;
                H("col_h1") = D("H3");
                H("col_h2") = D("H2");
                H("col_h3") = D("H1");
                if( D("vorot_dsgn") == 0 )
                    H("col_h4") = D("H2");
                else
                    H("col_h4") = D("H2lev");
                if( D("vorot_dsgn") == 0 )
                    H("col_h5") = D("H3");
                else
                    H("col_h5") = D("H3lev");
            }
            else if( LD("cut_location") == 1 ) //  полочка
            {
                p1 = collarpart(gorrm-cut,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),(gorrm-cut)+(gorr+cut));
                p2 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p3 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
                p4 = collarpart(gorr+cut,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),(gorrm-cut)+(gorr+cut));
                p1.y1 = D("OYpo");
                p1.y2 = D("OYsh");
                p1.cos1 = -D("OYpoa");
                p1.cos2 = -D("OYsha");
                p2.y2 = D("OYsp");
                p2.cos2 = D("OYspa");
                p3.y2 = D("OYsh");
                p3.cos2 = D("OYsha");
                p4.cos2 = -p1.cos1;
                spin = &p3;
                pol = &p4;
                spinm = &p2;
                polm = &p1;
                if( D("vorot_dsgn") == 0 )
                    H("col_h1") = D("H1");
                else
                    H("col_h1") = D("H1lev");
                if( D("vorot_dsgn") == 0 )
                    H("col_h2") = D("H2");
                else
                    H("col_h2") = D("H2lev");
                H("col_h3") = D("H3");
                H("col_h4") = D("H2");
                H("col_h5") = D("H1");
            }
            else
            {
                p1 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorl+gorlm);
                p2 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorl+gorlm);
                p3 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p4 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
                p1.y1 = D("OYsh");

                p1.y2 = D("OYsp");
                p1.cos1 = -D("OYsha");
                p1.cos2 = D("OYspa");
                p2.y2 = D("OYsh");
                p2.cos2 = D("OYsha");
                p3.y2 = D("OYpo");
                p3.cos2 = D("OYpoa");
                p4.cos2 = p1.cos1;
                spin = &p2;
                pol = &p3;
                spinm = &p1;
                polm = &p4;
                if( D("vorot_dsgn") == 0 )
                    H("col_h1") = D("H2");
                else
                    H("col_h1") = D("H2lev");
                H("col_h2") = D("H3");
                H("col_h3") = D("H2");
                H("col_h4") = D("H1");
                if( D("vorot_dsgn") == 0 )
                    H("col_h5") = D("H2");
                else
                    H("col_h5") = D("H2lev");
            }
        }else if( D("vorot_dsgn") == 0 )
        {
            p1 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
            p2 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
            p3 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
            p4 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
            p1.y1 = D("OYsh");
            p1.y2 = D("OYsp");
            p1.cos1 = -(D("OYsha"));
            p1.cos2 = D("OYspa");
            p2.y2 = D("OYsh");
            p2.cos2 = D("OYsha");
            p3.y2 = D("OYpo");
            p3.cos2 = D("OYpoa");
            p4.cos2 = p1.cos1;
            Unicus::console( "***************************************", D("OYspa") );
            spin = &p1;
            pol = &p3;
            spinm = &p2;
            polm = &p4;
            H("col_h1") = D("H2");
            H("col_h2") = D("H3");
            H("col_h3") = D("H2");
            H("col_h4") = D("H1");
            H("col_h5") = D("H2");
        }
        else
        {
            Unicus::console( "BUGBUGBGUBGUB",gorlm );
            p1 = collarpart(gorlm,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
            p2 = collarpart(gorl,D("v_r_sN"),D("v_r_suL"),D("v_r_sdL"),gorlm+gorl);
            p3 = collarpart(gorr,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
            p4 = collarpart(gorrm,D("v_r_pN"),D("v_r_puL"),D("v_r_pdL"),gorr+gorrm);
            p1.y1 = D("OYsh");
            p1.y2 = D("OYsp");
            p1.cos1 = -D("OYsha");
            ///Unicus::console( "***************************************", D("OYspa") );
            p1.cos2 = D("OYspa");
            p2.y2 = D("OYsh");
            p2.cos2 = D("OYsha");
            p3.y2 = D("OYpo");
            p3.cos2 = D("OYpoa");
            p4.cos2 = p1.cos1;
            spin = &p2;
            pol = &p3;
            spinm = &p1;
            polm = &p4;
            H("col_h1") = D("H2lev");
            H("col_h2") = D("H3");
            H("col_h3") = D("H2");
            H("col_h4") = D("H1");
            H("col_h5") = D("H2lev");
        }
    }

    if(simple != true)
        if( D("vorot_dsgn") == 0 )
        {
            spin->changel( D("Pos2")*spin->k() );
            spinm->changel( D("Pos2")*spinm->k() );
            spin->changef( D("Pos2") );
            spinm->changef( D("Pos2") );
            pol->changel( D("Pos1")*pol->k() );
            polm->changel( D("Pos1")*polm->k() );
            pol->changef( D("Pos1") );
            polm->changef( D("Pos1") );
        }else
        {
            //if( !Gmirropath_right )
            //{
            //    H("Pos1lev") = D("Pos1");
            //    H("Pos1") = D("Pos1");
           // }
           // if( !Gmirropath_left )
           // {
           //     H("Pos2lev") = D("Pos2");
           //     H("Pos2") = D("Pos2");
           // }
            spin->changel( LD("Pos2") );
            spinm->changel( LD("Pos2lev") );
            spin->changef( LD("Pos2")+LD("Pos2lev") );
            spinm->changef( LD("Pos2")+LD("Pos2lev") );
            pol->changel( LD("Pos1") );
            polm->changel( LD("Pos1lev") );
            pol->changef( LD("Pos1")+LD("Pos1lev") );
            polm->changef( LD("Pos1")+LD("Pos1lev") );
        }

    //Unicus::console( "gorl", gorl );
    //Unicus::console( "gorlm", gorlm );
    //Unicus::console( "gorr", gorr );
    //Unicus::console( "gorrm", gorrm );
    //Unicus::console("zipper",zipper);
    //Unicus::console("p1",p1.l());
    //Unicus::console("vorot_form",D("vorot_form"));
    //Unicus::console("colclasptype",colclasptype);

    //высота в разных участках
    //H("col_h4") = 60;
    //H("col_h5") = 70;
    H("vorot_l_add") = LD("AL");
    H("vorot_r_add") = LD("A");

    H("c0") = D("c0");
    H("c0_a") = D("c0_a");
    H("c0_b") = D("c0_b");
    H("c0_cl") = - D("c0_cl");
    H("c0_ct") = - ( D("c0_ct") );
    H("c0_a1") = - D("c0_a1");
    H("c0_a2") = - D("c0_a2");
    H("c0_a3") = - D("c0_a3");

    H("c1") = D("c1");
    H("c1_a") = ( D("c1_a") );
    H("c1_b") = D("c1_b");
    H("c1_cl") = -(D("c1_cl") );
    H("c1_ct") = D("c1_ct");
    H("c1_a1") = ( D("c1_a1") );
    H("c1_a2") = D("c1_a2");
    H("c1_a3") = ( D("c1_a3") );

    H("c2") = D("c2");//left down
    H("c2_a") = D("c2_a");
    H("c2_b") = - ( D("c2_b") );
    H("c2_cl") = -D("c2_cl");
    H("c2_ct") = D("c2_ct");
    H("c2_a1") = D("c2_a1");
    H("c2_a2") = D("c2_a2");
    H("c2_a3") = D("c2_a3");

    H("c3") = D("c3");
    H("c3_a") = D("c3_a");
    H("c3_b") = -D("c3_b");
    H("c3_cl") = -D("c3_cl");
    H("c3_ct") = -D("c3_ct");
    H("c3_a1") = -D("c3_a1");
    H("c3_a2") = -D("c3_a2");
    H("c3_a3") = -D("c3_a3");

    /*** Vorotnik : start ***/
    P["V1d"] = P["11"] + QPointF( 0,100 );
    P["V1u"] = P["V1d"] + QPointF( 0,LD("col_h1") );
    P["V2d"] = P["V1d"] + QPointF( p1.l(),0 );
    P["V2u"] = P["V2d"] + QPointF( 0,LD("col_h2") );
    P["V3d"] = P["V2d"] + QPointF( p2.l(),0 );
    P["V3u"] = P["V3d"] + QPointF( 0,LD("col_h3") );
    P["V4d"] = P["V3d"] + QPointF( p3.l(),0 );

    P["V4u"] = P["V4d"] + QPointF( 0,LD("col_h4") );
    P["V5d"] = P["V4d"] + QPointF( p4.l(),0 );

    if(simple)
        P["V5u"] = P["V3u"];
    else
        P["V5u"] = P["V5d"] + QPointF( 0,LD("col_h5") );

    double col_height = 0;
    double AR=0,AL=0;
    AL = p1.l();
    if( simple )
    {
        col_height = LD("col_h3");
        AR = p2.l();
    }
    else
    {
        col_height = LD("col_h5");
        AR = p4.l();
    }
        //add
    if( D("stoika_dsgn") == 0 )
        if(AR<AL)
            AL=AR;
        else
            AR=AL;

    if( LD("stoika_krai") == 1 )
    {
        if( -LD("vorot_l_add") > AL )
        {
            H("vorot_l_add") = -AL+0.0001;
            if( D("stoika_dsgn") == 1 )
            {
                VorotDialog->SetDspinVal( "AL", AL/10 );
                H("AL") = AL;
            }
        }
        if( -LD("vorot_r_add") > AR )
        {
            H("vorot_r_add") = -AR+0.0001;
            VorotDialog->SetDspinVal( "A", AR/10 );
            H("A") = AR;
        }

    }
    P["V_add_ld"] = P["V1d"] + QPointF( -LD("vorot_l_add"), 0 );
    P["V_add_lu"] = P["V_add_ld"] + QPointF( 0,LD("col_h1") );
    P["V_add_rd"] = P["V5d"] + QPointF( LD("vorot_r_add"), 0 );
    P["V_add_ru"] = P["V_add_rd"] + QPointF( 0,col_height );
    if(vorot_add==false)
    {
        if( !simple )
        {
            if( LD("vorot_l_add") < 0 )
            {
                if(-LD("vorot_l_add")<p1.l())
                {
                    p1.changel( LD("vorot_l_add") );
                    p1.changef( LD("vorot_l_add") );
                }else
                {
                    double tmp = -p1.l()+0.001;
                    p1.changel( tmp );
                    p1.changef( tmp );
                }
            }
            if( LD("vorot_r_add") < 0 )
            {
                if(-LD("vorot_r_add")<p4.l())
                {
                    p4.changel( LD("vorot_r_add") );
                    p4.changef( LD("vorot_r_add") );
                }
                else
                {
                    double tmp = -p4.l()+0.001;
                    p4.changel( tmp );
                    p4.changef( tmp );
                }
            }
        }
        P["V1d"] = P["V_add_ld"];
        P["V1u"] = P["V_add_lu"];
        P["V5d"] = P["V_add_rd"];
        P["V5u"] = P["V_add_ru"];
    }


    P["vorot_s1"] = P["V2d"];
    P["vorot_s1_dlg"] = P["V2d"] + QPointF( LD("vorot_sign"),0 );
    //VorotDialog->setheights( LD("col_h1")/10,col_height/10 );
    /*** Vorotnik : End ***/
    collar_topline = QPainterPath();
    collar_topline.moveTo( P["V_add_lu"] );
    collar_topline.lineTo( P["V1u"] );
    collar_topline.lineTo( P["V2u"] );
    collar_topline.lineTo( P["V3u"] );
    collar_topline.lineTo( P["V4u"] );
    collar_topline.lineTo( P["V5u"] );
    collar_topline.lineTo( P["V_add_ru"] );
    P["collar_topline"] = collar_topline.pointAtPercent(0)+QPointF(0,1);
    collar_bottomline = QPainterPath();
    collar_bottomline.moveTo( P["V_add_ld"] );
    collar_bottomline.lineTo( P["V1d"] );
    collar_bottomline.lineTo( P["V2d"] );
    collar_bottomline.lineTo( P["V3d"] );
    collar_bottomline.lineTo( P["V4d"] );
    collar_bottomline.lineTo( P["V5d"] );
    collar_bottomline.lineTo( P["V_add_rd"] );
    P["collar_bottomline"] = collar_bottomline.pointAtPercent(0)+QPointF(0,-1);

    ppath(  Sync( attr( SYNC_NAME,  QString( "collar_topline" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "collar_topline" ) ),
                                          LM->thick_red() ), &collar_topline, 0, 0,
                                  false );
    ppath(  Sync( attr( SYNC_NAME,  QString( "collar_bottomline" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "collar_bottomline" ) ),
                                          LM->thick_red() ), &collar_bottomline, 0, 0,
                                  false );
//оформление низа
    QPointF p;QLineF line3;
    QPainterPath p1path=QPainterPath(),p2path=QPainterPath(),p3path=QPainterPath(),p4path=QPainterPath();
    p = P["V1d"] - QPointF(0,p1.y1);
    line1.setPoints( p,p+ QPointF( 1,0 ));
    line1.setLength( p1.l() );
    line1.setAngle( line1.angle()+ p1.cos1 );
    p = P["V2d"] - QPointF(0,p1.y2);

    line2.setPoints( p,p- QPointF( 1,0 ) );
    line2.setLength( p1.l() );
    line2.setAngle( line2.angle()+p1.cos2 );
    p1path = splineaboutYl( line1,line2,
                             0.3,
                             0.3,p1.l(),
                             0.005  );
    line1.setPoints( p1path.pointAtPercent(1),p1path.pointAtPercent(1)+QPointF(1,0) );
    line1.setAngle( line2.angle()+180 );
    line1.setLength( p2.l() );
    p =P["V3d"]- QPointF(0,p2.y2);
    line2.setPoints( p,p-QPointF(1,0) );
    line2.setLength( p2.l() );
    line2.setAngle(line2.angle()+ p2.cos2);
    p2path = splineaboutYl( line1,line2,
                             0.3,
                             0.3,p2.l(),
                             0.005  );
    if(!simple)
    {
        line1.setPoints( p2path.pointAtPercent(1),p2path.pointAtPercent(1)+QPointF(1,0) );
        line1.setAngle( line2.angle()+180 );
        line1.setLength( p3.l() );
        p =P["V4d"]- QPointF(0,p3.y2);
        line2.setPoints( p,p-QPointF(1,0) );
        line2.setLength( p3.l() );
        line2.setAngle(line2.angle()+ p3.cos2);
        p3path = splineaboutYl( line1,line2,
                                 0.3,
                                 0.3,p3.l(),
                                 0.005  );
        line1.setPoints( p3path.pointAtPercent(1),p3path.pointAtPercent(1)+QPointF(1,0) );
        line1.setAngle( line2.angle()+180 );
        line1.setLength( p4.l() );
        p = P["V5d"]- QPointF(0,p1.y1);
        line2.setPoints( p,p-QPointF(1,0) );
        line2.setLength( p4.l() );
        line2.setAngle(line2.angle()+ p4.cos2);
        p4path = splineaboutYl( line1,line2,
                                 0.3,
                                 0.3,p4.l(),
                                 0.005  );

    }
    P["V1dline"] = p1path.pointAtPercent(0) - QPointF(0,0);
    //p1path.connectPath( p2path );

    ppath(  Sync( attr( SYNC_NAME,  QString( "V1dline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V1dline" ) ),
                                         LM->thick_red() ), &p1path, 0, 0,
                                  false );

    P["V2dline"] = p2path.pointAtPercent(0) - QPointF(0,0);
    //p1path.connectPath( p2path );

    ppath(  Sync( attr( SYNC_NAME,  QString( "V2dline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V2dline" ) ),
                                         LM->thick_yellow() ), &p2path, 0, 0,
                                  false );
    P["V3dline"] = p3path.pointAtPercent(0) - QPointF(0,0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "V3dline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V3dline" ) ),
                                         LM->thick_red() ), &p3path, 0, 0,
                                  !simple&&false );

    P["V4dline"] = p4path.pointAtPercent(0) - QPointF(0,0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "V4dline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V4dline" ) ),
                                         LM->thick_yellow() ), &p4path, 0, 0,
                                  !simple&&false );
    QPainterPath u1,u2,u3,u4;
    QList< QPainterPath > pathlist = gettoptines( p1path,p2path,p3path,p4path );
    u1 = pathlist.at(0);
    u2 = pathlist.at(1);
    u3 = pathlist.at(2);
    u4 = pathlist.at(3);
    double u1full=0,u2full=0,u3full=0,u4full=0;
    if(simple)
    {
        u1full = u1.length();u2full = u2.length();u3full = u3.length();u4full = u4.length();
    }else
    {
        if( ( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0 ) )
        {
            if(( LD("clasp_location") == 0 )||( LD("clasp_location") == 1 ))
            {
                u1full = u1.length()+u4.length();u4full=u1full;
                u2full = u2.length()+u3.length();u3full=u2full;
            }
            else
            {
                u1full = u1.length()+u2.length();u2full=u1full;
                u3full = u3.length()+u4.length();u4full=u3full;
            }
        }
        else if( LD("is_cut") == 1 )
        {
            if( (LD("cut_location") == 0)||( LD("cut_location") == 1 ) )
            {
                u1full = u1.length()+u4.length();u4full=u1full;
                u2full = u2.length()+u3.length();u3full=u2full;
            }else
            {
                u1full = u1.length()+u2.length();u2full=u1full;
                u3full = u3.length()+u4.length();u4full=u3full;
            }
        }
        else
        {
            u1full = u1.length()+u2.length();u2full=u1full;
            u3full = u3.length()+u4.length();u4full=u3full;
        }
    }

    P["V1uline"] = u1.pointAtPercent(0) - QPointF(0,3);
    ppath(  Sync( attr( SYNC_NAME,  QString( "V1uline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V1uline" ) ),
                                         LM->thick_red() ), &u1, 0, 0,
                                  false );

    P["V2uline"] = u2.pointAtPercent(0) - QPointF(0,0);
    //p1path.connectPath( p2path );

    ppath(  Sync( attr( SYNC_NAME,  QString( "V2uline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V2uline" ) ),
                                         LM->thick_yellow() ), &u2, 0, 0,
                                  false );
    P["V3uline"] = u3.pointAtPercent(0) - QPointF(0,0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "V3uline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V3uline" ) ),
                                         LM->thick_red() ), &u3, 0, 0,
                                  !simple&&false );

    P["V4uline"] = u4.pointAtPercent(0) - QPointF(0,0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "V4uline" ) ),
                                         attr( SYNC_TYPE, C2DSync::Ppath ),
                                         attr( SYNC_LIST, MakeList( "V4uline" ) ),
                                         LM->thick_yellow() ), &u4, 0, 0,
                                  !simple&&false );
//Воротник Разведение
    vorotnik = QPainterPath();
    QLineF focusline;
    QPainterPath up,down;
    QPainterPath tmppathUP=QPainterPath(),tmppathDWN=QPainterPath(),
                 tmppathUP2=QPainterPath(),tmppathDWN2=QPainterPath();
    double decorSign1=-1,decorSign2=-1,decorSign3=-1,decorSign4=-1;
    QPainterPath sign1=QPainterPath(),sign2=QPainterPath(),sign3=QPainterPath(),sign0=QPainterPath(),
            sign4=QPainterPath();
    double sign1d=-1,sign2d=-1,sign3d=-1,sign2u=-1,sign0d=-1,sign4d=-1;
    QPainterPath up1=QPainterPath(),up2=QPainterPath(),up3=QPainterPath(),
                up4=QPainterPath(),down1=QPainterPath(),down2=QPainterPath(),
                down3=QPainterPath(),down4=QPainterPath();


    line1 = QLineF( p1path.pointAtPercent(0), u1.pointAtPercent(0) );
    focusline = line1;

    QPainterPath UpBase, DownBase;
    if(simple)
    {
        P["Vbase"] = u1.pointAtPercent(0);
        UpBase = u1;
        UpBase.connectPath(u2);
        DownBase = p1path;
        DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1) ) );
        DownBase.connectPath(p2path);
    }else
    {
        P["Vbase"] = p2path.pointAtPercent(1);
        UpBase.connectPath(u1);
        UpBase.connectPath(u2);
        UpBase.connectPath(u3);
        UpBase.connectPath(u4);
        DownBase = p1path;
        DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1) ) );
        DownBase.connectPath(p2path);
        DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1) ) );
        DownBase.connectPath(p3path);
        DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1) ) );
        DownBase.connectPath(p4path);
    }


    if(!simple)
        line1 = resize_collar( u1,p1path,
                   p1.N(),p1.du()/u1full*u1.length(), p1.dd()/p1.f()*p1.l(), line1 );
    else
        line1 = resize_collar( u1,p1path,
                   p1.N(),p1.du()/u1full*u1.length()/2, p1.dd()/p1.f()*p1.l(), line1 );
    up = wide_collar_up;
    down = wide_collar_down;
    decorSign2=down.length();

    sign0d = 0.01;
    sign0 = cGeometry::GetSign( down.pointAtPercent(0), down.angleAtPercent(0) );

    sign1d = down.length();
    sign1 = cGeometry::GetSign( down.pointAtPercent(1), down.angleAtPercent(1) );
    bool resize_leftrightleftright=false;//кубики сп.сп.п.п.
    if( (LD("is_clasp") == 1) && ( LD("clasp_location") == 2 ) )
        resize_leftrightleftright=true;
    if( (LD("is_cut") == 1) && ( LD("cut_location") == 2 ) )
        resize_leftrightleftright=true;
    if( (LD("is_cut") == 0) && (LD("is_clasp") == 0) && ( D("vorot_dsgn") == 1 ) )
        resize_leftrightleftright=true;

    up1 = wide_collar_up;
    down1 = wide_collar_down;


    if(!simple)
        line1 = resize_collar( u2,p2path ,
                   p2.N(),p2.du()/u2full*u2.length(), p2.dd()/p2.f()*p2.l(), line1 );
    else
    {
        if(resize_leftrightleftright)
            line1 = resize_collar_right( u2,p2path ,
                   p2.N(),p2.du()/u2full*u2.length()/2, p2.dd()/p2.f()*p2.l(), line1 );
        else
            line1 = resize_collar( u2,p2path ,
                   p2.N(),p2.du()/u2full*u2.length()/2, p2.dd()/p2.f()*p2.l(), line1 );
    }

    up.connectPath(wide_collar_up);
    down.connectPath(wide_collar_down);
    tmppathUP=up;
    tmppathDWN=down;

    sign2u = up.length();
    sign2d = down.length();
    sign2.moveTo( down.pointAtPercent(1) );
    sign2.lineTo( down.pointAtPercent(1)+QPointF(0.01,0.01) );
    //sign2.lineTo( up.pointAtPercent(1) );
    sign2.moveTo( down.pointAtPercent(1) );

    up2 = wide_collar_up;
    down2 = wide_collar_down;

    if( simple != true )
    {

        focusline = line1;

        if( resize_leftrightleftright )
            line1 = resize_collar( u3,p3path,
                       p3.N(),p3.du()/u3full*u3.length(), p3.dd()/p3.f()*p3.l(), line1 );
        else
            line1 = resize_collar_right( u3,p3path,
                   p3.N(),p3.du()/u3full*u3.length(), p3.dd()/p3.f()*p3.l(), line1 );
        up.connectPath(wide_collar_up);
        down.connectPath(wide_collar_down);
        tmppathUP2=wide_collar_up;
        tmppathDWN2=wide_collar_down;
        decorSign3=tmppathDWN2.length();
        //drawpath( "dbg1",wide_collar_up,true,LM->thick_green() );
        //drawpath( "dbg2",wide_collar_down,true,LM->thick_green() );
        sign3d = down.length();
        sign3 = cGeometry::GetSign( down.pointAtPercent(1), down.angleAtPercent(1) );
        up3 = wide_collar_up;
        down3 = wide_collar_down;

        line1 = resize_collar_right( u4,p4path,
                       p4.N(),p4.du()/u4full*u4.length(), p4.dd()/p4.f()*p4.l(), line1 );
        up.connectPath(wide_collar_up);
        down.connectPath(wide_collar_down);
        tmppathUP2.connectPath(wide_collar_up);
        tmppathDWN2.connectPath(wide_collar_down);
        //drawpath( "dbg3",wide_collar_up,true,LM->thick_blue() );
        //drawpath( "dbg4",wide_collar_down,true,LM->thick_blue() );
        sign4d = down.length()-0.01;
        sign4 = cGeometry::GetSign( down.pointAtPercent(1), down.angleAtPercent(1) );
        up4 = wide_collar_up;
        down4 = wide_collar_down;
    }
    //Unicus::console( "focusline",focusline.angle() );
    //up = C2DPath(up,-(270-focusline.angle())).myshapefromstart();
    //down = C2DPath(down,-(270-focusline.angle())).myshapefromstart();

    if( (vorot_add == true) && ( (LD("A") > 0)||(LD("AL") > 0) ) )
    {
        //bool sign_add=false;
        if((D("is_vorot") == 1)&&(D("vorot_type") == 1))
        {//    sign_add = true;
            DownBase = DownBase.toReversed();
            if( (
                         ( D("stoika_dsgn")==0 ) && ( LD("A") > 0 )
                )||(
                         ( D("stoika_dsgn")==1 ) && ( LD("AL") > 0 )
                   ) )
                DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1)+180 ) );
            DownBase = DownBase.toReversed();
            if( LD("A") > 0 )
                DownBase.connectPath( cGeometry::GetSign( DownBase.pointAtPercent(1),DownBase.angleAtPercent(1) ) );
        }
        addvorotpathplus(UpBase,DownBase);
        UpBase = wide_collar_up;
        DownBase = wide_collar_down;


        addvorotpathplus(up,down);
        up = wide_collar_up;
        down = wide_collar_down;

        addvorotpathplus(tmppathUP,tmppathDWN,true);
        decorSign1 = wide_collar_down.length() - tmppathDWN.length();
        decorSign2 = decorSign2 + decorSign1;
        if( LD("AL")<0 )
            decorSign1 = -1;
        tmppathUP = wide_collar_up;
        tmppathDWN = wide_collar_down;
        ////////////////////////////////
        addvorotpathplus(tmppathUP2,tmppathDWN2,true,true);
        if( LD("A")>0 )
            decorSign4 = tmppathDWN2.length();
        tmppathUP2 = wide_collar_up;
        tmppathDWN2 = wide_collar_down;

        if(LD("AL") > 0)
        {
            sign1d = sign1d + LD("AL");
            sign2d = sign2d + LD("AL");
            sign2u = sign2u + LD("AL");
            sign3d = sign3d + LD("AL");
            sign4d = sign4d + LD("AL");
            sign0d = sign0d + LD("AL");
        }
    }
    /*double tempdouble = up.length();
    if( !simple )
    {
        equidistant->SetDspinMinMax( "L:OX",-(u1.length()-1)/10,10 );
        up = cGeometry::cutaddlengthtopath( up.toReversed(),LD("L:OX"),down.toReversed().pointAtPercent(1)  );
        up = up.toReversed();
        UpBase = cGeometry::cutaddlengthtopath( UpBase.toReversed(),LD("L:OX"),DownBase.toReversed().pointAtPercent(1) );
        UpBase = UpBase.toReversed();
    }
    sign2u = sign2u + up.length() - tempdouble;
    if( simple )
    {
        equidistant->SetDspinMinMax( "R:OX",-(up.length()-1)/10,10 );
        up = cGeometry::cutaddlengthtopath( up,LD("R:OX"),down.pointAtPercent(1),true  );
        UpBase = cGeometry::cutaddlengthtopath( UpBase,LD("R:OX"),DownBase.pointAtPercent(1),true );
    }
    else
    {
        equidistant->SetDspinMinMax( "R:OX",-(up.length()-1)/10,10 );
        up = cGeometry::cutaddlengthtopath( up,LD("R:OX"),down.pointAtPercent(1),true  );
        UpBase = cGeometry::cutaddlengthtopath( UpBase,LD("R:OX"),DownBase.pointAtPercent(1),true );
    }*/


//    Unicus::console( "leftH", QLineF( up.pointAtPercent(0), down.pointAtPercent(0) ).length() );
//    Unicus::console( "rightH", QLineF( up.pointAtPercent(1), down.pointAtPercent(1) ).length() );
//    QPainterPath endvar;
//    endvar = up;
//    endvar.lineTo(down.pointAtPercent(1));
//    endvar.connectPath( down.toReversed() );
//    endvar.lineTo(up.pointAtPercent(0));
//    P["v_w_endvar"] = endvar.pointAtPercent(0)+QPointF(0,-1);

//    ppath(  Sync( attr( SYNC_NAME,  QString( "v_w_endvar" ) ),
//                        attr( SYNC_TYPE, C2DSync::Ppath ),
//                        attr( SYNC_LIST, MakeList( "v_w_endvar" ) ),
//                        LM->thick_yellow() ), &endvar, /*(-(270-focusline.angle()))*/0, 0,
//                        true );


    /*--------------------------Уголки-----------------------------------------------------*/
    if( D("stoika_dsgn") == 0 )
    {
        H("c0") = D("c1");
            H("c0_a") = D("c1_a");
            H("c0_b") = D("c1_b");
            H("c0_cl") = -D("c1_cl");
            H("c0_ct") = -( D("c1_ct") );
            H("c0_a1") = -D("c1_a1");
            H("c0_a2") = -D("c1_a2");
            H("c0_a3") = -D("c1_a3");

            H("c2") = D("c3");
            H("c2_a") = D("c3_a");
            H("c2_b") = -( D("c3_b") );
            H("c2_cl") = -D("c3_cl");
            H("c2_ct") = D("c3_ct");
            H("c2_a1") = D("c3_a1");
            H("c2_a2") = D("c3_a2");
            H("c2_a3") = D("c3_a3");
    }
    if( (LD( "is_cut"   ) != 1)&&
        ((LD( "is_clasp" ) != 1)||( LD("clasp_form")==0 )) )
    {
        H("c0_a") = 0;
        H("c0_b") = 0;
        H("c1_a") = 0;
        H("c1_b") = 0;
        H("c2_a") = 0;
        H("c2_b") = 0;
        H("c3_a") = 0;
        H("c3_b") = 0;
    }

    ///CONDITION FOR CONNERS
    //col_con_leftH = P["V_add_lu"].y() - P["V_add_ld"].y();
    //col_con_rightH = P["V_add_ru"].y() - P["V_add_rd"].y();
    col_con_leftH = QLineF( up.pointAtPercent(0),down.pointAtPercent(0) ).length();
    col_con_rightH = QLineF( up.pointAtPercent(1),down.pointAtPercent(1) ).length();
    VorotDialog->setheights( col_con_leftH/10,col_con_rightH/10 );
    col_con_uX = up.length();
    col_con_dX = down.length();
    col_conners_changing_conditions();

    if( (D("Alut") != 0)||(( D("stoika_dsgn") == 0 ) && ( D("Arut") != 0 ) ) )
        cpath["c0"] = C2DPath( coners( P["V_add_lu"], LD("c0_a"), -LD("c0_b"), LD("c0_cl"), LD("c0_ct"),
                                       LD("c0_a1"), LD("c0_a2"), LD("c0_a3"), LD("c0"),up, QLineF( up.pointAtPercent(0),down.pointAtPercent(0) ) ) );
    else
        cpath["c0"] = C2DPath(QPainterPath());
    P["c0p"] = cpath["c0"].shape().pointAtPercent(0);

    if( D("Arut") != 0 )
        cpath["c1"] = C2DPath( coners( P["V_add_ru"], LD("c1_a"), -LD("c1_b"), LD("c1_cl"), LD("c1_ct"),
                                       LD("c1_a1"), LD("c1_a2"), LD("c1_a3"), LD("c1"), up.toReversed(),QLineF( up.pointAtPercent(1),down.pointAtPercent(1) ) ) );
    else
        cpath["c1"] = C2DPath(QPainterPath());
    P["c1p"] = cpath["c1"].shape().pointAtPercent(0);

    if( (D("Aldt") != 0)||(( D("stoika_dsgn") == 0 )&&( D("Ardt") != 0 )) )
        cpath["c2"] = C2DPath( coners( P["V_add_ld"], LD("c2_a"), LD("c2_b"), LD("c2_cl"), LD("c2_ct"),
                              LD("c2_a1"), LD("c2_a2"), LD("c2_a3"), LD("c2"),down,QLineF( down.pointAtPercent(0),up.pointAtPercent(0) ) ));
    else
        cpath["c2"] = C2DPath(QPainterPath());
    P["c2p"] = cpath["c2"].shape().pointAtPercent(0);

    if( D("Ardt") != 0 )
        cpath["c3"] = C2DPath( coners( P["V_add_rd"], LD("c3_a"), LD("c3_b"), LD("c3_cl"), LD("c3_ct"),
                              LD("c3_a1"), LD("c3_a2"), LD("c3_a3"), LD("c3"),down.toReversed(),QLineF( down.pointAtPercent(1),up.pointAtPercent(1) ) ) );
    else
        cpath["c3"] = C2DPath(QPainterPath());
    P["c3p"] = cpath["c3"].shape().pointAtPercent(0);

    //QPainterPath decorup=up, decordown=down;
/////////Конечный воротник
    if( D("Ardt") == 0 )
        H("c3_a") = 0;
    if(!( (D("Aldt") != 0)||(( D("stoika_dsgn") == 0 )&&( D("Ardt") != 0 )) ))
        H("c2_a") = 0;
    if( D("Arut") == 0 )
        H("c1_a") = 0;
    if(!( (D("Alut") != 0)||(( D("stoika_dsgn") == 0 ) && ( D("Arut") != 0 ) ) ))
        H("c0_a") = 0;
    QList < QPair<double, QPainterPath> > downsigns,upsigns;
    if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 )||(LD( "is_cut"   ) == 1) )
        if( LD("stoika_krai") == 2 )
            if( (
                        ( D("stoika_dsgn")==0 ) && ( LD("A") > 0 )
                )||
                (
                        ( D("stoika_dsgn")==1 ) && ( LD("AL") > 0 )
                ) )
                    downsigns.append( qMakePair( sign0d,sign0 ) );

    downsigns.append( qMakePair( sign1d,sign1 ) );
    if( simple != true )
        downsigns.append( qMakePair( sign2d,sign2 ) );
    if( simple != true )
        downsigns.append( qMakePair( sign3d,sign3 ) );
    if( simple != true )
        if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 )||(LD( "is_cut"   ) == 1) )
            if( LD("stoika_krai") == 2 )
                if( LD("A") > 0 )
                        downsigns.append( qMakePair( sign4d,sign4 ) );
    double newsign2u;
    QPainterPath oldUP = up;
    if( simple == true )
    {
        up = cGeometry::getsmoothpath( up,LD("c0_a"),LD("c1_a"),upsigns,1 );
        //UpBase = cGeometry::partofpath( UpBase,LD("c0_a"),(UpBase.length()-LD("c1_a")),1 );
    }
    else
    {
        up = cGeometry::getsmoothpath( oldUP,LD("c0_a"),oldUP.length()-sign2u,upsigns,1 );
        newsign2u = up.length();//(sign2u-LD("c0_a"));
        up.connectPath( cGeometry::getsmoothpath( oldUP,sign2u,LD("c1_a"),upsigns,1 ) );
        //UpBase = cGeometry::partofpath( UpBase,LD("c0_a"),(UpBase.length()-LD("c1_a")),1 );
    }
    QPointF p5 = up.pointAtPercent( newsign2u/up.length() ),v_pum,v_pdm;
    QPainterPath oldDOWN = down;
    down = QPainterPath();
    QLineF vorotdrawline=QLineF();
    Unicus::console( "DOWN>>>",down.length() );
    if(downsigns.count() == 0 )
    {
        down = cGeometry::getsmoothpath( oldDOWN,LD("c2_a"),LD("c3_a"),upsigns,1 );
        //DownBase = cGeometry::partofpath( DownBase,LD("c2_a"),(DownBase.length()-LD("c3_a")),1 );
    }
    else
    {
        double start=LD("c2_a");
        double end=LD("c3_a");
        QPainterPath somepath = QPainterPath();

        for(int i = 0;i<downsigns.count();i++)
        {
            if(i==0)
                down = cGeometry::getsmoothpath( oldDOWN,start,oldDOWN.length()-downsigns.at(i).first,upsigns,1 );
            else
                down.connectPath( cGeometry::getsmoothpath( oldDOWN,start,oldDOWN.length()-downsigns.at(i).first,upsigns,1 ) );

            Unicus::console( "downsigns>>>",downsigns.at(i).first );
            if(downsigns.at(i).second.length()>1)
                down.connectPath( cGeometry::GetSign( down.pointAtPercent(1),down.angleAtPercent(1) ) );
            else
            {
                QPointF somepoint = down.pointAtPercent(1);
                down.lineTo( p5 );
                vorotdrawline.setPoints( somepoint,p5 );
                down.lineTo(somepoint);
                v_pum = somepoint;
                v_pdm = p5;
            }
            start = downsigns.at(i).first;
        }
        down.connectPath( cGeometry::getsmoothpath( oldDOWN,start,end,upsigns,1 ) );
        //DownBase = cGeometry::partofpath( DownBase,LD("c2_a"),(DownBase.length()-LD("c3_a")),1 );
    }
    QPointF v_pul,v_pur;
    QPointF v_pdl,v_pdr;
    if(cpath["c0"].shape()!=QPainterPath())
    {
        vorotnik = cpath["c0"].shape().toReversed();
    }
    else
        vorotnik.moveTo( up.pointAtPercent(0) );
    vorotnik.connectPath(up);
    if(cpath["c1"].shape()!=QPainterPath())
    {
        vorotnik.connectPath(cpath["c1"].shape());
    }
    v_pul = vorotnik.pointAtPercent(0);
    v_pur = vorotnik.pointAtPercent(1);
    if((cpath["c3"].shape()!=QPainterPath()))
    {
        vorotnik.lineTo(cpath["c3"].shape().pointAtPercent(1));
        v_pdr = vorotnik.pointAtPercent(1);
        vorotnik.connectPath(cpath["c3"].shape().toReversed());
    }else
    {
        vorotnik.lineTo(down.pointAtPercent(1));
        v_pdr = vorotnik.pointAtPercent(1);
    }

    vorotnik.connectPath(down.toReversed());
    if(cpath["c2"].shape()!=QPainterPath())
    {
        vorotnik.connectPath(cpath["c2"].shape());
    }
    v_pdl = vorotnik.pointAtPercent(1);
    vorotnik.lineTo(vorotnik.pointAtPercent(0));

    if(vorotdrawline!=QLineF())
        focusline = vorotdrawline;
    if( !simple )
    {
        QPointF mypoint = Unicus::rPoint(vorotdrawline.p1(),vorotnik.pointAtPercent(0), (-(270-focusline.angle())) );
        P["v_w_endvar"] = P["Vbase"]+ vorotnik.pointAtPercent(0)-mypoint;//P["V3d"] + (vorotnik.pointAtPercent(0)-vorotdrawline.p1());
    }
    else
        P["v_w_endvar"] = P["Vbase"];

    bool vorotdraw = false;
    if((D("vorot_type") == 1)&&(D("is_vorot")==1))
        vorotdraw = true;
    ///BASE CONSTRUCTION
    UpBase.lineTo( DownBase.pointAtPercent(1) );
    UpBase.connectPath( DownBase.toReversed() );
    UpBase.lineTo( UpBase.pointAtPercent(0) );
    P["Vbasestart"] = UpBase.pointAtPercent(1);
    QPointF botpoint = QPointF(0,999);
    /*{//ОПРЕДЕЛЯЕМ НИЖНЮЮ ТОЧКУ
        QList <QPointF> v_plist;
        v_plist.append( v_pdl );
        v_plist.append( v_pdr );
        v_plist.append( v_pdm );
        v_plist.append( v_pul );
        v_plist.append( v_pur );
        v_plist.append( v_pum );
        while(!v_plist.isEmpty())
        {
            QPointF tmppoint;
            tmppoint = v_plist.takeFirst();
            if(botpoint.y()>tmppoint.x())
                botpoint = tmppoint;
        }
    }
    P["point_v"] = botpoint;
    this->point( Sync( attr( SYNC_NAME, QString( "point_v" ) ),
                      attr( SYNC_TYPE, C2DSync::Point ),
                      attr( SYNC_LIST, MakeList( "point_v" ) ),
                      LM->thick_green() ), true );
*/
    //P["Vbasestart"] = P["Vbasestart"] + ( P["Vbasestart"] - QPointF( P["11'"].x(),P["Gl"].y()+40 ));

    //P["v_w_endvar"] = P["v_w_endvar"] + ( P["v_w_endvar"] - QPointF( P["11'"].x(),P["Gl"].y()+40 ));
    ppath(  Sync( attr( SYNC_NAME,  QString( "Vbase" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "Vbasestart" ) ),
                            LM->bold_solid() ), &UpBase, /*(-(270-focusline.angle()))*/0, 0,
                            vorotdraw );
    /////////////////////

    ppath(  Sync( attr( SYNC_NAME,  QString( "v_w_endvar" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "v_w_endvar" ) ),
                            LM->thick_yellow() ), &vorotnik, (-(270-focusline.angle())), 0,
                            vorotdraw );
   //VOROTDECOR
    //QList < QPair<double, QPainterPath> > decorsigns;
    //decorup = cGeometry::getsmoothpath( decorup,LD("c0_a"),LD("c1_a"),decorsigns,1 );
    //decordown = cGeometry::getsmoothpath( decordown,LD("c2_a"),LD("c3_a"),decorsigns,1 );



    /*tmppathDWN = down1;
    tmppathDWN.connectPath(down2);
    tmppathUP2 = up3;
    tmppathUP2.connectPath(up4);
    tmppathDWN2 = down3;
    tmppathDWN2.connectPath(down4);
*/
    QList<QPainterPath> tmp1,tmp2;
    QPointF tmppoint;
    line2.setPoints( P["V5d"],P["V_add_rd"] );
    line1.setPoints( P["V1d"],P["V_add_ld"] );


    QLineF vert = QLineF( QPointF(0,0),QPointF(0,1) );
    double tmpdbl,tmpdb2=-1,tmpdb3=-1,tmpdb22=-1,tmpdb33=-1,lastangle;
    if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 )||(LD( "is_cut"   ) == 1) )
        if( LD("stoika_krai") == 2 )
            if( (
                        ( D("stoika_dsgn")==0 ) && ( LD("A") > 0 )
                )||
                (
                        ( D("stoika_dsgn")==1 ) && ( LD("AL") > 0 )
                ) )
                tmpdb2 = decorSign1/tmppathDWN.length();
    if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 )||(LD( "is_cut" ) == 1) )
        if( LD("stoika_krai") == 2 )
            if( LD("A") > 0 )
                tmpdb3 = decorSign4/tmppathDWN2.length();
    tmpdb22 = decorSign2/tmppathDWN.length();
    tmpdb33 = decorSign3/tmppathDWN2.length();
    //drawpath("tmppathUP-1",tmppathUP,true,LM->thick_green());
   // drawpath("tmppathDWN-1",tmppathDWN,true,LM->thick_green());
  //  drawpath("tmppathUP-2",tmppathUP2,true,LM->thick_blue());
  //  drawpath("tmppathDWN-2",tmppathDWN2,true,LM->thick_blue());
    if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 ) && ( LD("clasp_location") == 1 ) )// polka
    {

        tmp1 = getdecor(tmppathUP,tmppathDWN,&tmpdb2,&tmpdb22,false);

        //C2DPath( cGeometry::getpathfromlist( tmp1 ) );
        tmp2 = getdecor(tmppathUP2,tmppathDWN2,&tmpdb3,&tmpdb33,true,true);
        tmpdbl = QLineF( tmp1.at(2).pointAtPercent(1),tmp1.at(2).pointAtPercent(0) ).angle()-
                 QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ).angle();
        lastangle = vert.angleTo(QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ));

        line3.setPoints( tmp1.at(0).pointAtPercent(0),tmp1.at(2).pointAtPercent(1) );
        line3.setAngle( line3.angle()-tmpdbl-lastangle );
        tmppoint = P["Vbase"]-(line3.p2()-line3.p1());
        tmppoint = QPointF( tmppoint.x(),tmppoint.y() + QLineF(P["V3d"],P["V3u"]).length() + 70 );
        drawdecor( "decorEND",tmppoint, tmp1, true,-tmpdbl-lastangle,tmpdb2,tmpdb22 );
        drawdecor( "decorEND1",tmppoint+line3.p2()-line3.p1(), tmp2, true, -lastangle,tmpdb3,tmpdb33 );
    }
    else if( ( LD("is_clasp")==1 ) && ( LD("clasp_form") != 0 ) && ( LD("clasp_location") == 0 ) ) // spinka
    {

        tmp1 = getdecor(tmppathUP,tmppathDWN,&tmpdb2,&tmpdb22);
        tmp2 = getdecor(tmppathUP2,tmppathDWN2,&tmpdb3,&tmpdb33,false,true);
        tmpdbl = QLineF( tmp1.at(2).pointAtPercent(1),tmp1.at(2).pointAtPercent(0) ).angle()-
                 QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ).angle();
        lastangle = vert.angleTo(QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ));

        line3.setPoints( tmp1.at(0).pointAtPercent(0),tmp1.at(2).pointAtPercent(1) );
        line3.setAngle( line3.angle()-tmpdbl-lastangle );
        tmppoint = P["Vbase"]-(line3.p2()-line3.p1());
        tmppoint = QPointF( tmppoint.x(),tmppoint.y() + QLineF(P["V3d"],P["V3u"]).length() + 70 );
        drawdecor( "decorEND",tmppoint, tmp1, true,-tmpdbl-lastangle,tmpdb2,tmpdb22 );
        drawdecor( "decorEND1",tmppoint+line3.p2()-line3.p1(), tmp2, true, -lastangle,tmpdb3,tmpdb33 );
    }
    else if( ( LD("is_cut")==1 ) && ( LD("cut_location") == 1 ) ) // polka
    {

        tmp1 = getdecor(tmppathUP,tmppathDWN,&tmpdb2,&tmpdb22,false);
        tmp2 = getdecor(tmppathUP2,tmppathDWN2,&tmpdb3,&tmpdb33,true,true);
        tmpdbl = QLineF( tmp1.at(2).pointAtPercent(1),tmp1.at(2).pointAtPercent(0) ).angle()-
                         QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ).angle();
        lastangle = vert.angleTo(QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ));

        line3.setPoints( tmp1.at(0).pointAtPercent(0),tmp1.at(2).pointAtPercent(1) );
        line3.setAngle( line3.angle()-tmpdbl-lastangle );
        tmppoint = P["Vbase"]-(line3.p2()-line3.p1());
        tmppoint = QPointF( tmppoint.x(),tmppoint.y() + QLineF(P["V3d"],P["V3u"]).length() + 70 );
        drawdecor( "decorEND",tmppoint, tmp1, true,-tmpdbl-lastangle,tmpdb2,tmpdb22 );
        drawdecor( "decorEND1",tmppoint+line3.p2()-line3.p1(), tmp2, true, -lastangle,tmpdb3,tmpdb33 );
    }
    else if( ( LD("is_cut")==1 ) && ( LD("cut_location") == 0 ) ) // spinka
    {

        tmp1 = getdecor(tmppathUP,tmppathDWN,&tmpdb2,&tmpdb22);
        tmp2 = getdecor(tmppathUP2,tmppathDWN2,&tmpdb3,&tmpdb33,false,true);
        tmpdbl = QLineF( tmp1.at(2).pointAtPercent(1),tmp1.at(2).pointAtPercent(0) ).angle()-
                         QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ).angle();
        lastangle = vert.angleTo(QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ));
        line3.setPoints( tmp1.at(0).pointAtPercent(0),tmp1.at(2).pointAtPercent(1) );
        line3.setAngle( line3.angle()-tmpdbl-lastangle );
        tmppoint = P["Vbase"]-(line3.p2()-line3.p1());
        tmppoint = QPointF( tmppoint.x(),tmppoint.y() + QLineF(P["V3d"],P["V3u"]).length() + 70 );
        drawdecor( "decorEND",tmppoint, tmp1, true,-tmpdbl-lastangle,tmpdb2,tmpdb22 );
        drawdecor( "decorEND1",tmppoint+line3.p2()-line3.p1(), tmp2, true, -lastangle,tmpdb3,tmpdb33 );
    }else
    {

        //Unicus::console( "YYYYYYYYYYYYYY", LD("is_cut"));
        tmp1 = getdecor(tmppathUP,tmppathDWN,&tmpdb2,&tmpdb22);
        tmp2 = getdecor(tmppathUP2,tmppathDWN2,&tmpdb3,&tmpdb33,true,true);
        tmpdbl = QLineF( tmp1.at(2).pointAtPercent(1),tmp1.at(2).pointAtPercent(0) ).angle()-
                         QLineF( tmp2.at(0).pointAtPercent(0),tmp2.at(0).pointAtPercent(1) ).angle();

        drawdecor( "decorEND",P["Vbase"], tmp1 , false,-tmpdbl,tmpdb2 );

        drawdecor( "decorEND1",P["Vbase"], tmp2, false, 0,tmpdb3 );
    }

    //Unicus::console( "tmppathUP",tmppathUP.length() );
    //Unicus::console( "tmppathUP2",tmppathUP2.length() );
    //Unicus::console( "tmppathDWN",tmppathDWN.length() );
    //Unicus::console( "tmppathDWN2",tmppathDWN2.length() );
    //signs
    if( D("stoika_dsgn")==0 )
        H("AL") = LD("A");

    bool sign_less=false;

    //signP( "sign-vorot_1",P["V1d"],-90,false,sign_add );
    //signP( "sign-vorot_2",P["V5d"],-90,false,sign_add );
    QPointF sig3,sig4;
    if((D("is_vorot") == 1)&&(D("vorot_type") == 1))
        if( LD("stoika_krai") == 1 )
        {
            sign_less = true;
        }


    clasp_sign3_path = clasp_sign3_path.toReversed();
    tmpdbl = (clasp_sign3_start+fabs(LD("A")))/clasp_sign3_path.length();
    if(tmpdbl>1)
        tmpdbl = 1;
    sig3 = clasp_sign3_path.pointAtPercent( tmpdbl );
    clasp_sign3_start = clasp_sign3_path.angleAtPercent( tmpdbl );

    tmpdbl = (clasp_sign4_start+fabs(LD("AL")))/clasp_sign4_path.length();
    if(tmpdbl>1)
        tmpdbl = 1;
    sig4 = clasp_sign4_path.pointAtPercent( tmpdbl );
    clasp_sign4_start = clasp_sign4_path.angleAtPercent( tmpdbl );
    signP( "sign-vorot_3",sig3,clasp_sign3_start-90,false,sign_less );
    signP( "sign-vorot_4",sig4,clasp_sign4_start+90,false,sign_less );
    //Unicus::console( "ANGLE3", clasp_sign3_start );


}
void C2DDress::DrawCollar( bool is_collar )
{
    /****************DEBUG*****************/
    /*QPainterPath debugpath;
    debugpath.moveTo( -10,-10 );
    debugpath.cubicTo( -30,-10,-50,-50,-100,-50 );
    C2DPath debugc2d = C2DPath( debugpath );
    P["debug1"]=debugpath.pointAtPercent(0);
    QPainterPath debugpath2 = debugc2d.takepartofpath(0.2,0.5,1);
    P["debug2"]=debugpath2.pointAtPercent(0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "debug1" ) ),
                  attr( SYNC_TYPE, C2DSync::Ppath ),
                  attr( SYNC_LIST, MakeList( "debug1" ) ),
                  LM->thick_yellow() ), &debugpath, 0, 0,
                                  true );
    ppath(  Sync( attr( SYNC_NAME,  QString( "debug2" ) ),
                  attr( SYNC_TYPE, C2DSync::Ppath ),
                  attr( SYNC_LIST, MakeList( "debug2" ) ),
                  LM->thick_red() ), &debugpath2, 0, 0,
                                  true );
    /**************************************/
    if( D("vorot_type") == 0 )
        is_collar = false;
    bool l_add=false,r_add=false;
    if( LD("vorot_l_add") != 0 )
        l_add = true;
    if( LD("vorot_r_add") != 0 )
        r_add = true;
    /*line( Sync( attr( SYNC_NAME,  QString( "V_add_ld-V_add_lu" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_ld", "V_add_lu" ) ),
                LM->bold_solid() ),
          l_add && is_collar && vorot_add );
    line( Sync( attr( SYNC_NAME,  QString( "V_add_ld-V1d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_ld", "V1d" ) ),
                LM->bold_solid() ),
          l_add && is_collar && vorot_add );
    line( Sync( attr( SYNC_NAME,  QString( "V_add_lu-V1u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_lu", "V1u" ) ),
                LM->bold_solid() ),
          l_add && is_collar && vorot_add );

    line( Sync( attr( SYNC_NAME,  QString( "V_add_rd-V_add_ru" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_rd", "V_add_ru" ) ),
                LM->thick_solid() ),
          r_add && is_collar && vorot_add );
    line( Sync( attr( SYNC_NAME,  QString( "V_add_rd-V5d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_rd", "V5d" ) ),
                LM->bold_solid() ),
          r_add && is_collar && vorot_add );
    line( Sync( attr( SYNC_NAME,  QString( "V_add_ru-V5u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V_add_ru", "V5u" ) ),
                LM->thick_solid() ),
          r_add && is_collar && vorot_add );
    ///drawing
    line( Sync( attr( SYNC_NAME,  QString( "V1d-V1u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V1d", "V1u" ) ),
                LM->bold_solid() ),
          true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V1d-V2d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V1d", "V2d" ) ),
                LM->bold_solid() ),
          true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V2d-V2u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V2d", "V2u" ) ),
                LM->bold_solid() ),
          true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V2u-V1u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V2u", "V1u" ) ),
                LM->bold_solid() ),
          true && is_collar);

    line( Sync( attr( SYNC_NAME,  QString( "V3u-V2d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V3d", "V2d" ) ),
                LM->bold_solid() ),
          true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V3u-V2u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V3u", "V2u" ) ),
                LM->bold_solid() ),
         true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V3u-V3d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V3u", "V3d" ) ),
                LM->bold_solid() ),
          true && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V4d-V3d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V4d", "V3d" ) ),
                LM->bold_solid() ),
         !simple && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V4u-V3u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V4u", "V3u" ) ),
                LM->bold_solid() ),
          !simple && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V4u-V4d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V4u", "V4d" ) ),
                 LM->bold_solid() ),
          !simple && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V5u-V4d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V5d", "V4d" ) ),
                LM->bold_solid() ),
          !simple && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V5u-V4u" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V5u", "V4u" ) ),
                LM->bold_solid() ),
          !simple && is_collar);
    line( Sync( attr( SYNC_NAME,  QString( "V5u-V5d" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "V5u", "V5d" ) ),
                LM->bold_solid() ),
          !simple && is_collar);*/


    sign( Sync( attr( SYNC_NAME, QString( "S4" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "vorot_sign" ) ),
                LM->thick_dashed(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, 90 ) ),
          true && is_collar);

    sign( Sync( attr( SYNC_NAME, QString( "S4d" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "vorot_sign_dialog" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, 90 ) ),
          true && is_collar);
    ///////////Уголки

}

QPainterPath C2DDress::coners( QPointF p, double a, double b, double cl, double ct, double a1, double a2, double a3, int N, QPainterPath linepath, QLineF lineH )
{
    QPainterPath tmp=QPainterPath();
    ifg++;
    QLineF line1,line2;
    QPointF p0, p1, p2;
    if( (linepath.isEmpty()) || ( linepath.length() == 0 ) )
        return tmp;
    if( a > linepath.length() )
        a = linepath.length();
    if( a < 0 )
        a = -a;
    p0 = linepath.pointAtPercent( a/linepath.length() );
    b=-b;
    p2 = lineH.pointAt( b/lineH.length() );//p + QPointF( 0 ,b );

    if( ( a == 0 ) && ( b == 0 ) )
    {
        //tmp.moveTo(p);
        return tmp;
    }

    if( N != 0 )
    {
        line1.setPoints(p0,p2);
        if(cl>(line1.length()*0.5f) )
            cl = line1.length()*0.5f-0.1;
        else if(cl< -(line1.length()*0.5f) )
            cl = -1 * line1.length()*0.5f+0.1;
        line1.setLength( (line1.length()/2) + cl );
        if ( ct != 0 )
        {
            line2.setPoints(line1.p2(),line1.p1());
            line2.setAngle( line1.angle()-90 );
            line2.setLength(ct);
            line1 = line2;
        }
        p1 = line1.p2();

        line1.setPoints(p0,p1);
        line1.setAngle(QLineF(p0,p2).angle()+a1);
        line2.setPoints(p1,p0);
        line2.setAngle(QLineF(p2,p0).angle()+a2);
        tmp.moveTo(p0);
        tmp.cubicTo(line1.pointAt(0.4), line2.pointAt(0.4), p1);
        line2.setAngle(line2.angle()+180);
        line1.setPoints(p2,p1);
        line1.setAngle(QLineF(p2,p0).angle()-a3);
        tmp.cubicTo(line2.pointAt(0.4), line1.pointAt(0.4), p2 );

        P["po0"+QString::number(ifg)] = p0;
        P["po2"+QString::number(ifg)] = p2;
        P["po1"+QString::number(ifg)] = p1;
    }else
    {
        line1.setPoints(p0, p2 );
        line1.setAngle(QLineF(p0,p2).angle()+a1);
        line2.setPoints(p2, p0 );
        line2.setAngle(QLineF(p2,p0).angle()-a3);
        tmp.moveTo(line1.p1());
        tmp.cubicTo(line1.pointAt(0.4), line2.pointAt(0.4), line2.p1());

        P["po0"+QString::number(ifg)] = line1.p1();

        P["po1"+QString::number(ifg)] = line2.p1();
    }
    //line( Sync( attr( SYNC_NAME,  QString( "po1a"+QString::number(ifg) ) ),
    //            attr( SYNC_TYPE, C2DSync::Line ),
    //            attr( SYNC_LIST, MakeList( "po0"+QString::number(ifg), "po1"+QString::number(ifg) ) ),
    //            LM->thick_solid() ),
    //      true );
    //line( Sync( attr( SYNC_NAME,  QString( "po3a"+QString::number(ifg) ) ),
    //            attr( SYNC_TYPE, C2DSync::Line ),
    //            attr( SYNC_LIST, MakeList( "po1"+QString::number(ifg), "po2"+QString::number(ifg) ) ),
    //            LM->thick_solid() ),
    //      true );
    //line( Sync( attr( SYNC_NAME,  QString( "po0a"+QString::number(ifg) ) ),
    //            attr( SYNC_TYPE, C2DSync::Line ),
    //            attr( SYNC_LIST, MakeList( "po0"+QString::number(ifg), "po2"+QString::number(ifg) ) ),
    //            LM->thick_solid() ),
    //      true );
    return tmp;
}
///////path/////
QLineF C2DDress::resize_collar2( QPainterPath lineUP, QPainterPath lineDWN, int N,
                                double deltau, double deltad, QLineF lineSTRT )
{
    N=N+1;
    if( (lineUP.isEmpty()) || (lineDWN.isEmpty()) || ( N < 2 )
        || (lineSTRT.isNull()))
    {
        Unicus::console( "Bug dedected (resize_collar)", N );
        return QLineF();
    }
    ///разбиение на N частей
    QLineF line1,line2;
    double d_angle;
    C2DPath lup,ldwn;
    lup = C2DPath( lineUP );
    ldwn = C2DPath( lineDWN );

    if((deltau==0)&&(deltad==0))
    {
        Unicus::console( "Bug dedected (DELTA)", deltau );
        line1.setPoints( lineDWN.pointAtPercent(0),lineUP.pointAtPercent(0) );
        d_angle = lineSTRT.angle() - line1.angle();
        lup = C2DPath( lineUP,-d_angle );
        lineUP = lup.myshape( lineSTRT.p2() );
        //d_angle = (lineSTRT.angle() + 90) - lineDWN.angleAtPercent(0);
        ldwn = C2DPath( lineDWN,-d_angle );
        lineDWN = ldwn.myshape( lineSTRT.p1() );
        wide_collar_up = lineUP;
        wide_collar_down = lineDWN;
        return QLineF(lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1));
    }
    QList < QPainterPath > list_up = lup.splitpath(N,3);
    QList < QPainterPath > list_dwn = ldwn.splitpath(N,3);

    wide_collar_up = QPainterPath();
    wide_collar_down = QPainterPath();
/******************************/
    wide_collar_up.moveTo( lineSTRT.p2() );
    wide_collar_down.moveTo( lineSTRT.p1() );
    double d_deltau = deltau/(N);
    double d_deltad = deltad/(N);
    double angle;
    double angled;
    QPointF pd,pu,oldpu,oldpd;
        for( int i = 0; i<list_up.count(); i++ )
        {
            line1.setPoints( list_dwn.at(i).pointAtPercent(0),list_up.at(i).pointAtPercent(0) );
            d_angle = lineSTRT.angle() - line1.angle();
            lup = C2DPath( list_up.at(i),-d_angle );
            lineUP = lup.myshape( lineSTRT.p2() );
            ldwn = C2DPath( list_dwn.at(i),-d_angle );
            lineDWN = ldwn.myshape( lineSTRT.p1() );
            pd = lineDWN.pointAtPercent(1);
            pu = lineUP.pointAtPercent(1);
            //if( (i+1)!=list_up.count() )
            {
                if(d_deltau>0)
                    wide_collar_up.lineTo( pu );
                if(d_deltad>0)
                    wide_collar_down.lineTo( pd );
                //if(d_deltau>0)
                //{
                    oldpu = pu;
                    oldpd = pd;
                    angle = 2*180/M_PI*asin( d_deltau/(2*QLineF( pu,pd ).length()) );
                    pu = Unicus::rPoint( pu,pd,-angle );
                    if((d_deltau<0)&&(angle != 0)&&(angle != 180))
                    {
                        line1.setPoints( lineUP.pointAtPercent(0),lineUP.pointAtPercent(1) );
                        //line1.intersect(QLineF(pu,pd),&pu);
                    }

                    angled = 2*180/M_PI*asin( d_deltad/(2*QLineF( pu,pd ).length()) );
                    pd = Unicus::rPoint( pd,pu,angled );
                    if((d_deltad<0)&&(angled != 0)&&(angled != 180))
                    {
                        line1.setPoints( lineDWN.pointAtPercent(0),lineDWN.pointAtPercent(1) );
                        //line1.intersect(QLineF(pu,pd),&pd);
                    }
                //}else
                //{
                 //   if( -d_deltad>=lineDWN.length() )
                 //       d_deltad = - lineDWN.length()+0.0001;
                 //   pd = lineDWN.pointAtPercent( (lineDWN.length()+d_deltad)/lineDWN.length() );
                //}
                lineSTRT.setPoints(pd,pu);
            }
            wide_collar_up.lineTo( pu );
            wide_collar_down.lineTo( pd );
        }

    //wide_collar_up.lineTo( lineUP.pointAtPercent(1) );
    //wide_collar_down.lineTo( lineDWN.pointAtPercent(1) );
    //return QLineF( lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1) );
        return QLineF( pd,pu );
}
///^^^^^
QLineF C2DDress::resize_collar( QPainterPath lineUP, QPainterPath lineDWN, int N,
                                double deltau, double deltad, QLineF lineSTRT )
{
    //Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",deltad);
    //Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",deltau);
    //if((deltau>=0)&&(deltad>=0))
    //    return resize_coll( lineUP,lineDWN,N,deltau,deltad,lineSTRT );
    if(( deltau<0 )&&( lineUP.length()<-deltau ))
        deltau = -lineUP.length();
    if(( deltad<0 )&&( lineDWN.length()<-deltad ))
        deltad = -lineDWN.length();

    Unicus::console( "LINEUP-->>>>>>>",lineUP.length() );
    if(deltad<0)
        deltad=deltad+0.0001;
    if(deltau<0)
        deltau=deltau+0.0001;
    N=N+1;
    if( (lineUP.isEmpty()) || (lineDWN.isEmpty()) || ( N < 2 )
        || (lineSTRT.isNull()))
    {
        Unicus::console( "Bug dedected (resize_collar)", N );
        return QLineF();
    }
    ///разбиение на N частей
    QLineF line1,line2;
    double d_angle;
    C2DPath lup,ldwn;
    lup = C2DPath( lineUP );
    ldwn = C2DPath( lineDWN );

    if((deltau==0)&&(deltad==0))
    {
        Unicus::console( "Bug dedected (DELTA)", deltau );
        line1.setPoints( lineDWN.pointAtPercent(0),lineUP.pointAtPercent(0) );
        d_angle = lineSTRT.angle() - line1.angle();
        lup = C2DPath( lineUP,-d_angle );
        lineUP = lup.myshape( lineSTRT.p2() );
        //d_angle = (lineSTRT.angle() + 90) - lineDWN.angleAtPercent(0);
        ldwn = C2DPath( lineDWN,-d_angle );
        lineDWN = ldwn.myshape( lineSTRT.p1() );
        wide_collar_up = lineUP;
        wide_collar_down = lineDWN;
        return QLineF(lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1));
    }
    QList < QPainterPath > list_up = lup.splitpath(N,1);
    QList < QPainterPath > list_dwn = ldwn.splitpath(N,1);
    Unicus::console( "list_up.count()!!!!!!!!!",list_up.count() );
    Unicus::console( "list_dwn.count()!!!!!!!!!",list_dwn.count() );
    wide_collar_up = QPainterPath();
    wide_collar_down = QPainterPath();
/******************************/
    wide_collar_up.moveTo( lineSTRT.p2() );
    wide_collar_down.moveTo( lineSTRT.p1() );
    double d_deltau = deltau/(N-1);
    if(d_deltau<0)
        d_deltau = deltau/(N);
    double d_deltad = deltad/(N-1);
    if(d_deltad<0)
        d_deltad = deltad/(N);
    Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",d_deltad);
    Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",d_deltau);
    double angle,tmpstart,tmpend,lenU,lenD;
    double angled;
    QPointF pd,pu,oldpu,oldpd,p1d,p2u;
        for( int i = 0; i<list_up.count(); i++ )
        {
            //Unicus::console( "DWN_LINE!!!!!LENGTH at " ,list_dwn.at(i).length() );
            //Unicus::console( "UP_LINE !!!!!LENGTH at " ,list_up.at(i).length() );

            p1d=list_dwn.at(i).pointAtPercent(0);

            p2u=list_up.at(i).pointAtPercent(0);
            if( (d_deltad<0) )
            {
                Unicus::console("d_deltad------------------------------------------>",d_deltad);
                Unicus::console("d_length------------------------------------------>",list_dwn.at(i).length());
                double tmp_d_deltad = -d_deltad/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltad = -d_deltad;
                ldwn = C2DPath( list_dwn.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltad/list_dwn.at(i).length();

                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                {
                    tmpend = ((list_dwn.at(i).length()-tmp_d_deltad)/list_dwn.at(i).length())-tmpstart;
                }
                list_dwn.replace( i, ldwn.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("d_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("d_tmpend------------------------------------------>",tmpend);

            }
            //Unicus::console("d_deltau------------------------------------------>",d_deltau);
            if( (d_deltau<0) )
            {
                Unicus::console("u_deltad------------------------------------------>",d_deltau);
                Unicus::console("u_length------------------------------------------>",list_up.at(i).length());
                double tmp_d_deltau = -d_deltau/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltau = -d_deltau;
                lup = C2DPath( list_up.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltau/list_up.at(i).length();
                //Unicus::console("tmpstart------------------------------------------>",tmpstart);
                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                    tmpend = ((list_up.at(i).length()-tmp_d_deltau)/list_up.at(i).length())-tmpstart;
                list_up.replace(i, lup.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("u_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("u_tmpend------------------------------------------>",tmpend);
            }

            line1.setPoints( list_dwn.at(i).pointAtPercent(0),list_up.at(i).pointAtPercent(0) );
            d_angle = lineSTRT.angle() - line1.angle();
            lup = C2DPath( list_up.at(i),-d_angle );
            double tmplen1=0;

            if((d_deltau<0)&&(d_deltad<0))
            {
                line2.setPoints(lineSTRT.p2(),lineSTRT.p1());
                double tmptmpdouble =   (QLineF(list_dwn.at(i).pointAtPercent(0),
                                           list_up.at(i).pointAtPercent(0)).length()
                        -lineSTRT.length())*0.5f;
                line2.setLength( line2.length() + tmptmpdouble );
                line2.setPoints( line2.p2(),line2.p1() );
                line2.setLength( line2.length() + tmptmpdouble );
            }else if(d_deltau<0)
            {
                line2 = lineSTRT;
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
            }else if(d_deltad<0)
            {
                line2.setPoints( lineSTRT.p2(),lineSTRT.p1() );
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
                line2.setPoints( line2.p2(),line2.p1() );
            }

            if(d_deltau>=0)
                lineUP = lup.myshape( lineSTRT.p2() );
            else
            {
                //tmplen1 = 1;
                //        lineSTRT.length();

                lineUP = lup.myshape( line2.p2() );
            }
            ldwn = C2DPath( list_dwn.at(i),-d_angle );
            if(d_deltad>=0)
                lineDWN = ldwn.myshape( lineSTRT.p1() );
            else
            {

                    lineDWN = ldwn.myshape( line2.p1() );

            }
            pd = lineDWN.pointAtPercent(1);
            pu = lineUP.pointAtPercent(1);
            if( (i+1)!=list_up.count() )
            {
                if(d_deltau>0)
                {
                    wide_collar_up.connectPath( lineUP );
                    oldpu = pu;
                    oldpd = pd;
                    angle = 2*180/M_PI*asin( d_deltau/(2*QLineF( pu,pd ).length()) );
                    pu = Unicus::rPoint( pu,pd,-angle );
                    line1.setPoints( oldpd,oldpu );
                    wide_collar_up.moveTo( pu );
                    //wide_collar_up.arcTo( oldpd.x()-line1.length(),
                    //                      oldpd.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      angle);
                }
                else if( d_deltau<0 )
                {
                    wide_collar_up.connectPath( lineUP );
                }else
                {
                    wide_collar_up.connectPath( lineUP );
                }

                if(d_deltad>0)
                {
                    wide_collar_down.connectPath( lineDWN );
                    angled = 2*180/M_PI*asin( d_deltad/(2*QLineF( pu,pd ).length()) );
                    line1.setPoints( pu,pd );
                    //wide_collar_down.arcTo( pu.x()-line1.length(),
                    //                      pu.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      -angled);
                    pd = Unicus::rPoint( pd,pu,angled );
                    wide_collar_down.moveTo(pd);
                }
                else if( d_deltad < 0 )
                {
                    wide_collar_down.connectPath( lineDWN );
                }else
                {
                    wide_collar_down.connectPath( lineDWN );
                }

                lineSTRT.setPoints(pd,pu);
            }else
            {
                wide_collar_up.connectPath( lineUP );
                wide_collar_down.connectPath( lineDWN );
            }
        }
    //return QLineF( lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1) );
    return QLineF( pd,pu );
}
QLineF C2DDress::resize_collar_right( QPainterPath lineUP, QPainterPath lineDWN, int N,
                                double deltau, double deltad, QLineF lineSTRT )
{
    lineUP = lineUP.toReversed();
    lineDWN = lineDWN.toReversed();
    QLineF lineEND = lineSTRT;
    //Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",deltad);
    //Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",deltau);
    //if((deltau>=0)&&(deltad>=0))
    //    return resize_coll( lineUP,lineDWN,N,deltau,deltad,lineSTRT );
    if(( deltau<0 )&&( lineUP.length()<-deltau ))
        deltau = -lineUP.length();
    if(( deltad<0 )&&( lineDWN.length()<-deltad ))
        deltad = -lineDWN.length();

    Unicus::console( "LINEUP-->>>>>>>",lineUP.length() );
    if(deltad<0)
        deltad=deltad+0.0001;
    if(deltau<0)
        deltau=deltau+0.0001;
    N=N+1;
    if( (lineUP.isEmpty()) || (lineDWN.isEmpty()) || ( N < 2 )
        || (lineSTRT.isNull()))
    {
        Unicus::console( "Bug dedected (resize_collar)", N );
        return QLineF();
    }
    lineSTRT = QLineF( lineDWN.pointAtPercent(0),lineUP.pointAtPercent(0) );
    ///разбиение на N частей
    QLineF line1,line2;
    double d_angle;
    C2DPath lup,ldwn;
    lup = C2DPath( lineUP );
    ldwn = C2DPath( lineDWN );

    if((deltau==0)&&(deltad==0))
    {
        lineUP = lineUP.toReversed();
        lineDWN = lineDWN.toReversed();
        lineSTRT = lineEND;
        Unicus::console( "Bug dedected RIGHT(DELTA)", deltau );
        line1.setPoints( lineDWN.pointAtPercent(0),lineUP.pointAtPercent(0) );
        d_angle = lineSTRT.angle() - line1.angle();
        lup = C2DPath( lineUP,-d_angle );
        lineUP = lup.myshape( lineSTRT.p2() );
        //d_angle = (lineSTRT.angle() + 90) - lineDWN.angleAtPercent(0);
        ldwn = C2DPath( lineDWN,-d_angle );
        lineDWN = ldwn.myshape( lineSTRT.p1() );
        wide_collar_up = lineUP;
        wide_collar_down = lineDWN;
        return QLineF(lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1));
    }
    QList < QPainterPath > list_up = lup.splitpath(N,1);
    QList < QPainterPath > list_dwn = ldwn.splitpath(N,1);
    Unicus::console( "list_up.count()!!!!!!!!!",list_up.count() );
    Unicus::console( "list_dwn.count()!!!!!!!!!",list_dwn.count() );
    wide_collar_up = QPainterPath();
    wide_collar_down = QPainterPath();
/******************************/
    wide_collar_up.moveTo( lineSTRT.p2() );
    wide_collar_down.moveTo( lineSTRT.p1() );
    double d_deltau = deltau/(N-1);
    if(d_deltau<0)
        d_deltau = deltau/(N);
    double d_deltad = deltad/(N-1);
    if(d_deltad<0)
        d_deltad = deltad/(N);
    Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",d_deltad);
    Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",d_deltau);
    double angle,tmpstart,tmpend,lenU,lenD;
    double angled;
    QPointF pd,pu,oldpu,oldpd,p1d,p2u;
        for( int i = 0; i<list_up.count(); i++ )
        {
            //Unicus::console( "DWN_LINE!!!!!LENGTH at " ,list_dwn.at(i).length() );
            //Unicus::console( "UP_LINE !!!!!LENGTH at " ,list_up.at(i).length() );

            p1d=list_dwn.at(i).pointAtPercent(0);

            p2u=list_up.at(i).pointAtPercent(0);
            if( (d_deltad<0) )
            {
                Unicus::console("d_deltad------------------------------------------>",d_deltad);
                Unicus::console("d_length------------------------------------------>",list_dwn.at(i).length());
                double tmp_d_deltad = -d_deltad/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltad = -d_deltad;
                ldwn = C2DPath( list_dwn.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltad/list_dwn.at(i).length();

                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                {
                    tmpend = ((list_dwn.at(i).length()-tmp_d_deltad)/list_dwn.at(i).length())-tmpstart;
                }
                list_dwn.replace( i, ldwn.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("d_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("d_tmpend------------------------------------------>",tmpend);

            }
            //Unicus::console("d_deltau------------------------------------------>",d_deltau);
            if( (d_deltau<0) )
            {
                Unicus::console("u_deltad------------------------------------------>",d_deltau);
                Unicus::console("u_length------------------------------------------>",list_up.at(i).length());
                double tmp_d_deltau = -d_deltau/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltau = -d_deltau;
                lup = C2DPath( list_up.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltau/list_up.at(i).length();
                //Unicus::console("tmpstart------------------------------------------>",tmpstart);
                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                    tmpend = ((list_up.at(i).length()-tmp_d_deltau)/list_up.at(i).length())-tmpstart;
                list_up.replace(i, lup.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("u_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("u_tmpend------------------------------------------>",tmpend);
            }

            line1.setPoints( list_dwn.at(i).pointAtPercent(0),list_up.at(i).pointAtPercent(0) );
            d_angle = lineSTRT.angle() - line1.angle();
            lup = C2DPath( list_up.at(i),-d_angle );
            double tmplen1=0;

            if((d_deltau<0)&&(d_deltad<0))
            {
                line2.setPoints(lineSTRT.p2(),lineSTRT.p1());
                double tmptmpdouble =   (QLineF(list_dwn.at(i).pointAtPercent(0),
                                           list_up.at(i).pointAtPercent(0)).length()
                        -lineSTRT.length())*0.5f;
                line2.setLength( line2.length() + tmptmpdouble );
                line2.setPoints( line2.p2(),line2.p1() );
                line2.setLength( line2.length() + tmptmpdouble );
            }else if(d_deltau<0)
            {
                line2 = lineSTRT;
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
            }else if(d_deltad<0)
            {
                line2.setPoints( lineSTRT.p2(),lineSTRT.p1() );
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
                line2.setPoints( line2.p2(),line2.p1() );
            }

            if(d_deltau>=0)
                lineUP = lup.myshape( lineSTRT.p2() );
            else
            {
                //tmplen1 = 1;
                //        lineSTRT.length();

                lineUP = lup.myshape( line2.p2() );
            }
            ldwn = C2DPath( list_dwn.at(i),-d_angle );
            if(d_deltad>=0)
                lineDWN = ldwn.myshape( lineSTRT.p1() );
            else
            {

                    lineDWN = ldwn.myshape( line2.p1() );

            }
            pd = lineDWN.pointAtPercent(1);
            pu = lineUP.pointAtPercent(1);
            if( (i+1)!=list_up.count() )
            {
                if(d_deltau>0)
                {
                    wide_collar_up.connectPath( lineUP );
                    oldpu = pu;
                    oldpd = pd;
                    angle = 2*180/M_PI*asin( d_deltau/(2*QLineF( pu,pd ).length()) );
                    pu = Unicus::rPoint( pu,pd,angle );
                    line1.setPoints( oldpd,oldpu );
                    wide_collar_up.moveTo( pu );
                    //wide_collar_up.arcTo( oldpd.x()-line1.length(),
                    //                      oldpd.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      angle);
                }
                else if( d_deltau<0 )
                {
                    wide_collar_up.connectPath( lineUP );
                }else
                {
                    wide_collar_up.connectPath( lineUP );
                }

                if(d_deltad>0)
                {
                    wide_collar_down.connectPath( lineDWN );
                    angled = 2*180/M_PI*asin( d_deltad/(2*QLineF( pu,pd ).length()) );
                    line1.setPoints( pu,pd );
                    //wide_collar_down.arcTo( pu.x()-line1.length(),
                    //                      pu.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      -angled);
                    pd = Unicus::rPoint( pd,pu,-angled );
                    wide_collar_down.moveTo(pd);
                }
                else if( d_deltad < 0 )
                {
                    wide_collar_down.connectPath( lineDWN );
                }else
                {
                    wide_collar_down.connectPath( lineDWN );
                }

                lineSTRT.setPoints(pd,pu);
            }else
            {
                wide_collar_up.connectPath( lineUP );
                wide_collar_down.connectPath( lineDWN );
            }
        }
        wide_collar_up = wide_collar_up.toReversed();
        wide_collar_down = wide_collar_down.toReversed();
        line1.setPoints( wide_collar_down.pointAtPercent(0),wide_collar_up.pointAtPercent(0) );
        C2DPath c2dp = C2DPath( wide_collar_up, -(lineEND.angle()-line1.angle()) );
        wide_collar_up = c2dp.myshape( lineEND.p2() );
        c2dp = C2DPath( wide_collar_down, -(lineEND.angle()-line1.angle()) );
        wide_collar_down = c2dp.myshape( lineEND.p1() );

    //return QLineF( lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1) );
    return QLineF( wide_collar_down.pointAtPercent(1),wide_collar_up.pointAtPercent(1) );
}
QLineF C2DDress::resize_collar_botfirst( QPainterPath lineUP, QPainterPath lineDWN, int N,
                                double deltau, double deltad, QLineF lineSTRT )
{
    //Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",deltad);
    //Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",deltau);
    //if((deltau>=0)&&(deltad>=0))
    //    return resize_coll( lineUP,lineDWN,N,deltau,deltad,lineSTRT );
    if(( deltau<0 )&&( lineUP.length()<-deltau ))
        deltau = -lineUP.length();
    if(( deltad<0 )&&( lineDWN.length()<-deltad ))
        deltad = -lineDWN.length();

    Unicus::console( "LINEUP-->>>>>>>",lineUP.length() );
    if(deltad<0)
        deltad=deltad+0.0001;
    if(deltau<0)
        deltau=deltau+0.0001;
    N=N+1;
    if( (lineUP.isEmpty()) || (lineDWN.isEmpty()) || ( N < 2 )
        || (lineSTRT.isNull()))
    {
        Unicus::console( "Bug dedected (resize_collar)", N );
        return QLineF();
    }
    ///разбиение на N частей
    QLineF line1,line2;
    double d_angle;
    C2DPath lup,ldwn;
    lup = C2DPath( lineUP );
    ldwn = C2DPath( lineDWN );

    if((deltau==0)&&(deltad==0))
    {
        Unicus::console( "Bug dedected (DELTA)", deltau );
        line1.setPoints( lineDWN.pointAtPercent(0),lineUP.pointAtPercent(0) );
        d_angle = lineSTRT.angle() - line1.angle();
        lup = C2DPath( lineUP,-d_angle );
        lineUP = lup.myshape( lineSTRT.p2() );
        //d_angle = (lineSTRT.angle() + 90) - lineDWN.angleAtPercent(0);
        ldwn = C2DPath( lineDWN,-d_angle );
        lineDWN = ldwn.myshape( lineSTRT.p1() );
        wide_collar_up = lineUP;
        wide_collar_down = lineDWN;
        return QLineF(lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1));
    }
    QList < QPainterPath > list_up = lup.splitpath(N,1);
    QList < QPainterPath > list_dwn = ldwn.splitpath(N,1);
    Unicus::console( "list_up.count()!!!!!!!!!",list_up.count() );
    Unicus::console( "list_dwn.count()!!!!!!!!!",list_dwn.count() );
    wide_collar_up = QPainterPath();
    wide_collar_down = QPainterPath();
/******************************/
    wide_collar_up.moveTo( lineSTRT.p2() );
    wide_collar_down.moveTo( lineSTRT.p1() );
    double d_deltau = deltau/(N-1);
    if(d_deltau<0)
        d_deltau = deltau/(N);
    double d_deltad = deltad/(N-1);
    if(d_deltad<0)
        d_deltad = deltad/(N);
    Unicus::console("d_deltad>>>>>>>>>>>>>>>>>>>",d_deltad);
    Unicus::console("d_deltau>>>>>>>>>>>>>>>>>>>",d_deltau);
    double angle,tmpstart,tmpend,lenU,lenD;
    double angled;
    QPointF pd,pu,oldpu,oldpd,p1d,p2u;
        for( int i = 0; i<list_up.count(); i++ )
        {
            //Unicus::console( "DWN_LINE!!!!!LENGTH at " ,list_dwn.at(i).length() );
            //Unicus::console( "UP_LINE !!!!!LENGTH at " ,list_up.at(i).length() );

            p1d=list_dwn.at(i).pointAtPercent(0);

            p2u=list_up.at(i).pointAtPercent(0);
            if( (d_deltad<0) )
            {
                Unicus::console("d_deltad------------------------------------------>",d_deltad);
                Unicus::console("d_length------------------------------------------>",list_dwn.at(i).length());
                double tmp_d_deltad = -d_deltad/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltad = -d_deltad;
                ldwn = C2DPath( list_dwn.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltad/list_dwn.at(i).length();

                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                {
                    tmpend = ((list_dwn.at(i).length()-tmp_d_deltad)/list_dwn.at(i).length())-tmpstart;
                }
                list_dwn.replace( i, ldwn.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("d_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("d_tmpend------------------------------------------>",tmpend);

            }
            //Unicus::console("d_deltau------------------------------------------>",d_deltau);
            if( (d_deltau<0) )
            {
                Unicus::console("u_deltad------------------------------------------>",d_deltau);
                Unicus::console("u_length------------------------------------------>",list_up.at(i).length());
                double tmp_d_deltau = -d_deltau/2;
                if(( i == 0 )||(i+1 == list_up.count()))
                    tmp_d_deltau = -d_deltau;
                lup = C2DPath( list_up.at(i) );
                if( i == 0 )
                    tmpstart = 0;
                else
                    tmpstart = tmp_d_deltau/list_up.at(i).length();
                //Unicus::console("tmpstart------------------------------------------>",tmpstart);
                if( i+1 == list_up.count() )
                    tmpend = 1;
                else
                    tmpend = ((list_up.at(i).length()-tmp_d_deltau)/list_up.at(i).length())-tmpstart;
                list_up.replace(i, lup.takepartofpath( tmpstart,tmpend,1 ) );
                Unicus::console("u_tmpstart------------------------------------------>",tmpstart);
                Unicus::console("u_tmpend------------------------------------------>",tmpend);
            }

            line1.setPoints( list_dwn.at(i).pointAtPercent(0),list_up.at(i).pointAtPercent(0) );
            d_angle = lineSTRT.angle() - line1.angle();
            lup = C2DPath( list_up.at(i),-d_angle );
            double tmplen1=0;

            if((d_deltau<0)&&(d_deltad<0))
            {
                line2.setPoints(lineSTRT.p2(),lineSTRT.p1());
                double tmptmpdouble =   (QLineF(list_dwn.at(i).pointAtPercent(0),
                                           list_up.at(i).pointAtPercent(0)).length()
                        -lineSTRT.length())*0.5f;
                line2.setLength( line2.length() + tmptmpdouble );
                line2.setPoints( line2.p2(),line2.p1() );
                line2.setLength( line2.length() + tmptmpdouble );
            }else if(d_deltau<0)
            {
                line2 = lineSTRT;
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
            }else if(d_deltad<0)
            {
                line2.setPoints( lineSTRT.p2(),lineSTRT.p1() );
                line2.setLength( QLineF(list_dwn.at(i).pointAtPercent(0),
                                        list_up.at(i).pointAtPercent(0)).length() );
                line2.setPoints( line2.p2(),line2.p1() );
            }

            if(d_deltau>=0)
                lineUP = lup.myshape( lineSTRT.p2() );
            else
            {
                //tmplen1 = 1;
                //        lineSTRT.length();

                lineUP = lup.myshape( line2.p2() );
            }
            ldwn = C2DPath( list_dwn.at(i),-d_angle );
            if(d_deltad>=0)
                lineDWN = ldwn.myshape( lineSTRT.p1() );
            else
            {
                    lineDWN = ldwn.myshape( line2.p1() );
            }
            pd = lineDWN.pointAtPercent(1);
            pu = lineUP.pointAtPercent(1);
            if( (i+1)!=list_up.count() )
            {
                oldpu = pu;
                oldpd = pd;
                if(d_deltad>0)
                {
                    wide_collar_down.connectPath( lineDWN );
                    angled = 2*180/M_PI*asin( d_deltad/(2*QLineF( pu,pd ).length()) );
                    line1.setPoints( pu,pd );
                    //wide_collar_down.arcTo( pu.x()-line1.length(),
                    //                      pu.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      -angled);
                    pd = Unicus::rPoint( pd,pu,angled );
                    wide_collar_down.moveTo(pd);
                }
                else if( d_deltad < 0 )
                {
                    wide_collar_down.connectPath( lineDWN );
                }else
                {
                    wide_collar_down.connectPath( lineDWN );
                }

                if(d_deltau>0)
                {
                    wide_collar_up.connectPath( lineUP );

                    angle = 2*180/M_PI*asin( d_deltau/(2*QLineF( pu,pd ).length()) );
                    pu = Unicus::rPoint( pu,pd,-angle );
                    line1.setPoints( oldpd,oldpu );
                    wide_collar_up.moveTo( pu );
                    //wide_collar_up.arcTo( oldpd.x()-line1.length(),
                    //                      oldpd.y()-line1.length(),
                    //                      line1.length()*2,
                    //                      line1.length()*2,
                    //                      line1.angle(),
                    //                      angle);
                }
                else if( d_deltau<0 )
                {
                    wide_collar_up.connectPath( lineUP );
                }else
                {
                    wide_collar_up.connectPath( lineUP );
                }
                lineSTRT.setPoints(pd,pu);
            }else
            {
                wide_collar_up.connectPath( lineUP );
                wide_collar_down.connectPath( lineDWN );
            }
        }
    //return QLineF( lineDWN.pointAtPercent(1),lineUP.pointAtPercent(1) );
    return QLineF( pd,pu );
}
QPainterPath C2DDress::splineaboutYl( QLineF first, QLineF second, double K1, double K2, double lengh, double pogr )
{
    QPainterPath path;
    QLineF line;
    QPointF p;
    double b = fabs(first.p1().y()-second.p1().y());
    Unicus::console( "b---------------",b );
    double amin=0;//sqrt( abs( pow(lengh,2)-pow(b,2)) );
    double amax=lengh;
    double delta = amax-amin;
    first.setLength( first.length()*K1 );
    second.setLength( second.length()*K2 );
    int i = 0;
    do
    {
        delta = fabs(amax-amin);
        p = QPointF( (first.x1()+amin) + (delta/2),second.y1() );
        line.setPoints( p, p + QPointF(1,1) );
        line.setAngle(second.angle());
        line.setLength(second.length());
        second=line;
        path = QPainterPath();
        path.moveTo( first.p1() );
        path.cubicTo( first.p2(), second.p2(), second.p1() );
        if( path.length()>lengh )
            amax = amax - (delta/2);
        else if( path.length()<lengh )
            amin = amin + (delta/2);
        else
            break;
        i++;
    }
    while(( fabs(path.length()-lengh) > pogr ) && ( i < 200 ) );
    Unicus::console( "spline_about_Y - i =", i );
    Unicus::console( "nujnyy lengh", lengh );
    Unicus::console( "gotovyy lengh", path.length() );

    if( fabs(path.length()-lengh)>(pogr*2) )
    {

        return QPainterPath();
    }
    return path;
}
void C2DDress::col_conners_changing_conditions()
{
    double nowH = LD("c0_b")+fabs(LD("c2_b"));
    if( nowH > col_con_leftH )
    {
        H("c0_b") = LD("c0_b")/nowH*col_con_leftH;
        H("c2_b") = LD("c2_b")/nowH*col_con_leftH;
        VorotDialog->SetDspinVal( "c0_b", LD("c0_b")/10 );
        VorotDialog->SetDspinVal( "c2_b", -LD("c2_b")/10 );
    }
    nowH = LD("c1_b")+fabs(LD("c3_b"));
    if( nowH > col_con_rightH )
    {
        H("c1_b") = LD("c1_b")/nowH*col_con_rightH;
        H("c3_b") = LD("c3_b")/nowH*col_con_rightH;
        VorotDialog->SetDspinVal( "c1_b", LD("c1_b")/10 );
        VorotDialog->SetDspinVal( "c3_b", -LD("c3_b")/10 );
    }

    double col_condlX = (LD("vorot_l_add"));
    double col_condrX = LD("vorot_r_add");

    VorotDialog->SetDspinMinMax( "c0_a",0,col_con_uX/10 );
    VorotDialog->SetDspinMinMax( "c1_a",0,col_con_uX/10 );
    VorotDialog->SetDspinMinMax( "c2_a",0,col_con_dX/10 );
    VorotDialog->SetDspinMinMax( "c3_a",0,col_con_dX/10 );

    //VorotDialog->SetDspinVal( "c2_a",col_condlX/10 );
    //VorotDialog->SetDspinVal( "c3_a",col_condrX/10 );
    if(LD("c2_a")>col_condlX)
        H("c2_a") = col_condlX;
    if(LD("c3_a")>col_condrX)
        H("c3_a") = col_condrX;
    nowH = LD("c0_a")+LD("c1_a");
    Unicus::console( "nowH",nowH );
    Unicus::console( "col_con_uX",col_con_uX );
    if( nowH > col_con_uX )
    {
        H("c0_a") = LD("c0_a")/nowH*col_con_uX;
        H("c1_a") = LD("c1_a")/nowH*col_con_uX;
        VorotDialog->SetDspinVal( "c0_a", LD("c0_a")/10 );
        VorotDialog->SetDspinVal( "c1_a", LD("c1_a")/10 );
    }
    nowH = LD("c2_a")+LD("c3_a");
    if( nowH > col_con_dX )
    {
        H("c2_a") = LD("c2_a")/nowH*col_con_dX;
        H("c3_a") = LD("c3_a")/nowH*col_con_dX;
        VorotDialog->SetDspinVal( "c2_a", LD("c2_a")/10 );
        VorotDialog->SetDspinVal( "c3_a", LD("c3_a")/10 );
    }
}
QPointF C2DDress::GetUpPointOnBottomLines( QLineF leftline, QLineF rightline, double h, double a )
{
    QLineF line1;
    Unicus::console( "LEFTANGLE", leftline.angle() );
    Unicus::console( "RIGHTANGLE", rightline.angle() );

    if( leftline == QLineF() )
    {
        rightline.setAngle( a-90 );
        rightline.setLength( h );
        return rightline.p2();
    }
    if( rightline == QLineF() )
    {
        line1.setPoints( leftline.p2(),leftline.p1() );
        line1.setAngle( a-90 );
        line1.setLength( h );
        return line1.p2();
    }
    //{
    //    line1.setPoints( leftline.p2(),leftline.p1() );
    //    leftline = line1;
    //}
    //if(rightline.x1()>rightline.x2())
    //{
    //    line1.setPoints( rightline.p2(),rightline.p1() );
    //    rightline = line1;
    //}
    line1.setPoints( leftline.p2(),leftline.p1() );
    //if(line1.angle() == 180)
        //line1.setAngle( -line1.angle() );
    a = (rightline.angle()+line1.angle())*0.5f;
    Unicus::console( "A---", a );
    //if( a > 0 )
    //    a = -a;
    Unicus::console( "leftline.p2().y()", leftline.p2().y() );
    Unicus::console( "leftline.p1().y()", leftline.p1().y() );

    if((leftline.p1().y()==leftline.p2().y()))
    {
        Unicus::console( "A!!!!!!!!!", a );
        a = a + 180;
    }
    line1.setAngle( a );

    line1.setLength( h );
    //if( line1.p2().y()<line1.p1().y() )
    //    line1.setLength( -h );
    return line1.p2();
}

QPainterPath C2DDress::GetUpLineOnBottomLine( QPointF strt, QPainterPath lineDWN, QLineF l1, QLineF l2, bool first )
{
    QPainterPath result = QPainterPath();
    QLineF tmpl,line1,line2;
    QPointF p1,p2,pb;
    //tmpl.setPoints(strt,l1.p2());
    double start=0;

    if( strt.x() > l1.p1().x() )
    {
        line1.setPoints( strt,strt+QPointF(0,1) );
        line1.intersect( l1,&pb );
        start = QLineF(l1.p1(),pb).length();
        tmpl.setPoints( pb,l1.p2() );
        result.moveTo(pb);
    }else if( l1.p1().x()>strt.x() )
    {
        tmpl = l1;
        result.moveTo(strt);
        result.lineTo(l1.p1());
    }else
    {
        if((first)&&(lineDWN.pointAtPercent(0).x()<strt.x()))
        {
            result.moveTo( lineDWN.pointAtPercent(0)+QPointF(0,QLineF(lineDWN.pointAtPercent(0),l1.p1()).length()) );
            result.lineTo(strt);
        }else
            result.moveTo(strt);
    }
    ////////////////////////////////////////////////////////
    if( l2 == QLineF() )
    {
        result.lineTo( l1.p2() );
        //result.connectPath( partofline( QLineF(result.currentPosition(),l1.p2()),l1.length(),lineDWN,
        //                                start ) );
        if( lineDWN.pointAtPercent(1).x()>l1.p2().x() )
            result.lineTo( lineDWN.pointAtPercent(1)+QPointF( 0,QLineF(lineDWN.pointAtPercent(1),l1.p2()).length() ) );
    }
    else
        if( (l1.angle()!=l2.angle())&&(l1.angle()!=l2.angle()+180) )
        {
            if(l1.p2().x()<=lineDWN.pointAtPercent(1).x())
            {
                if(l2.p1().x()<lineDWN.pointAtPercent(1).x())
                {
                    result.lineTo( l1.p2() );
                    //result.connectPath( partofline( QLineF(result.currentPosition(),l1.p2()),l1.length(),lineDWN,
                    //                                start ) );
                    l2.intersect( QLineF(lineDWN.pointAtPercent(1),lineDWN.pointAtPercent(1)+QPointF(0,1)),&p2 );
                    result.lineTo( p2 );
                }else
                {
                    result.lineTo( l1.p2() );
                    //result.connectPath( partofline( QLineF(result.currentPosition(),l1.p2()),l1.length(),lineDWN,
                    //                                start ) );
                    result.lineTo( lineDWN.pointAtPercent(1)+
                                   QPointF( 0, QLineF(l2.p1(),lineDWN.pointAtPercent(1) ).length() ) );
                }
            }else
            {
                l1.intersect( l2,&p2 );
                result.lineTo( p2 );
                //result.connectPath( partofline( QLineF(result.currentPosition(),p2),l1.length(),lineDWN,
                //                                start ) );
            }
        }
        else
        {
            result.lineTo( l1.p2() );
            //result.connectPath( partofline( QLineF(result.currentPosition(),l1.p2()),l1.length(),lineDWN,
            //                                start ) );
        }
    //result.lineTo(p2);
    return result;
}
QPainterPath C2DDress::partofline(QLineF l1,double llength,QPainterPath pth1,double start,int parts)
{
    //parts = 3;
    QPainterPath result;
    result.moveTo( l1.p1() );
    int i;
    double tmplshag = l1.length()/parts;
    //double DWNstart = (start/l1.length())*lineDWN.length();
    QPointF p1,p2,p3;
    QLineF line1,line2;
    QLineF base = QLineF(pth1.pointAtPercent(0),pth1.pointAtPercent(1));
    double percent;

    Unicus::console( "L1.length---------------------",l1.length() );
    Unicus::console( "BASE.length---------------------",base.length() );
    Unicus::console( "START---------------------",start );
    for( i = 1; i<parts; i++ )
    {
        percent = (start+(tmplshag*i))/(llength);
        Unicus::console( "PERCENT---------------------",percent );
        p1 = pth1.pointAtPercent( percent );
        p2 = base.pointAt( percent );
        p3 = l1.pointAt(i*tmplshag/l1.length());
        line1.setPoints( p1,p2 );
        line2.setPoints( p3,p3+QPointF(1,1) );
        line2.setLength(line1.length());
        line2.setAngle(line1.angle()+180);
        result.lineTo(line2.p2());
    }
    result.lineTo( l1.p2() );
    return result;
}

QPainterPath C2DDress::gethightline( QPointF p1, double a1, double H2, QPainterPath path, double a2, int add )
{
    double left=0, right=0;
    if( add == 1 ) //0 -ничего не делать ;1 добавить слева ;2 добавить српправа)
    {
        left = LD("L:OX");
    }else if( add == 2 )
    {
        right = LD("R:OX");
    }

    //gethightline( u1.pointAtPercent(1),/*u1.angleAtPercent(1)*/a2,h3,p2path,a3+180 );
    QPainterPath result;
    QLineF l1,l2;
    QPointF p2;
    //l2.setPoints( path.pointAtPercent(1),path.pointAtPercent(1)+QPointF(1,1) );
    //l2.setAngle( path.angleAtPercent(1)-90 );
    //l2.setLength( H2 );
    //p2 = l2.p2();
    p2=path.pointAtPercent(1)+QPointF(right,H2);
    p1=p1+QPointF(-left,0);
    l1.setPoints(p1,p1+QPointF(1,1));
    l1.setAngle( a1 );
    l1.setLength( QLineF(p1,p2).length()*0.3 );

    l2.setPoints( p2,p2+QPointF(1,1));
    l2.setAngle( a2 );
    l2.setLength( QLineF(p1,p2).length()*0.3 );

    result.moveTo(l1.p1());
    result.cubicTo(l1.p2(),l2.p2(),l2.p1());
    return result;
}
QList< QPainterPath > C2DDress::gettoptines( QPainterPath p1path,QPainterPath p2path,
                                             QPainterPath p3path,QPainterPath p4path )
{

    double a1=0,a2=0,a3=0,a4=0,a5=0;
    if( simple == true )
    {
        equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
        equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
        equidistant->SetDspinText( "3:A",QObject::trUtf8( "центра полочки" ) );
        equidistant->SetDspinText( "4:A","false" );
        equidistant->SetDspinText( "5:A","false" );
        a1 = D("1:A");a2 = D("2:A");a3 = D("3:A");
    }else
    {
        if( LD("is_clasp") == 0 )
        {
            equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
            equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
            equidistant->SetDspinText( "3:A",QObject::trUtf8( "плечевого шва, левого" ) );
            equidistant->SetDspinText( "4:A",QObject::trUtf8( "центра полочки" ) );
            equidistant->SetDspinText( "5:A","false" );
            a1 = -D("3:A");a2 = D("1:A");a3 = D("2:A");a4 = D("4:A");a5 = D("3:A");
        }else
        {
            if( LD("clasp_location")==1 ) //polochka
            {
                if( D("vorot_dsgn")==0 )//simmetri4noe
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "4:A","false" );
                    equidistant->SetDspinText( "5:A","false" );
                    a1 = -D("3:A");a2 = -D("2:A");a3 = D("1:A");a4 = D("2:A");a5 = D("3:A");
                }else
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "плечавого шва, левого" ) );
                    equidistant->SetDspinText( "4:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "5:A",QObject::trUtf8( "центра полочки, левого" ) );
                    a1 = -D("5:A");a2 = -D("3:A");a3 = D("1:A");a4 = D("2:A");a5 = D("4:A");
                }
            }
            else if( LD("clasp_location")==0 ) //spinka
            {
                if( D("vorot_dsgn")==0 )//simmetri4noe
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "4:A","false" );
                    equidistant->SetDspinText( "5:A","false" );
                    a1 = -D("3:A");a2 = -D("2:A");a3 = D("1:A");a4 = D("2:A");a5 = D("3:A");
                }else
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "плечевого шва, левого" ) );
                    equidistant->SetDspinText( "4:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "5:A",QObject::trUtf8( "центра спинки, левого" ) );
                    a1 = D("4:A");a2 = D("2:A");a3 = D("1:A");a4 = -D("3:A");a5 = -D("5:A");
                }
            }
            else
            {
                if( D("vorot_dsgn")==0 )//simmetri4noe
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "4:A","false" );
                    equidistant->SetDspinText( "5:A","false" );
                    a1 = -D("2:A");a2 = D("1:A");a3 = D("2:A");a4 = D("3:A");a5 = -D("2:A");
                }else
                {
                    equidistant->SetDspinText( "1:A",QObject::trUtf8( "центра спинки" ) );
                    equidistant->SetDspinText( "2:A",QObject::trUtf8( "плечевого шва" ) );
                    equidistant->SetDspinText( "3:A",QObject::trUtf8( "плечевого шва, левого" ) );
                    equidistant->SetDspinText( "4:A",QObject::trUtf8( "центра полочки" ) );
                    equidistant->SetDspinText( "5:A","false" );
                    a1 = -D("3:A");a2 = D("1:A");a3 = D("2:A");a4 = D("4:A");a5 = -D("3:A");
                }
            }
        }
    }
    if( D("vorot_dsgn")==0 )
    {
        equidistant->SetDspinText( "L:OX",QObject::trUtf8( "Длиннее/Короче, см" ) );
        equidistant->SetDspinText( "R:OX","false" );
        H("L:OX") = D("L:OX");
        H("R:OX") = D("L:OX");
    }else
    {
        equidistant->SetDspinText( "L:OX",QObject::trUtf8( "Длиннее/Короче слева, см" ) );
        equidistant->SetDspinText( "R:OX",QObject::trUtf8( "Длиннее/Короче справа, см" ) );
        H("L:OX") = D("L:OX");
        H("R:OX") = D("R:OX");
    }
    QLineF line1,line2,line3,line4,tmpl;
    QPointF p;
    QPainterPath u1=QPainterPath(),u2=QPainterPath(),u3=QPainterPath(),u4=QPainterPath();
    double h1=QLineF( P["V1d"], P["V1u"] ).length();
    double h2=QLineF( P["V2d"], P["V2u"] ).length();
    double h3=QLineF( P["V3d"], P["V3u"] ).length();
    double h4=QLineF( P["V4d"], P["V4u"] ).length();
    double h5=QLineF( P["V5d"], P["V5u"] ).length();

    line1.setPoints( p1path.pointAtPercent(0),p1path.pointAtPercent(0)+QPointF(1,1) );
    //line1.setAngle( p1path.angleAtPercent(0)-90 );
    line1.setAngle( -90 );
    line1.setLength( h1 );
    if(simple)
        u1 = gethightline( line1.p2(),/*p1path.angleAtPercent(0)*/a1, h2, p1path,a2+180,0  );
    else
        u1 = gethightline( line1.p2(),/*p1path.angleAtPercent(0)*/a1, h2, p1path,a2+180,1  );

    //P["dbg1"] = line1.p2()+QPointF(0,1);
    //P["dbg2"] = p1path.pointAtPercent(1)+QPointF(0,h2+1);
    //P["dbg3"] = p2path.pointAtPercent(1)+QPointF(0,h3+1);


    //line( Sync( attr( SYNC_NAME,  QString( "dBu1-cl_up" ) ),
    //            attr( SYNC_TYPE, C2DSync::Line ),
    //            attr( SYNC_LIST, MakeList( "dbg1", "dbg2" ) ),
   //             LM->bold_solid() ),
   //       false );
   // line( Sync( attr( SYNC_NAME,  QString( "dBu1-cl_up3" ) ),
   //             attr( SYNC_TYPE, C2DSync::Line ),
   //             attr( SYNC_LIST, MakeList( "dbg2", "dbg3" ) ),
   //             LM->thick_red() ),
   //       false );
   // ppath(  Sync( attr( SYNC_NAME,  QString( "v_w_endvavcbr2" ) ),
   //                         attr( SYNC_TYPE, C2DSync::Ppath ),
   //                         attr( SYNC_LIST, MakeList( "dbg1" ) ),
   //                         LM->thick_red() ), &u1, /*(-(270-focusline.angle()))*/0, 0,
   //                         true );

    if(simple)
        u2 = gethightline( u1.pointAtPercent(1),/*u1.angleAtPercent(1)*/a2,h3,p2path,a3+180,2 );
    else
        u2 = gethightline( u1.pointAtPercent(1),/*u1.angleAtPercent(1)*/a2,h3,p2path,a3+180,0 );
    if(!simple)
    {
        u3 = gethightline( u2.pointAtPercent(1),/*u2.angleAtPercent(1)*/a3,h4,p3path,a4+180 );
        u4 = gethightline( u3.pointAtPercent(1),/*u3.angleAtPercent(1)*/a4,h5,p4path,a5+180,2 );
    }
    QList< QPainterPath > result;

    result.append( u1 );
    result.append( u2 );
    result.append( u3 );
    result.append( u4 );
    return result;
}
QList< QPainterPath > C2DDress::getdecor( QPainterPath up,QPainterPath down,double * sign1,double * sign2,bool spinka ,bool lev)
{
    double tmptmp = down.length();
    if( *sign1 != -1 )
        *sign1 = (*sign1) * tmptmp;
    if( *sign2 != -1 )
        *sign2 = (*sign2) * tmptmp;
    QList< QPainterPath > result;
    int N;
    double d1,d2;
    N = D("vd_vN");
    if(N<2)
        N = 2;
    d1 = D("vd_v")/2;
    d2 = D("vd_d")/2;
    //QPainterPath up,down;
    if(lev==false)
        resize_collar( up,down,N,d1,d2,QLineF( down.pointAtPercent(0),up.pointAtPercent(0) ) );
    else
        resize_collar_right( up,down,N,d1,d2,QLineF( down.pointAtPercent(0),up.pointAtPercent(0) ) );
    up = wide_collar_up;
    down = wide_collar_down;

    //QPainterPath endvar2;
    //endvar2 = up;
    //endvar2.lineTo(down.pointAtPercent(1));
    //endvar2.connectPath( down.toReversed() );
    //endvar2.lineTo(up.pointAtPercent(0));
    //P["v_w_endvar2"] = up.pointAtPercent(1)+QPointF(150,300);

    //ppath(  Sync( attr( SYNC_NAME,  QString( "v_w_endvar2" ) ),
    //                    attr( SYNC_TYPE, C2DSync::Ppath ),
    //                    attr( SYNC_LIST, MakeList( "v_w_endvar2" ) ),
    //                    LM->thick_yellow() ), &endvar2, /*(-(270-focusline.angle()))*/0, 0,
    //                    false );
    N = D("vd_hN");
    if(D("vorot_dsgn")==0)
    {
        if(spinka)
        {
            d1 = D("vd_s");
            d2 = D("vd_p");
        }else
        {
            d2 = D("vd_s");
            d1 = D("vd_p");
        }
    }
    else
    {
        if(lev==false)
        {
            if(spinka)
            {
                d1 = D("vd_s");
                d2 = D("vd_p");
            }else
            {
                d2 = D("vd_s");
                d1 = D("vd_p");
            }
        }else
        {
            if(spinka)
            {
                d1 = D("vd_s_lev");
                d2 = D("vd_p_lev");
            }else
            {
                d2 = D("vd_s_lev");
                d1 = D("vd_p_lev");
            }
        }
    }
    QPainterPath leftdecor,rightdecor;
    leftdecor.moveTo( down.pointAtPercent(0) );
    leftdecor.lineTo( up.pointAtPercent(0) );
    rightdecor.moveTo( down.pointAtPercent(1) );
    rightdecor.lineTo( up.pointAtPercent(1) );
//ограничения
    double leftl,rightl;
    leftl=leftdecor.length()/10;
    rightl=rightdecor.length()/10;
    if(lev)
    {
        if(spinka)
        {
            VorotDecor->SetDspinMinMax( "vd_s_lev",-leftl,20 );
            VorotDecor->SetDspinMinMax( "vd_p_lev",-rightl,20 );
        }else
        {
            VorotDecor->SetDspinMinMax( "vd_p_lev",-leftl,20 );
            VorotDecor->SetDspinMinMax( "vd_s_lev",-rightl,20 );
        }
    }else
    {
        if(spinka)
        {
            VorotDecor->SetDspinMinMax( "vd_s",-leftl,20 );
            VorotDecor->SetDspinMinMax( "vd_p",-rightl,20 );
        }else
        {
            VorotDecor->SetDspinMinMax( "vd_p",-leftl,20 );
            VorotDecor->SetDspinMinMax( "vd_s",-rightl,20 );
        }
    }
//конец ограничений
    if(lev==false)
        resize_collar( leftdecor,rightdecor,
                           N,d1,d2,
                           QLineF( rightdecor.pointAtPercent(0),leftdecor.pointAtPercent(0) ) );
    else
        resize_collar_right( leftdecor,rightdecor,
                           N,d1,d2,
                           QLineF( rightdecor.pointAtPercent(0),leftdecor.pointAtPercent(0) ) );
    QLineF line1,line2,line3;
    line1.setPoints(leftdecor.pointAtPercent(1),rightdecor.pointAtPercent(1));
    line3.setPoints(leftdecor.pointAtPercent(0),rightdecor.pointAtPercent(0));
    leftdecor = wide_collar_up;
    rightdecor = wide_collar_down;
    line2.setPoints(leftdecor.pointAtPercent(1),rightdecor.pointAtPercent(1));
    Unicus::console( "line1.length",line1.length() );
    Unicus::console( "line2.length",line2.length() );
    C2DPath tempc2dpath = C2DPath( up,line1.angle()-line2.angle() );
    result.append( leftdecor );
    result.append( tempc2dpath.myshape( leftdecor.pointAtPercent(1),1,1 ) );
    result.append( rightdecor.toReversed() );
    result.append( down.toReversed() );


    /*QPainterPath endvar3;
    endvar3 = leftdecor;
    endvar3.connectPath(tempc2dpath.myshape( endvar3.currentPosition(),1,3 ));
    endvar3.connectPath( rightdecor.toReversed() );
    line2.setPoints( leftdecor.pointAtPercent(0),rightdecor.pointAtPercent(0) );
    Unicus::console( "line3.length",line3.length() );
    Unicus::console( "line2.length",line2.length() );
    tempc2dpath = C2DPath( down,line3.angle()-line2.angle() );
    endvar3.connectPath(down.toReversed());
    P["v_w_endvar3"] = QPointF(500,300);

    ppath(  Sync( attr( SYNC_NAME,  QString( "v_w_endvar3" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "v_w_endvar3" ) ),
                        LM->thick_yellow() ), &endvar3, /*(-(270-focusline.angle()))/0, 0,
                        true );*/
    QList < QPair<double, QPainterPath> > decorsigns;
    for( int i = 0; i < result.count();i++ )
        if(result.at(i)!=QPainterPath())
            result.replace( i, cGeometry::getsmoothpath( result.at(i),0,0,decorsigns,3 ) );
    result = Gathers( result, lev, sign1, sign2 );
    if( *sign1 != -1 )
        *sign1 = *sign1 / result.at(3).length();
    if( *sign2 != -1 )
        *sign2 = *sign2 / result.at(3).length();
    return result;
}
void C2DDress::drawdecor( QString name, QPointF p, QList< QPainterPath > items, bool draw, double angle, double signpos, double signpos2 )
{
    //Unicus::console( "is_vorotdecor-",this->is_vorotdecor );

    //p = p - (  QPointF( items.at(2).pointAtPercent(1).x(),0 ) - QPointF( items.at(0).pointAtPercent(0).x(), 0 ) );
    //QPointF tmppoint = (items.at(2).pointAtPercent(1) - items.at(0).pointAtPercent(0));
    //p = p - QPointF( tmppoint.x(),-tmppoint.y()-150 );
    //
    QPainterPath path=QPainterPath();
    P[name+"_S"] = QPointF(1,1);
    if(signpos==0)
        signpos = -1;
    if(signpos2==0)
        signpos2 = -1;
    double sign_angle = 0, sign_angle2 = 0;
    QLineF l1;
    bool issign = false, issign2 = false;
    if((draw==false)||( is_vorotdecor == false ))
    {
        P[name] = p;
        ppath(  Sync( attr( SYNC_NAME, name ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( name ) ),
                            LM->thick_yellow() ), &path, 0, 0,
                            false );
        signP( name+"_S", P[name+"_S"],sign_angle+angle-90,false,issign&&draw );
        signP( name+"_S2", P[name+"_S2"],sign_angle2+angle-90,false,issign2&&draw );

        return;
    }



    path.moveTo(p);
    //path = items.at(0);
    for( int i = 0; i < items.count();i++ )
        if(items.at(i)!=QPainterPath())
        {
            if( signpos != -1 )
                if(i == 3)
                {
                    l1.setPoints( items.at(i).toReversed().pointAtPercent(0),
                                  items.at(i).toReversed().pointAtPercent( signpos ));
                    l1.setAngle( l1.angle() + angle );
                    sign_angle = items.at(i).toReversed().angleAtPercent( signpos );
                    P[name+"_S"] = p + (l1.p2()-l1.p1());
                }
            if( signpos2 != -1 )
                if(i == 3)
                {
                    l1.setPoints( items.at(i).toReversed().pointAtPercent(0),
                                  items.at(i).toReversed().pointAtPercent( signpos2 ));
                    l1.setAngle( l1.angle() + angle );
                    sign_angle2 = items.at(i).toReversed().angleAtPercent( signpos2 );
                    P[name+"_S2"] = p + (l1.p2()-l1.p1());
                }
            path.connectPath(items.at(i));
        }    //path.connectPath( items.at(i) );

    P[name] = p;
    ppath(  Sync( attr( SYNC_NAME, name ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( name ) ),
                        LM->thick_yellow() ), &path, -angle, 0,
                        draw );


    if((D("is_vorot") == 1)&&(D("vorot_type") == 1))
        //if( LD("stoika_krai") == 2 )
        //if( D("vorot_type") == 0 )
        {
            if(signpos != -1)
                issign = true;
            if(signpos2 != -1)
                issign2 = true;
        }

    if( ( LD("is_clasp")==0 )&&( LD("is_cut")==0 ) )
    {
        issign = false;
        issign2 = false;
    }


    signP( name+"_S", P[name+"_S"],sign_angle+angle-90,false,issign&&draw );
    signP( name+"_S2", P[name+"_S2"],sign_angle2+angle-90,false,issign2&&draw );
}



QList< QPainterPath > C2DDress::Gathers( QList< QPainterPath > items, bool lev, double * sign1, double * sign2 )
{
    QPainterPath pleft = items.at(0);
    QPainterPath ptop = items.at(1);
    QPainterPath pright = items.at(2);
    QPainterPath pbot = items.at(3).toReversed();
    //Обработка значений
    double GN,GType,GA1,GA2,GB1,GB2,GC1,GC2;
    if( (lev==false)||(D("vorot_dsgn")==0) )
        GType = D("G:Type");
    else
        GType = D("G:Type:l");

    if( (lev==false)||(D("vorot_dsgn")==0) )
    {

        //Unicus::console( "C1Epta",D("G:C1") );
        checkgathersvalues( ptop.length(),"G:A1","G:B1","G:C1","G:N",GType);
        /*Unicus::console( "ptop.length()",ptop.length() );
        Unicus::console( "pbot.length()",pbot.length() );
        Unicus::console( "GA1",LD("G:A1") );
        Unicus::console( "GA2",LD("G:A2") );
        Unicus::console( "GB1",LD("G:B1") );
        Unicus::console( "GB2",LD("G:B2") );
        Unicus::console( "GC1",LD("G:C1") );
        Unicus::console( "GC2",LD("G:C2") );
        Unicus::console( "Type",GType );*/
        checkgathersvalues( pbot.length(),"G:A2","G:B2","G:C2","G:N",GType);
        GN = D("G:N");
        //GType = D("G:Type");
        GA1 = LD("G:A1");
        GA2 = LD("G:A2");
        GB1 = LD("G:B1");
        GB2 = LD("G:B2");
        GC1 = LD("G:C1");
        GC2 = LD("G:C2");
        /*Unicus::console( "ptop.length()",ptop.length() );
        Unicus::console( "pbot.length()",pbot.length() );
        Unicus::console( "GA1",GA1 );
        Unicus::console( "GA2",GA2 );
        Unicus::console( "GB1",GB1 );
        Unicus::console( "GB2",GB2 );
        Unicus::console( "GC1",GC1 );
        Unicus::console( "GC2",GC2 );
        Unicus::console( "Type",GType );*/
    }else
    {
        checkgathersvalues( ptop.length(),"G:A1:l","G:B1:l","G:C1:l","G:N:l",GType);
        checkgathersvalues( pbot.length(),"G:A2:l","G:B2:l","G:C2:l","G:N:l",GType);
        GN = D("G:N:l");
        //GType = D("G:Type:l");
        GA1 = LD("G:A1:l");
        GA2 = LD("G:A2:l");
        GB1 = LD("G:B1:l");
        GB2 = LD("G:B2:l");
        GC1 = LD("G:C1:l");
        GC2 = LD("G:C2:l");
    }

    if((D("vorot_dsgn")==0)&&(lev==true))
    {
        if(GType==0)
            GType = 1;
        else if(GType==1)
            GType = 0;
    }else if((D("vorot_dsgn")==1)&&(lev==true))
    {
        if(GType==0)
            GType = 1;
        else if(GType==1)
            GType = 0;
    }


    if( ( GC1==0 ) && ( GC2==0 ) )
        return items;
    //D("G:N")      D("G:TYPE")     D("G:B1")    D("G:B2")    D("G:C1")    D("G:C2")




    ///разбиение на N частей
    QPointF pu,pd;
    QLineF line1,line2;double d_angle,tmptmp;C2DPath lup,ldwn;QLineF lineSTRT = QLineF( pbot.pointAtPercent(0),ptop.pointAtPercent(0) );
    lup = C2DPath( ptop );
    ldwn = C2DPath( pbot );
    double gaa1,gaa2;
    gaa1=ptop.length()-GA1-((GN-1)*GB1);
    gaa2=pbot.length()-GA2-((GN-1)*GB2);
    if((lev!=true))
    {
        gaa1=GA1;
        gaa2=GA2;
    }
    QList < QPainterPath > gather_path,gather_path2;
    QList < QPainterPath > list_up = lup.splitpath2(GN,gaa1,GB1,1);
    QList < QPainterPath > list_dwn = ldwn.splitpath2(GN,gaa2,GB2,1);

    QPainterPath g_up = QPainterPath();
    QPainterPath g_bot = QPainterPath();
    QPainterPath lineUP,lineDWN,tmppath;
/******************************/
    g_up.moveTo( lineSTRT.p2() );
    g_bot.moveTo( lineSTRT.p1() );
    double d_u;
    double d_d;
    if(GType!=2)
    {
        d_u = GC1/2;
        d_d = GC2/2;
    }else
    {
        d_u = GC1/4;
        d_d = GC2/4;
    }
    double tmpdouble;
    int k = 0,k2 = 0;
    QLineF ls,l1,le;
    QPainterPath lastfixbot,lastfixtop,addfix;
    C2DPath lfxt,lfxb;
    //QPointF intsct,intsct2;
    for( int i = 0;i<=GN;i++ )
    {
        line1.setPoints( list_dwn.at(i).pointAtPercent(0),list_up.at(i).pointAtPercent(0) );
        d_angle = lineSTRT.angle() - line1.angle();
        //lastfix
        k = 0;
        lastfixtop = list_up.at(k);
        lastfixbot = list_dwn.at(k);
        while(i > k)
        {
            k++;
            lastfixtop.connectPath( list_up.at(k) );
            lastfixbot.connectPath( list_dwn.at(k) );
        }
        lastfixtop = lastfixtop.toReversed();
        lastfixbot = lastfixbot.toReversed();

        //lastfix
        lup = C2DPath( list_up.at(i),-d_angle );
        ldwn = C2DPath( list_dwn.at(i),-d_angle );

        lineUP = lup.myshape( lineSTRT.p2() );
        lineDWN = ldwn.myshape( lineSTRT.p1() );

        lfxt = C2DPath( lastfixtop,-((lineUP.angleAtPercent(1)+180)-lastfixtop.angleAtPercent(0)) );
        lfxb = C2DPath( lastfixbot,-((lineDWN.angleAtPercent(1)+180)-lastfixbot.angleAtPercent(0)) );
        lastfixtop = lfxt.myshape(lineUP.pointAtPercent(1)).toReversed();
        lastfixbot = lfxb.myshape(lineDWN.pointAtPercent(1)).toReversed();
        //lfxb = C2DPath( lastfixbot,-d_angle );
        //drawpath( "lfxt:"+QString::number(i),lfxt.myshape(lineUP.pointAtPercent(1)+Po),true,LM->thick_blue() );
        //drawpath( "lineUP:"+QString::number(i),lineUP,true,LM->thick_green() );
        //drawpath( "lfxb:"+QString::number(i),lfxb.myshape(lineDWN.pointAtPercent(1)+Po),true,LM->thick_blue() );
        //drawpath( "lineDWN:"+QString::number(i),lineDWN,true,LM->thick_green() );
        ////

        pd = lineDWN.pointAtPercent(1);
        pu = lineUP.pointAtPercent(1);
        g_up.connectPath( lineUP );
        g_bot.connectPath( lineDWN );
        tmptmp = g_bot.length();
        if( i != GN )
        {
            ls.setPoints( pu,pd );
            if(GType==0)
            {
                QPointF p1,p2;
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                ls.setPoints( p1,p2 );
                gather_path = gathertype1( d_u,ls,ls.p1(),lastfixtop );
                g_up.connectPath(gather_path.at(0));
                //g_up.connectPath(gather_path.at(1));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path2 = gathertype1(d_d,ls,ls.p1(),lastfixbot );
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);
                g_bot.connectPath( gather_path2.at(0) );
                //g_bot.connectPath( gather_path2.at(1) );
                ///////////////
                ls.setPoints(g_up.pointAtPercent(1),g_bot.pointAtPercent(1));
                gather_path = gathertype1( d_u,ls,ls.p1(),g_up );
                g_up.connectPath(gather_path.at(0));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path = gathertype1( d_d,ls,ls.p1(),g_bot );
                g_bot.connectPath(gather_path.at(0));
                ///////////////
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);
                pu = g_up.pointAtPercent(1);
                pd = g_bot.pointAtPercent(1);
            }
            else if(GType==1)
            {
                QPointF p1,p2;
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                k2 = i+1;
                addfix = list_up.at(k2);
                while(k2<GN)
                {
                    k2++;
                    addfix.connectPath( list_up.at(k2) );
                }
                g_up = pregathertype2(g_up,addfix,d_u,-d_angle );
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);

                k2 = i+1;
                addfix = list_dwn.at(k2);
                while(k2<GN)
                {
                    k2++;
                    addfix.connectPath( list_dwn.at(k2) );
                }
                g_bot = pregathertype2(g_bot,addfix,d_d,-d_angle );
                ls.setPoints( g_up.pointAtPercent(1),g_bot.pointAtPercent(1) );
                gather_path = gathertype1( d_u,ls,ls.p1(),g_up );
                g_up.connectPath(gather_path.at(0));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path2 = gathertype1(d_d,ls,ls.p1(),g_bot );
                g_bot.connectPath( gather_path2.at(0) );
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);
                pu = g_up.pointAtPercent(1);
                pd = g_bot.pointAtPercent(1);
            }
            else
            {
                QPointF p1,p2;
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                tmpdouble = QLineF(p2,p1).angle();
                ls.setPoints( p1,p2 );
                gather_path = gathertype1( d_u,ls,ls.p1(),lastfixtop );
                g_up.connectPath(gather_path.at(0));
                //g_up.connectPath(gather_path.at(1));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path2 = gathertype1(d_d,ls,ls.p1(),lastfixbot );
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);
                g_bot.connectPath( gather_path2.at(0) );
                //g_bot.connectPath( gather_path2.at(1) );
                ///////////////
                ls.setPoints(g_up.pointAtPercent(1),g_bot.pointAtPercent(1));
                gather_path = gathertype1( d_u,ls,ls.p1(),g_up );
                g_up.connectPath(gather_path.at(0));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path = gathertype1( d_d,ls,ls.p1(),g_bot );
                g_bot.connectPath(gather_path.at(0));
                ///////////////
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                //g_bot.lineTo(p1);
                //g_bot.lineTo(p2);
                pu = g_up.pointAtPercent(1);
                pd = g_bot.pointAtPercent(1);
                //...........................
                tmpdouble = QLineF(pd,pu).angle() - tmpdouble;
                //--------------------------------------------
                //p1 = g_up.pointAtPercent(1);
                //p2 = g_bot.pointAtPercent(1);
                k2 = i+1;
                addfix = list_up.at(k2);
                while(k2<GN)
                {
                    k2++;
                    addfix.connectPath( list_up.at(k2) );
                }
                g_up = pregathertype2(g_up,addfix,d_u, -d_angle-tmpdouble );

                g_bot.lineTo(p1);
                g_bot.lineTo(p2);

                k2 = i+1;
                addfix = list_dwn.at(k2);
                while(k2<GN)
                {
                    k2++;
                    addfix.connectPath( list_dwn.at(k2) );
                }
                g_bot = pregathertype2(g_bot,addfix,d_d, -d_angle-tmpdouble );
                ls.setPoints( g_up.pointAtPercent(1),g_bot.pointAtPercent(1) );
                gather_path = gathertype1( d_u,ls,ls.p1(),g_up );
                g_up.connectPath(gather_path.at(0));
                ls.setPoints( ls.p2(),ls.p1() );
                gather_path2 = gathertype1(d_d,ls,ls.p1(),g_bot );
                g_bot.connectPath( gather_path2.at(0) );
                p1 = g_up.pointAtPercent(1);
                p2 = g_bot.pointAtPercent(1);
                g_bot.lineTo(p1);
                g_bot.lineTo(p2);
                pu = g_up.pointAtPercent(1);
                pd = g_bot.pointAtPercent(1);
            }
            if( *sign1 != -1 )
                if( tmptmp < *sign1 )
                    *sign1 = *sign1 + ( g_bot.length() - tmptmp );
            if( *sign2 != -1 )
                if( tmptmp < *sign2 )
                    *sign2 = *sign2 + ( g_bot.length() - tmptmp );
        }
        lineSTRT.setPoints( pd,pu );
    }

    line1.setPoints( pright.pointAtPercent(1),pright.pointAtPercent(0) );
    d_angle = lineSTRT.angle() - line1.angle();
    lup = C2DPath( pright,-d_angle );
    pright = lup.myshape( lineSTRT.p2() );
    QList < QPainterPath > result;
    result.append( pleft );
    result.append( g_up );
    result.append( pright );
    result.append( g_bot.toReversed() );
    return result;
}
//Цельнокроеный воротник
void C2DDress::celno_collar()
{
    QPointF centerpoint;
   // VorotDialog->changeDSPINstate( "c_0_asz",true );
   // VorotDialog->changeDSPINstate( "c_0_asp",true );
    if( D("c_0_d")==0 )
    {
        SetD("c_0_dk", 0);
        VorotDialog->SetDspinVal("c_0_dk",0);
    }
    if( D("c_0_e")==0 )
    {
        SetD("c_0_ek", 0);
        VorotDialog->SetDspinVal("c_0_ek",0);
    }
    if( D("c_0_f")==0 )
    {
        SetD("c_0_fk", 0);
        VorotDialog->SetDspinVal("c_0_fk",0);
    }

    if( D("VZ")==0 )
    {
        SetD( "c_0_asz", 0 );
        SetD( "c_0_f", 0 );
        SetD( "c_0_fk", 0 );
    }
    if( D("VP")==0 )
    {
        SetD( "c_0_asp", 0 );
        SetD( "c_0_d", 0 );
        SetD( "c_0_dk", 0 );
    }

    if( ( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0 )&&( LD("clasp_location")==0 ) )//spinka
    {
        SetD( "c_0_asz", 0 );
        SetD( "c_0_f", 0 );
        SetD( "c_0_fk", 0 );
    //    VorotDialog->changeDSPINstate( "c_0_asp",false );
       // Unicus::console( "c_0_asp>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>", D("c_0_asp") );
    }
    if( ( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0 )&&( LD("clasp_location")==1 ) )//polka
    {
   //     VorotDialog->changeDSPINstate( "c_0_asz",false );
        SetD( "c_0_asp", 0 );
        SetD( "c_0_d", 0 );
        SetD( "c_0_dk", 0 );
    }

    //"c_0_bsz""c_0_bsp""c_0_bsbsp""c_0_bsbp""c_darts","c_0_nsp""c_0_asp""c_0_nsb""c_0_asb""c_0_nsz""c_0_asz""c_0_d""c_0_e""c_0_f""c_0_dk""c_0_ek""c_0_fk"
    bool ic_c_d = true;

    if( D("is_vorot") != 1  )
        ic_c_d = false;
    if( D("vorot_type") != 0 )
        ic_c_d = false;
    //if( D("c_darts") != 0 )
    //    ic_c_d = false;
    if( D("is_mirror") == 0 )
        ic_c_d = false;
    //--------------------------------------
    if(  D("c_0_f")>D("c_0_nsz") )
    {
        VorotDialog->SetDspinVal("c_0_f", D("c_0_nsz")/10);
        SetD( "c_0_f", D("c_0_nsz") );
    }
    if(  D("c_0_e")>D("c_0_nsb") )
    {
        VorotDialog->SetDspinVal("c_0_e", D("c_0_nsb")/10);
        SetD( "c_0_e", D("c_0_nsb") );
    }
    //++++++++++
    if(  D("c_0_d")>D("c_0_nsp") )
    {
        VorotDialog->SetDspinVal("c_0_d", D("c_0_nsp")/10);
        SetD( "c_0_d", D("c_0_nsp") );
    }
    //--------------------------------------
    QPainterPath path= QPainterPath(),path2= QPainterPath(),path3=QPainterPath();
    QPainterPath path4= QPainterPath(),path5= QPainterPath(),path6=QPainterPath();
    QLineF l1,l2,l3,l4,l5;
    QPointF p1,p2,p3,p4,p5;
    double tmpdbl;
    if(ic_c_d)
    {
        p1 = P["11dialog"];
        p2 = P["Gl"];
        p3 = P["Gr"];
        p4 = P["172dialog"];

        l1.setPoints(p1, P["91'"] );
        l1.setLength(D("c_0_f")+0.0001);
        l2.setPoints(p1, p1+QPointF(0,1) );
        l2.setAngle( l2.angle()-D("c_0_asz") );
        l2.setLength( D("c_0_nsz")+0.0001 );
        l4 = l2;
        l2.setLength(l1.length());
        tmpdbl = l2.angleTo(l1)/2;
        l3.setPoints( p1,p1+QPointF(0,1) );
        l3.setAngle( l2.angle() + tmpdbl+180 );
        l3.setLength( D("c_0_fk")+0.0001 );
        path = cGeometry::splineon3points( D("c_0_f"),l1.p2(),l3.p2(),l2.p2(),p1, 0.2 );
        path.lineTo(l4.p2());
        //path.cubicTo( l3.p2(),l3.p2(),l2.p2() );
        P["c_sp"]=l1.p2();

        l1.setPoints(p2, P["pl-rtd"] );
        l1.setLength(D("c_0_e")+0.0001);
        l2.setPoints(p2, p2+QPointF(0,1) );
        l2.setAngle( l2.angle()+D("c_0_asb") );
        l2.setLength( D("c_0_nsb")+0.0001 );
        tmpdbl = l2.angleTo(l1)/2;
        l3.setPoints( p2,p2+QPointF(0,1) );
        l3.setAngle( l2.angle() + tmpdbl );
        l3.setLength( D("c_0_ek")+0.0001 );
        l5=l2;
        l2.setLength(l1.length());
        p5 = l2.p2();
        //path2.moveTo( l1.p2() );
        path2 = cGeometry::splineon3points( D("c_0_e"), l1.p2(),l3.p2(),l2.p2(),p2, 0.2 );
        path2.lineTo(l5.p2());
        //path2.cubicTo( l3.p2(),l3.p2(),l2.p2() );
        P["c_sb"]=l1.p2();

        l1.setPoints(l4.p2(),l4.p2()+QPointF(0,1));
        l2.setPoints(l5.p2(),l5.p2()+QPointF(0,1));
        l1.setAngle( (l4.angle()-90-D("c_0_bsz"))+180 );
        l2.setAngle( (l5.angle()-90+D("c_0_bsbp")) );
        l3.setPoints(l1.p1(),l2.p1());
        l1.setLength( l3.length()*0.5 );
        l2.setLength( l3.length()*0.5 );
        path3.moveTo( l1.p1() );
        path3.cubicTo( l1.p2(),l2.p2(),l2.p1() );
        P["c_L"]=l1.p1();
    }else
    {
        P["c_sp"] = QPointF(0,0);
        P["c_sb"] = QPointF(0,0);
        P["c_L"] = QPointF(0,0);
    }

    ppath(  Sync( attr( SYNC_NAME,  QString( "c_sp_s" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "c_sp" ) ),
                                          LM->thick_red() ), &path, 0, 0,
                                  ic_c_d );
    ppath(  Sync( attr( SYNC_NAME,  QString( "c_sb_s" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "c_sb" ) ),
                                          LM->thick_red() ), &path2, 0, 0,
                                  ic_c_d );
    /*bool dart = false;
    if(ic_c_d)
    {
        path3 = makedart(path3,"d1");
        if(lastdart!=QPainterPath())
            dart = true;
    }

    //ppath(  Sync( attr( SYNC_NAME,  QString( "c_L_s" ) ),
    //                                      attr( SYNC_TYPE, C2DSync::Ppath ),
    //                                      attr( SYNC_LIST, MakeList( "c_L" ) ),
    //                                      LM->thick_yellow() ), &path3, 0, 0,
    //                              ic_c_d );
    QPainterPath dart1 = lastdart;
    P["dart1"] = dart1.pointAtPercent(0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "ddart1" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "dart1" ) ),
                                          LM->thick_solid() ), &dart1, 0, 0,
                                  ic_c_d );*/

    ////правая часть
    if(ic_c_d)
    {
        //p1 = P["11dialog"];
       //p2 = P["Gl"];
       // p3 = P["Gr"];
        //p4 = P["172dialog"];

        l1.setPoints(p4, P["97"] );
        l1.setLength(D("c_0_d")+0.0001);
        l2.setPoints(p4, p4+QPointF(0,1) );
        l2.setAngle( l2.angle()+D("c_0_asp") );
        l2.setLength( D("c_0_nsp")+0.0001 );
        l4=l2;
        l2.setLength(l1.length());
        tmpdbl = l2.angleTo(l1)/2;
        l3.setPoints( p4,p4+QPointF(0,1) );
        l3.setAngle( l2.angle() + tmpdbl );
        l3.setLength( D("c_0_dk")+0.0001 );
        //path4.moveTo( l1.p2() );
        path4 = cGeometry::splineon3points( D("c_0_d"), l1.p2(),l3.p2(),l2.p2(),p4, 0.2 );
        path4.lineTo(l4.p2());
        //path4.cubicTo( l3.p2(),l3.p2(),l2.p2() );
        P["c_p"]=l1.p2();

        l1.setPoints(p3, P["pr-rtd"] );
        l1.setLength(D("c_0_e")+0.0001);
        l2.setPoints(p3, p3+QPointF(0,1) );
        l2.setAngle( l2.angle()-D("c_0_asb") );
        l2.setLength( D("c_0_nsb")+0.0001 );
        p5 = l2.p2();
        l5=l2;
        l2.setLength( l1.length() );
        tmpdbl = l2.angleTo(l1)/2;
        l3.setPoints( p3,p3+QPointF(0,1) );
        l3.setAngle( l2.angle() + tmpdbl+180 );
        l3.setLength( D("c_0_ek")+0.0001 );

        //path5.moveTo( l1.p2() );
        path5 = cGeometry::splineon3points( D("c_0_e"), l1.p2(),l3.p2(),l2.p2(),p3, 0.2 );
        path5.lineTo(p5);
        //path5.cubicTo( l3.p2(),l3.p2(),l2.p2() );
        P["c_pb"]=l1.p2();


        l1.setPoints(l4.p2(),l4.p2()+QPointF(0,1));
        l2.setPoints(l5.p2(),l5.p2()+QPointF(0,1));
        l1.setAngle( (l4.angle()-90+D("c_0_bsp")) );
        l2.setAngle( (l5.angle()-90-(180-D("c_0_bsbp"))) );
        l3.setPoints(l1.p1(),l2.p1());
        l1.setLength( l3.length()*0.5 );
        l2.setLength( l3.length()*0.5 );
        path6.moveTo( l1.p1() );
        path6.cubicTo( l1.p2(),l2.p2(),l2.p1() );
        P["c_R"]=l1.p1();
    }else
    {
        P["c_p"] = QPointF(0,0);
        P["c_pb"] = QPointF(0,0);
        P["c_R"] = QPointF(0,0);
    }

    ppath(  Sync( attr( SYNC_NAME,  QString( "c_p_s" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "c_p" ) ),
                                          LM->thick_red() ), &path4, 0, 0,
                                  ic_c_d );
    ppath(  Sync( attr( SYNC_NAME,  QString( "c_pb_s" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "c_pb" ) ),
                                          LM->thick_red() ), &path5, 0, 0,
                                  ic_c_d );
    //if(collar->ic_c_d)
    //{
    //    dart = makedartsdraw( leftendpath,"d3","d4","d_count2",true );//= makedart(leftendpath,"d1");
    //}
    //path6 = cGeometry::makedart(path6.toReversed(),D("d1_start"),D("d1_l"),D("d1_a"),D("d1_r")).toReversed();
    //ppath(  Sync( attr( SYNC_NAME,  QString( "c_R_s" ) ),
    //                                      attr( SYNC_TYPE, C2DSync::Ppath ),
    //                                      attr( SYNC_LIST, MakeList( "c_R" ) ),
    //                                      LM->thick_yellow() ), &path6, 0, 0,
    //                              ic_c_d );

    QPainterPath mirrorredline=QPainterPath();
    bool redline = false;
    P["redline"] = QPointF(0,0);
    if(ic_c_d)
    {
        path3 = makedartsdraw( path3.toReversed(),"d3","d4","d_count2",true );//= makedart(leftendpath,"d1");
        path6 = makedartsdraw( path6.toReversed(),"d1","d2","d_count",true );//= makedart(leftendpath,"d1");



        cpath["g_left_e"] = C2DPath(path3);
        cpath["g_leftm_e"] = C2DPath(path3);
        cpath["g_right_e"] = C2DPath(path6);
        cpath["g_rightm_e"] = C2DPath(path6);
        if(( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0  ))
        {
            redline = true;
            if( LD("clasp_location") == 0 ) //  спинка
            {
                mirrorredline = path2;
                l1.setPoints( path3.pointAtPercent(0),path3.pointAtPercent(1) );
            }else if( LD("clasp_location") == 1 ) //  polka
            {
                mirrorredline = path5;
                l1.setPoints( path6.pointAtPercent(0),path6.pointAtPercent(1) );
            }

            //C2DPath tmpcpath = C2DPath(mirrorredline,0,1);
            l1.setAngle( 180 - l1.angle() );
            //mirrorredline.moveTo(l1.p1());
            //mirrorredline.lineTo(l1.p2());

            P["redline"] = l1.p2();//mirrorredline.pointAtPercent(0);
        }

    }else
    {
        makedartsdraw( path3.toReversed(),"d3","d4","d_count2",true );//= makedart(leftendpath,"d1");
        makedartsdraw( path6.toReversed(),"d1","d2","d_count",true );//= makedart(leftendpath,"d1");
    }
    mirrorredline = mirrorredline.toReversed();
    ppath(  Sync( attr( SYNC_NAME,  QString( "redline" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "redline" ) ),
                                          LM->thick_red() ), &mirrorredline, 0, 1,
                                  redline );

    collar->ic_c_d = ic_c_d;
}
QList< QPainterPath > C2DDress::makedart(QPainterPath path, QString s, int k)
{
    QList< QPainterPath > result_list;
    QPainterPath gorlovina;
    if((s == "d1")||(s == "d2"))
    {
        gorlovina = cpath["g_right_e"].shape();
    }
    else if((s == "d3")||(s == "d4"))
    {
        gorlovina = cpath["g_left_e"].shape();
    }else
        gorlovina = QPainterPath();
    //if( gorlovina!=QPainterPath() )
    //    gorlovina
//    this->addVariable( C2DVariable::set( "d4_start", this->prefix() + "d4_start", "Not described",
//                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
//    this->addVariable( C2DVariable::set( "d4_a", this->prefix() + "d4_a", "Not described",
//                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
//    this->addVariable( C2DVariable::set( "d4_l", this->prefix() + "d4_l", "Not described",
//                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
//    this->addVariable( C2DVariable::set( "d4_r", this->prefix() + "d4_r", "Not described",
//                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    //path = path.toReversed();
    double strt = D(s+"_start");
Unicus::console( "strt>=path.length()***************************",path.length() );
    Unicus::console( "strt>=path.length()***************************",strt );
    if( strt>=path.length() )
    {
        strt = path.length()*0.99;
        Unicus::console( "strt>=path.length()***************************",strt );
        VorotDialog->SetDspinVal( s+"_start",strt/10 );
    }
    strt = strt/path.length();
    double a = D(s+"_a");

    double a2 = path.angleAtPercent( strt ) + (90*k);
    double l = D(s+"_l");
    double r = D(s+"_r");
    bool darts = false;
    if( (D("vorot_type") == 0)&&(D("is_vorot")==1) )
    {
        darts = true;
       // Unicus::console( "DARTS = TRUE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",D("vorot_type") );
    }
   // Unicus::console( "vorot_type >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",D("vorot_type") );
   // Unicus::console( "is_vorot >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",D("is_vorot") );
    if((r <= 0)||(l<=0)||( darts == false ))
    {
        //lastdart = QPainterPath();
        result_list.append(path);
        return result_list;//.toReversed();
    }



    double angle;
    //angle = 180/M_PI*atan( r/2/(l/2) ); // середина отрезка
    QPointF p1,p2;
    QLineF l1,l2,l3,l4,midline;


    p1 = path.pointAtPercent( strt );

    ///////////////////
    {
        QLineF dl1,dl2,dl3;
        if(p1==gorlovina.pointAtPercent(1))
            p1 = p1+QPointF(0.000,0.001);
        dl2.setPoints( p1,gorlovina.pointAtPercent(1) );
        if(p1==gorlovina.pointAtPercent(0))
            p1 = p1+QPointF(0.000,0.001);
        dl3.setPoints( p1,gorlovina.pointAtPercent(0) );
        dl1.setPoints( p1,p1+QPointF(20,20) );
        a = path.angleAtPercent( strt ) + (90*k);
        dl1.setAngle(a);
        double mina,maxa;
        if((s=="d1")||(s=="d2"))
        {
            mina = dl1.angleTo(dl2);
            maxa = dl3.angleTo(dl1);
        }else
        {
            mina = dl2.angleTo(dl1);
            maxa = dl1.angleTo(dl3);
        }
        mina = cGeometry::degrees360( mina );
        maxa = cGeometry::degrees360( maxa );

        VorotDialog->SetDspinMinMax( s+"_a",-mina,maxa );
        VorotDialog->SetDspinMinMax( s+"_a",-90,90 );
        a = VorotDialog->dspinbox[s+"_a"]->GetValue();
        Unicus::console("MIN>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",mina);
        Unicus::console("MAX>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",maxa);

        QPainterPath dp1,dp2,dp3;
        dp1.moveTo(dl1.p1());
        dp1.lineTo(dl1.p2());
        dp2.moveTo(dl2.p1());
        dp2.lineTo(dl2.p2());
        dp3.moveTo(dl3.p1());
        dp3.lineTo(dl3.p2());
        //drawpath( s+"yup1",dp1,true, LM->thick_blue() );
        //drawpath( s+"yup2",dp2,true, LM->thick_green() );
        //drawpath( s+"yup3",dp3,true, LM->thick_green() );
    }
    ////////////////////

    a = path.angleAtPercent( strt ) + (90*k) + a*k;

    l1.setPoints( p1,p1+QPointF(30,30) );
    l1.setAngle(a);
    QPainterPath dp4;
    dp4.moveTo(l1.p1());
    dp4.lineTo( l1.p2() );
    //drawpath( s+"yup4",dp4,true, LM->thick_yellow() );
    //диалоговые ограничения
    l1.setLength(l);
    //l4 = l1;
    /////находим пересечение с горловиной



    p2 = gorlovina.pointAtPercent( cGeometry::qpintrbtE( l1,gorlovina,0.5)/gorlovina.length() );
    if(l1.p1()==p2)
        p2 = p2+QPointF(0.001,0.001);
    midline.setPoints(l1.p1(),p2);
    if( l < midline.length() )
    {
        l1.setLength( midline.length() );
        VorotDialog->SetDspinMinMax( s+"_l",midline.length()/10,100 );
        VorotDialog->SetDspinMinMax( s+"_l",0,100 );
    }
    //p2 = //l1.pointAt(0.5);
    l2.setPoints( p2,p2+QPointF(1,1) );
    l2.setAngle( l1.angle()+(90*k) );
    l2.setLength( r/2 );
    l3.setPoints( l2.p2(),l2.p1() );
    l3.setLength( l3.length()*2 );
    angle = QLineF( l1.p1(),l3.p1() ).angleTo(l1);
    //p2 = Unicus::rPoint( p2,p1,-angle*2 );
    //l2.setPoints(p1,p2);

    QPainterPath lastdart = QPainterPath();
    QLineF dlineV,dlineH;
    dlineV = l1;
    dlineH = l3;
    //lastdart.moveTo( l1.p1() );
    //lastdart.lineTo( l3.p1() );
    //lastdart.lineTo( l1.p2() );
    //lastdart.lineTo( l3.p2() );
    //lastdart.lineTo( l1.p1() );
    //result_list.append( lastdart );
    l4.setPoints( l1.p1(),l3.p1() );





    C2DPath cp;
    cp = C2DPath(path);
    QPainterPath result;
    result = cp.myshapefromstart(strt);

    path = cp.takepartofpath(strt,1);
    strt = result.length();
    cp = C2DPath(path,angle*2);
    result.connectPath(cp.myshapefromstart());
    strt = strt/result.length();
    //result_list.append(result);
    cp = C2DPath(result,0);
    double slide = 10/result.length(); // радиус сглаживания
    double s_start = strt-slide;
    if(s_start<0)
        s_start = 0.001;
    double s_end = strt+slide;
    if(s_end>1)
        s_end = 0.999;
    QPainterPath tmppath;
    tmppath = cp.myshapefromstart( s_start );
    l1.setPoints(result.pointAtPercent(s_start),result.pointAtPercent(s_start)+QPointF(1,1));
    l1.setAngle(result.angleAtPercent(s_start));
    l2.setPoints( result.pointAtPercent( s_end ),result.pointAtPercent(s_end)+QPointF(1,1) );
    l2.setAngle( result.angleAtPercent(s_end)+180 );
    l3.setPoints( result.pointAtPercent(s_start ),result.pointAtPercent(s_end) );
    if(l3.length()==0)
    {
        Unicus::console( "ALARM TREVOGA ALARM TREVOGA ALARM TREVOGA ALARM TREVOGA ", D("c_0_asp") );
        return result_list;
    }
    l1.setLength(l3.length()*0.3);
    l2.setLength(l3.length()*0.3);
    QPainterPath tmppath2,tmppath3;
    tmppath2.moveTo(tmppath.pointAtPercent(1));
    tmppath2.cubicTo( l1.p2(),l2.p2(),l2.p1() );

    //result_list.append( tmppath2 );

    double intersect = cGeometry::qpintrbtD( l4, tmppath2, 0.5 );
    intersect = intersect/tmppath2.length();
    cp = C2DPath(tmppath2);
    tmppath.connectPath( cp.myshapefromstart(intersect) );
    p2 = Unicus::rPoint( tmppath2.pointAtPercent(intersect),p1,-angle*2);
    /////////вытачка
    lastdart.moveTo( tmppath2.pointAtPercent(intersect) );
    lastdart.lineTo( dlineH.p1() );
    lastdart.lineTo( dlineV.p2() );
    lastdart.lineTo( dlineH.p2() );
    lastdart.lineTo( p2 );
    result_list.append( lastdart );

    ///вытачка


    tmppath3 = cp.takepartofpath( intersect,1 );
    cp = C2DPath( tmppath3,-angle*2 );
    tmppath3 = cp.myshape( p2 );
    cp = C2DPath( result );
    tmppath2 = cp.takepartofpath(s_end,1  );
    cp = C2DPath( tmppath2,-angle*2 );
    tmppath3.connectPath( cp.myshape(tmppath3.pointAtPercent(1)) );

    dpath1 = tmppath;
    dpath2 = tmppath3;

    //tmppath.connectPath(tmppath3);
    result_list.append( tmppath );

    result_list.append( tmppath3 );
    return result_list;//.toReversed();
}
QPainterPath C2DDress::makedartsdraw(QPainterPath path, QString d1, QString d2, QString count, bool draw )
{
    int k;

    if(d1 == "d1")
    {

        k = -1;
    }
    else if(d1 == "d3")
    {

        k  = 1;
    }
    else
        k = 0;


    QList< QPainterPath > plist,plist2;
    QList< QPainterPath > dart_list;
    QPainterPath tmppath,path2;
    path2 = QPainterPath();
    plist = makedart(path.toReversed(),d1,k);
    if(plist.isEmpty()==false)
        if(plist.count()>1)
        {
            dart_list.append( plist.at(0) );
            path2 = plist.at(1);
        }
        else
            path2 = plist.at(0);
    if((plist.isEmpty()==false)&&( D(count)==1 ))
    {
        tmppath = plist.takeLast();

        plist2 = makedart( tmppath,d2,k );

        if(plist2.isEmpty()==false)
            if( plist2.count()>1 )
            {
                dart_list.append( plist2.at(0) );
                path2.connectPath(plist2.at(plist2.count()-2));
                path2.connectPath(plist2.at(plist2.count()-1));
            }else
                path2.connectPath(plist2.at(0));
        plist.append( plist2 );
    }else
        if(plist.count()>1)
           path2.connectPath( plist.at(plist.count()-1) );

    bool mirror = false;
    if( LD("is_clasp") == 1 )
        if( LD("clasp_form") != 0 )
            if( LD("clasp_location") <= 1 )
            {
                if( (d1 == "d1") && (LD("clasp_location")==1 ))
                    mirror = true;
                if( (d1 == "d3") && (LD("clasp_location")==0 ))
                    mirror = true;
            }

    QPointF mirrorp;
    if( (LD("clasp_location") == 0) && (d1 == "d3") && (mirror) )
        mirrorp = P["11dialog"];

    if( (LD("clasp_location") == 1) && (d1 == "d1") && (mirror) )
        mirrorp = P["172dialog"];

    draw = drawqpathqlist( d1+d2,dart_list,mirror,mirrorp );

    //P[d1+d1] = gorlovina.pointAtPercent(0);
    //ppath(  Sync( attr( SYNC_NAME,  QString( d1+d1 ) ),
    //                                      attr( SYNC_TYPE, C2DSync::Ppath ),
    //                                      attr( SYNC_LIST, MakeList( d1+d1 ) ),
    //                                      LM->thick_red() ), &gorlovina, 0, 0,
    //                              true );
    return path2;
}
bool C2DDress::drawqpathqlist( QString name, QList< QPainterPath > list, bool mirror, QPointF mp )
{
    bool draw,result;
    if(list.isEmpty())
        result = false;
    else
        result = true;
    QPainterPath path[6];
    QString tmpname;
    int i;
    for(i=0;i<6;i++)
    {
        tmpname = name + ":" + QString::number(i);
        if( list.isEmpty()== false )
        {
            path[i] = list.takeFirst();
            draw = true;
            P[tmpname] = path[i].pointAtPercent(0);
        }
        else
        {
            path[i] = QPainterPath();
            draw = false;
            P[tmpname] = QPointF(0,0);
        }

        ppath(  Sync( attr( SYNC_NAME,  QString( tmpname ) ),
                                              attr( SYNC_TYPE, C2DSync::Ppath ),
                                              attr( SYNC_LIST, MakeList( tmpname ) ),
                                              LM->thick_red() ), &path[i], 0, 0,
                                      draw );
        //////////mirror/////
        P[tmpname + "_m"]= QPointF(mp.x()+(mp.x()-P[tmpname].x()),P[tmpname].y());
        ppath(  Sync( attr( SYNC_NAME,  QString( tmpname + "_m" ) ),
                                              attr( SYNC_TYPE, C2DSync::Ppath ),
                                              attr( SYNC_LIST, MakeList( tmpname + "_m" ) ),
                                              LM->thick_red() ), &path[i], 0, 1,
                                      draw && mirror );
        //Unicus::console( "MIRROR->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>",mirror );
    }
    return result;
}
void C2DDress::signP( QString name, QPointF p1,double angle, bool dual, bool draw )
{
    double H = 5;
    double W = 5;
    QPainterPath path=QPainterPath();
    if(draw)
    {
        QLineF l1,l2;
        l1.setPoints( p1, p1 + QPointF(1,1));
        l1.setAngle(angle);
        l1.setLength(H);
        path.moveTo(l1.p1());
        path.lineTo( l1.p2() );
        l2.setPoints( l1.p2(),l1.p1() );
        l2.setAngle(l2.angle()+90);
        l2.setLength(W/2);
        path.lineTo( l2.p2() );
        l2.setAngle(l2.angle()+180);
        path.lineTo(l2.p2());
        path.lineTo(l2.p1());
        path.lineTo(p1);
    }
    P[name] = p1;
    ppath(  Sync( attr( SYNC_NAME,  QString( name ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( name ) ),
                                          LM->thick_solid() ), &path, 0, 0,
                                  draw  );
}
void C2DDress::drawpath( QString s, QPainterPath path, bool draw, C2DLayer * L )
{
    P[s] = path.pointAtPercent(0);
    ppath(  Sync( attr( SYNC_NAME,  QString( s ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( s ) ),
                                          L ), &path, 0, 0,
                                  draw  );
}
void C2DDress::drawline( QString name, QString p1, QString p2, bool draw, C2DLayer * L )
{
    line( Sync( attr( SYNC_NAME,  QString( name ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( p1, p2 ) ),
                    L ),
              draw );
}
void C2DDress::checkgathersvalues( double lup, QString A1, QString B1, QString C1, QString N, double GType )
{
    double tmpdouble;

    if( LD(A1)>lup-5 )
    {
        H(A1) = lup-5;
        gathers->SetDspinVal( A1, LD(A1)/10 );
    }

    tmpdouble = LD(A1) + ( LD(B1) * (D(N)-1) );
    if( tmpdouble > lup-5 )
    {
        H( B1 ) = ( lup - LD(A1)-5 )/(D(N)-1);
        gathers->SetDspinVal( B1, LD(B1)/10 );
    }

    if( GType==0 )
    {
        Unicus::console( "CHECK->A TYPE0" , LD(A1) );
        tmpdouble = LD(A1);
        if( D(N) > 1 )
            if( LD(B1)<tmpdouble )
                tmpdouble = LD(B1);

        Unicus::console( "CHECK->tmpdbl TYPE0" , tmpdouble );
        if((LD(C1)/2)>tmpdouble)
        {
            //H(C1) = tmpdouble*2;
            //gathers->SetDspinVal( C1,LD(C1)/10 );
            //H(C1) = gathers->GetDspinVal( C1 )*10;
        }
    }else if( GType == 1 )
    {
        tmpdouble = LD(B1)*(D(N)-1) ;
        Unicus::console( "CHECK->A TYPE1" , tmpdouble );
        tmpdouble = (lup - LD(A1)) - tmpdouble;
        if( D(N) > 1 )
            if( LD(B1)<tmpdouble )
                tmpdouble = LD(B1);
        Unicus::console( "CHECK->tmpdbl TYPE1" , tmpdouble );
        if((LD(C1)/2)>tmpdouble)
        {
            //H(C1) = tmpdouble*2;
            //gathers->SetDspinVal( C1,LD(C1)/10 );
            //H(C1) = gathers->GetDspinVal( C1 )*10;
        }
    }else
    {
        tmpdouble = (lup - LD(A1) - LD(B1)*(D(N)-1)) ;
        if( D(N) > 1 )
            if( LD(B1)<tmpdouble )
                tmpdouble = LD(B1);

        if( tmpdouble>LD(A1) )
            tmpdouble = LD(A1);

        if(LD(C1)/4>tmpdouble)
        {
            //H(C1) = tmpdouble*4;
            //gathers->SetDspinVal( C1,LD(C1)/10 );
        }
    }
}
