#ifndef C2DSTRAIGHTSKIRTDIALOG_H
#define C2DSTRAIGHTSKIRTDIALOG_H

#include <QLabel>
#include <QSpinBox>
#include <QVariant>
#include <QGroupBox>
#include <QGenericMatrix>

#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DStraightSkirtDialog : public C2DItemDialog
{

    Q_OBJECT

public:

    C2DStraightSkirtDialog( const QString            & name,
                            const QString            & prefix,
                            const QString            & tab,
                            QPair< QString, double >   units,
                            QWidget                  * parent );

    ~C2DStraightSkirtDialog();

protected slots:
    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:
    QList< QList< double > > defaults();

private slots:
    void valueChanged();

private:
    void requiredVariables();

    QSpinBox * spins[ 3 ];
    int front, side, back;

    QHash< int, QPair< QGroupBox *, QList< QDoubleSpinBox * > > > sets;

};

#endif //C2DSTRAIGHTSKIRTDIALOG_H
