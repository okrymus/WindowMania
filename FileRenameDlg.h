#pragma once


// CFileRenameDlg dialog

class CFileRenameDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileRenameDlg)

public:
	CFileRenameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFileRenameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_fileNewName;
	CString GetFileName() const;

	afx_msg void OnEnChangeEdit1();
};
