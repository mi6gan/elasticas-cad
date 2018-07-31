#ifndef C2DSLEEVEDIALOG_H
#define C2DSLEEVEDIALOG_H

#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DSleeveDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DSleeveDialog( const QString            & name,
                     const QString            & prefix,
                     const QString            & tab,
                     QPair< QString, double >   units,
                     QWidget                  * parent );

protected slots:
    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:
    QList< QList< double > > defaults();

private:
    void requiredVariables();

    QString edit_str;
    QList< QLineEdit * > returns;
    QList< QRadioButton * >  radio_returns;
    QList< QComboBox * > combobox_returns;
    QList< QVariant > dialog_list;
    QDoubleSpinBox * shovpos;
private slots:
    void typeselect( int cindex );
    void pposchange();
};

#endif // C2DSLEEVEDIALOG_H
