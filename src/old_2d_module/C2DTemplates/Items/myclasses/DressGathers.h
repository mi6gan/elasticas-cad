#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressGathers: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    DressGathers();
    void SetDspinVal( QString name,double d );
    double GetDspinVal( QString name );
    void SetSpinVal( QString name,double d );
    void SetDspinMinMax( QString name,double min,double max );
    void SetDspinText( QString name, QString txt );
    void showlabel( QString name, bool visible );
    void labelchangetext( QString name, QString s );
private:
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
    QHash< QString, QLabel* > labels;
};

