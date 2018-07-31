//#include "myclasses\C2DPath.h"
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressEquidistant: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    DressEquidistant();
    void SetDspinVal( QString name,double d );
    void SetDspinMinMax( QString name,double min,double max );
    void SetDspinText( QString name, QString txt );
private:
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
    QHash< QString, QLabel* > labels;
};

