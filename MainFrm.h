// MainFrm.h : interface of the CMainFrame class
//


#if !defined(AFX_MAINFRM_H__8F836C1D_F17C_45A9_997B_BBA5C1ADF9B8__INCLUDED_)
#define AFX_MAINFRM_H__8F836C1D_F17C_45A9_997B_BBA5C1ADF9B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MDIPaneSplitterWnd.h"
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateSplitterChildren();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMDIPaneSplitterWnd m_wndSplitter;

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnInfoDate();
	afx_msg void OnFileshellFile();
	afx_msg void OnWindowsDirectoryoperation();
	afx_msg void OnWindowsFileoperation();
	afx_msg void OnWindowsEdit();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8F836C1D_F17C_45A9_997B_BBA5C1ADF9B8__INCLUDED_)
