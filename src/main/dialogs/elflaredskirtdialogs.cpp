#include "elflaredskirtdialogs.h"
namespace Elasticas
{
FlaredSkirtBKBasicPropertiesDialog::FlaredSkirtBKBasicPropertiesDialog():SkirtPropertiesDialog(trUtf8("Основные параметры"),"FlaredSkirt:")
{
    this->InitSkirtBKBasicProperties();
}
//_______________________________________________________________________-
FlaredSkirtBKBasicSkewsPropertiesDialog::FlaredSkirtBKBasicSkewsPropertiesDialog():SkirtPropertiesDialog(trUtf8("Основные конструктивные швы"),"FlaredSkirt:")
{
    this->InitSkirtDressBKBasicSewsProperties();
}
//_______________________________________________________________________-
FlaredSkirtIMKBeltPropertiesDialog::FlaredSkirtIMKBeltPropertiesDialog():SkirtPropertiesDialog(trUtf8("Пояс"),"FlaredSkirt:")
{
    this->InitSkirtIMKBeltProperties();
}
//______________________________________________________________________
FlaredSkirtIMKClaspPropertiesDialog::FlaredSkirtIMKClaspPropertiesDialog():SkirtPropertiesDialog(trUtf8("Застёжка"),"FlaredSkirt:")
{
    this->InitSkirtIMKClaspProperties();
}
//_______________________________________________________________________
FlaredSkirtMKGarmentPropsDialog::FlaredSkirtMKGarmentPropsDialog(): SkirtPropertiesDialog(trUtf8("Основные"),"FlaredSkirt:")
{
    const CommonData & vars=Core::Instance()->CommonVariables();
    ComboBoxProperty* cbp1;
    DoubleSpinBoxProperty* dbp1;
    cbp1=this->AddComboBoxProperty(trUtf8("Величина расклешения"),"KrType");
    cbp1->AddItem(trUtf8("Ширина изделия по линии низа"));
    cbp1->AddItem(trUtf8("Коэффициент расклешения"));

    dbp1=this->AddDoubleSpinBoxProperty(trUtf8("Значение"),"Snr");
    dbp1->AddCondition(new ComboBoxCondition(cbp1,0));

    dbp1=this->AddDoubleSpinBoxProperty(trUtf8("Значение"),"Kr",0.01f,1.0f,5.0f);
    dbp1->AddCondition(new ComboBoxCondition(cbp1,1));

    QFrame* frame;
    this->properties_widget->layout()->addWidget(frame=new QFrame);
    frame->setFrameShape(QFrame::HLine);

    cbp1=this->AddComboBoxProperty(trUtf8("Сборка по талии"),"KsType");
    cbp1->AddItem(trUtf8("Ширина конструкции по линии талии"));
    cbp1->AddItem(trUtf8("Коэффициент сборки по талии"));

    dbp1=this->AddDoubleSpinBoxProperty(trUtf8("Значение"),"St");
    dbp1->AddCondition(new ComboBoxCondition(cbp1,0));

    dbp1=this->AddDoubleSpinBoxProperty(trUtf8("Значение"),"Ks");
    dbp1->AddCondition(new ComboBoxCondition(cbp1,1));


    this->properties_widget->layout()->addWidget(frame=new QFrame);
    frame->setFrameShape(QFrame::HLine);

    cbp1=this->AddComboBoxProperty(trUtf8("Тип ткани"),"MaterialType");
    cbp1->AddItem(trUtf8("Однотонная"));
    cbp1->AddItem(trUtf8("С геометрическим рисунком"));
}
}
