#pragma once
#include "afxwin.h"


// Create_Text_File dialog

class Create_Text_File : public CDialogEx
{
	DECLARE_DYNAMIC(Create_Text_File)

public:
	Create_Text_File(CWnd* pParent = NULL);   // standard constructor
	virtual ~Create_Text_File();

	virtual void OnFinalRelease();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATE_TEXT_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CEdit edit_name_text;
	afx_msg void OnBnClickedOk();
	CString newname;
};
