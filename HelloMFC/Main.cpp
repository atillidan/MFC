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
#include <afxext.h>
#include "resource.h"

class MyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR);
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg LRESULT Create(WPARAM wParam, LPARAM lParam);
	afx_msg void New();
	afx_msg void Save();
	afx_msg void Exit();
private:
	CMenu m_Menu;
	CToolBar m_ToolBar;
	CStatusBar m_StatusBar;
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_CREATE, Create)
	ON_COMMAND(ID_NEW, New)
	ON_COMMAND(ID_SAVE, Save)
	ON_COMMAND(ID_EXIT, Exit)
	ON_COMMAND(ID_A, New)
	ON_COMMAND(ID_B, Save)
	ON_COMMAND(ID_C, Exit)
END_MESSAGE_MAP()

afx_msg void MyFrameWnd::OnTimer(UINT_PTR)
{
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString time;
	time.Format(TEXT("%d年-%d月-%d日 %d:%d:%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_StatusBar.SetPaneText(1, time, TRUE);
}

afx_msg void MyFrameWnd::OnMouseMove(UINT, CPoint pt)
{
	CString pos;
	pos.Format(TEXT("X:%d, Y:%d"), pt.x, pt.y);
	m_StatusBar.SetPaneText(2, pos, TRUE);
}

afx_msg LRESULT MyFrameWnd::Create(WPARAM wParam, LPARAM lParam)
{
	//菜单
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	//工具条
	m_ToolBar.Create(this);
	m_ToolBar.SetWindowText(TEXT("工具条"));
	m_ToolBar.LoadToolBar(IDR_TOOLBAR1);
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar, AFX_IDW_DOCKBAR_LEFT);

	//状态栏
	m_StatusBar.Create(this);
	const UINT Indicators[] = { 0, 1, 2 };
	m_StatusBar.SetIndicators(Indicators, 3);
	m_StatusBar.SetPaneInfo(1, 1, SBPS_NOBORDERS, 200);
	m_StatusBar.SetPaneInfo(2, 2, SBPS_NOBORDERS, 120);
	SetTimer(100, 1000, NULL);

	//状态栏初始化
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	CString time;
	time.Format(TEXT("%d年-%d月-%d日 %d:%d:%d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_StatusBar.SetPaneText(1, time, TRUE);

	return 0;
}

afx_msg void MyFrameWnd::New()
{
	AfxMessageBox(TEXT("On New!"));
}

afx_msg void MyFrameWnd::Save()
{
	AfxMessageBox(TEXT("On Save!"));
}

afx_msg void MyFrameWnd::Exit()
{
	AfxMessageBox(TEXT("On Exit!"));
}

class MyApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
	afx_msg void Exit();
};

BEGIN_MESSAGE_MAP(MyApp, CWinApp)
	ON_COMMAND(ID_EXIT, Exit)
END_MESSAGE_MAP()

BOOL MyApp::InitInstance()
{
	CFrameWnd* pFrameWnd = new MyFrameWnd;
	this->m_pMainWnd = pFrameWnd;

	pFrameWnd->Create(NULL, TEXT("illidan"));
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->UpdateWindow();

	return TRUE;
}

afx_msg void MyApp::Exit()
{
	::PostQuitMessage(0);
}

MyApp app;
