#ifndef WINFILTER_H
#define WINFILTER_H

#include <QDialog>

namespace Ui {
class winfilter;
class MainWindow;
}

class winfilter : public QDialog
{
    Q_OBJECT

public:
    explicit winfilter(QWidget *parent = 0);
    ~winfilter();
    void load(QString*,size_t*);
private:
    Ui::winfilter *ui;
};

#endif // WINFILTER_H
