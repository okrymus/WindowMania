#include "stdafx.h"
#include "WindowMania.h"
#include "PanelListbox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanelListbox

CPanelListbox::CPanelListbox()
{

	m_folder = ( HICON ) ::LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDI_ICON_FOLDER ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
	m_folder_up = ( HICON ) ::LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDI_ICON_FOLDER_UP ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );
	m_file = ( HICON ) ::LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDI_ICON_FILE ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR );

}

CPanelListbox::~CPanelListbox()
{
}

BEGIN_MESSAGE_MAP(CPanelListbox, CListBox)
	//{{AFX_MSG_MAP(CPanelListbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanelListbox message handlers

void CPanelListbox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	int index = lpDrawItemStruct->itemID;
	int data = lpDrawItemStruct->itemData;
	int state = lpDrawItemStruct->itemState;

	if( index != LB_ERR )
	{
		// Setting up coordinates
		CRect rect( lpDrawItemStruct->rcItem );
		CRect drawRect( 0, 0, rect.Width(), rect.Height() );

		// Setting up a memory CDC
		CDC outdc;
		CDC dc;
		outdc.Attach( lpDrawItemStruct->hDC );
		dc.CreateCompatibleDC( &outdc );
		CBitmap bitmap;
		CBitmap* oldbitmap;
		bitmap.CreateCompatibleBitmap( &outdc, rect.Width(), rect.Height() );
		oldbitmap = dc.SelectObject( &bitmap );

		// Setting other attributes
		CBrush		background;
		COLORREF	oldtextcolor;
		COLORREF	oldbkcolor;
		HICON		icon;

		icon = NULL;
		if( data == 1 )
			icon = m_folder;
		if( data == 2 )
			icon = m_file;
		if( data == 3 )
			icon = m_folder_up;

		CFont* font = GetParent()->GetFont();
		dc.SelectObject( font );

		if( state & ODS_SELECTED )
		{
			background.CreateSolidBrush( ::GetSysColor( COLOR_HIGHLIGHT ) );
			oldbkcolor = dc.SetBkColor( ::GetSysColor( COLOR_HIGHLIGHT ) );
			oldtextcolor = dc.SetTextColor( ::GetSysColor( COLOR_HIGHLIGHTTEXT ) );
		}
		else
		{
			background.CreateSolidBrush( ::GetSysColor( COLOR_WINDOW ) );
			oldbkcolor = dc.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );
			oldtextcolor = dc.SetTextColor( ::GetSysColor( COLOR_WINDOWTEXT ) );
		}

		// Clearing the item
		dc.FillRect( drawRect, &background );

		// Drawing icon
		if( icon )
			::DrawIconEx( dc.m_hDC, 0, 0, icon, 16, 16, 0, NULL, DI_NORMAL );

		// Drawing the text
		drawRect.left += 17;
		CString text;
		GetText( index, text );

		dc.DrawText( text, drawRect, DT_SINGLELINE );

		// Drawing focus rect
		if( state & ODS_FOCUS )
			dc.DrawFocusRect( rect );

		// Output to screen
		outdc.BitBlt( rect.left, rect.top, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY );

		// Cleaning up
		dc.SelectObject( oldbitmap );
		dc.SetTextColor( oldtextcolor );
		dc.SetBkColor( oldbkcolor );
		outdc.Detach();
	}	
}

// 	Handler for the owner-draw compare message
int CPanelListbox::CompareItem(LPCOMPAREITEMSTRUCT /*lpCompareItemStruct*/) 
{

	return 0;

}

//	Handler for the owner - draw measure message
void CPanelListbox::MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/) 
{
	// Empty	
}

//	Adds the string "text" and associated item data to the listbox.
int CPanelListbox::AddItem(int type, const CString &text)
{
	int index = AddString( text );
	SetItemData( index, type );

	return index;
}

