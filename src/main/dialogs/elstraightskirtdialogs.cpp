#include "elstraightskirtdialogs.h"
namespace Elasticas
{
    StraightSkirtBKBasicPropertiesDialog::StraightSkirtBKBasicPropertiesDialog(const QString & class_name):SkirtPropertiesDialog(trUtf8("Основные параметры"),class_name)
    {
        this->InitSkirtBKBasicProperties();
    }
//_______________________________________________________________________-
    StraightSkirtBKBasicSkewsPropertiesDialog::StraightSkirtBKBasicSkewsPropertiesDialog(const QString & class_name):SkirtPropertiesDialog(trUtf8("Основные конструктивные швы"),class_name)
    {
        this->InitSkirtDressBKBasicSewsProperties();
    }
//_______________________________________________________________________
     StraightSkirtIMKBeltPropertiesDialog::StraightSkirtIMKBeltPropertiesDialog(const QString & class_name):SkirtPropertiesDialog(trUtf8("Пояс"),class_name)
     {
         this->InitSkirtIMKBeltProperties();
     }
  //______________________________________________________________________
     StraightSkirtIMKClaspPropertiesDialog::StraightSkirtIMKClaspPropertiesDialog(const QString & class_name):SkirtPropertiesDialog(trUtf8("Застёжка"),class_name)
     {
         this->InitSkirtIMKClaspProperties();
     }
//_______________________________________________________________________
     SkirtDressIMKNarrowingPropertiesDialog::SkirtDressIMKNarrowingPropertiesDialog(const QString & classname):PropertiesDialog(trUtf8("Заужение"),classname)
     {
         CheckBoxProperty* cbp1;
         AbstractProperty* p1;

         this->commonValue("Narrow:Default")=false; // Местоположение заужения
         this->commonValue("A3:Default")=1.0f; // Заужение по боковому шву
         this->commonValue("A3:Min")=-3.0f;
         this->commonValue("A3:Max")=3.0f;
         this->commonValue("A4:Default")=10.0f; // Уровень заужения от низа
         this->commonValue("A4:Min")=-10.0f;
         this->commonValue("A4:Max")=10.0f;

         cbp1=this->AddCheckBoxProperty(trUtf8("Заужение"),"Narrow");
         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по боковому шву 1 (см)"),"A3",0.1,-100,100);
         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по боковому шву 2 (см)"),"A3_",0.1,-100,100);
         //p1->AddCondition(new CheckBoxCondition(cbp1,true));

         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по переднему шву 1 (см)"),"A5",0.1,-100,100);
         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по переднему шву 2 (см)"),"A5_",0.1,-100,100);
         //p1->AddCondition(new CheckBoxCondition(cbp1,true));

         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по заднему шву 1 (см)"),"A6",0.1,-100,100);
         p1=this->AddDoubleSpinBoxProperty(trUtf8("Заужение по заднему шву 2 (см)"),"A6_",0.1,-100,100);
         //p1->AddCondition(new CheckBoxCondition(cbp1,true));

         p1=this->AddDoubleSpinBoxProperty(trUtf8("Уровень заужения от низа (см)"),"A4");
         //p1->AddCondition(new CheckBoxCondition(cbp1,true),OperationAnd,false);
         //p1->AddCondition(new CheckBoxCondition((CheckBoxProperty*)global_var_names_to_properties[this->dialogClass()->className()]["VB"],true));

     }
//________________________________________________________________________
     StraightSkirtIMKVentPropertiesDialog::StraightSkirtIMKVentPropertiesDialog(const QString & class_name):SkirtPropertiesDialog(trUtf8("Разрезы и шлицы"),class_name)
     {
         this->InitStraightSkirtDressIMKVentProperties();
     }

 }
