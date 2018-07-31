#include "dressdialog.h"
//Диалог платья
namespace Elasticas
{

dressdialog::dressdialog():PropertiesDialog(trUtf8("Kleid"),"Kleid:")
{
   //!!!
   //Инициализация списков и чекбоксов
   //!!!

   //Текст
   up_siluet = new QLabel(trUtf8("Верхняя часть(лиф):"));
   down_siluet = new QLabel(trUtf8("Нижняя часть(юбка):"));
   checkbox11 = new QLabel(trUtf8("Способ создания объемной формы:"));
   checkbox12 = new QLabel(trUtf8("Способ создания объемной формы по верхнему основанию:"));
   checkbox13 = new QLabel(trUtf8("Способ создания объемной формы спереди:"));
   checkbox14 = new QLabel(trUtf8("Способ создания объемной формы в верхней части спереди:"));
   checkbox21 = new QLabel(trUtf8("Способ создания объемной формы по нижнему основанию:"));
   checkbox22 = new QLabel(trUtf8("Способ создания объемной формы сзади:"));
   checkbox23 = new QLabel(trUtf8("Способ создания объемной формы в верхней части сзади:"));
   checkbox31 = new QLabel(trUtf8("Способ создания объемной формы в нижней части спереди:"));
   checkbox41 = new QLabel(trUtf8("Способ создания объемной формы в нижней части сзади:"));
   //Списки
   cover_sleeves = this->AddComboBoxProperty(trUtf8("Покрой рукава:"),"Sleeves");
   cover_figure = this->AddComboBoxProperty(trUtf8("Покрой стана:"),"Figure");
   siluet = this->AddComboBoxProperty(trUtf8("Силуэт:"),"GeneralSiluet");


   this->properties_widget->layout()->addWidget(up_siluet);
   siluet_up = this->AddComboBoxProperty(trUtf8("Силуэт:"),"UpSiluet");
   this->properties_widget->layout()->addWidget(down_siluet);
   siluet_down = this->AddComboBoxProperty(trUtf8("Силуэт:"),"DownSiluet");

   volume_form = this->AddComboBoxProperty(trUtf8("Вид объемной формы:"),"VolumeForm");
   volume_form_way = this->AddComboBoxProperty(trUtf8("Способ создания объемной формы спереди и сзади:"),"VolumeFormWay");

   //Чекбоксы первая группа
   this->properties_widget->layout()->addWidget(checkbox11);
   this->properties_widget->layout()->addWidget(checkbox12);
   this->properties_widget->layout()->addWidget(checkbox13);
   this->properties_widget->layout()->addWidget(checkbox14);
   check_folds_first = this->AddCheckBoxProperty(trUtf8("Складки"),"FirstFolds",false);
   check_ship_first = this->AddCheckBoxProperty(trUtf8("Зашипы"),"FirstShip",false);
   check_gather_first = this->AddCheckBoxProperty(trUtf8("Сборка"),"FirstGather",false);
   check_tuck_first = this->AddCheckBoxProperty(trUtf8("Вытачка"),"FirstTuck",false);

   //Чекбоксы вторая группа
   this->properties_widget->layout()->addWidget(checkbox21);
   this->properties_widget->layout()->addWidget(checkbox22);
   this->properties_widget->layout()->addWidget(checkbox23);
   check_folds_second = this->AddCheckBoxProperty(trUtf8("Складки"),"SecondFolds",false);
   check_ship_second = this->AddCheckBoxProperty(trUtf8("Зашипы"),"SecondShip",false);
   check_gather_second = this->AddCheckBoxProperty(trUtf8("Сборка"),"SecondGather",false);
   check_tuck_second = this->AddCheckBoxProperty(trUtf8("Вытачка"),"SecondTuck",false);

   //Чекбоксы третья группа
   this->properties_widget->layout()->addWidget(checkbox31);
   check_folds_third = this->AddCheckBoxProperty(trUtf8("Складки"),"ThirdFolds",false);
   check_ship_third = this->AddCheckBoxProperty(trUtf8("Зашипы"),"ThirdShip",false);
   check_gather_third = this->AddCheckBoxProperty(trUtf8("Сборка"),"ThirdGather",false);
   check_tuck_third = this->AddCheckBoxProperty(trUtf8("Вытачка"),"ThirdTuck",false);

   //Чекбоксы четвертая группа
   this->properties_widget->layout()->addWidget(checkbox41);
   check_folds_fourth = this->AddCheckBoxProperty(trUtf8("Складки"),"FourthFolds",false);
   check_ship_fourth = this->AddCheckBoxProperty(trUtf8("Зашипы"),"FourthShip",false);
   check_gather_fourth = this->AddCheckBoxProperty(trUtf8("Сборка"),"FourthGather",false);
   check_tuck_fourth = this->AddCheckBoxProperty(trUtf8("Вытачка"),"FourthTuck",false);

   //!!!
   //Инициализация элементов списков
   //!!!

   //Инициализация Покроя рукава
   cover_sleeves->AddItem(trUtf8("втачной"));
   cover_sleeves->AddItem(trUtf8("рубашечный"));
   cover_sleeves->AddItem(trUtf8("реглан"));
   cover_sleeves->AddItem(trUtf8("цельнокроеный"));
   cover_sleeves->AddItem(trUtf8("комбинированный"));

   //Инициализация Покроя стана
   cover_figure->AddItem(trUtf8("без горизонтальных членений"));
   cover_figure->AddItem(trUtf8("отрезное по линии талии(условной линии талии"));

   //Инициализация Силуэта
   siluet->AddItem(trUtf8("прилегающий"));
   siluet->AddItem(trUtf8("полуприлегающий"));
   siluet->AddItem(trUtf8("прямой"));
   siluet->AddItem(trUtf8("трапеция"));
   siluet->AddItem(trUtf8("овальный"));
   siluet->AddItem(trUtf8("сложный(комбинированный)"));

   //Инициализация Верхней части Силуэта
   siluet_up->AddItem(trUtf8("прилегающий"));
   siluet_up->AddItem(trUtf8("полуприлегающий"));
   siluet_up->AddItem(trUtf8("прямой"));
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
   siluet->AddCondition(new ComboBoxCondition(cover_figure,0));

   //Покрой стана: отрезное по линии талии (все покрои рукава)
   siluet_up->AddCondition(new ComboBoxCondition(cover_figure,1));
   siluet_down->AddCondition(new ComboBoxCondition(cover_figure,1));

   //Силуэт: Сложный
   volume_form->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   volume_form->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);
   volume_form->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);
   volume_form_way->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   volume_form_way->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);
   volume_form_way->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);

   //Первая группа чекбоксов
   check_folds_first->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   check_ship_first->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   check_gather_first->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   check_tuck_first->AddCondition(new ComboBoxCondition(siluet,5),OperationOr);
   check_folds_first->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);
   check_ship_first->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);
   check_gather_first->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);
   check_tuck_first->AddCondition(new ComboBoxCondition(siluet_down,3),OperationOr);
   check_folds_first->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);
   check_ship_first->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);
   check_gather_first->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);
   check_tuck_first->AddCondition(new ComboBoxCondition(siluet_up,3),OperationOr);

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

   //Привязка сигналов к слотам
   QObject::connect(cover_sleeves,SIGNAL(onChanged()),this,SLOT(apply()));
   QObject::connect(siluet,SIGNAL(onChanged()),this,SLOT(apply()));
   QObject::connect(volume_form,SIGNAL(onChanged()),this,SLOT(apply()));
   QObject::connect(volume_form_way,SIGNAL(onChanged()),this,SLOT(apply()));
   QObject::connect(cover_figure,SIGNAL(onChanged()),this,SLOT(apply()));

   this->apply();


}

void dressdialog::apply()
{


    up_siluet->setVisible(cover_figure->IsCurrentSelection(1));
    down_siluet->setVisible( cover_figure->IsCurrentSelection(1));

    int form = volume_form->GetCurrentId();
    int way = volume_form_way->GetCurrentId();
   // bool cb = cover_sleeves->GetCurrentId() == 0 && siluet->GetCurrentId() == 3;
    bool cb = (siluet_up->GetWidget()->isVisible() && siluet_up->IsCurrentSelection(3)) || (siluet_down->GetWidget()->isVisible() && siluet_down->IsCurrentSelection(3) ) || (siluet->GetWidget()->isVisible() && siluet->IsCurrentSelection(5));

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
