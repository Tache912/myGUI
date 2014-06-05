#include <cstring>
#include "Layer.h"

void Layer::Clean()
{
    if(Buffer!=NULL)
    {
        memset(Buffer,0,nWidth*nHeight*4);
    }
}

void Layer::SetBufferColor(unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A)
{
    if(Buffer!=NULL)
    {
        for(int i=0;i<nHeight;i++)
        {
            for(int j=0;j<nWidth;j++)
            {
                Buffer[i*nWidth*4+j*4]=_R;
                Buffer[i*nWidth*4+j*4+1]=_G;
                Buffer[i*nWidth*4+j*4+2]=_B;
                Buffer[i*nWidth*4+j*4+3]=_A;
            }
        }
    }
}

void myLayerArrayInitialization()
{
    for(int i=0;i<MAX_LAYER;i++)
    {
        myLayerArray[i].Enable=false;
        myLayerArray[i].Visible=false;

        myLayerArray[i].x=0;
        myLayerArray[i].y=0;

        myLayerArray[i].nWidth=-1;
        myLayerArray[i].nHeight=-1;

        myLayerArray[i].Buffer=NULL;
    }
}

int CreateMyLayer(int _x,int _y,int _nWidth,int _nHeight,unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A)
{
    for(int i=0;i<MAX_LAYER;i++)
    {
        if(myLayerArray[i].Enable==false)
        {
            myLayerArray[i].Buffer=new unsigned char[_nWidth*_nHeight*4];
            if(myLayerArray[i].Buffer!=NULL)
            {
                myLayerArray[i].Enable=true;
                myLayerArray[i].Visible=true;

                myLayerArray[i].x=_x;
                myLayerArray[i].y=_y;

                myLayerArray[i].nWidth=_nWidth;
                myLayerArray[i].nHeight=_nHeight;
                if(_R!=0 || _G!=0 || _B!=0 || _A!=0)
                {
                    myLayerArray[i].SetBufferColor(_R,_G,_B,_A);
                }
                else
                {
                    myLayerArray[i].Clean();
                }
                return i;
            }
            else
            {
                return -1;//内存申请失败
            }
        }
    }
    return -1;//图层已满
}

void SwapLayerInArray(int LayerID1,int LayerID2)
{
    Layer TempLayer;

    TempLayer.Enable=myLayerArray[LayerID1].Enable;
    TempLayer.Visible=myLayerArray[LayerID1].Visible;

    TempLayer.x=myLayerArray[LayerID1].x;
    TempLayer.y=myLayerArray[LayerID1].y;

    TempLayer.nWidth=myLayerArray[LayerID1].nWidth;
    TempLayer.nHeight=myLayerArray[LayerID1].nHeight;

    TempLayer.Buffer=myLayerArray[LayerID1].Buffer;


    myLayerArray[LayerID1].Enable=myLayerArray[LayerID2].Enable;
    myLayerArray[LayerID1].Visible=myLayerArray[LayerID2].Visible;

    myLayerArray[LayerID1].x=myLayerArray[LayerID2].x;
    myLayerArray[LayerID1].y=myLayerArray[LayerID2].y;

    myLayerArray[LayerID1].nWidth=myLayerArray[LayerID2].nWidth;
    myLayerArray[LayerID1].nHeight=myLayerArray[LayerID2].nHeight;

    myLayerArray[LayerID1].Buffer=myLayerArray[LayerID2].Buffer;


    myLayerArray[LayerID2].Enable=TempLayer.Enable;
    myLayerArray[LayerID2].Visible=TempLayer.Visible;

    myLayerArray[LayerID2].x=TempLayer.x;
    myLayerArray[LayerID2].y=TempLayer.y;

    myLayerArray[LayerID2].nWidth=TempLayer.nWidth;
    myLayerArray[LayerID2].nHeight=TempLayer.nHeight;

    myLayerArray[LayerID2].Buffer=TempLayer.Buffer;

}


void DeleteMyLayer(int LayerID)
{
    if(LayerID>=0 && LayerID<MAX_LAYER)
    {
        myLayerArray[LayerID].Enable=false;
        delete myLayerArray[LayerID].Buffer;
        myLayerArray[LayerID].Buffer=NULL;
    }
}
