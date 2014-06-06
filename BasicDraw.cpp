#include <cmath>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "global.h"
#include "BasicDraw.h"
#include "Pen.h"
#include "Layer.h"
#define TestOut(a) cout<<#a<<"="<<a<<endl
#define DegToArc(_theta) ((_theta*PI)/180)

using namespace std;


bool CheckCurrentLayerAndPen()
{
    if(CurrentLayerID==NO_LAYER ||CurrentPenID==NO_PEN || myLayerArray[CurrentLayerID].Enable==false || myPenArray[CurrentPenID].Enable==false)
    {
        cout<<"Layer or Pen is not ready."<<endl;
        cout<<"CurrentLayerID="<<CurrentLayerID<<endl;
        cout<<"CurrentPenID="<<CurrentPenID<<endl;
        cout<<"myLayerArray[CurrentLayerID].Enable="<<myLayerArray[CurrentLayerID].Enable<<endl;
        cout<<"myPenArray[CurrentPenID].Enable="<<myPenArray[CurrentPenID].Enable<<endl;
        return false;
    }
    else
    {
        return true;
    }
}

inline void DrawPixel(int _x,int _y)
{
    int x=_x-myLayerArray[CurrentLayerID].x;
    int y=_y-myLayerArray[CurrentLayerID].y;
    int nWidth=myLayerArray[CurrentLayerID].nWidth;
    int index=y*nWidth*4+x*4;

    if(x>=0 && x<nWidth && y>=0 && y<myLayerArray[CurrentLayerID].nHeight)
    {
        myLayerArray[CurrentLayerID].Buffer[index]=myPenArray[CurrentPenID].Color_RGBA[0];
        myLayerArray[CurrentLayerID].Buffer[index+1]=myPenArray[CurrentPenID].Color_RGBA[1];
        myLayerArray[CurrentLayerID].Buffer[index+2]=myPenArray[CurrentPenID].Color_RGBA[2];
        myLayerArray[CurrentLayerID].Buffer[index+3]=myPenArray[CurrentPenID].Color_RGBA[3];
    }
}



bool DrawCircle(int _x,int _y,int _r)
{
    int x=_r;
    int y=0;
    int RadiusError=1-x;

    while(x>=y)
    {
        DrawPixel(x+_x,y+_y);
        DrawPixel(y+_x,x+_y);
        DrawPixel(-x+_x,y+_y);
        DrawPixel(-y+_x,x+_y);
        DrawPixel(-x+_x,-y+_y);
        DrawPixel(-y+_x,-x+_y);
        DrawPixel(x+_x,-y+_y);
        DrawPixel(y+_x,-x+_y);
        y++;
        if(RadiusError<0)
        {
            RadiusError+=2*y+1;
        }
        else
        {
            x--;
            RadiusError+=2*(y-x+1);
        }
    }
    return true;
}

bool DrawArc(int _cx,int _cy,int _x0,int _y0,double _theta)
{
    //不懂
    return false;
}



bool DrawLine(int _x0,int _y0,int _x1,int _y1)//using Bresenham's line algorithm
{

    bool steep = abs(_y1-_y0)>abs(_x1-_x0)?true:false;
    if(steep==true)
    {
        MY_SWAP(int,_x0, _y0);
        MY_SWAP(int,_x1, _y1);
    }
    if(_x0>_x1)
    {
        MY_SWAP(int,_x0, _x1);
        MY_SWAP(int,_y0, _y1);
    }
    int delta_x=_x1-_x0;
    int delta_y=abs(_y1-_y0);
    int error=delta_x/2;
    int y_step;
    int y=_y0;
    if(_y0<_y1)
    {
        y_step=1;
    }
    else
    {
        y_step=-1;
    }
    for(int x=_x0;x<_x1;x++)
    {
        if(steep==true)
        {
            DrawPixel(y,x);
        }
        else
        {
            DrawPixel(x,y);
        }
        error=error-delta_y;
        if(error<0)
        {
            y=y+y_step;
            error=error+delta_x;
        }
    }
    return true;
}

bool DrawRectangle(int _width,int _Height,int _dx,int _dy,double theta)
{
    double d_x[4]={0.0,(double)_width,(double)_width,0.0};
    double d_y[4]={0.0,0.0,(double)_Height,(double)_Height};
    double Hypotenuse=sqrt((double)_width*_width+(double)_Height*_Height);

    d_x[1]=double(_width)*cos(theta);
    d_x[2]=Hypotenuse*(cos(theta)*((double)_width/Hypotenuse)-sin(theta)*((double)_Height/Hypotenuse));
    d_x[3]=double(_Height)*cos(theta+0.5*PI);
    d_y[1]=double(_width)*sin(theta);
    d_y[2]=Hypotenuse*(((double)_Height/Hypotenuse)*cos(theta)+sin(theta)*((double)_width/Hypotenuse));
    d_y[3]=double(_Height)*sin(theta+0.5*PI);

    d_x[0]+=(double)_dx;
    d_x[1]+=(double)_dx;
    d_x[2]+=(double)_dx;
    d_x[3]+=(double)_dx;

    d_y[0]+=(double)_dy;
    d_y[1]+=(double)_dy;
    d_y[2]+=(double)_dy;
    d_y[3]+=(double)_dy;

    return    DrawLine(d_x[0],d_y[0],d_x[1],d_y[1])
            &&DrawLine(d_x[1],d_y[1],d_x[2],d_y[2])
            &&DrawLine(d_x[2],d_y[2],d_x[3],d_y[3])
            &&DrawLine(d_x[3],d_y[3],d_x[0],d_y[0]);
}

bool DrawRoundedRectangle(int _width,int _Height,int _cx,int _cy,int _r)//cx、cy为矩形中心坐标,不能旋转
{
    double temp_cx=((double)_width)/2;
    double temp_cy=((double)_Height)/2;

    double ShortSide=min(_width,_Height);

    double r=(ShortSide>2*_r)?_r:(ShortSide/2);

}
