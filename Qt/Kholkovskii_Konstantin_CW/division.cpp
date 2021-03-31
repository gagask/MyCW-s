#include "division.h"
#include "ui_division.h"
#include <QMessageBox>

Division::Division(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Division)
{
    ui->setupUi(this);
    ui->spinBox_3->setMinimum(1);
    ui->spinBox_3->setMaximum(50);
    ui->radioButton->setChecked(true);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(50);
    ui->spinBox_2->setMinimum(1);
    ui->spinBox_2->setMaximum(50);
    color=Qt::black;
    file_path = "/home/gagask/CoursWork";
}

Division::~Division()
{
    delete ui;
}

void Division::load(int *n, int *m, QColor *color,int* fatness, bool *flag,QString* path)
{
    if(ui->radioButton->isChecked()) *flag = true;
    else *flag = false;
    *n=ui->spinBox_2->value();
    *m=ui->spinBox->value();
    *color=this->color;
    *fatness=ui->spinBox_3->value();
    *path=file_path;
    if(path->isEmpty()) *path="/home/gagask/CoursWork";
    //QMessageBox::information(this,"af",*path);
}

void Division::on_pushButton_clicked()
{
    color=QColorDialog::getColor(Qt::black,this,"Chose color lines");
}

void Division::on_pushButton_2_clicked()
{
    file_path = QFileDialog::getExistingDirectory(this,"Выберите папку","/home/gagask/CoursWork");
    //QMessageBox::information(this,"af",file_path);
}
