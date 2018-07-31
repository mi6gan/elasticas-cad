#ifndef DRESSDIALOG_H
#define DRESSDIALOG_H
#include "elcore/elbasicdialogs.h"
//Диалог платья
namespace Elasticas
{

class dressdialog : public  PropertiesDialog
{
    QLabel* up_siluet,*down_siluet,*checkbox11,*checkbox12,*checkbox13,*checkbox14,
    *checkbox21,*checkbox22,*checkbox23,*checkbox31,*checkbox41;
    ComboBoxProperty* cover_sleeves,*cover_figure, *siluet,*siluet_up,*siluet_down,*volume_form,
    *volume_form_way;
    CheckBoxProperty* check_folds_first,*check_ship_first,*check_gather_first,*check_tuck_first,
    *check_folds_second,*check_ship_second,*check_gather_second,*check_tuck_second,
    *check_folds_third,*check_ship_third,*check_gather_third,*check_tuck_third,*check_folds_fourth,
    *check_ship_fourth,*check_gather_fourth,*check_tuck_fourth;
public:
    dressdialog();
public slots:
    void apply();
};

}
#endif // DRESSDIALOG_H
