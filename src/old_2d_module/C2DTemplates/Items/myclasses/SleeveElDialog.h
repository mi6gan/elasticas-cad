
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class SleeveElDialog: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    SleeveElDialog();
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
};

