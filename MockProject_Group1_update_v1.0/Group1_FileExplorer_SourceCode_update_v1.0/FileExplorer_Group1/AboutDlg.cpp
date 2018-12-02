// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "AboutDlg.h"
#include "afxdialogex.h"


// AboutDlg dialog

IMPLEMENT_DYNAMIC(AboutDlg, CDialogEx)

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ABOUT, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AboutDlg, CDialogEx)
END_MESSAGE_MAP()


// AboutDlg message handlers
