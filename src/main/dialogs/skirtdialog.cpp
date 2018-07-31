#include "skirtdialog.h"
#include<QMessageBox>
//Диалог юбки
namespace Elasticas
{



skirtdialog::skirtdialog():PropertiesDialog(trUtf8("Юбка"),"Skirt:")
{

    //!!!
    //Инициализация списков и чекбоксов
    //!!!

    //Текст
    up_siluet = new QLabel(trUtf8("Верхняя часть:"));
    down_siluet = new QLabel(trUtf8("Нижняя часть:"));
    checkbox11 = new QLabel(trUtf8("Способ создания объемной формы:"));
    checkbox12 = new QLabel(trUtf8("Способ создания объемной формы по верхнему основанию:"));
    checkbox13 = new QLabel(trUtf8("Способ создания объемной формы спереди:"));
    checkbox14 = new QLabel(trUtf8("Способ создания объемной формы по верхнему основанию спереди:"));
    checkbox21 = new QLabel(trUtf8("Способ создания объемной формы по нижнему основанию:"));
    checkbox22 = new QLabel(trUtf8("Способ создания объемной формы сзади:"));
    checkbox23 = new QLabel(trUtf8("Способ создания объемной формы по верхнему основанию сзади:"));
    checkbox31 = new QLabel(trUtf8("Способ создания объемной формы по нижнему основанию спереди:"));
    checkbox41 = new QLabel(trUtf8("Способ создания объемной формы по нижнему основанию сзади:"));

    //Списки
    cover_sleeves = this->AddComboBoxProperty(trUtf8("Покрой:"),"Sleeves:");
    siluet = this->AddComboBoxProperty(trUtf8("Силуэт:"),"GeneralSiluet:");



    this->properties_widget->layout()->addWidget(up_siluet);
    siluet_up = this->AddComboBoxProperty(trUtf8("Силуэт:"),"UpSiluet:");
    this->properties_widget->layout()->addWidget(down_siluet);
    siluet_down = this->AddComboBoxProperty(trUtf8("Силуэт:"),"DownSiluet:");

    volume_form = this->AddComboBoxProperty(trUtf8("Вид объемной формы:"),"VolumeForm:");
    volume_form_way = this->AddComboBoxProperty(trUtf8("Способ создания объемной формы спереди и сзади:"),"VolumeFormWay:");

    //Чекбоксы первая группа
    this->properties_widget->layout()->addWidget(checkbox11);
    this->properties_widget->layout()->addWidget(checkbox12);
    this->properties_widget->layout()->addWidget(checkbox13);
    this->properties_widget->layout()->addWidget(checkbox14);
    check_folds_first = this->AddCheckBoxProperty(trUtf8("Складки"),"FirstFolds:",false);
    check_ship_first = this->AddCheckBoxProperty(trUtf8("Зашипы"),"FirstShip:",false);
    check_gather_first = this->AddCheckBoxProperty(trUtf8("Сборка"),"FirstGather:",false);
    check_tuck_first = this->AddCheckBoxProperty(trUtf8("Вытачки"),"FirstTuck:",false);

    //Чекбоксы вторая группа
    this->properties_widget->layout()->addWidget(checkbox21);
    this->properties_widget->layout()->addWidget(checkbox22);
    this->properties_widget->layout()->addWidget(checkbox23);
    check_folds_second = this->AddCheckBoxProperty(trUtf8("Складки"),"SecondFolds:",false);
    check_ship_second = this->AddCheckBoxProperty(trUtf8("Зашипы"),"SecondShip:",false);
    check_gather_second = this->AddCheckBoxProperty(trUtf8("Сборка"),"SecondGather:",false);
    check_tuck_second = this->AddCheckBoxProperty(trUtf8("Вытачки"),"SecondTuck:",false);

    //Чекбоксы третья группа
    this->properties_widget->layout()->addWidget(checkbox31);
    check_folds_third = this->AddCheckBoxProperty(trUtf8("Складки"),"ThirdFolds:",false);
    check_ship_third = this->AddCheckBoxProperty(trUtf8("Зашипы"),"ThirdShip:",false);
    check_gather_third = this->AddCheckBoxProperty(trUtf8("Сборка"),"ThirdGather:",false);
    check_tuck_third = this->AddCheckBoxProperty(trUtf8("Вытачки"),"ThirdTuck:",false);

    //Чекбоксы четвертая группа
    this->properties_widget->layout()->addWidget(checkbox41);
    check_folds_fourth = this->AddCheckBoxProperty(trUtf8("Складки"),"FourthFolds:",false);
    check_ship_fourth = this->AddCheckBoxProperty(trUtf8("Зашипы"),"FourthShip:",false);
    check_gather_fourth = this->AddCheckBoxProperty(trUtf8("Сборка"),"FourthGather:",false);
    check_tuck_fourth = this->AddCheckBoxProperty(trUtf8("Вытачки"),"FourthTuck:",false);

    //!!!
    //Инициализация элементов списков
    //!!!

    //Инициализация Покроя рукава
    cover_sleeves->AddItem(trUtf8("без членения по линии бёдер"));
    cover_sleeves->AddItem(trUtf8("отрезное по линии бёдер"));

    //Инициализация Силуэта
    siluet->AddItem(trUtf8("прилегающий"));
    siluet->AddItem(trUtf8("прямой"));
    siluet->AddItem(trUtf8("трапеция"));
    siluet->AddItem(trUtf8("сложный(комбинированный)"));

    //Инициализация Верхней части Силуэта
    siluet_up->AddItem(trUtf8("прилегающий"));
    siluet_up->AddItem(trUtf8("трапеция"));
    siluet_up->AddItem(trUtf8("сложный(объёмный)"));

    //Инициализация Нижней части Силуэлта
    siluet_down->AddItem(trUtf8("прилегающий"));
    siluet_down->AddItem(trUtf8("прямой"));
    siluet_down->AddItem(trUtf8("трапеция"));
    siluet_down->AddItem(trUtf8("сложный(объёмный)"));

    //Инициалзиация Вида объемной формы
    volume_form->AddItem(trUtf8("объемная по верхнему основанию"));
    volume_form->AddItem(trUtf8("объемная по нижнему основанию"));
    volume_form->AddItem(trUtf8("объемная по верхнему и нижнему основанию"));

    //Инициализация Способа создания объемной формы спереди и сзади
    volume_form_way->AddItem(trUtf8("одинаковый"));
    volume_form_way->AddItem(trUtf8("разный"));

    //!!!
    //Привязывание событий
    //!!!


    //Покрой стана: без членения (все покрои рукава)
    siluet->AddCondition(new ComboBoxCondition(cover_sleeves,0));

    //Покрой стана: отрезное по линии талии (все покрои рукава)
    siluet_up->AddCondition(new ComboBoxCondition(cover_sleeves,1));
    siluet_down->AddCondition(new ComboBoxCondition(cover_sleeves,1));

    //Силуэт: Сложный
    volume_form->AddCondition(new ComboBoxCondition(siluet,3));
    volume_form_way->AddCondition(new ComboBoxCondition(siluet,3));

    //Первая группа чекбоксов
    check_folds_first->AddCondition(new ComboBoxCondition(siluet,3));
    check_ship_first->AddCondition(new ComboBoxCondition(siluet,3));
    check_gather_first->AddCondition(new ComboBoxCondition(siluet,3));
    check_tuck_first->AddCondition(new ComboBoxCondition(siluet,3));

    //Вторая группа чекбоксов
    check_folds_second->AddCondition(new ComboBoxCondition(volume_form,2),OperationOr);
    check_ship_second->AddCondition(new ComboBoxCondition(volume_form,2),OperationOr);
    check_gather_second->AddCondition(new ComboBoxCondition(volume_form,2),OperationOr);
    check_tuck_second->AddCondition(new ComboBoxCondition(volume_form,2),OperationOr);
    check_folds_second->AddCondition(new ComboBoxCondition(volume_form_way,1),OperationOr);
    check_ship_second->AddCondition(new ComboBoxCondition(volume_form_way,1),OperationOr);
    check_gather_second->AddCondition(new ComboBoxCondition(volume_form_way,1),OperationOr);
    check_tuck_second->AddCondition(new ComboBoxCondition(volume_form_way,1),OperationOr);

    //Третья и четвертая группа чекбоксов
    check_folds_third->AddCondition(new ComboBoxCondition(volume_form,2));
    check_ship_third->AddCondition(new ComboBoxCondition(volume_form,2));
    check_gather_third->AddCondition(new ComboBoxCondition(volume_form,2));
    check_tuck_third->AddCondition(new ComboBoxCondition(volume_form,2));
    check_folds_third->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_ship_third->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_gather_third->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_tuck_third->AddCondition(new ComboBoxCondition(volume_form_way,1));

    check_folds_fourth->AddCondition(new ComboBoxCondition(volume_form,2));
    check_ship_fourth->AddCondition(new ComboBoxCondition(volume_form,2));
    check_gather_fourth->AddCondition(new ComboBoxCondition(volume_form,2));
    check_tuck_fourth->AddCondition(new ComboBoxCondition(volume_form,2));
    check_folds_fourth->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_ship_fourth->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_gather_fourth->AddCondition(new ComboBoxCondition(volume_form_way,1));
    check_tuck_fourth->AddCondition(new ComboBoxCondition(volume_form_way,1));

    //Привязывание сигналов к сигналам
    QObject::connect(cover_sleeves,SIGNAL(onChanged()),this,SLOT(apply()));
    QObject::connect(siluet,SIGNAL(onChanged()),this,SLOT(apply()));
    QObject::connect(volume_form,SIGNAL(onChanged()),this,SLOT(apply()));
    QObject::connect(volume_form_way,SIGNAL(onChanged()),this,SLOT(apply()));

    this->apply();


 }

void skirtdialog::apply()
{


    up_siluet->setVisible(siluet_up->GetWidget()->isVisible());
    down_siluet->setVisible( siluet_up->GetWidget()->isVisible());

    int form = volume_form->GetCurrentId();
    int way = volume_form_way->GetCurrentId();
    bool cb = cover_sleeves->GetCurrentId() == 0 && siluet->GetCurrentId() == 3;

    checkbox11->setVisible(cb && way == 0 && ( form == 0 || form == 1 ));

    checkbox12->setVisible(cb && way == 0 &&  form == 2 );
    checkbox21->setVisible(cb && way == 0 &&  form == 2 );

    checkbox13->setVisible(cb && way == 1 && ( form == 0 || form == 1 ));
    checkbox22->setVisible(cb && way == 1 && (form == 0 || form == 1 ));

    checkbox14->setVisible(cb && way == 1 && form == 2);
    checkbox23->setVisible(cb && way == 1 && form == 2);
    checkbox31->setVisible(cb && way == 1 && form == 2);
    checkbox41->setVisible(cb && way == 1 && form == 2);

    PropertiesDialog::apply();
}


}


