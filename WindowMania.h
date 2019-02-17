// WindowMania.h : main header file for the WindowMania application
//

/*
* Programmer: Panupong Leenawarat
* Last Modified: May 8, 2017
* CIT 284 Final Exam poject: WINDOWS MANIA
* The program performs as DOS/WINDOWS operating system 
* The code for each command is embedded into the Windows code for the User Interface
*/

#if !defined(AFX_WindowMania_H__FE38FF6D_E8AE_40C4_85E9_3DF221CEBC02__INCLUDED_)
#define AFX_WindowMania_H__FE38FF6D_E8AE_40C4_85E9_3DF221CEBC02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaApp:
// See WindowMania.cpp for the implementation of this class
//

class CWindowManiaApp : public CWinApp
{
public:
	CWindowManiaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowManiaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWindowManiaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileShutdown();

	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WindowMania_H__FE38FF6D_E8AE_40C4_85E9_3DF221CEBC02__INCLUDED_)
