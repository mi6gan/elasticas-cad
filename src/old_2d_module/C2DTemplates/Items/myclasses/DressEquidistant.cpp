#include "DressEquidistant.h"
DressEquidistant::DressEquidistant():Elasticas::PropertiesDialog(trUtf8("Редактирование верхней линии воротника"),"Dress:")
{
//default
    this->commonValue("1:A:Default") = 0;
    this->commonValue("2:A:Default") = 0;
    this->commonValue("3:A:Default") = 0;
    this->commonValue("4:A:Default") = 0;
    this->commonValue("5:A:Default") = 0;
    this->commonValue("L:OX:Default") = 0;
    this->commonValue("R:OX:Default") = 0;
//Скрытые формы для уже заданных в других диалогах параметров
    QString items0[]={trUtf8("0"),trUtf8("1"),NULL};
    combobox["is_vorot"] =this->AddComboBoxProperty(trUtf8("is_vorot"),items0,"is_vorot");
    combobox["is_vorot"]->GetWidget()->setVisible(false);

//формы
    dspinbox["L:OX"] = this->AddDoubleSpinBoxProperty(trUtf8("Длиннее/Короче слева, см"),"L:OX",0.1,-10,10);
    dspinbox["R:OX"] = this->AddDoubleSpinBoxProperty(trUtf8("Длиннее/Короче справа, см"),"R:OX",0.1,-10,10);
    this->properties_widget->layout()->addWidget(labels["alert"]=new QLabel(trUtf8("Угол касательной верхней линии воротника на уровне:")));
    labels["alert"]->setStyleSheet("*{font-weight:bold;}");
    dspinbox["1:A"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для y. спинки, град"),"1:A",1,-360,360);
    dspinbox["2:A"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной, для y. спинки, град"),"2:A",1,-360,360);
    dspinbox["3:A"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для уровня пл. шва, град"),"3:A",1,-360,360);
    dspinbox["4:A"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной, для уровня пл. шва, град"),"4:A",1,-360,360);
    dspinbox["5:A"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение по OY, для y. полочки, град"),"5:A",1,-360,360);
//Условия

//Сигналы!
}
void DressEquidistant::SetDspinVal( QString name, double d )
{
    this->dspinbox[name]->ReadVariantValue( d );
}
void DressEquidistant::SetDspinMinMax( QString name, double min, double max )
{
    this->dspinbox[name]->SetMinMax( min,max );
}
void DressEquidistant::SetDspinText( QString name, QString txt )
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
