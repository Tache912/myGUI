/**myPenArray用来保存、查找不同的Pen */

#define MAX_PEN 256

#ifndef Pen_H
#define Pen_H

struct Pen
{
    bool Enable;
    int LineWidth;
    unsigned char Color_RGBA[4];
};


void myPenArrayInitialization();

int CreateMyPen(int _LineWidth,unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A);

void DeleteMyPen(int PenID);

#endif // Pen_H




