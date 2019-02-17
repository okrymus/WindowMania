#if !defined(AFX_PANEFORMVIEW_H__F5438A73_D5D1_4057_B232_0F64051A5303__INCLUDED_)
#define AFX_PANEFORMVIEW_H__F5438A73_D5D1_4057_B232_0F64051A5303__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaneFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPaneFormView : public CFormView
{
protected:
	CPaneFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPaneFormView)

// Form Data
public:
	//{{AFX_DATA(CPaneFormView)
	enum { IDD = IDD_PANEFORMVIEW_FORM };
	CEdit	m_Edit;
	//}}AFX_DATA

// Attributes
public:
	CWindowManiaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPaneFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPaneFormView)
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpentxt();
	afx_msg void OnFileClear();
	afx_msg void OnFileSave();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnEditCut();
	afx_msg void OnEditUndo();
};

#ifndef _DEBUG  // debug version in PaneEditView.cpp
inline CWindowManiaDoc* CPaneFormView::GetDocument()
{ return (CWindowManiaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEFORMVIEW_H__F5438A73_D5D1_4057_B232_0F64051A5303__INCLUDED_)
