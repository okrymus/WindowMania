// DirectoryOperationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "DirectoryOperate.h"
#include "NewDirDlg.h"
#include "DirectoryOperationDlg.h"
#include "FileRenameDlg.h"

enum { OT_COPY = 0, OT_DEL, OT_MOVE, OT_NEWDIR, OT_REN };
// CDirectoryOperationDlg

int CALLBACK BFFCallbackProc(HWND hwnd, UINT uMsg, LPARAM /*lParam*/, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
		::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
	return 0;
}
IMPLEMENT_DYNCREATE(CDirectoryOperationDlg, CFormView)

CDirectoryOperationDlg::CDirectoryOperationDlg()
	: CFormView(IDD_DIRECTORY_OPERATION)
	, m_nOperationType(OT_COPY)
{
	m_leftFilter = _T("*.*");
	m_rightFilter = _T("*.*");
	m_leftDirStatic = _T("");
	m_rightDirStatic = _T("");
	m_rightBaseDirectory = _T("C:\\");
	m_leftBaseDirectory = _T("C:\\");
}

CDirectoryOperationDlg::~CDirectoryOperationDlg()
{
}

void CDirectoryOperationDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nOperationType);
	DDX_Control(pDX, IDC_LIST_RIGHT_PANEL, m_rightPanel);
	DDX_Control(pDX, IDC_LIST_LEFT_PANEL, m_leftPanel);
	DDX_Control(pDX, IDC_EDIT_FEEDBACK, m_feedbackCtrl);
	DDX_Text(pDX, IDC_STATIC_DIR1, m_leftDirStatic);
	DDX_Text(pDX, IDC_STATIC_DIR2, m_rightDirStatic);

}

BEGIN_MESSAGE_MAP(CDirectoryOperationDlg, CFormView)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_1, OnButtonBrowse1)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE_2, OnButtonBrowse2)
	ON_BN_CLICKED(IDC_RADIO1, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO2, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO3, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO4, OnSelOperations)
	ON_BN_CLICKED(IDC_RADIO5, OnSelOperations)
	ON_LBN_SELCHANGE(IDC_LIST_LEFT_PANEL, OnSelchangeListLeftPanel)
	ON_LBN_SELCHANGE(IDC_LIST_RIGHT_PANEL, OnSelchangeListRightPanel)
	ON_LBN_DBLCLK(IDC_LIST_LEFT_PANEL, OnDblClickListLeftPanel)
	ON_LBN_DBLCLK(IDC_LIST_RIGHT_PANEL, OnDblClickListRightPanel)
	ON_BN_CLICKED(IDC_REFRESH, &CDirectoryOperationDlg::OnBnClickedRefresh)
	ON_BN_CLICKED(IDC_BUTTON2, &CDirectoryOperationDlg::OnBnClickedButton2)
	ON_COMMAND(ID_EDIT_COPY, &CDirectoryOperationDlg::OnEditCopy)
	ON_COMMAND(ID_EDIT_DELETE, &CDirectoryOperationDlg::OnEditDelete)
	ON_COMMAND(ID_EDIT_MOVE, &CDirectoryOperationDlg::OnEditMove)
	ON_COMMAND(ID_EDIT_NEWDIRECTORY, &CDirectoryOperationDlg::OnEditNewdirectory)
	ON_COMMAND(ID_EDIT_RENAME, &CDirectoryOperationDlg::OnEditRename)
END_MESSAGE_MAP()


// CDirectoryOperationDlg diagnostics

void CDirectoryOperationDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDirectoryOperationDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif


// CDirectoryOperationDlg message handlers
void CDirectoryOperationDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	CFrameWnd *pFrameWnd = (CFrameWnd*)GetParent();
	pFrameWnd->SetWindowText("Directory Operation");
	pFrameWnd->ModifyStyle(WS_THICKFRAME , WS_DLGFRAME, SWP_FRAMECHANGED);

	//pFrameWnd->ModifyStyle(WS_THICKFRAME | WS_MAXIMIZEBOX, WS_DLGFRAME, SWP_FRAMECHANGED);
	pFrameWnd->RecalcLayout();

	ResizeParentToFit();

	FillBothPanels();
}

void CDirectoryOperationDlg::OnSelOperations()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}


void CDirectoryOperationDlg::OnTest()
{
	// TODO: Add your control notification handler code here
	switch (m_nOperationType)
	{
	case OT_COPY:
		OnCopy();
		break;
	case OT_DEL:
		OnDelete();
		break;
	case OT_MOVE:
		OnMove();
		break;
	case OT_NEWDIR:
		OnNewdir();
		break;
	case OT_REN:
		OnRename();
		break;
	default:
		break;
	}
}

void CDirectoryOperationDlg::OnCopy()
{
	CDirectoryOperate cdo(&m_feedbackCtrl);
	CString target = GetNonSelectedDirectory();

	CString filename = GetSelectedFilename();
	if (filename.GetLength())
	{
		if (!cdo.CopyFile(filename, target))
			AfxMessageBox(cdo.GetErrorMessage());
		else
			FillSelectedPanel();
	}
	else
	{
		CString directory;
		directory = GetSelectedDirectory();
		if (directory.GetLength())
		{
			CString text = GetSelectedFile();
			target = EndPath(target) + text;

			if (cdo.CreateDirectory(target))
			{
				if (!cdo.CopyDirectories(directory, target))
					AfxMessageBox(cdo.GetErrorMessage());

				FillBothPanels();

			}
			else
				AfxMessageBox(cdo.GetErrorMessage());
		}
		else
			AfxMessageBox(IDS_MUST_SELECT_A_FILE);
	}

}

// Handler for the Rename button. Renames the file
void CDirectoryOperationDlg::OnRename()
{
	CString filename;
	CDirectoryOperate cdo(&m_feedbackCtrl);
	
	filename = GetSelectedFilename();
	CFileRenameDlg renDlg;
	renDlg.m_fileNewName = filename;
	
	if (filename.GetLength())
	{

		if (renDlg.DoModal()==IDOK)
		{
			if (cdo.RenameFile(filename,renDlg.m_fileNewName))
				FillSelectedPanel();
			else
				AfxMessageBox(cdo.GetErrorMessage());
		}

	}
	else
	{
		CString directory;
		directory = GetSelectedDirectory();
		if (directory.GetLength())
		{
			if (renDlg.DoModal() == IDOK)
			{
				if (cdo.RenameDirectory(directory, renDlg.m_fileNewName))
					FillSelectedPanel();
				else
					AfxMessageBox(cdo.GetErrorMessage());
			}
		}
		else
			AfxMessageBox(IDS_MUST_SELECT_A_FILE);
	}
}

//	Handler for the Delete button. Deletes the file
void CDirectoryOperationDlg::OnDelete()
{
	CString filename;
	CDirectoryOperate cdo(&m_feedbackCtrl);
	filename = GetSelectedFilename();

	if (filename.GetLength())
	{

		if (AfxMessageBox(IDS_SURE_TO_DELETE, MB_YESNO) == IDYES)
		{
			if (cdo.RemoveFile(filename))
				FillSelectedPanel();
			else
				AfxMessageBox(cdo.GetErrorMessage());
		}

	}
	else
	{
		CString directory;
		directory = GetSelectedDirectory();
		if (directory.GetLength())
		{
			if (AfxMessageBox(IDS_SURE_TO_DELETE_DIR, MB_YESNO) == IDYES)
			{
				if (cdo.RemoveDirectories(directory))
					FillSelectedPanel();
				else
					AfxMessageBox(cdo.GetErrorMessage());
			}
		}
		else
			AfxMessageBox(IDS_MUST_SELECT_A_FILE);
	}
}

void CDirectoryOperationDlg::OnMove()
{

	CDirectoryOperate cdo(&m_feedbackCtrl);
	CString filename = GetSelectedFilename();
	CString target = GetNonSelectedDirectory();

	if (filename.GetLength())
	{
		if (AfxMessageBox(IDS_SURE_TO_MOVE, MB_YESNO) == IDYES)
		{
			if (cdo.CopyFile(filename, target))
			{
				if (cdo.RemoveFile(filename))
					FillBothPanels();
				else
					AfxMessageBox(cdo.GetErrorMessage());
			}
			else
				AfxMessageBox(cdo.GetErrorMessage());
		}
	}
	else
	{
		CString directory;
		directory = GetSelectedDirectory();
		if (directory.GetLength())
		{
			if (AfxMessageBox(IDS_SURE_TO_MOVE_DIR, MB_YESNO) == IDYES)
			{

				CString text = GetSelectedFile();
				target = EndPath(target) + text;

				if (cdo.CreateDirectory(target))
				{
					if (cdo.CopyDirectories(directory, target))
					{
						if (cdo.RemoveDirectories(directory))
							FillBothPanels();
						else
							AfxMessageBox(cdo.GetErrorMessage());
					}
					else
						AfxMessageBox(cdo.GetErrorMessage());
				}
				else
					AfxMessageBox(cdo.GetErrorMessage());
			}
		}
		else
			AfxMessageBox(IDS_MUST_SELECT_A_FILE);
	}
}

void CDirectoryOperationDlg::OnNewdir()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::OnNewdir
Description :	Handler for the New dir button. Creates a
new directory in the selected panel.
============================================================*/
{

	CNewDirDlg 	dlg;
	if (dlg.DoModal() == IDOK)
	{
		CString directory = GetSelectedBaseDirectory();
		CString dir = EndPath(directory) + dlg.m_dir;

		CDirectoryOperate cdo(&m_feedbackCtrl);
		if (!cdo.CreateDirectory(dir))
			AfxMessageBox(cdo.GetErrorMessage());

		FillSelectedPanel();
	}

}


/////////////////////////////////////////////////////////////////////////////
// Child message notification handlers

void CDirectoryOperationDlg::OnSelchangeListLeftPanel()
{

	OnSelchangePanel(&m_leftPanel, m_leftBaseDirectory);
	m_selectedPanel = PANEL_LEFT;

}

void CDirectoryOperationDlg::OnSelchangeListRightPanel()
{

	OnSelchangePanel(&m_rightPanel, m_rightBaseDirectory);
	m_selectedPanel = PANEL_RIGHT;

}

void CDirectoryOperationDlg::OnDblClickListLeftPanel()
{
	UpdateData();
	OnDblClickPanel(&m_leftPanel, m_leftBaseDirectory, m_leftFilter);
	m_leftDirStatic = m_leftBaseDirectory;
	UpdateData(FALSE);
}

void CDirectoryOperationDlg::OnDblClickListRightPanel()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::OnDblClickListRightPanel
Description :	Handler for right list double click
============================================================*/
{

	UpdateData();
	OnDblClickPanel(&m_rightPanel, m_rightBaseDirectory, m_rightFilter);
	m_rightDirStatic = m_rightBaseDirectory;
	UpdateData(FALSE);

}

/////////////////////////////////////////////////////////////////////////////
// Notification handler helpers

//	Helper for the select - change handlers for
void CDirectoryOperationDlg::OnSelchangePanel(CPanelListbox* panel, const CString& baseDirectory)
{
	CString text;
	int index = panel->GetCurSel();
	if (index != LB_ERR)
	{
		panel->GetText(index, text);
		text = EndPath(baseDirectory) + text;
		m_feedbackCtrl.SetWindowText(text);
	}

}

void CDirectoryOperationDlg::OnDblClickPanel(CPanelListbox* panel, CString& baseDirectory, const CString& filter)
{
	CString text;
	int index = panel->GetCurSel();
	if (index != LB_ERR)
	{
		int data = panel->GetItemData(index);

		panel->GetText(index, text);
		if (data == 1)
		{
			if (baseDirectory.GetLength() && baseDirectory[baseDirectory.GetLength() - 1] != _TCHAR('\\'))
				baseDirectory += _TCHAR('\\');

			baseDirectory += text;
			FillPanel(baseDirectory, panel, filter);
		}
		else if (data == 3)
		{
			int found = baseDirectory.ReverseFind(_TCHAR('\\'));
			if (found != -1)
				baseDirectory = baseDirectory.Left(found);
			if (baseDirectory.GetLength() == 2)
				baseDirectory += _TCHAR('\\');
			FillPanel(baseDirectory, panel, filter);
		}
		else
		{
			text = EndPath(baseDirectory) + text;
			::ShellExecute(m_hWnd, _T("open"), text, NULL, NULL, SW_SHOWNORMAL);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// Panel helpers

void CDirectoryOperationDlg::FillBothPanels()
{

	FillLeftPanel();
	FillRightPanel();

}

void CDirectoryOperationDlg::FillLeftPanel()
{

	UpdateData();
	FillPanel(m_leftBaseDirectory, &m_leftPanel, m_leftFilter);
	m_leftDirStatic = m_leftBaseDirectory;
	UpdateData(FALSE);

}

void CDirectoryOperationDlg::FillRightPanel()
{

	UpdateData();
	FillPanel(m_rightBaseDirectory, &m_rightPanel, m_rightFilter);
	m_rightDirStatic = m_rightBaseDirectory;
	UpdateData(FALSE);

}

void CDirectoryOperationDlg::FillPanel(const CString &baseDirectory, CPanelListbox* panel, const CString &filter)
{

	panel->ResetContent();

	CDirectoryOperate		cdo(&m_feedbackCtrl);
	CStringArray 	stra;
	int max;
	int t;

	// Read directories
	cdo.EnumDirectories(baseDirectory, stra);

	// Add root directory
	if (baseDirectory.GetLength() > 3)
		panel->AddItem(3, _T(".."));

	// Add directories
	max = stra.GetSize();
	for (t = 0; t < max; t++)
		panel->AddItem(1, stra[t]);

	// Read files
	stra.RemoveAll();
	cdo.EnumFilesInDirectoryWithFilter(filter, baseDirectory, stra);

	// Add files
	max = stra.GetSize();
	for (t = 0; t < max; t++)
		panel->AddItem(2, stra[t]);

}

/////////////////////////////////////////////////////////////////////////////
// Misc helpers

CString CDirectoryOperationDlg::GetLeftFilename()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetLeftFilename
Description :	Returns the fully qualified filename in
the left panel.
============================================================*/
{
	return GetFilename(&m_leftPanel, m_leftBaseDirectory);
}

CString CDirectoryOperationDlg::GetRightFilename()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetRightFilename
Description :	Returns the fully qualified filename in
the right panel.
============================================================*/
{
	return GetFilename(&m_rightPanel, m_rightBaseDirectory);
}

CString CDirectoryOperationDlg::GetFilename(CPanelListbox* panel, const CString& baseDirectory)
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetFilename
Description :	Returns the filename in the panel "panel".
============================================================*/
{
	CString text;
	int index = panel->GetCurSel();
	if (index != LB_ERR)
	{
		int data = panel->GetItemData(index);
		if (data == 2)
		{
			panel->GetText(index, text);
			text = EndPath(baseDirectory) + text;
		}
	}

	return text;
}

CString CDirectoryOperationDlg::GetRightDirectory()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetRightDirectory
Description :	Gets the directory selected in the right
============================================================*/
{
	return GetDirectory(&m_rightPanel, m_rightBaseDirectory);
}

CString CDirectoryOperationDlg::GetLeftDirectory()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetLeftDirectory
Description :	Gets the directory selected in the left
panel.
============================================================*/
{
	return GetDirectory(&m_leftPanel, m_leftBaseDirectory);
}

CString CDirectoryOperationDlg::GetDirectory(CPanelListbox* panel, const CString& baseDirectory)
{
	CString text;
	int index = panel->GetCurSel();
	if (index != LB_ERR)
	{
		int data = panel->GetItemData(index);
		if (data == 1)
		{
			panel->GetText(index, text);
			text = EndPath(baseDirectory) + text;
		}
	}
	else
		text = baseDirectory;

	return text;
}

void CDirectoryOperationDlg::FillSelectedPanel()
{
	if (m_selectedPanel == PANEL_LEFT)
		FillLeftPanel();
	else
		FillRightPanel();

	if (m_leftBaseDirectory == m_rightBaseDirectory)
	{
		if (m_selectedPanel == PANEL_LEFT)
			FillRightPanel();
		else
			FillLeftPanel();
	}
}

CString CDirectoryOperationDlg::GetSelectedFilename()
{
	CString filename;
	if (m_selectedPanel == PANEL_LEFT)
		filename = GetLeftFilename();
	else if (m_selectedPanel == PANEL_RIGHT)
		filename = GetRightFilename();

	return filename;
}

CString CDirectoryOperationDlg::GetSelectedDirectory()
{
	CString directory;
	if (m_selectedPanel == PANEL_LEFT)
		directory = GetLeftDirectory();
	else if (m_selectedPanel == PANEL_RIGHT)
		directory = GetRightDirectory();

	return directory;
}

CString CDirectoryOperationDlg::GetNonSelectedDirectory()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetNonSelectedDirectory
Description :	Gets the directory selected in the non-
selected panel.
============================================================*/
{
	CString directory;
	if (m_selectedPanel == PANEL_LEFT)
		directory = GetRightDirectory();
	else if (m_selectedPanel == PANEL_RIGHT)
		directory = GetLeftDirectory();

	return directory;
}

CString CDirectoryOperationDlg::GetSelectedFile()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetSelectedFile
Description :	Gets the text of the selected item in the
last selected panel.
============================================================*/
{
	CString file;
	int		index;

	if (m_selectedPanel == PANEL_LEFT)
	{
		index = m_leftPanel.GetCurSel();
		if (index != LB_ERR)
			m_leftPanel.GetText(index, file);
	}
	else if (m_selectedPanel == PANEL_RIGHT)
	{
		index = m_rightPanel.GetCurSel();
		if (index != LB_ERR)
			m_rightPanel.GetText(index, file);
	}

	return file;
}

CString CDirectoryOperationDlg::EndPath(const CString& path)
{
	CString delimiter;
	if (path.GetLength() && path[path.GetLength() - 1] != _TCHAR('\\'))
		delimiter = _TCHAR('\\');

	return path + delimiter;
}

CString CDirectoryOperationDlg::GetSelectedBaseDirectory()
{
	CString directory;
	if (m_selectedPanel == PANEL_LEFT)
		directory = m_leftBaseDirectory;
	else if (m_selectedPanel == PANEL_RIGHT)
		directory = m_rightBaseDirectory;

	return directory;
}

void CDirectoryOperationDlg::OnButtonBrowse1()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetSelectedBaseDirectory
Description :	Handles selection of the first browse button.
Access :		Protected
Return :		nothing
Parameters :	none
============================================================*/
{
	CString directory = BrowseForFolder(m_leftBaseDirectory);
	if (directory.GetLength())
	{
		m_leftBaseDirectory = directory;
		FillLeftPanel();
	}
}

void CDirectoryOperationDlg::OnButtonBrowse2()
/* ============================================================
Function :		CDirectoryOperateDemoDlg::GetSelectedBaseDirectory
Description :	Handles selection of the second browse button.
============================================================*/
{
	CString directory = BrowseForFolder(m_rightBaseDirectory);
	if (directory.GetLength())
	{
		m_rightBaseDirectory = directory;
		FillRightPanel();
	}
}

CString CDirectoryOperationDlg::BrowseForFolder(const CString& initial)
/* ============================================================
Function :		CDirectoryOperateDemoDlg::BrowseForFolder
Description :	Displays the standard directory select
dialog.
============================================================*/
{
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	CString str;

	CString title;
	title.LoadString(IDS_SELECT_FOLDER);

	_TCHAR initialPath[_MAX_PATH];
	lstrcpy(initialPath, initial);

	_TCHAR buffer[_MAX_PATH];
	ZeroMemory(buffer, _MAX_PATH);

	bi.hwndOwner = AfxGetMainWnd()->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = title;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lpfn = BFFCallbackProc;
	bi.lParam = (LPARAM)initialPath;

	if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
	{
		if (SUCCEEDED(::SHGetPathFromIDList(pidl, buffer)))
		{
			str = buffer;
		}

		LPMALLOC smalloc;
		if (SUCCEEDED(SHGetMalloc(&smalloc)))
		{
			smalloc->Free(pidl);
			smalloc->Release();
		}
	}

	return str;
}


void CDirectoryOperationDlg::OnBnClickedRefresh()
{
	// TODO: Add your control notification handler code here
	CWaitCursor	wait;
	FillBothPanels();
}


void CDirectoryOperationDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(WM_CLOSE, NULL, NULL);
}


void CDirectoryOperationDlg::OnEditCopy()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_COPY;
	UpdateData(FALSE);
	OnCopy();
}


void CDirectoryOperationDlg::OnEditDelete()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_DEL;
	UpdateData(FALSE);
	OnDelete();
}


void CDirectoryOperationDlg::OnEditMove()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_MOVE;
	UpdateData(FALSE);
	OnMove();
}


void CDirectoryOperationDlg::OnEditNewdirectory()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_NEWDIR;
	UpdateData(FALSE);
	OnNewdir();
}


void CDirectoryOperationDlg::OnEditRename()
{
	// TODO: Add your command handler code here
	m_nOperationType = OT_REN;
	UpdateData(FALSE);
	OnRename();
}
