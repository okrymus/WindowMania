#pragma once


// CNewDirDlg dialog

class CNewDirDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewDirDlg)

public:
	CNewDirDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewDirDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW_DIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_dir;
};
