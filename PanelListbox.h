#if !defined(AFX_PANELLISTBOX_H__8759CF35_7B30_42ED_91A5_C4E7EDC98E4B__INCLUDED_)
#define AFX_PANELLISTBOX_H__8759CF35_7B30_42ED_91A5_C4E7EDC98E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PanelListbox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPanelListbox window

class CPanelListbox : public CListBox
{
// Construction
public:
	CPanelListbox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanelListbox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	int AddItem( int type, const CString& text );
	virtual ~CPanelListbox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPanelListbox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	HICON m_file;
	HICON m_folder;
	HICON m_folder_up;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANELLISTBOX_H__8759CF35_7B30_42ED_91A5_C4E7EDC98E4B__INCLUDED_)
