// FileRenameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "FileRenameDlg.h"
#include "afxdialogex.h"


// CFileRenameDlg dialog

IMPLEMENT_DYNAMIC(CFileRenameDlg, CDialog)

CFileRenameDlg::CFileRenameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RENAME, pParent)
	, m_fileNewName(_T(""))
{

}

CFileRenameDlg::~CFileRenameDlg()
{
}

void CFileRenameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fileNewName);
}

BEGIN_MESSAGE_MAP(CFileRenameDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CFileRenameDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CFileRenameDlg message handlers
CString CFileRenameDlg::GetFileName() const
{
	return m_fileNewName;
}



void CFileRenameDlg::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
