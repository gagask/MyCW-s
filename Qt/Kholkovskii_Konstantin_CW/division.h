#ifndef DIVISION_H
#define DIVISION_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>

namespace Ui {
class Division;
}

class Division : public QDialog
{
    Q_OBJECT

public:
    explicit Division(QWidget *parent = 0);
    ~Division();
    void load(int* n, int* m, QColor* color, int *fatness, bool* flag, QString *path);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Division *ui;
    QColor color;
    QString file_path;
};

#endif // DIVISION_H
