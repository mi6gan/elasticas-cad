#include "SleeveElDialog.h"
SleeveElDialog::SleeveElDialog():Elasticas::PropertiesDialog(trUtf8("Рукав"),"Dress:")
{
    this->commonValue("Sleeve:H:Default")=0.07f;
    this->commonValue("Sleeve:Step65:Default")=0.62f;
    this->commonValue("Sleeve:Step87:Default")=2;
    this->commonValue("Sleeve:Step93:Default")=1;
    ///////def end
    dspinbox["Sleeve:H"] = this->AddDoubleSpinBoxProperty(trUtf8("Норма посадки"),"Sleeve:H",0.01f,0.0f,3.0f);
    //dspinbox["Sleeve:Ppos1"] = this->AddDoubleSpinBoxProperty(trUtf8("Коэффициент посадки на участке 1"),"Sleeve:Ppos1",0.01f,0.0f,0.075f);
    //УСЛОВИЯ
   ///////////////////////////////////////////////////////////////////////////
    dspinbox["Sleeve:Step65"] = this->AddDoubleSpinBoxProperty(trUtf8("Sleeve:Step65"),"Sleeve:Step65",0.01f,0.0f,1.0f);
    dspinbox["Sleeve:Step87"] = this->AddDoubleSpinBoxProperty(trUtf8("Sleeve:Step87"),"Sleeve:Step87",0.5f,0.0f,40.0f);
    dspinbox["Sleeve:Step93"] = this->AddDoubleSpinBoxProperty(trUtf8("Sleeve:Step93 cm"),"Sleeve:Step93",0.1,0.0f,4.0f);

}
