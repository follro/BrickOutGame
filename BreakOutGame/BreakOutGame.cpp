// BreakOutGame.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <Windows.h>
#include <cmath>
#include <tchar.h>
#include "framework.h"
#include "BreakOutGame.h"
#include "Object.h"
#include "Plate.h"
#include "Ball.h"
#include "Wall.h"
#include "Break.h"
#include <list>
#include <vector>
#define MAX_LOADSTRING 100
#define PLAET_HEIGHT 30
#define TIMER_NOMAL 0
#define RIGHT 1
#define LEFT -1


enum class OBJType
{
    WALL, PLATE, BALL
};
void Update();
RECT rectView = { 0,0,1200,800 };

Plate* plate;
Ball* ball;
//Wall* wall;
std::vector<Object*> obj;


HDC hdc;
HDC hMemDC;
HBITMAP hBitmap;
HBITMAP hOldBitmap;

std::vector<int> breakTypes=
{
    0,0,0,0,0,0,0,0,0,0,0,0,
    0,5,5,5,5,5,5,5,5,5,5,0,
    0,4,4,4,4,4,4,4,4,4,4,0,
    0,3,3,3,3,3,3,3,3,3,3,0,
    0,2,2,2,2,2,2,2,2,2,2,0,
    0,1,1,1,1,1,1,1,1,1,1,0
};

void BreakMapSetting(std::vector<int> breakTypes, std::vector<Object*> &obj);
void CreateDoubleBuffer(HWND hWnd);
void DeleteDoubleBuffer(HWND hWnd);

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_BREAKOUTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BREAKOUTGAME));

    MSG msg;

    //// 기본 메시지 루프입니다:
    //while (GetMessage(&msg, nullptr, 0, 0))
    //{
    //    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    //    {
    //        TranslateMessage(&msg);
    //        DispatchMessage(&msg);
    //    }
    //}

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        {
             Update();
        }
    }

    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BREAKOUTGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_BREAKOUTGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    static MyVector nomalVec;
    HBRUSH hBrush, oldBrush;
   
    switch (message)
    {

    case WM_CREATE:
        //GetClientRect(hWnd, &rectView);
        obj.push_back (new Wall(rectView));
        obj.push_back(new Plate({ rectView.right / 2,  rectView.bottom - PLAET_HEIGHT }));
        obj.push_back(new Ball());
        obj[(int)OBJType::PLATE]->SetWorldView(rectView);
        obj[(int)OBJType::BALL]->SetWorldView(rectView); 

        ball = dynamic_cast<Ball*>(obj[(int)OBJType::BALL]);
        plate = dynamic_cast<Plate*>(obj[(int)OBJType::PLATE]);

        //plate->SetWorldView(rectView);
        //ball->SetWorldView(rectView);

        BreakMapSetting(breakTypes,obj);

        //wall.SetWall(rectView);
        //plate->SetPlateCenter({ rectView.right / 2, rectView.bottom - static_cast<int>(plate->GetHeight()) });
        SetTimer(hWnd, TIMER_NOMAL, 5, NULL);
        nomalVec = { 0,1 };

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
      /*  switch (switch_on)
        {
        default:
            break;
        }*/
        
        InvalidateRgn(hWnd, NULL, TRUE);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            
            CreateDoubleBuffer(hWnd);
            for (Object* ob : obj)
            {
                ob->Draw(hdc, hBrush, oldBrush);
            }
            DeleteDoubleBuffer(hWnd);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        ball = NULL;
        plate = NULL;
        for (std::vector<Object*>::iterator iter = obj.begin();
            iter != obj.end();)
        {
            //Object* delObj = *iter;
            delete(*iter);
            iter = obj.erase(iter);
        }
        //obj.clear();
        KillTimer(hWnd, TIMER_NOMAL);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Update()
{
    DWORD newTime = GetTickCount();
    static DWORD oldTime = newTime;
    if (newTime - oldTime < 10)
        return;
    
    oldTime = newTime;

    /*if ( dynamic_cast<Ball*>(obj[(int)OBJType::BALL]) -> GetBallState() == Ball::BallState::BOUNCE)
    {
        for (Object* a : obj)
        {
            dynamic_cast<Ball*>(obj[(int)OBJType::BALL])->OnCollision(*a);
        }
       
    }

    dynamic_cast<Ball*>(obj[(int)OBJType::BALL])->Update(*obj[(int)OBJType::PLATE]);*/

    if (ball-> GetBallState() == Ball::BallState::BOUNCE)
    {
        for (Object* a : obj)
        {
            ball->OnCollision(*a);
        }
        ball->ResetOverLapCollision();
    }
    ball->Update(*obj[(int)OBJType::PLATE]);


    //비동기 키 (즉각적인 반응이 필요할때 사용)
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        plate->Move(LEFT);
        //plate.Move(LEFT);
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
       plate->Move(RIGHT);
        //plate.Move(RIGHT);
    }
    else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        ball->SetBallState(Ball::BallState::BOUNCE);
        //ball.SetBallState(1);
    }
}

void BreakMapSetting(std::vector<int> breakTypes, std::vector<Object*> &obj)
{
    int xAdd = 100;
    int yAdd = 50;
    int x = rectView.left + xAdd/2, y = rectView.top + yAdd/2;

    for (int i = 1; i <= breakTypes.size();i++)
    {
        if (rectView.right <= x )
        {
            x = rectView.left + xAdd / 2;
            y += yAdd;
        }
        obj.push_back(new Break({x,y}, breakTypes[i-1]));
        x += xAdd;
    }
}

void CreateDoubleBuffer(HWND hWnd)
{
    hMemDC = CreateCompatibleDC(hdc);
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
    BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
}

void DeleteDoubleBuffer(HWND hWnd)
{
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC); 
}





