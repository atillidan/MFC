/****************************************************************************************************************
 *    Date    : 2017/10/07 16:43
 *
 *    Author  : Smile
 *    Contact : smile@illidan.org
 *
 *    Brief   : 最简单的MFC程序 - 带有窗口的 - 带有消息的（使用重载）
 *
 ****************************************************************************************************************/
#include <afxwin.h>

class MyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg int OnCreate(LPCREATESTRUCT);
	//afx_msg void OnPaint();
	//afx_msg void OnSize(UINT, int, int);
	afx_msg LRESULT MyCreate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MyPaint(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT MySize(WPARAM wParam, LPARAM lParam);
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	//ON_WM_CREATE()
	//ON_WM_PAINT()
	//ON_WM_SIZE()
	ON_MESSAGE(WM_CREATE, MyCreate)
	ON_MESSAGE(WM_PAINT, MyPaint)
	ON_MESSAGE(WM_SIZE, MySize)
END_MESSAGE_MAP()

//int MyFrameWnd::OnCreate(LPCREATESTRUCT)
//{
//	AfxMessageBox(TEXT("On Create!"));
//	return 0;
//}
//void MyFrameWnd::OnPaint()
//{
//	CDC* cdc;
//	PAINTSTRUCT pt;
//	cdc = BeginPaint(&pt);
//	cdc->TextOut(0, 0, TEXT("Hello Text!"));
//	EndPaint(&pt);
//}
//void MyFrameWnd::OnSize(UINT, int, int)
//{
//	AfxMessageBox(TEXT("On Size!"));
//}

afx_msg LRESULT MyFrameWnd::MyCreate(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(TEXT("On Create!"));
	return 0;
}
afx_msg LRESULT MyFrameWnd::MyPaint(WPARAM wParam, LPARAM lParam)
{
	CDC* cdc;
	PAINTSTRUCT pt;
	cdc = BeginPaint(&pt);
	cdc->TextOut(0, 0, TEXT("Hello Text!"));
	EndPaint(&pt);
	return 0;
}
afx_msg LRESULT MyFrameWnd::MySize(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(TEXT("On Size!"));
	return 0;
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
