// WindowManiaDoc.h : interface of the CWindowManiaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WindowManiaDOC_H__49D8F3AF_8D99_4505_B349_457BCFF3155E__INCLUDED_)
#define AFX_WindowManiaDOC_H__49D8F3AF_8D99_4505_B349_457BCFF3155E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWindowManiaDoc : public CDocument
{
protected: // create from serialization only
	CWindowManiaDoc();
	DECLARE_DYNCREATE(CWindowManiaDoc)

// Attributes
public:
   CString m_csEdit;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowManiaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWindowManiaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWindowManiaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WindowManiaDOC_H__49D8F3AF_8D99_4505_B349_457BCFF3155E__INCLUDED_)
