//将键盘和鼠标消息全部放在这个消息池里（封装）

enum ButtonType{Left,Middle,Right};
#define UP 0;
#define DOWN 1;
struct MouseStatus
{
    int x;
    int y;
    bool ButtonStatus[3];//左键、中键、右键按下或释放的状态
    int WheelRollCounter;//滚轮计数器，每次滚轮消息会使其值增加或减少一个WHEEL_DELTA（即120），处理完该值时应将其清零。
    void Initialization();
};
static MouseStatus CurrentMouseStatus;
int SetCurrentMouseStatus(unsigned int _Message,unsigned int _wParam,int _x,int _y);


struct KeyboardStatus
{
    bool KeyStatus[255];//键盘单个按键状态
    void Initialization();
};
static KeyboardStatus CurrentKeyBoardStatus;
int SetCurrentKeyBoardStatus(unsigned int _Message,unsigned int _wParam);


