// FileOperateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "FileOperateDlg.h"
#include "FileAttributesDlg.h"
#include "FileRenameDlg.h"
#include "FileOperate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// operation types
enum { OT_COPY = 0, OT_DEL, OT_MOVE, OT_REN, OT_XCOPY, OT_SETATTRIBUTES };

// CFileOperateDlg

IMPLEMENT_DYNCREATE(CFileOperateDlg, CFormView)

CFileOperateDlg::CFileOperateDlg()
	: CFormView(IDD_FILE_OPERATION)	
	, m_nOperationType(OT_COPY)
{
	m_sDestination = _T("");
	m_sSource = _T("");
	m_bHidePrompt = TRUE;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hBrowse = AfxGetApp()->LoadIcon(IDI_BROWSE);
}

CFileOperateDlg::~CFileOperateDlg()
{
}

void CFileOperateDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nOperationType);
	DDX_Text(pDX, IDC_SOURCE, m_sSource);
	DDX_Text(pDX, IDC_DESTINATION, m_sDestination);
	DDX_Check(pDX, IDC_HIDEPROMPT, m_bHidePrompt);
}

BEGIN_MESSAGE_MAP(CFileOperateDlg, CFormView)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_RADIO1, OnSelOperations)
	ON_BN_CLICKED(IDC_BROWSESRC, OnBrowsesrc)
	ON_BN_CLICKED(IDC_RADIO2, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO3, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO4, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO5, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO7, OnSelOperations)
	ON_BN_CLICKED(IDC_BROWSEDES, OnBrowsedes)
	ON_COMMAND(ID_EDIT_COPY, &CFileOperateDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_DELETE, &CFileOperateDlg::OnEditDelete)
	ON_COMMAND(ID_EDIT_MOVE, &CFileOperateDlg::OnEditMove)
	ON_COMMAND(ID_EDIT_RENAME, &CFileOperateDlg::OnEditRename)
	ON_COMMAND(ID_EDIT_XCOPY, &CFileOperateDlg::OnEditXcopy)
	ON_COMMAND(ID_EDIT_SETATTRIBUTE, &CFileOperateDlg::OnEditSetattribute)
	ON_BN_CLICKED(IDC_BUTTON2, &CFileOperateDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CFileOperateDlg diagnostics

void CFileOperateDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFileOperateDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif


// CFileOperateDlg message handlers
void CFileOperateDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CFrameWnd *pFrameWnd = (CFrameWnd*)GetParent();
	pFrameWnd->SetWindowText("File Operation");

	pFrameWnd->ModifyStyle(WS_THICKFRAME, WS_DLGFRAME, SWP_FRAMECHANGED);
	pFrameWnd->RecalcLayout();

	ResizeParentToFit();

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileOperateDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CFileOperateDlg::OnTest()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
//	if (m_sSource.IsEmpty())
	//	return; // nothing can be done without a source

	if (isDirSelected()) {

		BOOL bResult = TRUE;
		BOOL bNeedUpdate = FALSE;
		int nFlag = 0;
		CFileAttributesDlg dlg(0);
		CFileRenameDlg dlg2;

		switch (m_nOperationType)
		{
		case OT_COPY:
			bResult = CFileOperate::Copy(m_sSource, m_sDestination, m_bHidePrompt);
			break;
		case OT_DEL:
			bResult = CFileOperate::Del(m_sSource, m_bHidePrompt);
			bNeedUpdate = TRUE;
			break;

		case OT_MOVE:
			bResult = CFileOperate::Move(m_sSource, m_sDestination, m_bHidePrompt);
			bNeedUpdate = TRUE;
			break;

		case OT_REN:
			dlg2.m_fileNewName = m_sSource;
			if (dlg2.DoModal() == IDOK)
				bResult = CFileOperate::Ren(m_sSource, dlg2.GetFileName(), m_bHidePrompt);
			//bResult = CFileOperate::Ren(m_sSource, m_sDestination, m_bHidePrompt);
			bNeedUpdate = TRUE;
			break;

		case OT_XCOPY:
			bResult = CFileOperate::XCopy(m_sSource, m_sDestination, m_bHidePrompt);
			break;

		case OT_SETATTRIBUTES:
			dlg.SetAttributes(CFileOperate::GetAttribute(m_sSource));
			if (dlg.DoModal() == IDOK)
				bResult = CFileOperate::SetAttribute(m_sSource, dlg.GetAttributes());
			break;

		default:
			break;
		}


		if (!bResult)
		{
			CString sMsg;
			CString sErr;
			sMsg.Format("Operation failed.\nCode: %x\n", ::GetLastError());
			MessageBox(sMsg);
		}
		else if (bNeedUpdate)
		{
			m_sSource.Empty();
			UpdateData(FALSE);
		}
	}
}

void CFileOperateDlg::OnSelOperations()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_nOperationType == OT_DEL || m_nOperationType == OT_SETATTRIBUTES || m_nOperationType== OT_REN)
	{
		GetDlgItem(IDC_DESTINATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_BROWSEDES)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_DESTINATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_BROWSEDES)->EnableWindow(TRUE);
	}
}

bool CFileOperateDlg::isDirSelected() {

	switch (m_nOperationType) {
	case OT_COPY:
	case OT_MOVE:
	case OT_XCOPY:
		if (m_sSource.IsEmpty() || m_sDestination.IsEmpty() ){
			MessageBox("Please choose file source and destination", "Error!", MB_ICONINFORMATION | MB_OK);
			return false;
		}
		break;
	case OT_DEL:
	case OT_REN:
	case OT_SETATTRIBUTES:
		if (m_sSource.IsEmpty()) {
			MessageBox("Please choose file source", "Error!", MB_ICONINFORMATION | MB_OK);
			return false;
		}
		break;
	default: return false;
		
	}
	return true;
}


CString CFileOperateDlg::Browse()
{
	CString sResult;
	CString sDummy("Please select directory or file");
	CFileDialog dlg(TRUE, NULL, sDummy, OFN_OVERWRITEPROMPT);
	if (dlg.DoModal() == IDOK)
		sResult = dlg.GetPathName();

	CFileFind ff;
	if (!ff.FindFile(sResult))
	{
		int nPos = sResult.ReverseFind('\\');
		if (nPos != -1)
			sResult = sResult.Left(nPos);
		else
			sResult.Empty();
	}

	ff.Close();
	return sResult;
}

void CFileOperateDlg::OnBrowsesrc()
{
	// TODO: Add your control notification handler code here
	CString str = Browse();
	if (!str.IsEmpty())
		m_sSource = str;
	UpdateData(FALSE);
}

void CFileOperateDlg::OnBrowsedes()
{
	// TODO: Add your control notification handler code here
	CString str = Browse();
	if (!str.IsEmpty())
		m_sDestination = str;
	UpdateData(FALSE);
}


void CFileOperateDlg::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_COPY;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnEditDelete()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_DEL;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnEditMove()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_MOVE;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnEditRename()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_REN;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnEditXcopy()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_XCOPY;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnEditSetattribute()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_SETATTRIBUTES;
	UpdateData(FALSE);
	OnSelOperations();
	OnTest();
}


void CFileOperateDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(WM_CLOSE, NULL, NULL);
}
