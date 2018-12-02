#pragma once
#include "afxwin.h"

// PropertiesDlg dialog

class PropertiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PropertiesDlg)

public:
	PropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~PropertiesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	CEdit edit_properties_name;
	CStatic edit_properties_type;
	CStatic edit_properties_size;
	CStatic edit_properties_path;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
