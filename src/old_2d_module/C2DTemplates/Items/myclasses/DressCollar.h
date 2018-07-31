//#include "C2DPath.h"
#include "../../../C2DModule/Frameworks/Items/include/C2DItem.h"
class DressCollar: public Elasticas::PropertiesDialog
{
    Q_OBJECT
    Elasticas::DoubleSpinBoxProperty* dsp1;
public:
    DressCollar();
    double clasp_pmin,clasp_pmax,clasp_pcenter;
    void SetDspinMinMax( QString name,double min,double max );
    void setFoo(double value);
    void setSpinminmax( int i,double min=0,double max=0 );
    void setlength( int i, double l );
    void addqpath( QString s, QPainterPath p );
    void addqline( QString s, QLineF l );
    double memwidValue( int i );
    void setSpinValue( int i , double val);
    void setDspinLabel( QString name, QString text ){ this->dspinbox[name]->GetLabel()->setText(text); }
    void setmemwidLabel( int index, QString text ){ this->memwid[index]->GetLabel()->setText(text); }
    void setmemwidValue( int index, double value ){ this->memwid[index]->ReadVariantValue(value); }
    bool ic_c_d;
    QHash< QString, Elasticas::ComboBoxProperty* > combobox;
    bool firstchangegorlo;
private:

    Elasticas::DoubleSpinBoxProperty* memwid[20];
    Elasticas::CheckBoxProperty* is_clasp;

    QHash< QString, Elasticas::DoubleSpinBoxProperty* > dspinbox;
    QHash< QString, Elasticas::SpinBoxProperty* > ispinbox;
    double lengths[20];
    QHash< QString, QPainterPath > qpath;
    QHash< QString, QLineF > qline;
    void changeButtons();
private slots:
    void changebuttonsR2();
    void changebuttonsR1N();
    void changeZipperR4();
    void changeZipperL1();
    void changeGorlo();
    void changePlankap7p8();
    void changePlankap9();
    void changeLocation();
    void cut_position();
    void clasp_elements_type();
    void clasp_on();
};

