// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WindowMania.h"
#include "SplashWindow.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum { DATE_TIME = 0, SHELL_EXTENTION, FILE_OPERATION, DIRECTORY_OPERATION, EDIT_VIEW, FORM_VIEW };

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_INFO_DATE, &CMainFrame::OnInfoDate)
	ON_COMMAND(ID_FILESHELL_FILE, &CMainFrame::OnFileshellFile)
	ON_COMMAND(ID_WINDOWS_DIRECTORYOPERATION, &CMainFrame::OnWindowsDirectoryoperation)
	ON_COMMAND(ID_WINDOWS_FILEOPERATION, &CMainFrame::OnWindowsFileoperation)
	ON_COMMAND(ID_WINDOWS_EDIT, &CMainFrame::OnWindowsEdit)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if(!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE("Failed to create splitter.\n");
		return FALSE;
	}

	if(!m_wndSplitter.CreateView(0, 0, pContext->m_pNewViewClass, CSize(0, 100), pContext))
	{
		TRACE("Failed to create splitter pane.\n");
		return FALSE;
	}

	if(!m_wndSplitter.CreateMDIPane(1, 0, CSize(0, 0), pContext))
	{
		TRACE("Failed to create splitter MDI pane.\n");
		return FALSE;
	}
	

	return TRUE;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if(m_wndSplitter.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}
	
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::CreateSplitterChildren()
{
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc);
}


void CMainFrame::OnInfoDate()
{
	// TODO: Add your command handler code here
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc, DATE_TIME);
}


void CMainFrame::OnFileshellFile()
{
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc, SHELL_EXTENTION);
}


void CMainFrame::OnWindowsDirectoryoperation()
{
	// TODO: Add your command handler code here
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc, DIRECTORY_OPERATION);
}


void CMainFrame::OnWindowsFileoperation()
{
	// TODO: Add your command handler code here
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc, FILE_OPERATION );
}


void CMainFrame::OnWindowsEdit()
{
	// TODO: Add your command handler code 
	CDocument *pDoc = GetActiveDocument();
	ASSERT(pDoc);

	m_wndSplitter.CreateChildren(pDoc, EDIT_VIEW);
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	if (nID == SC_CLOSE) {
		int Answer;

		Answer = MessageBox(_T("Are you sure?"), _T("EXIT"),
			MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2);

		if (Answer == IDYES)
		{
			CSplashWindow::ShowSplashScreen(NULL, "BEST TO YOU", 2000);
			Sleep(2000);

			CSplashWindow::ShowSplashScreen(NULL, "Bye Bye..", 2000);
			Sleep(2000);
			CWnd* pWnd = AfxGetApp()->GetMainWnd();
			pWnd->PostMessage(WM_CLOSE);
		}
	}
	else {
		CFrameWnd::OnSysCommand(nID, lParam);
	}
}
