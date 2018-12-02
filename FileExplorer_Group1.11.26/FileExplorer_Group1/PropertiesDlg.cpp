// PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "PropertiesDlg.h"
#include "afxdialogex.h"
#include "FileExplorer_Group1Dlg.h"

// PropertiesDlg dialog

IMPLEMENT_DYNAMIC(PropertiesDlg, CDialogEx)

PropertiesDlg::PropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROPERTIES, pParent)
{

}

PropertiesDlg::~PropertiesDlg()
{
}

void PropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROPERTIES_DLG_NAME, edit_properties_name);
	DDX_Control(pDX, IDC_STATIC_PROPERTIES_TYPE, edit_properties_type);
	DDX_Control(pDX, IDC_STATIC_PROPERTIES_SIZE, edit_properties_size);
	DDX_Control(pDX, IDC_STATIC_PROPERTIES_PATH, edit_properties_path);
}


BEGIN_MESSAGE_MAP(PropertiesDlg, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL PropertiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	edit_properties_name.SetWindowText(urlInfo.g_name);
	edit_properties_path.SetWindowText(urlInfo.g_path);
	edit_properties_size.SetWindowText(urlInfo.g_size);
	edit_properties_type.SetWindowText(urlInfo.g_type);
	SetTimer(1, 1000, NULL);
	return TRUE;
}


void PropertiesDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		ULONGLONG dwLength = sizeFile;
		if (dwLength < 1024)
		{
			urlInfo.g_size.Format(_T("%I64u bytes (%I64u bytes)"), dwLength, dwLength);

		}
		else if ((double)dwLength / 1024 < 1024)
		{
			urlInfo.g_size.Format(_T("%.2f KB (%I64u bytes)"), (double)dwLength / 1024, dwLength);
		}
		else if ((double)dwLength / 1024 / 1024 < 1024)
		{
			urlInfo.g_size.Format(_T("%.2f MB (%I64u bytes)"), (double)dwLength / 1024 / 1024, dwLength);
		}
		else
		{
			urlInfo.g_size.Format(_T("%.2f GB (%I64u bytes)"), (double)dwLength / 1024 / 1024 / 1024, dwLength);
		}
		edit_properties_size.SetWindowText(urlInfo.g_size);
		UpdateData(false);
	}
	CDialog::OnTimer(nIDEvent);
}
