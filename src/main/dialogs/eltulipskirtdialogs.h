#ifndef ELTULIPSKIRTDIALOGS_H
#define ELTULIPSKIRTDIALOGS_H
#include "elskirtdialogs.h"
#include <QColorDialog>
namespace Elasticas
{

class TulipSkirtBasicDialog: public SkirtPropertiesDialog
{
    Q_OBJECT
    ComboBoxProperty* length_name_cb,*length_type_cb;
    DoubleSpinBoxProperty* length_dsb;
    void ComputeLength();
public:
    TulipSkirtBasicDialog();
    virtual void apply();
private slots:
    void onChange();
};

class TulipSkirtDilutionDialog: public SkirtPropertiesDialog
{
    ComboBoxProperty* krType_cbp;
    DoubleSpinBoxProperty* kr_dbp, * kr18_dbp, * kr_abs_dbp;
public:
    TulipSkirtDilutionDialog();
    virtual void apply();
};

class TulipSkirtColorButton:public QWidget
{
    Q_OBJECT
    QPushButton* button;
    QColor color;
    QColorDialog* color_dialog;
public:
    TulipSkirtColorButton();
    const QColor & Color();
private slots:
    void SelectColor(const QColor & color);

};

class TulipSkirtMaterialDialog: public SkirtPropertiesDialog
{
    TulipSkirtColorButton* color_button;
public:
    TulipSkirtMaterialDialog();
    virtual void apply();
};

class TulipSkirtBKBasicSkewsPropertiesDialog: public SkirtPropertiesDialog //БК прямой юбки, основные конструктивные швы
{
public:
    TulipSkirtBKBasicSkewsPropertiesDialog();
};

class TulipSkirtIMKBeltPropertiesDialog: public SkirtPropertiesDialog //ИМК прямой юбки, пояс
{
public:
    TulipSkirtIMKBeltPropertiesDialog();
};

}
#endif // ELTULIPSKIRTDIALOGS_H
