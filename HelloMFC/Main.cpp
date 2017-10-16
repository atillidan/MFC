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
#include "resource.h"

class MyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT Create(WPARAM wParam, LPARAM lParam);
	afx_msg void New();
	afx_msg void Save();
	afx_msg void Exit();
private:
	CMenu m_Menu;
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	ON_MESSAGE(WM_CREATE, Create)
	ON_COMMAND(ID_NEW, New)
	ON_COMMAND(ID_SAVE, Save)
	ON_COMMAND(ID_EXIT, Exit)
END_MESSAGE_MAP()

afx_msg LRESULT MyFrameWnd::Create(WPARAM wParam, LPARAM lParam)
{
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);
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
