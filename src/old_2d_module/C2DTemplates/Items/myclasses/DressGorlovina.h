
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressGorlovina: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    DressGorlovina();
    void setT31( double d );
    Elasticas::CheckBoxProperty* getcheckboxpropertypointer( QString s );
    void setDSpinminmax( QString s,double min=0,double max=0 );
    void setSpinValue( QString s , double val);
private:
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
};

