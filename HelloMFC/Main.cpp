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

//相互的访问关系
//				CWinApp        CFrameWnd				   CView								    CDocument
//CWinApp		X			   m_pMainWnd				   m_pMainWnd->GetActiveView()			    m_pMainWnd->GetActiveView()->GetDocument()
//CFrameWnd		AfxGetApp()    X						   GetActiveView()						    GetActiveView()->GetDocument()
//CView			AfxGetApp()    AfxGetApp()->m_pMainWnd	   X									    GetDocument()
//CDocument		AfxGetApp()    AfxGetApp()->m_pMainWnd	   GetFirstViewPosition();GetNextView();    X

//CDocument
class MyDoc : public CDocument
{
public:
	MyDoc();
	CString* GetStr();

private:
	CString m_String;
};

MyDoc::MyDoc()
{
	m_String = TEXT("你好！我来自CDocument。");
}

CString* MyDoc::GetStr()
{
	return &m_String;
}

//CView
class MyView : public CView
{
	DECLARE_DYNCREATE(MyView)
public:
	virtual void OnDraw(CDC* pDC);
};
IMPLEMENT_DYNCREATE(MyView, CView)

void MyView::OnDraw(CDC* pDC)
{
	MyDoc* pMyDoc = (MyDoc*)GetDocument();
	pDC->TextOut(100, 100, *pMyDoc->GetStr());
}

//CFrameWnd
class MyFrameWnd : public CFrameWnd
{
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();	
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

afx_msg int MyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//创建并关联View
	MyView* pView = new MyView;
	pView->Create(NULL, TEXT("View"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(200, 200, 600, 600), this, 0);
	SetActiveView(pView);

	//获取FrameWnd的关联View
	//CView* pV = GetActiveView();

//创建并关联Doc
	MyDoc* pDoc = new MyDoc;
	pDoc->AddView(pView);

	//绘制Doc的关联View
	//POSITION pos = pDoc->GetFirstViewPosition();
	//while (pos != NULL)
	//{
	//	CView* pNView = pDoc->GetNextView(pos);
	//	pNView->UpdateWindow();
	//}

	return CFrameWnd::OnCreate(lpCreateStruct);
}

afx_msg void MyFrameWnd::OnPaint()
{
	PAINTSTRUCT pt;
	CDC* pDC = BeginPaint(&pt);

	pDC->TextOut(100, 100, TEXT("我是MyFrameWnd。"));

	EndPaint(&pt);
}

//CWindApp
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
//创建并关联FrameWnd
	CFrameWnd* pFrameWnd = new MyFrameWnd;
	//使用pContext动态创建MyView。必须在类MyView中使用宏：DECLARE_DYNCREATE(MyView) 和 IMPLEMENT_DYNCREATE(MyView, CView)
	pFrameWnd->Create(NULL, TEXT("illidan")); 
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->UpdateWindow();
	this->m_pMainWnd = pFrameWnd;

	return TRUE;
}

MyApp app;
