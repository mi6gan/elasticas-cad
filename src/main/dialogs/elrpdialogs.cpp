#include "elrpdialogs.h"
namespace Elasticas
{
    QList<RPDialog*> RPDialog::rpdialogs;
    RPDialog::RPDialog(const QString & dialog_name,const QString & object_class,const QString & database_name):DockDialog(dialog_name,object_class)
    {
        inited=false;
        //this->commonValue("T1")=164.0; this->commonValue("T16")=88.0; this->commonValue("T19")=96.0;
        if(!database_name.isEmpty())
        {
            database=QSqlDatabase::addDatabase("QSQLITE",database_name);
            database.setDatabaseName(database_name);
            database.open();
            this->apply();
        }
        this->setLayout(new QVBoxLayout);
        RPDialog::rpdialogs.append(this);
    }

    void RPDialog::apply()
    {
        if(database.isValid())
        {
            QSqlQuery query(database);
            if(inited)
            {
                query.exec("SELECT * FROM sizes WHERE T1="+this->commonValue("T1").toString()+" AND T16="+this->commonValue("T16").toString()+" AND T19="+this->commonValue("T19").toString()+";");
                query.first();
                if(!query.isValid()) {query.exec("SELECT * from sizes WHERE T1="+this->commonValue("T1").toString()+";");query.first();}
            }
            if(!inited||!query.isValid()) {query.exec("SELECT * from sizes;");query.first();}
            {
                const QSqlRecord r=query.record();
                int count=r.count();
                for(int i=0;i<count;i++) this->commonValue(r.fieldName(i))=QVariant(r.value(i).toString().replace(',','.')).toDouble();
            }
            RPDialog* dialog;
            foreach(dialog,RPDialog::rpdialogs) dialog->reset();
            inited=true;
        }
        DockDialog::apply();
        this->reject();
    }

    //________________________
    NewRPDialog::NewRPDialog(const QString & dialog_name,const QString & object_class):DockDialog(dialog_name,object_class)
    {
        QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE","database.sqlite3");
        database.open();

    }

    //________________________
    FakeManikinRPDialog::FakeManikinRPDialog():RPDialog(trUtf8("Размерные признаки"),"Woman:","database.sqlite3")
    {
        QWidget* w=new QWidget;
        /*
        this->layout()->addWidget(w);
        w->setLayout(new QHBoxLayout);
        w->layout()->addWidget(gender_combobox=new QComboBox);
        gender_combobox->addItem(trUtf8("Женский"));
        gender_combobox->addItem(trUtf8("Мужской"));
        gender_combobox->addItem(trUtf8("Детский"));
        QObject::connect(gender_combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(apply()));

        w=new QWidget;
        this->layout()->addWidget(w);
        w->setLayout(new QHBoxLayout);
        w->layout()->addWidget(new QLabel(trUtf8("№")));
        w->layout()->addWidget(spinbox=new QSpinBox);
        spinbox->setValue(0);*/

        w=new QWidget;
        this->layout()->addWidget(w);
        w->setLayout(new QHBoxLayout);
        w->layout()->addWidget(new QLabel(trUtf8("Рост, см")));
        w->layout()->addWidget(rp_spinboxes[0]=new QDoubleSpinBox);
        rp_spinboxes[0]->setRange(0,1000);
        rp_spinboxes[0]->setValue(0);
        w->setEnabled(true);


        w=new QWidget;
        this->layout()->addWidget(w);
        w->setLayout(new QHBoxLayout);
        w->layout()->addWidget(new QLabel(trUtf8("Обхват груди III, см")));
        w->layout()->addWidget(rp_spinboxes[1]=new QDoubleSpinBox);
        rp_spinboxes[1]->setRange(0,1000);
        rp_spinboxes[1]->setValue(0);
        w->setEnabled(true);

        w=new QWidget;
        this->layout()->addWidget(w);
        w->setLayout(new QHBoxLayout);
        w->layout()->addWidget(new QLabel(trUtf8("Обхват бёдер, см")));
        w->layout()->addWidget(rp_spinboxes[2]=new QDoubleSpinBox);
        rp_spinboxes[2]->setRange(0,1000);
        rp_spinboxes[2]->setValue(0);
        w->setEnabled(true);

        this->layout()->addWidget(this->top_dialog_button_box);
        this->layout()->addWidget(this->bottom_dialog_button_box);

        this->recomputeVariableValues();
    }

    void FakeManikinRPDialog::recomputeVariableValues()
    {
        double T1=this->commonValue("T1").toDouble(),T16=this->commonValue("T16").toDouble(), T19=this->commonValue("T19").toDouble();
        //Минимальная длина Т7-Вят+15см
          //      Мах высота шлицы относительно низа Дизд.- (Т7-Вят+15см) Мин. высота шлицы относительно низа 10см
        this->commonValue("T110")=3.182817+0.005663*T1+0.051009*T16+0.017945*T19;
        this->commonValue("T111")=this->commonValue("T4").toDouble()+3.0f; // 96.78516+0.013019*T1+0.03402*T16+0.010071*T19;
        this->commonValue("T161-T4")=2.0f; // 0.062*T1+0.009*T16-0.031*T19-1.1553;
        this->commonValue("T113")=97.516472-0.138804*T1-0.030582*T16-0.002496*T19;
        this->commonValue("dsh_v_osn_pop")=2.666903+0.04223071+0.042253*T16-0.036623*T19;
        this->commonValue("T86")=-25.56864+0.644649*T1+0.069473*T16-0.027446*T19;
        this->commonValue("T56")=26.12695+0.048339*T1+0.063721*T16-0.07281*T19;
        this->commonValue("T56_")=23.2184+0.070918*T1+0.053348*T16-0.04953*T19;
        this->commonValue("T112")=5.778342-0.089811*T1+0.129812*T16+0.243979*T19;
        this->commonValue("T112_")=38.57189-0.09339*T1-0.08733*T16+0.065423*T19;
        //  5.778342-0.089811*T1+0.129812*T16+0.243979*T19;
        this->commonValue("Vog1")=-4.209076+0.768192*T1+0.070404*T16-0.071447*T19;
        this->commonValue("Vog2")=63.558589+0.290083*T1-0.008059*T16+0.035119*T19;
        this->commonValue("Vog3")=-3.143624+0.778478*T1-0.046705*T16-0.016920*T19;
        this->commonValue("Vog4")=63.558589+0.290083*T1-0.008059*T16+0.0351*T19;
        this->commonValue("Vlt")=-13.228334+0.815606*T1+0.020459*T16+0.01117*T19;
        this->commonValue("Vzu")=6.143179+0.735499*T1-0.009065*T16-0.046124*T19;
        this->commonValue("dpzg1")=17.56837-0.0131*T1+0.00131*T16+0.01288*T19;
        this->commonValue("dpzg2")=44.7237-0.11123*T1+0.001882*T16-0.01548*T19;
        this->commonValue("dpzg3")=37.21105-0.06788*T1-0.02315*T16-0.00533*T19;
        this->commonValue("dpzg4")=26.69406-0.02982*T1-0.01365*T16-0.01536*T19;
        this->commonValue("Gtosngj")=3.878449+0.00004*T1-0.013274*T16-0.002955*T19;
        this->commonValue("Vgj")=-6.154744+0.0015083*T1+0.101431*T16-0.018344*T19;
        this->commonValue("shgp")=27.52988+0.00454*T1+0.065803*T16-0.06994*T19;
        this->commonValue("Vpu")=-23.45092+0.923386*T1+0.012479*T16-0.11276*T19;
        this->commonValue("Vps")=-24.894073+0.626460*T1+0.071291*T16-0.100910*T19;
        this->commonValue("Vvtb")=this->commonValue("T86").toDouble()-5.0;
        this->commonValue("Pk")=this->commonValue("T74");
        this->commonValue("T85")=79.755491+0.087773*T1+0.005166*T16+0.018837*T19;
        this->commonValue("Vst")=this->commonValue("T6");
        this->commonValue("Vvtj")=79.755491+0.087773*T1+0.005166*T16+0.018837*T19;
        if (this->commonValue("Vvtj").toDouble()>this->commonValue("T7").toDouble()-2.0) this->commonValue("Vvtj")=this->commonValue("T7").toDouble()-3.0;
        this->commonValue("T78")=2.855290+0.007369*T1+0.013405*T16-0.011943*T19;
        this->commonValue("T79")=7.100081-0.030614*T1-0.060682*T16+0.099252*T19;
        this->commonValue("Vlop")=122.103-0.02185*T1+0.00789*T16-0.035296*T19;
        this->commonValue("T200")=18.0f;
        this->commonValue("T61")=this->commonValue("T36a");
        this->commonValue("T45\'")= sqrtf
                    (
                    pow(this->commonValue("T16").toDouble()/2.0f - (this->commonValue("T47").toDouble()/2.0f +this->commonValue("T109").toDouble()+this->commonValue("T46").toDouble()/2.0f),double(2.0f))
                    + pow(this->commonValue("T11").toDouble() - this->commonValue("T6").toDouble() ,double(2.0f))
                    )
                    + this->commonValue("T46").toDouble()/2.0f;
        double X=log(2.0)/log(M_PI/2.0);
             //2.0*pow(pow((*this)["T20"].toDouble()/4.0,X)-pow((*this)["T56_"].toDouble()/2.0,X),1.0/X);
        this->commonValue("K25")=(this->commonValue("T25").toDouble()-0.5)-this->commonValue("T86").toDouble();
        this->commonValue("K26")=(this->commonValue("T26").toDouble()-0.1)-this->commonValue("T86").toDouble();
    }

    void FakeManikinRPDialog::apply()
    {
        //this->commonValue("Gender")=gender_combobox->currentIndex();
        this->commonValue("T1")=rp_spinboxes[0]->value();
        this->commonValue("T16")=rp_spinboxes[1]->value();
        this->commonValue("T19")=rp_spinboxes[2]->value();
        //this->commonValue("ManId")=spinbox->value();
        this->recomputeVariableValues();
        rp_spinboxes[0]->setValue(this->commonValue("T1").toDouble());
        rp_spinboxes[1]->setValue(this->commonValue("T16").toDouble());
        rp_spinboxes[2]->setValue(this->commonValue("T19").toDouble());
        RPDialog::apply();

    }

    void FakeManikinRPDialog::reject()
    {
        this->reset();
    }

    void FakeManikinRPDialog::reset()
    {
        rp_spinboxes[0]->setValue(this->commonValue("T1").toDouble());
        rp_spinboxes[1]->setValue(this->commonValue("T16").toDouble());
        rp_spinboxes[2]->setValue(this->commonValue("T19").toDouble());
        const CommonData & vars=Core::Instance()->CommonVariables();
        QString current_garment=vars["CurrentGarment"].toString();
        /*
        gender_combobox->setEnabled(current_garment=="Dummy");
        if(gender_combobox->isEnabled()) gender_combobox->setCurrentIndex(this->commonValue("Gender").toInt());
        else gender_combobox->setCurrentIndex(vars[current_garment+":Gender"].toInt());*/
    }

    //__________________________________________________
    ManikinRPDialog::ManikinRPDialog():RPDialog(trUtf8("Размерные признаки"),"Woman:","database.sqlite3")
    {
        QHBoxLayout* lay_out;
        QString names[]={trUtf8("Рост, см"),trUtf8("Обхват груди III, см"),trUtf8("Обхват бёдер, см")};
        for(int a=0;a<3;a++)
        {
            lay_out=new QHBoxLayout;
            properties.push_back(QPair<QLabel*,QComboBox*> (new QLabel(names[a]),new QComboBox));
            widgets.push_back(new QWidget);
            widgets.last()->setLayout(lay_out);
            lay_out->addWidget(properties.last().first);
            lay_out->addWidget(properties.last().second);
            this->layout()->addWidget(widgets.last());
            this->FillCombobox(a);
        }
        QWidget* prop_widget;
        this->layout()->addWidget(prop_widget=new QWidget);
        prop_widget->setLayout(new QHBoxLayout);
        prop_widget->layout()->addWidget(new QLabel(trUtf8("Выступ грудной клетки")));
        prop_widget->layout()->addWidget(chest_relief=new QCheckBox);


        this->layout()->addWidget(new QLabel(trUtf8("Уголь сгиба руки 1")));
        this->layout()->addWidget(alpha_spinbox=new QDoubleSpinBox);
        this->layout()->addWidget(new QLabel(trUtf8("Уголь сгиба руки 2")));
        this->layout()->addWidget(beta_spinbox=new QDoubleSpinBox);
        alpha_spinbox->setRange(0,360);
        beta_spinbox->setRange(0,360);

        this->layout()->addWidget(this->top_dialog_button_box);
        this->layout()->addWidget(this->bottom_dialog_button_box);
        this->reset();
    }

    void ManikinRPDialog::PropertyChanged(const QString & value)
    {
        QComboBox* combobox=dynamic_cast<QComboBox*>(QObject::sender());
         if(combobox==properties[0].second)
        {

             FillCombobox(1);
             FillCombobox(2);
        }
        else if(combobox==properties[1].second)
        {
            //FillCombobox(1);
            FillCombobox(2);
        }
    }

    void ManikinRPDialog::apply()
    {
        commonValue("T1")=properties[0].second->currentText();
        commonValue("T16")=properties[1].second->currentText();
        commonValue("T19")=properties[2].second->currentText();
        commonValue("ChestRelief")=this->chest_relief->isChecked();
        commonValue("ArmAlpha")=alpha_spinbox->value();
        commonValue("ArmBeta")=beta_spinbox->value();
        this->updateCommonValues();
        RPDialog::apply();
    }

    void ManikinRPDialog::reject()
    {
        this->reset();
    }

    void ManikinRPDialog::reset()
    {
        const CommonData & vars=Core::Instance()->CommonVariables();
        const QString StringsOfT[]={"T1","T16","T19"};
        if(vars.contains(StringsOfT[0]))
        {
            int i;
            for(int a=0;a<3;a++)
            {
                if(a) this->FillCombobox(a);
                i=properties[a].second->findText(vars[StringsOfT[a]].toString());
                if(i>=0) properties[a].second->setCurrentIndex(i);
                else throw "int Manikin::exec(): Unexpected "+StringsOfT[a]+" value";
            }
        }
        this->chest_relief->setChecked(commonValue("ChestRelief").toBool());
    }

    void ManikinRPDialog::FillCombobox(int i)
    {/*

        QVector<double> values;
         properties[i].second->disconnect();

        if(i==0) Core::Instance()->CommonVariables().FillBaseValuesVector(values,"","T1");
        else if(i==1)//&&!properties[0].second->currentText().isEmpty())
            Core::Instance()->CommonVariables().FillBaseValuesVector(values,
                                                                         " WHERE T1="+
                                                                         properties[0].second->currentText(),
                                                                         "T16");
       else if(i==2)//&&!properties[0].second->currentText().isEmpty()&&!properties[1].second->currentText().isEmpty())
            Core::Instance()->CommonVariables().FillBaseValuesVector(values,
                                                                         " WHERE T1="+
                                                                         properties[0].second->currentText()+
                                                                         " AND T16="+
                                                                         properties[1].second->currentText(),
                                                                         "T19");
        int size=values.size();
        properties[i].second->clear();
       for(int a=0;a<size;a++) properties[i].second->addItem(QString().setNum(values[a]));
       //properties[i].second->setCurrentIndex(0);
       QObject::connect( properties[i].second,SIGNAL(currentIndexChanged(QString)),this,SLOT(PropertyChanged(QString)));*/
    }
    //________________________________________________
    DebugWomanDialog::DebugWomanDialog(const QString & class_name):PropertiesDialog(trUtf8("РП"),class_name)
    {
        if(class_name=="Woman:") pnames<<"1g"<<"1r"<<"1r'"<<"1s"<<"2''r"<<"2g"<<"2r"<<"2r'"<<"2s"<<"3g"<<"3r"<<"3r'"<<"3s"<<"3s''"<<"4r"<<"4s"<<"4s''"<<"4t"<<"5r"<<"5t"<<"6r"<<"6t"<<"7r'"<<"7t"<<"8r'"<<"8t"<<"9r'"<<"9t"<<"10r'"<<"10t"<<"11r"<<"11t"<<"12t"<<"13t"<<"14t"<<"15t";
        else pnames<<"14t"<< "15t"<< "4s''"<< "1r'"<< "2r'"<< "13t"<<"8r'"<< "6r"<< "7t"<< "12t"<<  "11r"<< "5r"<< "9t"<< "10t"<< "7r'"<< "1s"<< "1r"<< "3r'"<< "2r"<< "11t"<< "3s"<< "3r"<< "2''r"<< "2s"<< "4r"<< "4s"<< "9r'"<< "3s''"<< "10r'"<< "2g"<< "8t"<< "5t"<< "6t"<< "14t_0"<< "3g"<< "4t";
        QList<float> xvalues,yvalues,zvalues;
        if(class_name=="Woman:") {
            xvalues<<0.0<<16.0078986403<<16.0078986403<<0.0<<19.7749044137<<0.0<<14.218639769<<16.9967720914<<0.0<<0.0<<13.463655966<<17.3314893636<<0.0<<3.83760299307<<18.8696260417<<0.0<<5.46107717897<<0.0<<24.1165082187<<0.0<<21.1993227612<<0.0<<21.4930671302<<0.0<<21.4930671302<<0.0<<17.3314893636<<0.0<<14.218639769<<0.0<<18.8237120627<<0.0<<0.0<<13.4420997953<<11.3869920761<<18.9274132159;
            yvalues<<-9.12763016262<<1.93414416665<<1.93414416665<<-8.24802751787<<2.13720579333<<-15.58949183<<0.0<<-3.0814780124<<-4.55512087487<<-11.1707187781<<1.67016405196<<-1.88341441498<<1.9428970979<<-2.39674103166<<-8.07679402878<<3.45454545455<<0.0<<-11.7408830428<<-8.07679402878<<-12.4060746851<<1.67016405196<<-14.5441906779<<-10.1886349463<<-10.6005545133<<-5.96495311129<<9.78281795227<<5.2237425189<<11.0181738593<<7.35588959906<<10.4955232832<<2.13720579333<<4.41377112568<<11.065687548<<0.0<<0.0<<0.0;
            zvalues<<128.521216101<<136.691898953<<138.921558877<<143.33159417<<126.010228118<<121.631731235<<125.96616369<<127.326739993<<137.148124412<<113.316835707<<104.853580913<<105.822513728<<148.463638469<<147.462952357<<82.2487564838<<142.303030303<<140.217504399<<109.515740608<<82.1677235545<<104.764371735<<105.059526103<<94.3113602144<<80.4398103923<<81.4351505684<<79.4854207469<<134.412913503<<103.10148793<<127.618456015<<128.281129639<<121.869299678<<133.729646161<<102.673769431<<82.6705064754<<115.113053783<<104.328284956<<75.8247251048;
        }
        else {
            xvalues<<12.3825488418<<12.5905366075<<8.264391081<<0.0<<0.0<<17.3326576653<<0.0<<31.0182526481<<0.0<<0.0<<23.1563151048<<29.7703260539<<0.0<<0.0<<0.0<<0.0<<20.826852129<<0.0<<16.4591090494<<0.0<<0.0<<24.2378514864<<25.6521682932<<0.0<<23.9466686145<<0.0<<0.0<<6.64208650857<<0.0<<0.0<<0.0<<0.0<<0.0<<12.1745610761<<0.0<<0.0;
            yvalues<<0.0<<0.0<<0.0<<0.468011101076<<-4.66225783921<<0.0<<0.0129065983086<<0.0<<-10.2476312823<<11.8456236703<<0.0<<0.0<<10.3148176155<<8.65989215088<<-4.49676529275<<-11.1164671512<<0.0<<-0.0698396749218<<0.0<<4.43983221613<<0.923115603843<<0.0<<0.0<<-7.31013858258<<0.0<<3.15726498106<<9.48735488319<<0.0<<7.17045923274<<-12.9782582989<<6.88084727643<<-14.6331837635<<-14.9641688564<<0.0<<-12.8127657524<<-13.7229747579;
            zvalues<<101.897786994<<84.5932048881<<139.501975032<<138.18400119<<127.220119987<<118.120832718<<79.0204158299<<104.393640182<<82.2475204859<<82.454386169<<130.059330469<<80.7246324462<<127.923463309<<116.79408956<<79.6410128792<<142.155822305<<132.971159189<<110.050268291<<122.696563564<<97.3073422138<<145.672538917<<103.520091566<<121.573429629<<136.611821998<<80.9326202119<<140.831881933<<105.044118761<<149.402192679<<127.55110508<<119.607462849<<136.694568271<<99.7483572741<<93.5423867819<<95.7413491294<<115.387402915<<110.422626521;
        }


        this->commonValue("UseDebugRP:Default")=false;
        this->AddCheckBoxProperty(trUtf8("Включить"),"UseDebugRP");
        int size=pnames.size();
        for(int a=0;a<size;a++)
        {
            this->commonValue(pnames[a]+"_x:Default")=xvalues[a];
            this->commonValue(pnames[a]+"_y:Default")=yvalues[a];
            this->commonValue(pnames[a]+"_z:Default")=zvalues[a];
            this->AddDoubleSpinBoxProperty(pnames[a]+"_x",pnames[a]+"_x",0.1,-200,200);
            this->AddDoubleSpinBoxProperty(pnames[a]+"_y",pnames[a]+"_y",0.1,-200,200);
            this->AddDoubleSpinBoxProperty(pnames[a]+"_z",pnames[a]+"_z",0.1,-200,200);
        }
        QWidget* save_load_widget=new QWidget;
        load_file_dialog=new QFileDialog;
        load_file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
        load_file_dialog->setFileMode(QFileDialog::AnyFile);
        save_load_widget->setLayout(new QHBoxLayout);
        save_load_widget->layout()->addWidget(load_button=new QPushButton(trUtf8("Загрузить")));
        this->properties_widget->layout()->addWidget(save_load_widget);
        QObject::connect(load_button,SIGNAL(released()),load_file_dialog,SLOT(exec()));
        QObject::connect(load_file_dialog,SIGNAL(accepted()),this,SLOT(loadFromFile()));
    }

    void DebugWomanDialog::loadFromFile()
    {
        QFile file(load_file_dialog->selectedFiles().first());
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        int size;
        size=QString(file.readLine()).remove('\n').toInt();

        for(int a=0;a<size;a++) file.readLine();

        size=QString(file.readLine()).remove('\n').toInt();
        for(int a=0;a<size;a++) this->commonValue(pnames[a]+"_x")=QString(file.readLine()).remove("\n").toFloat();

        size=QString(file.readLine()).remove('\n').toInt();
        for(int a=0;a<size;a++) this->commonValue(pnames[a]+"_y")=QString(file.readLine()).remove("\n").toFloat();

        size=QString(file.readLine()).remove('\n').toInt();
        for(int a=0;a<size;a++) this->commonValue(pnames[a]+"_z")=QString(file.readLine()).remove("\n").toFloat();

        file.close();
        this->reject();
        this->apply();
    }

    //_________________________________________________
    TableRPDialog::table_element::table_element(const QString & no,const QString & name1,const QString & name2,const QString & add_name1,const QString & add_name2)
    {
        this->no=no;this->name1=name1;this->name2=name2; this->add_name1=add_name1;this->add_name2=add_name2;
    }

    TableRPDialog::TableRPDialog(const QString & object_class,const QString & dialog_name):RPDialog(dialog_name,object_class)
    {
        this->table_generated=false;
    }

    void TableRPDialog::GenerateTable()
    {
        QGridLayout* grid_layout=new QGridLayout;
        this->rp_table=new QWidget;
        this->rp_table->setLayout(grid_layout);
        int size=rows.size();
        QDoubleSpinBox* spin_box;
        QLabel * label;
        QString style="""* {text-align:center;background-color: white; border: 1px solid black;margin:0px;padding:0px;}";
        QString style1="* {text-align:center;background-color: #FFFFCC; border: 1px solid black;margin:0px;padding:0px;}";
        QString style2="* {text-align:center;background-color: white; border: 1px solid black;margin:0px;padding:0px;}";
        grid_layout->setSpacing(0);

        grid_layout->addWidget(label=new QLabel(trUtf8("№")),0,0);
        label->setStyleSheet(style1);
        grid_layout->addWidget(label=new QLabel(trUtf8("Обозн.")),0,1);
        label->setStyleSheet(style1);
        grid_layout->addWidget(label=new QLabel(trUtf8("Наименование")),0,2);
        label->setStyleSheet(style1);
        grid_layout->addWidget(label=new QLabel(trUtf8("Значение")),0,3);
        label->setStyleSheet(style1);
        grid_layout->addWidget(label=new QLabel(trUtf8("Прибавка")),0,4);
        label->setStyleSheet(style1);
        grid_layout->addWidget(label=new QLabel(trUtf8("Значение")),0,5);
        label->setStyleSheet(style1);
        for(int a=0;a<size;a++)
        {
            spin_box=new QDoubleSpinBox;
            spin_box->setMaximum(200.0);
            spin_box->setMaximumHeight(10000);
            grid_layout->addWidget(label=new QLabel(rows[a].no),a+1,0);
            label->setStyleSheet(style);
            grid_layout->addWidget(label=new QLabel(rows[a].name1),a+1,1);
            label->setStyleSheet(style);
            grid_layout->addWidget(label=new QLabel(rows[a].name2),a+1,2);
            label->setStyleSheet(style2);
            grid_layout->addWidget(spin_box,a+1,3);
            grid_layout->addWidget(label=new QLabel(rows[a].add_name1),a+1,4);
            {
                spin_box=new QDoubleSpinBox;
                spin_box->setMinimum(-100.0);
                spin_box->setMaximum(100.0);
                spin_box->setMaximumHeight(10000);
                spin_box->setEnabled(!rows[a].add_name1.isEmpty());
                grid_layout->addWidget(spin_box,a+1,5);
            }
        }
    }

    void TableRPDialog::apply()
    {
        int size=rows.size();
        QGridLayout* grid_layout=dynamic_cast<QGridLayout*>(this->rp_table->layout());
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        for(int a=0;a<size;a++)
        {
            commonValue("T"+rows[a].no)=dynamic_cast<QDoubleSpinBox*>(grid_layout->itemAtPosition(a+1,3)->widget())->value();
            if(!rows[a].add_name2.isEmpty()) this->commonValue(rows[a].add_name2)=dynamic_cast<QDoubleSpinBox*>(grid_layout->itemAtPosition(a+1,5)->widget())->value();
        }
        RPDialog::apply();
    }

    void TableRPDialog::privateReset(bool from_global)
    {
        if(!table_generated)
        {
            QScrollArea* scroll_area=new QScrollArea;
            this->GenerateTable();
            this->layout()->addWidget(scroll_area);
            scroll_area->setWidget(this->rp_table);
            scroll_area->setWidgetResizable(true);
            this->layout()->addWidget(this->top_dialog_button_box);
            this->layout()->addWidget(this->bottom_dialog_button_box);
            table_generated=true;
        }
        int size=rows.size();
        QDoubleSpinBox* spin_box,*add_spin_box;
        QGridLayout* grid_layout=dynamic_cast<QGridLayout*>(this->rp_table->layout());
        const Elasticas::CommonData & vars=Elasticas::Core::Instance()->CommonVariables();
        for(int a=0;a<size;a++)
        {
            spin_box=dynamic_cast<QDoubleSpinBox*>(grid_layout->itemAtPosition(a+1,3)->widget());
            add_spin_box=dynamic_cast<QDoubleSpinBox*>(grid_layout->itemAtPosition(a+1,5)->widget());
            if(from_global) this->commonValue("T"+rows[a].no)=vars["Woman:T"+rows[a].no];
            spin_box->setValue(this->commonValue("T"+rows[a].no).toDouble());
            if(!rows[a].add_name2.isEmpty()&&vars.contains(this->dialogClass()->className()+rows[a].add_name2)) add_spin_box->setValue(vars[this->dialogClass()->className()+rows[a].add_name2].toDouble());
        }
    }

    void TableRPDialog::reject()
    {
        this->privateReset(false);
    }

    void TableRPDialog::reset()
    {
        this->privateReset(true);
    }
    //________________________________________________________________________
    DressRP::DressRP(const QString & class_name):TableRPDialog(class_name)
    {
       rows.push_back(table_element("13",trUtf8("Сш"),trUtf8("Полуобхват шеи"),trUtf8("Пшгс"),"PT13"));
       rows.push_back(table_element("15",trUtf8("Сг2"),trUtf8("Полуобхват груди второй"),trUtf8("Пг2"),"PT15"));
       rows.push_back(table_element("18",trUtf8("Ст"),trUtf8("Полуобхват талии"),trUtf8("Пт"),"PT18"));
       rows.push_back(table_element("19",trUtf8("Сб"),trUtf8("Полуобхват бёдер с учётом выступа живота"),trUtf8("Пб"),"PT19"));
       rows.push_back(table_element("28",trUtf8("Оп"),trUtf8("Обхват плеча"),trUtf8("Поп"),"PT28"));
       rows.push_back(table_element("29",trUtf8("T29"),trUtf8("T29"),trUtf8("PT29"),"PT29"));
       rows.push_back(table_element("31",trUtf8("Шп"),trUtf8("Ширина плечевого ската"),trUtf8("Пшпг"),"PT31"));
       rows.push_back(table_element("34",trUtf8("Вг1"),trUtf8("Расстояние от т. основания шеи сзади до ОГ1"),trUtf8("PT34"),"PT34"));
       rows.push_back(table_element("35",trUtf8("Вг2"),trUtf8("Расстояние от т. основания шеи сзади до сосковой точки"),trUtf8("PT35"),"PT35"));
       rows.push_back(table_element("36",trUtf8("Дтп"),trUtf8("Расстояние от точки основания шеи сзади до линии талии спереди"),trUtf8("PT36"),"PT36"));
       rows.push_back(table_element("39",trUtf8("Впрз"),trUtf8("Расстояние от точки основания шеи сзади до заднего угла ПВ"),trUtf8("Ппз"),"PT39"));
       rows.push_back(table_element("40",trUtf8("Дтс"),trUtf8("Длина спины до талии с учётом выступа лопаток"),trUtf8("Пдтс"),"PT40"));
       rows.push_back(table_element("41",trUtf8("Впк"),trUtf8("Высота плеча косая"),trUtf8("Пвпк"),"PT41"));
       rows.push_back(table_element("43",trUtf8("Дтс1"),trUtf8("Расстояние от линии талии сзади до точки осования шеи сбоку"),trUtf8("Пдтс1"),"PT42"));
       rows.push_back(table_element("45",trUtf8("Шг"),trUtf8("Ширина груди"),trUtf8("Пшг"),"PT45"));
       rows.push_back(table_element("45'",trUtf8("Шгб"),trUtf8("Ширина груди большая"),trUtf8("Пшп"),"PT45'"));
       rows.push_back(table_element("46",trUtf8("Цг"),trUtf8("Расстояние между сосковыми точками"),trUtf8("Пцг"),"PT46"));
       rows.push_back(table_element("47",trUtf8("Шс"),trUtf8("Ширина спины"),trUtf8("Пшс"),"PT47"));
       rows.push_back(table_element("57",trUtf8("dпзр"),trUtf8("Диаметр основания руки"),trUtf8("Пшпр"),"PT57"));
       rows.push_back(table_element("70",trUtf8("Дшк"),trUtf8("Расстояние от шейной точки до колена"),trUtf8("Пди"),"PT70"));
       rows.push_back(table_element("76",trUtf8("Дшош"),trUtf8("Расстояние от т. основания шеи сзади до т. основания шеи сбоку"),trUtf8("PT76"),"PT76"));
       this->reset();
       this->apply();
    }
    //________________________________________________________________________
    BlouseRP::BlouseRP(const QString & class_name):TableRPDialog(class_name)
    {
       //rows.push_back(table_element("1",trUtf8("Р"),trUtf8("Рост"),trUtf8("Пр"),"PT1"));
       rows.push_back(table_element("13",trUtf8("Сш"),trUtf8("Полуобхват шеи"),trUtf8("Пшгс"),"PT13"));
       rows.push_back(table_element("16",trUtf8("Сг"),trUtf8("Полуобхват груди"),trUtf8("Пг"),"PT16"));
       rows.push_back(table_element("18",trUtf8("Ст"),trUtf8("Полуобхват талии"),trUtf8("Пт"),"PT18"));
       rows.push_back(table_element("19",trUtf8("Сб"),trUtf8("Полуобхват бедер"),trUtf8("Пб"),"PT19"));
       rows.push_back(table_element("28",trUtf8("Оп"),trUtf8("Обхват плеча"),trUtf8("Поп"),"PT28"));
       rows.push_back(table_element("31",trUtf8("Шпл"),trUtf8("Ширина плеча"),trUtf8("Пшпл"),"PT31"));
       rows.push_back(table_element("36",trUtf8("Дтп"),trUtf8("Длина талии спереди от Шт"),trUtf8("Пдтп"),"PT36"));
       rows.push_back(table_element("39",trUtf8("Впр.з"),trUtf8("Высота проймы сзади"),trUtf8("Пвпр.з"),"PT39"));
       rows.push_back(table_element("43",trUtf8("Дтс"),trUtf8("Длина спины до талии"),trUtf8("Пдтс"),"PT43"));
       rows.push_back(table_element("45",trUtf8("Шг"),trUtf8("Ширина груди"),trUtf8("Пшг"),"PT45"));
       rows.push_back(table_element("45'",trUtf8("Шгб"),trUtf8("Ширина груди большая"),trUtf8("Пшгб"),"PT45'"));
       rows.push_back(table_element("46",trUtf8("Цг"),trUtf8("Центр груди"),trUtf8("Пцг"),"PT46"));
       rows.push_back(table_element("47",trUtf8("Шс"),trUtf8("Ширина спины"),trUtf8("Пшс"),"PT47"));
       rows.push_back(table_element("57",trUtf8("Шпр"),trUtf8("Ширина проймы"),trUtf8("Пшпр"),"PT57"));
       rows.push_back(table_element("68",trUtf8("Дрз"),trUtf8("Длина руки до запястья"),trUtf8("Пдрз"),"PT68"));
       rows.push_back(table_element("76",trUtf8("Дгс"),trUtf8("Расстояние от Шт до Тос"),trUtf8("Пдгс"),"PT76"));
       this->reset();
       this->apply();
    }
    //________________________________________________________________________
    JacketRP::JacketRP(const QString & dialog_name):TableRPDialog("Jacket:",dialog_name)
    {
       rows.push_back(table_element("7",trUtf8("T7"),trUtf8("наименование"),trUtf8("прибавка"),"PT7"));
       rows.push_back(table_element("12",trUtf8("T12"),trUtf8("наименование"),trUtf8("прибавка"),"PT12"));
       rows.push_back(table_element("13",trUtf8("T13"),trUtf8("наименование"),trUtf8("прибавка"),"PT13"));
       rows.push_back(table_element("14",trUtf8("T14"),trUtf8("наименование"),trUtf8("прибавка"),"PT14"));
       rows.push_back(table_element("15",trUtf8("T15"),trUtf8("наименование"),trUtf8("прибавка"),"PT15"));
       rows.push_back(table_element("18",trUtf8("От"),trUtf8("Обхват талии"),trUtf8("Пот"),"PT18"));
       rows.push_back(table_element("19",trUtf8("Об"),trUtf8("Обхват бедер"),trUtf8("Поб"),"PT19"));
       rows.push_back(table_element("25",trUtf8("T25"),trUtf8("наименование"),trUtf8("прибавка"),"PT25"));
       rows.push_back(table_element("26",trUtf8("T26"),trUtf8("наименование"),trUtf8("прибавка"),"PT26"));
       rows.push_back(table_element("28",trUtf8("Оп"),trUtf8("Обхват плеча"),trUtf8("Поп"),"PT28"));
       rows.push_back(table_element("34",trUtf8("T34"),trUtf8("наименование"),trUtf8("прибавка"),"PT34"));
       rows.push_back(table_element("35",trUtf8("T35"),trUtf8("наименование"),trUtf8("прибавка"),"PT35"));
       rows.push_back(table_element("36",trUtf8("T36"),trUtf8("наименование"),trUtf8("прибавка"),"PT36"));
       rows.push_back(table_element("38",trUtf8("T38"),trUtf8("наименование"),trUtf8("прибавка"),"PT38"));
       rows.push_back(table_element("39",trUtf8("T39"),trUtf8("наименование"),trUtf8("прибавка"),"PT39"));
       rows.push_back(table_element("40",trUtf8("T40"),trUtf8("наименование"),trUtf8("прибавка"),"PT40"));
       rows.push_back(table_element("44",trUtf8("T44"),trUtf8("наименование"),trUtf8("прибавка"),"PT44"));
       rows.push_back(table_element("45",trUtf8("T45"),trUtf8("наименование"),trUtf8("прибавка"),"PT45"));
       rows.push_back(table_element("46",trUtf8("T46"),trUtf8("наименование"),trUtf8("прибавка"),"PT46"));
       rows.push_back(table_element("47",trUtf8("T47"),trUtf8("наименование"),trUtf8("прибавка"),"PT47"));
       rows.push_back(table_element("57",trUtf8("T57"),trUtf8("наименование"),trUtf8("прибавка"),"PT57"));
       this->reset();
       this->apply();
    }
//________________________________________________________________________-
    SkirtRP::SkirtRP(const QString & object_class):TableRPDialog(object_class)
    {
        rows.push_back(table_element("7",trUtf8("Влт"),trUtf8("Расстояние от шейной точки")));
        rows.push_back(table_element("18",trUtf8("От"),trUtf8("Обхват талии")));
        rows.push_back(table_element("55",trUtf8("dт"),trUtf8("Поперечный диаметр талии")));
        rows.push_back(table_element("56",trUtf8("dб"),trUtf8("Поперечный диаметр бёдер")));
        rows.push_back(table_element("79",trUtf8("Гт2"),trUtf8("Глубина талии II")));
        rows.push_back(table_element("86",trUtf8("Вят"),trUtf8("Высота ягодичной точки")));
        rows.push_back(table_element("111",trUtf8("dпзт"),trUtf8("Поперечный диаметр талии")));
        rows.push_back(table_element("112",trUtf8("dпзб"),trUtf8("Передне-задний диаметр бёдер")));
        this->reset();
        this->apply();
    }

//__________________________________________________________________________
    FakeRP1::FakeRP1():PropertiesDialog(trUtf8("Размерные признаки"),"Man:")
    {
        this->commonValue("fake1:Default")=178.0f;
        this->commonValue("fake2:Default")=90.0f;
        this->commonValue("fake3:Default")=70.0f;
        this->AddDoubleSpinBoxProperty(trUtf8("Рост, см"),"fake1",0.1f,0,250);
        this->AddDoubleSpinBoxProperty(trUtf8("Обхват груди III, см"),"fake2",0.1f,0,250);
        this->AddDoubleSpinBoxProperty(trUtf8("Обхват бёдер, см"),"fake3",0.1f,0,250);
    }
}
