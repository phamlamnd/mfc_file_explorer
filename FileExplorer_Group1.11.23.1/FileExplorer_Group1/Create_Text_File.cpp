// Create_Text_File.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "Create_Text_File.h"
#include "afxdialogex.h"


// Create_Text_File dialog

IMPLEMENT_DYNAMIC(Create_Text_File, CDialogEx)

Create_Text_File::Create_Text_File(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATE_TEXT_FILE, pParent)
{

	EnableAutomation();

}

Create_Text_File::~Create_Text_File()
{
}

void Create_Text_File::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void Create_Text_File::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_name_text);
}


BEGIN_MESSAGE_MAP(Create_Text_File, CDialogEx)
	ON_BN_CLICKED(IDOK, &Create_Text_File::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(Create_Text_File, CDialogEx)
END_DISPATCH_MAP()

// Note: we add support for IID_Ireate_Text_File to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {4509D8DE-F0A5-4BF5-A3E7-C64E3C191F13}
static const IID IID_Ireate_Text_File =
{ 0x4509D8DE, 0xF0A5, 0x4BF5, { 0xA3, 0xE7, 0xC6, 0x4E, 0x3C, 0x19, 0x1F, 0x13 } };

BEGIN_INTERFACE_MAP(Create_Text_File, CDialogEx)
	INTERFACE_PART(Create_Text_File, IID_Ireate_Text_File, Dispatch)
END_INTERFACE_MAP()


// Create_Text_File message handlers


void Create_Text_File::OnBnClickedOk()
{
	edit_name_text.GetWindowTextW(newname);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
