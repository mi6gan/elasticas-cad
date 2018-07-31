#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressGLine: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    DressGLine();

private:
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;

};

