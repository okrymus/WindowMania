#if !defined(AFX_MDIPANESPLITTERWND_H__0093AF2E_E2EC_4CAF_94AA_29DCB1EAF035__INCLUDED_)
#define AFX_MDIPANESPLITTERWND_H__0093AF2E_E2EC_4CAF_94AA_29DCB1EAF035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MDIPaneSplitterWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMDIPaneSplitterWnd window

class CMDIPaneSplitterWnd : public CSplitterWnd
{
// Construction
public:
	CMDIPaneSplitterWnd();

// Attributes
public:
protected:
	CSize m_MultiPaneInfo;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIPaneSplitterWnd)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateChildren(CDocument *pDoc, int selectWindows = -1);
	BOOL CreateMDIPaneChild(CCreateContext *pContext, BOOL bSizeParent = FALSE);
	BOOL CreateMDIPane(int iRow, int iCol, CSize sizeInit, CCreateContext *pContext);
	virtual ~CMDIPaneSplitterWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDIPaneSplitterWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIPANESPLITTERWND_H__0093AF2E_E2EC_4CAF_94AA_29DCB1EAF035__INCLUDED_)
