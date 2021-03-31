#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image.h"
#include <QMouseEvent>
#include "picture.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_filter_triggered();

    void on_circle_triggered();

    void on_squaer_triggered();

    void on_division_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

private:
    picture* label;
    //image img;
    QPoint pos1;
    QPoint pos2;
    bool isopen=false;
    Ui::MainWindow *ui;
    QString info;

};

#endif // MAINWINDOW_H
