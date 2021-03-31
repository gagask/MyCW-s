#ifndef IMAGE_H
#define IMAGE_H
#include "png.h"
#include <QString>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>

struct Png{
    int width=0, height=0;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
};

class image
{
    struct Png* png,save;
public:
    image();
    ~image();
    void read(QString);
    void write(QString);
    void filterrgb(size_t,size_t);
    void circle(int,int,int,int,QColor,size_t,QColor);
    void square(int,int,int,int,QColor,bool,QColor);
    void division(int n,int m,QColor color,int fat,bool flag, QString path);
    size_t gethight();
    size_t getwidh();
    QPixmap getPixmap();
};

#endif // IMAGE_H
