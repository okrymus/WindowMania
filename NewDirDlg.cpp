// NewDirDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "NewDirDlg.h"
#include "afxdialogex.h"


// CNewDirDlg dialog

IMPLEMENT_DYNAMIC(CNewDirDlg, CDialog)

CNewDirDlg::CNewDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_NEW_DIR, pParent)
	, m_dir(_T(""))
{

}

CNewDirDlg::~CNewDirDlg()
{
}

void CNewDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dir);
}


BEGIN_MESSAGE_MAP(CNewDirDlg, CDialog)
END_MESSAGE_MAP()


// CNewDirDlg message handlers
