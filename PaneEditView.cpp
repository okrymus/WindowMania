// PaneEditView.cpp : implementation of the CPaneEditView class
//

#include "stdafx.h"
#include "WindowMania.h"
#include <fstream>
#include <strstream>
#include <io.h>
#include "WindowManiaDoc.h"
#include "PaneFormView.h"
#include "PaneEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const char fileDialogFilter[] = "C++ Files (*.cpp) | *.cpp|Header Files\
(*.h)|*.h|Resource Files (*.rc) | *.rc | Text Files (*.txt)|*.txt| All Files (*.*)| *.*||";
const char fileDialogExt[] = "cpp";

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView

IMPLEMENT_DYNCREATE(CPaneEditView, CEditView)

BEGIN_MESSAGE_MAP(CPaneEditView, CEditView)
	//{{AFX_MSG_MAP(CPaneEditView)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CPaneEditView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVETXT, &CPaneEditView::OnFileSavetxt)
	ON_COMMAND(ID_FILE_CLEAR, &CPaneEditView::OnFileClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView construction/destruction

CPaneEditView::CPaneEditView()
{
	// TODO: add construction code here

}

CPaneEditView::~CPaneEditView()
{
}

BOOL CPaneEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView drawing

void CPaneEditView::OnDraw(CDC* pDC)
{
	CWindowManiaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView printing

BOOL CPaneEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CPaneEditView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CPaneEditView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView diagnostics

#ifdef _DEBUG
void CPaneEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CPaneEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CWindowManiaDoc* CPaneEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWindowManiaDoc)));
	return (CWindowManiaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaneEditView message handlers

void CPaneEditView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	CWnd *pFrameWnd = GetParent();
	pFrameWnd->SetWindowText(_T("Edit View"));

	LOGFONT lf;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
	
	CClientDC dc(this);

	strcpy_s(lf.lfFaceName, _T("Arial"));
	lf.lfHeight = -MulDiv(10, GetDeviceCaps(dc.m_hDC, LOGPIXELSY), 72);;
	
	m_Font.CreateFontIndirect(&lf);

	SetFont(&m_Font);
}

void CPaneEditView::OnChange() 
{
	CWindowManiaDoc *pDoc = GetDocument();
	ASSERT(pDoc);
	GetWindowText(pDoc->m_csEdit);
		
	pDoc->UpdateAllViews(this);
}

void CPaneEditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CWindowManiaDoc *pDoc = GetDocument();
	ASSERT(pDoc);
	
	SetWindowText(pDoc->m_csEdit);
}



void CPaneEditView::OnFileOpen()
{
	// TODO: Add your command handler code here'
	char s[200];
	std::ostrstream ostr(s, 200);
	CFileDialog fileDlg(TRUE, fileDialogExt, NULL, OFN_FILEMUSTEXIST, fileDialogFilter);
	if (fileDlg.DoModal() == IDOK) {
		ostr << "Pathname: "
			<< fileDlg.GetPathName()
			<< std::endl
			<< "Filename: "
			<< fileDlg.GetFileName()
			<< std::endl
			<< "Extension: "
			<< fileDlg.GetFileExt()
			<< std::endl
			<< "File Title: "
			<< fileDlg.GetFileTitle()
			<< std::endl
			<< std::ends;
		CStdioFile f;
		CFileException exception;
		BOOL status;
		CString name;
		char b[65535];

		for (int a = 0; a < 65535; a++)
			b[a] = ' ';

		int x = 0;
		name = fileDlg.GetPathName();

		if (_access(name, 04) == 0)
			MessageBox("File is there","Status", MB_OK);

		try {
			std::ifstream file(name, std::ios::binary);
			while (!file.eof()) {
				file.read((char*)&b[x++], sizeof(char));
			}

			file.close();
		}
		catch (...) {
			MessageBox("File is too big to be loaded\n64k Maximum size\n-Returning!","Status", MB_OK);
			return;
		}

		status = f.Open(fileDlg.GetPathName(), CFile::modeRead, &exception);

		if (!status) {
			char s[100];
			sprintf_s(s, "Error opening file for readind. Code: %d", exception.m_cause);
			AfxMessageBox(s, MB_OK);
			return;
		}

		CWindowManiaDoc *pDoc = GetDocument();
		ASSERT(pDoc);
		pDoc->m_csEdit = (LPSTR)b;

		SetWindowText(pDoc->m_csEdit);
		pDoc->UpdateAllViews(this);

	}
	MessageBox(s, "Dialog Information", MB_ICONINFORMATION);
	return;
}





void CPaneEditView::OnFileSavetxt()
{
	// TODO: Add your command handler code here
	
	CFile file;
	static CString filePathName;
	CFileDialog fileDlg(FALSE, fileDialogExt, filePathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileDialogFilter);
	if (fileDlg.DoModal() == IDOK) {
		CString oldPathName(filePathName);
		filePathName = fileDlg.GetPathName();
	}

	char buffer[65535];
	UINT length = GetWindowTextLength();

	if (length == 0) {
		MessageBox("Nothing to Save", "Warning", MB_OK);
		return;
	}

	if (!file.Open(filePathName, CFile::modeCreate | CFile::modeWrite))
	{
		CString msg("Can't open " + filePathName + "\nCheck the name.");
		MessageBox(msg, "File Save Error", MB_ICONERROR);
		return;
	}

	char info[100];

	

	//FmtLines(TRUE);
	GetWindowText((LPSTR)buffer, length + 1);

	file.Write(buffer, length + 1);
	file.Close();
	//m_Edit.SetFocus();
	// TODO: Add your command handler code here
}


void CPaneEditView::OnFileClear()
{
	// TODO: Add your command handler code here
	UINT length = GetWindowTextLength();
	if (length > 0) {
		int result = MessageBox("Are you sure?\nProceed", "Caution", MB_ICONQUESTION | MB_YESNO);
		if (result == IDYES) {
			CWindowManiaDoc *pDoc = GetDocument();
			ASSERT(pDoc);
			pDoc->m_csEdit = "";
			SetWindowText(pDoc->m_csEdit);
			pDoc->UpdateAllViews(this);

		}		
	}
}



