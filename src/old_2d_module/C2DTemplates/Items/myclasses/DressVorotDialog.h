//#include "myclasses\C2DPath.h"
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressVorotDialog: public Elasticas::PropertiesDialog
{
    Q_OBJECT
    Elasticas::DoubleSpinBoxProperty* dsp1;
public:
    DressVorotDialog();
    void setheights( double left, double right );
    void SetDspinVal( QString name,double d );
    void SetDspinMinMax( QString name,double min,double max );
    void changelabel( QString name, bool visible ,QString text=QString(";") );
    void changeDSPINstate( QString name, bool state );
    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
private:
    void darts();
    void dsgnpoints( QString s );
    void minmaxheights( int i );
    double heightl,heightr;
    QHash< QString, Elasticas::CheckBoxProperty* > checkbox;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;

    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
    QHash< QString, QLabel* > labels;
    void v_r_add( QString name, int cond );
private slots:
    void heihgt_leftbottom();
    void heihgt_rightbottom();
    void heihgt_lefttop();
    void heihgt_righttop();
    void is_vorotnik();
    void vorotnik_celnokroeny();
    void asp();
    void asz();

};

