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
	//DECLARE_MESSAGE_MAP()
protected:
	static const AFX_MSGMAP* PASCAL GetThisMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;

public:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT, int, int);
};

//BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
//	ON_WM_CREATE()
//	ON_WM_PAINT()
//	ON_WM_SIZE()
//END_MESSAGE_MAP()

//PTM_WARNING_DISABLE
__pragma(warning(push))
__pragma(warning(disable : 4867))
const AFX_MSGMAP* MyFrameWnd::GetMessageMap() const
{ 
	return GetThisMessageMap(); 
}
const AFX_MSGMAP* PASCAL MyFrameWnd::GetThisMessageMap()
{
	typedef MyFrameWnd ThisClass;
	typedef CFrameWnd TheBaseClass;
	static const AFX_MSGMAP_ENTRY _messageEntries[] =
	{
		{ WM_CREATE, 0, 0, 0, AfxSig_is, (AFX_PMSG)(AFX_PMSGW)(static_cast<int (AFX_MSG_CALL CWnd::*)(LPCREATESTRUCT)> (&ThisClass::OnCreate)) },
		{ WM_PAINT, 0, 0, 0, AfxSig_vv, (AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(void)> (&ThisClass::OnPaint)) },
		{ WM_SIZE, 0, 0, 0, AfxSig_vwii, (AFX_PMSG)(AFX_PMSGW)(static_cast<void (AFX_MSG_CALL CWnd::*)(UINT, int, int)> (&ThisClass::OnSize)) },
		{ 0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 }
	};
	static const AFX_MSGMAP messageMap = { &TheBaseClass::GetThisMessageMap, &_messageEntries[0] };
	return &messageMap;
}
__pragma(warning(pop))
//PTM_WARNING_RESTORE

int MyFrameWnd::OnCreate(LPCREATESTRUCT)
{
	AfxMessageBox(TEXT("On Create!"));
	return 0;
}
void MyFrameWnd::OnPaint()
{
	CDC* cdc;
	PAINTSTRUCT pt;
	cdc = BeginPaint(&pt);
	cdc->TextOut(0, 0, TEXT("Hello Text!"));
	EndPaint(&pt);
}
void MyFrameWnd::OnSize(UINT, int, int)
{
	AfxMessageBox(TEXT("On Size!"));
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
