#ifndef C2DPANTSDIALOG_H
#define C2DPANTSDIALOG_H

#include <QTextCodec>


#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DPantsDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DPantsDialog( const QString            & name,
                    const QString            & prefix,
                    const QString            & tab,
                    QPair< QString, double >   units,
                    QWidget                  * parent  );

protected slots:
    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:
    QList< QList< double > > defaults();

private:
    void requiredVariables();

    QDoubleSpinBox * pantsspin[ 5 ];
    QList< QVariant > pantsdialog_list;
    QComboBox * pantscombo;

};

#endif // C2DPANTSDIALOG_H

