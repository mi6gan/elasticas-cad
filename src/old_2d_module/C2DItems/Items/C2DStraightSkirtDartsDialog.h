#ifndef C2DSTRAIGHTSKIRTDARTSDIALOG_H
#define C2DSTRAIGHTSKIRTDARTSDIALOG_H

#include <QLabel>
#include <QSpinBox>
#include <QVariant>
#include <QGroupBox>
#include <QGenericMatrix>

#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DStraightSkirtDartsDialog : public C2DItemDialog
{
    Q_OBJECT
public:
    C2DStraightSkirtDartsDialog( const QString & name, const QString & prefix, QPair< QString, double > units,
                                 QGraphicsScene * scene, QObject * parent );
    ~C2DStraightSkirtDartsDialog();

protected slots:
    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:
    QList< QList< double > > defaults();

private slots:
    void valueChanged();

private:
    QSpinBox * spins[ 3 ];
    int front, side, back;

    QHash< int, QPair< QGroupBox *, QList< QDoubleSpinBox * > > > sets;

};

#endif //C2DSTRAIGHTSKIRTDARTSDIALOG_H
