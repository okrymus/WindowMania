// PaneDialogView.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "PaneDialogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaneDialogView

IMPLEMENT_DYNCREATE(CPaneDialogView, CFormView)

CPaneDialogView::CPaneDialogView()
	: CFormView(CPaneDialogView::IDD)
	, time_label(_T("dd"))
{
	CTime t;
	t = CTime::GetCurrentTime();
	CString s = t.Format("Current date and time: %c");
	time_label = s;
	//{{AFX_DATA_INIT(CPaneDialogView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPaneDialogView::~CPaneDialogView()
{
}

void CPaneDialogView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaneDialogView)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_DATE, time_label);
}


BEGIN_MESSAGE_MAP(CPaneDialogView, CFormView)
	//{{AFX_MSG_MAP(CPaneDialogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneDialogView diagnostics

#ifdef _DEBUG
void CPaneDialogView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPaneDialogView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaneDialogView message handlers

void CPaneDialogView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CFrameWnd *pFrameWnd = (CFrameWnd*)GetParent();
	pFrameWnd->SetWindowText("Date and Time");
	

	pFrameWnd->ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, WS_DLGFRAME, SWP_FRAMECHANGED);
	pFrameWnd->RecalcLayout();
	
	ResizeParentToFit();
}
