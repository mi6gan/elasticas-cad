#ifndef C2DBLOUSEDIALOG_H
#define C2DBLOUSEDIALOG_H

#include <QTextCodec>
#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DBlouseDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DBlouseDialog( const QString            & name,
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

    QDoubleSpinBox * blousespin[ 11 ];
    QList< QVariant > blousedialog_list;

};

#endif // C2DBLOUSEDIALOG_H

