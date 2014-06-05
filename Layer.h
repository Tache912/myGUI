#define MAX_LAYER 64

struct Layer
{

    bool Enable;
    bool Visible;

    //左上角坐标
    int x;
    int y;
    //////////////

    int nWidth;
    int nHeight;

    unsigned char* Buffer;

    void Clean();
    void SetBufferColor(unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A);

};

static Layer myLayerArray[MAX_LAYER];

void myLayerArrayInitialization();

int CreateMyLayer(int _x,int _y,int _nWidth,int _nHeight,unsigned char _R,unsigned char _G,unsigned char _B,unsigned char _A);

void SwapLayerInArray(int LayerID1,int LayerID2);

void DeleteMyLayer(int LayerID);



