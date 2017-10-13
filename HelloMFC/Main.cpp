/****************************************************************************************************************
 *    Date    : 2017/10/07 16:43
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : ��򵥵�MFC���� - ���д��ڵ� - ������Ϣ�ģ�ʹ�����أ�
 *
 ****************************************************************************************************************/
#include <afxwin.h>

class MyFrameWnd : public CFrameWnd
{
public:
	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

LRESULT MyFrameWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDC* cdc;
	PAINTSTRUCT pt;
	switch (uMsg)
	{
	case WM_PAINT:
	{
		cdc = BeginPaint(&pt);
		cdc->TextOut(0, 0, TEXT("Hello MFC Paint!"));
		EndPaint(&pt);
		break;
	}
	}

	return CFrameWnd::WindowProc(uMsg, wParam, lParam);
}

class MyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

BOOL MyApp::InitInstance()
{
	CFrameWnd* pFrameWnd = new MyFrameWnd;
	this->m_pMainWnd = pFrameWnd;

	pFrameWnd->Create(NULL, TEXT("illidan"));
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->UpdateWindow();

	return TRUE;
}

MyApp app;
