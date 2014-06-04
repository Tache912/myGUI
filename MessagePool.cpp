#include "MessagePool.h"
#include <iostream>
#include <windows.h>

using namespace std;

void MouseStatus::Initialization()
{
    x=0;
    y=0;
    ButtonStatus[Left]=UP;
    ButtonStatus[Right]=UP;
    ButtonStatus[Middle]=UP;
    WheelRollCounter=0;
    //cout<<"MouseStatus Initialization Completed."<<endl;
}

int SetCurrentMouseStatus(unsigned int _Message,unsigned int _wParam,int _x,int _y)
{
    switch (_Message)
    {
        case WM_LBUTTONDOWN:
            CurrentMouseStatus.ButtonStatus[Left]=DOWN;
            //cout<<"Left Status=DOWN"<<endl;
            break;
        case WM_LBUTTONUP:
            CurrentMouseStatus.ButtonStatus[Left]=UP;
            //cout<<"Left Status=UP"<<endl;
            break;
        case WM_RBUTTONDOWN:
            CurrentMouseStatus.ButtonStatus[Right]=DOWN;
            //cout<<"Right Status=DOWN"<<endl;
            break;
        case WM_RBUTTONUP:
            CurrentMouseStatus.ButtonStatus[Right]=UP;
            //cout<<"Right Status=UP"<<endl;
            break;
        case WM_MBUTTONDOWN:
            CurrentMouseStatus.ButtonStatus[Middle]=DOWN;
            //cout<<"Middle Status=DOWN"<<endl;
            break;
        case WM_MBUTTONUP:
            CurrentMouseStatus.ButtonStatus[Middle]=UP;
            //cout<<"Middle Status=UP"<<endl;
            break;
        case WM_MOUSEWHEEL:
            CurrentMouseStatus.WheelRollCounter+=GET_WHEEL_DELTA_WPARAM(_wParam);
            //cout<<CurrentMouseStatus.WheelRollCounter<<endl;
            break;
        case WM_MOUSEMOVE:
            CurrentMouseStatus.x=_x;
            CurrentMouseStatus.y=_y;
            //cout<<CurrentMouseStatus.x<<","<<CurrentMouseStatus.y<<endl;
            break;
    }
    return 0;
}

void KeyboardStatus::Initialization()
{
    memset(KeyStatus,0,sizeof(KeyStatus)/sizeof(KeyStatus[0]));//快速数组初始化（用memset清零）
    //cout<<"KeyboardStatus Initialization Completed."<<endl;
}

int SetCurrentKeyBoardStatus(unsigned int _Message,unsigned int _wParam)
{
    switch(_Message)
    {
        case WM_KEYDOWN:
            CurrentKeyBoardStatus.KeyStatus[_wParam]=DOWN;
            //cout<<"Key "<<_wParam<<" Down now"<<endl;
            break;
        case WM_KEYUP:
            CurrentKeyBoardStatus.KeyStatus[_wParam]=UP;
            //cout<<"Key "<<_wParam<<" Up now"<<endl;
            break;
    }
    return 0;
}
