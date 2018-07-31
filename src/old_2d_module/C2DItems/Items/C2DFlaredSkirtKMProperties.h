#ifndef C2DFLAREDSKIRTKMPROPERTIES_H
#define C2DFLAREDSKIRTKMPROPERTIES_H

#include "../../C2DModule/Frameworks/Items/include/C2DItemDialog.h"

class C2DFlaredSkirtKMProperties : public C2DItemDialog
{

    Q_OBJECT

public:

    C2DFlaredSkirtKMProperties( const QString            & name,
                                const QString            & prefix,
                                const QString            & tab,
                                QPair< QString, double >   units,
                                QWidget                  * parent );

    ~C2DFlaredSkirtKMProperties()  {  }

protected slots:

    virtual void Apply();
    virtual void Reject();
    virtual void Reset();

protected:

    virtual QList< QList< double > > defaults();

private slots:

    void checkVariant();

private:

    void requiredVariables();

    QList< QLineEdit * > input;

};

#endif //C2DFLAREDSKIRTKMPROPERTIES_H
