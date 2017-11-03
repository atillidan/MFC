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

//相互的访问关系
//				CWinApp        CFrameWnd				   CView								    CDocument
//CWinApp		X			   m_pMainWnd				   m_pMainWnd->GetActiveView()			    m_pMainWnd->GetActiveView()->GetDocument()
//CFrameWnd		AfxGetApp()    X						   GetActiveView()						    GetActiveView()->GetDocument()
//CView			AfxGetApp()    AfxGetApp()->m_pMainWnd	   X									    GetDocument()
//CDocument		AfxGetApp()    AfxGetApp()->m_pMainWnd	   GetFirstViewPosition();GetNextView();    X

//CDocument
class MyDoc : public CDocument
{
	DECLARE_DYNCREATE(MyDoc)
public:
	MyDoc();
	CString* GetStr();

private:
	CString m_String;
};
IMPLEMENT_DYNCREATE(MyDoc, CDocument)

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
	DECLARE_DYNCREATE(MyFrameWnd)
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();	
};
IMPLEMENT_DYNCREATE(MyFrameWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

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
	//Create SigleDocTemplate Object pSingleDocTemplate.
	CSingleDocTemplate* pSingleDocTemplate = new CSingleDocTemplate(IDR_MENU1, RUNTIME_CLASS(MyDoc), RUNTIME_CLASS(MyFrameWnd), RUNTIME_CLASS(MyView));

	//Add pSingleDocTemplate to MyApp.
	AddDocTemplate(pSingleDocTemplate);

	//Create MyDoc/MyFrameWnd/MyView by pSingleDocTemplate and link those.
	OnFileNew();

	return TRUE;
}

MyApp app;
