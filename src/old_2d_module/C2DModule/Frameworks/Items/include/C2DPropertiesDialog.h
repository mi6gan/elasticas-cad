#ifndef C2DPROPERTIESDIALOG_H
#define C2DPROPERTIESDIALOG_H

#include <QVariant>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QResizeEvent>
#include <QStandardItem>
#include <QStandardItemModel>

#include "C2DDialog.h"

class C2DPropertiesDialog: public C2DDialog
{
    Q_OBJECT
public:
    C2DPropertiesDialog( QWidget * parent );
   ~C2DPropertiesDialog();

    void addSection( QString name );
    void addString( QString property, QVariant value );

protected:
    void resizeEvent( QResizeEvent * e );

private:
    bool                 header;
    QVBoxLayout        * l;
    QTableView         * v;
    QStandardItemModel * m;

private slots:
    void closed();

};

#endif // C2DPROPERTIESDIALOG_H
