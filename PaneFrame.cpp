// PaneFrame.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "PaneFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneFrame

IMPLEMENT_DYNCREATE(CPaneFrame, CMDIFrameWnd)

CPaneFrame::CPaneFrame()
{
}

CPaneFrame::~CPaneFrame()
{
}


BEGIN_MESSAGE_MAP(CPaneFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CPaneFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneFrame message handlers

BOOL CPaneFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	ASSERT(m_hWnd != NULL);
	ASSERT(m_hWndMDIClient == NULL);
	
	DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_BORDER |
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS |	WS_HSCROLL | WS_VSCROLL |
		MDIS_ALLCHILDSTYLES;    // allow children to be created invisible
	DWORD dwExStyle = 0;
	
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_CHILDTYPE));
	ccs.idFirstChild = AFX_IDM_FIRST_MDICHILD;
	
	// Create MDICLIENT control with special IDC
	if ((m_hWndMDIClient = ::CreateWindowEx(dwExStyle, _T("mdiclient"), NULL,
		dwStyle, 0, 0, 0, 0, m_hWnd, (HMENU)AFX_IDW_PANE_FIRST,
		AfxGetInstanceHandle(), (LPVOID)&ccs)) == NULL)
	{
		TRACE(_T("Warning: CPaneFrame::OnCreateClient: failed to create MDICLIENT as splitter pane.")
			_T(" GetLastError returns 0x%8.8X\n"), ::GetLastError());
		return FALSE;
	}
	// Move it to the top of z-order
	::BringWindowToTop(m_hWndMDIClient);
	
	return TRUE;
}


