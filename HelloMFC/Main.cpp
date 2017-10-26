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

class MyView : public CView
{
	DECLARE_DYNCREATE(MyView)
public:
	virtual void OnDraw(CDC* pDC);
};
IMPLEMENT_DYNCREATE(MyView, CView)

void MyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(100, 100, TEXT("我是MyView。"));
}

class MyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();

//private:
//	MyView* pView;
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	//ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//afx_msg int MyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	pView = new MyView;
//	pView->Create(NULL, TEXT("View"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(200, 200, 600, 600), this, 0);
//	SetActiveView(pView);
//
//	return CFrameWnd::OnCreate(lpCreateStruct);
//}

afx_msg void MyFrameWnd::OnPaint()
{
	PAINTSTRUCT pt;
	CDC* pDC = BeginPaint(&pt);

	pDC->TextOut(100, 100, TEXT("我是MyFrameWnd。"));

	EndPaint(&pt);
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
	CCreateContext* pContext = new CCreateContext;
	pContext->m_pCurrentDoc = NULL;
	pContext->m_pCurrentFrame = NULL;
	pContext->m_pLastView = NULL;
	pContext->m_pNewDocTemplate = NULL;
	pContext->m_pNewViewClass = RUNTIME_CLASS(MyView);

	CFrameWnd* pFrameWnd = new MyFrameWnd;
	//使用pContext动态创建MyView。必须在类MyView中使用宏：DECLARE_DYNCREATE(MyView) 和 IMPLEMENT_DYNCREATE(MyView, CView)
	pFrameWnd->Create(NULL, TEXT("illidan"), WS_OVERLAPPEDWINDOW, CRect(200, 200, 900, 900), NULL, NULL, 0, pContext); 
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->UpdateWindow();
	this->m_pMainWnd = pFrameWnd;

	return TRUE;
}

MyApp app;
