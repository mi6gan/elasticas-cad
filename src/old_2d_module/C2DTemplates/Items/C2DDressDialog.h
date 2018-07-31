#ifndef C2DDRESSDIALOG_H
#define C2DDRESSDIALOG_H

#include <QTextCodec>
#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"
//#include <QTabBar>


class C2DDressDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DDressDialog( const QString            & name,
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
    void requiredVariables();

    QDoubleSpinBox * dressspin[ 10 ], * dressspin2[4];
    QDoubleSpinBox * middleline[ 5 ];
    QList< QVariant > dressdialog_list;
    QTabWidget * tabs;
    QWidget * tabwidget[5];
    QGridLayout * tablayout[5];

    //QComboBox * Dresscombo;

};

#endif // C2DDRESSDIALOG_H

