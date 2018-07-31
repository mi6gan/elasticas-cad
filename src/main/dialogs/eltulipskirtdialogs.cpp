#include "eltulipskirtdialogs.h"
namespace Elasticas
{
//___________________________________________________________
    TulipSkirtBasicDialog::TulipSkirtBasicDialog():SkirtPropertiesDialog(trUtf8("Основные"),"TulipSkirt:")
    {
        this->commonValue("Length1:Default")=50.0f;
        this->commonValue("Length1:Min")=40.0f;
        this->commonValue("Length1:Max")=70.0f;
        this->commonValue("LengthType:Default")=0;
        this->commonValue("LengthName:Default")=0;
        QString length_types[]={trUtf8("Численно"),trUtf8("По названию"),NULL};
        QString length_names[]={trUtf8("Микро-мини"),trUtf8("Укороченное мини"),trUtf8("Мини"),
                                trUtf8("Над коленом"),trUtf8("До середины колена"),trUtf8("За колено"),
                                trUtf8("До середины икры"),trUtf8("За икру"),trUtf8("До щиколотки"),
                                trUtf8("Макси"),NULL};
        length_type_cb=this->AddComboBoxProperty(trUtf8("Способ задания"),length_types,"LengthType");
        length_name_cb=this->AddComboBoxProperty(trUtf8("Длина"),length_names,"LengthName");
        length_dsb=this->AddDoubleSpinBoxProperty(trUtf8("Длина, см"),"Length1",0.1f);
        length_dsb->AddCondition(new ComboBoxCondition(length_type_cb,0));
        length_name_cb->AddCondition(new ComboBoxCondition(length_type_cb,1));
        QObject::connect(length_name_cb,SIGNAL(onChanged()),this,SLOT(onChange()));
        this->ComputeLength();
    }

    void TulipSkirtBasicDialog::ComputeLength()
    {
        QVariant & length=this->commonValue("Length");
        const Elasticas::CommonData & vars=Core::Instance()->CommonVariables();
        if(length_type_cb->GetCurrentId())
        {
            double T7=vars["T7"].toDouble(),T9=vars["T9"].toDouble(),T12=vars["T12"].toDouble();
            switch(length_name_cb->GetCurrentId())
            {
                case 0: length=T7-T12-3.0f; break; // Mic
                case 1: length=T7-T12+(T12-T9)/4.0f; break; // Smin
                case 2: length=T7-T12+(T12-T9)/2.0f; break; // Mn
                case 3: length=T7-T12+3.0f*(T12-T9)/4.0f; break; // UKn
                case 4: length=T7-T9; break; // Kn
                case 5: length=T7-T9+(T9-10.0f)/4.0f; break; // LKn
                case 6: length=T7-T9+(T9-10.0f)/2.0f; break; // Msu
                case 7: length=T7-T9+3.0f*(T9-10.0f)/4.0f; break; // Lsu
                case 8: length=T7-10.0f; break; // An
                case 9: length=T7; break; // Max
            }
        } else length=length_dsb->GetValue();
    }

    void TulipSkirtBasicDialog::apply()
    {
        this->ComputeLength();
        SkirtPropertiesDialog::apply();
    }

    void TulipSkirtBasicDialog::onChange()
    {
        qDebug()<<"hello from void TulipSkirtBasicDialog::onChanged()";
    }

//__________________________________-
    TulipSkirtDilutionDialog::TulipSkirtDilutionDialog():SkirtPropertiesDialog(trUtf8("Разведение по верхнему срезу"),"TulipSkirt:")
    {
        this->commonValue("Kr:Default")=1.5f;
        this->commonValue("Kr:Min")=1.0f;
        this->commonValue("Kr:Max")=2.24f;
        this->commonValue("Kr18:Default")=1.5f;
        this->commonValue("Kr18:Min")=1.0f;
        this->commonValue("Kr18:Max")=2.24f;
        this->commonValue("Kr_abs:Default")=5.0f;
        this->commonValue("Kr_abs:Min")=0.0f;
        this->commonValue("Kr_abs:Max")=10.0f;
        this->AddProperty(krType_cbp=new ComboBoxProperty(trUtf8("Способ задания")),"KrType");
        krType_cbp->AddItem(trUtf8("По бёдрам"));
        krType_cbp->AddItem(trUtf8("По талии"));
        krType_cbp->AddItem(trUtf8("Абсолютная величина, см"));
        kr_dbp=this->AddDoubleSpinBoxProperty(trUtf8(""),"Kr",0.01f);
        kr_dbp->AddCondition(new ComboBoxCondition(krType_cbp,0));
        kr18_dbp=this->AddDoubleSpinBoxProperty(trUtf8(""),"Kr18",0.01f);
        kr18_dbp->AddCondition(new ComboBoxCondition(krType_cbp,1));
        kr_abs_dbp=this->AddDoubleSpinBoxProperty(trUtf8(""),"Kr_abs",0.1f);
        kr_abs_dbp->AddCondition(new ComboBoxCondition(krType_cbp,2));
    }

    void TulipSkirtDilutionDialog::apply()
    {

        const CommonData & vars=Core::Instance()->CommonVariables();
        QVariant & Kr=this->commonValue("Kr"),
                 & Kr18=this->commonValue("Kr18"),
                 & Kr_abs=this->commonValue("Kr_abs");
        double T19=vars["T19"].toDouble(), P19=vars[this->dialogClass()->className()+"P19"].toDouble();
        double T18=vars["T18"].toDouble(), P18=vars[this->dialogClass()->className()+"P18"].toDouble();
        Kr=kr_dbp->GetValue();
        Kr18=kr18_dbp->GetValue();
        Kr_abs=kr_abs_dbp->GetValue();
        switch(this->commonValue("KrType").toInt())
        {
            case 0:
                Kr18=Kr.toDouble()*(T19+P19)/(T18+P18);
                break;
            case 1:
                Kr=Kr18.toDouble()*(T18+P18)/(T19+P19);
                Kr_abs=(T18+P18)*(Kr18.toDouble()-1.0f);
                break;
            case 2:
                Kr18=(Kr_abs.toDouble()/(T18+P18))+1.0f;
                break;
        }
        SkirtPropertiesDialog::apply();
    }

//_________________________________
    TulipSkirtColorButton::TulipSkirtColorButton()
    {
        this->setLayout(new QHBoxLayout);
        this->layout()->addWidget(new QLabel(trUtf8("Цвет")));
        this->layout()->addWidget(button=new QPushButton);
        QObject::connect(button,SIGNAL(released()),color_dialog=new QColorDialog,SLOT(exec()));
        QObject::connect(color_dialog,SIGNAL(colorSelected(QColor)),this,SLOT(SelectColor(QColor)));
        this->SelectColor(color_dialog->currentColor());
    }

    const QColor & TulipSkirtColorButton::Color()
    {
        return this->color;
    }

    void TulipSkirtColorButton::SelectColor(const QColor & color)
    {
        this->button->setStyleSheet("*{background-color:"+color.name()+" ; max-width:50px}");
        this->color=color;
    }
//____________________________________
    TulipSkirtMaterialDialog::TulipSkirtMaterialDialog():SkirtPropertiesDialog(trUtf8("Вид материала"), "TulipSkirt:")
    {
        ComboBoxProperty* cbp1,* cbp2;
        DoubleSpinBoxProperty* sb1, * sb2;
        CheckBoxProperty* cb1;

        this->commonValue("Kmrig:Default")=1.5f;
        this->commonValue("Kmrig:Min")=1.0f;
        this->commonValue("Kmrig:Max")=2.5f;
        this->commonValue("Kdrap:Default")=1.5f;
        this->commonValue("Kdrap:Min")=1.0f;
        this->commonValue("Kdrap:Max")=2.5f;
        this->commonValue("MaterialName:Default")=3;
        this->commonValue("HasPicture:Default")=false;


        this->AddProperty(cbp1=new ComboBoxProperty(trUtf8("Способ задания свойств")));
        cbp1->AddItem(trUtf8("Из шаблона"));
        cbp1->AddItem(trUtf8("Вручную"));

        const QString items []={trUtf8("Крепдешин"),trUtf8("Атлас"),trUtf8("Бязь"),trUtf8("Тафта"),trUtf8("Джинса"),NULL};
        cbp2=this->AddComboBoxProperty(trUtf8("Название материала"),items,"MaterialName");


        sb1=this->AddDoubleSpinBoxProperty(trUtf8("Коэффициент жёсткости"),"Kmrig",0.01f);
        sb2=this->AddDoubleSpinBoxProperty(trUtf8("Коэффициент драпируемости"),"Kdrap",0.01f);
        cb1=this->AddCheckBoxProperty(trUtf8("Рисунок"),"HasPicture");

        cbp2->AddCondition(new ComboBoxCondition(cbp1,0));
        cb1->AddCondition(new ComboBoxCondition(cbp1,0));
        sb1->AddCondition(new ComboBoxCondition(cbp1,1));
        sb2->AddCondition(new ComboBoxCondition(cbp1,1));


        properties_widget->layout()->addWidget(color_button=new TulipSkirtColorButton);
        QColor color=color_button->Color();
        this->commonValue("MatColorR")=color.redF();
        this->commonValue("MatColorG")=color.greenF();
        this->commonValue("MatColorB")=color.blueF();
    }

    void TulipSkirtMaterialDialog::apply()
    {
        QColor color=color_button->Color();
        this->commonValue("MatColorR")=color.redF();
        this->commonValue("MatColorG")=color.greenF();
        this->commonValue("MatColorB")=color.blueF();
        SkirtPropertiesDialog::apply();
    }
    //_______________________________________________________________________-
    TulipSkirtBKBasicSkewsPropertiesDialog::TulipSkirtBKBasicSkewsPropertiesDialog():SkirtPropertiesDialog(trUtf8("Основные конструктивные швы"),"TulipSkirt:")
    {
        this->InitSkirtDressBKBasicSewsProperties();
    }
    //_______________________________________________________________________
    TulipSkirtIMKBeltPropertiesDialog::TulipSkirtIMKBeltPropertiesDialog():SkirtPropertiesDialog(trUtf8("Пояс"),"TulipSkirt:")
    {
        this->InitSkirtIMKBeltProperties();
    }
};
