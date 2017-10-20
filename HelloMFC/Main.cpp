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
#include <afxframewndex.h>
#include <afxribbonbar.h>

#include "resource.h"

class MyFrameWnd : public CFrameWndEx
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT);
private:
	CMFCRibbonBar m_RibbonBar;
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWndEx)
	ON_WM_CREATE()
END_MESSAGE_MAP()

afx_msg int MyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_RibbonBar.Create(this);
	m_RibbonBar.LoadFromResource(IDR_RIBBON1);

	return CFrameWndEx::OnCreate(lpCreateStruct);
}

class MyApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
};

BEGIN_MESSAGE_MAP(MyApp, CWinApp)
END_MESSAGE_MAP()

BOOL MyApp::InitInstance()
{
	AfxOleInit();

	CFrameWnd* pFrameWnd = new MyFrameWnd;
	this->m_pMainWnd = pFrameWnd;

	pFrameWnd->Create(NULL, TEXT("illidan"));
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->UpdateWindow();

	return TRUE;
}

MyApp app;
