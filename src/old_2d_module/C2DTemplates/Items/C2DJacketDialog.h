#ifndef C2DJACKETDIALOG_H
#define C2DJACKETDIALOG_H

#include <QTextCodec>
#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DJacketDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DJacketDialog( const QString            & name,
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

    QDoubleSpinBox * jacketspin[ 14 ];
    QList< QVariant > jacketdialog_list;

};

#endif // C2DJACKETDIALOG_H

