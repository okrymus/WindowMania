// WindowMania.cpp : Defines the class behaviors for the application.
//

/*
* Programmer: Panupong Leenawarat
* Last Modified: May 8, 2017
* CIT 284 Final Exam poject: WINDOWS MANIA
* The program performs as DOS/WINDOWS operating system
* The code for each command is embedded into the Windows code for the User Interface
*/

#include "stdafx.h"
#include "WindowMania.h"
#include "SplashWindow.h"
#include <fstream>
#include <strstream>
#include <io.h>
#include "MainFrm.h"
#include "WindowManiaDoc.h"
#include "WindowManiaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char fileDialogFilter[] = "C++ Files (*.cpp) | *.cpp|Header Files\
(*.h)| *.h|Resource Files (*.rc) | *.rc | Text Files(*.txt)|*.txt | All Files (*.*)| *.*||";
const char fileDialogExt[] = "cpp";
/////////////////////////////////////////////////////////////////////////////
// CWindowManiaApp

BEGIN_MESSAGE_MAP(CWindowManiaApp, CWinApp)
	//{{AFX_MSG_MAP(CWindowManiaApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_SHUTDOWN, &CWindowManiaApp::OnFileShutdown)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CWindowManiaApp construction

CWindowManiaApp::CWindowManiaApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWindowManiaApp object

CWindowManiaApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaApp initialization

BOOL CWindowManiaApp::InitInstance()
{
	AfxEnableControlContainer();

	CSplashWindow::ShowSplashScreen(NULL, "Starting application...");
	Sleep(2000);

	CSplashWindow::ShowSplashScreen(NULL, "Initializing hardware...");
	Sleep(2000);

	CSplashWindow::ShowSplashScreen(NULL, "Initializing database...");
	Sleep(2000);


	// display final splash screen and have it turn off after 3 seconds (3000 milliseconds)
	CSplashWindow::ShowSplashScreen(NULL, "Initializing...", 3000);



	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWindowManiaDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CWindowManiaView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	/**** JCz ***/
	// this just illustrate how to create children of the MDI pane.
	// in real world this would be done in other appropriate placed like menu handler for example
	((CMainFrame*)m_pMainWnd)->CreateSplitterChildren();

	return TRUE;
}



// App command to run the dialog
void CWindowManiaApp::OnAppAbout()
{
	CSplashWindow::ShowSplashScreen(NULL, "About", 3000);
}

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaApp message handlers



void CWindowManiaApp::OnFileShutdown()
{
	// TODO: Add your command handler code here
	if (AfxMessageBox(IDS_SURE_TO_SHUTDOWN, MB_YESNO) == IDYES)
	{
		CSplashWindow::ShowSplashScreen(NULL, "BEST TO YOU", 2000);
		Sleep(2000);

		CSplashWindow::ShowSplashScreen(NULL, "Bye Bye..", 2000);
		Sleep(2000);
		CWnd* pWnd = AfxGetApp()->GetMainWnd();
		pWnd->PostMessage(WM_CLOSE);
	}
}
