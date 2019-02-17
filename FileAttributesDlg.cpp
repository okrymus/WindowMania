// FileAttributesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "FileAttributesDlg.h"
#include "afxdialogex.h"

// FileAttributesDlg.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
ATTRIB[+R | -R][+A | -A][+S | -S][+H | -H][drive:][path][filename]
[/ S[/ D]]

+ Sets an attribute.
- Clears an attribute.
R   Read - only file attribute.
A   Archive file attribute.
S   System file attribute.
H   Hidden file attribute.
[drive:][path][filename]
Specifies a file or files for attrib to process.
/ S  Processes matching files in the current folder
and all subfolders.
/ D  Processes folders as well.
*/
/////////////////////////////////////////////////////////////////////////////
// CFileAttributesDlg dialog

CFileAttributesDlg::CFileAttributesDlg(DWORD dwAttributes, CWnd* pParent /*=NULL*/)
	: m_dwAttributes(dwAttributes), CDialog(CFileAttributesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileAttributesDlg)
	m_bArchive = 0 != (m_dwAttributes & FILE_ATTRIBUTE_ARCHIVE);
	m_bHidden = 0 != (m_dwAttributes & FILE_ATTRIBUTE_HIDDEN);
	m_bReadOnly = 0 != (m_dwAttributes & FILE_ATTRIBUTE_READONLY);
	m_bSystem = 0 != (m_dwAttributes & FILE_ATTRIBUTE_SYSTEM);
	//}}AFX_DATA_INIT
}


void CFileAttributesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileAttributesDlg)
	DDX_Check(pDX, IDC_ARCHIVE, m_bArchive);
	DDX_Check(pDX, IDC_HIDDEN, m_bHidden);
	DDX_Check(pDX, IDC_READONLY, m_bReadOnly);
	DDX_Check(pDX, IDC_SYSTEM, m_bSystem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileAttributesDlg, CDialog)
	//{{AFX_MSG_MAP(CFileAttributesDlg)
	ON_BN_CLICKED(IDC_ARCHIVE, OnAttributes)
	ON_BN_CLICKED(IDC_SYSTEM, OnAttributes)
	ON_BN_CLICKED(IDC_HIDDEN, OnAttributes)
	ON_BN_CLICKED(IDC_READONLY, OnAttributes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileAttributesDlg message handlers

void CFileAttributesDlg::SetAttributes(DWORD dwAttributes)
{
	m_dwAttributes = dwAttributes;
	m_bArchive = 0 != (m_dwAttributes & FILE_ATTRIBUTE_ARCHIVE);
	m_bHidden = 0 != (m_dwAttributes & FILE_ATTRIBUTE_HIDDEN);
	m_bReadOnly = 0 != (m_dwAttributes & FILE_ATTRIBUTE_READONLY);
	m_bSystem = 0 != (m_dwAttributes & FILE_ATTRIBUTE_SYSTEM);
}

DWORD CFileAttributesDlg::GetAttributes() const
{
	return m_dwAttributes;
}

void CFileAttributesDlg::OnAttributes()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	// an archive file or directory
	if (m_bArchive)
		//Bitwise OR (0x00000020)
		m_dwAttributes |= FILE_ATTRIBUTE_ARCHIVE;
	else
		// Bitwise AND  (0x00000020)
		m_dwAttributes &= ~FILE_ATTRIBUTE_ARCHIVE;

	// A file or directory that the operating system 
	if (m_bSystem)
		// Bitwise OR (0x000000040)
		m_dwAttributes |= FILE_ATTRIBUTE_SYSTEM;
	else
		//Bitwise AND (0x000000040)
		m_dwAttributes &= ~FILE_ATTRIBUTE_SYSTEM;

	// The file or directory is hidden.
	if (m_bHidden)
		//Bitwise OR (0x00000002)
		m_dwAttributes |= FILE_ATTRIBUTE_HIDDEN;
	else
		// Bitwise AND (0x00000002)
		m_dwAttributes &= ~FILE_ATTRIBUTE_HIDDEN;

	if (m_bReadOnly)
		// Bitwise OR (0x00000001)
		m_dwAttributes |= FILE_ATTRIBUTE_READONLY;
	else
		// Bitwise AND (0x00000001)
		m_dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
}

