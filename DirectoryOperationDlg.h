#pragma once

#include "PanelListbox.h"

#define PANEL_NONE	0
#define PANEL_LEFT	1
#define PANEL_RIGHT	2
// CDirectoryOperationDlg form view

class CDirectoryOperationDlg : public CFormView
{
	DECLARE_DYNCREATE(CDirectoryOperationDlg)

protected:
	CDirectoryOperationDlg();           // protected constructor used by dynamic creation
	virtual ~CDirectoryOperationDlg();

public:
	enum { IDD = IDD_DIRECTORY_OPERATION };
	CEdit	m_rightEdit;
	CEdit	m_leftEdit;
	CPanelListbox	m_rightPanel;
	CPanelListbox	m_leftPanel;
	CEdit	m_feedbackCtrl;
	CString	m_leftFilter;
	CString	m_rightFilter;
	CString	m_leftDirStatic;
	CString	m_rightDirStatic;

	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnTest();
	afx_msg void OnButtonBrowse1();
	afx_msg void OnButtonBrowse2();
	afx_msg void OnSelOperations();
	afx_msg void OnSelchangeListLeftPanel();
	afx_msg void OnSelchangeListRightPanel();
	afx_msg void OnDblClickListLeftPanel();
	afx_msg void OnDblClickListRightPanel();
	void OnCopy();
	void OnMove();
	void OnDelete();
	void OnNewdir();
	void OnRename();
	DECLARE_MESSAGE_MAP()

private:
	// Panels
	void FillBothPanels();
	void FillLeftPanel();
	void FillRightPanel();
	void FillPanel(const CString& baseDirectory, CPanelListbox* panel, const CString& filter);
	void FillSelectedPanel();

	// Misc helpers
	CString GetLeftFilename();
	CString GetLeftDirectory();
	CString GetRightFilename();
	CString GetRightDirectory();
	CString GetFilename(CPanelListbox* panel, const CString& baseDirectory);
	CString GetDirectory(CPanelListbox* panel, const CString& baseDirectory);
	CString GetSelectedFilename();
	CString GetSelectedDirectory();
	CString GetNonSelectedDirectory();
	CString GetSelectedFile();
	CString EndPath(const CString& path);
	CString GetSelectedBaseDirectory();
	CString BrowseForFolder(const CString& initial);

	// Shared handlers
	void OnDblClickPanel(CPanelListbox* panel, CString& baseDirectory, const CString& filter);
	void OnSelchangePanel(CPanelListbox* panel, const CString& baseDirectory);

	// Private data
	CString m_rightBaseDirectory;
	CString m_leftBaseDirectory;
	int		m_selectedPanel;
public:
	virtual void OnInitialUpdate();

	int m_nOperationType;

	afx_msg void OnBnClickedRefresh();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEditCopy();
	afx_msg void OnEditDelete();
	afx_msg void OnEditMove();
	afx_msg void OnEditNewdirectory();
	afx_msg void OnEditRename();
};


