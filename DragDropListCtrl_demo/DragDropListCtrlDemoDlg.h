// DragDropListCtrlDemoDlg.h : header file
//

#if !defined(AFX_DRAGDROPLISTCTRLDEMODLG_H__F09F06AB_9579_4A9D_A605_B2FE0CE9DC55__INCLUDED_)
#define AFX_DRAGDROPLISTCTRLDEMODLG_H__F09F06AB_9579_4A9D_A605_B2FE0CE9DC55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DragDropListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDragDropListCtrlDemoDlg dialog

class CDragDropListCtrlDemoDlg : public CDialog
{
// Construction
public:
	CDragDropListCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDragDropListCtrlDemoDlg)
	enum { IDD = IDD_DRAGDROPLISTCTRLDEMO_DIALOG };
	CDragDropListCtrl	m_List;
	CString	m_sItemData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragDropListCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDragDropListCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGDROPLISTCTRLDEMODLG_H__F09F06AB_9579_4A9D_A605_B2FE0CE9DC55__INCLUDED_)
