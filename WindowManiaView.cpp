// WindowManiaView.cpp : implementation of the CWindowManiaView class
//


/*
* Programmer: Panupong Leenawarat
* Last Modified: May 8, 2017
* CIT 284 Final Exam poject: WINDOWS MANIA
* The program performs as DOS/WINDOWS operating system
* The code for each command is embedded into the Windows code for the User Interface
*/

#include "stdafx.h"
#include "WindowMania.h"

#include "WindowManiaDoc.h"
#include "WindowManiaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView

IMPLEMENT_DYNCREATE(CWindowManiaView, CView)

BEGIN_MESSAGE_MAP(CWindowManiaView, CView)
	//{{AFX_MSG_MAP(CWindowManiaView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	//ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView construction/destruction

CWindowManiaView::CWindowManiaView()
{
	// TODO: add construction code here

}

CWindowManiaView::~CWindowManiaView()
{
}

BOOL CWindowManiaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView drawing

void CWindowManiaView::OnDraw(CDC* pDC)
{
	CWindowManiaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView printing

BOOL CWindowManiaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWindowManiaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWindowManiaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView diagnostics

#ifdef _DEBUG
void CWindowManiaView::AssertValid() const
{
	CView::AssertValid();
}

void CWindowManiaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWindowManiaDoc* CWindowManiaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWindowManiaDoc)));
	return (CWindowManiaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaView message handlers
