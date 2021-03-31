#include "square.h"
#include "ui_square.h"

square::square(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::square)
{
    ui->setupUi(this);
    ui->spinBox_2->setMaximum(50);
    ui->spinBox_2->setMinimum(1);
    ui->spinBox->setMaximum(300);
    ui->spinBox->setMinimum(1);
    color_1=Qt::black;
    color_2=Qt::red;
}

square::~square()
{
    delete ui;
}

void square::on_pushButton_clicked()
{
    color_1=QColorDialog::getColor(Qt::black,this,"Chose color lines");
}

void square::on_pushButton_2_clicked()
{
    color_2=QColorDialog::getColor(Qt::black,this,"Chose color fill");
}

void square::load(size_t* l,size_t* fatness,QColor* color1,bool* flag,QColor* color2){
    *l=ui->spinBox->value();
    *fatness=ui->spinBox_2->value();
    *color1=color_1;
    if (ui->checkBox->isChecked()) *flag=true;
    else *flag=false;
    *color2=color_2;
}
