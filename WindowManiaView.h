// WindowManiaView.h : interface of the CWindowManiaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WindowManiaVIEW_H__7779EFC9_CE7A_440E_B962_F5A0EB9383EF__INCLUDED_)
#define AFX_WindowManiaVIEW_H__7779EFC9_CE7A_440E_B962_F5A0EB9383EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWindowManiaView : public CView
{
protected: // create from serialization only
	CWindowManiaView();
	DECLARE_DYNCREATE(CWindowManiaView)

// Attributes
public:
	CWindowManiaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowManiaView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWindowManiaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWindowManiaView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WindowManiaView.cpp
inline CWindowManiaDoc* CWindowManiaView::GetDocument()
   { return (CWindowManiaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WindowManiaVIEW_H__7779EFC9_CE7A_440E_B962_F5A0EB9383EF__INCLUDED_)
