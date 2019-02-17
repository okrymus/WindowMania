// WindowManiaDoc.cpp : implementation of the CWindowManiaDoc class
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
#include "WindowManiaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaDoc

IMPLEMENT_DYNCREATE(CWindowManiaDoc, CDocument)

BEGIN_MESSAGE_MAP(CWindowManiaDoc, CDocument)
	//{{AFX_MSG_MAP(CWindowManiaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaDoc construction/destruction

CWindowManiaDoc::CWindowManiaDoc()
{
	// TODO: add one-time construction code here

}

CWindowManiaDoc::~CWindowManiaDoc()
{
}

BOOL CWindowManiaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWindowManiaDoc serialization

void CWindowManiaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaDoc diagnostics

#ifdef _DEBUG
void CWindowManiaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWindowManiaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWindowManiaDoc commands
