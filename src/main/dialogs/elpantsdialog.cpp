#include "elpantsdialog.h"
namespace Elasticas
{
     PantsBKBasicPropertiesDialog::PantsBKBasicPropertiesDialog():PropertiesDialog(trUtf8("Основные параметры"),"Pants:")
     {
         const CommonData & vars=Core::Instance()->commonVariables();
         this->commonValue("Length:Default")=vars["Dummy:T26"]; // Заужение по боковому шву
         this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к полуобхвату талии (см)"),"P18",0.1f,-3.0f,10.0f);
         this->AddDoubleSpinBoxProperty(trUtf8("Прибавка к полуобхвату бёдер (см)"),"P19",0.1f,-3.0f,10.0f);
         this->AddDoubleSpinBoxProperty(trUtf8("Длина брюк (см)"),"Length",0.5f,0,300);
         this->InitSkirtDressPT();
     }

//_______________________________________________________________________
     PantsIMKBeltPropertiesDialog::PantsIMKBeltPropertiesDialog():SkirtPropertiesDialog(trUtf8("Пояс"),"Pants:")
     {
         this->InitSkirtIMKBeltProperties();
     }
  //______________________________________________________________________
     PantsIMKClaspPropertiesDialog::PantsIMKClaspPropertiesDialog():SkirtPropertiesDialog(trUtf8("Застёжка"),"Pants:")
     {
         this->InitSkirtIMKClaspProperties(false);
     }
}
