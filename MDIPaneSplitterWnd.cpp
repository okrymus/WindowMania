// MDIPaneSplitterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "WindowMania.h"
#include "MDIPaneSplitterWnd.h"
#include "PaneFrame.h"
#include "FileOperateDlg.h"
#include "ChildFrm.h"
#include "DirectoryOperationDlg.h"
#include "WindowManiaDoc.h"
#include "PaneEditView.h"
#include "PaneFormView.h"
#include "paneFileManager.h"
#include "PaneDialogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum { DATE_TIME = 0, SHELL_EXTENTION, FILE_OPERATION, DIRECTORY_OPERATION, EDIT_VIEW, FORM_VIEW };


/////////////////////////////////////////////////////////////////////////////
// CMDIPaneSplitterWnd

CMDIPaneSplitterWnd::CMDIPaneSplitterWnd() : m_MultiPaneInfo(0, 0)
{
}

CMDIPaneSplitterWnd::~CMDIPaneSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CMDIPaneSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CMDIPaneSplitterWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMDIPaneSplitterWnd message handlers

BOOL CMDIPaneSplitterWnd::CreateMDIPane(int iRow, int iCol, CSize sizeInit, CCreateContext *pContext)
{
	if(m_MultiPaneInfo != CSize(0, 0))
	{
		TRACE("Pane already created! Only one MDI pane permitted\n");
		return FALSE;
	}

	m_MultiPaneInfo = CSize(iRow, iCol);
	
	return CreateView(1, 0, RUNTIME_CLASS(CPaneFrame), sizeInit, pContext);

}

/**** JCz ***/
// declared as void; it can be changed to BOOL if check is important 
void CMDIPaneSplitterWnd::CreateChildren(CDocument *pDoc, int selectWindows)
{
	CCreateContext cntxt;

	switch (selectWindows)
	{
	case DATE_TIME: 
			cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneDialogView);
		    CreateMDIPaneChild(&cntxt, TRUE);
			break;
	case SHELL_EXTENTION:
			cntxt.m_pNewViewClass = RUNTIME_CLASS(CFileManager);
			CreateMDIPaneChild(&cntxt, TRUE);
			break;
	case FILE_OPERATION: 
			cntxt.m_pNewViewClass = RUNTIME_CLASS(CFileOperateDlg);
			CreateMDIPaneChild(&cntxt, TRUE);
			break;
	case DIRECTORY_OPERATION:
			cntxt.m_pNewViewClass = RUNTIME_CLASS(CDirectoryOperationDlg);
			CreateMDIPaneChild(&cntxt, TRUE);
			break;
	case EDIT_VIEW:
			cntxt.m_pCurrentDoc = pDoc;
		/**** JCz ***/
		// Now views wired to document
			cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneEditView);
			CreateMDIPaneChild(&cntxt, TRUE);
			
	case FORM_VIEW: 	cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneFormView);
			CreateMDIPaneChild(&cntxt, TRUE);
			break;
	default:
		cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneDialogView);
		CreateMDIPaneChild(&cntxt, TRUE);
		cntxt.m_pNewViewClass = RUNTIME_CLASS(CFileManager);
		CreateMDIPaneChild(&cntxt, TRUE);
		cntxt.m_pNewViewClass = RUNTIME_CLASS(CFileOperateDlg);
		CreateMDIPaneChild(&cntxt, TRUE);
		cntxt.m_pNewViewClass = RUNTIME_CLASS(CDirectoryOperationDlg);
		CreateMDIPaneChild(&cntxt, TRUE);
		
		cntxt.m_pCurrentDoc = pDoc;

		cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneEditView);
		CreateMDIPaneChild(&cntxt, TRUE);
		cntxt.m_pNewViewClass = RUNTIME_CLASS(CPaneFormView);
		CreateMDIPaneChild(&cntxt, TRUE);
	
	}
}


BOOL CMDIPaneSplitterWnd::CreateMDIPaneChild(CCreateContext *pContext, BOOL bSizeParent /*= FALSE*/)
{

	CMDIFrameWnd *pFrame = static_cast<CMDIFrameWnd *>(GetPane(m_MultiPaneInfo.cx, m_MultiPaneInfo.cy));
	ASSERT(pFrame);

	CRuntimeClass *pClass = RUNTIME_CLASS(CChildFrame);
	CChildFrame *pChildFrame = static_cast<CChildFrame *>(pClass->CreateObject());
	ASSERT(pChildFrame);

	BOOL bRes = pChildFrame->LoadFrame(IDR_CHILDTYPE, WS_OVERLAPPEDWINDOW , pFrame, pContext);
	pChildFrame->InitialUpdateFrame(NULL, TRUE);

	return bRes;

}

BOOL CMDIPaneSplitterWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	CMDIFrameWnd *pFrame = static_cast<CMDIFrameWnd *>(GetPane(m_MultiPaneInfo.cx, m_MultiPaneInfo.cy));
	ASSERT(pFrame);
	
	if(pFrame->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
	{
		return TRUE;
	}

	return CSplitterWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
