
// test.h : main header file for the test application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CtestApp:
// See test.cpp for the implementation of this class
//

class CtestApp : public CWinApp
{
public:
	CtestApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtestApp theApp;
