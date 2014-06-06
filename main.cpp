#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#define WindowWidth 800
#define WindowHeight 600


#include <tchar.h>
#include <windows.h>
#include <iostream>

HDC hDC_global;


#include "MessagePool.h"
#include "Pen.h"
#include "Layer.h"
#include "BasicDraw.h"
#include "global.h"

void DrawCurrentLayerToWindow_Test()//测试用的图层显示函数，非最终版本
{
    HDC hDC=hDC_global;
    HDC DisplayLayer=CreateCompatibleDC(hDC);
    HBITMAP myBMP=CreateCompatibleBitmap(hDC,myLayerArray[CurrentLayerID].nWidth,myLayerArray[CurrentLayerID].nHeight);
    SetBitmapBits (myBMP,myLayerArray[CurrentLayerID].nWidth*myLayerArray[CurrentLayerID].nHeight*4,myLayerArray[CurrentLayerID].Buffer);
    SelectObject (DisplayLayer,myBMP);
    DeleteObject(myBMP);
    //SetMapMode(hDC,MM_LOMETRIC);
    //cout<<StretchBlt(hDC,0,CurrentLayer->y,CurrentLayer->x,CurrentLayer->y,DisplayLayer,0,0,CurrentLayer->x,CurrentLayer->y,SRCCOPY)<<endl;
    BitBlt(hDC,myLayerArray[CurrentLayerID].x,myLayerArray[CurrentLayerID].y,myLayerArray[CurrentLayerID].nWidth,myLayerArray[CurrentLayerID].nHeight,DisplayLayer,0,0,SRCCOPY);
}

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))



using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("myGUI");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("myGUI Demo V1"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           WindowWidth,                 /* The programs width */
           WindowHeight,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);



    //↓窗口构建完毕，开始初始化全局变量
    CurrentMouseStatus.Initialization();
    CurrentKeyBoardStatus.Initialization();
    myLayerArrayInitialization();
    myPenArrayInitialization();

    hDC_global=GetDC(hwnd);

    //↑全局变量初始化完毕

    //手工测试代码

    int test_Pen_ID=CreateMyPen(1,255,0,0,0);
    cout<<"myPenArray["<<test_Pen_ID<<"].Enable="<<myPenArray[test_Pen_ID].Enable<<endl;
    int test_Layer_ID=CreateMyLayer(100,50,500,500,255,255,255,255);




    CurrentPenID=test_Pen_ID;
    CurrentLayerID=test_Layer_ID;
    cout<<CurrentPenID<<","<<CurrentLayerID<<endl;

    if(CheckCurrentLayerAndPen())
    {
        DrawCircle(300,100,30);
        DrawRectangle(200,300,300,100,0);

        DrawCurrentLayerToWindow_Test();
        cout<<"OK"<<endl;
    }


    //测试代码结束


    //进入消息循环
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        case WM_KEYDOWN:
        case WM_KEYUP:                  //将键盘消息传给MessagePool
            return SetCurrentKeyBoardStatus(message,wParam);

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_MOUSEMOVE:              //将鼠标消息扔给内建的MessagePool
            return SetCurrentMouseStatus(message,wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
