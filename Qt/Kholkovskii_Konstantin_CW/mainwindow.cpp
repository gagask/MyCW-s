#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDir>
#include <QFileDialog>
#include "image.h"
#include "winfilter.h"
#include "circle.h"
#include <QMessageBox>
#include "square.h"
#include "division.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new picture;
    setCentralWidget(label);
    label->setAlignment(Qt::AlignLeft|Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete label;
}

void MainWindow::on_open_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,"Open Image","/home/gagask/CoursWork/","*.png");
    if(!filePath.isEmpty()){
        isopen=true;
        info="Путь к файлу: "+filePath+"\n";
        label->getImage()->read(filePath);
        label->setPixmap(label->getImage()->getPixmap());
        label->resize(label->getImage()->getwidh(),label->getImage()->gethight());
    }
}

void MainWindow::on_save_triggered()
{
    if(!isopen){
        QMessageBox::critical(nullptr, "Warning!", "Сначала откройте картинку");
        return;
    }
    QString save_filename = QFileDialog::getSaveFileName(this, "Choose a path to save image", "/home/", "*.png");
    if(!save_filename.isEmpty())
    label->getImage()->write(save_filename);
}

void MainWindow::on_filter_triggered()
{
    if(!isopen){
        QMessageBox::critical(nullptr, "Warning!", "Сначала откройте картинку");
        return;
    }
    size_t num;
    QString comp;
    winfilter my;
    my.setModal(true);
    if(!my.exec()) return;
    my.load(&comp,&num);
    size_t a;
    if(comp.toLatin1().constData()[0]=='R') a=0;
    if(comp.toLatin1().constData()[0]=='G') a=1;
    if(comp.toLatin1().constData()[0]=='B') a=2;
    label->getImage()->filterrgb(a,num);
    label->setPixmap(label->getImage()->getPixmap());
}

void MainWindow::on_circle_triggered()
{
    if(!isopen){
        QMessageBox::critical(nullptr, "Warning!", "Сначала откройте картинку");
        return;
    }
    size_t flag1,fatness,flag2;
    QColor color2,color1;
    Circle my;
    my.setModal(true);
    if(!my.exec()) return;
    my.load(&flag1,&fatness,&color1,&color2,&flag2);
    label->ActivateDoingCircle(flag1,fatness,color1,flag2,color2);
}

void MainWindow::on_squaer_triggered()
{
    if(!isopen){
        QMessageBox::critical(nullptr, "Warning!", "Сначала откройте картинку");
        return;
    }
    size_t l,fatness;
    bool flag;
    QColor color1,color2;
    square my;
    my.setModal(true);
    if(!my.exec()) return;
    my.load(&l,&fatness,&color1,&flag,&color2);
    label->ActivateDoingSquare(l,fatness,color1,flag,color2);
}


void MainWindow::on_division_triggered()
{
    if(!isopen){
        QMessageBox::critical(nullptr, "Warning!", "Сначала откройте картинку");
        return;
    }
    int n,m,fat;
    bool flag;
    QColor color;
    QString path;
    Division my;
    my.setModal(true);
    if(!my.exec())return;
    my.load(&n,&m,&color,&fat,&flag,&path);
    label->getImage()->division(n,m,color,fat,flag,path);
    label->setPixmap(label->getImage()->getPixmap());
}

void MainWindow::on_action_triggered()
{
    if(!isopen){
        QMessageBox::information(this,"Информация","Файл не открыт");
        return;
    }
    info+="Ширина: "+QString::number(label->getImage()->getwidh())+"   Высота: "+QString::number(label->getImage()->gethight())+"\n";
    QMessageBox::information(this,"Информация",info);
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::information(this,"Автор","Холковский Константин Владимирович, студент гр. 8304 СПБГЭТУ(ЛЭТИ)\nВариант курсовой на 5: 17");
}
