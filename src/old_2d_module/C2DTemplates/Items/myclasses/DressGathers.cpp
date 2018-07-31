#include "DressGathers.h"
DressGathers::DressGathers():Elasticas::PropertiesDialog(trUtf8("Складки отрезного воротника-стойки"),"Dress:")
{
//default
    /*this->commonValue("G:N:Default") = 0;
    this->commonValue("G:A:Default") = 0;
    this->commonValue("G:A:Default") = 0;
    this->commonValue("G:A:Default") = 0;
    this->commonValue("G:A:Default") = 0;
    this->commonValue("G:OX:Default") = 0;
    this->commonValue("G:OX:Default") = 0;*/
//Скрытые формы для уже заданных в других диалогах параметров
    QString items0[]={trUtf8("0"),trUtf8("1"),NULL};
    combobox["is_vorot"] =this->AddComboBoxProperty(trUtf8("is_vorot"),items0,"is_vorot");
    combobox["is_vorot"]->GetWidget()->setVisible(false);
    combobox["asimm"] =this->AddComboBoxProperty(trUtf8("simm"),items0,"vorot_dsgn");
    combobox["asimm"]->GetWidget()->setVisible(false);

    QString items00[]={trUtf8("Цельнокроеный со станом"),trUtf8("Самостоятельный элемент"),NULL};
    combobox["vorot_type"] =this->AddComboBoxProperty(trUtf8("Воротник:"),items00,"vorot_type");
    combobox["vorot_type"]->GetWidget()->setVisible(false);
//формы

    this->properties_widget->layout()->addWidget(labels["alert2"]=new QLabel(trUtf8("Неактивно")));
    labels["alert2"]->setStyleSheet("*{font-weight:bold;}");

    ispinbox["G:N"] = this->AddSpinBoxProperty(trUtf8("Число складок"),"G:N",1,1,10);
    dspinbox["G:A1"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края воротника до 1 складки сверху, см"),"G:A1",0.5,0.5,10);
    dspinbox["G:A2"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края воротника до 1 складки снизу, см"),"G:A2",0.5,0.5,10);

    dspinbox["G:B1"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между складками сверху, см"),"G:B1",0.5,0.5,10);
    dspinbox["G:B2"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между складками снизу, см"),"G:B2",0.5,0.5,10);

    QString items1[]={trUtf8("Односторонняя к центру"),trUtf8("Односторонняя от центра"),trUtf8("Встречная складка"),NULL};
    combobox["G:Type"] = this->AddComboBoxProperty( trUtf8("Тип складки"),items1,"G:Type" );

    dspinbox["G:C1"] = this->AddDoubleSpinBoxProperty(trUtf8("Глубина складки по верхнему срезу, см"),"G:C1",0.5,0,10);
    dspinbox["G:C2"] = this->AddDoubleSpinBoxProperty(trUtf8("Глубина складки по нижнему срезу, см"),"G:C2",0.5,0,10);

    ///LABEL LEV
    this->properties_widget->layout()->addWidget(labels["alert"]=new QLabel(trUtf8("Значения для второй, несимметричной части воротника")));
    labels["alert"]->setStyleSheet("*{font-weight:bold;}");
    ispinbox["G:N:l"] = this->AddSpinBoxProperty(trUtf8("Число складок"),"G:N:l",1,1,10);
    dspinbox["G:A1:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края воротника до 1 складки сверху, см"),"G:A1:l",0.5,0.5,10);
    dspinbox["G:A2:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края воротника до 1 складки снизу, см"),"G:A2:l",0.5,0.5,10);

    dspinbox["G:B1:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между складками сверху, см"),"G:B1:l",0.5,0.5,10);
    dspinbox["G:B2:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Расстояние между складками снизу, см"),"G:B2:l",0.5,0.5,10);

    //QString items1[]={trUtf8("Односторонняя слева направо"),trUtf8("Односторонняя справа налево"),trUtf8("Встречная складка"),NULL};
    combobox["G:Type:l"] = this->AddComboBoxProperty( trUtf8("Тип складки"),items1,"G:Type:l" );

    dspinbox["G:C1:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Глубина складки по верхнему срезу, см"),"G:C1:l",0.5,0,10);
    dspinbox["G:C2:l"] = this->AddDoubleSpinBoxProperty(trUtf8("Глубина складки по нижнему срезу, см"),"G:C2:l",0.5,0,10);

//Условия
    ispinbox["G:N:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A1:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A2:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B1:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B2:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    combobox["G:Type:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C1:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C2:l"]->AddCondition(new Elasticas::ComboBoxCondition( combobox["asimm"],1 ),Elasticas::OperationAnd);


    ispinbox["G:N"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    combobox["G:Type"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    ispinbox["G:N:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    combobox["G:Type:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["is_vorot"],1 ),Elasticas::OperationAnd);

    ispinbox["G:N"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    combobox["G:Type"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C1"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C2"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    ispinbox["G:N:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:A2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:B2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    combobox["G:Type:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C1:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);
    dspinbox["G:C2:l"]->AddCondition( new Elasticas::ComboBoxCondition( combobox["vorot_type"],1 ),Elasticas::OperationAnd);

//Сигналы!
}
void DressGathers::SetDspinVal( QString name, double d )
{
    this->dspinbox[name]->ReadVariantValue( d );
}
double DressGathers::GetDspinVal( QString name )
{
    return this->dspinbox[name]->GetValue();
}
void DressGathers::SetSpinVal( QString name, double d )
{
    this->ispinbox[name]->ReadVariantValue( d );
}
void DressGathers::SetDspinMinMax( QString name, double min, double max )
{
    this->dspinbox[name]->SetMinMax( min,max );
}
void DressGathers::showlabel( QString name, bool visible )
{
    this->labels[name]->setVisible( visible );
}
void DressGathers::labelchangetext( QString name, QString s )
{
    this->labels[name]->setText( s );
}
void DressGathers::SetDspinText( QString name, QString txt )
{
    if( txt == "false" )
        this->dspinbox[name]->GetWidget()->setVisible( false );
    else
    {
        this->dspinbox[name]->GetWidget()->setVisible( true );
        QLabel * label1 = this->dspinbox[name]->GetLabel();
        label1->setText(txt);
    }
}
