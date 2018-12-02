
// FileExplorer_Group1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFileExplorer_Group1App:
// See FileExplorer_Group1.cpp for the implementation of this class
//

class CFileExplorer_Group1App : public CWinApp
{
public:
	CFileExplorer_Group1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFileExplorer_Group1App theApp;