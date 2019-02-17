// paneFileManager.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "paneFileManager.h"
#include "SelRootFolderDlg.h"
#include "afxdialogex.h"


// CFileManager

IMPLEMENT_DYNCREATE(CFileManager, CFormView)

CFileManager::CFileManager()
	: CFormView(IDD_FILE_MANAGER)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CFileManager::~CFileManager()
{
}

void CFileManager::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOLDERS_TREE, m_cTreeCtrl);
//	DDX_Control(pDX, IDC_LIST_SEL, m_cListCtrlSel);
	DDX_Control(pDX, IDC_LIST_REM, m_cListCtrlRem);
}

BEGIN_MESSAGE_MAP(CFileManager, CFormView)
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_DEL_FILES, &CMFCShellExtensionDlg::OnBnClickedDelFiles)
	//ON_BN_CLICKED(IDC_ADD_FILES, &CMFCShellExtensionDlg::OnBnClickedAddFiles)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_DEFAULT, IDC_RADIO_CUSTOM, OnRootFolderChanged)
	ON_NOTIFY(TVN_SELCHANGED, IDC_FOLDERS_TREE, OnTvnSelchanged)
	ON_COMMAND(ID_FILE_CHANGEDIRECTORY, &CFileManager::OnFileChangedirectory)
END_MESSAGE_MAP()


// CFileManager diagnostics

#ifdef _DEBUG
void CFileManager::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFileManager::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFileManager message handlers




void CFileManager::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CFrameWnd *pFrameWnd = (CFrameWnd*)GetParent();
	pFrameWnd->SetWindowText("File Shell Extension");
	
	pFrameWnd->ModifyStyle(WS_THICKFRAME, WS_DLGFRAME, SWP_FRAMECHANGED);

	//pFrameWnd->ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, WS_DLGFRAME, SWP_FRAMECHANGED);
	pFrameWnd->RecalcLayout();

	ResizeParentToFit();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CheckRadioButton(IDC_RADIO_DEFAULT, IDC_RADIO_CUSTOM, IDC_RADIO_DEFAULT);
	// Not displaying subfolders
	//m_cListCtrlSel.SetItemTypes(SHCONTF_NONFOLDERS);
	m_cListCtrlRem.SetItemTypes(SHCONTF_NONFOLDERS);
	// Passing project files map pointer to both shell list controls
	//m_cListCtrlSel.SetProjectFiles(&m_cProjFileMap);
	m_cListCtrlRem.SetProjectFiles(&m_cProjFileMap);
	// Setting list control filters
	//m_cListCtrlSel.SetFilter(LISTFILTER_SELECTED);
	m_cListCtrlRem.SetFilter(LISTFILTER_REMAINING);
	HTREEITEM hParentItem = m_cTreeCtrl.GetRootItem();
	m_cTreeCtrl.SelectItem(hParentItem);
	m_cTreeCtrl.Expand(hParentItem, TVE_EXPAND);
}


void CFileManager::OnTvnSelchangedFoldersTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileManager::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFileManager::OnBnClickedDelFiles()
{
	CopyFiles(TRUE);
}

void CFileManager::OnBnClickedAddFiles()
{
	CopyFiles(FALSE);
}

void CFileManager::OnRootFolderChanged(UINT uID)
{
	BOOL bCustomFolder = (uID == IDC_RADIO_CUSTOM);
	if (bCustomFolder == m_bCustomFolder)
		return;
	CString cRootFolder = m_cRootFolder;
	if (uID == IDC_RADIO_CUSTOM)
	{
		CSelRootFolderDlg cDlg;
		cDlg.m_cRootFolder = m_cRootFolder;
		if (cDlg.DoModal() != IDOK)
		{
			int nID = bCustomFolder ? IDC_RADIO_DEFAULT : IDC_RADIO_CUSTOM;
			CheckRadioButton(IDC_RADIO_DEFAULT, IDC_RADIO_CUSTOM, nID);
			return;
		}
		cRootFolder = m_cRootFolder = cDlg.m_cRootFolder;
	}
	else
		cRootFolder.Empty();
	SetDlgItemText(IDC_EDIT_ROOTFOLDER, cRootFolder);
	m_cTreeCtrl.SetRootFolder(cRootFolder);
	m_bCustomFolder = bCustomFolder;
}

void CFileManager::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = m_cTreeCtrl.GetSelectedItem();
	CString cFolderPath;
	if (m_cTreeCtrl.GetItemPath(cFolderPath, hItem))
	{
		// Retrieving an existing (or adding a new: bAddIfNotFound = TRUE) project files array
		CStringArray *pFilesArr = m_cProjFileMap.GetFiles(cFolderPath, TRUE);
		// and using the resultant pointer as the selected tree item data
		m_cTreeCtrl.SetItemDataEx(hItem, (DWORD_PTR)pFilesArr);
		// Refreshing both list controls contents
		//m_cListCtrlSel.DisplayFolder(cFolderPath);
		m_cListCtrlRem.DisplayFolder(cFolderPath);
	}
}

void CFileManager::CopyFiles(BOOL bDelete)
{
	HTREEITEM hItem = m_cTreeCtrl.GetSelectedItem();
	CString cFolderPath;
	CStringArray *pFilesArr = (hItem && m_cTreeCtrl.GetItemPath(cFolderPath, hItem)) ? m_cProjFileMap.GetFiles(cFolderPath, FALSE) : NULL;
	if (!pFilesArr)
		return;
	// Moving files from one list control to the other
	CProjectListCtrl *pSrcList = bDelete ? &m_cListCtrlSel : &m_cListCtrlRem;
	CProjectListCtrl *pDstList = bDelete ? &m_cListCtrlRem : &m_cListCtrlSel;
	CUIntArray cItemPosArr;
	POSITION pos = pSrcList->GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = pSrcList->GetNextSelectedItem(pos);
		cItemPosArr.Add((UINT)nItem);
	}
	int nCount = cItemPosArr.GetSize();
	if (nCount > 0)
	{
		// Copying selected files from source to destination list control
		pDstList->CopyItems((const CMFCShellListCtrlEx&)*pSrcList, cItemPosArr);
		// and removing them from the source list control
		pos = pSrcList->GetFirstSelectedItemPosition();
		while (pos)
		{
			int nItem = pSrcList->GetNextSelectedItem(pos);
			pSrcList->DeleteItem(nItem);
			pos = pSrcList->GetFirstSelectedItemPosition();
		}
	}
	// Updating project files map
	pFilesArr->RemoveAll();
	nCount = m_cListCtrlSel.GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		CString cFileName = m_cListCtrlSel.GetItemText(i, CMFCShellListCtrl::AFX_ShellList_ColumnName);
		pFilesArr->Add(cFileName);
	}
}



void CFileManager::OnFileChangedirectory()
{
	// TODO: Add your command handler code here
	CString cRootFolder = m_cRootFolder;

		CSelRootFolderDlg cDlg;
		cDlg.m_cRootFolder = m_cRootFolder;
		if (cDlg.DoModal() != IDOK)
		{
			CheckRadioButton(IDC_RADIO_DEFAULT, IDC_RADIO_CUSTOM, IDC_RADIO_DEFAULT);
			return;
		}
		cRootFolder = m_cRootFolder = cDlg.m_cRootFolder;
	
		CheckRadioButton(IDC_RADIO_DEFAULT, IDC_RADIO_CUSTOM, IDC_RADIO_CUSTOM);

	SetDlgItemText(IDC_EDIT_ROOTFOLDER, cRootFolder);
	m_cTreeCtrl.SetRootFolder(cRootFolder);
}
