#ifndef PI
#define PI     3.1415926536
#endif // PI

#define NO_PEN -1
#define NO_LAYER -1

#define MY_SWAP(t,x,y) {t temp=x;x=y;y=temp;}
#define min(x,y) (x<y)?x:y

#ifndef BasicDraw_H
#define BasicDraw_H


bool CheckCurrentLayerAndPen();
inline void DrawPixel(int _x,int _y);
bool DrawCircle(int _x,int _y,int _r);
bool DrawArc(double _cx,double _cy,double _x0,double _y0,double _theta_Deg);
bool DrawLine(int _x0,int _y0,int _x1,int _y1);
bool DrawRectangle(int _width,int _Height,int _dx,int _dy,double theta);
bool DrawRoundedRectangle(int _width,int _Height,int _cx,int _cy,int _r,double _theta);//cx、cy为矩形中心坐标
#endif // BasicDraw_H
/**
基本绘图：
用于GUI内容绘制的各种绘图函数
在指定Layer上用指定Pen进行绘制
基本绘图函数有：

带图层边界检测的像素点√
单像素宽度的线段√
单像素宽度的空心圆√
单像素宽度的矩形√

单像素宽度圆角矩形

指定画笔宽度的空心圆（两个空心圆填充）
指定画笔宽度的线段（填充矩形）

单像素宽度圆角矩形
油漆桶（封闭区域填充）

将myLayerArray中所有Enable并且Visible的Layer进行混合，输出到一个最终显示用的Layer上
创建内存DC和bitmap，使用BitBlt将最终Layer显示至窗口。
*/




