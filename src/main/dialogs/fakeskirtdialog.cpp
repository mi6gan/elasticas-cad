#include "fakeskirtdialog.h"
namespace Elasticas
{
FakeSkirtDressDialog::FakeSkirtDressDialog(const QString & classname,const QString & name,bool is_sleeve):DockDialog(name,classname)
{
    QScrollArea * scroll_area=new QScrollArea;
    this->groupbox=new QGroupBox;
    QGridLayout* grid=new QGridLayout;
    QRadioButton* button;
    QString image_filename;
    this->is_sleeve=is_sleeve;
    if(is_sleeve) image_filename="sleeve";
    else if(classname=="ComplexSkirt:") image_filename="skirt";
    else if(classname=="ComplexDress:") image_filename="dress";
    else image_filename="blouse";
    this->setLayout(new QVBoxLayout);
    groupbox->setLayout(grid);
    for(int a=1;QFileInfo("images/"+image_filename+QString().setNum(a)+".png").exists();a++)
    {
        buttons.push_back(button=new QRadioButton(""));
        //button->setMinimumHeight(256);
        button->setIcon(QIcon(QPixmap("images/"+image_filename+QString().setNum(a)+".png")));
        button->setIconSize(QSize(200,200));
        grid->addWidget(button,(a-1)/2,(a-1)%2);
    }
    if(buttons.size()) buttons.first()->setChecked(true);
    scroll_area->setWidget(groupbox);
    scroll_area->setAlignment(Qt::AlignRight);
    scroll_area->setFrameShape(QFrame::NoFrame);
    scroll_area->setWidgetResizable(true);
    this->layout()->addWidget(scroll_area);
    this->layout()->addWidget(this->top_dialog_button_box);
    this->layout()->addWidget(this->bottom_dialog_button_box);
}

void FakeSkirtDressDialog::apply()
{
    int size=buttons.size();
    int i=0;
    for(i;i<size;i++)
        if(buttons[i]->isChecked()) break;
    if(this->is_sleeve) this->commonValue("SleeveForm")=i;
    else this->commonValue("Form")=i;
    DockDialog::apply();
}



FakeAllowanceDialog::FakeAllowanceDialog(const QString & classname):PropertiesDialog(trUtf8("Прибавки"),classname)
{
    this->commonValue("TempP1:Default")=0.0;
    this->commonValue("TempP2:Default")=0.0;
    this->commonValue("TempP3:Default")=0.0;
    this->AddDoubleSpinBoxProperty(trUtf8("Прибавка спереди"),"TempP1",0.1f,-100.0f,100.0f);
    this->AddDoubleSpinBoxProperty(trUtf8("Прибавка сзади"),"TempP2",0.1f,-100.0f,100.0f);
    this->AddDoubleSpinBoxProperty(trUtf8("Прибавка сбоку"),"TempP3",0.1f,-100.0f,100.0f);
}

}
