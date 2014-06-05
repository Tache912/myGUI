#include <cstring>
#include "Layer.h"


void Layer::CleanBuffer()
{
    if(Buffer!=NULL)
    {
        memset(Buffer,0,nWidth*nHeight*4);
    }
}

void Layer::CleanMask()
{
    if(Mask!=NULL)
    {
        memset(Mask,0,nWidth*nHeight);
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

void CreateMask(int LayerID)
{
    if(myLayerArray[LayerID].Enable==true)
    {
        myLayerArray[LayerID].hasMask=true;
        myLayerArray[LayerID].Mask=new unsigned char[myLayerArray[LayerID].nWidth*myLayerArray[LayerID].nHeight];
        if(myLayerArray[LayerID].Mask!=NULL)
        {
            myLayerArray[LayerID].CleanMask();
        }
    }
}

void DeleteMask(int LayerID)
{
    if(myLayerArray[LayerID].Enable==true)
    {
        if(myLayerArray[LayerID].hasMask==true)
        {
            myLayerArray[LayerID].hasMask=false;
            if(myLayerArray[LayerID].Mask!=NULL)
            {
                delete[] myLayerArray[LayerID].Mask;
                myLayerArray[LayerID].Mask=NULL;
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
        myLayerArray[i].hasMask=false;

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
                myLayerArray[i].hasMask=false;

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
                    myLayerArray[i].CleanBuffer();
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
    TempLayer.hasMask=myLayerArray[LayerID1].hasMask;

    TempLayer.x=myLayerArray[LayerID1].x;
    TempLayer.y=myLayerArray[LayerID1].y;

    TempLayer.nWidth=myLayerArray[LayerID1].nWidth;
    TempLayer.nHeight=myLayerArray[LayerID1].nHeight;

    TempLayer.Buffer=myLayerArray[LayerID1].Buffer;
    TempLayer.Mask=myLayerArray[LayerID1].Mask;

    myLayerArray[LayerID1].Enable=myLayerArray[LayerID2].Enable;
    myLayerArray[LayerID1].Visible=myLayerArray[LayerID2].Visible;
    myLayerArray[LayerID1].hasMask=myLayerArray[LayerID2].hasMask;

    myLayerArray[LayerID1].x=myLayerArray[LayerID2].x;
    myLayerArray[LayerID1].y=myLayerArray[LayerID2].y;

    myLayerArray[LayerID1].nWidth=myLayerArray[LayerID2].nWidth;
    myLayerArray[LayerID1].nHeight=myLayerArray[LayerID2].nHeight;

    myLayerArray[LayerID1].Buffer=myLayerArray[LayerID2].Buffer;
    myLayerArray[LayerID1].Mask=myLayerArray[LayerID2].Mask;


    myLayerArray[LayerID2].Enable=TempLayer.Enable;
    myLayerArray[LayerID2].Visible=TempLayer.Visible;
    myLayerArray[LayerID2].hasMask=TempLayer.hasMask;

    myLayerArray[LayerID2].x=TempLayer.x;
    myLayerArray[LayerID2].y=TempLayer.y;

    myLayerArray[LayerID2].nWidth=TempLayer.nWidth;
    myLayerArray[LayerID2].nHeight=TempLayer.nHeight;

    myLayerArray[LayerID2].Buffer=TempLayer.Buffer;
    myLayerArray[LayerID2].Mask=TempLayer.Mask;

}

void LayerResize(int LayerID,int _newWidth,int _newHeight)
{
    if(myLayerArray[LayerID].Enable==true)
    {
        unsigned char* newBuffer=new unsigned char[_newWidth*_newHeight*4];
        if(newBuffer!=NULL)
        {
            memset(newBuffer,0,_newWidth*_newHeight*4);
            int oldWidth=myLayerArray[LayerID].nWidth;
            int oldHeight=myLayerArray[LayerID].nHeight;

            int dx=(_newWidth-oldWidth)/2;
            int dy=(_newHeight-oldHeight)/2;

            myLayerArray[LayerID].x+=dx;
            myLayerArray[LayerID].y+=dy;

            for(int i=0;i<oldHeight;i++)
            {
                for(int j=0;j<oldWidth;j++)
                {
                    if(i+dy>0 && i+dy<_newHeight && j+dx>0 && j+dx<_newWidth)
                    {
                        newBuffer[(i+dy)*oldWidth*4+(j+dx)*4]=myLayerArray[LayerID].Buffer[i*oldWidth*4+j*4];
                        newBuffer[(i+dy)*oldWidth*4+(j+dx)*4+1]=myLayerArray[LayerID].Buffer[i*oldWidth*4+j*4+1];
                        newBuffer[(i+dy)*oldWidth*4+(j+dx)*4+2]=myLayerArray[LayerID].Buffer[i*oldWidth*4+j*4+2];
                        newBuffer[(i+dy)*oldWidth*4+(j+dx)*4+3]=myLayerArray[LayerID].Buffer[i*oldWidth*4+j*4+3];

                    }
                }
            }

            delete[] myLayerArray[LayerID].Buffer;
            myLayerArray[LayerID].Buffer=newBuffer;

            if(myLayerArray[LayerID].hasMask==true)
            {
                unsigned char* newMask=new unsigned char[_newWidth*_newHeight];
                if(newMask!=NULL)
                {
                    memset(newMask,0,_newWidth*_newHeight);
                    for(int i=0;i<oldHeight;i++)
                    {
                        for(int j=0;j<oldWidth;j++)
                        {
                            if(i+dy>0 && i+dy<_newHeight && j+dx>0 && j+dx<_newWidth)
                            {
                                newMask[(i+dy)*oldWidth+(j+dx)]=myLayerArray[LayerID].Mask[i*oldWidth+j];
                            }
                        }
                    }
                    delete[] myLayerArray[LayerID].Mask;
                    myLayerArray[LayerID].Mask=newMask;
                }
            }

        }
    }
}


void DeleteMyLayer(int LayerID)
{
    if(LayerID>=0 && LayerID<MAX_LAYER)
    {
        myLayerArray[LayerID].Enable=false;
        delete[] myLayerArray[LayerID].Buffer;
        delete[] myLayerArray[LayerID].Mask;

        myLayerArray[LayerID].Buffer=NULL;
        myLayerArray[LayerID].Mask=NULL;
    }
}
