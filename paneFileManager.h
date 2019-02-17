#pragma once

#include "afxcmn.h"
#include "ProjectListCtrl.h"
#include "ProjFilesArray.h"
#include "MFCShellTreeCtrlEx.h"

// CFileManager form view

class CFileManager : public CFormView
{
	DECLARE_DYNCREATE(CFileManager)

protected:
	CFileManager();           // protected constructor used by dynamic creation
	virtual ~CFileManager();
	HICON m_hIcon;
	BOOL m_bCustomFolder;
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_MANAGER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg HCURSOR OnQueryDragIcon();

	void CopyFiles(BOOL bDelete);

	afx_msg void OnBnClickedDelFiles();
	afx_msg void OnBnClickedAddFiles();
	afx_msg void OnRootFolderChanged(UINT uID);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedFoldersTree(NMHDR *pNMHDR, LRESULT *pResult);

	CMFCShellTreeCtrlEx m_cTreeCtrl;
	CProjectListCtrl m_cListCtrlSel;
	CProjectListCtrl m_cListCtrlRem;
	CProjFilesArray m_cProjFileMap;
	CString m_cRootFolder;
	afx_msg void OnFileChangedirectory();
};


