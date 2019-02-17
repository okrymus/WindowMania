// PaneEditView.h : interface of the CPaneEditView class
//

#if !defined(AFX_PANEEDITVIEW_H__59AD5ED7_1D2A_4CB2_8BA3_B3CC8E83ED24__INCLUDED_)
#define AFX_PANEEDITVIEW_H__59AD5ED7_1D2A_4CB2_8BA3_B3CC8E83ED24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaneEditView : public CEditView
{
protected: // create from serialization only
	CPaneEditView();
	DECLARE_DYNCREATE(CPaneEditView)

// Attributes
public:
	CWindowManiaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaneEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaneEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_Font;
// Generated message map functions
protected:
	//{{AFX_MSG(CPaneEditView)
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSavetxt();
	afx_msg void OnFileClear();
	afx_msg void OnEditCopy();
};

#ifndef _DEBUG  // debug version in PaneEditView.cpp
inline CWindowManiaDoc* CPaneEditView::GetDocument()
   { return (CWindowManiaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANEEDITVIEW_H__59AD5ED7_1D2A_4CB2_8BA3_B3CC8E83ED24__INCLUDED_)
