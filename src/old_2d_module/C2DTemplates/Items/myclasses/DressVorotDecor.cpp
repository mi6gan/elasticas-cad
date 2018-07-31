#include "DressVorotDecor.h"
void DressVorotDecor::vd_add( QString name, int cond )
{
    this->commonValue(name+":Default") = 0;

    dspinbox[name] = this->AddDoubleSpinBoxProperty(trUtf8("Величина разведения, см"),name,0.5f,-20.0f,20.0f);
    dspinbox[name]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],cond ),Elasticas::OperationAnd);
}
DressVorotDecor::DressVorotDecor():Elasticas::PropertiesDialog(trUtf8("Дополнительное разведение воротника"),"Dress:")
{
//default
    this->commonValue("vd:Default") = 0;
    this->commonValue("vd_vN:Default") = 2;
    this->commonValue("vd_hN:Default") = 2;
//Скрытые формы для уже заданных в других диалогах параметров
    QString items0[]={trUtf8("0"),trUtf8("1"),NULL};
    combobox["is_vorot"] =this->AddComboBoxProperty(trUtf8("is_vorot"),items0,"is_vorot");
    combobox["is_vorot"]->GetWidget()->setVisible(false);

    combobox["vorot_type"] =this->AddComboBoxProperty(trUtf8("vorot-type"),items0,"vorot_type");
    combobox["vorot_type"]->GetWidget()->setVisible(false);

    combobox["is_clasp"] =this->AddComboBoxProperty(trUtf8("is_clasp"),items0,"z1");
    combobox["is_clasp"]->GetWidget()->setVisible(false);

    QString items1[]={trUtf8("0"),trUtf8("1"),trUtf8("2"),NULL};
    combobox["is_openclasp"] =this->AddComboBoxProperty(trUtf8("is_openclasp"),items1,"z6");
    combobox["is_openclasp"]->GetWidget()->setVisible(false);

    combobox["is_cut"] =this->AddComboBoxProperty(trUtf8("is_cut"),items0,"z7");
    combobox["is_cut"]->GetWidget()->setVisible(false);

    combobox["Arut"] =this->AddComboBoxProperty(trUtf8("Arut"),items0,"Arut");
    combobox["Arut"]->GetWidget()->setVisible(false);

    combobox["Ardt"] =this->AddComboBoxProperty(trUtf8("Ardt"),items0,"Ardt");
    combobox["Ardt"]->GetWidget()->setVisible(false);

    combobox["Alut"] =this->AddComboBoxProperty(trUtf8("Alut"),items0,"Alut");
    combobox["Alut"]->GetWidget()->setVisible(false);

    combobox["Aldt"] =this->AddComboBoxProperty(trUtf8("Aldt"),items0,"Aldt");
    combobox["Aldt"]->GetWidget()->setVisible(false);

    combobox["asimm"] =this->AddComboBoxProperty(trUtf8("simm"),items0,"vorot_dsgn");
    combobox["asimm"]->GetWidget()->setVisible(false);
//формы
    //combobox["s"] = this->AddCheckBoxProperty( trUtf8( "Симметричная горловина:" ),"sss", );

    //Воротник Разведение
    QString items5[] = {trUtf8("верхняя линия"), trUtf8("нижняя линия"),
                        trUtf8("по высоте у полочки"), trUtf8("по высоте у спинки"), NULL};
    combobox["vd"] = this->AddComboBoxProperty(trUtf8("<b>Разведение</b>"),items5,"vd");

    //combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["is_vorot"],true ));
    //combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ));

    ispinbox["vd_vN"] = this->AddSpinBoxProperty(trUtf8("Число линий разведения верхней/нижней"),"vd_vN",1,2,20);
    ispinbox["vd_vN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],0 ));
    ispinbox["vd_vN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],1 ), Elasticas::OperationOr);

    ispinbox["vd_hN"] = this->AddSpinBoxProperty(trUtf8("Число л. разв. полочки/спинки по в."),"vd_hN",1,2,20);
    ispinbox["vd_hN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],2 ));
    ispinbox["vd_hN"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],3 ),Elasticas::OperationOr);
    vd_add( "vd_v",0 );
    vd_add( "vd_d",1 );
    vd_add( "vd_p",2 );
    vd_add( "vd_s",3 );
    this->commonValue("vd_p_lev:Default") = 0;
    dspinbox["vd_p_lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Величина разведения lev, см"),"vd_p_lev",0.5f,-20.0f,20.0f);
    dspinbox["vd_p_lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],2 ),Elasticas::OperationAnd);
    dspinbox["vd_p_lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    this->commonValue("vd_s_lev:Default") = 0;
    dspinbox["vd_s_lev"] = this->AddDoubleSpinBoxProperty(trUtf8("Величина разведения lev, см"),"vd_s_lev",0.5f,-20.0f,20.0f);
    dspinbox["vd_s_lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["vd"],3 ),Elasticas::OperationAnd);
    dspinbox["vd_s_lev"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);

    this->properties_widget->layout()->addWidget(labels["alert"]=new QLabel(trUtf8("Не активно до выбора застежки/разреза")));
    labels["alert"]->setStyleSheet("*{font-weight:bold;}");
//Условия
/*    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["is_clasp"],0),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["is_openclasp"],0),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Arut"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Ardt"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Alut"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Aldt"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["is_vorot"],1),Elasticas::OperationAnd);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["vorot_type"],1),Elasticas::OperationAnd);

    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["is_cut"],0),Elasticas::OperationOrNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Arut"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Ardt"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Alut"],1),Elasticas::OperationAndNot);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Aldt"],1),Elasticas::OperationAndNot);

    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["is_vorot"],1),Elasticas::OperationAnd);
    combobox["vd"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["vorot_type"],1),Elasticas::OperationAnd);

*/
    //combobox["vd"]->GetWidget()->setVisible(false);
//Сигналы!
}
void DressVorotDecor::SetDspinVal( QString name, double d )
{
    this->dspinbox[name]->ReadVariantValue( d );
}
void DressVorotDecor::SetDspinMinMax( QString name, double min, double max )
{
    this->dspinbox[name]->SetMinMax( min,max );
}

void DressVorotDecor::showlabel( QString name, bool visible )
{
    this->labels[name]->setVisible( visible );
    if(visible)
        show_all_widgets(false);
    else
        show_all_widgets(true);
}
void DressVorotDecor::changelabel( QString name, QString text )
{
    this->labels[name]->setText( text );
}
void DressVorotDecor::changecommon( QString name, int value )
{
    this->commonValue(name+":Default") = value;
}
void DressVorotDecor::show_all_widgets( bool visible )
{

    combobox["vd"]->ChangeState(visible);
    /*foreach( Elasticas::CheckBoxProperty* p, checkbox  )
        p->GetWidget()->setVisible(visible);
    foreach( Elasticas::ComboBoxProperty* p1, combobox  )
        p1->GetWidget()->setVisible(visible);
    foreach( Elasticas::DoubleSpinBoxProperty* p2, dspinbox  )
        p2->GetWidget()->setVisible(visible);
    foreach( Elasticas::SpinBoxProperty* p3, ispinbox  )
        p3->GetWidget()->setVisible(visible);*/
}
