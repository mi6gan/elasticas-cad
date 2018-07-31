#ifndef C2DDIALOG_H
#define C2DDIALOG_H

#include <QDialog>

class C2DDialog: public QDialog
{

    Q_OBJECT

public:

    C2DDialog( const QString & dialog_name,
               const QString & dialog_menu_tab,
               bool modal,
               QWidget * parent )
        : QDialog( parent ), dialog_tab( dialog_menu_tab )
    {
        this->setObjectName( dialog_name );
        this->setWindowTitle( this->objectName() );
        this->setModal( modal );
    }

    ~C2DDialog()  {  }

    inline const QString & tab()  {  return this->dialog_tab;  }

private:
    QString dialog_tab;
};

#endif
