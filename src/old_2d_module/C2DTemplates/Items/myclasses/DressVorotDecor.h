//#include "myclasses\C2DPath.h"
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressVorotDecor: public Elasticas::PropertiesDialog
{
    Q_OBJECT
public:
    DressVorotDecor();
    void SetDspinVal( QString name,double d );
    void SetDspinMinMax( QString name,double min,double max );
    void vd_add( QString name, int cond );
    void showlabel( QString name, bool visible = true );
    void changelabel( QString name, QString text );
    void changecommon( QString name, int value );

private:

    void show_all_widgets( bool visible );
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
    QHash< QString, QLabel* > labels;

};

