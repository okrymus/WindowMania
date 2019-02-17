#if !defined(AFX_PANEDIALOGVIEW_H__01D25E2C_DE06_4F19_92A6_020407062924__INCLUDED_)
#define AFX_PANEDIALOGVIEW_H__01D25E2C_DE06_4F19_92A6_020407062924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneDialogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaneDialogView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPaneDialogView : public CFormView
{
protected:
	CPaneDialogView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPaneDialogView)

// Form Data
public:
	//{{AFX_DATA(CPaneDialogView)
	enum { IDD = IDD_FORM_NO_DOC };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneDialogView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPaneDialogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPaneDialogView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString time_label;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEDIALOGVIEW_H__01D25E2C_DE06_4F19_92A6_020407062924__INCLUDED_)
