#include "circle.h"
#include "ui_circle.h"

Circle::Circle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Circle)
{
    ui->setupUi(this);
    color_1=Qt::black;
    color_2=Qt::red;
    ui->spinBox->setMaximum(50);
    ui->spinBox->setMinimum(1);
    ui->radioButton->setChecked(true);
}

Circle::~Circle()
{
    delete ui;
}

void Circle::on_pushButton_clicked()
{
    color_1=QColorDialog::getColor(Qt::black,this,"Chose color lines");
}

void Circle::on_pushButton_2_clicked()
{
    color_2=QColorDialog::getColor(Qt::red,this,"Chose color fill");
}

void Circle::load(size_t* flag,size_t* fatness,QColor* color_line,QColor* color_inside,size_t* flag_2){
    if (ui->radioButton->isChecked()) *flag=0;
    else *flag=1;
    *fatness=ui->spinBox->value();
    *color_line=color_1;
    *color_inside=color_2;
    if (ui->checkBox->isChecked()) *flag_2=1;
    else *flag_2=0;
}
