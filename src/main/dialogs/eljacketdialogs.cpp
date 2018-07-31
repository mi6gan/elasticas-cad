#include "eljacketdialogs.h"
namespace Elasticas
{
JacketBKBasicDialog::JacketBKBasicDialog():PropertiesDialog(trUtf8("Основные"),"Jacket:")
{
    this->InitTopGarmentsBKProperties();
}

void JacketBKBasicDialog::apply()
{
    switch(this->silhouette_cbp->GetCurrentId())
    {
        case 0: break;
        case 1: break;
        case 2: break;
    }
    PropertiesDialog::apply();
}
//___________________________________________
JacketVentDialog::JacketVentDialog():PropertiesDialog(trUtf8("Вытачки и шлицы"),"Jacket:")
{
    this->AddSpinBoxProperty(trUtf8("Количество шлиц"),"",1,1,2);
    this->AddDoubleSpinBoxProperty(trUtf8("Ширина шлицы"),"",0.1,0,10);
    this->AddDoubleSpinBoxProperty(trUtf8("Высота шлицы"),"",1,0,10);
    this->AddDoubleSpinBoxProperty(trUtf8("Раствор передней вытачки"),"",0.01,0,1.0);
}
//__________________________________________
JacketPocketsDialog::JacketPocketsDialog():PropertiesDialog(trUtf8("Карманы"),"Jacket:")
{
    QString pockets[]={trUtf8("Накладной"),trUtf8("Прорезной"),NULL};
    this->AddComboBoxProperty(trUtf8("Вид"),pockets);
    this->AddCheckBoxProperty(trUtf8("С листочкой"),"",false);
    this->AddCheckBoxProperty(trUtf8("С двумя обтачками"),"",false);
    this->AddCheckBoxProperty(trUtf8("С клапаном"),"",true);
    this->AddDoubleSpinBoxProperty(trUtf8("Длина клапана"),"",0.01,0,1);
    this->AddDoubleSpinBoxProperty(trUtf8("Ширина клапана"),"",0.01,0,1);
    this->AddDoubleSpinBoxProperty(trUtf8("Степень закругления клапана"),"",0.01,0,1);
}
//_____________________________
JacketCollarDialog::JacketCollarDialog():PropertiesDialog(trUtf8("Воротник"),"Jacket:")
{
    this->AddDoubleSpinBoxProperty(trUtf8("Высота стойки"),"",0.01,0,1);
    this->AddDoubleSpinBoxProperty(trUtf8("Ширина отлёта"),"",0.01,0,1);
    this->AddDoubleSpinBoxProperty(trUtf8("Угол отлёта"),"",0.01,0,1);
    this->AddDoubleSpinBoxProperty(trUtf8("Угол лацкана"),"",0.01,0,1);
}
//__________________________________________
JacketMKFormDialog::JacketMKFormDialog():PropertiesDialog(trUtf8("Рельефы и вытачки"),"Jacket:")
{    
    this->InitTopGarmentsMKProperties();
}
//__________________________________________
JacketMKNeckDialog::JacketMKNeckDialog():PropertiesDialog(trUtf8("Горловина"),"Jacket:")
{
    this->InitTopGarmentsNeckProperties();
}
}
