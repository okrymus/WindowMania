#pragma once


// CChangeDir dialog

class CChangeDir : public CDialog
{
	DECLARE_DYNAMIC(CChangeDir)

public:
	CChangeDir(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChangeDir();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHDIR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString mPathName;
};
