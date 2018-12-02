//#pragma once
//#include "afxwin.h"
//
//
//// RenameDialog dialog
//
//class RenameDialog : public CDialogEx
//{
//	DECLARE_DYNAMIC(RenameDialog)
//
//public:
//	RenameDialog(CWnd* pParent = NULL);   // standard constructor
//	virtual ~RenameDialog();
//
//// Dialog Data
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_DIALOG_RENAME };
//#endif
//
//protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//	DECLARE_MESSAGE_MAP()
//public:
//	CEdit edit_rename;
//};


#pragma once
#include "afxwin.h"


// Sub_Menu_To_Delete dialog

class RenameDialog : public CDialogEx
{
	DECLARE_DYNAMIC(RenameDialog)

public:
	RenameDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~RenameDialog();

	virtual void OnFinalRelease();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUB_MENU_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CEdit edit_rename;
	CString nameshow;

	afx_msg void OnBnClickedOk();
};