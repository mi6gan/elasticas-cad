#include "C2DDress.h"
NewDressDialog::NewDressDialog():Elasticas::DockDialog(trUtf8("Горловина0"),"Dress:")
{
    QVBoxLayout * layout=new QVBoxLayout;
    this->setLayout(layout);
    layout->addWidget(new QLabel("SomeLabel"));
    layout->addWidget(this->top_dialog_button_box);
    //layout->addWidget(this->bottom_dialog_button_box);
}

void NewDressDialog::apply()
{
    this->commonValue("G45")=45;
    Elasticas::DockDialog::apply();
}

C2DDress::C2DDress() : C2DItem()
{
    ifg=0;
    this->setPrefix( "Dress" );
    this->requiredVariables();
    this->addDialog( new C2DDressDialog( QObject::trUtf8( "Поправочные коэффициенты" ), this->prefix(), QObject::trUtf8("Параметры БК") ,
        QPair< QString, double> ( QObject::trUtf8( "см" ), 10.0f ), NULL ) );
    this->addElDialog(  collar = new DressCollar(  ),QObject::trUtf8("Параметры МК"));
    this->addElDialog( dress_gorlovina = new DressGorlovina,QObject::trUtf8("Параметры МК"));
    this->addElDialog( VorotDialog = new DressVorotDialog,QObject::trUtf8("Параметры МК"));
    this->addElDialog(  gline = new DressGLine(),QObject::trUtf8("Параметры МК"));
    this->addElDialog(  VorotDecor = new DressVorotDecor,QObject::trUtf8("Параметры МК"));
    this->addElDialog(  equidistant = new DressEquidistant,QObject::trUtf8("Параметры МК"));
    this->addElDialog( gathers = new DressGathers,QObject::trUtf8("Параметры МК") );
    this->addElDialog( elsleeve = new SleeveElDialog,QObject::trUtf8("Рукав") );

    // collar->blockSignals(true);
    //collar->combobox["z6"]->SetCurrentSelection(1);
   // collar->blockSignals(false);
    collar->firstchangegorlo = true;

    zipper = 0;
    cut = 0;
    colclasptype = 0;
    simple = false;
    vorot_planka_b = false;
    vorot_planka_sign = false;
    vorot_planka_sign_double = 0;
    vorotnik_type = 0;clasp_sign3_start=0;clasp_sign4_start=0;
    /*Sleeve*/
    this->SleeverequiredVariables();
    //c2dsleeve = new C2DSleeve();
}

void C2DDress::Update()
{
    gorl = 0;
    gorlm = 0;
    gorr = 0;
    gorrm = 0;
    collar_clasp_gl = 0;
    collar_clasp_gr = 0;
    vorot_planka_b = false;
    vorot_planka_sign = false;
    vorot_planka_sign_double = 0;
    qDebug() << this->prefix() << "::" << "Update() started;";
    this->setVariables();
    this->UpdatePoints();
    this->DrawOnWidget();



    if( D("is_mirror") == 1 )
        VorotDialog->changelabel("alert",false);
    else
        VorotDialog->changelabel("alert",true,QObject::trUtf8("Горловина несимметрична."));
    if(D("vorot_dsgn")==0)
        gathers->showlabel( "alert", false );
    else
        gathers->showlabel( "alert", true );
    this->CollarGetValues();
    if( (D("is_vorot")==1)&&(D("vorot_type")==1) )
    {
        if( ((LD("is_cut")==1)&&(LD("cut_location")<=1)  ) || ( (LD("is_clasp")==1)&&(LD("clasp_form")!=0) ) )
        {
            if(((LD("is_cut")==0)||(LD("cut_location")>1))&&( LD("clasp_location")>1 ))
            {
                VorotDecor->showlabel("alert",true);
                VorotDecor->changelabel( "alert", QObject::trUtf8("Не активно для застежки в плечевом шве.") );
                is_vorotdecor = false;
            }
            else if(  ( D("Arut")==1 )||( D("Ardt")==1 )||( D("Alut")==1 )||( D("Aldt")==1 )  )
            {
                VorotDecor->showlabel("alert",true);
                VorotDecor->changelabel( "alert", QObject::trUtf8("Не активно для оформленных концов стойки") );
                is_vorotdecor = false;
            }
            else
            {
                VorotDecor->showlabel("alert",false);
                is_vorotdecor = true;
            }
        }
        else
        {
            if( LD("is_clasp")==1 )
                VorotDecor->changelabel( "alert", QObject::trUtf8("Не активно при потайной застежке без разреза") );
            else
            {
                if( (LD("is_cut")==1)&&(LD("cut_location")>1) )
                    VorotDecor->changelabel(  "alert", QObject::trUtf8("Не активно для разреза в данном месте") );
                else
                    VorotDecor->changelabel(  "alert", QObject::trUtf8("Не активно до выбора застежки/разреза") );
            }
            VorotDecor->showlabel("alert",true);
            is_vorotdecor = false;
        }
    }else
    {
        VorotDecor->changelabel(  "alert", QObject::trUtf8("Требуется воротник как самостоятельный элемент") );
        VorotDecor->showlabel("alert",true);
        is_vorotdecor = false;
    }
    this->MakeCollar();
    bool is_collar = B("is_vorot");
    this->DrawCollar( is_collar );

    if((D("is_vorot")==1)&&(D("vorot_type")==0))
    {
        collar->setmemwidLabel(0,QObject::trUtf8("Расстояние от верхнего края воротника до начала молнии, см"));
        collar->setDspinLabel("R1",QObject::trUtf8("Расстояние от верхнего края воротника до первой пуговицы, см"));
        collar->setDspinLabel("p8",QObject::trUtf8("Расстояние от верхнего края воротника до первой пуговицы, см"));
    }else
    {
        collar->setmemwidLabel(0,QObject::trUtf8("Расстояние от горловины до начала молнии, см"));
        collar->setDspinLabel("R1",QObject::trUtf8("Расстояние от горловины до первой пуговицы, см"));
        collar->setDspinLabel("p8",QObject::trUtf8("Расстояние от горловины до первой пуговицы, см"));
    }
    bool sleeve = true;
    if(sleeve)
    {
        this->SleeveUpdate();
    }
}

void C2DDress::requiredVariables()
{
    this->addVariable( C2DVariable::set( "PTx", this->prefix() + "PTx",
                       "Not described", C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f ) );
    this->addVariable( C2DVariable::set( "PTy", this->prefix() + "PTy", "Not describedd",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 0.01f  ) );
    this->addVariable( C2DVariable::set( "T13", this->prefix() + "T13", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T15", this->prefix() + "T15", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T29", this->prefix() + "T29", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
  //  this->addVariable( C2DVariable::set( "T16", "T16", "Not described", C2DVariable::Metrics,
  //                     C2DVariable::General, 1000.0f, 0.5*10.0f ) );

    this->addVariable( C2DVariable::set( "T18", this->prefix() + "T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 5.0f ) );

    this->addVariable( C2DVariable::set( "T19", this->prefix() + "T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 5.0f ) );

    this->addVariable( C2DVariable::set( "T31", this->prefix() + "T31", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T34", this->prefix() + "T34", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T35", this->prefix() + "T35", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T36", this->prefix() + "T36", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T39", this->prefix() + "T39", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T40", this->prefix() + "T40", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T41", this->prefix() + "T41", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 10.0f ) );


    this->addVariable( C2DVariable::set( "T43", this->prefix() + "T43", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "T45", this->prefix() + "T45", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T45'", this->prefix() + "T45'", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T46", this->prefix() + "T46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T47", this->prefix() + "T47", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T57", this->prefix() + "T57", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T70", this->prefix() + "T70", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T76", this->prefix() + "T76", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );


  //  this->addVariable( "Y", C2DVariable::set( "P200", "P200", "Not described", C2DVariable::Metrics,
    //                                            C2DVariable::General, 20.0f ) );

   // this->addVariable( "P18", C2DVariable::set( "P18", this->prefix() + "P18", "Not described",
   //                                               C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
   // this->addVariable( "P19", C2DVariable::set( "P19", this->prefix() + "P19", "Not described",
   //                                               C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    //Back Dart parameters
   // this->addVariable( "B:K0", C2DVariable::set( "B:K0", "B:K0", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 0.3f, 10.0f ) );
   // this->addVariable( "B:K1", C2DVariable::set( "B:K1", "B:K1", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 5.0f, 10.0f ) );
   // this->addVariable( "B:K2", C2DVariable::set( "B:K2", "B:K2", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 120.0f, 10.0f ) );
   // this->addVariable( "B:K3", C2DVariable::set( "B:K3", "B:K3", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 25.0f, 10.0f ) );

    //Front Dart parameters
   // this->addVariable( "F:K0", C2DVariable::set( "F:K0", "F:K0", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 0.3f, 10.0f ) );
   // this->addVariable( "F:K1", C2DVariable::set( "F:K1", "F:K1", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 1.0f, 10.0f ) );
   // this->addVariable( "F:K2", C2DVariable::set( "F:K2", "F:K2", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 100.0f, 10.0f ) );
   // this->addVariable( "F:K3", C2DVariable::set( "F:K3", "F:K3", "Not described", C2DVariable::Metrics,
   //                                                C2DVariable::General, 20.0f, 10.0f ) );

    //Dress parameters
    /***********Ш
   // this->addVariable( "Kadd6", C2DVariable::set( "Kadd6", "Kadd6", "Not described",
                                                    C2DVariable::Metrics, C2DVariable::General, 0.6f, 10.0f ) );
      this->addVariable( "Pshpr", C2DVariable::set( "Pshpr", "Pshpr", "Not described",
                                                    C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( "Pv.p.k", C2DVariable::set( "Pv.p.k.", "Pv.p.k", "Not described",
                                                     C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    ****************/
    this->addVariable( C2DVariable::set( "PT13", this->prefix() + "PT13", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT15", this->prefix() + "PT15", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT18", this->prefix() + "PT18", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT19", this->prefix() + "PT19", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT29", this->prefix() + "PT29", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT31", this->prefix() + "PT31", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT34", this->prefix() + "PT34", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT35", this->prefix() + "PT35", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT36", this->prefix() + "PT36", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT39", this->prefix() + "PT39", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT40", this->prefix() + "PT40", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT41", this->prefix() + "PT41", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT43", this->prefix() + "PT43", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT45", this->prefix() + "PT45", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );


    this->addVariable( C2DVariable::set( "PT45'", this->prefix() + "PT45'", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT46", this->prefix() + "PT46", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT47", this->prefix() + "PT47", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT57", this->prefix() + "PT57", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT70", this->prefix() + "PT70", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "PT76", this->prefix() + "PT76", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Pdtp", "Pdtp", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );


    this->addVariable( C2DVariable::set( "SideSeamShift", this->prefix() + "A2", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

/***ДИАЛОГИ***/
    this->addVariable( C2DVariable::set( "K0", this->prefix() + "K0", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K1", this->prefix() + "K1", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K2", this->prefix() + "K2", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K3", this->prefix() + "K3", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K4", this->prefix() + "K4", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K5", this->prefix() + "K5", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K6", this->prefix() + "K6", "Not described",
                       C2DVariable::Metrics, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "K7", this->prefix() + "K7", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "Pspr", this->prefix() + "Pspr", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K8", this->prefix() + "K8", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "K11", this->prefix() + "K11", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K31", this->prefix() + "K31", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K41", this->prefix() + "K41", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K51", this->prefix() + "K51", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K91", this->prefix() + "K91", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );


    this->addVariable( C2DVariable::set( "K01", this->prefix() + "K01", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K02", this->prefix() + "K02", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K03", this->prefix() + "K03", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "K36", this->prefix() + "K36", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
////Наташа
    this->addVariable( C2DVariable::set( "Rg1", this->prefix() + "Rg1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Rg2", this->prefix() + "Rg2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Rg3", this->prefix() + "Rg3", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Rg3m", this->prefix() + "Rg3m", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Smpl1", this->prefix() + "Smpl1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Smpl2", this->prefix() + "Smpl2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Smpl1m", this->prefix() + "Smpl1m", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Smpl2m", this->prefix() + "Smpl2m", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Sh1", this->prefix() + "Sh1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Sh2", this->prefix() + "Sh2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Sh3", this->prefix() + "Sh3", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Sh4", this->prefix() + "Sh4", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "N", this->prefix() + "N", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "R1", this->prefix() + "R1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "R2", this->prefix() + "R2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "L1", this->prefix() + "L1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "R4", this->prefix() + "R4", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "z1", this->prefix() + "z1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z2", this->prefix() + "z2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z3", this->prefix() + "z3", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z6", this->prefix() + "z6", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z10", this->prefix() + "z10", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "p101", this->prefix() + "p101", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z7", this->prefix() + "z7", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "z8", this->prefix() + "z8", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "decor", this->prefix() + "decor", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "p6", this->prefix() + "p6", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "p7", this->prefix() + "p7", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "p8", this->prefix() + "p8", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "p9", this->prefix() + "p9", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "Sm", this->prefix() + "Sm", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Sm3", this->prefix() + "Sm3", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Sm4", this->prefix() + "Sm4", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "cutL", this->prefix() + "cutL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "cut_a", this->prefix() + "cut_a", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "is_vorot", this->prefix() + "is_vorot", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "is_mirror", this->prefix() + "is_mirror", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
   // gline->setmirror(D("is_mirror"));
    //////////////////////////////////////////
    this->addVariable( C2DVariable::set( "Gchange", this->prefix() + "Gchange", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "gssA", this->prefix() + "gssA", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "gpsA", this->prefix() + "gpsA", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "nat1", this->prefix() + "nat1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "nat2", this->prefix() + "nat2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->takegpoints();

    ////Воротник
    this->addVariable( C2DVariable::set( "vorot_type", this->prefix() + "vorot_type", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "vorot_form", this->prefix() + "vorot_form", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "vorot_dsgn", this->prefix() + "vorot_dsgn", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "stoika_krai", this->prefix() + "stoika_krai", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "stoika_dsgn", this->prefix() + "stoika_dsgn", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "skd_type", this->prefix() + "skd_type", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    /////////////////////////////////////////////////////////////////////////////////////////
    this->addVariable( C2DVariable::set( "H1", this->prefix() + "H1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "H2", this->prefix() + "H2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "H3", this->prefix() + "H3", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "H1lev", this->prefix() + "H1lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "H2lev", this->prefix() + "H2lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "H3lev", this->prefix() + "H3lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Pos1", this->prefix() + "Pos1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Pos2", this->prefix() + "Pos2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Pos1lev", this->prefix() + "Pos1lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "Pos2lev", this->prefix() + "Pos2lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "A", this->prefix() + "A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "AL", this->prefix() + "AL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "vorot_planka", this->prefix() + "vorot_planka", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    ////vorotnik razvedenie
    this->addVariable( C2DVariable::set( "v_r_sN", this->prefix() + "v_r_sN", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "v_r_pN", this->prefix() + "v_r_pN", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "v_r_puL", this->prefix() + "v_r_puL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "v_r_suL", this->prefix() + "v_r_suL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "v_r_pdL", this->prefix() + "v_r_pdL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "v_r_sdL", this->prefix() + "v_r_sdL", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    //vorotnik_razvedenie END
    this->addVariable( C2DVariable::set( "OYsp", this->prefix() + "OYsp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "OYspa", this->prefix() + "OYspa", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "OYsh", this->prefix() + "OYsh", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "OYsha", this->prefix() + "OYsha", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "OYpo", this->prefix() + "OYpo", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "OYpoa", this->prefix() + "OYpoa", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
//vorotdecor
    this->addVariable( C2DVariable::set( "vd_hN", this->prefix() + "vd_hN", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "vd_vN", this->prefix() + "vd_vN", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "vd_v", this->prefix() + "vd_v", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "vd_d", this->prefix() + "vd_d", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "vd_p", this->prefix() + "vd_p", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "vd_s", this->prefix() + "vd_s", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "vd_p_lev", this->prefix() + "vd_p_lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "vd_s_lev", this->prefix() + "vd_s_lev", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
//equidistant
    this->addVariable( C2DVariable::set( "1:A", this->prefix() + "1:A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "2:A", this->prefix() + "2:A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "3:A", this->prefix() + "3:A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "4:A", this->prefix() + "4:A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "5:A", this->prefix() + "5:A", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "L:OX", this->prefix() + "L:OX", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10 ) );
    this->addVariable( C2DVariable::set( "R:OX", this->prefix() + "R:OX", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10 ) );
//gathers
    this->addVariable( C2DVariable::set( "G:N", this->prefix() + "G:N", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "G:A1", this->prefix() + "G:A1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:A2", this->prefix() + "G:A2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:B1", this->prefix() + "G:B1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:B2", this->prefix() + "G:B2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:C1", this->prefix() + "G:C1", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:C2", this->prefix() + "G:C2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:Type", this->prefix() + "G:Type", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    ///////////////////
    this->addVariable( C2DVariable::set( "G:N:l", this->prefix() + "G:N:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "G:A1:l", this->prefix() + "G:A1:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:A2:l", this->prefix() + "G:A2:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:B1:l", this->prefix() + "G:B1:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:B2:l", this->prefix() + "G:B2:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:C1:l", this->prefix() + "G:C1:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:C2:l", this->prefix() + "G:C2:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "G:Type:l", this->prefix() + "G:Type:l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
//цельнокроеный форотник
    //без вытачек
    this->addVariable( C2DVariable::set( "c_0_bsz", this->prefix() + "c_0_bsz", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "c_0_bsp", this->prefix() + "c_0_bsp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "c_0_bsbsp", this->prefix() + "c_0_bsbsp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "c_0_bsbp", this->prefix() + "c_0_bsbp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "c_darts", this->prefix() + "c_darts", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "c_0_asp", this->prefix() + "c_0_asp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "c_0_asb", this->prefix() + "c_0_asb", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "c_0_asz", this->prefix() + "c_0_asz", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );


    this->addVariable( C2DVariable::set( "c_0_nsp", this->prefix() + "c_0_nsp", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_nsb", this->prefix() + "c_0_nsb", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_nsz", this->prefix() + "c_0_nsz", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_d", this->prefix() + "c_0_d", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_e", this->prefix() + "c_0_e", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_f", this->prefix() + "c_0_f", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_dk", this->prefix() + "c_0_dk", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "c_0_ek", this->prefix() + "c_0_ek", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "c_0_fk", this->prefix() + "c_0_fk", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "VZ", this->prefix() + "VZ", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "VB", this->prefix() + "VB", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "VP", this->prefix() + "VP", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "d_count", this->prefix() + "d_count", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d_count2", this->prefix() + "d_count2", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d1_start", this->prefix() + "d1_start", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d1_a", this->prefix() + "d1_a", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d1_l", this->prefix() + "d1_l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d1_r", this->prefix() + "d1_r", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d2_start", this->prefix() + "d2_start", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d2_a", this->prefix() + "d2_a", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d2_l", this->prefix() + "d2_l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d2_r", this->prefix() + "d2_r", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d3_start", this->prefix() + "d3_start", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d3_a", this->prefix() + "d3_a", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d3_l", this->prefix() + "d3_l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d3_r", this->prefix() + "d3_r", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d4_start", this->prefix() + "d4_start", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d4_a", this->prefix() + "d4_a", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "d4_l", this->prefix() + "d4_l", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
    this->addVariable( C2DVariable::set( "d4_r", this->prefix() + "d4_r", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );

}
void C2DDress::takegpoints()
{
    QStringList s;
    s << "gsp" << "gspm" << "gpp" << "gppm";

    for(int j=0;j<s.count();j++)
    {
        this->addVariable( C2DVariable::set( s[j]+"count", this->prefix() + s[j]+"count", "Not described",
                       C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( s[j]+"AA", this->prefix() + s[j]+"AA", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( s[j]+"AB", this->prefix() + s[j]+"AB", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( s[j]+"AS", this->prefix() + s[j]+"AS", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        this->addVariable( C2DVariable::set( s[j]+"AS1", this->prefix() + s[j]+"AS1", "Not described",
                           C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        for( int i=0;i<2;i++ )
        {
            this->addVariable( C2DVariable::set( s[j]+QString::number(i)+"L", this->prefix() + s[j]+QString::number(i)+"L", "Not described",
                               C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
            this->addVariable( C2DVariable::set( s[j]+QString::number(i)+"T", this->prefix() + s[j]+QString::number(i)+"T", "Not described",
                               C2DVariable::Unitless, C2DVariable::General, 0.0f, 10.0f ) );
            this->addVariable( C2DVariable::set( s[j]+QString::number(i)+"A", this->prefix() + s[j]+QString::number(i)+"A", "Not described",
                               C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
            this->addVariable( C2DVariable::set( s[j]+QString::number(i)+"A2", this->prefix() + s[j]+QString::number(i)+"A2", "Not described",
                               C2DVariable::Unitless, C2DVariable::General, 0.0f, 1.0f ) );
        }
    }
}

void C2DDress::setVariables()
{
    H("G:A1") = D("G:A1");
    H("G:A2") = D("G:A2");
    H("G:B1") = D("G:B1");
    H("G:B2") = D("G:B2");
    H("G:C1") = D("G:C1");
    H("G:C2") = D("G:C2");

    H("G:A1:l") = D("G:A1:l");
    H("G:A2:l") = D("G:A2:l");
    H("G:B1:l") = D("G:B1:l");
    H("G:B2:l") = D("G:B2:l");
    H("G:C1:l") = D("G:C1:l");
    H("G:C2:l") = D("G:C2:l");

    Unicus::console("K7 ||",D("K7"));
    H( "Tx" ) = ( 1.0f + D( "PTx" ) );
    H( "Ty" ) = ( 1.0f + D( "PTy" ) );
    H( "Pdi" ) = 0.0f;

    H( "T31" ) = D("T31")+D("PT31");
    H( "T34" ) = D("T34")+D("PT34");
    H( "T35" ) = D("T35")+D("PT35");
    H( "T36" ) = D("T36")+D("PT36");
    //39norm
    H( "T40" ) = D("T40")+D("PT40");
    H( "T41" ) = D("T41")+D("PT41");
    H( "T43" ) = D("T43")+D("PT43");
    H( "T45" ) = D("T45")+D("PT45");
    H( "T45'" ) = D("T45'")+D("PT45'");
    //H( "T45'" ) = 139.05f;
    H( "T46" ) = D("T46")+D("PT46");
    H( "T47" ) = D("T47")+D("PT47");
    H( "T57" ) = D("T57")+D("PT57");
    H( "T70" ) = D("T70")+D("PT70");
    H( "T76" ) = D("T76")+D("PT76");

    H( "Pdts" ) = -5.0f;
    H( "Pvpk" ) = -5.0f;
    H( "Pspr" ) = 35; //Горизонталь основания проймы
    H( "Pshpr" ) = 0.0f;

    H("PT15") = D("PT15");
    H( "Width" ) = LD("T47") + LD("T57") + LD("T45") + 20.0f + 20.0f + LD("PT15");
//    Unicus::console( "K8", D("K8")  );
/*    H( "K0", 20.0f );
    H( "K1" ) = 0.0f;//Направление вытачки
    H( "K2" ) = 70.0f;//22-124
    H( "K3" ) = 25.0f;//Шаг 26. 20-30
    H( "K4" ) = 0.0f;//Шаг 32. 0-8
    H( "K5" ) = 10.0f;//Шаг 38. 5-15
    H( "K6" ) = 0.5f;//Шаг 41.
    H( "Pspr" ) = 35.0f;//Шаг 47. K65
    H( "K7" ) = 0.35f;//Шаг 61. 0.25-0.5
    H( "K8" ) = 30.0f;//Шаг 75. -20-50
*/
    H( "K11" ) = D("K11");//Шаг
    H( "K31" ) = D("K31");//Шаг
    H( "K41" ) = D("K41");//Шаг
    H( "K51" ) = D("K51");//Шаг
    H( "K91" ) = D("K91");//Шаг
/*
H( "K01" ) = 5.0f;//Шаг9
H( "K02" ) = 10.0f;//Шаг10
H( "K03" ) = 5.0f;//Шаг15
H( "K36" ) = 15.0f;//вытачка 36


    /*************/
    H( "T35'" ) = LD("T35") - LD("T76");
    H("T35''") = LD("T35") - LD("T34");
    H("T61") = LD("T36") - LD("T76");
    H("Kadd6") = 0.6f;
    /*Параметры вытачек*/
    H("D:LT") = 120.0f;
    H("D:LB") = 120.0f;

    H("D:RT") = 100.0f;
    H("D:RB") = 80.0f;


    if( D("z3") == 0 )
        H("clasp_location") = 1;
    else if( D("z3") == 1 )
        H("clasp_location") = 0;
    else
        H("clasp_location") = 2;

    if( LD("clasp_location")==2 )
    {
        collar->setmemwidValue( 3,0 );
        collar->setmemwidValue( 4,0 );
        collar->setmemwidValue( 5,0 );
    }
    //H("clasp_type") = -1; //тип застежки 0-пуговицы 1-молния 2-навесные петли
    switch( I("z10") )
    {
        case( 0 ):
            H("clasp_type") = 1;
        break;
        case( 1 ):
            H("clasp_type") = 0;
        break;
        case( 2 ):
            H("clasp_type") = 0;
        break;
        case( 3 ):
            H("clasp_type") = 0;
        break;
        case( 4 ):
            H("clasp_type") = 2;
        break;
    }

    ///Диалоги, Наташа
    H("Gchange") = D("Gchange");
    //Unicus::console( "Gchange",LD("Gchange") );

    H("ProimaBalance") = D("Smpl2");     //Пройма
    H("GorlovinaBalance") = D("Smpl1");     //Горловина

    H("ProimaBalance_m") = D("Smpl2m");     //Пройма
    H("GorlovinaBalance_m") = D("Smpl1m");     //Горловина
    H("ProimaShag") = 1.0f;        //Шаг по сплайну
    H("GorlovinaShag") = 1;        //Шаг по сплайну

    H("rasshir_gorloviny_spinka") = D("Rg2"); //расширение горловины спинка
    H("rasshirenie_gorloviny_plecho") = D("Rg3"); //расширение горловины у плеча
    H("rasshir_gorloviny_polochka") = D("Rg1"); //расширение горловины полочка

    H("rasshir_gorloviny_spinka_m") = D("Rg2"); //расширение горловины спинка mirror
    H("rasshirenie_gorloviny_plecho_m") = D("Rg3m"); //расширение горловины у плеча mirror RG4
    H("rasshir_gorloviny_polochka_m") = D("Rg1"); //расширение горловины полочка mirror
    /////////
    if(B("z1")==true)
        H("is_clasp") = 1; //есть ли застежка
    else    H("is_clasp") = 0; //есть ли застежка
    Unicus::console( "Zastejka",LD("is_clasp") );
    if(B("z2")==true)
        H("is_intersect_gorlovina") = 1; //проходит ли через горловину
    else    H("is_intersect_gorlovina") = 0; //проходит ли через горловину
    //H("clasp_location") = 1; //расположение спинка = 0 полочка =1
    H("clasp_move_by_gorlovina") = D("Sm3"); //смещение
    H("clasp_move_by_niz") = D("Sm4"); //смещение

    if(B("z7")==true)
        H("is_cut") = 1; //есть ли разрез
    else H("is_cut") = 0; //есть ли разрез

    if(D("z8")==0)
    {
        H("cut_location") = 1; // 0спинка или 1полочка
        H("cut_angle") = 90 - D("cut_a"); // направление
    }
    else if(D("z8")==1)
    {
        H("cut_location") = 0; // 0спинка или 1полочка
        H("cut_angle") = (90 - D("cut_a"))+180; // направление
    }
    else if(D("z8")>=2)
        H("cut_location") = D("z8"); // 0спинка или 1полочка
    H("cut_left") = -D("Sm"); // положительное напправо
    H("cut_length") = D("cutL"); // длина


    H("clasp_decor") = D("decor");//1 гладко 0 - перпендикуляр
    H("clasp_form") = D("z6"); //вид застежки 0-потайная 1-не потайная 2-застежка планка
    //if( LD("is_clasp") == 0 )
    //    H("clasp_form") = 0;

    //H("clasp_type") = 1; //тип застежки 0-пуговицы 1-молния 2-навесные петли
    if(D("p101")==0)
        H("hanging_loop") = 1; // навесные петли 0-с заходом 1-в стык
    else    H("hanging_loop") = 0; // навесные петли 0-с заходом 1-в стык
    //type 0
    H("clasp_t0_width") = D("Sh1");//10; //ширина заноса SH1
    H("clasp_t0_btns_num") = D("N"); //количество пуговиц
    H("clasp_t0_begining") = D("R1"); //расстояние от горловины до первой пуговицы
    H("clasp_t0_l_between") = D("R2"); //расстояние между пуговицами

    //type 1
    H("clasp_t1_width") = D("Sh3"); //ширина молнии SH3
    H("clasp_t1_length") = D("L1"); //длина молнии L1
    H("clasp_t1_begining") = D("R4"); //расстояние от горловины до молнии R4
    //type 2
    H("clasp_t2_width") = D("Sh1"); //ширина заноса SH1
    H("clasp_t2_btns_num") = D("N"); //количество пуговиц
    H("clasp_t2_begining") = D("R1"); //расстояние от горловины до первой пуговицы
    H("clasp_t2_l_between") = D("R2"); //расстояние между пуговицами
    //type 3
    H("clasp_t3_width") = D("p6"); //ширина заноса SH4 планки
    H("clasp_t3_btns_num") = D("p7"); //количество пуговиц для планки
    H("clasp_t3_begining") = D("p8"); //расстояние от горловины до первой пуговицы на планке
    H("clasp_t3_l_between") = D("p9"); //расстояние между пуговицами    планки
///горловина
    H("g_p_double_angle") = D("gppAS"); //сопряжение углом 0-нет 1-да ;  ; p = полочка
    H("g_p_double_angle1") = D("gppAS1"); //сопряжение углом 0-нет 1-да ;  ; p = полочка
    H("g_p_alpha") = +180 + ( D("gppAA") );  //172dialog
    if(D("nat1"))
        H("g_p_beta") = -D("gppAB");   //16diaolg
    else
    {
        if(LD("Gchange")==2)
        {
            H("g_p_beta") = -D("gppAB");
            H("g_pm_beta") = -D("gppAB")+180;
        }else
        {
            H("g_p_beta") = 0;
        }
    }
    H("g_p_point_count") = D("gppcount");
    H("g_p_p1_left") = -1 * ( D("gpp0L") );
    H("g_p_p1_top") = D("gpp0T");
    H("g_p_p1_angle1") = D("gpp0A");
    H("g_p_p1_angle2") = D("gpp0A2");
    H("g_p_p2_left") = D("gpp1L");
    H("g_p_p2_top") = D("gpp1T");
    H("g_p_p2_angle1") = D("gpp1A");
    H("g_p_p2_angle2") = D("gpp1A2");
    ///горловина
    if( D("is_mirror") == 1 )
        H("g_p_nomirror") = false;
    else
        H("g_p_nomirror") = true; //false если зеркалка

    H("g_pm_double_angle") = D("gppmAS"); //сопряжение углом 0-нет 1-да ;  ; p = полочка
    H("g_pm_double_angle1") = D("gppmAS1"); //сопряжение углом 0-нет 1-да ;  ; p = полочка
        if(D("gpsA")==false)
            H("g_pm_alpha") = -LD("g_p_alpha")+180;
        else
            H("g_pm_alpha") = + ( D("gppmAA") );  //172dialog

        if(D("nat2"))
            H("g_pm_beta") = -D("gppmAB");   //16diaolg
        else
            if( LD("Gchange") != 2 )
                H("g_pm_beta") = 0;
            else
            {
                H("g_pm_beta") = -D("gppmAB");
                H("g_sm_beta") = -D("gppmAB");
            }
        if(LD("g_p_point_count") == 0)
            H("g_p_alpha") = ( D("gppAA") );
        H("g_pm_point_count") = D("gppmcount");
        if(LD("g_pm_point_count") != 0)
            H("g_pm_alpha") = LD("g_pm_alpha")+180;
        H("g_pm_p1_left") = -1 * ( D("gppm0L") );
        H("g_pm_p1_top") = D("gppm0T");
        H("g_pm_p1_angle1") = D("gppm0A");
        H("g_pm_p1_angle2") = D("gppm0A2");
        H("g_pm_p2_left") = D("gppm1L");
        H("g_pm_p2_top") = -D("gppm1T");
        H("g_pm_p2_angle1") = D("gppm1A");
        H("g_pm_p2_angle2") = D("gppm1A2");
///горловина спинка
    H("g_s_double_angle") = D("gspAS"); //сопряжение углом 0-нет 1-да ;  ; s = спинка
    H("g_s_double_angle1") = D("gspAS1"); //сопряжение углом 0-нет 1-да ;  ; p = полочка
    H("g_s_alpha") = -0 - ( D("gspAA") );  //172dialog
    if(D("nat1"))
        H("g_s_beta") = (-1) * D("gspAB");   //16diaolg
    else
        if(LD("Gchange")!=2)
            H("g_s_beta") = 0;
        else
            H("g_s_beta") = LD("g_p_beta");

    H("g_s_point_count") = D("gspcount");
    H("g_s_p1_left") = -1 * ( D("gsp0L") );
    H("g_s_p1_top") = (-1) * D("gsp0T");
    H("g_s_p1_angle1") = (-1) * D("gsp0A");
    H("g_s_p1_angle2") = (-1) * D("gsp0A2");
    H("g_s_p2_left") = D("gsp1L");
    H("g_s_p2_top") = (-1) * D("gsp1T");
    H("g_s_p2_angle1") = (-1) * D("gsp1A");
    H("g_s_p2_angle2") = (-1) * D("gsp1A2");
    ///горловина спинка
        H("g_sm_double_angle") = D("gspmAS"); //сопряжение углом 0-нет 1-да ;  ; s = спинка
        H("g_sm_double_angle1") = D("gspmAS1"); //сопряжение углом 0-нет 1-да ;  ; s = спинка

        if(D("gssA")==false)
            H("g_sm_alpha") = -( LD("g_s_alpha") );  //172dialog
        else
            H("g_sm_alpha") = -0 - ( D("gspmAA") );  //172dialog
        if(D("nat2"))
            H("g_sm_beta") = (-1) * D("gspmAB");   //16diaolg
        else
            if(LD("Gchange")!=2)
                H("g_sm_beta") = 0;
           // else
               // H("g_sm_beta") = LD("g_pm_beta");
        H("g_sm_point_count") = D("gspmcount");
        H("g_sm_p1_left") = -1 * ( D("gspm0L") );
        H("g_sm_p1_top") = (-1) * D("gspm0T");
        H("g_sm_p1_angle1") = (-1) * D("gspm0A");
        H("g_sm_p1_angle2") = (-1) * D("gspm0A2");
        H("g_sm_p2_left") = D("gspm1L");
        H("g_sm_p2_top") = (-1) * D("gspm1T");
        H("g_sm_p2_angle1") = (-1) * D("gspm1A");
        H("g_sm_p2_angle2") = (-1) * D("gspm1A2");
//////////////
       // H("clasp_move_by_gorlovina") = collar->memwidValue(2)*10;

        if( D("VZ")==0 )
        {
            H( "K11" ) = 0;//Шаг
            H( "K31" ) = 0;//Шаг
            H( "K41" ) = 0;//Шаг
            H( "K51" ) = 0;//Шаг
            H( "K91" ) = 0;//Шаг
        }
    if( LD("is_clasp") == 1 )
    {
        if( LD("is_intersect_gorlovina") == 1 )
        {
            if( LD("clasp_location") == 0 )
            {
                H("clasp_move_by_gorlovina") = -LD("clasp_move_by_gorlovina"); //смещение
                //H("clasp_move_by_niz") = LD("clasp_move_by_niz"); //смещение
               //Смещаем верх из точки спинки
                H( "K11" ) = 0;//Шаг
                H( "K31" ) = 0;//Шаг
                H( "K41" ) = 0;//Шаг
                H( "K51" ) = 0;//Шаг
                H( "K91" ) = 0;//Шаг
                H("clasp_t0_width") = -LD("clasp_t0_width");
                H("clasp_t2_width") = -LD("clasp_t2_width");
               // H("clasp_move_by_gorlovina") = 30;
               // H("clasp_move_by_niz") = 10;
            }else if( LD("clasp_location") == 1 )
            {
                //Смещаем верх из точки полочки
                //H("clasp_move_by_gorlovina") = 10;
                //H("clasp_move_by_niz") = 10;
            }else
            {
                // работаем с линией плечевого среза;
            }


            //if( LD("") )
        }
    }
    if( LD("is_cut") == 1 )
    {
        if(collar->ic_c_d)
            if( (LD("is_clasp") == 0) ||
                ( LD("clasp_form") == 0 ) ||
                ( LD("clasp_location")!=LD("cut_location") ) )
            {
                collar->SetDspinMinMax( "c_c10",0,9999 );
                collar->SetDspinMinMax( "c_c10",-9999,9999 );
                if(LD("cut_left")>0)
                    H("cut_left") = 0;
            }

    }



    /////VOROT dialog
    H("vorot_height") = 30;
    H("vorot_sign") = 20;

    cut = LD("cut_left");
    bool asymmetric = false;
    if( ( LD("is_clasp") > 0 ) || ( LD("is_cut") > 0 ) || ( LD("g_p_nomirror") == false ) )
        asymmetric = true;
    double location;
    if( LD("is_cut") == 1 )
        location = LD("cut_location");
    else
        location = LD("clasp_location");

    if( ( D("is_vorot") == 1 ) && (D("vorot_type") == 1) )
        gathers->showlabel( "alert2", false );
    else
    {
        if( D("is_vorot") == 0 )
            gathers->labelchangetext( "alert2", QObject::trUtf8("Неактивно без воротника") );
        else
            gathers->labelchangetext( "alert2", QObject::trUtf8("Неактивно для цельнокроеного воротника") );
        gathers->showlabel( "alert2", true );
    }


}


void C2DDress::UpdatePoints()
{
    Unicus::console( "---------------------------------------", LD("clasp_move_by_gorlovina") );
    qDebug() << "C2DDress::UpdatePoints()";
    QLineF unitX = QLineF( QPointF( 0.0f, 0.0f ), QPointF( 1.0f, 0.0f ) );
    QLineF line1,line2;
    QPointF intersectionPoint;
    QPointF* p;
    p=&intersectionPoint;

    P["P0"]=QPointF(10.0f,150.0f);

    P["View:Center"] = P["P0"] + QPointF( LD("Width") / 2.0f - D("SideSeamShift"), 2.0f );

    /******************** BASE ************************************************/
    //Base
    P["11"]=P["P0"];
    P["11'"]=P["11"]+QPointF(LD("K11"),0);

    P["171"]=P["11"]+QPointF( D("T15")-5+LD("PT15"),0 );
    //P["171"]=P["11'"]+QPointF( D("T47")+D("T57")+LD("T45'")+D("PT15"),0 );
    P["31"]=P["11"]+QPointF( 0,-D("T39")-D("PT39") );
    P["31'"]=P["31"]+QPointF( LD("K31"), 0 );
    P["41"]=P["11"]+QPointF( 0,-(LD("T40")) );
    P["41'"]=P["41"]+QPointF( LD("K41") , 0 );
    P["51"]=P["41"]+QPointF( 0,-(LD("T40")*0.5) );
    P["51'"]=P["51"]+QPointF( LD("K51"),0);
    P["91"]=P["11"]+QPointF( 0,-(LD("T70")+LD("Pdi")) );
    P["91'"]=P["91"]+QPointF(LD("K91"),0);
    P["47"]=QPointF(P["171"].x(),P["41'"].y());
    P["57"]=P["47"]+QPointF( 0,-(LD("T40")*0.5) );
    P["471"]=P["47"]+QPointF( 0,-(D("K0")) );
    P["17"]=P["471"]+QPointF( 0,LD("T61")+D("Pdtp") );
    P["371"]=P["17"]+QPointF(0,-(LD("T35'")+D("K01")));    //K01
    Unicus::console("To4kaT35'",LD("T35'"));
    P["311"]=QPointF( P["11'"].x(),P["371"].y() );
    P["97"]=QPointF(P["171"].x(),P["91'"].y());
    P["971"]=P["97"]-QPointF(0,D("K02"));//K02
    P["971'"]=P["971"]+QPointF( -LD("T46") , 0);

    P["33"]=P["31'"]+QPointF( LD("T47"),0 );
    P["35"]=P["33"]+QPointF( LD("T57"),0 );
    //P["37"]=P["35"]+QPointF( LD("T45'")+D("PT45'"),0 );КОНТРОЛЬ ПРОВАЛЕН
    P["37"]=QPointF( P["171"].x(),P["35"].y() );
    P["12"]=P["11"]+QPointF(0.35*D("T13")+D("PT13"),0);
    P["121"]=P["12"]+QPointF( 0,( LD("T43")-LD("T40")-D("K03")) );//K03
    P["111"]=P["11"]+QPointF( QLineF(P["11'"],P["12"]).length()*0.25,0 );
    line1.setPoints(P["12"],P["111"]);
    line2.setPoints(P["12"],P["121"]);
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(0.64*line2.length());
    P["122"]=line1.p2();

    P["111-SS"] = P["111"] + QPointF( QLineF( P["11'"], P["111"] ).length() * 1.0f, 0.0f );
    P["122-SE"] = Unicus::PointOnRay( P["122"],
                                         Unicus::uNormal( QLineF( P["12"], P["122"] ), true )
                                         .angleTo( unitX ) - 9.0f,
                                         QLineF( P["12"], P["122"] ).length() * 0.5f );
    P["122-SS"] = Unicus::PointOnRay( P["122"],
                                         Unicus::uNormal( QLineF( P["12"], P["122"] ), false )
                                         .angleTo( unitX ) - 9.0f,
                                         QLineF( P["12"], P["122"] ).length() * 0.4f );
    P["121-SE"] = QLineF( P["121"], QLineF( P["12"], P["122"] ).pointAt( 0.4f ) )
                     .pointAt( 0.2f );

    P["14"] = Unicus::CircCirc( P["121"], LD("T31"), P["41"], LD("T41"), false );
    line2.setPoints(P["11'"],P["11'"]+QPointF(0,1));
    line1.setPoints(P["14"],P["14"]+QPointF(1,0));
    line1.setAngle(line2.angle()+90);
    line1.intersect(line2,p);

    P["112"] = intersectionPoint;

    line1.setPoints(P["112"],P["14"]);
    line2.setPoints(P["121"],P["121"]+QPointF( 0 , 1 ));
    line2.setAngle(line1.angle()+90);
    line2.intersect( line1,p );
    P["123"] = intersectionPoint;


  //  P["D:P14"] = Unicus::PointOnRay( P["D:P12"], D("Y"), LD("T31") );
    line1.setPoints(P["121"],P["14"]);
    line1.setLength( 0.25 * line1.length());
    P["124"] = line1.p2();


 //   P["D:P124"] = QLineF( P["D:P121"], P["D:P14"] ).pointAt(  )


    P["22"] = P["124"] + QPointF( D("K1"),-sqrt( abs( pow(D("K2"),2)-pow(D("K1"),2)) ) );
    double beta;
    beta = 2*180/M_PI*asin(D("K3")/2.0f/QLineF(P["14"],P["33"]).length());///

    P["14-1"] = Unicus::rPoint(P["14"],P["33"],-beta);
    //line1.setPoints(P["22"],P["14-1"]);


    P["141"] = Unicus::CircCirc( P["22"], QLineF( P["22"], P["14-1"] ).length(),
                                    P["121"], QLineF( P["121"], P["14"] ).length(),
                                    true );

    line1.setPoints(P["121"],P["141"]);
    line2.setPoints(P["22"],P["124"]);
    line1.intersect(line2,p);
    P["125"] = intersectionPoint;

    P["125-1"] = Unicus::CircCirc( P["22"], QLineF( P["22"], P["125"] ).length(),
                                      P["14-1"], QLineF( P["125"], P["141"] ).length(),
                                      false );
//////Горловинушка
    P["16"]=P["17"]+QPointF( -(QLineF(P["11"],P["12"]).length()-D("K4")),0 );
    P["172"]=P["17"]+QPointF( 0,-( QLineF(P["17"],P["16"]).length()+10 ));
    line1.setPoints(P["17"],P["172"]);
    P["173"] = Unicus::CircCirc( P["172"], line1.length(),
                                    P["16"], line1.length(),
                                    true );

    P["(14)"] = P["16"] + QPointF( -QLineF( P["121"], P["14"] ).dx(),
                                          QLineF( P["121"], P["14"] ).dy() );

    P["161"] = QLineF( P["16"], P["(14)"] ).pointAt(
                          QLineF( P["121"], P["125"] ).length() /
                          QLineF( P["16"], P["(14)"] ).length() );
    P["36"] = P["371"] + QPointF( -( LD("T46")+D("K5") ), 0.0f );




    line1 = QLineF(P["36"],P["161"]);
    line1.setLength(LD("T35''"));
    P["26"] = line1.p2();
    beta = 2*180/M_PI*asin((D("T45'")-D("T45")+D("K6"))/2.0f/line1.length());///
    Unicus::console( "BETA T45'->>>>>>>))))))",D("T45'"));
    Unicus::console( "BETA T45->>>>>>>))))))",D("T45"));
    Unicus::console( "BETA K6->>>>>>>))))))",D("K6"));
    Unicus::console( "BETA CM->>>>>>>))))))",(D("T45'")-D("T45")+D("K6")) );
    Unicus::console( "BETA->>>>>>>))))))",beta );
    P["26-1"] = Unicus::rPoint(P["26"],P["36"],beta);
    line1.setPoints(P["36"],P["26-1"]);
    line1.setLength( QLineF(P["36"],P["161"]).length() );
    P["161-1"]=line1.p2();
    P["14-2"] = Unicus::CircCirc( P["36"], QLineF( P["36"], P["(14)"] ).length(),
                                     P["161-1"], QLineF( P["125-1"], P["14-1"] ).length(),
                                     false );


    line1.setPoints(P["33"], P["35"]);
    P["331"] = P["33"] + QPointF( 0, -LD("Pspr") );

    P["341"] = P["331"] + QPointF( LD("Kadd6") * line1.length(), 0);
    P["332"] = P["331"] + QPointF( 0.0f, LD("Kadd6") * line1.length() );
    P["351"] = QPointF( P["35"].x(),P["341"].y() );  //P["35"] + QPointF( 0, -LD("Pspr") );
    P["352"] = P["351"] + QPointF( 0.0f, ( 1 - LD("Kadd6") ) * line1.length() );
    sleevewidth = QLineF( P["331"],P["351"] ).length();
    sleevestartpoint = QPointF( P["171"].x(),P["341"].y() );
    QPointF tmppoint2 = QLineF( P["14-2"],P["14-1"] ).pointAt(0.5);
    sleeve_VOK = QLineF( tmppoint2, QPointF(tmppoint2.x(),P["331"].y())).length();
    P["tmppo"] = tmppoint2;
    P["tmppo2"] = QPointF(tmppoint2.x(),P["331"].y());
    this->line( Sync( attr( SYNC_NAME,  QString( "tmppo-g" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "tmppo", "tmppo2" ) ),
                      LM->thick_yellow() ),
               true );


    P["342"] = P["341"] + QPointF( 0.0f, LD("Kadd6") * line1.length() );

    P["343"] = P["341"] + QPointF( 0.0f, ( 1 - LD("Kadd6") ) * line1.length() );

    line1.setPoints(P["36"],P["26"]);
    line2.setPoints(P["36"],P["26-1"]);
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(D("K36"));
    P["36'"]=line1.p2();

///Левая часть проймы
    line1.setPoints(P["14-1"],P["125-1"]);
    line1.setAngle(line1.angle()+90);
    line2.setPoints(P["332"],P["332"]+QPointF(0,1));
    line1.intersect(line2,p);
    P["142"]=intersectionPoint;
    line1.setPoints(P["14-1"],P["332"]);
    line1.setLength(line1.length()/2);
    P["143"]=line1.p2();
    line1.setPoints(P["142"],P["143"]);
    line1.setLength(line1.length()/2);
    P["144"]=line1.p2();

////Правая часть проймы
    line1.setPoints(P["14-2"],P["161-1"]);
    line1.setAngle(line1.angle()-90);
    line2.setPoints(P["352"],P["352"]+QPointF(0,1));
    line1.intersect(line2,p);
    P["145"]=intersectionPoint;
    line1.setPoints(P["14-2"],P["352"]);
    line1.setLength(line1.length()/2);
    P["146"]=line1.p2();
    line1.setPoints(P["145"],P["146"]);
    line1.setLength(line1.length()/2);
    P["147"]=line1.p2();
/////////////////БОКОВЫЕ СРЕЗЫ И ВЫТАЧКИ НА ТАЛИИ
    line1.setPoints(P["33"],P["35"]);
    P["34"] =  P["33"] + QPointF( D("K7")*line1.length(),0 );

    line1.setPoints(P["34"],P["34"]+QPointF(0,-1));
    QLineF(P["311"],P["371"]).intersect(line1,&P["344"]);
    QLineF(P["41'"],P["47"]).intersect(line1,&P["44"]);
    QLineF(P["51'"],P["57"]).intersect(line1,&P["54"]);
    QLineF(P["91'"],P["97"]).intersect(line1,&P["94"]);
    P["42"]=P["41'"]+QPointF(QLineF(P["31'"],P["33"]).length()*0.5,0);
    line1.setPoints(P["42"],P["42"]+QPointF(0,1));
    QLineF(P["311"],P["371"]).intersect(line1,&P["32"]);
    QLineF(P["51'"],P["57"]).intersect(line1,&P["52"]);
    line1.setPoints(P["36"],P["36"]+QPointF(0,-1));
    QLineF(P["41'"],P["47"]).intersect(line1,&P["46"]);
    QLineF(P["51'"],P["57"]).intersect(line1,&P["56"]);
    P["470"]=P["41'"]+QPointF( D("T18")+D("PT18") ,0);
    double summrastvor=QLineF(P["47"],P["470"]).length();
    P["421"]=P["42"]+QPointF( -summrastvor*0.3*0.5,0);
    P["421'"]=P["42"]+QPointF( summrastvor*0.3*0.5,0);

    P["441"]=P["44"]+QPointF( -summrastvor*0.5*0.5,0);
    P["441'"]=P["44"]+QPointF( summrastvor*0.5*0.5,0);

    P["441a"]=P["441"]+QPointF(0,15);
    P["441'a"]=P["441'"]+QPointF(0,15);

    P["461"]=P["46"]+QPointF( -summrastvor*0.2*0.5,0);
    P["461'"]=P["46"]+QPointF( summrastvor*0.2*0.5,0);

    P["570"]=P["51'"]+QPointF( D("T19")+D("PT19"),0);
    double shirnalinbed=(D("T19")+D("PT19"))-QLineF(P["51'"],P["57"]).length();
    P["541"]=P["54"]+QPointF( shirnalinbed*0.5,0);
    P["541'"]=P["54"]+QPointF( -shirnalinbed*0.5,0);
    P["941"]=QPointF(P["541"].x(),P["91'"].y());
    P["941'"]=QPointF(P["541'"].x(),P["91'"].y());
    P["942"]=P["941"]+QPointF(D("K8"),0);
    P["942'"]=P["941'"]+QPointF(-D("K8"),0);

    line1.setPoints( P["541"],P["942"] );
    line1.setLength(QLineF(P["541"],P["941"]).length());
    P["943"]=line1.p2();
    line1.setPoints( P["541'"],P["942'"] );
    line1.setLength(QLineF(P["541'"],P["941'"]).length());
    P["943'"]=line1.p2();
//////ВЫТАЧКИ!
    if(P["44"].x()<=P["341"].x())
        P["347"]=Unicus::circline(QLineF(P["344"],P["34"]),P["342"],QLineF(P["342"],P["341"]).length(),false);
    else
        P["347"]=Unicus::circline(QLineF(P["344"],P["34"]),P["343"],QLineF(P["343"],P["341"]).length(),false);

    P["D:LT"]=P["42"]+QPointF(0,LD("D:LT"));
    P["D:LB"]=P["42"]+QPointF(0,-LD("D:LB"));
    P["D:RT"]=P["46"]+QPointF(0,LD("D:RT"));
    P["D:RB"]=P["46"]+QPointF(0,-LD("D:RB"));
   // P["D:CB"]=P["44"]+QPointF(0,-D("D:CB"));


//ПРОЙМА Сплайны
    ///////////////////////LEFT
    line1.setPoints(P["14-1"], P["142"]);
    line1.setLength(QLineF(P["14-1"],P["144"]).length()*0.4);
    P["14-1-SS"] = line1.p2();
    line1.setPoints( P["144"],P["14-1"] );
    line2.setPoints( P["332"],P["144"] );
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.5);
    P["144-SU"] = line1.p2();
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.3);
    P["144-SB"] = line1.p2();
    line1.setPoints(P["332"], P["332"]+QPointF(0,1));
    line1.setLength(QLineF(P["144"],P["332"]).length()*0.2);
    P["332-SS"] = line1.p2();

    line2.setPoints( P["332"], P["341"] );
    line1.setPoints( P["332"],P["332"] - QPointF( 0,1 ) );
    line1.setLength( line2.length() * 0.4 );
    P["332d"] = line1.p2();
    line1.setPoints(P["341"],P["341"]-QPointF(1,0));
    line1.setLength( line2.length() * 0.4 );
    P["341l"] = line1.p2();

    line2.setPoints( P["352"],P["341"] );
    line1.setPoints( P["352"],P["352"] - QPointF( 0,1 ) );
    line1.setLength( line2.length() * 0.4 );
    P["352d"] = line1.p2();
    line1.setPoints(P["341"],P["341"]+QPointF(1,0));
    line1.setLength( line2.length() * 0.4 );
    P["341r"] = line1.p2();

    line2.setPoints( P["16"],P["172"] );
    line1.setPoints( P["16"],P["16"] - QPointF( 0,1 ) );
    line1.setLength( line2.length() * 0.4 );
    P["16d"] = line1.p2();
    line1.setPoints(P["172"],P["172"]-QPointF(1,0));
    line1.setLength( line2.length() * 0.4 );
    P["172l"] = line1.p2();


    //////////////////////RIGHT
    line1.setPoints(P["14-2"], P["145"]);
    line1.setLength( QLineF(P["14-2"],P["147"]).length()*0.3);
    P["14-2-SS"] = line1.p2();
    line1.setPoints( P["147"],P["14-2"] );
    line2.setPoints( P["352"],P["147"] );
    line1.setAngle((line1.angle()+line2.angle())/2);
    line1.setLength(line1.length()*0.3);
    P["147-SU"] = line1.p2();
    line1.setAngle(line1.angle()+180);
    line1.setLength(line2.length()*0.3);
    P["147-SB"] = line1.p2();
    line1.setPoints(P["352"], P["352"]+QPointF(0,1) );
    line1.setLength(QLineF(P["147"],P["352"]).length()*0.3);
    P["352-SS"] = line1.p2();

    ////// Нижний сплайн
    line1.setPoints(P["943'"],P["541'"]);
    line1.setAngle(line1.angle()+90);
    line1.setLength(QLineF(P["943'"],P["971'"]).length()*0.3);
    P["943':SR"]=line1.p2();

    line1.setPoints(P["971'"],P["971"]);
    line1.setAngle(line1.angle()+180);
    line1.setLength(QLineF(P["943'"],P["971'"]).length()*0.3);
    P["971':SL"]=line1.p2();

    line1.setPoints( P["11'"], P["111"] );
    line1.setLength( QLineF(P["11'"],P["121"]).length() * 0.7f );
    line2.setPoints( P["121"], P["121-SE"] );
    line2.setLength( QLineF(P["121"], QPointF(P["121"].x(),P["11'"].y())).length() * 0.9f );
    P["11-ss"] = line1.p2();
    P["122-se2"] = line2.p2();

    P["11dialog"] = P["11'"] - QPointF( 0,LD("rasshir_gorloviny_spinka") );
    P["111dialog"] = P["111"] - QPointF( 0,LD("rasshir_gorloviny_spinka") );

    line1.setPoints(P["121"],P["125"]);
    line1.setLength(LD("rasshirenie_gorloviny_plecho"));
    P["121dialog"] = line1.p2();
    P["121-SEdialog"] = P["121-SE"] + (P["121dialog"] - P["121"]);

    P["11dialog_m"] = P["11'"] - QPointF( 0,LD("rasshir_gorloviny_spinka_m") );
    P["111dialog_m"] = P["111"] - QPointF( 0,LD("rasshir_gorloviny_spinka_m") );

    line1.setPoints(P["121"],P["125"]);
    gangleSm = line1.angle();

    line1.setLength(LD("rasshirenie_gorloviny_plecho_m"));
    P["121dialog_m"] = line1.p2();
    P["121-SEdialog_m"] = P["121-SE"] + (P["121dialog_m"] - P["121"]);
    //
    P["172dialog"] = P["172"] - QPointF( 0,LD("rasshir_gorloviny_polochka") );
    P["172ldialog"] = P["172l"] - QPointF( 0,LD("rasshir_gorloviny_polochka") );
    line1.setPoints(P["16"],P["161"]);
    line1.setLength(LD("rasshirenie_gorloviny_plecho"));
    P["16dialog"] = line1.p2();
    P["16Ddialog"] = P["16d"] + P["16dialog"] - P["16"];

    P["172dialog_m"] = P["172"] - QPointF( 0,LD("rasshir_gorloviny_polochka_m") );
    P["172ldialog_m"] = P["172l"] - QPointF( 0,LD("rasshir_gorloviny_polochka_m") );
    line1.setPoints(P["16"],P["161"]);
    ganglePm = line1.angle();
    line1.setLength(LD("rasshirenie_gorloviny_plecho_m"));
    P["16dialog_m"] = line1.p2();
    P["16Ddialog_m"] = P["16d"] + P["16dialog_m"] - P["16"];
    /*** Dress : End ***/

    Unicus::console( "51y", P["51'"].y());
    Unicus::console( "57y", P["57"].y());
    P["butt"] = QPointF(-5 - LD("K11") ,10);
}

void C2DDress::DrawOnWidget()
{
    qDebug() << "C2DDress::DrawOnWidget();";

    cpath["g_left_e"] = C2DPath();
    cpath["g_leftm_e"] = C2DPath();
    cpath["g_right_e"] = C2DPath();
    cpath["g_rightm_e"] = C2DPath();
    //*********************/
    this->line( Sync( attr( SYNC_NAME,  QString( "11-171" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11", "171" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "11dialog-31" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11dialog", "31" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "31-41" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "31", "41" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "41-51" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "41", "51" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "51-91" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "51", "91" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "11'-31'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "11'", "31'" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "31'-41'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "31'", "41'" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "41'-51'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "41'", "51'" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "51'-91'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "51'", "91'" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "91-91'" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "91", "91'" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "47-41" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "47", "41" ) ),
                      LM->thick_dashed() ),
               true );

   // this->line( MakeSync( "11-51", Sync::Line, MakeList( "11", "51" ), LM->thick_dashed() ), true );
    this->line( Sync( attr( SYNC_NAME,  QString( "57-51" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "57", "51" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "17-471" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "17", "471" ) ),
                      LM->thick_dashed() ),
               true );

    this->line( Sync( attr( SYNC_NAME,  QString( "97-971" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "97", "971" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "97-471" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "97", "471" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "97-91" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "97", "91" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "311-371" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "311", "371" ) ),
                      LM->thick_dashed() ),
               true );
    this->line( Sync( attr( SYNC_NAME,  QString( "35-37" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "35", "37" ) ),
                      LM->thick_dashed() ),
               true );

    this->spline( Sync( attr( SYNC_NAME,  QString( "S11-121" ) ),
                        attr( SYNC_TYPE, C2DSync::Spline ),
                        attr( SYNC_LIST, MakeList( "11", "11-ss", "122-se2", "121" ) ),
                        LM->thick_dashed() ),
                  true );


    line( Sync( attr( SYNC_NAME,  QString( "121-123" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121", "123" ) ),
                      LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "112-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "112", "14" ) ),
                      LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "124-14" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "124", "14" ) ),
                      LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "121-141" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121", "141" ) ),
                      LM->thick_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "121-125" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "121", "125" ) ),
                      LM->thick_dashed() ),
          true );

   // line( Sync( attr( SYNC_NAME,  QString( "121dialog-125" ) ),
   //                   attr( SYNC_TYPE, C2DSync::Line ),
   //                   attr( SYNC_LIST, MakeList( "121dialog", "125" ) ),
   //                   LM->bold_solid() ),
   //       true );

    line( Sync( attr( SYNC_NAME,  QString( "125-22" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "125", "22" ) ),
                      LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "22-125-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "22", "125-1" ) ),
                      LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "125-1-14-1" ) ),
                      attr( SYNC_TYPE, C2DSync::Line ),
                      attr( SYNC_LIST, MakeList( "125-1", "14-1" ) ),
                      LM->thick_dashed() ),
          true );



    //this->arc( MakeSync( "332-341", Sync::Arc, MakeList( "342", "332", "341" ), LM->thick_solid() ), true );
    //this->arc( MakeSync( "341-352", Sync::Arc, MakeList( "343", "341", "352" ), LM->thick_solid() ), true );


    //FRONT
    this->spline( Sync( attr( SYNC_NAME,  QString( "S16-172" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "16", "16d", "172l", "172" ) ),
                      LM->thick_dashed() ),
                 true );
    //this->arc( MakeSync( "16-172", Sync::Arc, MakeList( "173", "172", "16" ), LM->bold_solid() ), true );
    line( Sync( attr( SYNC_NAME,  QString( "16-161" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "16", "161" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "161-26" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "161", "26" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "26-36'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "26", "36'" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "36'-26-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "36'", "26-1" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "26-1-161-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "26-1", "161-1" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "161-1-14-2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "161-1", "14-2" ) ),
                LM->thick_dashed() ),
          true );

    if( LD("GorlovinaBalance") == 0 )
    {
        H("GorlovinaBalance") = 0.00001;
        if( LD("GorlovinaBalance_m") == 0 )
            H("GorlovinaBalance_m") = 0.00001;
    }
    if( LD("ProimaBalance") == 0 )
    {
        H("ProimaBalance") = 0.00001;
        if( LD("ProimaBalance_m") == 0 )
            H("ProimaBalance_m") = 0.00001;
    }
//////////Вытачки и боковые срезы
    line( Sync( attr( SYNC_NAME,  QString( "347-344" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "347", "344" ) ),
                LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "344-44" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "344", "44" ) ),
                LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "32-52" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "32", "52" ) ),
                LM->thick_solid() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "36-56" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "36", "56" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "421-421'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "421", "421'" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "441-441'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "441", "441'" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "461-461'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "461", "461'" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "541-541'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "541", "541'" ) ),
                LM->thick_dashed() ),
          true );

    line( Sync( attr( SYNC_NAME,  QString( "971-971'" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "971", "971'" ) ),
                LM->thick_dashed() ),
          true );

    point( Sync( attr( SYNC_NAME,  QString( "470" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "470" ) ),
                 LM->thick_solid() ),
           true );

    point( Sync( attr( SYNC_NAME,  QString( "570" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "570" ) ),
                 LM->thick_solid() ),
           true );

   // QMessageBox( QMessageBox::Warning,"Warning",QObject::trUtf8("Голова не пролезет.") ).exec();
    QPainterPath myspline,temppath;
    QLineF line1;
    DartItem * LT = dart( Sync( attr( SYNC_NAME, QString( "DartLT-001" ) ),
                                attr( SYNC_TYPE, C2DSync::Dart ),
                                attr( SYNC_LIST, MakeList( "D:LT", "421'", "421" ) ),
                                LM->thick_solid() ),
                          true );
    if ( LT )
    {
        LT->setKK( -3.0f );
        LT->update();
        myspline = LT->rightSplineShape();
        line1.setPoints(P["421"],P["421"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["32"],P["421"]).length()*0.2);
        P["421-SB"]=line1.p2();

        P["TT1"]=myspline.pointAtPercent(0.99f);
        myspline = LT->leftSplineShape();
        line1.setPoints(P["421'"],P["421'"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["32"],P["421'"]).length()*0.2);
        P["421'-SB"]=line1.p2();
        P["TT2"]=myspline.pointAtPercent(0.99f);


        QLineF line2(P["D:LB"],P["42"]);
        line2.setLength(QLineF(P["D:LB"],P["421"]).length()*0.5);
        P["D:LB-ST"]=line2.p2();

        point( Sync( attr( SYNC_NAME, QString( "421'-SB" ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "421'-SB" ) ),
                     LM->thick_solid() ),
                true );
        point( Sync( attr( SYNC_NAME, QString( "421-SB" ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "421-SB" ) ),
                     LM->thick_solid() ),
                true );

        spline( Sync( attr( SYNC_NAME,  QString( "S421-D:LB" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "421", "421-SB", "D:LB-ST", "D:LB" ) ),
                      LM->thick_solid() ),
                 true );
        spline( Sync( attr( SYNC_NAME,  QString( "S421'-D:LB" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "421'", "421'-SB", "D:LB-ST", "D:LB" ) ),
                      LM->thick_solid() ),
                 true );

    }

    DartItem * RT = dart( Sync( attr( SYNC_NAME, QString( "DartRT-001" ) ),
                                attr( SYNC_TYPE, C2DSync::Dart ),
                                attr( SYNC_LIST, MakeList( "D:RT", "461'", "461" ) ),
                                LM->thick_solid() ),
                          true );
    if ( RT )
    {
        RT->setKK( -3.0f );

        myspline = RT->rightSplineShape();
        line1.setPoints(P["461"],P["461"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["36"],P["461"]).length()*0.15);
        P["461-SB"]=line1.p2();

        myspline = RT->leftSplineShape();
        line1.setPoints(P["461'"],P["461'"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["36"],P["461'"]).length()*0.05);
        P["461'-SB"]=line1.p2();

        QLineF line2(P["D:RB"],P["46"]);
        line2.setLength(QLineF(P["D:RB"],P["461"]).length()*0.6);
        P["D:RB-ST"]=line2.p2();

        spline( Sync( attr( SYNC_NAME,  QString( "S461-D:RB" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "461", "461-SB", "D:RB-ST", "D:RB" ) ),
                      LM->thick_solid() ),
                 true );

        spline( Sync( attr( SYNC_NAME,  QString( "S461'-D:RB" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "461'", "461'-SB", "D:RB-ST", "D:RB" ) ),
                      LM->thick_solid() ),
                 true );

    }

    bool VB=false;
    if( D("VB")==1 )
        VB = true;
    //P["VBpoint"] = QPointF(0,0);
    QLineF(P["44"],P["44"]+QPointF(0,1)).intersect( QLineF(P["971"],P["971'"]), &P["VBpoint"] );
    line( Sync( attr( SYNC_NAME,  QString( "44-VBpoint" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "44", "VBpoint" ) ),
                LM->bold_solid() ),
          !VB );

    DartItem * CT = dart( Sync( attr( SYNC_NAME, QString( "DartCT-001" ) ),
                                attr( SYNC_TYPE, C2DSync::Dart ),
                                attr( SYNC_LIST, MakeList( "347", "441'a", "441a" ) ),
                                LM->thick_solid() ),
                          true );
    SplineItem * CTright, * CTleft;
    if ( CT )
    {
        CT->setKK( -9.0f );
        myspline = CT->rightSplineShape();
        line1.setPoints(P["441a"],P["441a"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["441a"],P["541"]).length()*0.2);
        P["441a-SB"]=line1.p2();
        line1.setPoints(P["541"],P["943"]);
        line1.setAngle(line1.angle()+180);
        line1.setLength(QLineF(P["441a"],P["541"]).length()*0.6);
        P["541-ST"]=line1.p2();
        if(!VB)
            CT->setVisible(false);
        else
            CT->setVisible(true);
        myspline = CT->leftSplineShape();
        line1.setPoints(P["441'a"],P["441'a"]+QPointF(0,-1));
        line1.setAngle(myspline.angleAtPercent(1));
        line1.setLength(QLineF(P["441'a"],P["541'"]).length()*0.2);
        P["441'a-SB"]=line1.p2();
        line1.setPoints(P["541'"],P["943'"]);
        line1.setAngle(line1.angle()+180);
        line1.setLength(QLineF(P["441'a"],P["541'"]).length()*0.6);
        P["541'-ST"]=line1.p2();

        CTleft = spline( Sync( attr( SYNC_NAME,  QString( "S441a-541" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "441a", "441a-SB", "541-ST", "541" ) ),
                      LM->thick_solid() ),
                 VB );
        CTright = spline( Sync( attr( SYNC_NAME,  QString( "S441'a-541'" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "441'a", "441'a-SB", "541'-ST", "541'" ) ),
                      LM->thick_solid() ),
                 VB );
/*        this->point( MakeSync( "441a-SB", Sync::Point, MakeList( "441a-SB" ), LM->thick_solid() ), true );
        this->point( MakeSync( "541-ST", Sync::Point, MakeList( "541-ST" ), LM->thick_solid() ), true );
        this->point( MakeSync( "441'a-SB", Sync::Point, MakeList( "441'a-SB" ), LM->thick_solid() ), true );
        this->point( MakeSync( "541'-ST", Sync::Point, MakeList( "541'-ST" ), LM->thick_solid() ), true );
*/
        line( Sync( attr( SYNC_NAME,  QString( "541-943" ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( "541", "943" ) ),
                    LM->thick_solid() ),
              VB );

        line( Sync( attr( SYNC_NAME,  QString( "541'-943'" ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( "541'", "943'" ) ),
                    LM->thick_solid() ),
              VB );

        line( Sync( attr( SYNC_NAME,  QString( "941-943" ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( "941", "943" ) ),
                    LM->thick_solid() ),
              VB );

        line( Sync( attr( SYNC_NAME,  QString( "941'-943'" ) ),
                    attr( SYNC_TYPE, C2DSync::Line ),
                    attr( SYNC_LIST, MakeList( "941'", "943'" ) ),
                    LM->thick_solid() ),
              VB );
    }
    bool tmpb = false;
    if( D("VP") == 1 )
        tmpb = true;
    line( Sync( attr( SYNC_NAME,  QString( "172dialog-47" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "172dialog", "971" ) ),
                LM->bold_solid() ),
          tmpb );
/////ВЕРХНЯЯ ЧАСТЬ ПРОЙМЫ
    SplineItem * spitem;
    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S14-1-144" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "14-1", "14-1-SS", "144-SU", "144" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[0] = spitem->shape();

    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S144-332" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "144", "144-SB", "332-SS", "332" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[1] = spitem->shape();

    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S14-2-147" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "14-2", "14-2-SS", "147-SU", "147" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[5] = spitem->shape().toReversed();

    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S147-352" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "147", "147-SB", "352-SS", "352" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[4] = spitem->shape().toReversed();

    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S341-332" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "332", "332d", "341l", "341" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[2] = spitem->shape();

    spitem = spline( Sync( attr( SYNC_NAME,  QString( "S341-352" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "341", "341r", "352d", "352" ) ),
                      LM->thick_dashed() ),
                 true );
    proima[3] = spitem->shape();

    point( Sync( attr( SYNC_NAME,  QString( "331" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "331" ) ),
                 LM->thick_solid() ),
           true );
    ////Отведение средней линии спинки
    point( Sync( attr( SYNC_NAME,  QString( "11'" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "11'" ) ),
                 LM->thick_solid() ),
           true );
    point( Sync( attr( SYNC_NAME,  QString( "31'" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "31'" ) ),
                 LM->thick_solid() ),
           true );

    point( Sync( attr( SYNC_NAME,  QString( "41'" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "41'" ) ),
                 LM->thick_solid() ),
           true );
    point( Sync( attr( SYNC_NAME,  QString( "51'" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "51'" ) ),
                 LM->thick_solid() ),
           true );
    point( Sync( attr( SYNC_NAME,  QString( "91'" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "91'" ) ),
                 LM->thick_solid() ),
           true );
    point( Sync( attr( SYNC_NAME,  QString( "(14)" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "(14)" ) ),
                 LM->thick_solid() ),
           true );

    spline( Sync( attr( SYNC_NAME,  QString( "S971'-943'" ) ),
                      attr( SYNC_TYPE, C2DSync::Spline ),
                      attr( SYNC_LIST, MakeList( "971'", "971':SL", "943':SR", "943'" ) ),
                      LM->thick_solid() ),
                 true );

    ///Надсечки
    sign( Sync( attr( SYNC_NAME, QString( "S1" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "41" ) ),
                LM->thick_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, 0 ) ),
          true );



    myspline = CT->rightSplineShape();
    sign( Sync( attr( SYNC_NAME, QString( "S2" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "441a" ) ),
                LM->thick_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -myspline.angleAtPercent(1)+90 ) ),
          VB );
    myspline = CT->leftSplineShape();
    sign( Sync( attr( SYNC_NAME, QString( "S3" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "441'a" ) ),
                LM->thick_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -myspline.angleAtPercent(1)-90 ) ),
          VB );

    point( Sync( attr( SYNC_NAME,  QString( "421-SB" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "421-SB" ) ),
                 LM->thick_solid() ),
           true );
    point( Sync( attr( SYNC_NAME,  QString( "421'-SB" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "421'-SB" ) ),
                 LM->thick_solid() ),
           true );

  //  point( Sync( attr( SYNC_NAME,  QString( "TT1" ) ),
  //               attr( SYNC_TYPE, C2DSync::Point ),
  //               attr( SYNC_LIST, MakeList( "TT1" ) ),
  //               LM->thick_solid() ),
  //         true );
    point( Sync( attr( SYNC_NAME,  QString( "TT2" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "TT2" ) ),
                 LM->thick_solid() ),
           true );
     point( Sync( attr( SYNC_NAME,  QString( "341" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "341" ) ),
                 LM->thick_solid() ),
           true );


    QPainterPath mymark;
    mymark.moveTo(P["14-1"]);
    mymark.cubicTo(P["14-1-SS"],P["144-SU"],P["144"]);
    mymark.cubicTo(P["144-SB"],P["332-SS"],P["332"]);
    mymark.cubicTo(P["332d"],P["341l"],P["341"]);
    mymark.cubicTo(P["341r"],P["352d"],P["352"]);
    mymark.cubicTo(P["352-SS"],P["147-SB"],P["147"]);
    mymark.cubicTo(P["147-SU"],P["14-2-SS"],P["14-2"]);
    QPainterPath pbleft,pbright;
    PpathItem * myitem1 , * myitem2;
    if(( LD( "ProimaBalance" ) != 0 ) && ( LD("ProimaShag") > 0 ) )
    {
        double leftangle=0, rightangle=0,balance, shag = LD("ProimaShag");
        double templength=shag;
        QPointF target_p;
        if( LD("ProimaBalance") < 0 )
        {
            balance = -LD("ProimaBalance");
            target_p = mymark.pointAtPercent( balance / mymark.length() );
        }else if( LD("ProimaBalance") > 0 )
        {
            balance = mymark.length() - LD("ProimaBalance");
            target_p = mymark.pointAtPercent( balance / mymark.length() );
        }
        pbleft.moveTo( mymark.pointAtPercent( 0 ) );

        while( templength < balance )
        {
            pbleft.lineTo( mymark.pointAtPercent( templength/mymark.length() ) );
            templength = templength + shag;
        }
        pbleft.lineTo( target_p );
        pbright.moveTo( target_p );
        templength = balance + shag;
        while( templength < mymark.length() )
        {
            pbright.lineTo( mymark.pointAtPercent( templength/mymark.length() ) );
            templength = templength + shag;
        }
        pbright.lineTo( mymark.pointAtPercent( 1 ) );

        if( LD("ProimaBalance") > 0 )
        {
            pbright = pbright.toReversed();
            P["pbleft"] = mymark.pointAtPercent( 0 );
            P["pbright"] = pbleft.pointAtPercent( 0 );
            leftangle = 0;
            rightangle = pbright.angleAtPercent( 0 ) - pbleft.angleAtPercent( 0 ) + 180;//mymark.angleAtPercent( 0 )+180;
        }else
        {
            P["pbleft"] = mymark.pointAtPercent( 1 );
            P["pbright"] = pbleft.pointAtPercent( 1 );
            leftangle = pbleft.angleAtPercent( 0 ) - pbright.angleAtPercent( 1 );//mymark.angleAtPercent(1)+180;
            rightangle = 0;
        }
        Unicus::console( "Not null",  LD( "ProimaBalance" ) );
        myitem1 = ppath(  Sync( attr( SYNC_NAME,  QString( "pbleft" ) ),
                    attr( SYNC_TYPE, C2DSync::Ppath ),
                    attr( SYNC_LIST, MakeList( "pbleft" ) ),
                    LM->thick_solid() ), &pbleft, leftangle, 0,
              true );

        myitem2 =  ppath(  Sync( attr( SYNC_NAME,  QString( "pbright" ) ),
                    attr( SYNC_TYPE, C2DSync::Ppath ),
                    attr( SYNC_LIST, MakeList( "pbright" ) ),
                    LM->thick_solid() ), &pbright, rightangle, 0,
              true );

        if( LD("ProimaBalance") > 0 )
        {
            P["pl"] = myitem2->getEnd();
            P["pr"] = myitem1->getEnd();
            temppath = myitem2->myshape_fromstart(2);
            temppath = temppath.toReversed();
            temppath.connectPath(myitem1->myshape_fromstart(2));
        }else
        {
            P["pl"] = myitem2->getStartPoint();
            P["pr"] = myitem1->getEnd();
            temppath = myitem2->myshape_fromstart(2);
            temppath.connectPath(myitem1->myshape_fromstart(2));
        }
    }else
    {
        Unicus::console( "Равно",  LD( "ProimaBalance" ) );
        temppath = mymark;

        PpathItem * myitem1 = ppath(  Sync( attr( SYNC_NAME,  QString( "PPath" ) ),
                    attr( SYNC_TYPE, C2DSync::Ppath ),
                    attr( SYNC_LIST, MakeList( "14-1" ) ),
                    LM->bold_solid() ), &mymark, 0, 0,
              true );
        P["pl"] = myitem1->getStartPoint();
        P["pright"] = myitem1->getEnd();
    }
    // если незеркально
    cpath["old_proima"] = C2DPath(mymark);
    if( LD("g_p_nomirror") )
    {
        this->NewProima();
    }else
        cpath["mirror_proima"] = temppath;

    P["m14-1"] = cpath["mirror_proima"].shape().pointAtPercent(0);
    P["m14-2"] = cpath["mirror_proima"].shape().pointAtPercent(1);
    P["m22"] = P["22"];
    P["m36"] = P["36"];

    point( Sync( attr( SYNC_NAME,  QString( "pl" ) ),
                attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "pl" ) ),
                LM->bold_solid() ),
          true );

    point( Sync( attr( SYNC_NAME,  QString( "pr" ) ),
                attr( SYNC_TYPE, C2DSync::Point ),
                attr( SYNC_LIST, MakeList( "pr" ) ),
                LM->bold_solid() ),
          true );

    ///////Диалоги для горловины точки. Создам дубликаты точек 11 и 111 чтобы ввести переменную регулирующую их положение по У
    //P["11dialog"] = P["11"] - QPointF( 0,\LD("rasshir_gorloviny_spinka") );
    //P["111dialog"] = P["111"] - QPointF( 0,\LD("rasshir_gorloviny_spinka") );
    //P["121dialog"] = P["121"] - QPointF( LD("rasshirenie_gorloviny_plecho"),0 );
    //P["121-SEdialog"] = P["121-SE"] - QPointF( LD("rasshirenie_gorloviny_plecho"),0 );
    ///////
    //P["172dialog"] = P["172"] - QPointF( 0,LD("rasshir_gorloviny_polochka") );
    //P["172ldialog"] = P["172l"] - QPointF( 0,LD("rasshir_gorloviny_polochka") );
    //P["16dialog"] = P["16"] - QPointF( LD("shirina_gorloviny_polochka"),0 );
    //P["16Ddialog"] = P["16d"] - QPointF( LD("shirina_gorloviny_polochka"),0 );

    QPainterPath GorLeft,GorRight,GorLeftm,GorRightm;
    GorLeft.moveTo(P["11dialog"]);
    line1.setPoints( P["11dialog"], P["111dialog"] );
    line1.setLength( QLineF(P["11dialog"],P["121dialog"]).length() * 0.7f );
    QLineF line2( P["121dialog"], P["121-SEdialog"] );
    line2.setLength( QLineF(P["121dialog"], QPointF(P["121dialog"].x(),P["11dialog"].y())).length() * 0.9f );
    GorLeft.cubicTo( line1.p2(),line2.p2(),P["121dialog"] );
    P["g_s_slengthLR"] = QPointF( QLineF(P["121dialog"],line2.p2()).length(),
                                QLineF(P["11dialog"],line1.p2()).length() );
    GorLeftm.moveTo(P["11dialog_m"]);
    line1.setPoints( P["11dialog_m"], P["111dialog_m"] );
    line1.setLength( QLineF(P["11dialog_m"],P["121dialog_m"]).length() * 0.7f );
    line2.setPoints( P["121dialog_m"], P["121-SEdialog_m"] );
    line2.setLength( QLineF(P["121dialog_m"], QPointF(P["121dialog_m"].x(),P["11dialog_m"].y())).length() * 0.9f );
    GorLeftm.cubicTo( line1.p2(),line2.p2(),P["121dialog_m"] );
    P["g_sm_slengthLR"] = QPointF( QLineF(P["121dialog_m"],line2.p2()).length(),
                                QLineF(P["11dialog_m"],line1.p2()).length() );
    //GorLeft.lineTo(P["111"]);
    //GorLeft.cubicTo(P["111-SS"],P["122-SE"],P["122"]);
    //GorLeft.cubicTo(P["122-SS"],P["121-SE"],P["121"]);
    // "122", "122-SS", "121-SE", "121"
    //"111", "111-SS", "122-SE", "122"
    GorRight.moveTo( P["172dialog"] );
    GorRight.cubicTo( P["172ldialog"], P["16Ddialog"], P["16dialog"] );
    GorRightm.moveTo( P["172dialog_m"] );
    GorRightm.cubicTo( P["172ldialog_m"], P["16Ddialog_m"], P["16dialog_m"] );

    P["g_p_slengthLR"] = QPointF( QLineF(P["16Ddialog"],P["16dialog"]).length(),
                                QLineF(P["172dialog"],P["172ldialog"]).length() );
    P["g_pm_slengthLR"] = QPointF( QLineF(P["16Ddialog_m"],P["16dialog_m"]).length(),
                                QLineF(P["172dialog_m"],P["172ldialog_m"]).length() );

    //горловина несколько точек Нчало
    ppath(  Sync( attr( SYNC_NAME,  QString( "G_p_0" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "172dialog" ) ),
                            LM->thick_dashed() ), &GorRight, 0, 0,
                      true );

    bool g_s_points = false;
    //if ( LD("g_s_point_count") > 0 )
    {
        GorLeft = make_dialog_gorlovina( &GorLeft, "spinka" );
        g_s_points = true;
    }
    for( int i=0;i<LD("g_s_point_count");i++ )
        point( Sync( attr( SYNC_NAME,  QString( "g_s"+QString::number(i) ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "g_s"+QString::number(i) ) ),
                     LM->thick_solid() ),
               g_s_points );
//----------------------------------------
    //C2DPath c2dps(GorLeft), c2dpp(GorRight);
    bool g_p_points = false;
    //if ( LD("g_p_point_count") > 0 )
    {

        GorRight = make_dialog_gorlovina( &GorRight, "polochka" );
        g_p_points = true;
    }
    for( int i=0;i<LD("g_p_point_count");i++ )
        point( Sync( attr( SYNC_NAME,  QString( "g_p"+QString::number(i) ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "g_p"+QString::number(i) ) ),
                     LM->thick_solid() ),
               g_p_points );
////для незеркальной
    bool g_sm_points = false;
    bool g_pm_points = false;
    if( LD("g_p_nomirror") == true )
        //if ( LD("g_sm_point_count") > 0 )
        {
            GorLeftm = make_dialog_gorlovina( &GorLeftm, "spinka_m" );
            g_sm_points = true;
        }
    for( int i=0;i<LD("g_sm_point_count");i++ )
        point( Sync( attr( SYNC_NAME,  QString( "g_sm"+QString::number(i) ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "g_sm"+QString::number(i) ) ),
                     LM->thick_solid() ),
               g_sm_points );

    if( LD("g_p_nomirror") == true )
        //if (( LD("g_pm_point_count") > 0 )||( LD("g_pm_alpha")!=0 )||( LD("g_pm_beta")!=0 ))
        {
             GorRightm = make_dialog_gorlovina( &GorRightm, "polochka_m" );
             g_pm_points = true;
        }
    for( int i=0;i<LD("g_pm_point_count");i++ )
        point( Sync( attr( SYNC_NAME,  QString( "g_pm"+QString::number(i) ) ),
                     attr( SYNC_TYPE, C2DSync::Point ),
                     attr( SYNC_LIST, MakeList( "g_pm"+QString::number(i) ) ),
                     LM->thick_solid() ),
               g_pm_points );
    P["172dialog-1"] =P["172dialog"]+QPointF(20,0);
    P["11dialog-1"] =P["11dialog"]-QPointF(20,0);

/*    ppath(  Sync( attr( SYNC_NAME,  QString( "G_p_0m11" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "36" ) ),
                            LM->thick_dashed() ), &GorLeft, 0, 0,
                      true );
    ppath(  Sync( attr( SYNC_NAME,  QString( "G_p_0m1" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "22" ) ),
                            LM->thick_dashed() ), &GorRight, 0, 0,
                      true );
*/
    dress_gorlovina->setDSpinminmax( "dsp1",-GorLeft.length()/10,GorRight.length()/10 );
    dress_gorlovina->setDSpinminmax( "dsp1m",-GorLeftm.length()/10,GorRightm.length()/10 );
        //горловина несколько точек конец
    cpath["GorRight"] = C2DPath(GorRight);
    cpath["GorRightm"] = C2DPath(GorRightm);
    cpath["GorLeft"] = C2DPath(GorLeft);
    cpath["GorLeftm"] = C2DPath(GorLeftm);
    NewGorlovinaBalance();
    if( LD("g_p_nomirror") == true )
    {
        cpath["GorLeftm"] = C2DPath(GorLeftm);
        cpath["GorRightm"] = C2DPath(GorRightm);
        this->NewGorlovina();
        //cpath["g_left_e"] = result.at(0);
        //cpath["g_right_e"] = result.at(1);
        //cpath["mirror_proima"]
    }else
    {
        cpath["GorLeftm"] = C2DPath(GorLeft);
        cpath["GorRightm"] = C2DPath(GorRight);
    }
    //if ( ( D("is_mirror")==0 ) )
   // {
   //     gorlm = cpath["g_leftm_e"].shape().length();
   //     gorrm = cpath["g_rightm_e"].shape().length();
   //     Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!2gorr",gorr );
   //     Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!2",gorrm );
   // }

//QPainterPath Gorlovina[3];double angle[3];
    //"16", "16d", "172l", "172"
    gangleS = QLineF( P["121"],P["125"] ).angle();
    gangleP = QLineF( P["16"],P["161"] ).angle();
    QPainterPath Gorlovina[3];
    double angle[3];
    angle[0] = 0;angle[1] = 0;angle[2] = 0;
    if( LD("GorlovinaBalance")!= 0 )
    {
        QList < QPainterPath > GorArr;
        if( LD("GorlovinaBalance") > 0 )
        {
           if(LD("GorlovinaBalance")>GorRight.length())
                H("GorlovinaBalance") = GorRight.length();
           GorArr = splitPath( GorRight, GorRight.length() - LD("GorlovinaBalance"), LD("GorlovinaShag") );
           Gorlovina[0] = GorLeft;
           Gorlovina[1] = GorArr.at(1);
           Gorlovina[1] = Gorlovina[1].toReversed();
           //angle[1] = Gorlovina[1].angleAtPercent(0)-Gorlovina[0].angleAtPercent(1);
           angle[1] = gangleP - gangleS;
           Gorlovina[2] = GorArr.at(0);
           P["gorlovina1"] = P["121dialog"];
           P["gorlovina2"] = P["16dialog"];
        }else
        {
            if(-LD("GorlovinaBalance")>GorLeft.length())
                 H("GorlovinaBalance") = -GorLeft.length();
           GorArr = splitPath( GorLeft, GorLeft.length() + LD("GorlovinaBalance"), LD("GorlovinaShag") );
           Gorlovina[0] = GorArr.at(0);
           Gorlovina[1] = GorArr.at(1);
           Gorlovina[1] = Gorlovina[1].toReversed();
           Gorlovina[2] = GorRight;
           //angle[1] = Gorlovina[1].angleAtPercent(0)-Gorlovina[2].angleAtPercent(1);
           angle[1] = gangleS - gangleP;
           P["gorlovina1"] = P["16dialog"];
           P["gorlovina2"] = P["121dialog"];
        }
    }else
    {
        Gorlovina[0] = GorLeft;
        Gorlovina[2] = GorRight;
        cpath["g_left_e"] = C2DPath(GorLeft);
        cpath["g_right_e"] = C2DPath(GorRight);
    }



    C2DLayer * templayer;
    bool tempbool;
    if( ( ( LD("is_clasp") == 1 ) && ( LD("clasp_location") == 0 ) && (LD("is_intersect_gorlovina")==1) )||
        ( ( LD("is_cut") == 1 ) && ( LD("cut_location") == 0 ) )  )
                tempbool = false;
    else
        tempbool = true;


    PpathItem * myigor1 = ppath(  Sync( attr( SYNC_NAME,  QString( "Gor1" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "11dialog" ) ),
                        LM->thick_dashed() ), &Gorlovina[0], 0, 0,
                  true );
    //ppath(  Sync( attr( SYNC_NAME,  QString( "Gor1__" ) ),
    //                    attr( SYNC_TYPE, C2DSync::Ppath ),
    //                    attr( SYNC_LIST, MakeList( "11dialog" ) ),
    //                    LM->bold_solid() ), &Gorlovina[0], 0, 0,
    //              tempbool );

    PpathItem * myigor3, * myigor4;
    if( LD("GorlovinaBalance") != 0 )
    {
        bool mygorbool = true;
        templayer = LM->bold_solid();
        if( ( LD("clasp_type") == 0 ) || ( LD("clasp_type") == 1 ) || ( LD("clasp_type") == 2 ) )
            if(( LD("is_clasp") == 1 ) && ( LD("is_intersect_gorlovina") == 1 ))
            {
                if(( LD("clasp_location") == 0 )&&( LD("GorlovinaBalance") > 0 ))
                     mygorbool = false;
                if(( LD("clasp_location") == 1 )&&( LD("GorlovinaBalance") < 0 ))
                     mygorbool = false;
            }

        myigor3 = ppath(  Sync( attr( SYNC_NAME,  QString( "Gor2" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "gorlovina1" ) ),
                                LM->thick_dashed() ), &Gorlovina[1], angle[1], 0,
                  true );
        ppath(  Sync( attr( SYNC_NAME,  QString( "Gor2doubledum" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "gorlovina1" ) ),
                                        LM->bold_solid() ), &Gorlovina[1], angle[1], 0,
                          mygorbool );
        myigor4 = ppath(  Sync( attr( SYNC_NAME,  QString( "Gor22" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "gorlovina2" ) ),
                                        LM->thick_dashed() ), &Gorlovina[1], 0, 0,
                          true );
    }
    if(( LD("is_clasp") == 1 ) && ( LD("is_intersect_gorlovina") == 1 ) &&
            ( LD("clasp_location") == 1 ))
                templayer = LM->thick_dashed();
    else
        templayer = LM->bold_solid();
    PpathItem * myigor2 = ppath(  Sync( attr( SYNC_NAME,  QString( "Gor3" ) ),
                        attr( SYNC_TYPE, C2DSync::Ppath ),
                        attr( SYNC_LIST, MakeList( "172dialog" ) ),
                            LM->thick_dashed() ), &Gorlovina[2], 0, 0,
                  true );


    if( LD("GorlovinaBalance") == 0 )
    {
        P["Gl"] = myigor1->getEnd();
        P["Gr"] = myigor2->getEnd();
    }
    else if( LD("GorlovinaBalance") > 0 )
    {
        P["Gl"] = myigor3->getEnd();
        P["Gr"] = myigor2->getEnd();
        temppath = myigor1->myshape_fromstart(1);
        temppath.connectPath(myigor3->myshape_fromstart(1));
        cpath["g_left_e"] = C2DPath(temppath);
        cpath["g_right_e"] = C2DPath(myigor2->myshape_fromstart(1));
    }else
    {
        P["Gl"] = myigor1->getEnd();
        P["Gr"] = myigor3->getEnd();
        cpath["g_left_e"] = C2DPath(myigor1->myshape_fromstart(1));
        temppath = myigor2->myshape_fromstart(1);
        temppath.connectPath(myigor3->myshape_fromstart(1));
        cpath["g_right_e"] = C2DPath(temppath);
    }

    point( Sync( attr( SYNC_NAME,  QString( "Gl" ) ),
                attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "Gl" ) ),
                LM->bold_solid() ),
          true );

    point( Sync( attr( SYNC_NAME,  QString( "Gr" ) ),
                attr( SYNC_TYPE, C2DSync::Point ),
                attr( SYNC_LIST, MakeList( "Gr" ) ),
                LM->bold_solid() ),
          true );
    if( LB("g_p_nomirror") == false )
    {
        cpath["g_leftm_e"] = cpath["g_left_e"];
        cpath["g_rightm_e"] = cpath["g_right_e"];
    }

    cpath[ "g_leftm_end" ] = C2DPath( cpath["g_leftm_e"].shape(),0,1 );
    cpath[ "g_rightm_end" ] = C2DPath( cpath["g_rightm_e"].shape(),0,1 );
    P["m121"] = cpath["g_leftm_e"].shape().pointAtPercent(1);
    P["m16"] = cpath["g_rightm_e"].shape().pointAtPercent(1);
    P["m14-1"] = cpath["mirror_proima"].shape().pointAtPercent(0);
    P["m14-2"] = cpath["mirror_proima"].shape().pointAtPercent(1);
    P["m22"] = P["22"];
    P["m36"] = P["36"];
    double tempangle;
    tempangle = QLineF(P["22"],P["125"]).angleTo( QLineF(P["22"],P["125-1"]) );
    P["m14-11"] = Unicus::rPoint( P["m14-1"],P["m22"], tempangle );
    line1.setPoints(P["m14-11"],P["m121"]);
    line2.setPoints(P["m22"],P["125"]);
    line1.intersect(line2,&P["m125"]);
    P["m125-1"] = Unicus::rPoint(P["m125"],P["m22"],-tempangle);

    tempangle = QLineF(P["36"],P["161-1"]).angleTo( QLineF(P["36"],P["161"]) );
    P["m14-22"] = Unicus::rPoint( P["m14-2"],P["m36"], -tempangle );
    line1.setPoints(P["m14-22"],P["m16"]);
    line2.setPoints(P["m36"],P["161"]);
    line1.intersect(line2,&P["m161"]);
    P["m161-1"] = Unicus::rPoint(P["m161"],P["m36"],tempangle);


    temppath = cpath["g_leftm_e"].shape();
    double end125m = QLineF( temppath.pointAtPercent(1),P["m125"] ).angle();
    end125m = -end125m + 180;
    temppath.lineTo( P["m125"] );
    temppath.lineTo( P["m22"] );
    temppath.lineTo(P["m125-1"]);
    temppath.lineTo(P["m14-1"]);
    tempangle = cGeometry::qpintrbtD( QLineF(P["347"],P["441"]),cpath["mirror_proima"].shape(),1 );
    temppath.connectPath( cpath["mirror_proima"].myshapefromstart( tempangle/cpath["mirror_proima"].length() ) );
    //temppath.moveTo(P["347"]);
    temppath.lineTo(P["441"]);
    temppath.lineTo(P["541"]);
    temppath.lineTo(P["943"]);
    temppath.lineTo(P["91"]);
    cpath["m_spinka"] = C2DPath(temppath);

    cpath["mirror_proima"].toReversed();
    temppath = cpath["g_rightm_e"].shape();
    double end26m = QLineF( temppath.pointAtPercent(1),P["m161"] ).angle();
    end26m = -end26m + 180;
    temppath.lineTo( P["m161"] );
    temppath.lineTo( P["m36"] );
    temppath.lineTo(P["m161-1"]);
    temppath.lineTo(P["m14-2"]);
    tempangle = cGeometry::qpintrbtD( QLineF(P["347"],P["441'"]),cpath["mirror_proima"].shape(),1 );
    temppath.connectPath( cpath["mirror_proima"].myshapefromstart( tempangle/cpath["mirror_proima"].length() ) );
    //temppath.moveTo(P["347"]);
    temppath.lineTo(P["441'"]);
    temppath.lineTo(P["541'"]);
    temppath.lineTo(P["943'"]);
    temppath.lineTo(P["971'"]);
    temppath.lineTo(P["971"]);
    cpath["m_polka"] = C2DPath(temppath);



    gorl = cpath["g_left_e"].shape().length();
    gorr = cpath["g_right_e"].shape().length();
    gorlm = cpath["g_leftm_e"].shape().length();
    gorrm = cpath["g_rightm_e"].shape().length() ;
    ////КОНЕЙ ПРОЙМы И ГОРЛОВИНы
    Unicus::console( "gorr",gorr );
    Unicus::console( "gorrm",gorrm );
    Unicus::console( "gorl",gorl );
    Unicus::console( "gorlm",gorlm );
    ////////////ПЕРЕОПРЕДЕЛЕНИИ ЛИНИИ СШИВАНИЯ ВЕРХНЕЙ
    //double tempangle;
    line1.setPoints(P["22"],P["125"]);
    line2.setPoints(P["22"],P["125-1"]);
    tempangle = line1.angleTo( line2 );
    P["pl-rtd"] = Unicus::rPoint( P["pl"], P["22"], tempangle );
    line2.setPoints(P["Gl"],P["pl-rtd"]);
    line1.intersect( line2, &P["125end"] );
    P["125end-1"] = Unicus::rPoint( P["125end"], P["22"], -tempangle );

    line1.setPoints(P["36"],P["26"]);
    line2.setPoints(P["36"],P["26-1"]);
    tempangle = line1.angleTo( line2 );
    P["pr-rtd"] = Unicus::rPoint( P["pr"], P["36"], tempangle );
    line2.setPoints(P["Gr"],P["pr-rtd"]);
    line1.intersect( line2, &P["26end"] );
    P["26end-1"] = Unicus::rPoint( P["26end"], P["36"], -tempangle );

    line( Sync( attr( SYNC_NAME,  QString( "Gl-pl-rtd" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "Gl", "pl-rtd" ) ),
                LM->thick_dashed() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "Gl-125end" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "Gl", "125end" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "22-125end" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "22", "125end" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "22-125end-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "22", "125end-1" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "pl-125end-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "pl", "125end-1" ) ),
                LM->bold_solid() ),
          true );

///////////////////////////////////////////////right
    line( Sync( attr( SYNC_NAME,  QString( "Gr-pr-rtd" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "Gr", "pr-rtd" ) ),
                LM->thick_dashed() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "Gr-26end" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "Gr", "26end" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "36'-26end" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "36'", "26end" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "36'-26end-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "36'", "26end-1" ) ),
                LM->bold_solid() ),
          true );
    line( Sync( attr( SYNC_NAME,  QString( "pr-26end-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                 attr( SYNC_LIST, MakeList( "pr", "26end-1" ) ),
                LM->bold_solid() ),
          true );
    double templangth;

   ///ZASTEJKA : START ***/
    this->celno_collar();

    P["cl_l_dwn"] = P["91"] + QPointF( LD("clasp_move_by_niz"),0 );
    P["cl_r_dwn"] = P["971"] + QPointF( LD("clasp_move_by_niz"),0 );
    collar->setlength( 10, P["cl_l_dwn"].x() );
    collar->setlength( 11, P["cl_l_dwn"].y() );
    collar->setlength( 12, P["cl_r_dwn"].x() );
    collar->setlength( 13, P["cl_r_dwn"].y() );
    tempbool=false;
    //PpathItem * clasp_gor;
    C2DPath clasp_gor;
    QPainterPath Clasp_path;
    QList < QPainterPath > ClaspArr;
    double cl_width_on_gorl = -1;

    if( LD("is_clasp") == 1 )
    {
        if( LD("is_intersect_gorlovina") == 1 )
        {
            if( LD("clasp_location") == 0 )
            {
               //Смещаем верх из точки спинки
                Clasp_path = cpath["g_left_e"].myshapefromstart();
                temppath = cpath["g_leftm_e"].myshapefromstart();
                //this->memwid[2]->SetMinMax( -qpath["g_minus"].length()/10+0.2,qpath["g_plus"].length()/10-0.2 );
                collar->setSpinminmax( 2, -Clasp_path.length()/10+0.2, temppath.length()/10-0.2 );
                H("clasp_move_by_gorlovina") = -collar->memwidValue(2)*10;
                clasp_gor = C2DPath( temppath, 0, 1);//11dialog
                P["g_end"]= clasp_gor.myshapefromstart().pointAtPercent(1);
                Clasp_path = Clasp_path.toReversed();
                P["clasp_gor_start"] = Clasp_path.pointAtPercent(0);
                templangth = Clasp_path.length();
                Clasp_path.connectPath( clasp_gor.myshapefromstart() );
                templangth = templangth + LD("clasp_move_by_gorlovina");
                cl_width_on_gorl = templangth;
                /////////////////////////////***********************************
                P["cl_dwn"] = P["91"] + QPointF( LD("clasp_move_by_niz"),0 );

                line1.setPoints( Clasp_path.pointAtPercent( templangth/Clasp_path.length() )
                                 , P["cl_dwn"] );

                double gorlovinatmpd = cGeometry::qpintrbtD( line1,Clasp_path );
                if( gorlovinatmpd != 0 )
                    templangth = gorlovinatmpd;

                //collar->setSpinValue( 2,-(templangth - cpath["g_left_e"].length())/10 );
                /////////////////////////////***********************************
                clasp_gor = C2DPath( Clasp_path );
                temppath = clasp_gor.myshapefromstart( templangth/clasp_gor.length() );
                cpath["clasp_g_clasp"] = C2DPath(temppath);
                //clasp_gor = ppath(  Sync( attr( SYNC_NAME, QString( "Cl_gend" ) ),
                //                          attr( SYNC_TYPE, C2DSync::Ppath ),
                //                          attr( SYNC_LIST, MakeList( "clasp_gor_start" ) ),
                //                       LM->bold_solid() ), &temppath, 0, 0,
                //                  true );
                P["clasp_down_strt"] = P["91"];
                tempbool = true;                
            }else if( LD("clasp_location") == 1 )
            {
                //Смещаем верх из точки полочки
                Clasp_path = cpath["g_right_e"].myshapefromstart();
                temppath = cpath["g_rightm_e"].shape();
                collar->setSpinminmax( 2, -Clasp_path.length()/10+0.2, temppath.length()/10-0.2 );
                H("clasp_move_by_gorlovina") = collar->memwidValue(2)*10;
                clasp_gor = C2DPath( temppath, 0, 1);
                P["g_end"]=clasp_gor.myshapefromstart().pointAtPercent(1);
                Clasp_path = Clasp_path.toReversed();
                P["clasp_gor_start"] = Clasp_path.pointAtPercent(0);
                templangth = Clasp_path.length();
                templangth = templangth + LD("clasp_move_by_gorlovina");
                cl_width_on_gorl = templangth;
                Clasp_path.connectPath( clasp_gor.myshapefromstart() );
                /////////////////////////////***********************************
                P["cl_dwn"] = P["971"] + QPointF( LD("clasp_move_by_niz"),0 );
                line1.setPoints( Clasp_path.pointAtPercent( templangth/Clasp_path.length() )
                                 , P["cl_dwn"] );
                double gorlovinatmpd = cGeometry::qpintrbtD( line1,Clasp_path );
                if( gorlovinatmpd != 0 )
                    templangth = gorlovinatmpd;

                collar->setSpinValue( 2,(templangth - cpath["g_right_e"].length())/10 );
                /////////////////////////////***********************************
                clasp_gor = C2DPath( Clasp_path );
                temppath = clasp_gor.myshapefromstart( templangth / clasp_gor.length() );
                cpath["clasp_g_clasp"] = C2DPath(temppath);
                //clasp_gor = ppath(  Sync( attr( SYNC_NAME,  QString( "Cl_gend" ) ),
                //                          attr( SYNC_TYPE, C2DSync::Ppath ),
                //                          attr( SYNC_LIST, MakeList( "clasp_gor_start" ) ),
                //                       LM->bold_solid() ), &temppath, 0, 0,
                //                  true );
                P["clasp_down_strt"] = P["971"];
                tempbool = true;
            }else
            {
                // работаем с линией плечевого среза;
            }
        }
    }
    zipper = LD("clasp_move_by_gorlovina");
    P["cl_up"] = cpath["clasp_g_clasp"].shape().pointAtPercent(1);
    clasp_sign3_path = Clasp_path;
    clasp_sign3_start = clasp_sign3_path.length() - cpath["clasp_g_clasp"].shape().length();
    clasp_sign4_path = Clasp_path;
    clasp_sign4_start = cpath["clasp_g_clasp"].shape().length();
    //line1.setPoints( P["cl_up"], P["cl_dwn"] );
    //double doublleofpath = cGeometry::qpintrbtD( line1,Clasp_path );
    //P["cl_up"] = Clasp_path.pointAtPercent( doublleofpath/Clasp_path.length() );
    QPainterPath ppptahn = cpath["clasp_g_clasp"].shape();
    //if(tempbool)
    //ppath(  Sync( attr( SYNC_NAME,  QString( "Cl_gdsfg3" ) ),
    //                                  attr( SYNC_TYPE, C2DSync::Ppath ),
    //                                  attr( SYNC_LIST, MakeList( "clasp_gor_start" ) ),
    //                                  LM->thick_red() ), &ppptahn, 0, 0,
    //                                  tempbool );
    C2DPath cut_gor;
    QPainterPath cut_path;
    QLineF Cut_line;

    C2DPath c2dp( temppath );

    double cut_angle=0,cut_sign_sp_angle=0,cut_sign_pol_angle=0;
    bool cut_sign=false, is_cut=false;
    if(LD( "is_cut" ) == 1)
    {
       // H("is_cut") = 1; //есть ли застежка
       // H("cut_location") = 0; // спинка или полочка
       // H("cut_left") = 10; // положительное напправо
       // H("cut_length") = 70; // длина
       // H("cut_angle") = 70; // направление
        if( LD("cut_location") == 0 ) // спинка или полочка)
        {
            is_cut=true;
            //спинка
            cut_path = cpath["g_left_e"].myshapefromstart();
            temppath = cpath["g_leftm_e"].myshapefromstart();
            cut_gor = C2DPath(temppath,0,1);
            temppath = cut_gor.myshapefromstart();
            cut_path = cut_path.toReversed();
            P["cut_gor_start"] = cut_path.pointAtPercent(0);
            templangth = cut_path.length();
            templangth = templangth + LD("cut_left");
            cut_path.connectPath( temppath );
            cut_gor = C2DPath(cut_path);
            cpath["cut_g_cut"] = C2DPath( cut_gor.myshapefromstart( templangth/cut_gor.length() ) );
            P["c_end"] = cpath["cut_g_cut"].shape().pointAtPercent(1);
            //ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_gend" ) ),
                      //                attr( SYNC_TYPE, C2DSync::Ppath ),
                      //                attr( SYNC_LIST, MakeList( "cut_gor_start" ) ),
                      //             LM->bold_solid() ), &temppath, 0, 0,
                      //        true );cut_gor
            Cut_line.setPoints( P["c_end"],QPointF(P["c_end"].x()+1,P["c_end"].y()+1) );
            Cut_line.setAngle( ( cut_angle + 180 ) + LD("cut_angle") );
            Cut_line.setLength( LD("cut_length") );
            P["c_l_s"] = Cut_line.p1();
            P["c_l_e"] = Cut_line.p2();
        }else if( LD("cut_location") == 1 ) //  полочка
        {
            is_cut=true;
            cut_path = cpath["g_right_e"].myshapefromstart();
            cut_gor = C2DPath(cpath["g_rightm_e"].myshapefromstart(),0,1);
            temppath = cut_gor.myshapefromstart();
            cut_path = cut_path.toReversed();
            P["cut_gor_start"] = cut_path.pointAtPercent(0);
            templangth = cut_path.length();
            templangth = templangth + LD("cut_left");
            cut_path.connectPath( temppath );
            cut_gor = C2DPath(cut_path);
            cpath["cut_g_cut"] = C2DPath( cut_gor.myshapefromstart( templangth/cut_gor.length() ) );
            P["c_end"] = cpath["cut_g_cut"].shape().pointAtPercent(1);
            //cut_gor = ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_gend" ) ),
            //                          attr( SYNC_TYPE, C2DSync::Ppath ),
            //                          attr( SYNC_LIST, MakeList( "cut_gor_start" ) ),
            //                       LM->bold_solid() ), &temppath, 0, 0,
            //                  true );

            Cut_line.setPoints( P["c_end"],QPointF(P["c_end"].x()+1,P["c_end"].y()+1) );
            Cut_line.setAngle( ( cut_angle ) + LD("cut_angle") );
            Cut_line.setLength( LD("cut_length") );
            P["c_l_s"] = Cut_line.p1();
            P["c_l_e"] = Cut_line.p2();
        }else
        {
            //разрез в плечевом шве
            cut_sign = true;
            QLineF sp_line1( P["Gl"], P["125end"]   );
            QLineF sp_line2( P["125end-1"], P["pl"] );
            QLineF pol_line1( P["Gr"], P["26end"]   );
            QLineF pol_line2( P["26end-1"], P["pr"] );
            if( LD("cut_length") > sp_line1.length() )
            {
                P["cut_sign_sp"] = sp_line2.pointAt( ( LD("cut_length") - sp_line1.length() ) / sp_line2.length() );
                cut_sign_sp_angle = sp_line2.angle();
            }
            else
            {
                P["cut_sign_sp"] = sp_line1.pointAt( LD("cut_length")/sp_line1.length() );
                cut_sign_sp_angle = sp_line1.angle();
            }
            if( LD("cut_length") > pol_line1.length() )
            {
                P["cut_sign_pol"] = pol_line2.pointAt( ( LD("cut_length") - pol_line1.length() ) / pol_line2.length() );
                cut_sign_pol_angle = pol_line2.angle();
            }
            else
            {
                P["cut_sign_pol"] = pol_line1.pointAt( LD("cut_length") / pol_line1.length() );
                cut_sign_pol_angle = sp_line1.angle();
            }
        }

    }
    //ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_gend" ) ),
    //                                 attr( SYNC_TYPE, C2DSync::Ppath ),
    //                                 attr( SYNC_LIST, MakeList( "cut_gor_start" ) ),
    //                                 LM->bold_solid() ), cpath["cut_g_cut"].pointer(), 0, 0,
    //                            is_cut );
    line( Sync( attr( SYNC_NAME,  QString( "c_line" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "c_l_s", "c_l_e" ) ),
                LM->bold_solid() ),
          is_cut );

    sign( Sync( attr( SYNC_NAME, QString( "csp" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "cut_sign_sp" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -cut_sign_sp_angle-90 ) ),
          cut_sign );

    sign( Sync( attr( SYNC_NAME, QString( "cpol" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "cut_sign_pol" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -cut_sign_pol_angle+90 ) ),
          cut_sign );
    //////////////////////////////////cl_up new
    double koeftemp=1;
    if( LD("is_clasp") == 1 )
        if( ( LD("clasp_location") == 0 ) || ( LD("clasp_location") == 1 ) )
        {
            if( LD("clasp_location") == 0 )
            {
                koeftemp = -1;
                temppath = cpath["g_left_e"].myshapefromstart().toReversed();
                C2DPath tmppath = C2DPath( cpath["g_leftm_e"].myshapefromstart(),0,1 );
                temppath.connectPath( tmppath.myshapefromstart() );
            }else if( LD("clasp_location") == 1 )
            {
                koeftemp=1;
                temppath = cpath["g_right_e"].myshapefromstart().toReversed();
                C2DPath tmppath = C2DPath( cpath["g_rightm_e"].myshapefromstart(),0,1 );
                temppath.connectPath( tmppath.myshapefromstart() );
            }
            P["claspwidthlimit"] = this->claspwidthlimit( temppath, QLineF(P["cl_up"],P["cl_dwn"]) );
        }

    ///////////////////////////////////cl_up_new end


    double planka_adds = 0;

    bool clusrebuild=false;
    double gorloboldleft = -1;
    bool gorloboldlefte = false;
    bool zu=false,bu=false,hang=false,hang_no_loop=false,planka=false;
    double Zus1,Zus2,tmpdouble=0;
    tempbool = false;

    bool collar_leftright=false;
    if(( LD("is_intersect_gorlovina") == 1 ))
    if( ( LD("clasp_form") == 1 ) )
    {
        if( LD("clasp_type") == 1 ) //тип застежки 0-пуговицы 1-молния 2-навесные петли
        {
            if( LD("clasp_location") == 0 )
                    koeftemp = koeftemp * -1;
            tempbool = true;
            //"clasp_decor"
            //H("clasp_t1_width") = 10; //ширина молнии SH3
            //H("clasp_t1_length") = 70; //длина молнии L1
            //H("clasp_t1_begining") = 10; //расстояние от горловины до молнии R1
            line1.setPoints( P["cl_up"],P["cl_dwn"] );
            line2 = line1;
            line2.setAngle( line2.angle()+(90*koeftemp) );

            line2.setLength( LD("clasp_t1_width")/2 );
            P["Zu1"] = line2.p2();
            line2.setAngle( line2.angle()+180 );
            P["Zu2"] = line2.p2();
            line2.setPoints( P["cl_dwn"],P["cl_up"] );
            line2.setAngle( line2.angle()-90*koeftemp );
            line2.setLength( LD("clasp_t1_width")/2 );
            P["Zu3"] = line2.p2();
            line2.setAngle( line2.angle()+180 );
            P["Zu4"] = line2.p2();
            if( LD("clasp_t1_width") != 0 )
            {
            //    tmpdouble = cGeometry::qpintrbtD( QLineF(P["Zu1"],P["Zu3"]),temppath,2);
            //    P["Zu1"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
            //    tmpdouble = cGeometry::qpintrbtD( QLineF(P["Zu2"],P["Zu4"]),temppath,2);
            //    P["Zu2"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
            //}else
            //{
                clusrebuild = true;
                tmpdouble = cGeometry::qpintrbtD( QLineF(P["Zu1"],P["Zu3"]),temppath,0.5);
                if(LD("clasp_location")==0)
                    collar_clasp_gl = temppath.length() - tmpdouble;
                else if(LD("clasp_location") == 1)
                    collar_clasp_gl = tmpdouble;
                collar_leftright =true;
                P["Zu1"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
                line2.setPoints( P["cl_up"],P["cl_dwn"] );
                line1.setPoints( P["Zu1"],P["Zu1"] + QPointF( 1*koeftemp,0 ) );
                line1.setAngle( line2.angle()-90*koeftemp );
                line1.setLength( LD("clasp_t1_width") );
                P["Zu2"] = line1.p2();
                gorloboldlefte = true;
                gorloboldleft = tmpdouble;
            }

            zu=true;
            line1.setPoints(P["Zu1"],P["Zu3"]);
            line2.setPoints(P["Zu2"],P["Zu4"]);
            P["ZuSign1s"] = line1.pointAt( LD("clasp_t1_begining")/line1.length() );
            P["ZuSign1e"] = line1.pointAt(
                        (LD("clasp_t1_begining")+LD("clasp_t1_length"))/line1.length() );
            Zus1 = -line1.angle()-90*koeftemp;
            P["ZuSign2s"] = line2.pointAt( LD("clasp_t1_begining")/line2.length() );
            P["ZuSign2e"] = line2.pointAt(
                        (LD("clasp_t1_begining")+LD("clasp_t1_length"))/line2.length() );
            Zus2 = -line2.angle()+90*koeftemp;
            P["CluE"] = P["Zu2"];
            P["CluS"] = P["Zu1"];
            colclasptype = -LD("clasp_t1_width")/2;
        }else if( LD("clasp_type") == 0 )
        {
            tempbool = true;
            //H("clasp_t0_width") = 10; //ширина заноса SH1
            //H("clasp_t0_btns_num") = 4; //количество пуговиц
            //H("clasp_t0_begining") = 90; //расстояние от горловины до первой пуговицы
            //H("clasp_t0_l_between") = 100; //расстояние между пуговицами
            line1.setPoints( P["cl_up"],P["cl_dwn"] );//Всегда справа от основной линии
            line2 = line1;
            templangth = -90*koeftemp;
            line2.setAngle( line1.angle() + templangth );
            line2.setLength( LD("clasp_t0_width") );
            //новая линия становится жирной
            P["Bu1"] = line2.p2();
            line2.setPoints( P["cl_dwn"], P["cl_up"] );
            line2.setAngle( line1.angle() + templangth );
            line2.setLength( LD("clasp_t0_width") );
            P["Bu2"] = line2.p2();
            if( LD("clasp_decor") == 0 )
            {
                tmpdouble = cGeometry::qpintrbtD( QLineF(P["Bu1"],P["Bu2"]),temppath,0.5);
                P["Bu1"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
                colclasptype = tmpdouble - cl_width_on_gorl;
            }else
            {
                if( LD("clasp_t0_width")!=0 )
                     clusrebuild = true;
                //tmpdouble = cGeometry::qpintrbtD( QLineF(P["Bu1"],P["Bu2"]),temppath,2);
                line2.setPoints( P["cl_up"],P["cl_dwn"] );
                line1.setPoints( P["cl_up"], P["cl_up"] + QPointF( 1,1 ) );
                line1.setAngle( line2.angle()-90*koeftemp );
                line1.setLength( LD("clasp_t0_width") );
                P["Bu1"] = line1.p2();
                colclasptype = LD("clasp_t0_width");
            }
            //Unicus::console("colclasptype",colclasptype);
            //    пуговицы на новой линии , новая линия до пересечения с горловиной продлевается
            line2.setPoints( P["cl_up"],P["cl_dwn"] );
            for(int i = 0; i < LD("clasp_t0_btns_num"); i++ )
            {
                templangth = ( LD("clasp_t0_begining") + LD("clasp_t0_l_between") * i )/line2.length();
                if(templangth>1)
                    templangth = 1;
                P["But"+QString::number(i)] = line2.pointAt( templangth );
            }
            // старая линия становится тонкой
            bu=true;
            P["CluE"] = P["Bu1"];
            P["CluS"] = P["cl_up"];

        }else if( LD("clasp_type") == 2 ) //навесные петли
        {
            tempbool = true;
            //H("clasp_t2_width") = 10; //ширина заноса SH2
            //H("clasp_t2_btns_num") = 4; //количество пуговиц
            //H("clasp_t2_begining") = 90; //расстояние от горловины до первой пуговицы
            //H("clasp_t2_l_between") = 100; //расстояние между пуговицами
            if( LD("hanging_loop") == 0 ) //с заходом
            {
                //.ширина захода делится на пополам и откладывается в каждую сторону
                line1.setPoints( P["cl_up"],P["cl_dwn"] );
                line2 = line1;
                line2.setAngle( line2.angle()+90*koeftemp );
                line2.setLength( LD("clasp_t2_width") );
                P["Hang1"] = P["cl_up"];
                line2.setAngle( line2.angle()+180 );
                P["Hang2"] = line2.p2();
                P["cl_up2"] = line2.pointAt(0.5);
                line2.setPoints( P["cl_dwn"],P["cl_up"] );
                line2.setAngle( line2.angle()-90*koeftemp );
                line2.setLength( LD("clasp_t2_width") );
                P["Hang3"] = P["cl_dwn"];
                line2.setAngle( line2.angle()+180 );
                P["Hang4"] = line2.p2();
                P["cl_dwn"] = line2.pointAt(0.5);
                P["cl_up"] = P["cl_up2"];
                bool colclaspbool = false;
                if( LD("clasp_t2_width") != 0 )
                    if( LD("clasp_decor") == 0 )
                    {
                        tmpdouble = cGeometry::qpintrbtD( QLineF(P["Hang2"],P["Hang4"]),temppath,0.5);
                        double tmpdouble2 = tmpdouble;
                        P["Hang2"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
                        tmpdouble = cGeometry::qpintrbtD( QLineF(P["cl_up"],P["cl_dwn"]),temppath,0.5);
                        P["cl_up"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
                        colclasptype = tmpdouble2 - tmpdouble;
                        colclaspbool = true;
                    }else
                    {
                        clusrebuild = true;
                        tmpdouble = cGeometry::qpintrbtD( QLineF(P["Hang1"],P["Hang3"]),temppath,0.5 );
                        P["Hang1"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
                        line2.setPoints( P["Hang1"],P["Hang3"] );
                        line1.setPoints( P["Hang1"],P["Hang1"] + QPointF( 1,0 ) );
                        line1.setAngle( line2.angle()-90*koeftemp );
                        line1.setLength( LD("clasp_t2_width") );
                        P["Hang2"] = line1.p2();
                        P["CluE"] = P["Hang2"];
                        P["CluS"] = P["Hang1"];
                    }

                line2.setPoints( P["Hang2"],P["Hang4"] );
                //лнии продлебаются до горловины и до низа, как и выше, пуговицы всегда справа и на полке и на спинке
                //жирная линия только правая остальные пунктир, и на полочке и на спинке.
                hang = true;
                if( colclaspbool == false )
                    colclasptype = LD("clasp_t2_width");
            }
            else // в стык
            {
                colclasptype = 0;
                //ничего не откладываем нкуда. на линии ставим пуговицы она жирная
                line2.setPoints( P["cl_up"],P["cl_dwn"] );
                hang_no_loop = true;
            }
            //расставляем пуговицы
            for(int i = 0; i < LD("clasp_t2_btns_num"); i++ )
            {
                templangth = ( LD("clasp_t2_begining") + LD("clasp_t2_l_between") * i )/line2.length();
                if(templangth>1)
                    templangth = 1;
                P["But"+QString::number(i)] = line2.pointAt( templangth );
            }
        }
    }else //планка
    {
        if( LD("clasp_location") == 0 )
                koeftemp = koeftemp * -1;
        tempbool = true;
        //ширина планки откладывается вправо и влево(делится пополам) жирная как левая так и правая
        // средняя пунктир , кнопки на средней. до горловины и до низа
        //H("clasp_t3_width") = 10; //ширина заноса SH4 планки
        //H("clasp_t3_btns_num") = 5; //количество пуговиц для планки
        //H("clasp_t3_begining") = 90; //расстояние от горловины до первой пуговицы на планке
        //H("clasp_t3_l_between") = 100; //расстояние между пуговицами    планки
        line1.setPoints( P["cl_up"],P["cl_dwn"] );
        line2 = line1;
        line2.setAngle( line2.angle()+90*koeftemp );
        line2.setLength( LD("clasp_t3_width")/2 );
        //Unicus::console( "-----------)!!-----", line2.length() );
        P["Zu1"] = line2.p2();
        line2.setAngle( line2.angle()+180 );
        P["Zu2"] = line2.p2();
        line2.setPoints( P["cl_dwn"],P["cl_up"] );
        line2.setAngle( line2.angle()-90*koeftemp );
        line2.setLength( LD("clasp_t3_width")/2 );
        P["Zu3"] = line2.p2();
        line2.setAngle( line2.angle()+180 );
        P["Zu4"] = line2.p2();
        planka=true;


        if( LD("clasp_t3_width") != 0 )
        {
            clusrebuild = true;
            tmpdouble = cGeometry::qpintrbtD( QLineF(P["Zu1"],P["Zu3"]),temppath,0.5);
            collar_leftright = true;
            if(LD("clasp_location") == 0)
                collar_clasp_gl = temppath.length() - tmpdouble;
            else if(LD("clasp_location") == 1)
                collar_clasp_gl = tmpdouble;
            gorloboldleft = tmpdouble;
            P["Zu1"] = temppath.pointAtPercent( tmpdouble/temppath.length() );
            line2.setPoints( P["Zu1"],P["Zu3"] );
            line1.setPoints( P["Zu1"],P["Zu1"] + QPointF( 1,0 ) );
            line1.setAngle( line2.angle()-90*koeftemp );
            line1.setLength( LD("clasp_t3_width") );
            P["Zu2"] = line1.p2();
            line2.setPoints(P["cl_up"],P["cl_dwn"]);
            line1.setPoints(P["Zu1"],P["Zu2"]);
            line1.intersect(line2,&P["cl_up"]);


            gorloboldlefte = true;
        }
        line2.setPoints(P["cl_up"],P["cl_dwn"]);
        for(int i = 0; i < LD("clasp_t3_btns_num"); i++ )
        {
            templangth = ( LD("clasp_t3_begining") + LD("clasp_t3_l_between") * i )/line2.length();
            if(templangth>1)
                templangth = 1;
            P["But"+QString::number(i)] = line2.pointAt( templangth );
        }
        P["CluE"] = P["Zu2"];
        P["CluS"] = P["Zu1"];
        if( ( D("vorot_planka") == 1 ) && ( D("is_vorot") == 1 ) && ( D("vorot_type") == 1 ) )
        {
            double vorot_height=20;
            if(D("vorot_dsgn")==0)
            {
                if( LD("clasp_location") == 0 )
                    vorot_height = D("H3");
                if( LD("clasp_location") == 1 )
                    vorot_height = D("H1");
            }else
            {
                if( LD("clasp_location") == 0 )
                {
                    vorot_planka_sign = true;
                    if( D("H3") > D("H3lev") )
                        vorot_height = D("H3");
                    else
                        vorot_height = D("H3lev");
                    vorot_planka_sign_double = fabs( D("H3lev") - D("H3") );
                }
                if( LD("clasp_location") == 1 )
                {
                    vorot_planka_sign = true;
                    if( D("H1") > D("H1lev") )
                        vorot_height = D("H1");
                    else
                        vorot_height = D("H1lev");
                    vorot_planka_sign_double = fabs( D("H1lev") - D("H1") );
                }
            }
            Unicus::console( "vorot_height",vorot_height );
            vorot_planka_b = true;
            line1.setPoints( P["Zu3"],P["Zu1"] );
            line1.setLength( line1.length() + vorot_height );
            P["vp_1"] = line1.p2();
            line1.setPoints( P["Zu4"],P["Zu2"] );
            line2.setPoints( P["vp_1"],P["Zu3"] );
            line2.setAngle( line2.angle() + 90 );
            line1.intersect( line2, &P["vp_2"] );
            if(vorot_planka_sign_double == 0)
                vorot_planka_sign = false;
            if(vorot_planka_sign)
            {
                line1.setPoints( P["Zu3"],P["vp_1"] );
                line2.setPoints( P["Zu4"],P["vp_2"] );
                line1.setLength( line1.length() - vorot_planka_sign_double );
                line2.setLength( line2.length() - vorot_planka_sign_double );
                P["vp_1sign"] = line1.p2();
                P["vp_2sign"] = line2.p2();
                vorot_planka_sign_angle = line1.angle();
            }
            colclasptype = -LD("clasp_t3_width")/2;
        }else
        {
            planka_adds = LD("clasp_t3_width");
            vorot_planka_b = false;
            colclasptype = LD("clasp_t3_width")/2;
        }
    }

////////диалоговое перестраивание линии горловины под застежку.
    ///////////////////////////////////////////////////////////НАЧАЛО
    //Дань битому движку
    if( LD("clasp_location") == 0 )
        temppath = temppath.toReversed();
    cpath["eGEnd"] = C2DPath( temppath );
    P["eGEnd"] = temppath.pointAtPercent(0);
    cpath["eGStart"] = C2DPath( temppath );
    P["eGStart"] = temppath.pointAtPercent(0);
    //clusrebuild = false;
    //bool clusrebuild=true;
    bool eGAll = false,eGStart=false;
    cpath["eGAll"] = C2DPath(temppath);
    P["eGAll"] = temppath.pointAtPercent(0);

    if( ( LD("is_clasp") == 1 ) && ( LD("clasp_form") != 0 ) )
    {
        eGAll = true;
        if( clusrebuild )
        {
            eGStart=true;
            eGAll =false;
            QLineF tmpline,tmpline2;
            QPainterPath newgore;
            double d2,d3;
            QPointF pend;
            line1.setPoints( P["cl_up"],P["cl_dwn"] );
            line2.setPoints( P["CluE"], P["CluE"] + QPointF(1,1) );
            QLineF line3 = QLineF( P["CluS"], P["CluS"] + QPointF(1,1) );
            line2.setAngle( line1.angle() );
            line3.setAngle( line1.angle() );
            //if(LD("clasp_location") == 0)
            //    temppath = temppath.toReversed();
            d2 = cGeometry::qpintrbtD( line2,temppath,0.5);
            d3 = cGeometry::qpintrbtD( line3,temppath,0.5);
            d2 = d2 + 15;
            if( d2>temppath.length() )
                d2=temppath.length()-1;
            pend = temppath.pointAtPercent( d2/temppath.length() );
            tmpline.setPoints( P["CluE"],pend );
            tmpline.setAngle( temppath.angleAtPercent( d3/temppath.length() ) );
            tmpline.setLength( tmpline.length() * 0.4 );
            tmpline2.setPoints( pend,P["CluE"] );
            tmpline2.setAngle( temppath.angleAtPercent(d2/temppath.length())+180 );
            tmpline2.setLength( tmpline2.length() * 0.4 );
            newgore.moveTo( P["CluE"] );
            newgore.cubicTo( tmpline.p2(),tmpline2.p2(),tmpline2.p1() );
            C2DPath gorlovend = C2DPath( temppath.toReversed() );
            newgore.connectPath( gorlovend.myshapefromstart( (temppath.length()-d2)/temppath.length() ).toReversed() );
            collar_clasp_gr = newgore.length();
            cpath["eGEnd"] = C2DPath( newgore );
            P["eGEnd"] = newgore.pointAtPercent(0);
            cpath["eGStart"] = C2DPath( temppath );
            cpath["eGStart"] = C2DPath( cpath["eGStart"].myshapefromstart( d3/temppath.length(),1 ) );
            P["eGStart"] = cpath["eGStart"].shape().pointAtPercent(0);
        }
    }


    if( ( LD("is_intersect_gorlovina")==0 ) || ( LD("is_clasp") == 0 ) || ( LD("clasp_form")==0 ) || ( LD("clasp_location")==2 ) )
        tempbool = false;

 ////Конец диалогового перестроения лини горловины
    bool intersects;
    intersects = tempbool;

    sign( Sync( attr( SYNC_NAME, QString( "vp_1sign" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "vp_1sign" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -vorot_planka_sign_angle-90 ) ),
          vorot_planka_sign && intersects );
    sign( Sync( attr( SYNC_NAME, QString( "vp_2sign" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "vp_2sign" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, -vorot_planka_sign_angle+90 ) ),
          vorot_planka_sign && intersects );

    line( Sync( attr( SYNC_NAME,  QString( "vp_1-vp_2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "vp_1", "vp_2" ) ),
                LM->bold_solid() ),
          vorot_planka_b && intersects );

    line( Sync( attr( SYNC_NAME, QString( "Zu1-vp_1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "vp_1", "Zu1" ) ),
                LM->bold_solid() ),
          vorot_planka_b && intersects );

    line( Sync( attr( SYNC_NAME, QString( "Zu2-vp_2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "vp_2", "Zu2" ) ),
                LM->bold_solid() ),
          vorot_planka_b && intersects );


    line( Sync( attr( SYNC_NAME,  QString( "hl1-" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Hang1", "Hang3" ) ),
                LM->bold_solid() ),
          hang && intersects );
    line( Sync( attr( SYNC_NAME,  QString( "hl2-" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Hang2", "Hang4" ) ),
                LM->bold_solid() ),
          hang && intersects );


    line( Sync( attr( SYNC_NAME,  QString( "Bu1-" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Bu1", "Bu2" ) ),
                LM->bold_solid() ),
          bu && intersects );
    int butnum=0;
    for(int i=0;i<30;i++ )
    {
        if( bu )
            butnum = LD("clasp_t0_btns_num");
        else if( hang || hang_no_loop )
            butnum = LD("clasp_t2_btns_num");
        else if( planka )
            butnum = LD("clasp_t3_btns_num");

        if( i < butnum )
            tempbool = true;
        else
            tempbool = false;

        button( Sync( attr( SYNC_NAME,  QString( "Bu-"+QString::number(i) ) ),
                      attr( SYNC_TYPE, C2DSync::Button ),
                      attr( SYNC_LIST, MakeList( "But"+QString::number(i) ) ),
                      LM->bold_solid() ),
                tempbool && intersects );
    }

    line( Sync( attr( SYNC_NAME,  QString( "Zu1-1" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Zu1", "Zu3" ) ),
                LM->bold_solid() ),
          (zu||planka)&& intersects );
    line( Sync( attr( SYNC_NAME,  QString( "Zu1-111" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Zu1", "Zu2" ) ),
                LM->bold_solid() ),
          (planka)&& intersects && !vorot_planka_b);
    line( Sync( attr( SYNC_NAME,  QString( "Zu1-1111" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Zu1", "Zu2" ) ),
                LM->thick_dashed() ),
          (planka)&& intersects && vorot_planka_b);
    line( Sync( attr( SYNC_NAME,  QString( "Zu2-2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Zu2", "Zu4" ) ),
                LM->bold_solid() ),
          (zu||planka)&& intersects );
    sign( Sync( attr( SYNC_NAME, QString( "Zs1s" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "ZuSign1s" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, Zus1 ) ),
          zu && intersects );
    sign( Sync( attr( SYNC_NAME, QString( "Zs1e" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "ZuSign1e" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, Zus1 ) ),
          zu && intersects );

    sign( Sync( attr( SYNC_NAME, QString( "Zs2s" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "ZuSign2s" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, Zus2 ) ),
          zu && intersects );
    sign( Sync( attr( SYNC_NAME, QString( "Zs2e" ) ),
                attr( SYNC_TYPE, C2DSync::Sign ),
                attr( SYNC_LIST, MakeList( "ZuSign2e" ) ),
                LM->bold_solid(),
                attr( SYNC_SIGN_DUAL, false ),
                attr( SYNC_SIGN_ANGLE, Zus2 ) ),
          zu && intersects );


    bool tmpbool2=false;
    if( ( zu == true ) || ( bu == true ) || ( hang == true ) || ( planka == true ) )
        tmpbool2 = false;
    else
        tmpbool2 = true;


    line( Sync( attr( SYNC_NAME,  QString( "Cu-Cd" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "cl_up", "cl_dwn" ) ),
                LM->thick_dashed() ),
          true && intersects && (!tmpbool2) );

    line( Sync( attr( SYNC_NAME,  QString( "Cu-Cd2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "cl_up", "cl_dwn" ) ),
                LM->bold_solid() ),
          true && intersects && tmpbool2 );
   ///ZASTEJKA : END ***/
//    C2DPath c2dpath( GorLeft, 0 , 0 );
//    C2DPath c2dpath1( temppath );
    //c2dpath.toReversed();
//    c2dpath1 = path_balance( c2dpath, c2dpath1,10 ).at(0);
//    temppath = c2dpath.myshapefromstart(  );

    bool mirropath_left=false,mirropath_right=false;
    if( (LD("is_cut")==1) )
        if( LD("cut_location") == 0 )
            mirropath_left=true;
        else if( LD("cut_location") == 1 )
            mirropath_right=true;
    if( (LD("is_clasp")==1) )
        if( LD("clasp_location") == 0 )
            mirropath_left=true;
        else if( LD("clasp_location") == 1 )
            mirropath_right=true;

    Gmirropath_right = mirropath_right;
    Gmirropath_left = mirropath_left;
    QPainterPath ms_ = cpath["m_spinka"].shape();
    ppath(  Sync( attr( SYNC_NAME,  QString( "ms_" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "11dialog" ) ),
                      LM->thick_dashed() ), &ms_, 0, 1,
                           (LB("g_p_nomirror")||mirropath_left) );
    QPainterPath mp_ = cpath["m_polka"].shape();
    ppath(  Sync( attr( SYNC_NAME,  QString( "mp_" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "172dialog" ) ),
                      LM->thick_dashed() ),  &mp_, 0, 1,
                           (LB("g_p_nomirror")||mirropath_right) );

    if( QLineF(P["cl_up"],P["cl_dwn"]).length() != 0 )
        this->collar->setlength( 1, QLineF(P["cl_up"],P["cl_dwn"]).length() );
    else
        this->collar->setlength( 1, QLineF(P["91"],P["11"]).length() );

    QPainterPath collar_minus_path, collar_plus_path,collar_left_minus_path,
            collar_left_plus_path,collar_right_minus_path,collar_right_plus_path;
    if( LD("clasp_location") == 0 )
    {
        collar_plus_path = cpath["g_left_e"].myshapefromstart();
        C2DPath tmppath = C2DPath( cpath["g_leftm_e"].myshapefromstart(),0,1 );
        collar_minus_path = tmppath.myshapefromstart().toReversed();
    }else if( LD("clasp_location") == 1 )
    {
        collar_minus_path = cpath["g_right_e"].myshapefromstart().toReversed();
        C2DPath tmppath = C2DPath( cpath["g_rightm_e"].myshapefromstart(),0,1 );
        collar_plus_path = tmppath.myshapefromstart();
    }


    collar_left_plus_path = cpath["g_left_e"].myshapefromstart();
    C2DPath tmppath = C2DPath( cpath["g_leftm_e"].myshapefromstart(),0,1 );
    collar_left_minus_path = tmppath.myshapefromstart().toReversed();
    collar_right_minus_path = cpath["g_right_e"].myshapefromstart().toReversed();
    tmppath = C2DPath( cpath["g_rightm_e"].myshapefromstart(),0,1 );
    collar_right_plus_path = tmppath.myshapefromstart();


    this->collar->addqpath( "g_minus", collar_minus_path );
    this->collar->addqpath( "g_plus", collar_plus_path );

    this->collar->addqpath( "g_l_minus", collar_left_minus_path );
    this->collar->addqpath( "g_l_plus", collar_left_plus_path );
    this->collar->addqpath( "g_r_minus", collar_right_minus_path  );
    this->collar->addqpath( "g_r_plus", collar_right_plus_path );


    this->collar->addqline( "g_line", QLineF(P["cl_up"],P["cl_dwn"]) );
    this->collar->setlength( 2, P["clasp_down_strt"].x() );
    this->collar->setlength( 3, P["clasp_down_strt"].y() );
    this->collar->setlength( 4, P["claspwidthlimit"].x() );
    this->collar->setlength( 5, P["claspwidthlimit"].y() );
    this->dress_gorlovina->setT31( LD("T31") );
    cpath["g_minus"] = C2DPath( collar_minus_path );
    cpath["g_plus"] = C2DPath( collar_plus_path );

    //this->NewGorlovinaClasp();
    QPainterPath leftendpath,rightendpath;
    double leftendp,rightendp;
    ///отрисовка застежки
    //Unicus::console("CLASPFORM", LD("clasp_form"));
    bool leftbold=false,rightbold=false;
    if( ( LD("is_clasp")==1 )&&( LD("clasp_location") == 0 )&&( LD("clasp_form") != 0 ) )
    {
        rightbold = true;
    }else if( ( LD("is_clasp")==1 )&&( LD("clasp_location") == 1 )&&( LD("clasp_form") != 0 ))
    {
        leftbold = true;
    }else
    {
        rightbold = true;
        leftbold = true;
    }

    QPainterPath leftgorlopath,rightgorlopath;
    rightgorlopath = cpath["g_right_e"].shape().toReversed();
    rightendp = rightgorlopath.length();
    if( (mirropath_right == true)||(LB("g_p_nomirror")) )
        rightgorlopath.connectPath( cpath["g_rightm_end"].myshapefromstart() );
    leftgorlopath = cpath["g_left_e"].shape().toReversed();
    leftendp = leftgorlopath.length();
    if( (mirropath_left == true)||(LB("g_p_nomirror")) )
        leftgorlopath.connectPath( cpath["g_leftm_end"].myshapefromstart() );
    P["rightgorlopath"] = rightgorlopath.pointAtPercent(0);
    P["leftgorlopath"] = leftgorlopath.pointAtPercent(0);
    //if(leftbold)
    {
        leftendpath = leftgorlopath;
    }
    //if(rightbold)
        rightendpath = rightgorlopath;

    //P[""]
    ppath(  Sync( attr( SYNC_NAME,  QString( "c_L_sleftgorlopath" ) ),
                                          attr( SYNC_TYPE, C2DSync::Ppath ),
                                          attr( SYNC_LIST, MakeList( "leftgorlopath" ) ),
                                          LM->bold_solid() ), &leftendpath, 0, 0,
                                  leftbold );
    //Unicus::console("leftbold", leftbold);
    //Unicus::console("rightbold", rightbold);
    //ppath(  Sync( attr( SYNC_NAME,  QString( "leftgorlopath" ) ),
    //                            attr( SYNC_TYPE, C2DSync::Ppath ),
    //                            attr( SYNC_LIST, MakeList( "leftgorlopath" ) ),
    //                       LM->bold_solid() ),  &leftgorlopath, 0, 0,
    //                           leftbold  );
    ppath(  Sync( attr( SYNC_NAME,  QString( "rightgorlopath" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "rightgorlopath" ) ),
                           LM->bold_solid() ),  &rightgorlopath, 0, 0,
                               rightbold  );

    QPainterPath pathmy3;
    pathmy3 = cpath["eGAll"].shape();
    ppath(  Sync( attr( SYNC_NAME,  QString( "eGAll" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "eGAll" ) ),
                           LM->thick_solid() ),  &pathmy3, 0, 0,
                               eGAll||bu||hang  );
    //QPainterPath pathmy2111;
    //pathmy2111 = cpath["eGStart"].shape();
    //ppath(  Sync( attr( SYNC_NAME,  QString( "eGStart111" ) ),
    //                            attr( SYNC_TYPE, C2DSync::Ppath ),
    if( LD("clasp_location") == 0 )
        gorloboldleft = temppath.length() - gorloboldleft;
    if( ( gorloboldleft < 0 ) || ( gorloboldleft > temppath.length() ) )
        gorloboldleft = temppath.length();

    //Unicus::console( "gorloboldleft", gorloboldleft );
    //Unicus::console( "temppath.length()", temppath.length() );
    //Unicus::console( "gorloboldlefte", gorloboldlefte );
    QPainterPath pathmy2111;
    C2DPath p2dpath = C2DPath( temppath );

    if((gorloboldlefte)&&( LD("is_clasp")!=0 ))
        pathmy2111 = p2dpath.myshapefromstart( gorloboldleft/temppath.length() );
    else
        pathmy2111 = QPainterPath();
    P["pathmy2111"] = pathmy2111.pointAtPercent(0);
    ppath(  Sync( attr( SYNC_NAME,  QString( "pathmy2111" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "pathmy2111" ) ),
                           LM->bold_solid() ),  &pathmy2111, 0, 0,
                               true );

    if(gorloboldlefte)
    {
        clasp_sign3_path = pathmy2111;
        clasp_sign3_start = 0;
    }
    //                             attr( SYNC_LIST, MakeList( "eGStart" ) ),
    //                      LM->bold_solid() ), &pathmy2111, 0, 0,
    //                           eGStart );

    bool plecho_shov = false;
    if( (LD("clasp_location") == 2 ) )
        plecho_shov = true;
    QPainterPath pathmy1;
    if((eGStart)&&(!bu)&&(!hang)&&(!plecho_shov))
        pathmy1 = cpath["eGEnd"].shape();
    else
        pathmy1 = QPainterPath();

    ppath(  Sync( attr( SYNC_NAME,  QString( "eGEnd" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "eGEnd" ) ),
                          LM->bold_solid() ), &pathmy1, 0, 0,
                               true  );
    if((eGStart)&&(!bu)&&(!hang))
    {
        clasp_sign4_path = pathmy1;
        clasp_sign4_start = 0;
    }
    //если планка
    if( LD("clasp_form") == 2 )
        if(LD("clasp_t3_width") != 0) // шириназаноса планки не равна 0
        {
            QPainterPath tmppath1 ,tmppath2;
            tmppath1 = clasp_sign3_path;
            tmppath1.lineTo(clasp_sign4_path.pointAtPercent(0));
            tmppath2 = clasp_sign4_path.toReversed();
            tmppath2.lineTo(clasp_sign3_path.pointAtPercent(1));

            clasp_sign3_path = tmppath1;
            clasp_sign4_path = tmppath2.toReversed();
        }
    //Unicus::console( "BLUEGIRL", bluegirl );


    line( Sync( attr( SYNC_NAME,  QString( "Bu1-cl_up" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Bu1", "cl_up" ) ),
                LM->bold_solid() ),
          bu && eGStart );

    line( Sync( attr( SYNC_NAME,  QString( "Hang1-Hang2" ) ),
                attr( SYNC_TYPE, C2DSync::Line ),
                attr( SYNC_LIST, MakeList( "Hang1", "Hang2" ) ),
                LM->bold_solid() ),
          hang && eGStart );
    //////дублирование линии горловины
    //end125 = QLineF( P["Gl"],P["125end"] ).angle();
    //end26 = QLineF( P["Gr"],P["26end"] ).angle();

    cpath["GchangeR"] = C2DPath(cpath["g_right_e"].shape().toReversed());
    cpath["GchangeRm"] = C2DPath(cpath["g_rightm_end"].myshapefromstart().toReversed(),0,1);
    //cpath["Gchange"] = C2DPath(GorLeft.toReversed(),180);
    cpath["Gchange"] = C2DPath( cpath["g_left_e"].shape().toReversed(),-(gangleP-gangleS));
    cpath["Gchangem"] = C2DPath(cpath["g_leftm_end"].shape().toReversed(),-(gangleSm-ganglePm),1);
    Unicus::console( "cpath[g_left_e]",cpath["g_left_end"].shape().length() );
    Unicus::console( "cpath[g_leftm_e]",cpath["g_leftm_e"].shape().length() );
    bool doublineofgorlo = false;
    if( LD("Gchange") == 2 )
        doublineofgorlo = true;
    QPainterPath Gchange = cpath["Gchange"].myshapefromstart();
    QPainterPath Gchangem = cpath["GchangeRm"].myshapefromstart().toReversed();
    //Gchangem.connectPath( cpath["Gchangem"].myshape( Gchangem.pointAtPercent(1) ) );
    Gchangem = cpath["Gchangem"].myshape( cpath["GchangeRm"].myshapefromstart().toReversed().pointAtPercent(1) ) ;
    P["Gchange"] = cpath["GchangeR"].shape().pointAtPercent(0);
    P["Gchangem"] = cpath["GchangeRm"].myshapefromstart().pointAtPercent(0);
    P["GchangeEND"] = cpath["GchangeR"].shape().pointAtPercent(1);
    ppath(  Sync( attr( SYNC_NAME,  QString( "Gchange" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "Gchange" ) ),
                          LM->thick_solid() ), &Gchange, 0, 0,
                               doublineofgorlo );

    if( D("is_mirror") == 0 )
        tempbool = true;
    else
        tempbool = false;
    ppath(  Sync( attr( SYNC_NAME,  QString( "Gchangem" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "Gchangem" ) ),
                          LM->thick_solid() ), &Gchangem, 0, 0,
                                doublineofgorlo && tempbool );


    //Unicus::console("AngleS", gangleS);
    //Unicus::console("AngleP", gangleP);
    //Unicus::console("AngleSm", gangleSm);
    //Unicus::console("AnglePm", ganglePm);
    //Unicus::console("Gchange", Gchange.length());
    //Unicus::console("Gchangem", Gchangem.length());
    //Unicus::console("PointX", P["Gchange"].x() );
    //Unicus::console("PointY", P["Gchange"].y() );
    //Unicus::console("PointXm", P["Gchangem"].x() );
    //Unicus::console("PointYm", P["Gchangem"].y() );
    //Unicus::console("PointXend", cpath["Gchange"].myshape( P["Gchange"] ).pointAtPercent(1).x() );
    //Unicus::console("PointYend", cpath["Gchange"].myshape( P["Gchange"] ).pointAtPercent(1).y() );
    //Unicus::console("PointXendM", Gchangem.pointAtPercent(1).x() );
    //Unicus::console("PointYendM", Gchangem.pointAtPercent(1).y() );

    //Unicus::console("SpinkastrtX", cpath["g_left_e"].myshapefromstart().pointAtPercent(0).x() );
    //Unicus::console("SpinkastrtY", cpath["g_left_e"].myshapefromstart().pointAtPercent(0).y() );
    //Unicus::console("SpinkastrtXm", cpath["g_leftm_end"].myshapefromstart().pointAtPercent(0).x() );
    //Unicus::console("SpinkastrtYm", cpath["g_leftm_end"].myshapefromstart().pointAtPercent(0).y() );

    //Unicus::console("PstrtX", cpath["g_right_e"].myshapefromstart().pointAtPercent(0).x() );
    //Unicus::console("PstrtY", cpath["g_right_e"].myshapefromstart().pointAtPercent(0).y() );
    //Unicus::console("PstrtXm", cpath["g_rightm_e"].myshapefromstart().pointAtPercent(0).x() );
    //Unicus::console("PstrtYm", cpath["g_rightm_e"].myshapefromstart().pointAtPercent(0).y() );

    if(planka_adds != 0)
    {
        collar_clasp_gl = collar_clasp_gl + planka_adds;
        collar_clasp_gr = collar_clasp_gr + planka_adds;
    }

    if( (LD("is_clasp")==1) && (LD("clasp_form")!=0) )
        if(collar_leftright)
        {

            if(LD("clasp_location") == 0)
            {
                zipper = 0;
                colclasptype = 0;
                gorl = collar_clasp_gr;
                gorlm = collar_clasp_gl;
                //Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!3gorr",gorr );
                //Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!3",gorrm );
            }else if(LD("clasp_location") == 1)
            {
                zipper = 0;
                colclasptype = 0;
                gorrm = collar_clasp_gr;
                gorr = collar_clasp_gl;
                //Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!3gorr",gorr );
                //Unicus::console( "!!!!!!!!!!!!!!!!!!!!!!!!3",gorrm );
            }
        }

    //////DEBUG
    point( Sync( attr( SYNC_NAME,  QString( "d-33" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "33" ) ),
                 LM->thick_blue() ),
           true );

    point( Sync( attr( SYNC_NAME,  QString( "d-351" ) ),
                 attr( SYNC_TYPE, C2DSync::Point ),
                 attr( SYNC_LIST, MakeList( "351" ) ),
                 LM->thick_blue() ),
           true );
}

QList < QPainterPath > C2DDress::splitPath( QPainterPath path, double balance, double shag )
{
    QList < QPainterPath > patharr;
    if(shag==0)
        return patharr;
    double templength = shag;
    QPainterPath patharr0,patharr1;
    QPointF bpoint = path.pointAtPercent( balance/path.length() );

    patharr0.moveTo( path.pointAtPercent(0) );

    while( templength < balance )
    {
        patharr0.lineTo( path.pointAtPercent( templength/path.length() ) );
        templength = templength + shag;
    }
    patharr0.lineTo( bpoint );
    templength = balance + shag;
    patharr1.moveTo( bpoint );
    while( templength < path.length() )
    {
        patharr1.lineTo( path.pointAtPercent( templength/path.length() ) );
        templength = templength + shag;
    }
    patharr1.lineTo( path.pointAtPercent(1) );
    patharr.append(patharr0);
    patharr.append(patharr1);
    return patharr;
}
QPainterPath C2DDress:: g_splinemaker( QPointF p1, QPointF p2, double angle1, double angle2,
                            double length1, double length2 )
{
    QPainterPath path;
    QLineF line1,line2;
    if( length2 == 0 )
        length2 = length1;

    line1.setPoints( p1, p1 + QPointF(1,1) );
    line1.setAngle( angle1 );
    line1.setLength( length1 );
    line2.setPoints( p2, p2 + QPointF(1,1) );
    line2.setAngle( angle2 );
    line2.setLength( length2 );

    path.moveTo( p1 );
    path.cubicTo( line1.p2(), line2.p2(), p2 );

    return path;
}
QPainterPath C2DDress::make_dialog_gorlovina( QPainterPath * path, QString const str )
{
    QLineF line1, line2;
    double templangth, angle_p[3], tempangle;
    //Горловина несколько точек старт
    QPainterPath gor_polka_points;
    QString part;
    if( str == "polochka" )
    {
        part = "p";
    }else if( str == "spinka" )
    {
        part = "s";
    }
    else if( str == "polochka_m" )
    {
        part = "pm";
    }else if( str == "spinka_m" )
    {
        part = "sm";
    }

    if ( LD("g_"+part+"_point_count") > 0 )
    {

        for( int i=0;i<LD("g_"+part+"_point_count");i++ )
        {
            templangth = ( 1 / (LD("g_"+part+"_point_count") + 1) ) * ( i + 1 );
            angle_p[i] = path->angleAtPercent( templangth );
            P["g_"+part+QString::number(i)] = path->pointAtPercent( templangth );
            line1.setPoints( P["g_"+part+QString::number(i)], P["g_"+part+QString::number(i)] + QPointF( 1, 1 ) );
            line1.setAngle( angle_p[i] );
            if( LD("g_"+part+"_p"+QString::number(i+1)+"_left") != 0 )
            {
                line1.setLength( LD("g_"+part+"_p"+QString::number(i+1)+"_left") );
                P["g_"+part+QString::number(i)] = line1.p2();
            }
            if( LD("g_"+part+"_p"+QString::number(i+1)+"_top") != 0 )
            {
                line2.setPoints( P["g_"+part+QString::number(i)], P["g_"+part+QString::number(i)] + QPointF( 1, 1 ) );
                line2.setAngle( angle_p[i]+90 );
                line2.setLength( LD("g_"+part+"_p"+QString::number(i+1)+"_top") );
                P["g_"+part+QString::number(i)] = line2.p2();
            }
        }

        line1.setPoints( path->pointAtPercent(0),P["g_"+part+"0"] );
        templangth = line1.length();

        if( LD("g_"+part+"_double_angle") == 1 )
            tempangle = angle_p[0] + LD( "g_"+part+"_p1_angle2" ) + 180;
        else
            tempangle = angle_p[0] + LD( "g_"+part+"_p1_angle1" ) + 180;

        gor_polka_points = g_splinemaker( path->pointAtPercent(0), P["g_"+part+"0"], LD("g_"+part+"_alpha"),
                                          tempangle, templangth/3 );
        cpath["g_"+part+"_1"] = C2DPath(gor_polka_points);
        tempangle = LD("g_"+part+"_p1_angle1") + angle_p[0];
        if( LD("g_"+part+"_point_count") > 1 )
        {
            line1.setPoints( P["g_"+part+"0"],P["g_"+part+"1"] );
            templangth = line1.length();

            if( LD("g_"+part+"_double_angle1") == 1 )
                tempangle = angle_p[1] + LD( "g_"+part+"_p2_angle2" ) + 180;
            else
                tempangle = angle_p[1] + LD( "g_"+part+"_p2_angle1" ) + 180;
            cpath["g_"+part+"_2"] = C2DPath(g_splinemaker( P["g_"+part+"0"], P["g_"+part+"1"], LD("g_"+part+"_p1_angle1") + angle_p[0] ,
                                                           tempangle, templangth/3 ));
            gor_polka_points.connectPath( cpath["g_"+part+"_2"].shape() );
            tempangle = LD("g_"+part+"_p2_angle1") + angle_p[1];
        }
        line1.setPoints( gor_polka_points.pointAtPercent(1),path->pointAtPercent(1) );
        templangth = line1.length();
        cpath["g_"+part+"_3"] = C2DPath( g_splinemaker( gor_polka_points.pointAtPercent(1),
                                                        path->pointAtPercent(1),
                                                        tempangle, path->angleAtPercent(1) + 180 + LD("g_"+part+"_beta"),
                                                        templangth/3 ) );
        gor_polka_points.connectPath( cpath["g_"+part+"_3"].shape() );
        return gor_polka_points;
    }else
    {
        //if( ( (LI("g_"+part+"_beta")%360) != 0 ) || ( (LI("g_"+part+"_alpha")%360) != 0 ) )
        {
            line1.setPoints( path->pointAtPercent(0),path->pointAtPercent(1) );
            templangth = line1.length();
            //gor_polka_points = g_splinemaker( path->pointAtPercent(0), path->pointAtPercent(1),path->angleAtPercent(0) + LD("g_"+part+"_alpha"),
            //                                  path->angleAtPercent(1) + 180 + LD("g_"+part+"_beta"), templangth*0.4 );
            Unicus::console( "slengthLR_Y",P["g_"+part+"_slengthLR"].y() );
            Unicus::console( "slengthLR_X",P["g_"+part+"_slengthLR"].x() );
            line1.setPoints( path->pointAtPercent(0),path->pointAtPercent(0)+QPointF(1,1) );
            line1.setAngle( path->angleAtPercent(0) + LD("g_"+part+"_alpha") );
            line1.setLength( P["g_"+part+"_slengthLR"].y() );
            line2.setPoints( path->pointAtPercent(1),path->pointAtPercent(1)+QPointF(1,1) );
            line2.setAngle( path->angleAtPercent(1) + 180 + LD("g_"+part+"_beta") );
            line2.setLength( P["g_"+part+"_slengthLR"].x() );
            gor_polka_points.moveTo( path->pointAtPercent(0) );
            gor_polka_points.cubicTo( line1.p2(),line2.p2(),line2.p1() );
            cpath["g_"+part+"_1"] = C2DPath( gor_polka_points );
            return gor_polka_points;
        }//else
        //{
        //    cpath["g_"+part+"_1"] = C2DPath( *path );
        //    return *path;
        //}
    }
}
QList< C2DPath > C2DDress::path_balance( C2DPath cp1, C2DPath cp2,
                               double balance, double shag, double a1, double a2 )
{
    QList < C2DPath > result;
    Unicus::console("hhhh",balance);
    C2DPath tmpc2dpath;
    QPainterPath tmppath;
    if( balance > 0 )
    {
        tmpc2dpath = cp2;
        tmpc2dpath.toReversed();
        //tmpc2dpath.setAngle( tmpc2dpath.shape().angleAtPercent(0) - cp1.shape().angleAtPercent(1) );
        tmpc2dpath.setAngle( a2 - a1 );
        tmppath = cp1.myshapefromstart(1,0.5);
        tmppath.connectPath( tmpc2dpath.myshape( tmppath.pointAtPercent(1), balance / tmpc2dpath.length() ) );
        cp1 = C2DPath(tmppath);
        cp2 = C2DPath(cp2.myshapefromstart( (cp2.length()-balance)/cp2.length(),0.5 ) );
    }else if( balance < 0 )
    {
        tmpc2dpath = cp1;
        tmpc2dpath.toReversed();
        //tmpc2dpath.setAngle( tmpc2dpath.shape().angleAtPercent(0) - cp2.shape().angleAtPercent(1) );
        tmpc2dpath.setAngle( a1 - a2 );
        tmppath = cp2.myshapefromstart(1,0.5);
        tmppath.connectPath( tmpc2dpath.myshape( tmppath.pointAtPercent(1), -balance / tmpc2dpath.length(),0.5 ) );
        cp2 = C2DPath(tmppath);
        cp1 = C2DPath(cp1.myshapefromstart( (cp1.length()+balance)/cp1.length(),0.5 ) );
    }
    result.append(cp1);
    result.append(cp2);
    return result;
}

void C2DDress::NewGorlovina()
{
    QList < C2DPath > result;
    QPainterPath temppath;

    result = path_balance( cpath["GorLeftm"], cpath["GorRightm"], LD("GorlovinaBalance_m"),0.1,gangleSm,ganglePm );
    cpath["g_leftm_e"] = result.at(0);
    cpath["g_rightm_e"] = result.at(1);

   // QPointF pl = cpath["g_leftm_e"].shape().pointAtPercent( 1 );
  //  QPointF pr = cpath["g_rightm_e"].shape().pointAtPercent( 1 );
   // line1.setPoints(P["16"],P["161"]);
 /*   temppath = cpath["g_left_e"].shape();
    ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_!!!!!!!!345" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "31'" ) ),
                            LM->bold_solid() ), &temppath, 0, 0,
                            true );
    temppath = cpath["g_right_e"].shape();
    ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_!!!!!!!!2345" ) ),
                            attr( SYNC_TYPE, C2DSync::Ppath ),
                            attr( SYNC_LIST, MakeList( "31'" ) ),
                            LM->bold_solid() ), &temppath, 0, 0,
                            true );*/
}
void C2DDress::NewProima()
{
    C2DPath tmpc2dpath = cpath["old_proima"];
    QPainterPath temppath;
    if( LD("ProimaBalance_m") == 0 )
        cpath["mirror_proima"] = cpath["old_proima"];
    else if( LD("ProimaBalance_m") > 0 )
    {
        tmpc2dpath.toReversed();
        tmpc2dpath.setAngle( tmpc2dpath.shape().angleAtPercent(0) - tmpc2dpath.shape().angleAtPercent(1) );
        temppath = tmpc2dpath.myshape( cpath["old_proima"].shape().pointAtPercent(0),LD("ProimaBalance_m") / tmpc2dpath.length() );
        temppath = temppath.toReversed();
        P["14-1mirror"] = temppath.pointAtPercent(0);
        temppath.connectPath( cpath["old_proima"].myshapefromstart( (cpath["old_proima"].length() - temppath.length())/cpath["old_proima"].length() ) );
        cpath["mirror_proima"] = C2DPath(temppath);
    }else if( LD("ProimaBalance_m") < 0 )
    {
        tmpc2dpath.setAngle( tmpc2dpath.shape().angleAtPercent(0) - tmpc2dpath.shape().angleAtPercent(1) );
        temppath = tmpc2dpath.myshape( cpath["old_proima"].shape().pointAtPercent(1),-LD("ProimaBalance_m") / tmpc2dpath.length() );
        temppath = temppath.toReversed();

        cpath["old_proima"].toReversed();
        temppath.connectPath( cpath["old_proima"].myshapefromstart( (cpath["old_proima"].length() - temppath.length())/cpath["old_proima"].length() ) );
        temppath = temppath.toReversed();
        P["14-1mirror"] = temppath.pointAtPercent(0);
        cpath["mirror_proima"] = C2DPath(temppath);
    }

    //QPainterPath temppath = tmpc2dpath.myshapefromstart(  );
    //ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_!!!!!!!!" ) ),
    //                        attr( SYNC_TYPE, C2DSync::Ppath ),
    //                        attr( SYNC_LIST, MakeList( "14-1mirror" ) ),
    //                        LM->bold_solid() ), &temppath, 0, 0,
    //                        true );
}
QPainterPath C2DDress::findC2Dpathpart( QPointF p )
{
    QPainterPath result;
    QLineF l[10];
    int k = 1;
    if( LD("clasp_location") == 0 )
    {
        if( LD("g_s_point_count") == 0 )
            l[k++] = Zeroguidelineofpath( cpath["g_s_1"].shape() );
        else if( LD("g_s_point_count") == 1 )
        {
            l[k++] = Zeroguidelineofpath( cpath["g_s_1"].shape() );
            l[k++] = Zeroguidelineofpath( cpath["g_s_3"].shape() );
        }else if( LD("g_s_point_count") == 2 )
        {
            l[k++] = Zeroguidelineofpath( cpath["g_s_1"].shape() );
            l[k++] = Zeroguidelineofpath( cpath["g_s_2"].shape() );
            l[k++] = Zeroguidelineofpath( cpath["g_s_3"].shape() );
        }
        if( LD("g_sm_point_count") == 0 )
            l[k++] = Zeroguidelineofpath( cpath["g_sm_1"].shape().toReversed() );
        else if( LD("g_sm_point_count") == 1 )
        {
            l[k++] = Zeroguidelineofpath( cpath["g_sm_1"].shape().toReversed() );
            l[k++] = Zeroguidelineofpath( cpath["g_sm_3"].shape().toReversed() );
        }else if( LD("g_sm_point_count") == 2 )
        {
            l[k++] = Zeroguidelineofpath( cpath["g_s_1"].shape() );
            l[k++] = Zeroguidelineofpath( cpath["g_s_2"].shape() );
            l[k++] = Zeroguidelineofpath( cpath["g_s_3"].shape() );
        }

    }
}
QLineF C2DDress::Zeroguidelineofpath( QPainterPath p )
{
    QLineF result;
    result = QLineF( p.pointAtPercent(0), p.pointAtPercent(0) + QPointF(1,1));
    result.setAngle( p.angleAtPercent(0) );
    return result;
}
QPointF C2DDress::claspwidthlimit( QPainterPath path, QLineF line )
{
    if( path.isEmpty() )
        return  QPointF(0,0);
    double xleft=99999,xright=-99999,l=0,shag = 1;
    QPointF p,pleft,pright;
    QLineF line1;
    do
    {
        p = path.pointAtPercent( l/path.length() );
        if( xleft > p.x() )
        {
            xleft = p.x();
            pleft = p;
        }
        if( xright < p.x() )
        {
            xright = p.x();
            pright = p;
        }
        l = l + shag;
    }
    while( l < path.length() );

    line1.setPoints( pleft,pleft+QPointF(1,1) );
    line1.setAngle( line.angle() + 90 );
    line1.intersect( line1,&p );
    line1.setPoints( pleft,p );
    xleft = line1.length();
////////////////////////
    line1.setPoints( pright,pright+QPointF(1,1) );
    line1.setAngle( line.angle() + 90 );
    line1.intersect( line1,&p );
    line1.setPoints( pright,p );
    xright = line1.length();

    return QPointF( xleft, xright );
}
void C2DDress::NewGorlovinaBalance()
{
    QPainterPath path;
    QPointF PL,PLM,PR,PRM, STARTPoint;
    QLineF line3;
    QLineF line1,line2;
    double tempangle;
    line1.setPoints(P["36"],P["26"]);
    line2.setPoints(P["36"],P["26-1"]);
    tempangle = line1.angleTo( line2 );
    PR = Unicus::rPoint( P["pr"], P["36"], tempangle );
    line1.setPoints(P["22"],P["125"]);
    line2.setPoints(P["22"],P["125-1"]);
    tempangle = line1.angleTo( line2 );
    PL = Unicus::rPoint( P["pl"], P["22"], tempangle );

    tempangle = QLineF(P["36"],P["161-1"]).angleTo( QLineF(P["36"],P["161"]) );
    PRM = Unicus::rPoint( P["m14-2"],P["m36"], -tempangle );
    tempangle = QLineF(P["22"],P["125"]).angleTo( QLineF(P["22"],P["125-1"]) );
    PLM = Unicus::rPoint( P["m14-1"],P["m22"], tempangle );

    double tmpdouble;

    if(LD("GorlovinaBalance")>0)
    {
        tmpdouble = cpath["GorRight"].shape().length() - LD("GorlovinaBalance");
        line1.setPoints( PR, cpath["GorRight"].shape().pointAtPercent( tmpdouble/cpath["GorRight"].shape().length() ) );

        path = cpath["GorLeft"].shape().toReversed();
        line2.setPoints( PL , path.pointAtPercent(0) );
        line3.setPoints( PR , cpath["GorRight"].shape().pointAtPercent(1) );
        path = C2DPath( path, line2.angle() - line3.angle() ).myshape( cpath["GorRight"].shape().pointAtPercent(1) );
        path = path.toReversed();
        path.connectPath(cpath["GorRight"].shape().toReversed());


        tempangle = cGeometry::qpathintersectmaxlength(line1,path,true);
        if( tempangle != -1 )
        {
            tempangle = tempangle - cpath["GorLeft"].shape().length();
            if( ( tempangle ) < LD("GorlovinaBalance") )
            {
                H("GorlovinaBalance") = tempangle;
                dress_gorlovina->setSpinValue( "dsp1", tempangle/10 );
            }
        }
    }else if(LD("GorlovinaBalance")<0)
    {
        tmpdouble = cpath["GorLeft"].shape().length() + LD("GorlovinaBalance");
        line1.setPoints( PL, cpath["GorLeft"].shape().pointAtPercent( tmpdouble/cpath["GorLeft"].shape().length() ) );

        path = cpath["GorRight"].shape().toReversed();
        line2.setPoints( PR , path.pointAtPercent(0) );
        line3.setPoints( PL , cpath["GorLeft"].shape().pointAtPercent(1) );
        path = C2DPath( path, line2.angle() - line3.angle() ).myshape( cpath["GorLeft"].shape().pointAtPercent(1) );
        path = path.toReversed();
        path.connectPath(cpath["GorLeft"].shape().toReversed());

        tempangle = cGeometry::qpathintersectmaxlength(line1,path,false);
        if( tempangle != -1 )
        {
            tempangle = tempangle - cpath["GorRight"].shape().length();

            if( (tempangle ) < -LD("GorlovinaBalance") )
            {
                H("GorlovinaBalance") = -tempangle;
                dress_gorlovina->setSpinValue( "dsp1", -tempangle/10 );
            }
        }
    }
//Unicus::console( "LD(GorlovinaBalance_mmm)",LD("GorlovinaBalance_m") );
    if(LD("GorlovinaBalance_m")>0)
    {
        tmpdouble = cpath["GorRightm"].shape().length() - LD("GorlovinaBalance_m");
        line1.setPoints( PRM, cpath["GorRightm"].shape().pointAtPercent( tmpdouble/cpath["GorRightm"].shape().length() ) );

        path = cpath["GorLeftm"].shape().toReversed();
        line2.setPoints( PLM , path.pointAtPercent(0) );
        line3.setPoints( PRM , cpath["GorRightm"].shape().pointAtPercent(1) );
        path = C2DPath( path, line2.angle() - line3.angle() ).myshape( cpath["GorRightm"].shape().pointAtPercent(1) );
        path = path.toReversed();
        path.connectPath(cpath["GorRightm"].shape().toReversed());

        tempangle = cGeometry::qpathintersectmaxlength(line1,path,true);
        Unicus::console( "LD(tempangle)1",tempangle );
        if( tempangle != -1 )
        {
            tempangle = tempangle - cpath["GorLeftm"].shape().length();
            Unicus::console( "LD(tempangle)2",tempangle );
            if( (tempangle ) < LD("GorlovinaBalance_m") )
            {
                H("GorlovinaBalance_m") = tempangle;
                dress_gorlovina->setSpinValue( "dsp1m", tempangle/10 );
            }

        }
    }else if(LD("GorlovinaBalance_m")<0)
    {
        tmpdouble = cpath["GorLeftm"].shape().length() + LD("GorlovinaBalance_m");
        line1.setPoints( PLM, cpath["GorLeftm"].shape().pointAtPercent( tmpdouble/cpath["GorLeftm"].shape().length() ) );

        path = cpath["GorRightm"].shape().toReversed();
        line2.setPoints( PRM , path.pointAtPercent(0) );
        line3.setPoints( PLM , cpath["GorLeftm"].shape().pointAtPercent(1) );
        path = C2DPath( path, line2.angle() - line3.angle() ).myshape( cpath["GorLeftm"].shape().pointAtPercent(1) );
        path = path.toReversed();
        path.connectPath(cpath["GorLeftm"].shape().toReversed());


        tempangle = cGeometry::qpathintersectmaxlength(line1,path,false);
        if( tempangle != -1 )
        {
            tempangle = tempangle - cpath["GorRightm"].shape().length();
            if( (tempangle ) < -LD("GorlovinaBalance_m") )
            {
                H("GorlovinaBalance_m") = -tempangle;
                dress_gorlovina->setSpinValue( "dsp1m", -tempangle/10 );
            }
        }
        P["000"] = QPointF(-100,0);
        ppath(  Sync( attr( SYNC_NAME,  QString( "Cu_!!!!!!!!23451" ) ),
                                attr( SYNC_TYPE, C2DSync::Ppath ),
                                attr( SYNC_LIST, MakeList( "000" ) ),
                                LM->bold_solid() ), &path, 0, 0,
                                true );
    }
    //Unicus::console( "LD(GorlovinaBalance_m)",LD("GorlovinaBalance_m") );
    //Unicus::console( "tempangle",tempangle );

    //pathleft pathrigth balance

}
