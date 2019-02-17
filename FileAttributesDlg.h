#pragma once


#if !defined(AFX_FILEATTRIBUTESDLG_H__A1C02CE4_0163_42CC_94A0_C32EEB7C1B39__INCLUDED_)
#define AFX_FILEATTRIBUTESDLG_H__A1C02CE4_0163_42CC_94A0_C32EEB7C1B39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileAttributesDlg dialog

class CFileAttributesDlg : public CDialog
{
	// Construction
public:
	DWORD GetAttributes() const;
	void SetAttributes(DWORD dwAttributes);
	CFileAttributesDlg(DWORD dwAttributes, CWnd* pParent = NULL);   // standard constructor

	enum { IDD = IDD_ATTRIBUTESDLG };
	BOOL	m_bArchive;
	BOOL	m_bHidden;
	BOOL	m_bReadOnly;
	BOOL	m_bSystem;
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileAttributesDlg)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileAttributesDlg)
	afx_msg void OnAttributes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	DWORD m_dwAttributes;
};

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_FILEATTRIBUTESDLG_H__A1C02CE4_0163_42CC_94A0_C32EEB7C1B39__INCLUDED_)


