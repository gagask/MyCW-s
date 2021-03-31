#include "image.h"
#include "stdio.h"
#include <cstring>
#include <stdlib.h>

image::image(){
    this->png=new struct Png;
}

image::~image()
{
    /* cleanup heap allocation */
    if(!png->height==0)
    {
        for (int y = 0; y < png->height; y++)
            free(png->row_pointers[y]);
        free(png->row_pointers);
    }
    delete png;
}

QPixmap image::getPixmap() {
    QImage* image = new QImage(png->width, png->height, QImage::Format_ARGB32);//Пофиксить формат
    QColor pixel;
    for (int y = 0; y < png->height; y++) {
        png_byte* row = png->row_pointers[y];
        for (int x = 0; x < png->width; x++) {
            png_byte* ptr = &(row[x*4]);
            pixel.setRed(ptr[0]);
            pixel.setGreen(ptr[1]);
            pixel.setBlue(ptr[2]);
            pixel.setAlpha(ptr[3]);
            image->setPixel(x, y, pixel.rgba());
        }
    }
    return QPixmap::fromImage(*image);
}

size_t image::gethight(){
    return png->height;
}

size_t image::getwidh(){
    return png->width;
}

void image::write(QString file_name) {
    /* create file */
    char* convPath = new char[file_name.length() + 1];
    std::strcpy(convPath,file_name.toLatin1());
    FILE *fp = fopen(convPath, "wb");
    if (!fp){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    /* initialize stuff */
    png->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png->png_ptr){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    png->info_ptr = png_create_info_struct(png->png_ptr);
    if (!png->info_ptr){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    if (setjmp(png_jmpbuf(png->png_ptr))){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;}

    png_init_io(png->png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(png->png_ptr))){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    png_set_IHDR(png->png_ptr, png->info_ptr, png->width, png->height,
                 png->bit_depth, png->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png->png_ptr, png->info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(png->png_ptr))){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    png_write_image(png->png_ptr, png->row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(png->png_ptr))){
        QMessageBox::critical(nullptr, "Warning!", "Some error");
        return;
    }

    png_write_end(png->png_ptr, NULL);

    fclose(fp);
    free(convPath);
}

void image::read(QString file_name) {
        int y;
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = NULL;
        char* convPath = new char[file_name.length() + 1];
        std::strcpy(convPath,file_name.toLatin1());
        fp=fopen(convPath, "rb");
        if (!fp){
            QMessageBox::critical(nullptr, "Warning!", file_name.toLatin1().constData());
            return;
        }
        fread(header, 1, 8, fp);
        /* initialize stuff */
        png->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png->png_ptr){
            QMessageBox::critical(nullptr, "Warning!", "Не считался указатель на png");
            return;
        }

        png->info_ptr = png_create_info_struct(png->png_ptr);
        if (!png->info_ptr){
            QMessageBox::critical(nullptr, "Warning!", "couldn't read *.png file");
            return;
        }

        if (setjmp(png_jmpbuf(png->png_ptr))){
            QMessageBox::critical(nullptr, "Warning!", "couldn't read *.png file");
            return;
        }

        png_init_io(png->png_ptr, fp);
        png_set_sig_bytes(png->png_ptr, 8);

        png_read_info(png->png_ptr, png->info_ptr);

        png->width = png_get_image_width(png->png_ptr, png->info_ptr);
        png->height = png_get_image_height(png->png_ptr, png->info_ptr);
        png->color_type = png_get_color_type(png->png_ptr, png->info_ptr);
        png->bit_depth = png_get_bit_depth(png->png_ptr, png->info_ptr);

        png->number_of_passes = png_set_interlace_handling(png->png_ptr);
        png_read_update_info(png->png_ptr, png->info_ptr);

        /* read file */
        if (setjmp(png_jmpbuf(png->png_ptr))){
            QMessageBox::critical(nullptr, "Warning!", "couldn't read *.png file");
            return;
        }

        png->row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * png->height);
        for (y = 0; y < png->height; y++)
            png->row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(png->png_ptr, png->info_ptr));

        png_read_image(png->png_ptr, png->row_pointers);

    fclose(fp);
    free(convPath);
}

void image::circle(int mx,int my,int r,int fatness,QColor color_line,size_t flag,QColor color_inside)
{
    int x,y;

    if (png_get_color_type(png->png_ptr, png->info_ptr) != PNG_COLOR_TYPE_RGBA){
        QMessageBox::critical(nullptr, "Warning!", "Type is not RGBA");
        return;
    }

    for (y = 0; y < png->height; y++) {
        png_byte *row = png->row_pointers[y];
        for (x = 0; x < png->width; x++)
        {
            png_byte *ptr = &(row[x * 4]);
            if(((y-my)*(y-my)+(x-mx)*(x-mx)>=(r-fatness)*(r-fatness))&&((y-my)*(y-my)+(x-mx)*(x-mx)<=(r+fatness)*(r+fatness)))
            {
                ptr[0]=color_line.red();
                ptr[1]=color_line.green();
                ptr[2]=color_line.blue();
            }
            if (flag&&((y-my)*(y-my)+(x-mx)*(x-mx)<(r-fatness)*(r-fatness)))
            {
                ptr[0]=color_inside.red();
                ptr[1]=color_inside.green();
                ptr[2]=color_inside.blue();
            }

        }
    }
}

void image::square(int ux, int uy, int l, int fatness,QColor color1,bool flag,QColor color2){
    int x,y;
    if (png_get_color_type(png->png_ptr, png->info_ptr) != PNG_COLOR_TYPE_RGBA){
        QMessageBox::critical(nullptr, "Warning!", "type is not RGBA");
        return;
    }

    for (y = 0; y < png->height; y++) {
        png_byte *row = png->row_pointers[y];
        for (x = 0; x < png->width; x++)
        {
            png_byte *ptr = &(row[x * 4]);
            if( (((x>=ux-fatness)&&(x<=ux+fatness))&&((y>=uy-fatness)&&(y<=uy+fatness+l)))||
                (((x>=ux-fatness+l)&&(x<=ux+fatness+l))&&((y>=uy-fatness)&&(y<=uy+fatness+l)))||
                (((x>=ux-fatness)&&(x<=ux+fatness+l))&&((y>=uy-fatness)&&(y<=uy+fatness)))||
                (((x>=ux-fatness)&&(x<=ux+fatness+l))&&((y>=uy-fatness+l)&&(y<=uy+fatness+l))))
            {
                ptr[0]=color1.red();
                ptr[1]=color1.green();
                ptr[2]=color1.blue();
            }
            if(((((y-uy<=x-ux+fatness)&&(y-uy>=x-ux-fatness))||
               ((y-uy-l<=-x+ux+fatness)&&(y-uy-l>=-x+ux-fatness))))
               &&(y>uy+fatness)&&(y<uy-fatness+l)&&(x>ux+fatness)&&(x<ux+l-fatness))
            {
                ptr[0]=color1.red();
                ptr[1]=color1.green();
                ptr[2]=color1.blue();
            }
            else
                if(flag&&(y>uy+fatness)&&(y<uy-fatness+l)&&(x>ux+fatness)&&(x<ux+l-fatness))
                {
                    ptr[0]=color2.red();
                    ptr[1]=color2.green();
                    ptr[2]=color2.blue();
                }
        }
    }
}

void image::division(int m, int n, QColor color, int fat, bool flag, QString path)
{
    int dw=png->width/n;
    int dh=png->height/m;
    int y,x;
    if(flag)//если рисовать, то
    {
        for (y = 0; y < png->height; y++) {
            png_byte *row = png->row_pointers[y];
            for (x = 0; x < png->width; x++)
            {
                png_byte *ptr = &(row[x * 4]);
                if((x%dw<=fat)||(x%dw>=dw-fat)||(y%dh<=fat)||(y%dh>=dh-fat))
                {
                    ptr[0]=color.red();
                    ptr[1]=color.green();
                    ptr[2]=color.blue();
                }
            }
        }

    }
    else{//разбить по файлам
        int width,hight,mx,my,i,j,count=0,pngheight,pngwidth;

        pngheight=png->height;
        pngwidth=png->width;
        //копируем row_pointers
        png_bytep* pp = (png_bytep *) malloc(sizeof(png_bytep) * png->height);
        for (y = 0; y < png->height; y++){
            pp[y] = (png_byte *) malloc(png_get_rowbytes(png->png_ptr, png->info_ptr));
            png_byte *rowp = pp[y];
            png_byte *rowd = png->row_pointers[y];
            for(x=0;x<png->width;x++)
            {
                png_byte *ptrp = &(rowp[x * 4]);
                png_byte *ptrd = &(rowd[x * 4]);
                ptrp[0]=ptrd[0];
                ptrp[1]=ptrd[1];
                ptrp[2]=ptrd[2];
                ptrp[3]=ptrd[3];
            }
        }

        for (y = 0; y < m-1; y++) {
            my=y*dh;
            hight=dh;
            for (x = 0; x < n-1; x++) {
                mx=x*dw;
                width=dw;

                png->height=hight;
                png->width=width;
                for(i=0;i<hight;i++)
                {
                    png_byte *rowp = pp[my+i];
                    png_byte *rowd = png->row_pointers[i];
                    for(j=0;j<width;j++)
                    {
                        png_byte *ptrp = &(rowp[(mx+j) * 4]);
                        png_byte *ptrd = &(rowd[j * 4]);
                        ptrd[0]=ptrp[0];
                        ptrd[1]=ptrp[1];
                        ptrd[2]=ptrp[2];
                        ptrd[3]=ptrp[3];
                    }
                }
                QString savename=path+"/file"+QString::number(count)+".png";
                write(savename);
                count++;
                //основная часть
            }
            mx=x*dw;
            width=pngwidth-mx;

            png->height=hight;
            png->width=width;
            for(i=0;i<hight;i++)
            {
                png_byte *rowp = pp[my+i];
                png_byte *rowd = png->row_pointers[i];
                for(j=0;j<width;j++)
                {
                    png_byte *ptrp = &(rowp[(mx+j) * 4]);
                    png_byte *ptrd = &(rowd[j * 4]);
                    ptrd[0]=ptrp[0];
                    ptrd[1]=ptrp[1];
                    ptrd[2]=ptrp[2];
                    ptrd[3]=ptrp[3];
                }
            }
            QString savename=path+"/file"+QString::number(count)+".png";
            write(savename);
            count++;
            //туть правый столбик
        }
        my=y*dh;
        hight=pngheight-my;
        for(x=0;x<n-1;x++)
        {
            mx=x*dw;
            width=dw;
            png->height=hight;
            png->width=width;
            for(i=0;i<hight;i++)
            {
                png_byte *rowp = pp[my+i];
                png_byte *rowd = png->row_pointers[i];
                for(j=0;j<width;j++)
                {
                    png_byte *ptrp = &(rowp[(mx+j) * 4]);
                    png_byte *ptrd = &(rowd[j * 4]);
                    ptrd[0]=ptrp[0];
                    ptrd[1]=ptrp[1];
                    ptrd[2]=ptrp[2];
                    ptrd[3]=ptrp[3];
                }
            }
            QString savename=path+"/file"+QString::number(count)+".png";
            write(savename);
            count++;
            //туть нижняя строка
        }
        mx=x*dw;
        width=pngwidth-mx;
        png->height=hight;
        png->width=width;
        for(i=0;i<hight;i++)
        {
            png_byte *rowp = pp[my+i];
            png_byte *rowd = png->row_pointers[i];
            for(j=0;j<width;j++)
            {
                png_byte *ptrp = &(rowp[(mx+j) * 4]);
                png_byte *ptrd = &(rowd[j * 4]);
                ptrd[0]=ptrp[0];
                ptrd[1]=ptrp[1];
                ptrd[2]=ptrp[2];
                ptrd[3]=ptrp[3];
            }
        }
        QString savename=path+"/file"+QString::number(count)+".png";
        write(savename);
        count++;
        //туть правый нижний элемент

        png->height=pngheight;
        png->width=pngwidth;
        for (y = 0; y < png->height; y++){
            png_byte *rowp = pp[y];
            png_byte *rowd = png->row_pointers[y];
            for(x=0;x<png->width;x++)
            {
                png_byte *ptrp = &(rowp[x * 4]);
                png_byte *ptrd = &(rowd[x * 4]);
                ptrd[0]=ptrp[0];
                ptrd[1]=ptrp[1];
                ptrd[2]=ptrp[2];
                ptrd[3]=ptrp[3];
            }
        }
        for (int y = 0; y < png->height; y++)
            free(pp[y]);
        free(pp);
    }
}


void image::filterrgb(size_t i,size_t color) {
    int x,y;
    if (png_get_color_type(png->png_ptr, png->info_ptr) != PNG_COLOR_TYPE_RGBA){
        QMessageBox::critical(nullptr, "Warning!", "type is not RGBA");
        return;
    }

    for (y = 0; y < png->height; y++) {
        png_byte *row = png->row_pointers[y];
        for (x = 0; x < png->width; x++) {
            png_byte *ptr = &(row[x * 4]);
            ptr[i] = color;
        }
    }
}
