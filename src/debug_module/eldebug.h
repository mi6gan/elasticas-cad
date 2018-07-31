#include <QHash>
#include <QRegExp>
#include <QLineEdit>
#include <QTableView>
#include <QToolBar>
#include <QDialog>
#include <QAction>
#include <QtGui/QHeaderView>
#include <QtGui/QStandardItemModel>
#include <QDialogButtonBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include "elcore/elplugin.h"
#include "elcore/elbasicdialogs.h"
#include <QTextEdit>


class DebugDialog: public Elasticas::DockDialog
{
    Q_OBJECT
    QList<QLabel*> var_labels;
    QList<QLineEdit*> var_text;
    QLineEdit* pattern_edit;
    QGridLayout* prop_layout;
public:
    DebugDialog(const QString &dialog_name);
    virtual void reject();
    virtual void apply();
private:
    void updateVariablesList();
private slots:
    void patternChanged(const QString & text);
    void addVariable();
};

class DebugOut:public QDialog
{
    Q_OBJECT

    QStandardItemModel * debug_model;
    QTableView * debug_table;
    QLineEdit * search_string;
    QDialogButtonBox* buttons;
    QHash<QString, QVariant> list;

    void GenerateTable( bool search_pattern = false );
    public:
     DebugOut();
    private slots:
     void Update();
     void Search();
};

class DebugPlugin:public Elasticas::Plugin
{
    DebugOut* debug_dialog;
    QToolBar* tool_bar;
    public:
     DebugPlugin();

};

class DebugRPDialog: public Elasticas::SimpleDialog
{
    Q_OBJECT
    QTableWidget* table_widget;
    QStringList variables;
    QSqlDatabase database;
public:
    DebugRPDialog();
    ~DebugRPDialog();
    //void ReadTable();
    void WriteTable();
};

extern "C" EXPORTSPEC Elasticas::Plugin* GetPlugin();
