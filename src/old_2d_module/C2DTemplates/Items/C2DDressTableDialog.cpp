#include "C2DDressTableDialog.h"
/*
DressRP2::DressRP2():TableRPDialog("Dress:")
{
       rows.push_back(table_element("13",trUtf8("Сш"),trUtf8("Полуобхват шеи"),trUtf8("Пшгс"),"Pshgs"));
       rows.push_back(table_element("15",trUtf8("Сг2"),trUtf8("Полуобхват груди второй"),trUtf8("Пг2"),"Pg2"));
       rows.push_back(table_element("18",trUtf8("Ст"),trUtf8("Полуобхват талии"),trUtf8("Пт"),"Pt"));
       rows.push_back(table_element("19",trUtf8("Сб"),trUtf8("Полуобхват бёдер с учётом выступа живота"),trUtf8("Пб"),"Pb"));
       rows.push_back(table_element("31",trUtf8("Шп"),trUtf8("Ширина плечевого ската"),trUtf8("Пш.пл"),"Pshpl"));
       rows.push_back(table_element("35'",trUtf8("Вг1"),trUtf8("Высота груди от точки основания шеи"),trUtf8("Пвг"),"Pvg"));
       rows.push_back(table_element("35''",trUtf8("Вг2"),trUtf8("Высота груди вторая")));
       rows.push_back(table_element("39",trUtf8("Впрз"),trUtf8("Расстояние проймы зада"),trUtf8("Ппрз"),"Pprz"));
       rows.push_back(table_element("40",trUtf8("Дтс"),trUtf8("Длина спины до талии с учётом выступа лопаток")));
       rows.push_back(table_element("43",trUtf8("Дтс1"),trUtf8("Расстояние от линии талии до точки осования шеи"),trUtf8("Пдтс"),"Pdts"));
       rows.push_back(table_element("45",trUtf8("Шг"),trUtf8("Ширина груди")));
       rows.push_back(table_element("45'",trUtf8("Шгб"),trUtf8("Ширина груди большая"),trUtf8("Пшп"),"Pshp"));
       rows.push_back(table_element("46",trUtf8("Цг"),trUtf8("Расстояние между сосковыми точками"),trUtf8("Пцг"),"Pcg"));
       rows.push_back(table_element("47",trUtf8("Шс"),trUtf8("Ширина спины"),trUtf8("Пшс"),"Pshs"));
       rows.push_back(table_element("61",trUtf8("Дтп1"),trUtf8("Длина талии спереди от точки основания шеи"),trUtf8("Пдтп"),"Pdtp"));
       rows.push_back(table_element("200",trUtf8("Y"),trUtf8("Угол наклона плеча, градусы")));
       this->Reset();
}
*/
void C2DDressTableDialog::addHorizontalItems( QVariantList * list )
{
    if(table)
    {
        int j=0;
        j=table->rowCount();
        table->insertRow(j);
        table->setCellWidget(j,0, new QLabel(list->at(0).toString()));
        table->setCellWidget(j,1, new QLabel(list->at(1).toString()));
        table->setCellWidget(j,2, new QLabel(list->at(2).toString()));
        table->setCellWidget(j,3, razmmain[j]);
        table->setCellWidget(j,4, new QLabel(list->at(3).toString()));
        table->setCellWidget(j,5, razmprib[j]);

        //razmmain[j]->setValue(list->at(3).toFloat());
        //razmprib[j]->setValue(list->at(5).toFloat());


    }
}

C2DDressTableDialog::C2DDressTableDialog( const QString            & name,
                                const QString            & prefix,
                                const QString            & tab,
                                QPair< QString, double >   units,
                                QWidget                  * parent )
    : C2DItemDialog( name, prefix, tab, units, parent )
{

    this->requiredVariables();

    QGridLayout * l = new QGridLayout( this );

    QTextCodec::setCodecForTr( QTextCodec::codecForName( "UTF-8" ) );

    if ( l )
    {
        table = new QTableWidget( this );

        table->setColumnCount(6);
        table->verticalHeader()->hide();
        //table->horizontalHeader()->hide();
        table->setHorizontalHeaderLabels(
            QStringList()   <<trUtf8("№")
                            <<trUtf8("Обозн.")
                            <<trUtf8("Наименование")
                            <<trUtf8("Значение")
                            <<trUtf8("Прибавка")
                            <<trUtf8("Значение"));
        table->horizontalHeader()->setResizeMode(0,QHeaderView::ResizeToContents);
        table->horizontalHeader()->setResizeMode(1,QHeaderView::ResizeToContents);
        table->horizontalHeader()->setResizeMode(2,QHeaderView::ResizeToContents);
        table->horizontalHeader()->setResizeMode(3,QHeaderView::ResizeToContents);
        table->horizontalHeader()->setResizeMode(4,QHeaderView::ResizeToContents);
        table->horizontalHeader()->setResizeMode(5,QHeaderView::ResizeToContents);
        for ( int i = 0; i <= 18; i++ )
        {
            razmmain[ i ] = new QDoubleSpinBox( this );
            razmmain[ i ]->setSingleStep(0.1f);
            razmmain[ i ]->setMinimum(-100);
            razmmain[ i ]->setMaximum(100);

            razmprib[ i ] = new QDoubleSpinBox( this );
            razmprib[ i ]->setSingleStep(0.1f);
            razmprib[ i ]->setMinimum(-100);
            razmprib[ i ]->setMaximum(100);
        }


        QVariantList sl;

        sl << "T13"         << trUtf8( "Полуобхват шеи"  )                << trUtf8( "Сш" )
           << trUtf8( "Пшгс" )                           ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T15"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст15" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T18"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст18" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T19"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст19" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T31"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст31" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T34"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст34" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T35"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст35" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T36"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст36" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T39"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст39" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T40"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст40" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T41"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст41" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T43"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст43" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T45"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст45" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T45'"        << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст45'" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T46"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст46" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T47"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст47" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T57"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст57" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T70"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст70" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();
        sl << "T76"         << trUtf8( "Полуобхват груди второй" )        << trUtf8( "Ст76" )
           << trUtf8( "Прибавка" )                       ;
        this->addHorizontalItems(&sl); sl.clear();


        l->addWidget( table, 0, 0, 2,3 );
        l->addWidget( this->top_dialog_button_box, 2, 0);
        l->addWidget( this->bottom_dialog_button_box, 3, 0);

        //l->SetMinimumSize( QSize(table->, 30) );

        //this->setSize( table->horizontalHeaderItem(0)->sizeHint()
        //+table->horizontalHeaderItem(1)->sizeHint()
        //+table->horizontalHeaderItem(2)->sizeHint() );
        this->Reset();
        this->Apply();
    }
    this->setLayout( l );

}

void C2DDressTableDialog::Apply()
{
    rmain.clear();
    rprib.clear();
    for ( int i = 0; i <= 18; i++ )
    {
        rmain.append(razmmain[i]->value());
        rprib.append(razmprib[i]->value());
    }


    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T13" ), QVariant( this->rmain.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T15" ), QVariant( this->rmain.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T18" ), QVariant( this->rmain.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T19" ), QVariant( this->rmain.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T31" ), QVariant( this->rmain.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T34" ), QVariant( this->rmain.at( 5 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T35" ), QVariant( this->rmain.at( 6 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T36" ), QVariant( this->rmain.at( 7 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T39" ), QVariant( this->rmain.at( 8 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T40" ), QVariant( this->rmain.at( 9 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T41" ), QVariant( this->rmain.at( 10) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T43" ), QVariant( this->rmain.at( 11) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T45" ), QVariant( this->rmain.at( 12) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T45'"), QVariant( this->rmain.at( 13) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T46" ), QVariant( this->rmain.at( 14) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T47" ), QVariant( this->rmain.at( 15) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T57" ), QVariant( this->rmain.at( 16) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T70" ), QVariant( this->rmain.at( 17) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "T76" ), QVariant( this->rmain.at( 18) ) );

    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT13" ), QVariant( this->rprib.at( 0 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT15" ), QVariant( this->rprib.at( 1 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT18" ), QVariant( this->rprib.at( 2 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT19" ), QVariant( this->rprib.at( 3 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT31" ), QVariant( this->rprib.at( 4 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT34" ), QVariant( this->rprib.at( 5 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT35" ), QVariant( this->rprib.at( 6 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT36" ), QVariant( this->rprib.at( 7 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT39" ), QVariant( this->rprib.at( 8 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT40" ), QVariant( this->rprib.at( 9 ) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT41" ), QVariant( this->rprib.at( 10) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT43" ), QVariant( this->rprib.at( 11) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT45" ), QVariant( this->rprib.at( 12) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT45'"), QVariant( this->rprib.at( 13) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT46" ), QVariant( this->rprib.at( 14) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT47" ), QVariant( this->rprib.at( 15) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT57" ), QVariant( this->rprib.at( 16) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT70" ), QVariant( this->rprib.at( 17) ) );
    this->values.insert( QString( "%1%2" ).arg( this->prefix() ).arg( "PT76" ), QVariant( this->rprib.at( 18) ) );

    this->transmitData( this->values );
}

void C2DDressTableDialog::Reject()
{
    if ( ( this->rmain.isEmpty() )&&( this->rprib.isEmpty() ) )
        this->Reset();
    else
    {
        for ( int i = 0; i <= 18; i++ )
        {
            razmmain[i]->setValue( rmain.at(i) );
            razmprib[i]->setValue( rprib.at(i) );
        }
    }
}

void C2DDressTableDialog::Reset()
{
    Unicus::console("T77777777777777",D("T15"));
    QList< double > s2;
    s2 << 14.9f  << 36.8f  << 47.5f/2 << 66.0f/2 << 11.85f    << 20.8f  << 28.65f
       << 44.25 << 14.7f  << 35.55f  << 37.7f  << 37.5f   << 13.6f << 27.8f/2
       << 7.95f << 14.75f  << 7.55f    << 80.55f   << 6.6f;
    for ( int i = 0; i <= 18; i++ )
    {
        razmmain[i]->setValue( s2.at(i) );
        razmprib[i]->setValue( 0 );
    }
}

QList< QList< double > > C2DDressTableDialog::defaults()
{
    this->Reset();
}

void C2DDressTableDialog::requiredVariables()
{
    this->addVariable( C2DVariable::set( "T1", "T1", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 10.0f ) );

    this->addVariable( C2DVariable::set( "T15", "Alt:T15", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
  //  this->addVariable( C2DVariable::set( "T16", "T16", "Not described", C2DVariable::Metrics,
  //                     C2DVariable::General, 1000.0f, 0.5*10.0f ) );

    this->addVariable( C2DVariable::set( "T18", "Alt:T18", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 0.5f ) );

    this->addVariable( C2DVariable::set( "T19", "Alt:T19", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 0.5f ) );

    this->addVariable( C2DVariable::set( "T31", "Alt:T31", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T34", "T34", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T35", "T35", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T36", "T36", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T39", "Alt:T39", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T40", "Alt:T40", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T41", "T41", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 0.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T43", "Alt:T43", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );
    this->addVariable( C2DVariable::set( "T45", "Alt:T45", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T45'", "Alt:T45'", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 0.5f ) );

    this->addVariable( C2DVariable::set( "T46", "Alt:T46", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T47", "Alt:T47", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T57", "T57", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T70", "T70", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    this->addVariable( C2DVariable::set( "T76", "T76", "Not described", C2DVariable::Metrics,
                       C2DVariable::General, 1000.0f, 1.0f ) );

    //double my = Elasticas::Core::Instance()->CommonVariables()["T13"].toDouble();
    //Unicus::console("my",my);
}
