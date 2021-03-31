#include "winfilter.h"
#include "ui_winfilter.h"

winfilter::winfilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winfilter)
{
    ui->setupUi(this);
    ui->comboBox->addItem("R");
    ui->comboBox->addItem("G");
    ui->comboBox->addItem("B");
    ui->radioButton->setChecked(true);
}

winfilter::~winfilter()
{
    delete ui;
}

void winfilter::load(QString* comp,size_t* num){
    if (ui->radioButton->isChecked())*num=255;
    else *num=0;
    *comp=ui->comboBox->currentText();
    return;
}
