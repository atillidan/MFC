/****************************************************************************************************************
 *    Date    : 2017/10/07 16:44
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : 最简单的WinAPI程序
 *
 ****************************************************************************************************************/
#include <windows.h>
#include <tchar.h>

INT WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nShowCmd)
{
	::MessageBox(0, TEXT("Hello"), TEXT("illidan"), MB_OK);
	return 0;
}

