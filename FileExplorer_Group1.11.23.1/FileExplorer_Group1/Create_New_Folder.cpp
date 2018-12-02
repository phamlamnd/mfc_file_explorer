// Create_New_Folder.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "Create_New_Folder.h"
#include "afxdialogex.h"


// Create_New_Folder dialog

IMPLEMENT_DYNAMIC(Create_New_Folder, CDialogEx)

Create_New_Folder::Create_New_Folder(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_NEW_FOLDER, pParent)
{

	EnableAutomation();

}

Create_New_Folder::~Create_New_Folder()
{
}

void Create_New_Folder::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void Create_New_Folder::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_name_folder);
}


BEGIN_MESSAGE_MAP(Create_New_Folder, CDialogEx)
	ON_BN_CLICKED(IDOK, &Create_New_Folder::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Create_New_Folder, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_Ireate_New_Folder to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {86E2BD1A-05EA-4DBD-9C4F-805D85738D4D}
static const IID IID_Ireate_New_Folder =
{ 0x86E2BD1A, 0x5EA, 0x4DBD, { 0x9C, 0x4F, 0x80, 0x5D, 0x85, 0x73, 0x8D, 0x4D } };

BEGIN_INTERFACE_MAP(Create_New_Folder, CDialogEx)
	INTERFACE_PART(Create_New_Folder, IID_Ireate_New_Folder, Dispatch)
END_INTERFACE_MAP()


// Create_New_Folder message handlers


void Create_New_Folder::OnBnClickedOk()
{
	edit_name_folder.GetWindowTextW(newname);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
