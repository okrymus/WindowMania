// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "WindowMania.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	/**** JCz ***/
	// we cannot allow to maximize MDI-way (client of the child covers client of the parent
	// this functionality would require buttons in non-client area of the main window
	// maybe in the future i will implement this
	if(SIZE_MAXIMIZED == nType)
	{
		CRect rectParent;
		CWnd *pWnd = GetParent();

		pWnd->GetClientRect(rectParent);

		SetWindowPos(NULL, 0, 0, rectParent.Width(), rectParent.Height(), SWP_FRAMECHANGED | SWP_NOZORDER);
		BringWindowToTop();

		RecalcLayout();
		return;
	}

	CMDIChildWnd::OnSize(nType, cx, cy);
}

void CChildFrame::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	/**** JCz ***/
	// since we do not receive request for repainting NC area, we have to force it
	lpwndpos->flags |= SWP_FRAMECHANGED;
	CMDIChildWnd::OnWindowPosChanging(lpwndpos);
}

void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	
	CWnd *pWnd = GetDlgItem(AFX_IDW_PANE_FIRST);
	ASSERT(pWnd);

	pWnd->SetFocus();
	
}
