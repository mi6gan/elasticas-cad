#ifndef ELRPDIALOGS_H
#define ELRPDIALOGS_H
#include "elcore/elbasicdialogs.h"
#include <QTextStream>
#include <QScrollArea>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QFileDialog>

namespace Elasticas
{
    class RPDialog: public DockDialog
    {
        Q_OBJECT
        bool inited;
        static QList<RPDialog*> rpdialogs;
        protected:
            QSqlDatabase database;
        public:
            RPDialog(const QString & dialog_name,const QString & object_class="Dummy:",const QString & database_name="");
            virtual void apply();
    };

    class NewRPDialog: public DockDialog
    {
        public:
            NewRPDialog(const QString & dialog_name,const QString & object_class);
            //
    };

    class ManikinRPDialog: public RPDialog
    {
        Q_OBJECT
         QVector<QPair<QLabel*,QComboBox*> > properties;
         QVector<QWidget*> widgets;
    //     QWidget* widget;
         QCheckBox*  chest_relief;
         QDoubleSpinBox* alpha_spinbox,* beta_spinbox;
         void FillCombobox(int i);
        public:
         ManikinRPDialog();
         virtual void apply();
         virtual void reject();
         virtual void reset();
        private slots:
         void PropertyChanged(const QString & value);
    };

    class FakeManikinRPDialog: public RPDialog
    {
        QDoubleSpinBox* rp_spinboxes[3];
        QSpinBox* spinbox;
        QComboBox* gender_combobox;
        void recomputeVariableValues();
    public:
        FakeManikinRPDialog();
        virtual void apply();
        virtual void reject();
        virtual void reset();
    };

    class TableRPDialog:public RPDialog
    {
            Q_OBJECT
            QWidget* rp_table;
            bool table_generated;
           protected:
            struct DLL_DECLSPEC table_element
            {
                QString no,name1,name2,add_name1,add_name2;
                table_element(const QString & no,const QString & name1,const QString & name2,const QString & add_name1="",const QString & add_name2="");
            };
            QList<table_element> rows;
            void GenerateTable();
            void privateReset(bool from_global);
           public:
            TableRPDialog(const QString & object_class="Alt:",const QString & dialog_name=trUtf8("Размерные признаки"));
           public slots:
            virtual void apply();
            virtual void reject();
            virtual void reset();
    };

    class DebugWomanDialog: public PropertiesDialog
    {
        Q_OBJECT
        QPushButton* save_button,* load_button;
        QFileDialog* load_file_dialog;
        QList<QString> pnames;
    public:
        DebugWomanDialog(const QString & class_name="Woman:");
    private slots:
        void loadFromFile();
    };

    class DressRP:public TableRPDialog
    {
           public:
               DressRP(const QString & class_name);
    };

    class BlouseRP:public TableRPDialog
    {
           public:
               BlouseRP(const QString & class_name);
    };

    class JacketRP:public TableRPDialog
    {
           public:
               JacketRP(const QString & dialog_name=trUtf8("Размерные признаки"));
    };

    class SkirtRP:public TableRPDialog
    {
           public:
               SkirtRP(const QString & object_class);
    };

    class FakeRP1: public PropertiesDialog
    {
    public:
        FakeRP1();
    };
}

#endif // ELRPDIALOGS_H
