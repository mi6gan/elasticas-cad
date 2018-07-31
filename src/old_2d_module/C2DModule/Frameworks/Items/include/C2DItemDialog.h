#ifndef C2DITEMDIALOG_H
#define C2DITEMDIALOG_H

#include <QHash>
#include <QDebug>
#include <QLabel>
#include <QVariant>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QTextCodec>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QGraphicsView>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>

#include "C2DDialog.h"
#include "C2DExchange.h"

class C2DItemDialog : public C2DDialog, public C2DExchange
{

    Q_OBJECT

public:

    C2DItemDialog( const QString            & name,
                   const QString            & prefix,
                   const QString            & tab,
                   QPair< QString, double >   units,
                   QWidget                  * parent );

    ~C2DItemDialog()  {  delete this->dialog_grid;  }

    inline       void      startup()  {  this->Reset(); this->Apply();      }
    inline const QString & prefix()   {  return this->dialog_prefix;        }
    inline const double  & modifier() {  return this->dialog_units.second;  }

signals:

    void UpdateNeeded();
    void transmitData( QHash< QString, QVariant > data );

public slots:
    void kernelBusy( bool busy );

protected slots:

    void Accept();
    void Cancel();
    virtual void Apply()  = 0;
    virtual void Reject() = 0;
    virtual void Reset()  = 0;

protected:

    virtual QList< QList< double > > defaults() = 0;

    QList< QList< double > > user;
    QHash< QString, QVariant > values;

    QDialogButtonBox * top_dialog_button_box;
    QDialogButtonBox * bottom_dialog_button_box;

private:

    QString                           dialog_prefix;
    QGridLayout                     * dialog_grid;
    QPair< QString, double >          dialog_units;
    QHash< QString, QVariant >        dialog_hash;
    QHash< QString, C2DVariable * >   variables;

};

#endif //C2DITEMDIALOG_H
