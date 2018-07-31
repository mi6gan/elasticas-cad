#ifndef ELDRESS_H
#define ELDRESS_H
#include "elcore/elbasicdialogs.h"
namespace Elasticas
{
    class DressGoresDialog: public PropertiesDialog
    {
    public:
        DressGoresDialog(const QString & class_name);
    };

    class DressBKBasicPropertiesDialog: public PropertiesDialog //БК платья, основные параметры
    {
            ComboBoxProperty* length_input_type_cb;
            DoubleSpinBoxProperty* length1_dsp,*length2_dsp;
            void initDefaults();
            virtual void apply();
        public:
            DressBKBasicPropertiesDialog(const QString & class_name);
    };

    class DressBKBasicSkewsPropertiesDialog: public PropertiesDialog //БК платья, основные швы
    {
        public:
           DressBKBasicSkewsPropertiesDialog(const QString & class_name);
    };

    class DressIMKVentPropertiesDialog: public PropertiesDialog  //ИМК платья, разрезы/шлицы
    {
        public:
            DressIMKVentPropertiesDialog(const QString & classname);
    };

    class DressIMKClaspPropertiesDialog: public PropertiesDialog  //ИМК платья, разрезы/шлицы
    {
        public:
            DressIMKClaspPropertiesDialog(const QString & class_name);
    };

    class DressMKNeckDialog : public PropertiesDialog
    {
    public:
        DressMKNeckDialog(const QString & class_name);
    };

    class IMF1_10Dialog: public PropertiesDialog
    {
    public:
        IMF1_10Dialog();
    };

    class IMF4_4Dialog: public PropertiesDialog
    {
    public:
        IMF4_4Dialog();
    };

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


}
#endif
