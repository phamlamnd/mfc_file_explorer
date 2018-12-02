//// RenameDialog.cpp : implementation file
////
//
//#include "stdafx.h"
//#include "FileExplorer_Group1.h"
//#include "RenameDialog.h"
//#include "afxdialogex.h"
//
//
//// RenameDialog dialog
//
//IMPLEMENT_DYNAMIC(RenameDialog, CDialogEx)
//
//RenameDialog::RenameDialog(CWnd* pParent /*=NULL*/)
//	: CDialogEx(IDD_DIALOG_RENAME, pParent)
//{
//
//}
//
//RenameDialog::~RenameDialog()
//{
//}
//
//void RenameDialog::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_EDIT_RENAME, edit_rename);
//}
//
//
//BEGIN_MESSAGE_MAP(RenameDialog, CDialogEx)
//END_MESSAGE_MAP()
//
//
//// RenameDialog message handlers

// Sub_Menu_To_Delete.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "RenameDialog.h"
#include "afxdialogex.h"
#include "FileExplorer_Group1Dlg.h"


// Sub_Menu_To_Delete dialog

IMPLEMENT_DYNAMIC(RenameDialog, CDialogEx)

RenameDialog::RenameDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RENAME, pParent)
{

	EnableAutomation();

}

RenameDialog::~RenameDialog()
{
}

void RenameDialog::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void RenameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RENAME, edit_rename);
}


BEGIN_MESSAGE_MAP(RenameDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &RenameDialog::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(RenameDialog, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_ISub_Menu_To_Delete to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {401E5024-A0C9-4745-9EB7-C86483278D1E}
static const IID IID_ISub_Menu_To_Rename =
{ 0x401E5024, 0xA0C9, 0x4745,{ 0x9E, 0xB7, 0xC8, 0x64, 0x83, 0x27, 0x8D, 0x1E } };

BEGIN_INTERFACE_MAP(RenameDialog, CDialogEx)
	INTERFACE_PART(RenameDialog, IID_ISub_Menu_To_Rename, Dispatch)
END_INTERFACE_MAP()


// Sub_Menu_To_Delete message handlers


void RenameDialog::OnBnClickedOk()
{
	edit_rename.GetWindowTextW(nameshow);
	CDialogEx::OnOK();
}