#ifndef CIRCLE_H
#define CIRCLE_H
#include <QDialog>
#include <QColorDialog>
#include <QColor>
namespace Ui {
class Circle;
}

class Circle : public QDialog
{
    Q_OBJECT

public:
    explicit Circle(QWidget *parent = 0);
    ~Circle();
    void load(size_t*,size_t*,QColor*,QColor*,size_t*);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Circle *ui;
    QColor color_1;
    QColor color_2;
};

#endif // CIRCLE_H
