#include "eldebug.h"
DebugDialog::DebugDialog(const QString &dialog_name):Elasticas::DockDialog(dialog_name)
{
    QFrame* prop_widget=new QFrame;
    QFrame* pattern_area=new QFrame;
    QPushButton* add_button=new QPushButton("+");
    pattern_area->setLayout(new QHBoxLayout);
    QScrollArea* scroll_area=new QScrollArea;
    scroll_area->setWidgetResizable(true);
    scroll_area->setWidget(prop_widget);
    this->setLayout(new QVBoxLayout);
    pattern_area->layout()->addWidget(pattern_edit=new QLineEdit);
    pattern_area->layout()->addWidget(add_button);
    this->layout()->addWidget(pattern_area);
    this->layout()->addWidget(scroll_area);
    this->layout()->addWidget(top_dialog_button_box);
    this->layout()->addWidget(bottom_dialog_button_box);

    prop_widget->setLayout(prop_layout=new QGridLayout);
    QObject::connect(pattern_edit,SIGNAL(textChanged(QString)),this,SLOT(patternChanged(QString)));
    QObject::connect(add_button,SIGNAL(released()),this,SLOT(addVariable()));
    this->updateVariablesList();
}

void DebugDialog::reject()
{
    QObject::disconnect(pattern_edit,SIGNAL(textChanged(QString)));
    pattern_edit->clear();
    QObject::connect(pattern_edit,SIGNAL(textChanged(QString)),this,SLOT(patternChanged(QString)));
    this->setVisible(false);
    this->updateVariablesList();
    this->setVisible(true);
    DockDialog::reset();
}

void DebugDialog::updateVariablesList()
{

    const Elasticas::CommonData & vars=Elasticas::Core::Instance()->commonVariables();
    int cnt=var_labels.size();
    for(int i=0;i<cnt;i++)
    {
        delete var_labels[i];
        delete var_text[i];
    }
    var_labels.clear();
    var_text.clear();
    foreach(const QString & key,vars.keys())
    {
        var_labels.append(new QLabel(key));
        var_text.append(new QLineEdit(vars[key].toString()));
        prop_layout->addWidget(var_labels.last(),var_labels.size()-1,0);
        prop_layout->addWidget(var_text.last(),var_text.size()-1,1);

    }
}

void DebugDialog::apply()
{
    int cnt=var_labels.size();
    for(int i=0;i<cnt;i++)
    {
        QVariant & v=this->commonValue(var_labels[i]->text());
        QVariant::Type type=v.type();
        v=var_text[i]->text();
        if(type!=QVariant::Invalid) v.convert(type);
    }
    Elasticas::DockDialog::apply();
}

void DebugDialog::patternChanged(const QString & text)
{
    this->update();
    if(!var_labels.size()) this->updateVariablesList();
    int cnt=var_labels.size();

    bool matches;
    this->setVisible(false);
    for(int i=0;i<cnt;i++)
    {
        matches=text.isEmpty()||QRegExp( ("*"+text+"*" ),Qt::CaseSensitive, QRegExp::Wildcard ).exactMatch(var_labels[i]->text());
        var_labels[i]->setVisible(matches);
        var_text[i]->setVisible(matches);
    }
    this->setVisible(true);
    this->pattern_edit->setFocus();
}

void DebugDialog::addVariable()
{
    this->commonValue(pattern_edit->text());
    this->updateVariablesList();
    this->patternChanged(pattern_edit->text());
}

//________________________________________
DebugOut::DebugOut()
{
    this->setWindowTitle(trUtf8("Переменные"));
    this->setMinimumWidth( 380 );
    this->setMinimumHeight( 650 );

    search_string = new QLineEdit;
    QPushButton * search_button = new QPushButton( trUtf8( "Поиск" ), this );

    debug_model = new QStandardItemModel( 0, 2, this );
    debug_table = new QTableView( this );
    debug_table->setModel( debug_model );
    debug_table->setCornerButtonEnabled( false );
    debug_table->setSortingEnabled( false );
    debug_table->setSelectionMode( QAbstractItemView::NoSelection );
    debug_table->verticalHeader()->setVisible( false );
    debug_table->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );

    buttons = new QDialogButtonBox;

    QPushButton * b_ok = buttons->addButton(trUtf8("Ок"),QDialogButtonBox::AcceptRole);
    QPushButton * b_refresh = buttons->addButton(trUtf8("Обновить"),QDialogButtonBox::ResetRole);

    QVBoxLayout * basic_layout = new QVBoxLayout;
    QHBoxLayout * search_layout = new QHBoxLayout;
    search_layout->addWidget( search_string );
    search_layout->addWidget( search_button );
    basic_layout->addLayout(search_layout);
    basic_layout->addWidget(debug_table);
    basic_layout->addWidget(buttons);
    this->setLayout(basic_layout);

    QObject::connect(search_button,SIGNAL(released()),this,SLOT(Search()));
    QObject::connect(b_ok,SIGNAL(released()),this,SLOT(accept()));
    QObject::connect(b_refresh,SIGNAL(released()),this,SLOT(Update()));

    this->GenerateTable();
}

void DebugOut::GenerateTable( bool search_pattern )
{
    this->debug_model->clear();

    QRegExp pattern;

    QStandardItem * h;
    debug_model->setHorizontalHeaderItem( 0, h = new QStandardItem( trUtf8("Переменная") ) );
    h->setEditable( false );
    debug_model->setHorizontalHeaderItem( 1, h = new QStandardItem( trUtf8("Значение") ) );
    h->setEditable( false );

    if ( search_pattern )
        pattern = QRegExp( QString( "*%1*" ).arg( search_string->text() ),
                           Qt::CaseSensitive,
                           QRegExp::Wildcard );
    else
        this->list = Elasticas::Core::Instance()->CommonVariables();

    QHashIterator< QString, QVariant > i( list );


    while( i.hasNext() )
    {
        i.next();

        if ( ( !search_pattern ) || ( search_pattern && pattern.exactMatch( i.key() ) ) )
        {
            QStandardItem * si;
            debug_model->setItem( debug_model->rowCount(), 0, si = new QStandardItem( trUtf8( i.key().toAscii() ) ) );
            si->setEditable( false );
            debug_model->setItem( debug_model->rowCount() - 1, 1, si = new QStandardItem( trUtf8( i.value().toString().toAscii() ) ) );
            si->setEditable( false );
        }
        else
            continue;

    }

}

void DebugOut::Search()
{
    this->GenerateTable( true );
}

void DebugOut::Update()
{
    this->GenerateTable();
}
//___________________________________________
DebugRPDialog::DebugRPDialog():Elasticas::SimpleDialog(new QDialog,trUtf8("РП"),"")
{
    variables<< "T1" << "T16" << "T19" << "ky141" << "kpzp16" << "Rpop5"<<"Rpop5_"<<"Rpop15"<<"Rpop16_"<<"Rpop18"<<"Rpop19_";
    variables<<"Rpzp13"<<"Rpop13_"<<"Rpzp14"<<"Rpzp16"<<"Rpzp17"<<"Rpzp18"<<"Rpzp20"<<"Rpop19"<<"Rpzp19"<<"Rpzz19";
    variables<<"Rpzz18"<<"Rpzz13"<<"Rpzp18_"<<"Rpzz161"<<"Rpzz162"<<"Rpzz16"<<"Rpzp28"<<"Rpzp28_"<<"Rpop28_"<<"hz13";
    variables<<"hb13"<<"hp13"<<"h5"<<"h5_"<<"hz161"<<"hpb15"<<"hpb15z"<<"hz16"<<"hp16"<<"hz162"<<"hp17"<<"hp18_"<<"hb18";
    variables<<"hz18"<<"hp18"<<"hp20"<<"hb19_"<<"m18"<<"m19"<<"m16"<<"m161"<<"hp14";
    table_widget=new QTableWidget(0,variables.count());
    table_widget->setHorizontalHeaderLabels(variables);
    QObject::connect(qdialog,SIGNAL(accepted()),this,SLOT(apply()));
    QObject::connect(qdialog,SIGNAL(rejected()),this,SLOT(cancel()));
    qdialog->setLayout(new QVBoxLayout);
    qdialog->layout()->addWidget(table_widget);
    database=QSqlDatabase::addDatabase("QSQLITE","debug_connection");
    database.setDatabaseName("debug_database.sqlite3");
    database.open();
    if(database.tables().contains("LUCY_DUMMY"))
    {
        QString query_string="CREATE TABLE LUCY_DUMMY (";
        QStringListIterator it(variables);
        int i=0;
        while(it.hasNext())
        {
            const QString & str=it.next();
            query_string+=str;
            if(it.hasNext()) query_string+=",";
            else
            {
                query_string+=")";
                break;
            }
        }
        database.exec(query_string);
    }
    //ReadTable();
}
/*
DebugRPDialog::ReadTable()
{
    QSqlQuery query=database.exec("SELECT * FROM LUCY_DUMMY");
    if(query.first())
        while(query.next())
        {
            table_widget->insertRow(table_widget->rowCount());
            QSqlRecord record=query.record();
            int count=record.count();
            for(int i=0;i<count;i++) table_widget->setItem();
        }

}
*/
DebugRPDialog::~DebugRPDialog()
{
    database.close();
}

//___________________________________________
DebugPlugin::DebugPlugin()
{
  //  addDialog(new DebugRPDialog,QObject::trUtf8("Отладка"));
    //addQDialog(new DebugOut,QObject::trUtf8("Отладка"));
    addDockDialog(new DebugDialog(QObject::trUtf8("Отладка")),QObject::trUtf8("Отладка"));
}
//_____________________________________________
Elasticas::Plugin* GetPlugin()
{
    return new DebugPlugin;
}

