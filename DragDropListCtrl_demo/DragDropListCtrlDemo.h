// DragDropListCtrlDemo.h : main header file for the DRAGDROPLISTCTRLDEMO application
//

#if !defined(AFX_DRAGDROPLISTCTRLDEMO_H__C7DA6C75_3814_4631_AA13_99610B48CEC4__INCLUDED_)
#define AFX_DRAGDROPLISTCTRLDEMO_H__C7DA6C75_3814_4631_AA13_99610B48CEC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDragDropListCtrlDemoApp:
// See DragDropListCtrlDemo.cpp for the implementation of this class
//

class CDragDropListCtrlDemoApp : public CWinApp
{
public:
	CDragDropListCtrlDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragDropListCtrlDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDragDropListCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPLISTCTRLDEMO_H__C7DA6C75_3814_4631_AA13_99610B48CEC4__INCLUDED_)
