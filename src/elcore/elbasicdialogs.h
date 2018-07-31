#ifndef ELDIALOGS_H
#define ELDIALOGS_H
#include "elcore.h"
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QDockWidget>
#include <QDialog>
#include <QScrollArea>
namespace Elasticas
{
    class DLL_DECLSPEC Dialog: public QWidget
    {
        Q_OBJECT
        QString dialog_name;
        QString object_class;
        Core::ObjectClass * dialog_class;
    protected:
        QVariant & commonValue(const QString & key);
        void updateCommonValues();
    public:
        Dialog(const QString & dialog_name,const QString & object_class="");
        Core::ObjectClass * dialogClass();
        const QString & dialogName();
    public slots:
        virtual void exec()=0;
        virtual void accept()=0;
        virtual void cancel()=0;
        virtual void apply();
        virtual void reject()=0;
        virtual void reset()=0;
    signals:
     void commonValuesChanged();
    };

    class DLL_DECLSPEC SimpleDialog: public Elasticas::Dialog
    {
        Q_OBJECT
    protected:
        QDialog* qdialog;
    public:
        SimpleDialog(QDialog* qdialog,const QString & dialog_name,const QString & object_class="");
    public slots:
        virtual void exec();
        virtual void accept();
        virtual void cancel();
        virtual void apply();
        virtual void reject();
        virtual void reset();
    };

    class DLL_DECLSPEC DockDialog: public Elasticas::Dialog
    {
         Q_OBJECT
       protected:
         QDockWidget* current_dock_widget;
         QDialogButtonBox* top_dialog_button_box;
         QDialogButtonBox* bottom_dialog_button_box;
       public:
         DockDialog(const QString & dialog_name,const QString & object_class="");
         void setCurrentDockWidget(QDockWidget* where);
       public slots:
         virtual void exec();
         virtual void accept();
         virtual void cancel();
         virtual void apply();
         virtual void reject();
         virtual void reset();
    };

    enum ConditionOperation {OperationAnd,OperationOr,OperationAndNot,OperationOrNot};
    class AbstractProperty;

    class DLL_DECLSPEC AbstractCondition
    {
         AbstractProperty* property;
        protected:
         virtual bool PrivateIsSatisfied()=0;
        public:
         AbstractCondition(AbstractProperty* property);
         bool IsSatisfied(bool inverse=false);
         AbstractProperty* GetProperty();
    };

    template<class SpinBoxType, class ValueType> class SpinBoxConditionTemplate: public AbstractCondition
    {
         SpinBoxType *p;
         ValueType from,to;
        public:
         SpinBoxConditionTemplate(SpinBoxType *p,ValueType from,ValueType to):AbstractCondition(p)
         {
             this->p=p; this->from=from; this->to=to;
         }

         virtual bool PrivateIsSatisfied()
         {
             ValueType v=p->value();
             return ((v>=from)&&(v<=to));
         }
    };
    typedef SpinBoxConditionTemplate<QSpinBox,int> SpinBoxCondition;
    typedef SpinBoxConditionTemplate<QDoubleSpinBox,int> DoubleSpinBoxCondition;


    class CheckBoxProperty;
    class DLL_DECLSPEC CheckBoxCondition:public AbstractCondition
    {
         CheckBoxProperty* p;
         bool value;
        public:
         CheckBoxCondition(CheckBoxProperty* p,bool value);
         virtual bool PrivateIsSatisfied();
    };

    class ComboBoxProperty;
    class DLL_DECLSPEC ComboBoxCondition: public AbstractCondition
    {
        ComboBoxProperty* p;
        int value;
       public:
        ComboBoxCondition(ComboBoxProperty* p,int value);
        virtual bool PrivateIsSatisfied();
    };

    class DLL_DECLSPEC AbstractProperty: public QObject
    {
        Q_OBJECT
       protected:
        QVector< QPair<AbstractCondition*, ConditionOperation > > conditions;
        QVector< AbstractProperty*> dependents;
        QLabel* label;
        QWidget* widget;
        bool state;
        bool AreConditionsSatisfied();
       public:
        AbstractProperty(const QString & name="");
        void AddCondition(AbstractCondition* new_cond, const ConditionOperation & pre_operation=OperationAnd,bool check_conditions=true);
        virtual void WriteVariantValue(QVariant & variant)=0;
        virtual void ReadVariantValue(const QVariant & variant)=0;
        virtual void ChangeState(bool conditions_satisfied);
        bool GetState();
        QWidget* GetWidget();
        QLabel* GetLabel();
      protected slots:
        void CheckDependents();
        void CheckConditions();
      signals:
        void StateChanged();
        void onChanged();
    };

    template <class QSpinBoxType,class ValueType,char ValueTypeFirstLetter> class SpinBoxPropertyTemplate: public AbstractProperty
    {
        friend class SpinBoxConditionTemplate< SpinBoxPropertyTemplate<QSpinBoxType,ValueType,ValueTypeFirstLetter>, ValueType >;
        QSpinBoxType* spin_box;
     public:
        SpinBoxPropertyTemplate(const QString & name,ValueType value,ValueType min,ValueType max,ValueType step=1):AbstractProperty(name)
        {
            spin_box=new QSpinBoxType;
            spin_box->setValue(value);
            spin_box->setRange(min,max);
            spin_box->setSingleStep(step);
            this->widget->layout()->addWidget(spin_box);
            switch(ValueTypeFirstLetter)
            {
             case 'd':
                QObject::connect(spin_box,SIGNAL(valueChanged(double)),this,SLOT(CheckDependents()));
                break;
             case 'i':
                QObject::connect(spin_box,SIGNAL(valueChanged(int)),this,SLOT(CheckDependents()));
                break;
            }
        }

        double GetValue()
        {
            return spin_box->value();
        }

        virtual void WriteVariantValue(QVariant & variant)
        {
            variant=spin_box->value();
        }

        virtual void ReadVariantValue(const QVariant & variant)
        {
            spin_box->setValue(variant.toDouble());
        }

        void SetMinMax(ValueType min,ValueType max)
        {
            spin_box->setRange(min,max);
        }
    };
    typedef SpinBoxPropertyTemplate<QSpinBox, int,'i'> SpinBoxProperty;
    typedef SpinBoxPropertyTemplate<QDoubleSpinBox, double,'d'> DoubleSpinBoxProperty;

    class DLL_DECLSPEC CheckBoxProperty: public AbstractProperty
    {
         friend class CheckBoxCondition;
         QCheckBox * check_box;
        public:
         CheckBoxProperty(const QString & name,bool value);
         virtual void WriteVariantValue(QVariant & variant);
         virtual void ReadVariantValue(const QVariant & variant);
    };


    class DLL_DECLSPEC ComboBoxProperty: public AbstractProperty
    {
    public:
     class DLL_DECLSPEC Item: public AbstractProperty
     {
             friend class ComboBoxProperty;
             int combobox_id;
             ComboBoxProperty* owner;
             bool hidden;
             Item(ComboBoxProperty* owner,const QString & text,int combobox_id);
             virtual void WriteVariantValue(QVariant & variant);
             virtual void ReadVariantValue(const QVariant & variant);
             virtual void ChangeState(bool conditions_siatisfied);
     };
     private:
        friend class ComboBoxCondition;
        QComboBox* combo_box;
        QVector<Item*> items;
        int ComboboxToCommonId(int combobox_id);
    public:
        ComboBoxProperty(const QString & name);
        void SetCurrentItem(Item* item);
        Item * AddItem(const QString & item_text);
        void HideItem(Item* item);
        void UnhideItem(Item* item);
        virtual void WriteVariantValue(QVariant & variant);
        virtual void ReadVariantValue(const QVariant & variant);
        bool IsCurrentSelection(int common_id);
        int GetCurrentId();
        QString GetCurrentText();
    };

    class DLL_DECLSPEC PropertiesDialog: public DockDialog
    {
        Q_OBJECT
         static int property_auto_id;
        protected:
         QHash<QString,AbstractProperty*> var_names_to_properties;
         ComboBoxProperty* silhouette_cbp;
         void WriteToCommonValues(const QString & var_prefix);
         void ReadFromCommonValues(const QString & var_prefix);
         static QHash< QString, QHash<QString,AbstractProperty*> > global_var_names_to_properties;
         QWidget* properties_widget;
         QScrollArea* scroll_area;
         QString GetAutoNameIfEmpty(const QString& name);
         static QString GetNextPropertyAutoName();
         void AddProperty(AbstractProperty* property,const QString & var_name=PropertiesDialog::GetNextPropertyAutoName());
         template <class SpinBoxType,class ValueType,char ValueTypeFirstLetter> SpinBoxPropertyTemplate<SpinBoxType, ValueType, ValueTypeFirstLetter>* AddSpinBoxPropertyTemplate(const QString & name,const QString & var_name,ValueType step,ValueType min,ValueType max)
         {
             ValueType default_value;
             SpinBoxPropertyTemplate<SpinBoxType, ValueType, ValueTypeFirstLetter>* sbp;
             const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
             if((min==max)&&(max==0))
             {
                 min=vars[this->dialogClass()->className()+var_name+":Min"].toDouble();
                 max=vars[this->dialogClass()->className()+var_name+":Max"].toDouble();
             }
             if(vars.contains(this->dialogClass()->className()+var_name+":Default")) default_value=vars[this->dialogClass()->className()+var_name+":Default"].toDouble();
             else default_value=0;
             this->commonValue(var_name)=default_value;
            sbp=new SpinBoxPropertyTemplate<SpinBoxType, ValueType, ValueTypeFirstLetter>(name,default_value,min,max,step);
            this->AddProperty(sbp,var_name);
            return sbp;
         }

         SpinBoxProperty* AddSpinBoxProperty(const QString & name,const QString & var_name="",int step=1,int min=0,int max=0);
         DoubleSpinBoxProperty* AddDoubleSpinBoxProperty(const QString & name,const QString & var_name="",double step=0.1f,double min=0.0f,double max=100.0f);

         CheckBoxProperty* AddCheckBoxProperty(const QString & name,const QString & var_name="",bool default_value=true);
         ComboBoxProperty* AddComboBoxProperty(const QString & name,const QString items[],const QString & var_name="" );
         ComboBoxProperty* AddComboBoxProperty(const QString & name,const QString & var_name="" );
         void InitSkirtDressBKBasicSewsProperties();
         void InitStraightSkirtDressIMKVentProperties();
         void InitSkirtDressPT();
         void InitTopGarmentsBKProperties();
         void InitTopGarmentsMKProperties();
         void InitTopGarmentsNeckProperties();
         void InitTopGarmentsClaspProperties();
 //    void InitSkirtDressClasp();
        public:
            PropertiesDialog(const QString & dialog_name,const QString & object_class);
        public slots:
            virtual void exec();
            virtual void apply();
            virtual void reject();
            virtual void reset();
            void AdjustSizes();
        signals:
            void ContentSizeChanged();
    };
}

#endif // ELDIALOGS_H
