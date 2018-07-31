#ifndef C2DDRESSTABLEDIALOG_H
#define C2DDRESSTABLEDIALOG_H

#include <QTextCodec>

#include <QTableWidget>
#include <QHeaderView>
#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"
/*class DressRP2:public Elasticas::TableRPDialog
{
       public:
           DressRP2();
};*/
class C2DDressTableDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DDressTableDialog(const QString            & name,
                        const QString            & prefix,
                        const QString            & tab,
                        QPair< QString, double >   units,
                        QWidget                  * parent );

public slots:
    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:
    QList< QList< double > > defaults();

private:
    void addHorizontalItems( QVariantList * list );
    void requiredVariables();
    QList< double > rmain, rprib;
    QTableWidget * table;
    QDoubleSpinBox * razmprib[ 21 ];
    QDoubleSpinBox * razmmain[ 21 ];
};

#endif // C2DDRESSTABLEDIALOG_H

