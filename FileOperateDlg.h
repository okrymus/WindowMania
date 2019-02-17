
#if !defined(AFX_FileOperatePRJDLG_H__9BCCAC9D_0520_4CAE_84F5_0C157891C1BC__INCLUDED_)
#define AFX_FileOperatePRJDLG_H__9BCCAC9D_0520_4CAE_84F5_0C157891C1BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// CFileOperateDlg form view

class CFileOperateDlg : public CFormView
{
	DECLARE_DYNCREATE(CFileOperateDlg)

protected:
	CFileOperateDlg();           // protected constructor used by dynamic creation
	virtual ~CFileOperateDlg();

public:
#//ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_OPERATION };
//#endif
//#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HICON m_hIcon;
	HICON m_hBrowse;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	afx_msg void OnSelOperations();
	afx_msg void OnBrowsesrc();
	afx_msg void OnBrowsedes();
	DECLARE_MESSAGE_MAP()

private:
	CString Browse();
	bool isDirSelected();
public:
	virtual void OnInitialUpdate();
	CString m_sSource;
	CString m_sDestination;
	BOOL	m_bHidePrompt;

	int m_nOperationType;
	afx_msg void OnEditCopy();
	afx_msg void OnEditDelete();
	afx_msg void OnEditMove();
	afx_msg void OnEditRename();
	afx_msg void OnEditXcopy();
	afx_msg void OnEditSetattribute();
	afx_msg void OnBnClickedButton2();
};

#endif // !defined(AFX_FileOperatePRJDLG_H__9BCCAC9D_0520_4CAE_84F5_0C157891C1BC__INCLUDED_)

