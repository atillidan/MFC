/****************************************************************************************************************
 *    Date    : 2017/10/07 16:43
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : ��򵥵�MFC����
 *
 ****************************************************************************************************************/

#include <afxwin.h>

class MyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL MyApp::InitInstance()
{
	::MessageBox(0, TEXT("Hello"), TEXT("illidan"), MB_OK);
	return TRUE;
}

MyApp app;