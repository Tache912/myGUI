#define MAX_LAYER 64
#ifndef Layer_H
#define Layer_H

struct Layer
{

    bool Enable;
    bool Visible;
    bool hasMask;


    //左上角坐标
    int x;
    int y;
    //////////////

    int nWidth;
    int nHeight;

    unsigned char* Buffer;
    unsigned char* Mask;

    void CleanBuffer();
    void CleanMask();
    void SetBufferColor(unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A);

};

void myLayerArrayInitialization();

int CreateMyLayer(int _x,int _y,int _nWidth,int _nHeight,unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A);

void CreateMask(int _LayerID);

void DeleteMask(int LayerID);

void SwapLayerInArray(int LayerID1,int LayerID2);

void LayerResize(int LayerID,int _newWidth,int _newHeight);//从图层中点扩大整个图层，内容不变。为旋转图层内容做准备,如图层有Mask，须连Mask一起扩大

void DeleteMyLayer(int LayerID);

#endif // Layer_H

