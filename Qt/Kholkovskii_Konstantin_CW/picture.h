#ifndef PICTURE_H
#define PICTURE_H
#include <QLabel>
#include <QMouseEvent>
#include "image.h"

struct Parms{
    int l,fatness;
    QColor color1,color2;
    bool flag;
};

class picture : public QLabel
{
private:
    image img;
    struct Parms squ;
    bool dsquare=false;
    bool dcircle=false;
    int count=0;
    QPoint tmp;
public:
    picture();
    void mousePressEvent(QMouseEvent* event);
    image* getImage();
    void ActivateDoingSquare(int,int,QColor,bool,QColor);
    void ActivateDoingCircle(int,int,QColor,bool,QColor);
};

#endif // PICTURE_H
