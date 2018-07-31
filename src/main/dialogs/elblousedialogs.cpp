#include "elblousedialogs.h"
namespace Elasticas
{
BlouseBKBasicDialog::BlouseBKBasicDialog(const QString & class_name):PropertiesDialog(trUtf8("Основные"),class_name)
{
    this->InitTopGarmentsBKProperties();
}

BlouseMKFormDialog::BlouseMKFormDialog(const QString & class_name):PropertiesDialog(trUtf8("Рельефы и вытачки"),class_name)
{
    this->InitTopGarmentsMKProperties();
}

BlouseMKNeckDialog::BlouseMKNeckDialog(const QString & class_name):PropertiesDialog(trUtf8("Горловина"),class_name)
{
    this->InitTopGarmentsNeckProperties();
}
}
