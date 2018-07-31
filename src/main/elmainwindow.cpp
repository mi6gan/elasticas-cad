#include "elmainwindow.h"
namespace Elasticas
{

MainWindow::ViewportsWidget::ViewportsWidget()
{
    this->setMinimumWidth(0);
    this->setMinimumHeight(0);
}

void MainWindow::ViewportsWidget::resizeEvent(QResizeEvent *event)
{
    this->alignViewports(event->size().width());
    QWidget::resizeEvent(event);
}

void MainWindow::ViewportsWidget::alignViewports(int width)
{
    if(width<0) width=this->width();
    int count=this->viewports.count();
    int actual_count=0;
    int j=0;
    for(int i=0;i<count;i++) if(this->viewports[i]->isVisible()) actual_count++;
    for(int i=0;i<count;i++)
    {
        if(this->viewports[i]->isVisible())
        {
            this->viewports[i]->setGeometry(j*width/actual_count,0,width/actual_count,this->height());
            j++;
        }
    }
}

void MainWindow::ViewportsWidget::addViewport(QWidget* viewport)
{
    this->viewports.push_back(viewport);
    viewport->setParent(this);
    this->alignViewports();
}

QSize MainWindow::ViewportsWidget::sizeHint() const
{
    QListIterator<QWidget*> it(viewports);
    QSize size(0,0);
    while(it.hasNext()) size+=it.next()->sizeHint();
    return size;
}

//________________________________________________________________

    int MainWindow::addTabIfNotExist(const QString & tab_name)
    {
        int i=tabs_names.indexOf(tab_name);
        if(i<0)
        {
            tabs_names.append(tab_name);
            tabs.append(new QToolBar);
            i=tabs.size()-1;
        }
        return i;
    }

    void MainWindow::addDialog(Elasticas::Dialog* dialog,const QString & tab_name)
    {
        int i=addTabIfNotExist(tab_name);
        QAction* action=tabs[i]->addAction(dialog->dialogName());
        QObject::connect(action,SIGNAL(triggered()),dialog,SLOT(exec()));
        QObject::connect(dialog,SIGNAL(commonValuesChanged()),this,SLOT(updatePlugins()));
        tab_actions_classnames[action]=dialog->dialogClass()->className();
    }

    void MainWindow::addDockDialog(Elasticas::DockDialog* dialog,const QString & tab_name)
    {
        dialog->setCurrentDockWidget(dialog_dock_widget);
        this->addDialog(dialog,tab_name);
    }

    void MainWindow::addWidgetToToolbar(QWidget* widget,const QString & tab_name,const QString & classname)
    {
        int i=addTabIfNotExist(tab_name);
        tab_actions_classnames[tabs[i]->addWidget(widget)]=classname;
    }

    void MainWindow::updateTabMenu()
    {
        QString last_tab=tab_menu->tabText(tab_menu->currentIndex());
        dialog_dock_widget->hide();
        tab_menu->clear();
        int count=tabs.size();
        QString class_name=classes_combobox->itemData(classes_combobox->currentIndex()).toString();
        const QHash< QString,Core::ObjectClass* > & classes= Core::Instance()->objectClassesHash();
        for(int i=0;i<count;i++)
        {
            QListIterator<QAction*> actions_i=tabs[i]->actions();
            int total_hidden=0;
            while(actions_i.hasNext())
            {
                QAction* action=actions_i.next();
                const QString & action_classname=tab_actions_classnames[action];
                action->setVisible(classes.contains(action_classname)&&classes[action_classname]->isEnabled()||action_classname.isEmpty());
                if(!action->isVisible())  total_hidden++;
            }
            if(total_hidden<tabs[i]->actions().size())
            {
                tab_menu->addTab(tabs[i],tabs_names[i]);
                if(last_tab==tabs_names[i]) tab_menu->setCurrentIndex(tab_menu->count()-1);
            }
        }
    }
    void MainWindow::updateMainClassesList()
    {
        QObject::disconnect(main_classes_combobox,SIGNAL(currentIndexChanged(int)));
        main_classes_combobox->clear();
        QString name;
        Core::ObjectClass* obj;
        foreach(obj,Core::Instance()->objectClasses())
        {
            const QString & class_name=obj->className();
            if(Core::Instance()->CommonVariables()[class_name+"Level"].toInt()!=-1) continue;
            name=Core::Instance()->CommonVariables()[class_name+"Name"].toString();
            if(name.isEmpty())
            {
                name=class_name;
                name.remove(':');
            }
            main_classes_combobox->addItem(name,class_name);
        }
        this->updateClassesList();
        QObject::connect(main_classes_combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateClassesList()));
    }

    void MainWindow::updateClassesList()
    {
        QObject::disconnect(classes_combobox,SIGNAL(currentIndexChanged(int)));
        classes_combobox->clear();
        CommonData & vars=Core::Instance()->CommonVariablesSafeRW();
        QList<Core::ObjectClass*> classes;
        QString main_class_name=main_classes_combobox->itemData(main_classes_combobox->currentIndex()).toString();
        vars["Dummy"]=main_class_name;
        Core::Instance()->objectClassesHash()[main_class_name]->subTreeList(classes);
        QString name;
        Core::ObjectClass* obj;
        foreach(obj,classes)
        {
            const QString & class_name=obj->className();
            if(Core::Instance()->CommonVariables()[class_name+"Level"].toInt()==-1) continue;
            name=Core::Instance()->CommonVariables()[class_name+"Name"].toString();
            if(name.isEmpty())
            {
                name=class_name;
                name.remove(':');
            }
            classes_combobox->addItem(name,class_name);
        }
        QObject::connect(classes_combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateAll()));
    }

    void MainWindow::saveLoadDialogAccepted()
    {
        if(QObject::sender()==save_dialog) Core::Instance()->saveCommonVariablesToFile(save_dialog->selectedFiles().first());
        else if(QObject::sender()==load_dialog)
        {
            Core::Instance()->loadCommonVariablesFromFile(load_dialog->selectedFiles().first());
            int i=this->classes_combobox->currentIndex();
            int ni=this->classes_combobox->findData(Core::Instance()->commonVariables()["CurrentGarment"].toString()+":");
            if(i!=ni&&ni>=0) this->classes_combobox->setCurrentIndex(ni);
            else this->updatePlugins();
        }
    }

    void MainWindow::loadPlugins()
    {

        QStringList files=QDir("./modules").entryList(QDir::Files);
        #ifdef Q_WS_WIN
            files.filter("*.dll");
        #else
            #ifdef Q_WS_X11
                files.filter("*.so");
            #endif
        #endif
        int total=files.size();
        typedef Plugin* (*EntryFunction)();
        for(int a=0;a<total;a++)
        {
            QLibrary lib("modules/"+files[a]);
            if(!lib.load()) { QMessageBox(QMessageBox::Warning,"Error","Couldn't load module"+files[a]+": "+lib.errorString()).exec(); continue;}
            EntryFunction GetPlugin = (EntryFunction) lib.resolve("GetPlugin");

            if(!GetPlugin) QMessageBox(QMessageBox::Warning,"Error","Couldn't load module "+files[a]).exec();
            else
            {
                Elasticas::Plugin* plugin=GetPlugin();
                plugins.append(plugin);
                QListIterator<QWidget*> viewports_it(plugin->viewportsList());
                while(viewports_it.hasNext())
                {
                    this->central_widget->addViewport(viewports_it.next());
                }
                QListIterator<QPair<Elasticas::DockDialog*,QString > > dock_dialogs_it(plugin->dockDialogs());
                while(dock_dialogs_it.hasNext())
                {
                    const QPair<Elasticas::DockDialog*,QString > & pair=dock_dialogs_it.next();
                    this->addDockDialog(pair.first,pair.second);
                }
                QListIterator<QPair<Elasticas::Dialog*,QString > >  dialogs_it(plugin->dialogsList());
                while(dialogs_it.hasNext())
                {
                    const QPair<Elasticas::Dialog*,QString > & pair=dialogs_it.next();
                    this->addDialog(pair.first,pair.second);
                }
                QListIterator<QPair<QAction*,QString > >  actions_it(plugin->actionsList());
                while(actions_it.hasNext())
                {
                    const QPair<QAction*,QString > & pair=actions_it.next();
                    int i=addTabIfNotExist(trUtf8("Устаревшие диалоги"));
                    tabs[i]->addAction(pair.first);
                    tab_actions_classnames[pair.first]=pair.second;
                }
            }
         }
    }

    void MainWindow::updatePlugins()
    {
        CommonData & vars=Core::Instance()->CommonVariablesSafeRW();
        const QString & class_name=classes_combobox->itemData(classes_combobox->currentIndex()).toString();
        QString garment_name=class_name;
        garment_name.remove(':');

        vars["LastGarment"]=vars["CurrentGarment"];
        vars["LastSkirtType"]=vars["SkirtType"];
        vars["SkirtType"]=garment_name;
        vars["CurrentGarment"]=garment_name;

        if(Core::Instance()->objectClassesHash().contains(current_classname)) Core::Instance()->objectClassesHash()[current_classname]->setEnabled(false);
        if(Core::Instance()->objectClassesHash().contains(class_name)) Core::Instance()->objectClassesHash()[class_name]->setEnabled(true);
        current_classname=class_name;
        QListIterator<Elasticas::Plugin*> it(plugins);
        while(it.hasNext())
        {
            Elasticas::Plugin* p=it.next();
            p->update();
            p->Update(); // to remove in feature
        }
        QHashIterator< QString,Core::ObjectClass* > it2(Core::Instance()->objectClassesHash());
        while(it2.hasNext())
        {
            it2.next();
            if(it2.value()->isEnabled()) it2.value()->changed=false;
        }
        vars[class_name+"Changed"]=false;
    }

    void MainWindow::updateAll()
    {
        const CommonData & vars=Core::Instance()->CommonVariables();
        QString next_garment=classes_combobox->itemData(classes_combobox->currentIndex()).toString().remove(":");
        QString current_garment=vars["CurrentGarment"].toString();
        //if(next_garment!=current_garment) Core::Instance()->objectClassesHash()[vars["Dummy"].toString()]->setChanged(true);
        updatePlugins();
        updateTabMenu();
        this->central_widget->alignViewports();
    }

    MainWindow::MainWindow()
    {
        this->setWindowTitle(trUtf8("3D-эскиз"));

        tab_menu=new QTabWidget;

        dialog_dock_widget=new QDockWidget;
        this->addDockWidget(Qt::LeftDockWidgetArea,dialog_dock_widget);


        QDockWidget* menu_dockwidget=new QDockWidget(trUtf8("Главное меню"));
        menu_dockwidget->setStyleSheet("*{font-weight:bold;}");
        menu_dockwidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        menu_dockwidget->setWidget(tab_menu);
        tab_menu->setStyleSheet("*{font-weight:normal;}");
        this->addDockWidget(Qt::TopDockWidgetArea,menu_dockwidget);

        central_widget=new ViewportsWidget;
        this->setCentralWidget(central_widget);

        //this->addDockDialog(new ManikinRPDialog,trUtf8("Манекен"));
        //------------dialogs------------
        //this->addWidgetToToolbar(new QLabel(trUtf8("Пол")),trUtf8("Основные параметры"));
        this->addWidgetToToolbar(save_button=new QPushButton(trUtf8("Сохранить")),trUtf8("Файл"));
        this->addWidgetToToolbar(load_button=new QPushButton(trUtf8("Загрузить")),trUtf8("Файл"));
        save_dialog=new QFileDialog;
        save_dialog->setAcceptMode(QFileDialog::AcceptSave);
        save_dialog->setFileMode(QFileDialog::AnyFile);
        save_dialog->setNameFilter("El3d files (*.e3d)");
        save_dialog->setDefaultSuffix("e3d");
        QObject::connect(save_button,SIGNAL(released()),save_dialog,SLOT(exec()));
        QObject::connect(save_dialog,SIGNAL(accepted()),this,SLOT(saveLoadDialogAccepted()));
        load_dialog=new QFileDialog;
        load_dialog->setAcceptMode(QFileDialog::AcceptOpen);
        load_dialog->setFileMode(QFileDialog::AnyFile);
        load_dialog->setNameFilter("El3d files (*.e3d)");
        QObject::connect(load_button,SIGNAL(released()),load_dialog,SLOT(exec()));
        QObject::connect(load_dialog,SIGNAL(accepted()),this,SLOT(saveLoadDialogAccepted()));
        this->addWidgetToToolbar(main_classes_combobox=new QComboBox,trUtf8("Основные параметры"));
        this->addWidgetToToolbar(new QLabel(trUtf8("Изделие")),trUtf8("Основные параметры"));
        this->addWidgetToToolbar(classes_combobox=new QComboBox,trUtf8("Основные параметры"));
        classes_combobox->setMinimumWidth(150);



        this->addDockDialog(new FakeManikinRPDialog,trUtf8("Основные параметры"));
        this->addDockDialog(new FakeRP1,trUtf8("Основные параметры"));
        this->addDockDialog(new PantsBKBasicPropertiesDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new PantsIMKBeltPropertiesDialog,trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new PantsIMKClaspPropertiesDialog,trUtf8("Параметры ИМК/ИМФ"));

        this->addDockDialog(new FakeSkirtDressDialog("ComplexSkirt:"),trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new FakeSkirtDressDialog("ComplexDress:"),trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new FakeSkirtDressDialog("ComplexBlouse:"),trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new FakeSkirtDressDialog("ComplexBlouse:",trUtf8("Форма рукава"),true),trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new FakeSkirtDressDialog("ComplexDress:",trUtf8("Форма рукава"),true),trUtf8("Параметры ИМК/ИМФ"));


        const QString skirt_names[]={"StraightSkirt:","ComplexSkirt:"};
        for(int i=0;i<2;i++)
        {
            this->addDockDialog(new StraightSkirtBKBasicPropertiesDialog(skirt_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new StraightSkirtBKBasicSkewsPropertiesDialog(skirt_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new SkirtRP(skirt_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new StraightSkirtIMKBeltPropertiesDialog(skirt_names[i]),trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new StraightSkirtIMKClaspPropertiesDialog(skirt_names[i]),trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new SkirtDressIMKNarrowingPropertiesDialog((skirt_names[i])),trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new StraightSkirtIMKVentPropertiesDialog(skirt_names[i]),trUtf8("Параметры ИМК/ИМФ"));
        }

        /*
        this->addDockDialog(new FlaredSkirtBKBasicPropertiesDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new FlaredSkirtBKBasicSkewsPropertiesDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new SkirtRP("FlaredSkirt:"),trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new FlaredSkirtIMKBeltPropertiesDialog,trUtf8("Параметры ИМК/ИМФ"));
        this->addDockDialog(new FlaredSkirtIMKClaspPropertiesDialog,trUtf8("Параметры ИМК/ИМФ"));*/
        const QString dress_names[]={"Dress:","ComplexDress:"};
        for(int i=0;i<2;i++)
        {
            this->addDockDialog(new DressBKBasicPropertiesDialog(dress_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new DressBKBasicSkewsPropertiesDialog(dress_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new DressRP(dress_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new DressMKNeckDialog(dress_names[i]),trUtf8("Параметры МК/МФ"));
            this->addDockDialog(new DressIMKClaspPropertiesDialog(dress_names[i]),trUtf8("Параметры МК/МФ"));
            this->addDockDialog(new DressGoresDialog(dress_names[i]),trUtf8("Параметры ИМК/ИМФ"));
            //this->addDockDialog(new JacketBKBasicDialog,trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new SkirtDressIMKNarrowingPropertiesDialog(dress_names[i]),trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new DressIMKVentPropertiesDialog(dress_names[i]),trUtf8("Параметры ИМК/ИМФ"));
        }
        this->addDockDialog(new IMF1_10Dialog,trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new IMF4_4Dialog,trUtf8("Параметры МК/МФ"));

/*
        this->addDockDialog(new TulipSkirtBasicDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new TulipSkirtBKBasicSkewsPropertiesDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new TulipSkirtDilutionDialog,trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new TulipSkirtMaterialDialog,trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new TulipSkirtIMKBeltPropertiesDialog,trUtf8("Параметры ИМК/ИМФ"));
*/

        //this->addDockDialog(new DressGorlovina,trUtf8("Параметры МК/МФ"));
        //this->addDockDialog(new DressVorotDialog,trUtf8("Параметры МК/МФ"));

        this->addDockDialog(new JacketBKBasicDialog,trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new JacketRP(trUtf8("Прибавки")),trUtf8("Параметры БК/БФ"));

        fake_button1=new QPushButton(trUtf8("Карманы")); fake_button2=new QPushButton(trUtf8("Пуговицы"));
        this->addWidgetToToolbar(fake_button1,trUtf8("Параметры БК/БФ"),"Jacket:");
        this->addWidgetToToolbar(fake_button2,trUtf8("Параметры БК/БФ"),"Jacket:");
        fake_button1->setCheckable(true);
        fake_button2->setCheckable(true);
        QObject::connect(fake_button1,SIGNAL(pressed()),this,SLOT(fakeButton12()));
        QObject::connect(fake_button2,SIGNAL(pressed()),this,SLOT(fakeButton12()));

        //this->addDockDialog(new JacketRP(trUtf8("Прибавки")),trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new JacketCollarDialog,trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new JacketVentDialog,trUtf8("Параметры МК/МФ"));
        //this->addDockDialog(new JacketPocketsDialog,trUtf8("Параметры МК/МФ"));
        //this->addDockDialog(new JacketMKFormDialog,trUtf8("Параметры МК/МФ"));
        //this->addDockDialog(new JacketMKNeckDialog,trUtf8("Параметры МК/МФ"));
        //this->addDockDialog(new JacketRP,trUtf8("Параметры МК/МФ"));
        const QString blouse_names[]={"Blouse:","ComplexBlouse:"};
        for(int i=0;i<2;i++)
        {
            this->addDockDialog(new BlouseBKBasicDialog(blouse_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new BlouseRP(blouse_names[i]),trUtf8("Параметры БК/БФ"));
            this->addDockDialog(new DressIMKVentPropertiesDialog(blouse_names[i]),trUtf8("Параметры ИМК/ИМФ"));
            this->addDockDialog(new BlouseMKFormDialog(blouse_names[i]),trUtf8("Параметры МК/МФ"));
            this->addDockDialog(new BlouseMKNeckDialog(blouse_names[i]),trUtf8("Параметры МК/МФ"));
            this->addDockDialog(new BlouseRP(blouse_names[i]),trUtf8("Параметры МК/МФ"));
        }
        this->addDockDialog(new dressdialog,trUtf8("Новые диалоги"));
        this->addDockDialog(new skirtdialog,trUtf8("Новые диалоги"));


        //------------dialogs------------

        this->addDockDialog(new FakeAllowanceDialog("Blouse:"),trUtf8("Отладка"));
        this->addDockDialog(new FakeAllowanceDialog("Dress:"),trUtf8("Отладка"));
        this->addDockDialog(new DebugWomanDialog,trUtf8("Отладка"));
        this->addDockDialog(new DebugWomanDialog("Man:"),trUtf8("Отладка"));
        this->addDockDialog(new SkirtDebugDialog(trUtf8("Юбка"),"ComplexDress:"),trUtf8("Отладка"));
        this->addDockDialog(new BlouseDebugDialog(trUtf8("Блузка"),"ComplexDress:"),trUtf8("Отладка"));
        this->addDockDialog(new BlouseDebugDialog(trUtf8("Блузка"),"ComplexBlouse:"),trUtf8("Отладка"));
        this->addDockDialog(new SkirtDebugDialog(trUtf8("Юбка"),"ComplexSkirt:"),trUtf8("Отладка"));

/*/ FAKE
        this->addDockDialog(new DockDialog(trUtf8("РП манекена"),"Man:"),trUtf8("Основные параметры"));

        this->addDockDialog(new DockDialog(trUtf8("Основные"),"Jacket:"),trUtf8("Параметры БК/БФ"));
        this->addDockDialog(new DockDialog(trUtf8("Прибавки"),"Jacket:"),trUtf8("Параметры БК/БФ"));

        this->addDockDialog(new DockDialog(trUtf8("Вытачки"),"Jacket:"),trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new DockDialog(trUtf8("Шлицы"),"Jacket:"),trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new DockDialog(trUtf8("Горловина"),"Jacket:"),trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new DockDialog(trUtf8("Воротник"),"Jacket:"),trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new DockDialog(trUtf8("Застёжка"),"Jacket:"),trUtf8("Параметры МК/МФ"));
        this->addDockDialog(new DockDialog(trUtf8("Карманы"),"Jacket:"),trUtf8("Параметры МК/МФ"));
 /*/
        CommonData & vars=Core::Instance()->CommonVariablesSafeRW();
        vars["Changed"]=true;
        //this->gender=vars["Dummy:Gender"].toInt();
        this->loadPlugins();
        this->updateMainClassesList();
        int i;
        if((i=classes_combobox->findData("Dummy:"))>-1)
        {
            classes_combobox->insertItem(0,classes_combobox->itemText(i),classes_combobox->itemData(i));
            classes_combobox->removeItem(i+1);
            classes_combobox->setCurrentIndex(0);
        }
        this->updateAll();
        int i0=tabs_names.indexOf("Параметры ИМК/ИМФ"),i1=tabs_names.indexOf("Параметры МК/МФ");
        if(i0>=0&&i1>=0&&i0>i1) tabs_names.swap(i0,i1);
    }

    void MainWindow::fakeButton12()
    {
        QPushButton* button=(QPushButton*)QObject::sender();
        if(button==fake_button1) Core::Instance()->CommonVariablesSafeRW()["Jacket:fake1"]=!button->isChecked();
        else Core::Instance()->CommonVariablesSafeRW()["Jacket:fake2"]=!button->isChecked();
        Core::Instance()->CommonVariablesSafeRW()["Jacket:Changed"]=true;
        Core::Instance()->classByName("Jacket:")->setChanged(true);
        this->updatePlugins();
    }
}
