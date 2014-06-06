#include <iostream>
using namespace std;
#include "global.h"
#include "Pen.h"

void myPenArrayInitialization()
{
    for(int i=0;i<MAX_PEN;i++)
    {
        myPenArray[i].Enable=false;
        myPenArray[i].LineWidth=0;
        myPenArray[i].Color_RGBA[0]=0;
        myPenArray[i].Color_RGBA[1]=0;
        myPenArray[i].Color_RGBA[2]=0;
        myPenArray[i].Color_RGBA[3]=0;
    }
}

int CreateMyPen(int _LineWidth,unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A)
{
    for(int i=0;i<MAX_PEN;i++)
    {
        if(myPenArray[i].Enable==false)
        {
            myPenArray[i].Enable=true;
            myPenArray[i].LineWidth=_LineWidth;
            myPenArray[i].Color_RGBA[0]=_B;
            myPenArray[i].Color_RGBA[1]=_G;
            myPenArray[i].Color_RGBA[2]=_R;
            myPenArray[i].Color_RGBA[3]=_A;
            cout<<"myPenArray["<<i<<"].Enable="<<myPenArray[i].Enable<<endl;
            return i;
        }
    }
    return -1;
}

void DeleteMyPen(int PenID)
{
    if(PenID>=0 && PenID<MAX_PEN)
    {
        myPenArray[PenID].Enable=false;
    }
}
