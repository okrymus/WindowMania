// PaneFormView.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include <fstream>
#include <strstream>
#include <io.h>
#include "WindowManiaDoc.h"
#include "PaneFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const char fileDialogFilter[] = "C++ Files (*.cpp) | *.cpp|Header Files\
(*.h)|*.h|Resource Files (*.rc) | *.rc | Text Files (*.txt)|*.txt| All Files (*.*)| *.*||";
const char fileDialogExt[] = "cpp";

/////////////////////////////////////////////////////////////////////////////
// CPaneFormView

IMPLEMENT_DYNCREATE(CPaneFormView, CFormView)

CPaneFormView::CPaneFormView()
	: CFormView(CPaneFormView::IDD)
{
	//{{AFX_DATA_INIT(CPaneFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPaneFormView::~CPaneFormView()
{
}

void CPaneFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPaneFormView)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPaneFormView, CFormView)
	//{{AFX_MSG_MAP(CPaneFormView)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN, &CPaneFormView::OnFileOpentxt)
	ON_COMMAND(ID_FILE_CLEAR, &CPaneFormView::OnFileClear)
	ON_COMMAND(ID_FILE_SAVETXT , &CPaneFormView::OnFileSave)
	ON_COMMAND(ID_EDIT_COPY, &CPaneFormView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CPaneFormView::OnEditPaste)
	ON_COMMAND(ID_EDIT_DELETE, &CPaneFormView::OnEditDelete)
	ON_COMMAND(ID_EDIT_CUT, &CPaneFormView::OnEditCut)
	ON_COMMAND(ID_EDIT_UNDO, &CPaneFormView::OnEditUndo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaneFormView diagnostics

#ifdef _DEBUG
void CPaneFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPaneFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWindowManiaDoc* CPaneFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWindowManiaDoc)));
	return (CWindowManiaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaneFormView message handlers

void CPaneFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	CWnd *pFrameWnd = GetParent();
	pFrameWnd->SetWindowText("Form View");

	pFrameWnd->ModifyStyle(WS_THICKFRAME, WS_DLGFRAME, SWP_FRAMECHANGED);

	ResizeParentToFit();
}

void CPaneFormView::OnChangeEdit1() 
{
	CWindowManiaDoc *pDoc = GetDocument();
	ASSERT(pDoc);
	m_Edit.GetWindowText(pDoc->m_csEdit);

	pDoc->UpdateAllViews(this);

}

void CPaneFormView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CWindowManiaDoc *pDoc = GetDocument();
	ASSERT(pDoc);
	
	m_Edit.SetWindowText(pDoc->m_csEdit);
	
}


void CPaneFormView::OnFileOpentxt()
{
	// TODO: Add your command handler code here
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
			AfxMessageBox("File is there", MB_OK);

		try {
			std::ifstream file(name, std::ios::binary);
			while (!file.eof()) {
				file.read((char*)&b[x++], sizeof(char));
			}

			file.close();
		}
		catch (...) {
			MessageBox("File is too big to be loaded\n64k Maximum size\n-Returning!","Warning", MB_OK);
			m_Edit.SetFocus();
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

		m_Edit.SetWindowText(pDoc->m_csEdit);
		pDoc->UpdateAllViews(this);

	}
	AfxMessageBox(s,MB_OK, MB_ICONINFORMATION);
	m_Edit.SetFocus();
	return;
}


void CPaneFormView::OnFileClear()
{
	// TODO: Add your command handler code here
	UINT length = m_Edit.GetWindowTextLength();
	if (length > 0) {
		int result = MessageBox("Are you sure?", "Caution", MB_ICONINFORMATION | MB_YESNO);

		if (result == IDYES) {
			CWindowManiaDoc *pDoc = GetDocument();
			ASSERT(pDoc);
			pDoc->m_csEdit = (LPSTR)"";

			m_Edit.SetWindowText(pDoc->m_csEdit);
			pDoc->UpdateAllViews(this);
		}
	}
	m_Edit.SetFocus();
}


void CPaneFormView::OnFileSave()
{
	CFile file;
	static CString filePathName;
	CFileDialog fileDlg(FALSE, fileDialogExt, filePathName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileDialogFilter);
	if (fileDlg.DoModal() == IDOK) {
		CString oldPathName(filePathName);
		filePathName = fileDlg.GetPathName();
	}

	char buffer[65535];

	UINT length = m_Edit.GetWindowTextLength();

	if (length == 0) {
		MessageBox("Nothing to Save", "Warning", MB_OK);
		m_Edit.SetFocus();
		return;
	}

	if (!file.Open(filePathName, CFile::modeCreate | CFile::modeWrite))
	{
		CString msg("Can't open " + filePathName + "\nCheck the name.");
		MessageBox(msg, "File Save Error", MB_ICONERROR);
		return;
	}

	char info[100];
	sprintf_s(info, "Saving %d Lines", m_Edit.GetLineCount());
	MessageBox(info, "File Save", MB_ICONINFORMATION | MB_OK);

	m_Edit.FmtLines(TRUE);
	m_Edit.GetWindowText((LPSTR)buffer, length + 1);

	file.Write(buffer, length + 1);
	file.Close();
	m_Edit.SetFocus();
	// TODO: Add your command handler code here
}


void CPaneFormView::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_Edit.Copy();
}


void CPaneFormView::OnEditPaste()
{
	// TODO: Add your command handler code here
	m_Edit.Paste();
}


void CPaneFormView::OnEditDelete()
{
	// TODO: Add your command handler code here
	m_Edit.ReplaceSel("");
}


void CPaneFormView::OnEditCut()
{
	// TODO: Add your command handler code here
	m_Edit.Cut();
}


void CPaneFormView::OnEditUndo()
{
	// TODO: Add your command handler code here
	m_Edit.Undo();
}
