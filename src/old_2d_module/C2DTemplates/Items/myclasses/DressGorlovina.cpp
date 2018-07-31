#include "DressGorlovina.h"
DressGorlovina::DressGorlovina():Elasticas::PropertiesDialog(trUtf8("Моделирование горловины"),"Dress:")
{
    this->commonValue("Smpl1:Default")=1.0f;
    this->commonValue("Smpl2:Default")=1.0f;
    this->commonValue("Smpl1m:Default")=1.0f;
    this->commonValue("Smpl2m:Default")=1.0f;

    ///////def end
    checkbox["is_mirror"] = this->AddCheckBoxProperty( trUtf8( "Симметричная горловина:" ),"is_mirror",true );

    QLabel* label;
    this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("Модельное расширение/углубление линии горловины")));
    label->setStyleSheet("*{font-weight:bold;}");
    dspinbox["dsp7"] = this->AddDoubleSpinBoxProperty(trUtf8("Углубление горловины на полочке, см"),"Rg1",0.1f,0.0f,100.0f);
    dspinbox["dsp8"] = this->AddDoubleSpinBoxProperty(trUtf8("Углубление горловины на спинке, см"),"Rg2",0.1f,0.0f,100.0f);
    dspinbox["dsp9"] = this->AddDoubleSpinBoxProperty(trUtf8("Расширение горловины у плечевого среза, см"),"Rg3",0.1f,0.0f,100.0f);
    dspinbox["dsp9m"] = this->AddDoubleSpinBoxProperty(trUtf8("Расширение горловины у плечевого среза слева, см"),"Rg3m",0.1f,0.0f,100.0f);


    this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("Смещение плечевого среза")));
    label->setStyleSheet("*{font-weight:bold;}");
    dspinbox["dsp1"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки основания шеи, см"),"Smpl1",0.1f,-100.0f,100.0f);
    dspinbox["dsp2"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки конца плеча, см"),"Smpl2",0.1f,-100.0f,100.0f);

    dspinbox["dsp1m"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки основания шеи слева, см"),"Smpl1m",0.1f,-100.0f,100.0f);
    dspinbox["dsp2m"] = this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки конца плеча слева, см"),"Smpl2m",0.1f,-100.0f,100.0f);

    //УСЛОВИЯ
    this->dspinbox["dsp9m"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false));
    this->dspinbox["dsp1m"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false));
    this->dspinbox["dsp2m"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false));
    ///////////////////////////////////////////////////////////////////////////

}
void DressGorlovina::setT31( double d )
{
    dspinbox["dsp9"]->SetMinMax( 0, floor(d)/10 );
    dspinbox["dsp9m"]->SetMinMax( 0, floor(d)/10 - 0.1 );
}
Elasticas::CheckBoxProperty* DressGorlovina::getcheckboxpropertypointer( QString s )
{
    return this->checkbox[s];
}
void DressGorlovina::setDSpinminmax(QString s, double min, double max)
{
    this->dspinbox[s]->SetMinMax( min,max );
}
void DressGorlovina::setSpinValue(QString s, double val)
{
    this->dspinbox[s]->ReadVariantValue( val );
}
