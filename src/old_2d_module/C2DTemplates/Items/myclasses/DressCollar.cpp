#include "DressCollar.h"
#include "cGeometry.h"
DressCollar::DressCollar():Elasticas::PropertiesDialog( QObject::trUtf8("Застежка"),"Dress:")
{
    firstchangegorlo = true;
    lengths[1] = 1000;

    this->commonValue("Sm3:Default") = 0;
    this->commonValue("Sm4:Default") = 0;

    this->commonValue("z4:Default") = 1;
    this->commonValue("z5:Default") = 1;
    this->commonValue("Sm:Default") = 0;
    this->commonValue("z7:Default") = 0;
    this->commonValue("z6:Default") = 1;
    this->commonValue("z10:Default") = 0;
    this->commonValue("Sh1:Default") = 1.5f;
    this->commonValue("Sh3:Default") = 1.2f;
    this->commonValue("L1:Default") = 30.0f;
    this->commonValue("N:Default") = 4;
    this->commonValue("R1:Default") = 1.5f;
    this->commonValue("R2:Default") = 6;

    this->commonValue("p6:Default") = 3;
    this->commonValue("p7:Default") = 4;
    this->commonValue("p8:Default") = 1.5f;
    this->commonValue("p9:Default") = 6;

    this->commonValue("cutL:Default") = 8;

    ////defaults end
    QString items1[]={trUtf8("На полочке"),trUtf8("На спинке"),trUtf8("В плечевом шве"),NULL};
    QString items2[]={trUtf8("Потайная"),trUtf8("Открытая"),trUtf8("Застежка-планка"),NULL};
    QString items3[]={trUtf8("На полочке"),trUtf8("На спинке"),trUtf8("В плечевом шве"),
                      trUtf8("В центральном шве"),trUtf8("В рельефе"),NULL};
    Elasticas::CheckBoxProperty* c1=this->AddCheckBoxProperty(trUtf8("<b>Застежка</b>"),"z1",false);
    //is_clasp = c1;
    Elasticas::CheckBoxProperty* c2=this->AddCheckBoxProperty(trUtf8("Проходит через горловину"),"z2");
    combobox["c3"]=this->AddComboBoxProperty(trUtf8("Расположение"),items1,"z3");
    this->memwid[2] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии застежки по линии горловины, см"),"Sm3",0.1f,-10,10);
    this->memwid[6] =this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии застежки по линии талии, см"),"Sm4",0.1f,-10,10);
    //this->commonValue("z6:Default") = 1;
    combobox["z6"] = this->AddComboBoxProperty(trUtf8("Вид застежки"),items2,"z6");

    QString items4[]={trUtf8("Застежка на молнию"),trUtf8("Застежка на пуговицы"),trUtf8("Застежка на ленту велькро"),
                      trUtf8("Застежка на кнопки"),trUtf8("Застежка на навесные петли"),NULL};
    combobox["z10"]=this->AddComboBoxProperty(trUtf8("Тип застегивающих элементов"),items4,"z10");
    Elasticas::CheckBoxProperty* decor=this->AddCheckBoxProperty(trUtf8("Оформление по перпендикуляру"),"decor");
    this->memwid[3]=this->AddDoubleSpinBoxProperty(trUtf8("Ширина молнии, см"),"Sh3",0.1f,0,10000);
    this->memwid[1]=this->AddDoubleSpinBoxProperty(trUtf8("Длина молнии, см"),"L1",0.1f,1,1000);
    this->memwid[0]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от горловины до начала молнии, см"),"R4",0.1f,0,1000);
    //Elasticas::DoubleSpinBoxProperty* p5=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от линии низа до конца молнии, см"),"R5",0.1f,-10,10);
    QString items5[]={trUtf8("Встык"),trUtf8("С заходом"),NULL};
    combobox["p101"]=this->AddComboBoxProperty(trUtf8(" "),items5,"p101");
    this->memwid[4]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края борта до л. полузаноса, см"),"Sh1",0.1f,0,10000);
    ispinbox["N"]=this->AddSpinBoxProperty(trUtf8("Количество пуговиц/кнопок, см"),"N",1,0,25);
    dspinbox["R1"]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от горловины до первой пуговицы, см"),"R1",0.1f,0,100);
    dspinbox["R2"]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между пуговицами, см"),"R2",0.1f,0.5,100);

    this->memwid[5]=this->AddDoubleSpinBoxProperty(trUtf8("Ширина планки, см"),"p6",0.1f,0,10000);
    ispinbox["p7"]=this->AddSpinBoxProperty(trUtf8("Количество пуговиц/кнопок, см"),"p7",1,0,25);
    dspinbox["p8"]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от горловины до первой пуговицы, см"),"p8",0.1f,0,100);
    dspinbox["p9"]=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между пуговицами, см"),"p9",0.1f,1,100);

    Elasticas::CheckBoxProperty* c7=this->AddCheckBoxProperty(trUtf8("<b>Разрез/вырез</b>"),"z7",false);
    Elasticas::ComboBoxProperty* c8=this->AddComboBoxProperty(trUtf8("Расположение"),items3,"z8");
    combobox["c_c8"] = c8;
    Elasticas::DoubleSpinBoxProperty* c9=this->AddDoubleSpinBoxProperty(trUtf8("Длина разреза, см"),"cutL",0.5f,0,40);
    Elasticas::DoubleSpinBoxProperty* c10=this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии относительно центра, см"),"Sm",0.1f,-10,10);
    dspinbox["c_c10"] = c10;
    Elasticas::DoubleSpinBoxProperty* c11=this->AddDoubleSpinBoxProperty(trUtf8("Направление, град"),"cut_a",1,-360,360);
    c2->AddCondition(new Elasticas::CheckBoxCondition(c1,true));
    combobox["c3"]->AddCondition(new Elasticas::CheckBoxCondition(c1,true));
    this->memwid[2]->AddCondition(new Elasticas::CheckBoxCondition(c1,true));
    this->memwid[6]->AddCondition(new Elasticas::CheckBoxCondition(c1,true));
    combobox["z6"]->AddCondition(new Elasticas::CheckBoxCondition(c1,true));

    combobox["c3"]->AddCondition(new Elasticas::CheckBoxCondition(c2,true));
    this->memwid[2]->AddCondition(new Elasticas::CheckBoxCondition(c2,true));
    this->memwid[6]->AddCondition(new Elasticas::CheckBoxCondition(c2,true));

    this->memwid[2]->AddCondition(new Elasticas::ComboBoxCondition(combobox["c3"],0));
    this->memwid[6]->AddCondition(new Elasticas::ComboBoxCondition(combobox["c3"],0));
    this->memwid[2]->AddCondition(new Elasticas::ComboBoxCondition(combobox["c3"],1),Elasticas::OperationOr);
    this->memwid[6]->AddCondition(new Elasticas::ComboBoxCondition(combobox["c3"],1),Elasticas::OperationOr);

    combobox["z10"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],1));
    this->memwid[3]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],1));
    this->memwid[1]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],1));
    this->memwid[0]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],1));
    //p5->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],1));

    this->memwid[5]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],2));
    ispinbox["p7"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],2));
    dspinbox["p8"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],2));
    dspinbox["p9"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z6"],2));

    this->memwid[3]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],0));
    this->memwid[1]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],0));
    this->memwid[0]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],0));
    //p5->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],0));
    decor->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],1));
    decor->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],2),Elasticas::OperationOr);
    decor->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],3),Elasticas::OperationOr);
    decor->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],4),Elasticas::OperationOr);
    decor->AddCondition(new Elasticas::ComboBoxCondition(combobox["p101"],1),Elasticas::OperationAnd);

    this->memwid[4]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],1));
    ispinbox["N"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],1));
    dspinbox["R1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],1));
    dspinbox["R2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],1));
    this->memwid[4]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],2),Elasticas::OperationOr);
    ispinbox["N"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],2),Elasticas::OperationOr);
    dspinbox["R1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],2),Elasticas::OperationOr);
    dspinbox["R2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],2),Elasticas::OperationOr);
    this->memwid[4]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],3),Elasticas::OperationOr);
    ispinbox["N"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],3),Elasticas::OperationOr);
    dspinbox["R1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],3),Elasticas::OperationOr);
    dspinbox["R2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],3),Elasticas::OperationOr);
    ispinbox["N"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],4),Elasticas::OperationOr);
    dspinbox["R1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],4),Elasticas::OperationOr);
    dspinbox["R2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],4),Elasticas::OperationOr);
    combobox["p101"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["z10"],4));

    this->memwid[4]->AddCondition(new Elasticas::ComboBoxCondition(combobox["p101"],1),Elasticas::OperationOr);

    c8->AddCondition(new Elasticas::CheckBoxCondition(c7,true));
    c9->AddCondition(new Elasticas::CheckBoxCondition(c7,true));
    c10->AddCondition(new Elasticas::ComboBoxCondition(c8,0));
    c10->AddCondition(new Elasticas::ComboBoxCondition(c8,1),Elasticas::OperationOr);
    c10->AddCondition(new Elasticas::CheckBoxCondition(c7,true),Elasticas::OperationAnd);
    c11->AddCondition(new Elasticas::ComboBoxCondition(c8,0));
    c11->AddCondition(new Elasticas::ComboBoxCondition(c8,1),Elasticas::OperationOr);
    c11->AddCondition(new Elasticas::CheckBoxCondition(c7,true),Elasticas::OperationAnd);
    //Elasticas::ComboBoxProperty* cbp1=this->AddComboBoxProperty(trUtf8("Воротник"),items1,"rnd1");
    //Elasticas::ComboBoxProperty* cbp2=this->AddComboBoxProperty(trUtf8("Форма"),items2,"z7");
    //cbp2->AddCondition(new Elasticas::CheckBoxCondition(c1,true));
    //cbp2->AddCondition(new Elasticas::ComboBoxCondition(cbp1,2),Elasticas::OperationOr);
    //dsp1=this->AddDoubleSpinBoxProperty("sdsd","sdsd6",0.1,0);
    //Elasticas::CheckBoxProperty* cbp3=this->AddCheckBoxProperty(trUtf8("Воротник"),"rnd1");
    QObject::connect(this->memwid[0],SIGNAL(onChanged()),this,SLOT(changeZipperR4()));
    QObject::connect(this->memwid[1],SIGNAL(onChanged()),this,SLOT(changeZipperL1()));

    QObject::connect(this->ispinbox["N"],SIGNAL(onChanged()),this,SLOT(changebuttonsR1N()));
    QObject::connect(this->dspinbox["R1"],SIGNAL(onChanged()),this,SLOT(changebuttonsR1N()));
    QObject::connect(this->dspinbox["R2"],SIGNAL(onChanged()),this,SLOT(changebuttonsR2()));

    QObject::connect(this->ispinbox["p7"],SIGNAL(onChanged()),this,SLOT(changePlankap7p8()));
    QObject::connect(this->dspinbox["p8"],SIGNAL(onChanged()),this,SLOT(changePlankap7p8()));
    QObject::connect(this->dspinbox["p9"],SIGNAL(onChanged()),this,SLOT(changePlankap9()));

    QObject::connect(combobox["c3"],SIGNAL(onChanged()),this,SLOT(changeLocation()));

    QObject::connect(this->dspinbox["c_c10"],SIGNAL(onChanged()),this,SLOT(cut_position()));
    QObject::connect(this->combobox["z10"],SIGNAL(onChanged()),this,SLOT(clasp_elements_type()));
    QObject::connect( c1,SIGNAL(onChanged()),this,SLOT(clasp_on())       );
//    QObject::connect(combobox["c3"],SIGNAL(onChanged()),this,SLOT(changeGorlo()));

}

void DressCollar::setFoo(double v1)
{
    this->memwid[1]->SetMinMax( 1,v1 );
    //dsp1->SetMinMax(0,value);
}
void DressCollar::setSpinminmax(int i, double min, double max)
{
    this->memwid[i]->SetMinMax( min,max );
}
void DressCollar::setSpinValue(int i, double val)
{
    this->memwid[i]->ReadVariantValue( val );
}
void DressCollar::changeZipperR4()
{
    this->memwid[1]->disconnect();
    //memwid[1] - L1
    //memwid[0] - R4
    this->memwid[0]->SetMinMax( 0, (this->lengths[1]/10)-1);
    double tmpdouble = (this->lengths[1]/10)-this->memwid[0]->GetValue();
    if(tmpdouble<1)
        tmpdouble = 1;
    this->memwid[1]->SetMinMax( 1, tmpdouble );
    this->memwid[1]->SetMinMax( 1, 99999);
    this->memwid[0]->SetMinMax( 0, 99999);
    QObject::connect(this->memwid[1],SIGNAL(onChanged()),this,SLOT(changeZipperL1()));
}
void DressCollar::changeZipperL1()
{
    this->memwid[0]->disconnect();
    //memwid[1] - L1
    //memwid[0] - R4
    this->memwid[1]->SetMinMax( 1, (this->lengths[1]/10));
    double tmpdouble = (this->lengths[1]/10)-this->memwid[1]->GetValue();
    if(tmpdouble<0)
        tmpdouble = 0;
    this->memwid[0]->SetMinMax( 0, tmpdouble );
    this->memwid[0]->SetMinMax( 0, 99999);
    this->memwid[1]->SetMinMax( 1, 99999);
    QObject::connect(this->memwid[0],SIGNAL(onChanged()),this,SLOT(changeZipperR4()));
}
void DressCollar::changebuttonsR1N()
{
    this->changeButtons();
}
void DressCollar::changebuttonsR2()
{
    this->dspinbox["R1"]->disconnect();
    int n;
    n = ispinbox["N"]->GetValue();
    if(n<=1)
        return;
    dspinbox["R2"]->SetMinMax( 1, ((this->lengths[1]/10))/(n-1) );
    if(dspinbox["R1"]->GetValue()>0)
    {
        double tmpdouble = (this->lengths[1]/10)-(dspinbox["R2"]->GetValue()*(n-1)) ;
        if( tmpdouble<0 )
            tmpdouble = 0;
        dspinbox["R1"]->SetMinMax( 0,tmpdouble );
    }
    //dspinbox["R2"]->SetMinMax( 1, ((this->lengths[1]/10)-dspinbox["R1"]->GetValue())/(n-1) );
    dspinbox["R1"]->SetMinMax( 0, this->lengths[1]/10 );
    QObject::connect(this->dspinbox["R1"],SIGNAL(onChanged()),this,SLOT(changebuttonsR1N()));
}
void DressCollar::changeButtons()
{
    this->dspinbox["R2"]->disconnect();
    int n;
    n = ispinbox["N"]->GetValue();
    if(n == 0)
           n++;

    dspinbox["R2"]->SetMinMax( 1, ((this->lengths[1]/10)-dspinbox["R1"]->GetValue())/(n-1) );
    dspinbox["R1"]->SetMinMax( 0, this->lengths[1]/10 );
    double tmpdouble;
    if ( (dspinbox["R2"]->GetValue() *( n-1 ))+dspinbox["R1"]->GetValue() > this->lengths[1]/10 )
    {
        if(( dspinbox["R2"]->GetValue()>1 ))
        {
            tmpdouble = dspinbox["R2"]->GetValue() - 0.1f;
            if( tmpdouble<1 )
                tmpdouble = 1;
            dspinbox["R2"]->SetMinMax( 1,tmpdouble );
        }else
        {
            tmpdouble = dspinbox["R1"]->GetValue() - 0.1f;
            if( tmpdouble<0 )
                tmpdouble = 0;
            dspinbox["R1"]->SetMinMax( 0,tmpdouble );
        }
    }
    dspinbox["R2"]->SetMinMax( 1, (this->lengths[1]/10)/(n-1) );
    dspinbox["R1"]->SetMinMax( 0, this->lengths[1]/10 );
    QObject::connect(this->dspinbox["R2"],SIGNAL(onChanged()),this,SLOT(changebuttonsR2()));
}
void DressCollar::changePlankap9()
{
    this->dspinbox["p8"]->disconnect();
    int n;
    n = ispinbox["p7"]->GetValue();
    if(n<=1)
        return;
    dspinbox["p9"]->SetMinMax( 1, ((this->lengths[1]/10))/(n-1) );
    if(dspinbox["p8"]->GetValue()>0)
    {
        double tmpdouble = (this->lengths[1]/10)-(dspinbox["p9"]->GetValue()*(n-1)) ;
        if( tmpdouble<0 )
            tmpdouble = 0;
        dspinbox["p8"]->SetMinMax( 0,tmpdouble );
    }

    dspinbox["p8"]->SetMinMax( 0, this->lengths[1]/10 );
    QObject::connect(this->dspinbox["p8"],SIGNAL(onChanged()),this,SLOT(changePlankap7p8()));
}
void DressCollar::changePlankap7p8()
{
    this->dspinbox["p9"]->disconnect();
    int n;
    n = ispinbox["p7"]->GetValue();
    if(n == 0)
           n++;

    dspinbox["p9"]->SetMinMax( 1, ((this->lengths[1]/10)-dspinbox["p8"]->GetValue())/(n-1) );
    dspinbox["p8"]->SetMinMax( 0, this->lengths[1]/10 );
    double tmpdouble;
    if ( (dspinbox["p9"]->GetValue() *( n-1 ))+dspinbox["p8"]->GetValue() > this->lengths[1]/10 )
    {
        if(( dspinbox["p9"]->GetValue()>1 ))
        {
            tmpdouble = dspinbox["p9"]->GetValue() - 0.1f;
            if( tmpdouble<1 )
                tmpdouble = 1;
            dspinbox["p9"]->SetMinMax( 1,tmpdouble );
        }else
        {
            tmpdouble = dspinbox["p8"]->GetValue() - 0.1f;
            if( tmpdouble<0 )
                tmpdouble = 0;
            dspinbox["p8"]->SetMinMax( 0,tmpdouble );
        }
    }
    dspinbox["p9"]->SetMinMax( 1, (this->lengths[1]/10)/(n-1) );
    dspinbox["p8"]->SetMinMax( 0, this->lengths[1]/10 );
    QObject::connect(this->dspinbox["p9"],SIGNAL(onChanged()),this,SLOT(changePlankap9()));
}
void DressCollar::changeLocation()
{
    int i = combobox["c3"]->GetCurrentId();
    if( i == 1 )
    {
        this->addqpath( "g_minus", qpath["g_l_minus"] );
        this->addqpath( "g_plus", qpath["g_l_plus"] );
        this->setlength( 2 , lengths[10] );
        this->setlength( 3 , lengths[11] );
    }
    else if( i == 0 )
    {
        this->addqpath( "g_minus", qpath["g_r_minus"] );
        this->addqpath( "g_plus", qpath["g_r_plus"] );
        this->setlength( 2 , lengths[12] );
        this->setlength( 3 , lengths[13] );
    }
    this->changeGorlo();
}

void DressCollar::changeGorlo()
{
    //if(firstchangegorlo)
   // {
        //firstchangegorlo = false;
   //     return;
   // }
    //double max;
    //if( this->lengths[6] < this->lengths[7] )
    //    max = this->lengths[6];
    //else
    //    max = this->lengths[7];

    Unicus::console( "qpath[g_minus].length()",qpath["g_minus"].length() );
    Unicus::console( "qpath[g_plus].length()",qpath["g_plus"].length() );
    this->memwid[2]->SetMinMax( -qpath["g_minus"].length()/10+0.2,qpath["g_plus"].length()/10-0.2 );
    this->memwid[5]->SetMinMax(0,9999);
    this->memwid[4]->SetMinMax(0,9999);
    this->memwid[3]->SetMinMax(0,9999);
    double lminus,lplus;
    int id=-1;
    lplus = 0;
    lminus=0;
    if( combobox["z6"]->GetCurrentId() == 1 )
    {
        if( combobox["z10"]->GetCurrentId() == 0 )
        {
            lminus = -this->memwid[3]->GetValue()/2;
            lplus = this->memwid[3]->GetValue()/2;
            //this->memwid[3]->SetMinMax(0,max*2);
            id=3;
        }else if( (combobox["z10"]->GetCurrentId() == 1)||
                  (combobox["z10"]->GetCurrentId() == 2)||
                  (combobox["z10"]->GetCurrentId() == 3) )
        {
            lplus = this->memwid[4]->GetValue();
            //this->memwid[4]->SetMinMax(0,this->lengths[7]);
            id=4;
        }else if( combobox["z10"]->GetCurrentId() == 4 )
        {
            if( combobox["p101"]->GetCurrentId() == 1 )
            {
                //lminus = -this->memwid[4]->GetValue()/2;
                lplus = this->memwid[4]->GetValue();
                //this->memwid[4]->SetMinMax(0,max);
                id=4;
            }
        }
    }else if( combobox["z6"]->GetCurrentId() == 2 )
    {
        lminus = -this->memwid[5]->GetValue()/2;
        lplus = this->memwid[5]->GetValue()/2;
        //this->memwid[5]->SetMinMax(0,max*2);
        id=5;
    }
    if( (lminus==0) && (lplus==0) )
    {
        return;
    }
    lminus = lminus * 10;
    lplus = lplus * 10;
    //this->memwid[2]->SetMinMax( -(this->lengths[3]/10), (this->lengths[2]/10) );
    QPainterPath gorlo,gorlo2;
    gorlo = qpath["g_minus"];
    gorlo.connectPath( qpath["g_plus"] );
    QLineF line,line1;
    line.setPoints( gorlo.pointAtPercent(
        (qpath["g_minus"].length()+( this->memwid[2]->GetValue()*10 ))/gorlo.length() ),
                    QPointF( lengths[2]+(this->memwid[6]->GetValue()*10), lengths[3] ));

    double l=0,minx=32000,maxx=-32000;
    double lengthleft,lengthright;
    QPointF tmppoint;
    /******************************************/
    //определяем границы лево-право для диалоога
    C2DPath pppp = C2DPath(gorlo,line.angle()-90);
    QPainterPath mypath;
    mypath = pppp.myshapefromstart();
    QPointF center = mypath.pointAtPercent( qpath["g_minus"].length()/mypath.length() );
    while(l<mypath.length())
    {
        tmppoint = mypath.pointAtPercent( l/mypath.length() );
        if(minx > tmppoint.x())
            minx = tmppoint.x();
        if(maxx < tmppoint.x())
            maxx = tmppoint.x();
        l = l + 2;
    }
    double cwidth = maxx-minx-4;
    if( this->memwid[id]->GetValue()*10 > cwidth )
    {
        this->memwid[id]->SetMinMax(0,cwidth/10);
        return;
    }

    double lmin,lmax;
    //if( !((lminus != 0 ) && (lplus != 0))  )
    {
        if( lminus!=0 )
        {
            QLineF line3;
            line3.setPoints( line.p1(),line.p1()+QPointF(1,1) );
            line3.setAngle( line.angle() - 90 );
            line3.setLength( lminus-2 );
            line1.setPoints( line3.p2(),line3.p2()+QPointF(1,1));
            //line1.setPoints( line.p1()+QPointF( lminus,0 ),line.p1()+QPointF( lminus,1 ) );
            line1.setAngle( line.angle() );
            lmin = cGeometry::qpintrbtD( line1, gorlo, 0.2 );

            if( lmin==0 )
            {
                if( cwidth-1 > this->memwid[id]->GetValue()*10 )
                    this->memwid[2]->SetMinMax( memwid[2]->GetValue()+0.1,qpath["g_plus"].length()/10-0.2 );
                else
                {
                    lmin = memwid[id]->GetValue()-0.1;
                    if(lmin < 0)
                        lmin=0;
                    this->memwid[id]->SetMinMax(0,lmin);
                }
                //this->memwid[2]->SetMinMax( memwid[2]->GetValue()+0.1,qpath["g_plus"].length()/10-0.2 );
            }
            clasp_pmin = lmin;

        }
        if( lplus!=0 )
        {
            QLineF line3;
            line3.setPoints( line.p1(),line.p1()+QPointF(1,1) );
            line3.setAngle( line.angle() - 90 );
            line3.setLength( lplus+2 );
            line1.setPoints( line3.p2(),line3.p2()+QPointF(1,1));
            //line1.setPoints( line.p1()+QPointF( lplus,0 ),line.p1()+QPointF( lplus,1 ) );
            line1.setAngle( line.angle() );
            lmax = cGeometry::qpintrbtD( line1, gorlo, 0.2 );
            if( lmax==0 )
            {
                Unicus::console( "cwidth", cwidth );
                Unicus::console( "memwid[id]", this->memwid[id]->GetValue()*10 );
                if( cwidth-1 > this->memwid[id]->GetValue()*10 )
                    this->memwid[2]->SetMinMax( -qpath["g_minus"].length()/10+0.2,memwid[2]->GetValue()-0.1 );
                else
                {
                    lmax = memwid[id]->GetValue()-0.1;
                    if(lmax < 0)
                        lmax=0;
                    this->memwid[id]->SetMinMax(0,lmax);
                    //this->memwid[2]->SetMinMax( -qpath["g_minus"].length()/10+0.2,memwid[2]->GetValue()-0.1 );
                }
            }
            clasp_pmax = lmax;
        }
    }



}

void DressCollar::setlength( int i, double l )
{
    this->lengths[i] = l;
}
void DressCollar::addqpath( QString s, QPainterPath p )
{
    this->qpath[s] = p;
}
void DressCollar::addqline( QString s, QLineF l )
{
    this->qline[s] = l;
}
double DressCollar::memwidValue( int i )
{
    return this->memwid[i]->GetValue();
}
void DressCollar::SetDspinMinMax( QString name, double min, double max )
{
    this->dspinbox[name]->SetMinMax( min,max );
}
void DressCollar::cut_position()
{
    if( combobox["c_c8"]->GetCurrentId() > 1 )
        return;

    dspinbox["c_c10"]->disconnect();

    double min,max;
    if( combobox["c_c8"]->GetCurrentId() == 0 )
    {
        min = qpath["g_r_minus"].length();
        max = qpath["g_r_plus"].length();
    }else if( combobox["c_c8"]->GetCurrentId() == 1 )
    {
        min = qpath["g_l_minus"].length();
        max = qpath["g_l_plus"].length();
    }
    //if(ic_c_d)
    //    if( (is_clasp==false) )//||
        //    ( combobox["z6"]->GetCurrentId()!=0 ) ||
        //    ( combobox["c3"]->GetCurrentId()!=combobox["c_c8"]->GetCurrentId() ) )
    //                max = 0;

    this->SetDspinMinMax( "c_c10",-min/10,max/10 );
    QObject::connect(this->dspinbox["c_c10"],SIGNAL(onChanged()),this,SLOT(cut_position()));
}
void DressCollar::clasp_elements_type()
{
    if( this->combobox["z10"]->GetCurrentId() != 4 )
        this->memwid[4]->GetLabel()->setText( trUtf8("Расстояние от края борта до л. полузаноса, см") );
    else
        this->memwid[4]->GetLabel()->setText( trUtf8("Ширина захода сторон друг на друга, см") );
}
void DressCollar::clasp_on()
{
    QObject::connect(this->memwid[3],SIGNAL(onChanged()),this,SLOT(changeGorlo()));
    QObject::connect(this->memwid[2],SIGNAL(onChanged()),this,SLOT(changeGorlo()));
    QObject::connect(this->memwid[6],SIGNAL(onChanged()),this,SLOT(changeGorlo()));
    QObject::connect(this->memwid[4],SIGNAL(onChanged()),this,SLOT(changeGorlo()));
    QObject::connect(this->memwid[5],SIGNAL(onChanged()),this,SLOT(changeGorlo()));
}
