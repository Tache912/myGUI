#include <cmath>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "global.h"
#include "BasicDraw.h"
#include "Pen.h"
#include "Layer.h"
#define TestOut(a) cout<<#a<<"="<<a<<endl
#define DegToArc(_theta) (((_theta)*PI)/180)
#define Rotation_x(x,y,theta_Arc) ((x)*cos(theta_Arc)-(y)*sin(theta_Arc))
#define Rotation_y(x,y,theta_Arc) ((x)*sin(theta_Arc)+(y)*cos(theta_Arc))

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

bool DrawArc(double _cx,double _cy,double _x0,double _y0,double _theta_Deg)
{
    double x=_x0-_cx;
    double y=_y0-_cy;

    double y_temp=y;

    //平面旋转变换 x'=xcosa-ysina; y'=xsina+ycosa;

    double theta_Arc=DegToArc(_theta_Deg);

    double xd=Rotation_x(x,y,theta_Arc);
    double yd=Rotation_y(x,y,theta_Arc);

    //TestOut(xd+_cx);
    //TestOut(yd+_cy);


    double rr=x*x+y*y;
    double r=sqrt(rr);
    //TestOut(r);
    double Unit=(y>0)?-1:1;
    while((abs(x-xd)>0.5) || (abs(y-yd)>0.5))
    {
        //TestOut(x);
        //TestOut(xd);
        //TestOut((x-xd));

        //Sleep(500);

        DrawPixel(x+_cx,y+_cy);
        x+=Unit;
        if(x*x<=rr)
        {
            y=-Unit*(sqrt(rr-x*x));
            //TestOut(rr-x*x);
        }
        else
        {
            Unit=-Unit;
            //y=y_temp;
        }


        while(abs(y-y_temp)>0.5)
        {
            //TestOut(abs(y-y_temp));

            if(y-y_temp>0)
            {
                y_temp++;
            }
            else
            {
                y_temp--;
            }
            DrawPixel(x+_cx,y_temp+_cy);
            //TestOut(x-xd);
            //TestOut(y_temp-yd);
            //Sleep(500);
            if(abs(y_temp-yd)<0.5)
            {
                x-=Unit;
                y=y_temp;
                //DrawPixel(x+_cx,y+_cy);
                break;
            }
        }
        //cout<<endl;

        y_temp=y;

        //TestOut(x+_cx);
        //TestOut(y+_cy);

        //TestOut(xd+_cx);
        //TestOut(yd+_cy);
        //TestOut(abs(x-xd));
        //TestOut(abs(y-yd));

        //Sleep(500);
    }
    DrawPixel(x+_cx,y+_cy);
    return true;
}



bool DrawLine(double _x0,double _y0,double _x1,double _y1)//using Bresenham's line algorithm
{

    bool steep = abs(_y1-_y0)>abs(_x1-_x0)?true:false;
    if(steep==true)
    {
        MY_SWAP(double,_x0, _y0);
        MY_SWAP(double,_x1, _y1);
    }
    if(_x0>_x1)
    {
        MY_SWAP(double,_x0, _x1);
        MY_SWAP(double,_y0, _y1);
    }
    double delta_x=_x1-_x0;
    double delta_y=abs(_y1-_y0);
    double error=delta_x/2;
    double y_step;
    double y=_y0;
    if(_y0<_y1)
    {
        y_step=1;
    }
    else
    {
        y_step=-1;
    }
    for(double x=_x0;x<_x1;x++)
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

bool DrawRoundedRectangle(int _width,int _Height,int _cx,int _cy,int _r,double _theta)//cx、cy为矩形中心坐标
{
    double temp_cx=((double)_width)/2;
    double temp_cy=((double)_Height)/2;

    double ShortSide=min(_width,_Height);

    double r=(ShortSide>2*_r)?_r:(ShortSide/2);

    double r0_cx=Rotation_x(r-temp_cx,r-temp_cy,DegToArc(_theta))+_cx;
    double r0_cy=Rotation_y(r-temp_cx,r-temp_cy,DegToArc(_theta))+_cy;

    double r0_x0=Rotation_x(0-temp_cx,r-temp_cy,DegToArc(_theta))+_cx;
    double r0_y0=Rotation_y(0-temp_cx,r-temp_cy,DegToArc(_theta))+_cy;

    double r0_x1=Rotation_x(r-temp_cx,0-temp_cy,DegToArc(_theta))+_cx;
    double r0_y1=Rotation_y(r-temp_cx,0-temp_cy,DegToArc(_theta))+_cy;


    double r1_cx=Rotation_x(_width-r-temp_cx,r-temp_cy,DegToArc(_theta))+_cx;
    double r1_cy=Rotation_y(_width-r-temp_cx,r-temp_cy,DegToArc(_theta))+_cy;


    double r1_x0=Rotation_x(_width-r-temp_cx,0-temp_cy,DegToArc(_theta))+_cx;
    double r1_y0=Rotation_y(_width-r-temp_cx,0-temp_cy,DegToArc(_theta))+_cy;

    double r1_x1=Rotation_x(_width-temp_cx,r-temp_cy,DegToArc(_theta))+_cx;
    double r1_y1=Rotation_y(_width-temp_cx,r-temp_cy,DegToArc(_theta))+_cy;



    double r2_cx=Rotation_x(_width-r-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cx;
    double r2_cy=Rotation_y(_width-r-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cy;

    double r2_x0=Rotation_x(_width-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cx;
    double r2_y0=Rotation_y(_width-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cy;

    double r2_x1=Rotation_x(_width-r-temp_cx,_Height-temp_cy,DegToArc(_theta))+_cx;
    double r2_y1=Rotation_y(_width-r-temp_cx,_Height-temp_cy,DegToArc(_theta))+_cy;

    double r3_cx=Rotation_x(r-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cx;
    double r3_cy=Rotation_y(r-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cy;

    double r3_x0=Rotation_x(r-temp_cx,_Height-temp_cy,DegToArc(_theta))+_cx;
    double r3_y0=Rotation_y(r-temp_cx,_Height-temp_cy,DegToArc(_theta))+_cy;

    double r3_x1=Rotation_x(0-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cx;
    double r3_y1=Rotation_y(0-temp_cx,_Height-r-temp_cy,DegToArc(_theta))+_cy;

    DrawArc(r0_cx,r0_cy,r0_x0,r0_y0,90);
    DrawArc(r1_cx,r1_cy,r1_x0,r1_y0,90);
    DrawArc(r2_cx,r2_cy,r2_x0,r2_y0,90);
    DrawArc(r3_cx,r3_cy,r3_x0,r3_y0,90);

    //TestOut(r2_x1);
    //TestOut(r2_y1);

    DrawLine(r0_x1,r0_y1,r1_x0,r1_y0);
    DrawLine(r1_x1,r1_y1,r2_x0,r2_y0);
    DrawLine(r2_x1,r2_y1,r3_x0,r3_y0);
    DrawLine(r3_x1,r3_y1,r0_x0,r0_y0);

    return true;

}
