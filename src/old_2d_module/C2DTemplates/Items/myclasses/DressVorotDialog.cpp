#include "DressVorotDialog.h"
void DressVorotDialog::v_r_add( QString name, int cond )
{
    this->commonValue(name+"L:Default") = 0;

    dspinbox[name+"L"] = this->AddDoubleSpinBoxProperty(trUtf8("Величина разведения, см"),name+"L",0.5f,-20.0f,20.0f);
    dspinbox[name+"L"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["v_r_s"],cond ),Elasticas::OperationAnd);
}
DressVorotDialog::DressVorotDialog():Elasticas::PropertiesDialog(trUtf8("Воротник-стойка"),"Dress:")
{
//default
    this->commonValue("H1:Default")=4.0f;
    this->commonValue("H2:Default")=4.0f;
    this->commonValue("H3:Default")=4.0f;
    this->commonValue("Pos1:Default")=0;
    this->commonValue("Pos2:Default")=0;
    this->commonValue("H1lev:Default")=4.0f;
    this->commonValue("H2lev:Default")=4.0f;
    this->commonValue("H3lev:Default")=4.0f;
    this->commonValue("Pos1lev:Default")=0;
    this->commonValue("Pos2lev:Default")=0;
    this->commonValue("A:Default")=3.0f;
    this->commonValue("AL:Default")=3.0f;
    this->commonValue("OYspa:Default")=0.0f;
    this->commonValue("OYsha:Default")=0.0f;
    this->commonValue("OYpoa:Default")=0.0f;
//Скрытые формы для уже заданных в других диалогах параметров
    QString items0[]={trUtf8("polka"),trUtf8("spinka"),trUtf8("plecho"),NULL};
    combobox["claspl"] =this->AddComboBoxProperty(trUtf8("claspl"),items0,"z3");
    combobox["claspl"]->GetWidget()->setVisible(false);
    //combobox["claspt"] =this->AddComboBoxProperty(trUtf8("claspt"),items0,"z6");
    //combobox["claspt"]->GetWidget()->setVisible(false);

    QString items00[]={trUtf8("0"),trUtf8("1"),NULL};
    combobox["VB"] =this->AddComboBoxProperty(trUtf8("bokovye"),items00,"VB");
    combobox["VZ"] =this->AddComboBoxProperty(trUtf8("zadnyye"),items00,"VZ");
    combobox["VP"] =this->AddComboBoxProperty(trUtf8("peredny"),items00,"VP");
    combobox["VB"]->GetWidget()->setVisible(false);
    combobox["VP"]->GetWidget()->setVisible(false);
    combobox["VZ"]->GetWidget()->setVisible(false);



    combobox["clasp"] =this->AddComboBoxProperty(trUtf8("clasp"),items00,"z1");
    combobox["clasp"]->GetWidget()->setVisible(false);

    combobox["cut"] =this->AddComboBoxProperty(trUtf8("cut"),items00,"z7");
    combobox["cut"]->GetWidget()->setVisible(false);
    QString items000[]={trUtf8("0"),trUtf8("1"),trUtf8("2"),trUtf8("3"),trUtf8("4"),NULL};
    combobox["cutl"] =this->AddComboBoxProperty(trUtf8("cutl"),items000,"z8");
    combobox["cutl"]->GetWidget()->setVisible(false);

    combobox["is_mirror"] =this->AddComboBoxProperty(trUtf8("is_mirror"),items00,"is_mirror");
    combobox["is_mirror"]->GetWidget()->setVisible(false);

//    checkbox["is_mirror"] = this->AddCheckBoxProperty( trUtf8( "Симметричная горловина:" ),"is_mirror",true );

//формы
    checkbox["is_vorot"] = this->AddCheckBoxProperty( trUtf8( "Воротник-стойка:" ),"is_vorot",false );
    QString items1[]={trUtf8("Цельнокроеный со станом"),trUtf8("Самостоятельный элемент"),NULL};
    this->commonValue("vorot_type:Default")=1;
    combobox["vorot_type"] =this->AddComboBoxProperty(trUtf8("Воротник:"),items1,"vorot_type");
    QString items2[]={trUtf8("Мягкой"),trUtf8("Жесткой"),NULL};
    this->commonValue("vorot_form:Default")=1;
    combobox["vorot_form"] =this->AddComboBoxProperty(trUtf8("Формы:"),items2,"vorot_form");
//--------------------------------------------//
    //QLabel* label;
    //this->properties_widget->layout()->addWidget(labels["label"]=new QLabel(trUtf8("Общие параметры воротника")));
    //labels["label"]->setStyleSheet("*{font-weight:bold;}");
    QString items3[]={trUtf8("Симметричное"),trUtf8("Асимитричное"),NULL};
    combobox["vorot_dsgn"] =this->AddComboBoxProperty(trUtf8("Оформление воротника:"),items3,"vorot_dsgn");

    QString items31[]={trUtf8("нет планки"),trUtf8("нет планки"),trUtf8("есть планка"),NULL};
    combobox["vplanka"] =this->AddComboBoxProperty(trUtf8("Длина планки"),items31,"z6");
    combobox["vplanka"]->GetWidget()->setVisible(false);
    QString items32[]={trUtf8("Планка до горловины"),trUtf8("Планка до верхнего края воротника"),NULL};
    combobox["vorot_planka"] =this->AddComboBoxProperty(trUtf8("Длина планки"),items32,"vorot_planka");

    dspinbox["H1"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника спереди, см"),"H1",0.5f,0.1f,50.0f);
    dspinbox["H2"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника сбоку, см"),"H2",0.5f,0.1f,50.0f);
    dspinbox["H3"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника сзади, см"),"H3",0.5f,0.1f,50.0f);
    dspinbox["Pos1"] = this->AddDoubleSpinBoxProperty(trUtf8("Оттяжка/ Посадка на участке полочки, см"),"Pos1",0.5f,-20.0f,50.0f);
    dspinbox["Pos2"] = this->AddDoubleSpinBoxProperty(trUtf8("Оттяжка/ Посадка на участке спинки, см"),"Pos2",0.5f,-20,50.0f);
//--------------------------------------------//
    dspinbox["H1lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника спереди лев пол, см"),"H1lev",0.5f,0.1f,50.0f);
    dspinbox["H2lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника сбоку левый, см"),"H2lev",0.5f,0.1f,50.0f);
    dspinbox["H3lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Высота воротника сзади левая спинка, см"),"H3lev",0.5f,0.1f,50.0f);
    dspinbox["Pos1lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Оттяжка/ Посадка на участке полочки левой, см"),"Pos1lev",0.5f,-20.0f,50.0f);
    dspinbox["Pos2lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Оттяжка/ Посадка на участке спинки левой, см"),"Pos2lev",0.5f,-20.0,50.0f);
//--------------------------------------------//
    dspinbox["OYsp"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для y. спинки, см"),"OYsp",0.5f,0.0f,10.0f);
    dspinbox["OYspa"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной, для y. спинки, град"),"OYspa",1,-360,360);
    dspinbox["OYsh"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для уровня пл. шва, см"),"OYsh",0.5f,0.0f,10.0f);
    dspinbox["OYsha"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной, для уровня пл. шва, град"),"OYsha",1,-360,360);
    dspinbox["OYpo"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для y. полочки, см"),"OYpo",0.5f,0.0f,10.0f);
    dspinbox["OYpoa"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной, для y. полочки, град"),"OYpoa",1,-360,360);
    //QLabel* label2;
    //this->properties_widget->layout()->addWidget(labels["label2"]=new QLabel(trUtf8("Характеристика концов стойки")));
    //labels["label2"]->setStyleSheet("*{font-weight:bold;}");
    QString items4[]={trUtf8("Доходит до конца борта/разреза"),trUtf8("НЕ доходит до конца борта/разреза"),trUtf8("Выходит за край борта/разреза"),NULL};
    combobox["stoika_krai"] =this->AddComboBoxProperty(trUtf8("Край воротника стойки:"),items4,"stoika_krai");
    combobox["stoika_dsgn"] =this->AddComboBoxProperty(trUtf8("Оформление концов стойки:"),items3,"stoika_dsgn");
    dspinbox["A"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края борта до края воротника, см"),"A",0.5f,0.0f,50.0f);
    dspinbox["AL"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края борта до края воротника слева, см"),"AL",0.5f,0.0f,50.0f);
    //QLabel* label3;
    //this->properties_widget->layout()->addWidget(labels["label3"]=new QLabel(trUtf8("Тип оформления концов стойки")));
    //labels["label3"]->setStyleSheet("*{font-weight:bold;}");
    QString items5[]={trUtf8("Оформление углом"),trUtf8("Оформление сплайном"),NULL};
    combobox["Arut"] =this->AddComboBoxProperty(trUtf8("Правый верхний:"),items5,"Arut");
    this->dsgnpoints("c1");
    combobox["Ardt"] =this->AddComboBoxProperty(trUtf8("Правый нижний:"),items5,"Ardt");
    this->dsgnpoints("c3");
    combobox["Alut"] =this->AddComboBoxProperty(trUtf8("Левый верхний:"),items5,"Alut");
    this->dsgnpoints("c0");
    combobox["Aldt"] =this->AddComboBoxProperty(trUtf8("Левый нижний:"),items5,"Aldt");
    this->dsgnpoints("c2");
    //dspinbox["Alu"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол правый верхний, см"),"Alu",1,-360,360.0f);
    //dspinbox["Ald"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол правый нижний, см"),"Ald",1,-360,360.0f);
    //dspinbox["Aru"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол левый верхний, см"),"Aru",1,-360,360.0f);
    //dspinbox["Ard"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол левый нижний, см"),"Ard",1,-360,360.0f);


    //Воротник Разведение
    QString items6[] = {trUtf8("верхняя линия полочки"),trUtf8("верхняя линия спинки"),
                        trUtf8("нижняя линия полочки"), trUtf8("нижняя линия спинки"),NULL};
    combobox["v_r_s"] = this->AddComboBoxProperty(trUtf8("<b>Разведение</b>"),items6,"v_r_s");
    combobox["v_r_s"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["v_r_s"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));

    this->commonValue("v_r_sN:Default") = 2;
    ispinbox["v_r_sN"] = this->AddSpinBoxProperty(trUtf8("Число линий разведения"),"v_r_sN",1,2,20);
    ispinbox["v_r_sN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["v_r_s"],1 ));
    ispinbox["v_r_sN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["v_r_s"],3 ),Elasticas::OperationOr);

    this->commonValue("v_r_pN:Default") = 2;
    ispinbox["v_r_pN"] = this->AddSpinBoxProperty(trUtf8("Число линий разведения"),"v_r_pN",1,2,20);
    ispinbox["v_r_pN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["v_r_s"],0 ));
    ispinbox["v_r_pN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["v_r_s"],2 ),Elasticas::OperationOr);

    v_r_add( "v_r_pu",0 );
    v_r_add( "v_r_su",1 );
    v_r_add( "v_r_pd",2 );
    v_r_add( "v_r_sd",3 );

//Условия
    //Условие воротника
    combobox["vorot_planka"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    this->combobox["vorot_type"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    this->combobox["vorot_form"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    this->combobox["vorot_dsgn"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));

    dspinbox["H1"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["H2"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["H3"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["Pos1"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["Pos2"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["H1lev"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["H2lev"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["H3lev"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    //dspinbox["Pos1lev"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    //dspinbox["Pos2lev"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["stoika_krai"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    dspinbox["A"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["Arut"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["Ardt"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["Alut"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    combobox["Aldt"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ));
    ///Условие Цельнокроенный со станом
    combobox["vorot_planka"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    this->combobox["vorot_form"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    this->combobox["vorot_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));

    dspinbox["H1"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["H2"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["H3"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["Pos1"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["Pos2"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["H2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    dspinbox["Pos1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["Pos2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["OYsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["OYspa"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["OYsh"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["OYsha"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["OYpo"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    dspinbox["OYpoa"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["A"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    dspinbox["AL"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    combobox["Ardt"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    combobox["Alut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    combobox["Aldt"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    /////////
    this->combobox["vorot_form"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));
    //dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ));
    combobox["vorot_planka"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["claspl"],2 ), Elasticas::OperationAndNot);
    combobox["vorot_planka"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1 ));
    dspinbox["H2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1 ));
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1 ), Elasticas::OperationAnd);
    dspinbox["Pos1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1 ), Elasticas::OperationAnd);

    dspinbox["Pos2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1 ), Elasticas::OperationAnd);
    //dspinbox["Pos2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ),Elasticas::OperationAnd);

    //dspinbox["Pos2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["claspl"],1 ),Elasticas::OperationOr);
    //dspinbox["Pos2lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],0 ),Elasticas::OperationAndNot);



    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["claspl"],0 ),Elasticas::OperationAnd);
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["claspl"],1 ),Elasticas::OperationAnd);
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ),Elasticas::OperationAnd);

    //dspinbox["Pos1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["claspl"],0 ),Elasticas::OperationAnd);


    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ),Elasticas::OperationAndNot );

    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cutl"],0 ),Elasticas::OperationOr);
    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ),Elasticas::OperationAnd);
    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1),Elasticas::OperationAnd );
    dspinbox["H1lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1),Elasticas::OperationAnd );

    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cutl"],1 ),Elasticas::OperationOr);
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ),Elasticas::OperationAnd);
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_dsgn"],1),Elasticas::OperationAnd );
    dspinbox["H3lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1),Elasticas::OperationAnd );
    //this->combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_dsgn"],0 ));
    this->dspinbox["A"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_krai"],0 ),Elasticas::OperationAndNot);
    this->dspinbox["AL"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_krai"],0 ),Elasticas::OperationAndNot);
    this->dspinbox["AL"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_dsgn"],1 ),Elasticas::OperationAnd);

    this->combobox["Ardt"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_krai"],2 ),Elasticas::OperationAnd);
    this->combobox["Aldt"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_krai"],2 ),Elasticas::OperationAnd);
    combobox["vorot_planka"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],2 ),Elasticas::OperationAnd);
    combobox["Aldt"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_dsgn"],1 ),Elasticas::OperationAnd);
    combobox["Alut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["stoika_dsgn"],1 ),Elasticas::OperationAnd);

    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],1 ),Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationOr);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],2 ),Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_planka"],1 ), Elasticas::OperationAndNot);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ), Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["stoika_krai"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],0 ),Elasticas::OperationAnd);

    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],1 ),Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationOr);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],2 ),Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_planka"],1 ), Elasticas::OperationAndNot);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["stoika_dsgn"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],0 ),Elasticas::OperationAnd);
    ///
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],1 ),Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationOr);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],2 ),Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_planka"],1 ), Elasticas::OperationAndNot);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],0 ), Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ), Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    combobox["Arut"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],0 ),Elasticas::OperationAnd);

    //Сигналы!
    QObject::connect(dspinbox["c2_b"],SIGNAL(onChanged()),this,SLOT(heihgt_leftbottom()));
    QObject::connect(dspinbox["c0_b"],SIGNAL(onChanged()),this,SLOT(heihgt_lefttop()));
    QObject::connect(dspinbox["c3_b"],SIGNAL(onChanged()),this,SLOT(heihgt_rightbottom()));
    QObject::connect(dspinbox["c1_b"],SIGNAL(onChanged()),this,SLOT(heihgt_righttop()));

    QObject::connect(combobox["vorot_type"],SIGNAL(onChanged()),this,SLOT(vorotnik_celnokroeny()));
    QObject::connect(checkbox["is_vorot"],SIGNAL(onChanged()),this,SLOT(is_vorotnik()));
    ///Цельнокроеный со станом
    //QString items8[]={trUtf8("Да"), trUtf8("Нет"), NULL};
    //combobox["c_clasp"] =this->AddComboBoxProperty(trUtf8("Застежка до верхнего края воротника:"),items8,"c_clasp");
    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],0 ), Elasticas::OperationAnd);

    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["clasp"],1 ), Elasticas::OperationAnd);
    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vplanka"],0 ), Elasticas::OperationAndNot);
    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],0 ), Elasticas::OperationAnd);
    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["cut"],1 ), Elasticas::OperationOr);
    //combobox["c_clasp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],0 ), Elasticas::OperationAnd);
    //combobox["c_clasp"]->AddCondition(new Elasticas::CheckBoxCondition( checkbox["is_vorot"],true ), Elasticas::OperationAnd);
    //(combobox["clasp_type"]->GetCurrentId() != 0)&&
    //            (combobox["clasp"]->GetCurrentId() != 0))||
    //            (combobox["cut"]->GetCurrentId() != 0)


    QString items7[]={trUtf8("Основные"),trUtf8("вытачек на полочке"),
                      trUtf8("вытачек на спинке"),NULL};
    combobox["c_darts"] =this->AddComboBoxProperty(trUtf8("Параметры:"),items7,"c_darts");
    combobox["c_darts"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],0 ), Elasticas::OperationAnd);
    //без вытачек
    this->commonValue("c_0_nsp:Default")=4;
    dspinbox["c_0_nsp"] = this->AddDoubleSpinBoxProperty(trUtf8("Нсп, см"),"c_0_nsp",0.5f,0.0f,50.0f);
    dspinbox["c_0_nsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_asp:Default")=0;
    dspinbox["c_0_asp"] = this->AddDoubleSpinBoxProperty(trUtf8("Асп, град"),"c_0_asp",1,-180.0f,180.0f);
    //dspinbox["c_0_asp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);

    this->commonValue("c_0_nsb:Default")=4;
    dspinbox["c_0_nsb"] = this->AddDoubleSpinBoxProperty(trUtf8("Нсб, см"),"c_0_nsb",0.5f,0.0f,50.0f);
    dspinbox["c_0_nsb"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_asb:Default")=-15;
    dspinbox["c_0_asb"] = this->AddDoubleSpinBoxProperty(trUtf8("Асб, град"),"c_0_asb",1,-180.0f,180.0f);
    dspinbox["c_0_asb"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);

    this->commonValue("c_0_nsz:Default")=4;
    dspinbox["c_0_nsz"] = this->AddDoubleSpinBoxProperty(trUtf8("Нсз, см"),"c_0_nsz",0.5f,0.0f,50.0f);
    dspinbox["c_0_nsz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_asz:Default")=0;
    dspinbox["c_0_asz"] = this->AddDoubleSpinBoxProperty(trUtf8("Асз, град"),"c_0_asz",1,-180.0f,180.0f);
    //dspinbox["c_0_asz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);

    this->commonValue("c_0_d:Default")=1;
    dspinbox["c_0_d"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние для сглаживания переднего контура, см"),"c_0_d",0.5f,0.0f,50.0f);
    //dspinbox["c_0_d"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_e:Default")=1;
    dspinbox["c_0_e"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние для сглаживания бокового контура, см"),"c_0_e",0.5f,0.0f,50.0f);
    dspinbox["c_0_e"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_f:Default")=1;
    dspinbox["c_0_f"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние для сглаживания заднего контура, см"),"c_0_f",0.5f,0.0f,50.0f);
    //dspinbox["c_0_f"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);

    this->commonValue("c_0_dk:Default")=0;
    dspinbox["c_0_dk"] = this->AddDoubleSpinBoxProperty(trUtf8("Кривизна переднего контура по биссектрисе угла, см"),"c_0_dk",0.1f,-10.0f,50.0f);
    //dspinbox["c_0_dk"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_ek:Default")=0.2;
    dspinbox["c_0_ek"] = this->AddDoubleSpinBoxProperty(trUtf8("Кривизна бокового контура по биссектрисе угла, см"),"c_0_ek",0.1f,-10.0f,50.0f);
    dspinbox["c_0_ek"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_fk:Default")=0;
    dspinbox["c_0_fk"] = this->AddDoubleSpinBoxProperty(trUtf8("Кривизна заднего контура по биссектрисе угла, см"),"c_0_fk",0.1f,-10.0f,50.0f);
    //dspinbox["c_0_fk"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);

    this->commonValue("c_0_bsbp:Default")=0;
    dspinbox["c_0_bsbp"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной для оформления среза сбп, град"),"c_0_bsbp",1,-90.0f,90.0f);
    dspinbox["c_0_bsbp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    //this->commonValue("c_0_bsbsp:Default")=0;
    //dspinbox["c_0_bsbsp"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной для оформления среза сбсп, град"),"c_0_bsbsp",1,-180.0f,180.0f);
    //dspinbox["c_0_bsbsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_bsp:Default")=0;
    dspinbox["c_0_bsp"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной для оформления среза сп, град"),"c_0_bsp",1,-90.0f,90.0f);
    dspinbox["c_0_bsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);
    this->commonValue("c_0_bsz:Default")=0;
    dspinbox["c_0_bsz"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной для оформления среза сз, град"),"c_0_bsz",1,-180.0f,180.0f);
    dspinbox["c_0_bsz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],0 ), Elasticas::OperationAnd);


    this->properties_widget->layout()->addWidget(labels["alert"]=new QLabel(trUtf8("Не активно до выбора застежки/разреза")));
    labels["alert"]->setStyleSheet("*{font-weight:bold;}");
    labels["alert"]->setVisible(false);
    /*dspinbox["c_0_bsz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_bsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_bsbp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_fk"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_ek"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_dk"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);

    dspinbox["c_0_f"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_e"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_d"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);

    dspinbox["c_0_nsz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_asz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_asb"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_nsb"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_asp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    dspinbox["c_0_nsp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    */combobox["c_darts"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);
    //dspinbox["c_0_asp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_mirror"],1 ), Elasticas::OperationAnd);

    //dspinbox["c_0_asz"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["VZ"],1 ), Elasticas::OperationAnd);


    //dspinbox["c_0_asp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["VP"],1 ), Elasticas::OperationAnd);


  //  dspinbox["c_0_asp"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_clasp"],1 ), Elasticas::OperationAnd);
    //Сигналы!
    QObject::connect(combobox["c_darts"],SIGNAL(onChanged()),this,SLOT(asp()));
    QObject::connect(checkbox["is_vorot"],SIGNAL(onChanged()),this,SLOT(asp()));
    QObject::connect(combobox["VP"],SIGNAL(onChanged()),this,SLOT(asp()));
    QObject::connect(combobox["clasp"],SIGNAL(onChanged()),this,SLOT(asp()));
    QObject::connect(combobox["vplanka"],SIGNAL(onChanged()),this,SLOT(asp()));
    QObject::connect(combobox["claspl"],SIGNAL(onChanged()),this,SLOT(asp()));

    QObject::connect(combobox["c_darts"],SIGNAL(onChanged()),this,SLOT(asz()));
    QObject::connect(checkbox["is_vorot"],SIGNAL(onChanged()),this,SLOT(asz()));
    QObject::connect(combobox["VZ"],SIGNAL(onChanged()),this,SLOT(asz()));
    QObject::connect(combobox["clasp"],SIGNAL(onChanged()),this,SLOT(asz()));
    QObject::connect(combobox["vplanka"],SIGNAL(onChanged()),this,SLOT(asz()));
    QObject::connect(combobox["claspl"],SIGNAL(onChanged()),this,SLOT(asz()));

    darts();

}
void DressVorotDialog::dsgnpoints( QString s )
{
    QString cond;
    if( s == "c0" )
        cond = "Alut";
    else if( s == "c1" )
        cond = "Arut";
    else if( s == "c2" )
        cond = "Aldt";
    else if( s == "c3" )
        cond = "Ardt";


    this->commonValue(s+"_a:Default")=1.5;
    this->commonValue(s+"_b:Default")=1.5;
    this->commonValue(s+"_cl:Default")=0;
    this->commonValue(s+"_ct:Default")=0;
    this->commonValue(s+"_a1:Default")=45;
    this->commonValue(s+"_a2:Default")=0;
    this->commonValue(s+"_a3:Default")=45;
    //"c0" "c0_a" "c0_b" "c0_cl" "c0_ct" "c0_a1" "c0_a2" "c0_a3"
    QString items[]={trUtf8("0"),trUtf8("1"),NULL};
    combobox[s] =this->AddComboBoxProperty(trUtf8("Количество точек:"),items,s);
    //ispinbox[s] = this->AddSpinBoxProperty(trUtf8("Количество точек, см"),s,1,0,1);
    dspinbox[s+"_ct"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по биссектрисе угла, см"),s+"_ct",0.1,-10,10);
    dspinbox[s+"_cl"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение в сторону верхнего среза воротника, см"),s+"_cl",0.1,-10,10);
    dspinbox[s+"_b"] = this->AddDoubleSpinBoxProperty(trUtf8("Отступ по верхнему срезу воротника, см"),s+"_b",0.1,0,10.0f);
    dspinbox[s+"_a"] = this->AddDoubleSpinBoxProperty(trUtf8("Отступ по высоте воротника, см"),s+"_a",0.1,0,10.0f);


    dspinbox[s+"_a1"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке на верхней линии, град"),s+"_a1",1,-360,360.0f);
    dspinbox[s+"_a3"] = this->AddDoubleSpinBoxProperty(trUtf8("угол касательной в точке на высоте воротника, град"),s+"_a3",1,-360,360.0f);
    dspinbox[s+"_a2"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в дополнительной точке, град"),s+"_a2",1,-360,360.0f);

    combobox[s]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_b"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_cl"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_ct"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_a1"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_a2"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));
    dspinbox[s+"_a3"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[cond],1 ));

    dspinbox[s+"_cl"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[s],1 ),Elasticas::OperationAnd);
    dspinbox[s+"_ct"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[s],1 ),Elasticas::OperationAnd);
    //dspinbox[s+"_a1"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[s],1 ),Elasticas::OperationAnd);
    dspinbox[s+"_a2"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[s],1 ),Elasticas::OperationAnd);
    //dspinbox[s+"_a3"]->AddCondition(new Elasticas::ComboBoxCondition( combobox[s],1 ));
}
void DressVorotDialog::setheights( double hl, double hr )
{
    this->heightl = hl;
    this->heightr = hr;
    dspinbox["c0_b"]->SetMinMax( 0, heightl );
    dspinbox["c1_b"]->SetMinMax( 0, heightr );
    dspinbox["c2_b"]->SetMinMax( 0, heightl );
    dspinbox["c3_b"]->SetMinMax( 0, heightr );
}
void DressVorotDialog::minmaxheights( int i )
{
    switch(i)
    {
        case 1:
            //dspinbox["c0_b"]->SetMinMax( 0, heightl );
            //dspinbox["c2_b"]->blockSignals(true);
            dspinbox["c2_b"]->SetMinMax( 0, heightl-dspinbox["c0_b"]->GetValue() );
            dspinbox["c2_b"]->SetMinMax( 0, heightl );
            //dspinbox["c2_b"]->blockSignals(false);
            //dspinbox["c2_b"]->SetMinMax( 0, heightl-dspinbox["c0_b"]->GetValue() );
        break;
        case 2:
            //dspinbox["c1_b"]->SetMinMax( 0, heightr );
            //dspinbox["c3_b"]->blockSignals(true);
            dspinbox["c3_b"]->SetMinMax( 0, heightr-dspinbox["c1_b"]->GetValue() );
            dspinbox["c3_b"]->SetMinMax( 0, heightr );
            //dspinbox["c3_b"]->blockSignals(false);
            //dspinbox["c3_b"]->SetMinMax( 0, heightr-dspinbox["c1_b"]->GetValue() );

        break;
        case 3:
            //dspinbox["c2_b"]->SetMinMax( 0, heightl );
            dspinbox["c0_b"]->SetMinMax( 0, heightl-dspinbox["c2_b"]->GetValue() );
            dspinbox["c0_b"]->SetMinMax( 0, heightl );
            //dspinbox["c0_b"]->SetMinMax( 0, heightl-dspinbox["c2_b"]->GetValue() );

        break;
        case 4:
            //dspinbox["c3_b"]->SetMinMax( 0, heightr );
            dspinbox["c1_b"]->SetMinMax( 0, heightr-dspinbox["c3_b"]->GetValue() );
            dspinbox["c1_b"]->SetMinMax( 0, heightr );
            //dspinbox["c1_b"]->SetMinMax( 0, heightr-dspinbox["c3_b"]->GetValue() );

        break;
    }
}
void DressVorotDialog::heihgt_leftbottom()
{
    minmaxheights(3);
}
void DressVorotDialog::heihgt_lefttop()
{
    minmaxheights(1);
}
void DressVorotDialog::heihgt_rightbottom()
{
    minmaxheights(4);
}
void DressVorotDialog::heihgt_righttop()
{
    minmaxheights(2);
}
void DressVorotDialog::is_vorotnik()
{
    if((combobox["vorot_type"]->GetState())&&(combobox["vorot_type"]->GetCurrentId()==0))
    {
        if(combobox["is_mirror"]->GetCurrentId()==0)
            this->labels["alert"]->setVisible(true);
        else
            this->labels["alert"]->setVisible(false);
    }
    else
    {
        this->labels["alert"]->setVisible(false);
    }
//    if( ((QCheckBox*)checkbox["is_vorot"]->GetWidget())->isChecked() == true )

//        this->labels["alert"]->setVisible(true);
//    else
//        this->labels["alert"]->setVisible(false);


}
void DressVorotDialog::vorotnik_celnokroeny()
{

}
void DressVorotDialog::SetDspinVal( QString name, double d )
{
    this->dspinbox[name]->ReadVariantValue( d );
}
void DressVorotDialog::SetDspinMinMax( QString name, double min, double max )
{
    this->dspinbox[name]->SetMinMax( min,max );
}
void DressVorotDialog::changelabel( QString name, bool visible, QString text )
{
    if( text == QString(";") )
        text = this->labels[name]->text();

    this->labels[name]->setText( text );
    this->labels[name]->setVisible( visible );
}
void DressVorotDialog::changeDSPINstate( QString name, bool state )
{
    dspinbox[name]->GetWidget()->setVisible( state );
}
void DressVorotDialog::asp()
{
    if((combobox["c_darts"]->GetState())&&(combobox["c_darts"]->GetCurrentId()==0)&&(combobox["VP"]->GetCurrentId()==1) )
    {
        dspinbox["c_0_asp"]->ChangeState(true);
        dspinbox["c_0_d"]->ChangeState(true);
        dspinbox["c_0_dk"]->ChangeState(true);
    }
    else
    {
        dspinbox["c_0_asp"]->ChangeState(false);
        dspinbox["c_0_d"]->ChangeState(false);
        dspinbox["c_0_dk"]->ChangeState(false);
    }

    if( combobox["clasp"]->GetCurrentId()==1 )
        if( combobox["vplanka"]->GetCurrentId()!=0 )
            if( combobox["claspl"]->GetCurrentId()==0 )
            {
                dspinbox["c_0_asp"]->ChangeState(false);
                dspinbox["c_0_d"]->ChangeState(false);
                dspinbox["c_0_dk"]->ChangeState(false);
            }
    // if( ( LD("is_clasp") == 1 )&&( LD("clasp_form") != 0 )&&( LD("clasp_location")==0 ) )
}
void DressVorotDialog::asz()
{
    if((combobox["c_darts"]->GetState())&&(combobox["c_darts"]->GetCurrentId()==0)&&(combobox["VZ"]->GetCurrentId()==1) )
    {
        dspinbox["c_0_asz"]->ChangeState(true);
        dspinbox["c_0_f"]->ChangeState(true);
        dspinbox["c_0_fk"]->ChangeState(true);
    }
    else
    {
        dspinbox["c_0_asz"]->ChangeState(false);
        dspinbox["c_0_f"]->ChangeState(false);
        dspinbox["c_0_fk"]->ChangeState(false);
    }
    if( combobox["clasp"]->GetCurrentId()==1 )
        if( combobox["vplanka"]->GetCurrentId()!=0 )
            if( combobox["claspl"]->GetCurrentId()==1 )
            {
                dspinbox["c_0_asz"]->ChangeState(false);
                dspinbox["c_0_f"]->ChangeState(false);
                dspinbox["c_0_fk"]->ChangeState(false);
            }
}
void DressVorotDialog::darts()
{
    QString items0[]={trUtf8("1"),trUtf8("2"),NULL};
    //combobox["d_loc"] =this->AddComboBoxProperty(trUtf8("Вытачки:"),items0,"d_loc");
    combobox["d_count"] = this->AddComboBoxProperty(trUtf8("Число вытачек:"),items0,"d_count");
    combobox["d_count2"] = this->AddComboBoxProperty(trUtf8("Число вытачек:"),items0,"d_count2");
    //далее длдя кждой вытачки
    //111111111111111111111111111111111//
    this->commonValue("d1_start:Default")=0.0f;
    dspinbox["d1_start"] = this->AddDoubleSpinBoxProperty(trUtf8("начало вытачки №1 от центра (среднего шва),см"),"d1_start",0.1,0.0f,100.0f);
    this->commonValue("d1_a:Default")=0.0f;
    dspinbox["d1_a"] = this->AddDoubleSpinBoxProperty(trUtf8("направление вытачки №1, град."),"d1_a",1,-90.0f,90.0f);
    this->commonValue("d1_l:Default")=0.0f;
    dspinbox["d1_l"] = this->AddDoubleSpinBoxProperty(trUtf8("длина вытачки №1, см"),"d1_l",0.1f,0.0f,100.0f);
    dspinbox["d1_r"] = this->AddDoubleSpinBoxProperty(trUtf8("раствор вытачки №1, см"),"d1_r",0.1f,0.0f,10.0f);
    //222222222222222222222222222222222//
    this->commonValue("d2_start:Default")=0.0f;
    dspinbox["d2_start"] = this->AddDoubleSpinBoxProperty(trUtf8("начало вытачки №2 от центра (среднего шва),см"),"d2_start",0.1,0.0f,100.0f);
    this->commonValue("d2_a:Default")=0.0f;
    dspinbox["d2_a"] = this->AddDoubleSpinBoxProperty(trUtf8("направление вытачки №2, град."),"d2_a",1,-90.0f,90.0f);
    this->commonValue("d2_l:Default")=0.0f;
    dspinbox["d2_l"] = this->AddDoubleSpinBoxProperty(trUtf8("длина вытачки №2, см"),"d2_l",0.1f,0.0f,100.0f);
    dspinbox["d2_r"] = this->AddDoubleSpinBoxProperty(trUtf8("раствор вытачки №2, см"),"d2_r",0.1f,0.0f,10.0f);
    //3333333333333333333333333333333333//
    this->commonValue("d3_start:Default")=0.0f;
    dspinbox["d3_start"] = this->AddDoubleSpinBoxProperty(trUtf8("начало вытачки №1 от центра (среднего шва),см"),"d3_start",0.1,0.0f,100.0f);
    this->commonValue("d3_a:Default")=0.0f;
    dspinbox["d3_a"] = this->AddDoubleSpinBoxProperty(trUtf8("направление вытачки №1, град."),"d3_a",1,-90.0f,90.0f);
    this->commonValue("d3_l:Default")=0.0f;
    dspinbox["d3_l"] = this->AddDoubleSpinBoxProperty(trUtf8("длина вытачки №1, см"),"d3_l",0.1f,0.0f,100.0f);
    dspinbox["d3_r"] = this->AddDoubleSpinBoxProperty(trUtf8("раствор вытачки №1, см"),"d3_r",0.1f,0.0f,10.0f);
    //444444444444444444444444444444444444//
    this->commonValue("d4_start:Default")=0.0f;
    dspinbox["d4_start"] = this->AddDoubleSpinBoxProperty(trUtf8("начало вытачки №2 от центра (среднего шва),см"),"d4_start",0.1,0.0f,100.0f);
    this->commonValue("d4_a:Default")=0.0f;
    dspinbox["d4_a"] = this->AddDoubleSpinBoxProperty(trUtf8("направление вытачки №2, град."),"d4_a",1,-90.0f,90.0f);
    this->commonValue("d4_l:Default")=0.0f;
    dspinbox["d4_l"] = this->AddDoubleSpinBoxProperty(trUtf8("длина вытачки №2, см"),"d4_l",0.1f,0.0f,100.0f);
    dspinbox["d4_r"] = this->AddDoubleSpinBoxProperty(trUtf8("раствор вытачки №2, см"),"d4_r",0.1f,0.0f,10.0f);
    //условия
    combobox["d_count"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    combobox["d_count2"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    //111111111111111111111111//
    dspinbox["d1_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d1_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d1_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d1_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    //22222222222222222222222//
    dspinbox["d2_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count"],1 ), Elasticas::OperationAnd);
    dspinbox["d2_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count"],1 ), Elasticas::OperationAnd);
    //33333333333333333333//
    dspinbox["d3_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d3_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d3_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d3_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    //22222222222222222222222//
    dspinbox["d4_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d4_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d4_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d4_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["c_darts"],2 ), Elasticas::OperationAnd);
    dspinbox["d4_start"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count2"],1 ), Elasticas::OperationAnd);
    dspinbox["d4_a"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count2"],1 ), Elasticas::OperationAnd);
    dspinbox["d4_l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count2"],1 ), Elasticas::OperationAnd);
    dspinbox["d4_r"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["d_count2"],1 ), Elasticas::OperationAnd);
}

