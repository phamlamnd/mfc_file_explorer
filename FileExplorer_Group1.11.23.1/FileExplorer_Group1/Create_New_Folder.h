#pragma once
#include "afxwin.h"


// Create_New_Folder dialog

class Create_New_Folder : public CDialogEx
{
	DECLARE_DYNAMIC(Create_New_Folder)

public:
	Create_New_Folder(CWnd* pParent = NULL);   // standard constructor
	virtual ~Create_New_Folder();

	virtual void OnFinalRelease();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_NEW_FOLDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	CEdit edit_name_folder;
public:
	afx_msg void OnBnClickedOk();
	CString newname;
};
