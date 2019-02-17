#include "stdafx.h"
#include <tchar.h>
#include "DirectoryOperate.h"

#pragma warning( disable : 4706 )

#define Trigger(a)	if( m_feedbackWindow ) m_feedbackWindow->SetWindowText( a );

////////////////////////////////////////////////////////////////////
// CDirectoryOperate construction/destruction/initialization

CDirectoryOperate::CDirectoryOperate()
{
	m_feedbackWindow = NULL;
}

CDirectoryOperate::CDirectoryOperate( CWnd* feedbackWindow )
{
	m_feedbackWindow = feedbackWindow;
}

CDirectoryOperate::~CDirectoryOperate( )
{
}

////////////////////////////////////////////////////////////////////
// CDirectoryOperate operations
//

// File operations

BOOL CDirectoryOperate::CopyFiles( const CString& sourceDirectory,const CString& destDirectory )
/* ============================================================
	Description :	The member copies all files from 
					"sourceDirectory" to "destDirectory". 
					Subdirectories will not be copied.			
   ============================================================*/
{
	BOOL result = false;
	ClearError( );
	CString source( sourceDirectory );
	CString dest( destDirectory );
	if( QualifyPath( source ) )
	{
		if( QualifyPath( dest ) )
		{

			CStringArray files;
			result = EnumFilesInDirectory( source, files );
			if( result )
			{

				result = CreateDirectory( dest );
				if( result )
				{
					int max = files.GetSize( );
					for( int t = 0 ; t < max ; t++ )
					{

						CString file;
						file = files[ t ];
						Trigger( file );
						CString sourcefile( source + file );
						CString destfile( dest + file );
						result = ::CopyFile( sourcefile, destfile, FALSE );
						if( !result )
						{

							SetSystemErrorMessage( ::GetLastError( ), 
											source + 
											file + 
											_T( " -> " ) + 
											dest + 
											file );
							t = max;
						}
					}
				}
			}
		}
	}

	return result;
}

BOOL CDirectoryOperate::CopyFiles( CStringArray& files,const CString& destDirectory )
/* ============================================================
	Description :	The function copies the files in the 
					"CStringArray" "files" to the directory 
					"destDirectory". Existing files will be
					overwritten. The destination will be 
					created if it doesn't already exist.
   ============================================================*/
{
	ClearError( );
	CString dest( destDirectory );

	BOOL result = TRUE;
	if( files.GetSize( ) )
	{
		QualifyPath( dest );

		// Create destination, if necessary
		result = CreateDirectory( dest );
		if( result )
		{
			int max = files.GetSize( );
			for( int t = 0 ; t < max ; t++ )
			{
				// Loop and copy the files
				CString file;
				file = files[ t ];
				if( file.GetLength( ) )
				{
					Trigger( file );
					QualifyFile( file );

					// Create destination filename
					CString to = dest + GetFileName( file );
					if( !( result = ::CopyFile( file, to, FALSE ) ) )
					{
						// Set error message
						SetSystemErrorMessage( ::GetLastError( ),
												file + 
												_T( " -> " ) + 
												dest + 
												file );
						t = max;
					}
				}
			}
		}
	}
	else
	{
		SetInternalErrorMessage( );
		result =  FALSE;
	}

	return result;
}

BOOL CDirectoryOperate::CopyFile( const CString& sourceFile,const CString& destDirectory )
/* ============================================================
	Description :	Will copy "sourceFile" to "destDirectory". 
					An existing file will be overwritten. The 
					directory will be created if it doesn't exist.			
   ============================================================*/
{
	ClearError( );
	CString source( sourceFile );
	CString dest( destDirectory );

	BOOL result = FALSE;
	if( sourceFile.GetLength( ) )
	{
		if( QualifyFile( source ) )
		{
			if( QualifyPath( dest ) )
			{
				if( FileExists( source ) )
				{
					// Creating destDirectory if necessary.
					if( CreateDirectory( dest )  )
					{
						CString filePart = GetFileName( source );

						// Copy the file
						Trigger( filePart );
						if( ::CopyFile( source, dest + filePart, FALSE ) ) 
							result = TRUE;
						else
							SetSystemErrorMessage( ::GetLastError( ), source );
					}
				}
			}
		}
	}
	else
		SetInternalErrorMessage( );

	return result;
}

BOOL CDirectoryOperate::CopyFile( const CString& sourceFile,const CString& destDirectory, const CString& destFile )
/* ============================================================
	Description :	Will copy "sourceFile" to "destDirectory" 
					with the new name "destFile". 
					An existing file will be overwritten. The 
					directory will be created if it doesn't exist.
   ============================================================*/
{
	ClearError( );
	CString source( sourceFile );
	CString destDir( destDirectory );
	CString dest( destFile );

	BOOL result = false;
	if( sourceFile.GetLength( ) )
	{
		if( QualifyFile( source ) )
		{
			if( QualifyPath( destDir ) )
			{
				dest = destDir + dest;
				if( FileExists( source ) )
				{
					// Creating destDirectory if necessary.
					if( CreateDirectory( destDir ) )
					{
						// Copy the file
						Trigger( dest );
						if( ::CopyFile( source, dest, FALSE ) ) 
							result = TRUE;
						else
							SetSystemErrorMessage( ::GetLastError( ), source );
					}
				}
			}
		}
	}
	else
		SetInternalErrorMessage();

	return result;
}

// 	Will remove "sourceFile".	
BOOL CDirectoryOperate::RemoveFile( const CString& sourceFile )
{
	ClearError( );
	CString source( sourceFile );

	BOOL result = FALSE;
	if( sourceFile.GetLength( ) )
	{
		result = QualifyFile( source );
		if( result )
		{
			result = ::DeleteFile( source );
			if( !result )
				SetSystemErrorMessage( ::GetLastError( ), source );
		}
	}
	else
		SetInternalErrorMessage( );

	return result;
}

////////////////////////////////////////
// Directory operations
//

// Returns "TRUE" if the directory "directory" exists
BOOL CDirectoryOperate::DirectoryExists( const CString& directory )
{
	ClearError( );

	BOOL result = FALSE;

	if( directory.GetLength( ) )
	{
		CString indir( directory );
		if( QualifyPath( indir ) )
		{

			TCHAR buff[ _MAX_PATH ];
			::GetCurrentDirectory(_MAX_PATH, buff );

			if( ::SetCurrentDirectory( indir ) )
				result = TRUE;

			::SetCurrentDirectory( buff );
		}
	}
	else
	{
		SetInternalErrorMessage( );
	}

	return result;
}

// Will recursively create the directory "directory".
BOOL CDirectoryOperate::CreateDirectory( const CString& directory )	
{
	ClearError( );

	BOOL result = TRUE;
	CString indir( directory );
	if( indir.GetLength() )
	{
		result = QualifyPath( indir );
		if( result )
		{

			_TCHAR drive[ _MAX_PATH ];
			_TCHAR dir[ _MAX_DIR ];
			_TCHAR fname[ _MAX_FNAME ];
			_TCHAR ext[ _MAX_EXT ];

			// Split directory into parts
			_tsplitpath_s( indir, drive, dir, fname, ext );

			TCHAR currentDirectory[ _MAX_PATH ];
			::GetCurrentDirectory( _MAX_PATH, currentDirectory );

			CStringArray directories;
			CString parts = dir;

			if( parts.GetLength( ) > 2 )
			{
				if( parts.Left( 2 ) == _T( "\\\\" ) )
				{
					// We have an UNC name
					CString strComputer;
					parts = parts.Right( parts.GetLength( ) - 2 );
					int findDir = parts.Find( _TCHAR( '\\' ) );
					if( findDir!=-1 )
					{
						strComputer = _T( "\\\\" ) + parts.Left( findDir );
						parts = parts.Right( parts.GetLength( ) - ( findDir + 1 ) );
					}
					_tcscpy_s( drive, strComputer );
				}
			}

			CString strRoot( drive );

			// Strip leading \'s
			while( parts.GetLength() && parts[0] == _TCHAR( '\\' ) )
				parts = parts.Right( parts.GetLength( ) - 1 );

			// Cut into separate directories
			int find = parts.Find( _TCHAR( '\\' ) );
			while( find != -1 )
			{
				directories.Add( parts.Left( find ) );
				parts = parts.Right( parts.GetLength( ) - ( find + 1 ) );
				find = parts.Find( _TCHAR( '\\' ) );
			}

			if( parts.GetLength() )
				directories.Add( parts );

			if( _tcslen( fname ) )
				directories.Add( fname );

			// Loop directories one-by-one, creating as necessary
			int max = directories.GetSize( );
			CString strCurrentDirectory( strRoot );
			CString finalDirectory;

			for( int t = 0 ; t < max ; t++ )
			{
				strCurrentDirectory += _TCHAR( '\\' ) + directories[ t ];
				Trigger( strCurrentDirectory );
				::SetCurrentDirectory( strCurrentDirectory );
				::CreateDirectory( strCurrentDirectory, NULL );
			}

			if( !::SetCurrentDirectory( strCurrentDirectory ) )
				SetSystemErrorMessage( ::GetLastError( ), strCurrentDirectory );
			else
				result = TRUE;

			::SetCurrentDirectory( currentDirectory );
		}
	}
	else
	{
		SetInternalErrorMessage( );
		result = FALSE;
	}
	return result;
}

BOOL CDirectoryOperate::EmptyDirectory( const CString& directory )
{
	// Will delete all files in directory. 
	BOOL result = false;
	ClearError( );
	CString indir( directory );
	if( QualifyPath( indir ) )
	{

		// Enumerate all files
		CStringArray files;
		result = EnumFilesInDirectory( indir, files );
		if( result )
		{
			int max = files.GetSize( );
			for( int t = 0 ; t < max ; t++ )
			{
				// Loop and delete
				CString file = files[ t ];
				Trigger( file );
				BOOL remove = ::DeleteFile( indir + file );
				if( !remove )
				{
					SetSystemErrorMessage( ::GetLastError( ), indir + file );
					t = max;
					result = false;
				}

			}
		}
	}

	return result;
}

// Will remove the directory "directory", even
// if not empty.Will not remove
// subdirectories.
BOOL CDirectoryOperate::RemoveDirectory( const CString& directory )	
{
	ClearError( );

	BOOL result = TRUE;
	CString indir( directory );
	if( indir.GetLength( ) )
	{
		result = QualifyPath( indir );
		if( result )
		{

			result = EmptyDirectory( indir );
			if( result )
			{
				Trigger( indir );
				result = ::RemoveDirectory( indir );
				if( !result )
					SetSystemErrorMessage( ::GetLastError( ), indir );
			}
		}
	}
	else
	{
		// Small sanity check, we can't
		// delete the current directory.
		SetInternalErrorMessage( );
		result = FALSE;
	}

	return result;
}

BOOL CDirectoryOperate::RemoveDirectories( const CString& directory )
/* ============================================================
	Function :		CDirectoryOperate::RemoveDirectories
	Description :	Will remove the directory "directory", even
					if not empty. Will remove subdirectories.
   ============================================================*/
{
	ClearError( );

	BOOL result = true;

	CString indir( directory );
	if( indir.GetLength() )
	{
		result = QualifyPath( indir );
		if( result )
		{
			CStringArray directories;

			result = EnumAllDirectories( indir, directories );
			if( result )
			{

				int max = directories.GetSize( );
				for( int t = max - 1; t >= 0 ; t-- )
				{
					result = RemoveDirectory( directories[ t ] );
					if( !result )
						t = -1;
				}
				
				if( result )
					result = RemoveDirectory( indir );
			}
		}
	}
	else
	{
		// Small sanity check, we can't
		// delete the current directory.
		SetInternalErrorMessage( );
		result = false;
	}

	return result;
}

BOOL CDirectoryOperate::EmptyDirectories( const CString& directory )
/* ============================================================
	Description :	Will delete all files in "directory". Will 
					also empty subdirectories.
   ============================================================*/
{
	BOOL result = false;
	ClearError( );

	CString indir( directory );

	if( QualifyPath( indir ) )
	{
		CStringArray directories;

		result = EnumAllDirectories( indir, directories );
		if( result )
		{
			int max = directories.GetSize( );

			for( int t = max - 1 ; t >= 0 ; t-- )
			{
				result = EmptyDirectory( directories[ t ] );
				if( !result )
					t = -1;
			}

			if( result )
				result = EmptyDirectory( indir );
		}
	}

	return result;
}

BOOL CDirectoryOperate::CopyDirectory( const CString& sourceDirectory,const CString& destDirectory )
/* ============================================================
	Description :	Copies all the files from "sourceDirectory" 
					to "destDirectory". Existing files will be
					overwritten. "destDirectory" will be created
					if necessary. Subdirectories will not be
					copied.
   ============================================================*/
{
	ClearError( );
	CString source( sourceDirectory );
	CString dest( destDirectory );
	if( QualifyPath( source ) )
	{
		if( QualifyPath( dest ) )
		{

			Trigger( dest );

			// We don't care if this fails - CopyFiles will 
			// return an error in that case.
			CreateDirectory( dest );

			return CopyFiles( source, dest );
		}
	}

	return false;
}

BOOL CDirectoryOperate::CopyDirectories( const CString& sourceDirectory,const CString& destDirectory )
/* ============================================================
	Description :	Copies all the files and subdirectories 
					from "sourceDirectory" to "destDirectory", 
					keeping the directory structure. Existing 
					files will be overwritten. "destDirectory" 
					and subdirectories will be created if 
					necessary.
   ============================================================*/
{
	BOOL result = false;
	ClearError( );

	CString source( sourceDirectory );
	CString dest( destDirectory );
	if( QualifyPath( source ) )
	{
		if( QualifyPath( dest ) )
		{

			CStringArray directories;
			directories.Add( source );

			result = EnumAllDirectories( source, directories );
			if( result )
			{

				int max = directories.GetSize( );
				for( int t = 0 ; t < max ; t++ )
				{

					CString from = directories[ t ];
					CString part = from.Right( from.GetLength( ) - source.GetLength( ) );
					CString to = dest + part;

					result = CopyFiles( from, to );
					if( !result )
						t = max;
				}
			}
		}
	}

	return result;
}

////////////////////////////////////////
// File-oriented operations
//

// Description :	Returns "TRUE" if the file file exists
BOOL CDirectoryOperate::FileExists( const CString& file )

{
	ClearError();

	BOOL result = true;

	if( file.GetLength( ) )
	{
		CString infile( file );
		result = QualifyFile( infile );
		if( result )
		{
			HANDLE filehandle = ::CreateFile( 
									infile,
									GENERIC_READ,
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL
								);

			if( filehandle == INVALID_HANDLE_VALUE )
				result = FALSE;
			else
				CloseHandle( filehandle );
		}
	}
	else
	{
		SetInternalErrorMessage();
		result = false;
	}

	return result;
}

//Returns "TRUE" if the file file exists, At this time file_info is filled out
BOOL CDirectoryOperate::FileInformation( const CString& file, BY_HANDLE_FILE_INFORMATION &file_info )
{
	ClearError( );

	BOOL result = TRUE;

	if( file.GetLength( ) )
	{
		CString infile( file );
		result = QualifyFile( infile );
		if( result )
		{
			HANDLE filehandle = ::CreateFile(infile,
												GENERIC_READ,
												FILE_SHARE_READ | FILE_SHARE_WRITE,
												NULL,
												OPEN_EXISTING,
												FILE_ATTRIBUTE_NORMAL,
												NULL);

			if( filehandle == INVALID_HANDLE_VALUE )
				result = FALSE;
			else
			{
				BY_HANDLE_FILE_INFORMATION file_info_local;
				if (GetFileInformationByHandle( filehandle, &file_info_local ))
				{
					memcpy(&file_info, &file_info_local, sizeof(file_info_local));
				}
				else
				{
					result = FALSE;
					SetInternalErrorMessage( );
				}
				CloseHandle( filehandle );
			}
		}
	}
	else
	{
		SetInternalErrorMessage( );
		result = FALSE;
	}

	return result;

}

//Creates the file "file", as well as the directories necessary
BOOL CDirectoryOperate::CreateFile( const CString& file )
{
	ClearError( );

	BOOL result = TRUE;

	if( file.GetLength( ) )
	{

		CString infile( file );
		result = QualifyFile( infile );

		if( result )
		{

			// Split into directory and file
			CString directory = GetDirectoryName( infile );
			CString filename = GetFileName( infile );

			result = CreateDirectory( directory );
			if( result )
			{
				Trigger( file );
				HANDLE filehandle = ::CreateFile( 
										infile,
										GENERIC_WRITE,
										0,
										NULL,
										CREATE_ALWAYS,
										FILE_ATTRIBUTE_NORMAL,
										NULL
									);

				if( filehandle == INVALID_HANDLE_VALUE )
					result = FALSE;
				else
					CloseHandle( filehandle );
			}
		}
	}
	else
	{
		SetInternalErrorMessage( );
		result = FALSE;
	}

	return result;
}

//Move the file "sourceFile" to "destFile". Creates the destination directory if necessary
BOOL CDirectoryOperate::MoveFile( const CString& sourceFile, const CString& destFile )
{

	ClearError( );

	BOOL result = FALSE;

	if( sourceFile.GetLength() && destFile.GetLength() )
	{
		CString insourcefile( sourceFile );
		if( QualifyFile( insourcefile ) )
		{
			CString indestdir = GetDirectoryName( destFile );
			CString indestfilename = GetFileName( destFile );

			if( CopyFile( insourcefile, indestdir, indestfilename ) )
			{
				result = RemoveFile( sourceFile );
			}
		}
	}

	return result;
}

// Renames the file "sourceFile" to "destFile". "destFile" is assumed to be a filename rather
// than a fully qualified path.
BOOL CDirectoryOperate::RenameFile( const CString& sourceFile, const CString& destFile )
{

	ClearError( );

	BOOL result = FALSE;


	TCHAR szSource[MAX_PATH + 2] = _T("");
	TCHAR szDestination[MAX_PATH + 2] = _T("");
	::_tcsncpy_s(szSource, sourceFile, MAX_PATH);
	::_tcsncpy_s(szDestination, destFile, MAX_PATH);

	// Ren should not be able to affect any directories, just like
	// how "ren" works in DOS. If need to rename directories, use 
	// Move instead.
	if  (sourceFile.GetLength() && destFile.GetLength())
	{
		CString insourcefile(sourceFile);
		if (QualifyFile(insourcefile))
		{
			SHFILEOPSTRUCT fs;
			::memset(&fs, 0, sizeof(SHFILEOPSTRUCT));

			fs.pFrom = szSource;
			fs.pTo = szDestination;
			fs.wFunc = FO_RENAME;
			fs.fFlags = FOF_FILESONLY;
			result = (::SHFileOperation(&fs) == 0);
		}
	}


	return result;
}

////////////////////////////////////////
// Helpers
//

// Enumerates all files in directory "sourceDirectory", and adds them to the "CStringArray" "files".Will not add
// subdirectories
BOOL CDirectoryOperate::EnumFilesInDirectory( const CString& sourceDirectory, CStringArray& files, int mode )
{
	return EnumFilesInDirectoryWithFilter( _T( "*.*" ), sourceDirectory, files, mode );
}


// Enumerates all files matching "strFilter" in the directory "sourceDirectory", and adds them to the "CStringArray" "files".Will not
// add subdirectories.
BOOL CDirectoryOperate::EnumFilesInDirectoryWithFilter( const CString& strFilter,const CString& sourceDirectory, CStringArray& files, int mode )
{

	ClearError( );
	CString source( sourceDirectory );
	BOOL result = QualifyPath( source );
	if( result )
	{
		if( DirectoryExists( source ) )
		{
			CString sourceFiles( source + strFilter );
			WIN32_FIND_DATA ff;

			HANDLE findhandle = ::FindFirstFile( sourceFiles, &ff );
			if( findhandle != INVALID_HANDLE_VALUE )
			{
				BOOL res = TRUE;
				while( res )
				{
					// We only want files
					if( !( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
					{
						BOOL    added = FALSE;
						CString file = ff.cFileName;

						if( mode == EF_FULLY_QUALIFIED )
							file = source + file;

						// Return the array alphabetically ordered
						for( int i = 0; i < files.GetSize(); i++ )
						{
							if ( files.GetAt( i ) > file )
							{
								files.InsertAt( i, file );
								added = TRUE;
								break;
							}
						}
						if ( !added )
						{
							files.Add( file );
						}

						Trigger( file );
					}

					res = ::FindNextFile( findhandle, &ff );
				}

				::FindClose( findhandle );
			}
			else
			{

				SetSystemErrorMessage( ::GetLastError( ), sourceFiles );
				result = FALSE;
			}
		}
	}

	return result;

}
 
// Enumerates all directories recursively in directory "sourceDirectory", and adds them to the "CStringArray" "directories".Each entry
// will be a fully qualified name
BOOL CDirectoryOperate::EnumAllDirectories( const CString& sourceDirectory, CStringArray& directories, int mode )
{
	CString source( sourceDirectory );
	BOOL result = QualifyPath( source );
	if( result )
	{
		result = EnumAllDirs( sourceDirectory, directories );

		if( mode == EF_RELATIVE_NAMES )
		{
			CStringArray temp;
			int max = directories.GetSize();
			for( int t = 0 ; t < max ; t++ )
			{
				CString newname = directories[ t ];
				newname = newname.Right( newname.GetLength() - source.GetLength() );
				newname = newname.Left( newname.GetLength() - 1 ); // strip final slash
				temp.Add( newname );
			}
			directories.RemoveAll();
			max = temp.GetSize();
			for(int t = 0 ; t < max ; t++ )
				directories.Add( temp[ t ] );
		}
	}

	return result;
}
 
// Enumerates all directories recursively in directory "sourceDirectory", and adds them
// to the "CStringArray" "directories".Each entry will be a fully qualified name
BOOL CDirectoryOperate::EnumAllDirs( const CString& sourceDirectory, CStringArray& directories )

	
{
	ClearError( );

	CString source( sourceDirectory );
	BOOL result = QualifyPath( source );
	if( result )
	{
		CString sourceFiles( source + _T( "*.*" ) );
		
		WIN32_FIND_DATA ff;
		HANDLE findhandle = ::FindFirstFile( sourceFiles, &ff );
		if( findhandle != INVALID_HANDLE_VALUE )
		{

			BOOL res = TRUE;
			while( res )
			{
				// We only want directories
				if( ( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) && _tcscmp( ff.cFileName, _T( "." ) ) && _tcscmp( ff.cFileName, _T( ".." ) ) )
				{
					CString directory( source + ff.cFileName );
					directories.Add( directory + _TCHAR( '\\' ) );

					Trigger( ff.cFileName );
					result = EnumAllDirs( directory, directories );
					if( !result )
						res = FALSE;
				}

				if( res )
					res = ::FindNextFile( findhandle, &ff );
			}

			::FindClose( findhandle );
		}
		else
		{

			SetSystemErrorMessage( errno, sourceFiles );
			result = false;
		}
	}

	return result;

}
 
// Enumerates all directories in directory "sourceDirectory", and adds them to
// the "CStringArray" "directories".Each entry will be a fully qualified name
BOOL CDirectoryOperate::EnumDirectories( const CString& sourceDirectory, CStringArray& directories, int mode )
{
	ClearError( );

	CString source( sourceDirectory );
	BOOL result = QualifyPath( source );
	if( result )
	{
		CString sourceFiles( source + _T( "*.*" ) );
		WIN32_FIND_DATA ff;

		HANDLE findhandle = FindFirstFile( sourceFiles, &ff );
		if( findhandle != INVALID_HANDLE_VALUE)
		{

			BOOL res = TRUE;
			while( res)
			{
				// We only want directories
				if( ( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) && _tcscmp( ff.cFileName, _T( "." ) ) && _tcscmp( ff.cFileName, _T( ".." ) ) )
				{
					if( mode == EF_RELATIVE_NAMES )
						directories.Add( ff.cFileName );
					else
					{
						CString file( source + ff.cFileName );
						directories.Add( file );
					}

					Trigger( ff.cFileName );
				}

				res = FindNextFile( findhandle, &ff );
			}

			FindClose( findhandle );
		}
		else
		{

			SetSystemErrorMessage( ::GetLastError( ), sourceFiles );
			result = FALSE;
		}
	}

	return result;
}
 
// Returns, recursively, the fully qualified names of all files found under "sourceDirectory".
BOOL CDirectoryOperate::EnumAllFiles( const CString& sourceDirectory, CStringArray& files, int mode )

{
	return EnumAllFilesWithFilter( _T( "*.*" ), sourceDirectory, files, mode );
}

// Returns, recursively, the fully qualified names of all files matching the filter found under "sourceDirectory".
BOOL CDirectoryOperate::EnumAllFilesWithFilter( const CString& filter,const CString& sourceDirectory, CStringArray& files, int mode )
{
	CString indir = sourceDirectory;
	BOOL result = false;

	if( QualifyPath( indir ) )
	{

		result = EnumAllFilesWF( filter, indir, files );

		if( mode == EF_RELATIVE_NAMES )
		{
			CStringArray temp;
			int max = files.GetSize();
			for( int t = 0 ; t < max ; t++ )
			{
				CString newname = files[ t ];
				newname = newname.Right( newname.GetLength() - indir.GetLength() );
				temp.Add( newname );
			}
			files.RemoveAll();
			max = temp.GetSize();
			for(int t = 0 ; t < max ; t++ )
				files.Add( temp[ t ] );
		}
	}

	return result;

}

// Returns, recursively, the fully qualified names of all files matching the filter found under "sourceDirectory".
BOOL CDirectoryOperate::EnumAllFilesWF( const CString& filter,const CString& sourceDirectory, CStringArray& files)
{
	CStringArray dirs;
	CStringArray dirs2;
	CStringArray dirfiles;
	BOOL result = false;
	CString indir = sourceDirectory;
	if( QualifyPath( indir ) )
	{

		if (EnumFilesInDirectoryWithFilter( filter, indir, dirfiles, EF_FULLY_QUALIFIED )) 
		{
			int max0 = dirfiles.GetSize( );
			for( int i = 0 ; i < max0 ; i++ )
			{
				CString file = dirfiles[ i ];
				Trigger( file );
				files.Add( file );
			}

			dirfiles.RemoveAll();
			result = TRUE;
		}

		if( EnumAllDirectories( sourceDirectory, dirs2, EF_FULLY_QUALIFIED ) )
		{
			int max1 = dirs2.GetSize( );
			for( int t = 0 ; t < max1 ; t++ )
			{
				CString dir = dirs2[ t ];
				QualifyPath( dir );
				if( EnumFilesInDirectoryWithFilter( filter, dir, dirfiles, EF_FULLY_QUALIFIED ) ) 
				{
					int max2 = dirfiles.GetSize( );
					for( int i = 0 ; i < max2 ; i++ )
					{
						CString file = dirfiles[ i ];
						Trigger( file );
						files.Add( file );
					}

					dirfiles.RemoveAll();
				}

			}

			result = TRUE;
		}
		else
			result = FALSE;
	}

	return result;

}

////////////////////////////////////////
// Error handling

// Will return the current error message for the "CDirectoryOperate".
CString CDirectoryOperate::GetErrorMessage( )
{
	return m_errorMessage;
}

// Private methods

// Clears the internal error message string
void CDirectoryOperate::ClearError( )
{
	m_errorMessage = _T( "" );
}

// Sets the error message string with the system error message as gotten from "GetLastError". "elements" will be appended.
void CDirectoryOperate::SetSystemErrorMessage( int error,const CString& elements)
{
	LPVOID msgBuff;

	// Format error message from system
	::FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		error,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		( LPTSTR ) &msgBuff,
		0,
		NULL
	);

	// Create the error string
	m_errorMessage = CString( ( LPTSTR ) msgBuff );
	m_errorMessage.TrimLeft( );
	m_errorMessage.TrimRight( );

	if( elements.GetLength( ) )
		m_errorMessage += _TCHAR( ' ' ) + elements;

	Trigger ( m_errorMessage );

	// Free the buffer.
	LocalFree( msgBuff );
}

// Sets the error message to the internal error message
void CDirectoryOperate::SetInternalErrorMessage( )
{
	m_errorMessage = _T( "CDirectoryOperate internal error - check call parameters" );
	Trigger ( m_errorMessage );
}

////////////////////////////////////////
// Helpers

// Creates a fully qualified path from "str".
BOOL CDirectoryOperate::QualifyPath( CString& str )
{

	BOOL result = TRUE;

	str.Replace( _TCHAR( '/' ), _TCHAR( '\\' ) );

	// Append a trailing backslash to directory name
	if( str.GetLength( ) )
		if( str[ str.GetLength( ) - 1 ] != _TCHAR( '\\' ) )
			str += _TCHAR( '\\' );

	if( str.GetLength( ) < 2 || str.Left( 2 ) != "\\\\" )
		result = QualifyFile( str );

	return result;

}

// Creates a fully qualified path from "str".
BOOL CDirectoryOperate::QualifyFile( CString& str )
{
	BOOL result = true;

	str.Replace( _TCHAR( '/' ), _TCHAR( '\\' ) );

	_TCHAR drive[ _MAX_DRIVE ];
	_TCHAR dir[ _MAX_DIR ];
	_TCHAR fname[ _MAX_FNAME ];
	_TCHAR ext[ _MAX_EXT ];

	_tsplitpath_s( str, drive, dir, fname, ext );

	if( !_tcsclen( drive ) )
	{
		CString test( dir );
		// The name is not fully qualified.
		// We assume it to be relative the 
		// current directory

		TCHAR currentDirectory[ _MAX_PATH ];
		::GetCurrentDirectory( _MAX_PATH, currentDirectory );

		if( test.GetLength() > 2 && test.Left( 2 ) == _T( "\\\\" ) )
		{
			// We have an UNC-part, and will not need to qualify further.
		}
		else if( test.GetLength( ) > 2 && test.Left( 3 ) == _T( "..\\" ) )
		{

			TCHAR upDirectory[ _MAX_PATH ];
			while( test.GetLength( ) > 2 && test.Left( 3 ) == _T( "..\\" ) )
			{
				::SetCurrentDirectory( _T( ".." ) );
				test = test.Right( test.GetLength( ) - 3 );
			}

			::GetCurrentDirectory( _MAX_PATH, upDirectory );

			str = upDirectory;
			str += _TCHAR( '\\' );
			str += fname;
			str += ext;
			::SetCurrentDirectory( currentDirectory );
		}
		else if ( test.GetLength() && test[ 0 ] == _TCHAR( '\\' ) )
		{
			// Start from root
			_tsplitpath_s( currentDirectory, drive, dir, fname, ext );
			str = drive + str;
		}
		else
		{
			str = _TCHAR( '\\' ) + str;
			str = currentDirectory + str;
		}
	}

	if( !TestPart( dir ) || 
		!TestPart( fname ) ||
		!TestPart( ext ) )
	{
		SetInternalErrorMessage();
		result = false;
	}

	return result;
}

// Checks the string for invalid characters
BOOL CDirectoryOperate::TestPart( const CString& str )
{
	BOOL result = TRUE;
	if( str.Find( _TCHAR( ':' ) ) != -1 )
		result = FALSE;
	if( str.Find( _TCHAR( '*' ) ) != -1 )
		result = FALSE;
	if( str.Find( _TCHAR( '?' ) ) != -1 )
		result = FALSE;

	return result;
}

//	Returns the file name part of "str".

CString CDirectoryOperate::GetFileName( const CString& str )
{
	CString instr( str );
	CString file;
	if( QualifyFile( instr ) )
	{
		int found = instr.ReverseFind( _TCHAR( '\\' ) );
		if( found != -1 )
			file = instr.Right( str.GetLength( ) - ( found + 1 ) );
	}

	return file;
}

// Returns the directory name part of "str"
CString CDirectoryOperate::GetDirectoryName( const CString& str )
{
	CString instr( str );
	CString directory;
	if( QualifyFile( instr ) )
	{
		int found = instr.ReverseFind( _TCHAR( '\\' ) );
		if( found != -1 )
			directory = instr.Left( found );
	}

	return directory;
}

// Renames the directory "oldDirectory" to "newName",
BOOL CDirectoryOperate::RenameDirectory( const CString& oldDirectory, const CString& newName )
{
	BOOL result = false;
	int findDir = newName.Find( _TCHAR( '\\' ) );
	if( findDir == -1 )
	{
		CString fullName( oldDirectory );

		if( QualifyPath( fullName ) )
		{
			CString fullNewName( fullName );
			fullNewName = fullNewName.Left( fullNewName.GetLength() - 1 );
			findDir = fullNewName.ReverseFind( _TCHAR( '\\' ) );
			if( findDir != -1 )
			{
				fullNewName = fullNewName.Left( findDir + 1 );
			}
			fullNewName += newName;
			if( ::MoveFile( fullName, fullNewName ) )
			{
				// Set error message
				SetSystemErrorMessage( ::GetLastError(), 
										fullName + 
										_T( " -> " ) + 
										fullNewName );
			}
			else
				result = true;
		}
	}

	return result;
}

// Moves the directory "oldDirectory" to "newDirectory",
BOOL CDirectoryOperate::MoveDirectory( const CString& oldDirectory, const CString& newDirectory )
{

	ClearError();

	BOOL result = FALSE;
	int len = oldDirectory.GetLength() > newDirectory.GetLength() ? newDirectory.GetLength() : oldDirectory.GetLength();
	if( oldDirectory.GetLength() && newDirectory.GetLength() && _tcsncicmp(newDirectory, oldDirectory, len ) != 0 )
	{
		if( CopyDirectories( oldDirectory, newDirectory ) )
		{
			result = RemoveDirectories( oldDirectory );
		}
	}

	return result;

}

#pragma warning( default : 4706 )
