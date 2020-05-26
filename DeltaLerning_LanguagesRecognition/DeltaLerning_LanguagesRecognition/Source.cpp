
#include <windows.h>
#pragma comment(lib, "user32.lib")

#define FILE_MENU 0
#define EXIT_MENU -1
#define HELP_MENU 1
#define CALCULATE 2
#define CLEAR 3
#define CALC_ONE 4

#include "Algorithm.h"
using namespace std;
WNDCLASSEX wc;
HWND hwnd;
MSG Msg;

HMENU menu;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void addMenu(HWND hwnd);
void addControl(HWND hwnd);
void calc(HWND hwnd);
void clear();
void calcOne();


int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR args, int ncmdShow)
{
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"NAI03";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"NAI03",
        L"Language detector",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInst, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, ncmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wParam)
        {
        case FILE_MENU:
            MessageBeep(MB_OK);
            break;
        case EXIT_MENU:
            MessageBeep(MB_OK);
            exit(0);
            break;
        case HELP_MENU:
            MessageBox(NULL, L"info", L"Information", MB_OK);
            break;
        case CALCULATE:
            calc(hwnd);
            break;
        case CALC_ONE:
            calcOne();
            break;
        case CLEAR:
            clear();
            break;
        }
        break;
    case WM_CREATE:
        addMenu(hwnd);
        addControl(hwnd);
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HWND fieldt,labelOut;
void addControl(HWND hwnd)
{
    {//button
            CreateWindow(
            L"BUTTON",
            L"CALCULATE",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 10, 450, 30,
            hwnd,
            (HMENU)CALCULATE, NULL, NULL);
            CreateWindow(
                L"BUTTON",
                L"CLEAR",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                450, 10, 100, 30,
                hwnd,
                (HMENU)CLEAR, NULL, NULL);
            CreateWindow(
                L"BUTTON",
                L"CALC ONE",
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                450, 270, 100, 30,
                hwnd,
                (HMENU)CALC_ONE, NULL, NULL);
    }
    {//output
       labelOut=  CreateWindow(L"static", L"",
            WS_CHILD | WS_VISIBLE | WS_TABSTOP,
            10, 45, 300, 50,
            hwnd, NULL,
            NULL, NULL);
    }
    {//input
        fieldt = CreateWindow(L"edit", L"--input text here--",
                    WS_CHILD | WS_VISIBLE | WS_TABSTOP
                    | ES_LEFT | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
                   10, 100, 300, 200,
                    hwnd,NULL,
                    NULL, NULL);
    }
}

void addMenu(HWND hwnd) 
{
    menu = CreateMenu();

    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu,MF_STRING,EXIT_MENU,L"EXIT");


    AppendMenu(menu,MF_POPUP,(UINT_PTR)hFileMenu,L"FILE");
    AppendMenu(menu, MF_STRING, HELP_MENU, L"HELP");

    SetMenu(hwnd, menu);
}

string wchar2string(wchar_t* str)
{
    std::string mystring;
    while (*str)
        mystring += (char)*str++;
    return  mystring;
}

void calcOne()
{
    wchar_t str[1000];
    GetWindowText(fieldt, str, 1000);
    Algorithm alg = Algorithm(TRAINING_FILE_PATH, wchar2string(str),1);
    string result = alg.getOneRes();
    wstring res(result.begin(), result.end());
    SetWindowTextW(fieldt, L"--input text here--");
    SetWindowTextW(labelOut, res.c_str());
}

void calc(HWND hwnd)
{
    Algorithm alg = Algorithm(TRAINING_FILE_PATH, TEST_FILE_PATH);
    int succ = 0, nsucc = 0;
    alg.calcStats(succ, nsucc);
    string result = "Input data: " + to_string(succ + nsucc) + " samples;\nCorrectly classified: " + to_string(succ)
        + " samples;\nPercentage: " + to_string(succ * 100 / (succ + nsucc)) + "%";
    wstring res(result.begin(), result.end());
    SetWindowTextW(labelOut,res.c_str());
}


void clear()
{
    SetWindowTextW(fieldt, L"--input text here--");
}