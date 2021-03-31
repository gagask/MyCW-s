#ifndef SQUARE_H
#define SQUARE_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class square;
}

class square : public QDialog
{
    Q_OBJECT

public:
    explicit square(QWidget *parent = 0);
    ~square();
    void load(size_t*,size_t*,QColor*,bool*,QColor*);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::square *ui;
    QColor color_1;
    QColor color_2;
};

#endif // SQUARE_H
