#ifndef FAKESKIRTDIALOG_H
#define FAKESKIRTDIALOG_H

#include "elcore/elbasicdialogs.h"
#include <QRadioButton>
#include <QGroupBox>
namespace Elasticas
{
class FakeSkirtDressDialog: public DockDialog
{
    bool is_sleeve;
    QGroupBox* groupbox;
    QList<QRadioButton*> buttons;
public:
    FakeSkirtDressDialog(const QString & classname,const QString & name=trUtf8("Форма изделия"),bool is_sleeve=false);
    virtual void apply();
};

class FakeAllowanceDialog: public PropertiesDialog
{
public:
    FakeAllowanceDialog(const QString & classname);
};
}
#endif // FAKESKIRTDIALOG_H
