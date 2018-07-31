#include "DressGLine.h"
DressGLine::DressGLine():Elasticas::PropertiesDialog(trUtf8("Редактирование формы горловины"),"Dress:")
{
    //this->commonValue("Smpl1:Default")=1.0f;
    checkbox["is_mirror"] = this->AddCheckBoxProperty( trUtf8( "is_mir:" ),"is_mirror" );
    checkbox["is_mirror"]->GetWidget()->setVisible(false);
    ///////def end
    checkbox["nat1"] = this->AddCheckBoxProperty( trUtf8( "Сопряжение в точке ОШ сбоку уголом:" ),"nat1",false );
    checkbox["nat2"] = this->AddCheckBoxProperty( trUtf8( "Сопряжение в точке ОШ сбоку уголом m:" ),"nat2",false );
    QLabel* label;
    QString items1[]={trUtf8("Спереди"),trUtf8("Сзади"),trUtf8("И спереди, и сзади"),NULL};
    combobox["Gchange"] =this->AddComboBoxProperty(trUtf8("<b>Изменение формы горловины</b>"),items1,"Gchange");

    //this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("<b>Спинка:</b>")));
    checkbox["gssA"] = this->AddCheckBoxProperty( trUtf8( "Сопряжение в точке ОШ сзвди уголом:" ),"gssA",false );
    QString items2[]={trUtf8("0"),trUtf8("1"),trUtf8("2"),NULL};
    this->commonValue("gspAA:Default") = 0;
    dspinbox["gspAA"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сзади"),"gspAA",1,-360.0f,360.0f);
    this->commonValue("gspmAA:Default") = 0;
    dspinbox["gspmAA"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сзади, левой"),"gspmAA",1,-360.0f,360.0f);
    this->commonValue("gspAB:Default") = 0;
    dspinbox["gspAB"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сбоку (для спинки)"),"gspAB",1,-360.0f,360.0f);
    this->commonValue("gspmAB:Default") = 0;
    dspinbox["gspmAB"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сбоку (для спинки), левой"),"gspmAB",1,-360.0f,360.0f);
    combobox["gspcount"] = this->AddComboBoxProperty(trUtf8("Количество точек на спинке"),items2,"gspcount");
    checkbox["gspAS"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gspAS",false );
    this->commonValue("gsp0L:Default") = 0;
    dspinbox["gsp0L"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 left, см"),"gsp0L",0.1f,-100.0f,100.0f);
    this->commonValue("gsp0T:Default") = 0;
    dspinbox["gsp0T"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 top, см"),"gsp0T",0.1f,-100.0f,100.0f);
    this->commonValue("gsp0A:Default") = 0;
    dspinbox["gsp0A"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle, град"),"gsp0A",1,-360.0f,360.0f);
    this->commonValue("gsp0A2:Default") = 0;
    dspinbox["gsp0A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle 2, град"),"gsp0A2",1,-360.0f,360.0f);
    checkbox["gspAS1"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gspAS1",false );
    this->commonValue("gsp1L:Default") = 0;
    dspinbox["gsp1L"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 left, см"),"gsp1L",0.1f,-100.0f,100.0f);
    this->commonValue("gsp1T:Default") = 0;
    dspinbox["gsp1T"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 top, см"),"gsp1T",0.1f,-100.0f,100.0f);
    this->commonValue("gsp1A:Default") = 0;
    dspinbox["gsp1A"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle, град"),"gsp1A",1,-360.0f,360.0f);
    this->commonValue("gsp1A2:Default") = 0;
    dspinbox["gsp1A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle 2, град"),"gsp1A2",1,-360.0f,360.0f);

    combobox["gspmcount"] = this->AddComboBoxProperty(trUtf8("Количество точек на спинке nomirror"),items2,"gspmcount");
    checkbox["gspmAS"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gspmAS",false );
    this->commonValue("gspm0L:Default") = 0;
    dspinbox["gspm0L"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 left, см"),"gspm0L",0.1f,-100.0f,100.0f);
    this->commonValue("gspm0T:Default") = 0;
    dspinbox["gspm0T"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 top, см"),"gspm0T",0.1f,-100.0f,100.0f);
    this->commonValue("gspm0A:Default") = 0;
    dspinbox["gspm0A"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle, град"),"gspm0A",1,-360.0f,360.0f);
    this->commonValue("gspm0A2:Default") = 0;
    dspinbox["gspm0A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle 2, град"),"gspm0A2",1,-360.0f,360.0f);
    checkbox["gspmAS1"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gspmAS1",false );
    this->commonValue("gspm1L:Default") = 0;
    dspinbox["gspm1L"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 left, см"),"gspm1L",0.1f,-100.0f,100.0f);
    this->commonValue("gspm1T:Default") = 0;
    dspinbox["gspm1T"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 top, см"),"gspm1T",0.1f,-100.0f,100.0f);
    this->commonValue("gspm1A:Default") = 0;
    dspinbox["gspm1A"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle, град"),"gspm1A",1,-360.0f,360.0f);
    this->commonValue("gspm1A2:Default") = 0;
    dspinbox["gspm1A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle 2, град"),"gspm1A2",1,-360.0f,360.0f);

    checkbox["gpsA"] = this->AddCheckBoxProperty( trUtf8( "Сопряжение в точке ОШ спереди уголом:" ),"gpsA",false );
    //this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("<b>Полочка:</b>")));
    this->commonValue("gppAA:Default") = 0;
    dspinbox["gppAA"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи спереди"),"gppAA",1,-360.0f,360.0f);
    this->commonValue("gppmAA:Default") = 0;
    dspinbox["gppmAA"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи спереди, левой"),"gppmAA",1,-360.0f,360.0f);
    this->commonValue("gppAB:Default") = 0;
    dspinbox["gppAB"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сбоку (для полочки)"),"gppAB",1,-360.0f,360.0f);
    this->commonValue("gppmAB:Default") = 0;
    dspinbox["gppmAB"] = this->AddDoubleSpinBoxProperty(trUtf8("Угол касательной в точке основания шеи сбоку (для полочки), левой"),"gppmAB",1,-360.0f,360.0f);
    combobox["gppcount"] = this->AddComboBoxProperty(trUtf8("Количество точек на полочке"),items2,"gppcount");
    checkbox["gppAS"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gppAS",false );
    this->commonValue("gpp0L:Default") = 0;
    dspinbox["gpp0L"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 left, см"),"gpp0L",0.1f,-100.0f,100.0f);
    this->commonValue("gpp0T:Default") = 0;
    dspinbox["gpp0T"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 top, см"),"gpp0T",0.1f,-100.0f,100.0f);
    this->commonValue("gpp0A:Default") = 0;
    dspinbox["gpp0A"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle, град"),"gpp0A",1,-360.0f,360.0f);
    this->commonValue("gpp0A2:Default") = 0;
    dspinbox["gpp0A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle 2, град"),"gpp0A2",1,-360.0f,360.0f);
    checkbox["gppAS1"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gppAS1",false );
    this->commonValue("gpp1L:Default") = 0;
    dspinbox["gpp1L"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 left, см"),"gpp1L",0.1f,-100.0f,100.0f);
    this->commonValue("gpp1T:Default") = 0;
    dspinbox["gpp1T"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 top, см"),"gpp1T",0.1f,-100.0f,100.0f);
    this->commonValue("gpp1A:Default") = 0;
    dspinbox["gpp1A"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle, град"),"gpp1A",1,-360.0f,360.0f);
    this->commonValue("gpp1A2:Default") = 0;
    dspinbox["gpp1A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle 2, град"),"gpp1A2",1,-360.0f,360.0f);

    combobox["gppmcount"] = this->AddComboBoxProperty(trUtf8("Количество точек на полочке mirror"),items2,"gppmcount");
    checkbox["gppmAS"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gppmAS",false );
    this->commonValue("gppm0L:Default") = 0;
    dspinbox["gppm0L"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 left, см"),"gppm0L",0.1f,-100.0f,100.0f);
    this->commonValue("gppm0T:Default") = 0;
    dspinbox["gppm0T"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 top, см"),"gppm0T",0.1f,-100.0f,100.0f);
    this->commonValue("gppm0A:Default") = 0;
    dspinbox["gppm0A"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle, град"),"gppm0A",1,-360.0f,360.0f);
    this->commonValue("gppm0A2:Default") = 0;
    dspinbox["gppm0A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p0 angle, град 2"),"gppm0A2",1,-360.0f,360.0f);
    checkbox["gppmAS1"] = this->AddCheckBoxProperty( trUtf8( "<b>Сопряжение в точке уголом:</b>" ),"gppmAS1",false );
    this->commonValue("gppm1L:Default") = 0;
    dspinbox["gppm1L"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 left, см"),"gppm1L",0.1f,-100.0f,100.0f);
    this->commonValue("gppm1T:Default") = 0;
    dspinbox["gppm1T"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 top, см"),"gppm1T",0.1f,-100.0f,100.0f);
    this->commonValue("gppm1A:Default") = 0;
    dspinbox["gppm1A"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle, град"),"gppm1A",1,-360.0f,360.0f);
    this->commonValue("gppm1A2:Default") = 0;
    dspinbox["gppm1A2"] = this->AddDoubleSpinBoxProperty(trUtf8("p1 angle 2, град"),"gppm1A2",1,-360.0f,360.0f);


    //УСЛОВИЯ

    dspinbox["gppmAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false));
    dspinbox["gspAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["nat1"],true));
    dspinbox["gspmAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["nat2"],true));
    dspinbox["gppAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["nat1"],true));
    dspinbox["gppmAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["nat2"],true),Elasticas::OperationAnd);
    dspinbox["gppAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],2),Elasticas::OperationOr);
    dspinbox["gppmAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],2),Elasticas::OperationOr);
    dspinbox["gppmAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false));

    checkbox["gpsA"]->AddCondition( new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot );
    checkbox["gssA"]->AddCondition( new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot );

    dspinbox["gspmAA"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gssA"],true));
    dspinbox["gppmAA"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gpsA"],true));

    this->dspinbox["gsp0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gspAS"],true));
    this->dspinbox["gsp1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gspAS1"],true));

    this->dspinbox["gspm0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gspmAS"],true));
    this->dspinbox["gspm1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gspmAS1"],true));

    this->dspinbox["gpp0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gppAS"],true));
    this->dspinbox["gpp1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gppAS1"],true));

    this->dspinbox["gppm0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gppmAS"],true));
    this->dspinbox["gppm1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["gppmAS1"],true));

    this->checkbox["gspAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],0),Elasticas::OperationAndNot);
    this->dspinbox["gsp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],1));
    this->dspinbox["gsp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2),Elasticas::OperationOr);
    this->dspinbox["gsp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],1));
    this->dspinbox["gsp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2),Elasticas::OperationOr);
    this->dspinbox["gsp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],1));
    this->dspinbox["gsp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2),Elasticas::OperationOr);
    this->dspinbox["gsp0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],0),Elasticas::OperationAndNot);
    this->checkbox["gspAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2),Elasticas::OperationAnd);
    this->dspinbox["gsp1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2));
    this->dspinbox["gsp1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2));
    this->dspinbox["gsp1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2));
    this->dspinbox["gsp1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspcount"],2),Elasticas::OperationAnd);

    this->checkbox["gspmAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],0),Elasticas::OperationAndNot);
    this->checkbox["gspmAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2),Elasticas::OperationAnd);
    this->dspinbox["gspm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],1));
    this->dspinbox["gspm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gspm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],1));
    this->dspinbox["gspm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gspm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],1));
    this->dspinbox["gspm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gspm0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],0),Elasticas::OperationAndNot);
    this->dspinbox["gspm1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2));
    this->dspinbox["gspm1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2));
    this->dspinbox["gspm1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2));
    this->dspinbox["gspm1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gspmcount"],2),Elasticas::OperationAnd);

    this->checkbox["gppAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],0),Elasticas::OperationAndNot);
    this->checkbox["gppAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2),Elasticas::OperationAnd);
    this->dspinbox["gpp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],1));
    this->dspinbox["gpp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2),Elasticas::OperationOr);
    this->dspinbox["gpp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],1));
    this->dspinbox["gpp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2),Elasticas::OperationOr);
    this->dspinbox["gpp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],1));
    this->dspinbox["gpp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2),Elasticas::OperationOr);
    this->dspinbox["gpp0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],0),Elasticas::OperationAndNot);
    this->dspinbox["gpp1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2));
    this->dspinbox["gpp1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2));
    this->dspinbox["gpp1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2));
    this->dspinbox["gpp1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppcount"],2),Elasticas::OperationAnd);

    this->checkbox["gppmAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],0),Elasticas::OperationAndNot);
    this->checkbox["gppmAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2),Elasticas::OperationAnd);
    this->dspinbox["gppm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],1));
    this->dspinbox["gppm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gppm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],1));
    this->dspinbox["gppm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gppm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],1));
    this->dspinbox["gppm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2),Elasticas::OperationOr);
    this->dspinbox["gppm0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],0),Elasticas::OperationAndNot);
    this->dspinbox["gppm1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2));
    this->dspinbox["gppm1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2));
    this->dspinbox["gppm1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2));
    this->dspinbox["gppm1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["gppmcount"],2),Elasticas::OperationAnd);

    dspinbox["gspAA"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    combobox["gspcount"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    checkbox["gspAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    checkbox["gspAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);

    dspinbox["gsp0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gsp1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);

    dspinbox["gspmAA"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspmAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    combobox["gspmcount"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    checkbox["gspmAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    checkbox["gspmAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);
    dspinbox["gspm1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],0),Elasticas::OperationAndNot);

    dspinbox["gppAA"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    combobox["gppcount"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    checkbox["gppAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    checkbox["gppAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gpp1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);

    dspinbox["gppmAA"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    //dspinbox["gppmAB"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);

    combobox["gppmcount"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    checkbox["gppmAS"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    checkbox["gppmAS1"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm0L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm0T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm0A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm0A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm1L"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm1T"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm1A"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);
    dspinbox["gppm1A2"]->AddCondition(new Elasticas::ComboBoxCondition(combobox["Gchange"],1),Elasticas::OperationAndNot);

//ismirror
    checkbox["nat2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspmAA"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspmAB"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    combobox["gspmcount"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    checkbox["gspmAS"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm0L"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm0T"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm0A"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    checkbox["gspmAS1"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm1L"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm1T"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm1A"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gspm1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppmAA"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    combobox["gppmcount"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    checkbox["gppmAS"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm0L"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm0T"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm0A"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm0A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    checkbox["gppmAS1"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm1L"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm1T"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm1A"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
    dspinbox["gppm1A2"]->AddCondition(new Elasticas::CheckBoxCondition(checkbox["is_mirror"],false),Elasticas::OperationAnd);
}

