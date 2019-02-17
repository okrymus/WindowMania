// ChangeDir.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "ChangeDir.h"
#include "afxdialogex.h"


// CChangeDir dialog

IMPLEMENT_DYNAMIC(CChangeDir, CDialog)

CChangeDir::CChangeDir(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_CHDIR, pParent)
	, mPathName(_T(""))
{

}

CChangeDir::~CChangeDir()
{
}

void CChangeDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mPathName);
}


BEGIN_MESSAGE_MAP(CChangeDir, CDialog)
END_MESSAGE_MAP()


// CChangeDir message handlers
