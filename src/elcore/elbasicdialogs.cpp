#include "elbasicdialogs.h"
namespace Elasticas
{
    Dialog::Dialog(const QString & dialog_name,const QString & object_class)
    {
        this->object_class=object_class;
        this->dialog_name=dialog_name;
        this->dialog_class=Core::Instance()->classByName(object_class);
    }

    Core::ObjectClass * Dialog::dialogClass()
    {
        return this->dialog_class;
    }

    const QString & Dialog::dialogName()
    {
        return this->dialog_name;
    }

    QVariant & Dialog::commonValue(const QString & key)
    {
        return Core::Instance()->CommonVariablesSafeRW()[this->dialogClass()->className()+key];
    }

    void Dialog::updateCommonValues()
    {
    }

    void Dialog::apply()
    {
        if(dialog_class)
        {
            this->dialog_class->setChanged(true);
            this->commonValue("Changed")=true;
        }
        if(object_class.isEmpty())
            foreach(Core::ObjectClass* object_class,Core::Instance()->objectClasses())
            {
                object_class->setChanged(true);
                Core::Instance()->CommonVariablesSafeRW()[object_class->name+":Changed"]=true;
            }
        this->commonValuesChanged();
    }

  //__________________________________________
    SimpleDialog::SimpleDialog(QDialog *qdialog, const QString &dialog_name, const QString &object_class):Dialog(dialog_name,object_class)
    {
        this->qdialog=qdialog;
    }

    void SimpleDialog::exec()
    {
        qdialog->exec();
    }

    void SimpleDialog::accept()
    {

    }

    void SimpleDialog::cancel()
    {
        qdialog->close();
    }

    void SimpleDialog::apply()
    {

    }

    void SimpleDialog::reject()
    {

    }

    void SimpleDialog::reset()
    {

    }

  //__________________________________________________________________


    DockDialog::DockDialog(const QString & dialog_name,const QString & object_class):Dialog(dialog_name,object_class)
    {        
        this->top_dialog_button_box=new QDialogButtonBox;
        this->bottom_dialog_button_box=new QDialogButtonBox;
        this->current_dock_widget=NULL;
        QObject::connect(this->top_dialog_button_box->addButton(trUtf8("Ок"),QDialogButtonBox::ApplyRole),SIGNAL(released()),this,SLOT(accept()));
        QObject::connect(this->top_dialog_button_box->addButton(trUtf8("Отмена"),QDialogButtonBox::ApplyRole),SIGNAL(released()),this,SLOT(cancel()));
        QObject::connect(this->top_dialog_button_box->addButton(trUtf8("Применить"),QDialogButtonBox::ApplyRole),SIGNAL(released()),this,SLOT(apply()));
        QObject::connect(this->bottom_dialog_button_box->addButton(trUtf8("Сброс"),QDialogButtonBox::ApplyRole),SIGNAL(released()),this,SLOT(reject()));
        QObject::connect(this->bottom_dialog_button_box->addButton(trUtf8("По умолчанию"),QDialogButtonBox::ApplyRole),SIGNAL(released()),this,SLOT(reset()));
    }

    void DockDialog::setCurrentDockWidget(QDockWidget* current_dock_widget)
    {
        this->current_dock_widget=current_dock_widget;
    }

    void DockDialog::exec()
    {
        if(this->current_dock_widget)
        {
            this->reject();
            current_dock_widget->setWindowTitle(this->dialogName());
            current_dock_widget->setWidget(this);
            //this->adjustSize();
            current_dock_widget->adjustSize();
            current_dock_widget->show();
        }
        else throw Exception("void DockDialog::exec(): no dock widget installed");
    }

    void DockDialog::accept()
    {
        this->apply();
        this->cancel();
    }


    void DockDialog::cancel()
    {
        if(this->current_dock_widget)
        {
            this->current_dock_widget->hide();
        }
    }

    void DockDialog::apply()
    {
        Elasticas::Dialog::apply();
    }

    void DockDialog::reject()
    {
    }

    void DockDialog::reset()
    {
    }

  //________________________________________________________________

    AbstractCondition::AbstractCondition(AbstractProperty* property)
    {
        this->property=property;
    }

    bool AbstractCondition::IsSatisfied(bool inverse)
    {
        bool is_satisified=this->PrivateIsSatisfied();
        if(inverse) is_satisified=!is_satisified;
        return ((this->property->GetState())&&(is_satisified));
    }

    //______________________________________________________________
    CheckBoxCondition::CheckBoxCondition(CheckBoxProperty* p,bool value):AbstractCondition(p)
    {
        this->p=p;
        this->value=value;
    }

    bool CheckBoxCondition::PrivateIsSatisfied()
    {
        return ((this->p->check_box->checkState()==Qt::Checked)==this->value);
    }
    //_______________________________________________________________
    ComboBoxCondition::ComboBoxCondition(ComboBoxProperty* p,int value):AbstractCondition(p)
    {
        this->value=value;
        this->p=p;
    }

    bool ComboBoxCondition::PrivateIsSatisfied()
    {
        return this->p->IsCurrentSelection(value);
    }

    //_______________________________________________________________

    AbstractProperty* AbstractCondition::GetProperty()
    {
        return this->property;
    }
    //______________________________
    AbstractProperty::AbstractProperty(const QString & name)
    {
        this->label=new QLabel(name);
        this->widget=new QWidget;
        this->widget->setLayout(new QHBoxLayout);
        this->widget->layout()->addWidget(label);
        this->state=true;
    }

    bool AbstractProperty::AreConditionsSatisfied()
    {
        bool common_res=true;
        int count=conditions.size();
        if(count)
        {
            bool res=conditions[0].first->IsSatisfied(conditions[0].second==OperationAndNot||conditions[0].second==OperationOrNot);
            bool last_was_or=false;
            for(int a=1;a<count;a++)
            {
                bool is_satisfied=conditions[a].first->IsSatisfied(conditions[a].second==OperationAndNot||conditions[a].second==OperationOrNot);
                if(conditions[a].second==OperationAnd||conditions[a].second==OperationAndNot) res=(res&&is_satisfied);
                else
                {
                    if(last_was_or) common_res=common_res||res;
                    else common_res=res;
                    res=is_satisfied;
                    last_was_or=true;
                }
            }
            if(last_was_or) common_res=common_res||res;
            else common_res=res;
        }
        return common_res;
    }

    void AbstractProperty::AddCondition(AbstractCondition* cond, const ConditionOperation & pre_operation,bool check_conditions)
    {
        conditions.push_back(QPair<AbstractCondition*, ConditionOperation >(cond,pre_operation));
        cond->GetProperty()->dependents.push_back(this);
        if(check_conditions) this->CheckConditions();
    }

    void AbstractProperty::ChangeState(bool conditions_satisfied)
    {
        this->widget->setVisible(conditions_satisfied);
        this->state=conditions_satisfied;
        this->CheckDependents();
        this->StateChanged();
    }

    bool AbstractProperty::GetState()
    {
        return this->state;
    }

    QWidget* AbstractProperty::GetWidget()
    {
        return this->widget;
    }

    QLabel* AbstractProperty::GetLabel()
    {
        return label;
    }

    void AbstractProperty::CheckDependents()
    {
        int count=dependents.size();
        for(int a=0;a<count;a++) dependents[a]->CheckConditions();
        this->onChanged();
    }

    void AbstractProperty::CheckConditions()
    {
        this->ChangeState(this->AreConditionsSatisfied());
    }

  //________________________________________________________________
    CheckBoxProperty::CheckBoxProperty(const QString & name,bool value):AbstractProperty(name)
    {
        check_box=new QCheckBox;
        check_box->setChecked(value);
        QObject::connect(check_box,SIGNAL(toggled(bool)),this,SLOT(CheckDependents()));
        this->widget->layout()->addWidget(check_box);
    }

    void CheckBoxProperty::WriteVariantValue(QVariant & variant)
    {
        variant=(check_box->checkState()==Qt::Checked);
    }

    void CheckBoxProperty::ReadVariantValue(const QVariant & variant)
    {
        check_box->setChecked(variant.toBool());
    }
//_____________________________________________________________________________


    ComboBoxProperty::Item::Item(ComboBoxProperty* owner,const QString & text,int combobox_id):AbstractProperty(text)
    {
        this->owner=owner; this->combobox_id=combobox_id; this->hidden=false;
    }

    void ComboBoxProperty::Item::ChangeState(bool conditions_siatisfied)
    {
        if(this->hidden) ;
        if(!conditions_siatisfied) owner->HideItem(this);
        else owner->UnhideItem(this);
        this->hidden=(!conditions_siatisfied);
    }

    void ComboBoxProperty::Item::WriteVariantValue(QVariant & variant){}

    void ComboBoxProperty::Item::ReadVariantValue(const QVariant & variant){}


    int ComboBoxProperty::ComboboxToCommonId(int combobox_id)
    {
        int count=items.size();
        for(int a=0;a<count;a++)
            if(items[a]->combobox_id==combobox_id) return a;
        return -1;
    }

    ComboBoxProperty::ComboBoxProperty(const QString & name):AbstractProperty(name)
    {
        combo_box=new QComboBox;
        QObject::connect(combo_box,SIGNAL(currentIndexChanged(int)),this,SLOT(CheckDependents()));
        this->widget->layout()->addWidget(combo_box);
    }

    void ComboBoxProperty::SetCurrentItem(Item* item)
    {
        if(!item->hidden) this->combo_box->setCurrentIndex(item->combobox_id);
    }

    ComboBoxProperty::Item * ComboBoxProperty::AddItem(const QString & item_text)
    {
        items.push_back(new ComboBoxProperty::Item(this,item_text,this->combo_box->count()));
        this->combo_box->addItem(item_text);
        if(combo_box->count()==1) combo_box->setCurrentIndex(0);
        return items.last();
    }

    void ComboBoxProperty::HideItem(ComboBoxProperty::Item* item)
    {
        if(item->hidden) return;
        combo_box->disconnect(SIGNAL(currentIndexChanged(int)));
        this->combo_box->removeItem(item->combobox_id);
        int count=items.size();
        for(int a=0;a<count;a++)
            if(items[a]->combobox_id>item->combobox_id) items[a]->combobox_id--;
        item->combobox_id--;
        QObject::connect(combo_box,SIGNAL(currentIndexChanged(int)),this,SLOT(CheckDependents()));
    }

    void ComboBoxProperty::UnhideItem(ComboBoxProperty::Item* item)
    {
        if(!item->hidden) return;
        this->combo_box->insertItem(item->combobox_id+1,item->label->text());
        int count=items.size();
        for(int a=0;a<count;a++)
            if(items[a]->combobox_id>item->combobox_id) items[a]->combobox_id++;
        item->combobox_id++;
    }

    void ComboBoxProperty::WriteVariantValue(QVariant & variant)
    {
        int count=items.size();
      //  for(int a=0;a<items.size();a++) qDebug()<<items[a]->label->text()<<" "<<a<<" "<<items[a]->combobox_id;
     //   qDebug()<<this->label->text()<<" "<<combo_box->currentIndex()<<" "<<(this->ComboboxToCommonId(combo_box->currentIndex()));
        variant=this->ComboboxToCommonId(combo_box->currentIndex());
    }

    void ComboBoxProperty::ReadVariantValue(const QVariant & variant)
    {
        int id=variant.toInt();
        if((id<0)||(id>this->combo_box->count())) return;
        if(items[id]->hidden) return;
        this->combo_box->setCurrentIndex(items[id]->combobox_id);
    }

    bool ComboBoxProperty::IsCurrentSelection(int common_id)
    {
        return (this->ComboboxToCommonId(this->combo_box->currentIndex())==common_id);
    }

    int ComboBoxProperty::GetCurrentId()
    {
        int count=items.size();
        for(int a=0;a<count;a++) if(this->IsCurrentSelection(a)) return a;
        return -1;
    }

    QString ComboBoxProperty::GetCurrentText()
    {
        return this->combo_box->currentText();
    }

//_______________________________________________________________
    QHash< QString, QHash<QString,AbstractProperty*> > PropertiesDialog::global_var_names_to_properties;
    int PropertiesDialog::property_auto_id=0;
    PropertiesDialog::PropertiesDialog(const QString & dialog_name,const QString & object_class):DockDialog(dialog_name,object_class)
    {
        QVBoxLayout* lay_out=new QVBoxLayout;
        this->setLayout(lay_out);

        properties_widget=new QWidget;
        properties_widget->setLayout(new QVBoxLayout);
        scroll_area=new QScrollArea;
        scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll_area->setWidget(properties_widget);
        scroll_area->setWidgetResizable(true);
        lay_out->addWidget(scroll_area);

        this->layout()->addWidget(top_dialog_button_box);
        this->layout()->addWidget(bottom_dialog_button_box);



        /*

        lay_out->addWidget(properties_widget)
        */
       // this->AdjustSizes();
        //lay_out->setSizeConstraint(QLayout::SetMinAndMaxSize);
    }

    void PropertiesDialog::WriteToCommonValues(const QString & var_prefix)
    {
        QHashIterator<QString,AbstractProperty*> i(var_names_to_properties);
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        while(i.hasNext())
        {
            i.next();
            //if(i.value()->GetState())
            i.value()->WriteVariantValue(commonValue(i.key()));
        }
    }

    void PropertiesDialog::ReadFromCommonValues(const QString & var_prefix)
    {
        QHashIterator<QString,AbstractProperty*> i(var_names_to_properties);
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        while(i.hasNext())
        {
            i.next();
            const QString & key=var_prefix+i.key();
            if(vars.contains(key)) i.value()->ReadVariantValue(vars[key]);
        }
    }

    QString PropertiesDialog::GetNextPropertyAutoName()
    {
        property_auto_id++;
        return "RandomProperty"+QString().setNum(property_auto_id);
    }

    QString PropertiesDialog::GetAutoNameIfEmpty(const QString & name)
    {
        if(name.isEmpty()) return this->GetNextPropertyAutoName();
        return name;
    }

    void PropertiesDialog::AddProperty(AbstractProperty* property,const QString & var_name)
    {
#ifdef BUILD_DEBUG
        property->GetWidget()->setToolTip(var_name);
#endif
        global_var_names_to_properties[this->dialogClass()->className()][var_name]=var_names_to_properties[var_name]=property;
        properties_widget->layout()->addWidget(property->GetWidget());
        QObject::connect(property,SIGNAL(StateChanged()),this,SLOT(AdjustSizes()));
    }

    SpinBoxProperty* PropertiesDialog::AddSpinBoxProperty(const QString & name,const QString & var_name,int step,int min,int max)
    {
        QString final_var_name;
        return this->AddSpinBoxPropertyTemplate<QSpinBox,int,'i'>(name,this->GetAutoNameIfEmpty(var_name),step,min,max);
    }

    DoubleSpinBoxProperty* PropertiesDialog::AddDoubleSpinBoxProperty(const QString & name,const QString & var_name,double step,double min,double max)
    {
        return this->AddSpinBoxPropertyTemplate<QDoubleSpinBox,double,'d'>(name,this->GetAutoNameIfEmpty(var_name),step,min,max);
    }

    CheckBoxProperty* PropertiesDialog::AddCheckBoxProperty(const QString & name,const QString & in_var_name,bool default_value)
    {
        const QString & var_name=this->GetAutoNameIfEmpty(in_var_name);
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        CheckBoxProperty* cbp;
        if(vars.contains(this->dialogClass()->className()+var_name+":Default")) default_value=vars[this->dialogClass()->className()+var_name+":Default"].toBool();
        this->commonValue(var_name)=default_value;

        cbp=new CheckBoxProperty(name,default_value);
        this->AddProperty(cbp,var_name);
        return cbp;
    }

    ComboBoxProperty* PropertiesDialog::AddComboBoxProperty(const QString & name,const QString items[],const QString & in_var_name)
    {
        const QString & var_name=this->GetAutoNameIfEmpty(in_var_name);
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        ComboBoxProperty* cbp=new ComboBoxProperty(name);
        ComboBoxProperty::Item* item;
        int default_value=0;
        if(vars.contains(this->dialogClass()->className()+var_name+":Default")) default_value=vars[this->dialogClass()->className()+var_name+":Default"].toInt();
        this->commonValue(var_name)=default_value;
        for(int a=0;(items[a]!=NULL);a++)
        {
            item=cbp->AddItem(items[a]);
            if(a==default_value) cbp->SetCurrentItem(item);
        }
        this->AddProperty(cbp,var_name);
        return cbp;
    }

    ComboBoxProperty* PropertiesDialog::AddComboBoxProperty(const QString & name,const QString & var_name )
    {
        QString set[]={NULL};
        return this->AddComboBoxProperty(name,set,var_name);
    }

    void PropertiesDialog::InitTopGarmentsBKProperties()
    {
        this->commonValue("Length1:Default")=59;
        this->commonValue("SleeveLength:Default")=68;
        this->AddDoubleSpinBoxProperty(trUtf8("Длина изделия"),"Length1",0.1,0,100);
        QString items[]={trUtf8("полуприлегающий"),trUtf8("прилегающий"),trUtf8("прямой"),NULL};
        silhouette_cbp=this->AddComboBoxProperty(trUtf8("Силуэт"),items,"SilhouetteType");
        this->commonValue("Sleeve:Default")=false;
        CheckBoxProperty* chbp=this->AddCheckBoxProperty(trUtf8("С рукавом"),"Sleeve");
        DoubleSpinBoxProperty* dsbp=this->AddDoubleSpinBoxProperty(trUtf8("Длина рукава"),"SleeveLength",0.1,0,100);
        dsbp->AddCondition(new CheckBoxCondition(chbp,true));

        this->commonValue("HorizPart:Default")=false;
        this->AddCheckBoxProperty(trUtf8("С горизонтальным членением"),"HorizPart");
    }

    void PropertiesDialog::InitTopGarmentsMKProperties()
    {
        //QString items[]={trUtf8("Рельефы"),trUtf8("Вытачки"),NULL};
        //ComboBoxProperty* cbp1=this->AddComboBoxProperty(trUtf8("Элементы формообразования"),items);

        QString items2[]={trUtf8("от плечевого шва"),trUtf8("от линии проймы"),trUtf8("Без рельефа"),NULL};
        ComboBoxProperty* cbp2=this->AddComboBoxProperty(trUtf8("Рельеф"),items2,"Relief");

        //cbp2->AddCondition(new ComboBoxCondition(cbp1,0));
        //dsp1->AddCondition(new ComboBoxCondition(cbp1,0));
        //dsp2->AddCondition(new ComboBoxCondition(cbp1,0));

        //QString items3[]={trUtf8("двухшовный"),trUtf8("одношовный"),NULL};

        //ComboBoxProperty* cbp3=this->AddComboBoxProperty(trUtf8("Рукав"),items3);
        //cbp3->AddCondition(new ComboBoxCondition(cbp1,0));

        //this->AddDoubleSpinBoxProperty(trUtf8("Вытачки на полочке"));
        //this->AddDoubleSpinBoxProperty(trUtf8("Талиевые "));
    }

    void PropertiesDialog::InitTopGarmentsNeckProperties()
    {
        this->commonValue("Smpl1:Default")=1.0f;
        this->commonValue("Smpl2:Default")=1.0f;
        QLabel* label;
        this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("Модельное расширение/углубление линии горловины")));
        label->setStyleSheet("*{font-weight:bold;}");
        DoubleSpinBoxProperty* dsp7=this->AddDoubleSpinBoxProperty(trUtf8("Расширение горловины на полочке, см"),"Rg1",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp8=this->AddDoubleSpinBoxProperty(trUtf8("Расширение горловины на спинке, см"),"Rg2",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp9=this->AddDoubleSpinBoxProperty(trUtf8("Расширение горловины у плечевого среза, см"),"Rg3",0.1f,0.0f,100.0f);

        this->properties_widget->layout()->addWidget(label=new QLabel(trUtf8("Смещение плечевого среза")));
        label->setStyleSheet("*{font-weight:bold;}");
        DoubleSpinBoxProperty* dsp1=this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки основания шеи, см"),"Smpl1",0.1f,-100.0f,100.0f);
        DoubleSpinBoxProperty* dsp2=this->AddDoubleSpinBoxProperty(trUtf8("Смещение у точки конца плеча, см"),"Smpl2",0.1f,-100.0f,100.0f);

    }

    void PropertiesDialog::InitTopGarmentsClaspProperties()
    {
        this->commonValue("Sh1:Default")=1.3f;
        this->commonValue("Sh2:Default")=3.0f;
        this->commonValue("Sh4:Default")=3.0f;
        this->commonValue("R1:Default")=1.5f;
        this->commonValue("R2:Default")=6.0f;
        this->commonValue("N:Default")=4;
        this->commonValue("Sm3:Default")=1.0f;
        this->commonValue("Sm4:Default")=1.0f;

        CheckBoxProperty* cbp1=this->AddCheckBoxProperty(trUtf8("Застёжка"));
        CheckBoxProperty* cbp2=this->AddCheckBoxProperty(trUtf8("Проходит через горловину"));
        cbp1->GetWidget()->setStyleSheet("*{font-weight:bold;}");
        QString list1[]={trUtf8("На полочке"),trUtf8("На спинке"),trUtf8("В плечевом шве"),NULL};
        ComboBoxProperty* cmbp1=this->AddComboBoxProperty(trUtf8("Расположение"),list1);
        cmbp1->AddCondition(new CheckBoxCondition(cbp1,true));
        cbp2->AddCondition(new CheckBoxCondition(cbp1,true));
        DoubleSpinBoxProperty* dsp10=this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии застёжки по линии горловины, см"),"Sm3",0.1f,-100.0f,100.0f);
        DoubleSpinBoxProperty* dsp11=this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии застёжки по линии талии, см"),"Sm4",0.1f,-100.0f,100.0f);
        cmbp1->AddCondition(new CheckBoxCondition(cbp2,true));
        dsp10->AddCondition(new ComboBoxCondition(cmbp1,0));
        dsp10->AddCondition(new ComboBoxCondition(cmbp1,1),Elasticas::OperationOr);
        dsp11->AddCondition(new ComboBoxCondition(cmbp1,0));
        dsp11->AddCondition(new ComboBoxCondition(cmbp1,1),Elasticas::OperationOr);

        QString list3[]={trUtf8("Потайная"),trUtf8("Открытая"),trUtf8("Застёжка-планка"),NULL};
        ComboBoxProperty* cmbp2=this->AddComboBoxProperty(trUtf8("Вид застёжки"),list3);
        cmbp2->AddCondition(new CheckBoxCondition(cbp1,true));

        QString list4[]={trUtf8("Застёжка на молнию"),trUtf8("Застёжка на пуговицы"), trUtf8("Застёжка на ленту велькро"),
                         trUtf8("Застёжка на кнопки"),trUtf8("Застёжка на навесные петли"),NULL};
        ComboBoxProperty* cmbp3=this->AddComboBoxProperty(trUtf8("Тип застёгивающих элементов"),list4);

        QString list5[]={trUtf8("Встык"),trUtf8("С заходом"),NULL};
        ComboBoxProperty* cmbp4=this->AddComboBoxProperty(trUtf8(""),list5);

        cmbp3->AddCondition(new ComboBoxCondition(cmbp2,1));
        DoubleSpinBoxProperty* dsp12=this->AddDoubleSpinBoxProperty(trUtf8("Ширина молнии, см"),"Sh3",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp13=this->AddDoubleSpinBoxProperty(trUtf8("Длина молнии, см"),"L1",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp14=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от горловины до начала молнии, см"),"R4",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp20=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от линии низа до конца молнии, см"),"R5",0.1f,0.0f,100.0f);
        dsp12->AddCondition(new ComboBoxCondition(cmbp3,0));
        dsp13->AddCondition(new ComboBoxCondition(cmbp3,0));
        dsp14->AddCondition(new ComboBoxCondition(cmbp3,0));
        dsp20->AddCondition(new ComboBoxCondition(cmbp3,0));

        DoubleSpinBoxProperty* dsp15=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от края борта до л. полузаноса, см"),"Sh1",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp18=this->AddDoubleSpinBoxProperty(trUtf8("Ширина захода сторон друг на друга, см"),"Sh2",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp19=this->AddDoubleSpinBoxProperty(trUtf8("Ширина планки, см"),"Sh4",0.1f,0.0f,100.0f);
        SpinBoxProperty* sp1=this->AddSpinBoxProperty(trUtf8("Количество пуговиц/кнопок"),"N",1,0,100);
        DoubleSpinBoxProperty* dsp16=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от горловины до первой пуговицы, см"),"R1",0.1f,0.0f,100.0f);
        DoubleSpinBoxProperty* dsp17=this->AddDoubleSpinBoxProperty(trUtf8("Расстояние от линии низа до последней пуговицы, см"),"R2",0.1f,0.0f,100.0f);



        dsp15->AddCondition(new ComboBoxCondition(cmbp3,1));
        dsp15->AddCondition(new ComboBoxCondition(cmbp3,2),Elasticas::OperationOr);
        dsp15->AddCondition(new ComboBoxCondition(cmbp3,3),Elasticas::OperationOr);

        sp1->AddCondition(new ComboBoxCondition(cmbp3,1));
        sp1->AddCondition(new ComboBoxCondition(cmbp3,2),Elasticas::OperationOr);
        sp1->AddCondition(new ComboBoxCondition(cmbp3,3),Elasticas::OperationOr);
        sp1->AddCondition(new ComboBoxCondition(cmbp3,4),Elasticas::OperationOr);
        sp1->AddCondition(new ComboBoxCondition(cmbp2,2),Elasticas::OperationOr);


        dsp16->AddCondition(new ComboBoxCondition(cmbp3,1));
        dsp16->AddCondition(new ComboBoxCondition(cmbp3,2),Elasticas::OperationOr);
        dsp16->AddCondition(new ComboBoxCondition(cmbp3,3),Elasticas::OperationOr);
        dsp16->AddCondition(new ComboBoxCondition(cmbp3,4),Elasticas::OperationOr);
        dsp16->AddCondition(new ComboBoxCondition(cmbp2,2),Elasticas::OperationOr);

        dsp17->AddCondition(new ComboBoxCondition(cmbp3,1));
        dsp17->AddCondition(new ComboBoxCondition(cmbp3,2),Elasticas::OperationOr);
        dsp17->AddCondition(new ComboBoxCondition(cmbp3,3),Elasticas::OperationOr);
        dsp17->AddCondition(new ComboBoxCondition(cmbp3,4),Elasticas::OperationOr);
        dsp17->AddCondition(new ComboBoxCondition(cmbp2,2),Elasticas::OperationOr);

        cmbp4->AddCondition(new ComboBoxCondition(cmbp3,4));
        dsp18->AddCondition(new ComboBoxCondition(cmbp4,1));

        dsp19->AddCondition(new ComboBoxCondition(cmbp2,2));



        cbp1=this->AddCheckBoxProperty(trUtf8("Разрез/вырез"));
        cbp1->GetWidget()->setStyleSheet("*{font-weight:bold;}");
        QString list2[]={trUtf8("На полочке"),trUtf8("На спинке"),trUtf8("В плечевом шве"),NULL};
        cmbp1=this->AddComboBoxProperty(trUtf8("Расположение"),list2);
        cmbp1->AddCondition(new CheckBoxCondition(cbp1,true));
        dsp10=this->AddDoubleSpinBoxProperty(trUtf8("Смещение линии относительно центра, см"),"Sm",0.1f,-100.0f,100.0f);
        dsp10->AddCondition(new ComboBoxCondition(cmbp1,0));
        dsp10->AddCondition(new ComboBoxCondition(cmbp1,1),Elasticas::OperationOr);



    }

    void PropertiesDialog::InitSkirtDressBKBasicSewsProperties()
    {
        AbstractProperty* p1;
        CheckBoxProperty* cbp1;

        this->commonValue("A2:Default")=0.5f;
        this->commonValue("A2:Min")=-400.0f;
        this->commonValue("A2:Max")=400.0f;
        this->commonValue("VB:Default")=true;
        this->commonValue("VP:Default")=false;
        this->commonValue("VZ:Default")=true;

        cbp1=this->AddCheckBoxProperty(trUtf8("Боковые швы"),"VB");
        this->AddCheckBoxProperty(trUtf8("Задний шов"),"VZ");
        this->AddCheckBoxProperty(trUtf8("Передний шов"),"VP");
        p1=this->AddDoubleSpinBoxProperty(trUtf8("Смещение бокового шва в сторону спинки (см)"),"A2",0.5f);
        p1->AddCondition(new CheckBoxCondition(cbp1,true));
    }

    void PropertiesDialog::InitStraightSkirtDressIMKVentProperties()
    {

        this->commonValue("BackVentType:Default")=1;
        ComboBoxProperty* cmbp1;
        AbstractProperty* p1;
        ComboBoxProperty::Item* cmbp1_item;
        QString sew_names[]={trUtf8("шве спереди"),trUtf8("шве сзади"),trUtf8("левом боковом шве"),trUtf8("правом боковом шве")};
        QString sew_var_names[]={"VP","VZ","VB","VB"};
        QString vent_var_names[]={"Front","Back","Left","Right"};
        QString vent_type_names[]={trUtf8("Ничего"),trUtf8("Шлица"),trUtf8("Разрез")};
        for(int a=0;a<4;a++)
        {
           this->commonValue(vent_var_names[a]+"VentHeight:Default")=this->commonValue(vent_var_names[a]+"VentWidth:Default")=3.0f;
           this->commonValue(vent_var_names[a]+"VentHeight:Min")=this->commonValue(vent_var_names[a]+"VentWidth:Min")=0.0f;
           this->commonValue(vent_var_names[a]+"VentHeight:Max")=this->commonValue(vent_var_names[a]+"VentWidth:Max")=100.0f;

           cmbp1=this->AddComboBoxProperty(trUtf8("В ")+sew_names[a],vent_var_names[a]+"VentType");
           int default_vent_type=this->commonValue(vent_var_names[a]+"VentType:Default").toInt();
           for(int b=0;b<3;b++)
           {
               cmbp1_item=cmbp1->AddItem(vent_type_names[b]);
               if(default_vent_type==b) cmbp1->SetCurrentItem(cmbp1_item);
           }
           cmbp1->AddCondition(new CheckBoxCondition((CheckBoxProperty*)global_var_names_to_properties[this->dialogClass()->className()][sew_var_names[a]],true));

           p1=this->AddDoubleSpinBoxProperty(trUtf8("Ширина (см)"),vent_var_names[a]+"VentWidth");



           p1->AddCondition(new ComboBoxCondition(cmbp1,1));

           this->AddProperty(p1=this->AddDoubleSpinBoxProperty(trUtf8("Высота от линии низа (см)"),vent_var_names[a]+"VentHeight"));
           p1->AddCondition(new ComboBoxCondition(cmbp1,0),OperationAndNot);

           QFrame* frame=new QFrame;
           frame->setFrameShape(QFrame::HLine);
           properties_widget->layout()->addWidget(frame);
       }
    }

    void PropertiesDialog::InitSkirtDressPT()
    {

        this->commonValue("PTx:Default")=0; // PTx
        this->commonValue("PTx:Min")=0;
        this->commonValue("PTx:Max")=100;

        this->commonValue("PTy:Default")=0; // PTy
        this->commonValue("PTy:Min")=0;
        this->commonValue("PTy:Max")=100;
        AbstractProperty* property;
        QLabel* label=new QLabel(trUtf8("Технологический припуск"));
        label->setFixedHeight(20);
        label->setAlignment(Qt::AlignCenter);
        this->properties_widget->layout()->addWidget(label);

        property=this->AddSpinBoxProperty(trUtf8("PTx (%)"),"PTx");
        property->GetLabel()->setAlignment(Qt::AlignRight);
        property->GetWidget()->setFixedHeight(50);

        property=this->AddSpinBoxProperty(trUtf8("PTy (%)"),"PTy");
        property->GetLabel()->setAlignment(Qt::AlignRight);
        property->GetWidget()->setFixedHeight(50);

    }
    void PropertiesDialog::exec()
    {
        this->AdjustSizes();
        DockDialog::exec();

        //
        //if(current_dock_widget) current_dock_widget->resize(10,10); //scroll_area->minimumWidth(),current_dock_widget->height());
    }

    void PropertiesDialog::apply()
    {
        WriteToCommonValues(this->dialogClass()->className());
        DockDialog::apply();
    }

    void PropertiesDialog::reject()
    {
        ReadFromCommonValues(this->dialogClass()->className());
    }

    void PropertiesDialog::reset()
    {
        ReadFromCommonValues(this->dialogClass()->className()+":Default");
        this->apply();
    }

    void PropertiesDialog::AdjustSizes()
    {
        /*
        if(this->properties_widget->height()>200)
        {
            this->layout()->removeWidget(this->scroll_area);
            this->layout()->removeWidget(properties_widget);
            this->scroll_area->setWidget(properties_widget);
            this->layout()->addWidget(this->scroll_area);
        }
        else
        {
            this->layout()->removeWidget(this->scroll_area);
            this->layout()->addWidget(this->properties_widget);
        }*/
        this->properties_widget->adjustSize();
        //this->scroll_area->setMaximumHeight(this->properties_widget->height());
        //this->scroll_area->setMaximumHeight(this->properties_widget->height());
        this->scroll_area->setMinimumWidth(this->properties_widget->width());
        //this->resize(this->properties_widget->width(),this->height());
        this->ContentSizeChanged();
    }

}
