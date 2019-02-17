

#ifndef __FileOperate_H__
#define __FileOperate_H__

#include <windows.h> 

// User difined error code, it will be returned by ::GetLastError()
// if a "file-only" operation attempts to modify a directory.
#define ERR_DIRECTORY	0x10000000

class CFileOperate
{
public:
	// File/directory existence check
	enum { FM_NOTEXIST = 0, FM_DIRECTORY, FM_FILE };
	static int Existence(LPCTSTR lpSource);

	// File/directory operations
	static BOOL XCopy(LPCTSTR lpSource, LPCTSTR lpDestination, BOOL bHidePrompt = TRUE);
	//static BOOL DelTree(LPCTSTR lpSource, BOOL bHidePrompt = TRUE);
	static BOOL Move(LPCTSTR lpSource, LPCTSTR lpDestination, BOOL bHidePrompt = TRUE);
	
	// Directory-only operations
	static BOOL MkDir(LPCTSTR lpDirectory);
	static BOOL RmDir(LPCTSTR lpDirectory);

	// File/directory attributes access
	static BOOL SetAttribute(LPCTSTR lpSource, DWORD dwNewAttr);
	static DWORD GetAttribute(LPCTSTR lpSource);

	// Directory travelling and checking
	static BOOL CdDotDot(LPTSTR lpCurDirectory = NULL);
	static TCHAR IsRoot(LPCTSTR lpDirectory);
	static BOOL IsParentDirectory(LPCTSTR lpParent, LPCTSTR lpSubDirectory);

	// File-only operations
	static BOOL Copy(LPCTSTR lpSource, LPCTSTR lpDestination, BOOL bHidePrompt = TRUE);
	static BOOL Del(LPCTSTR lpSource, BOOL bHidePrompt = TRUE);
	static BOOL Ren(LPCTSTR lpSource, LPCTSTR lpDestination, BOOL bHidePrompt = TRUE);
};

#endif