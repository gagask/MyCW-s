#include "picture.h"
#include <math.h>

picture::picture()
{
}

void picture::mousePressEvent(QMouseEvent* event){
    int l;
    if (event->button()==Qt::LeftButton){
        if(dsquare){
            img.square(event->x(),event->y(),squ.l,squ.fatness,squ.color1,squ.flag,squ.color2);
            setPixmap(img.getPixmap());
        }
        if(dcircle){
            if(count==0){
                count++;
                tmp=event->pos();
            }
            else{
                count=0;
                if (squ.l){
                    if (abs(event->x()-tmp.x())>abs(event->y()-tmp.y())) l=abs(event->y()-tmp.y())/2;
                    else l=abs(event->x()-tmp.x())/2;
                    if(event->x()>tmp.x())
                        if(event->y()>tmp.y())
                            img.circle(tmp.x()+l,tmp.y()+l,l,squ.fatness,squ.color1,squ.flag,squ.color2);
                        else
                            img.circle(tmp.x()+l,tmp.y()-l,l,squ.fatness,squ.color1,squ.flag,squ.color2);
                    else
                        if(event->y()>tmp.y())
                            img.circle(tmp.x()-l,tmp.y()+l,l,squ.fatness,squ.color1,squ.flag,squ.color2);
                        else
                            img.circle(tmp.x()-l,tmp.y()-l,l,squ.fatness,squ.color1,squ.flag,squ.color2);
                }
                else{
                l=sqrt((event->x()-tmp.x())*(event->x()-tmp.x())+(event->y()-tmp.y())*(event->y()-tmp.y()));
                img.circle(tmp.x(),tmp.y(),l,squ.fatness,squ.color1,squ.flag,squ.color2);}
                setPixmap(img.getPixmap());}
        }
    }
}

image *picture::getImage()
{
    return &img;
}

void picture::ActivateDoingSquare(int l,int fat,QColor a,bool f,QColor b)
{
    squ.l=l;
    squ.fatness=fat;
    squ.color1=a;
    squ.color2=b;
    squ.flag=f;
    dcircle=false;
    dsquare=true;
}

void picture::ActivateDoingCircle(int flag,int fat, QColor a, bool f, QColor b)
{
    squ.l=flag;
    squ.fatness=fat;
    squ.color1=a;
    squ.color2=b;
    squ.flag=f;
    dcircle=true;
    dsquare=false;
}
