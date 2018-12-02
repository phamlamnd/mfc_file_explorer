
// FileExplorer_Group1Dlg.h : header file
//

#pragma once
#include "afxshelltreectrl.h"
#include "afxshelllistctrl.h"
#include "afxwin.h"
#include "PropertiesDlg.h"
#include "AboutDlg.h"
#include "RenameDialog.h"
#include "FileOperations.h"
#include <vector>
#include <thread>
#include <unordered_map>
#include <thread>
//Declare Current file and folder properties
extern ULONGLONG sizeFile;
extern bool check_Thread;
struct CurrentUrlInfo
{
	CString g_name;
	CString g_type;
	CString g_size;
	CString g_path;
};

#define MODIFY_NONE					0
#define MODIFY_CUT					1
#define MODIFY_COPY					2
#define MODIFY_PASTE				4
#define MODIFY_ITEM_TREE_CLICK		8
#define MODIFY_ITEM_LIST_CLICK		16

struct ModifyInfo
{
	int IsCut;
	int IsCopy;
	int IsPaste;
	int IsItemTreeClick;
	int IsItemListClick;
	CString src_path;
	CString src_name;
	CString des_path;
	CString des_name;

	std::vector<CString> src_path_;
	std::vector<CString> src_name_;
};

extern CurrentUrlInfo urlInfo;
extern ModifyInfo modifyInfo;

// CFileExplorer_Group1Dlg dialog
class CFileExplorer_Group1Dlg : public CDialogEx
{
// Construction
public:
	CFileExplorer_Group1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEEXPLORER_GROUP1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void OnOK(); 
	CMFCShellTreeCtrl shell_tree; 
	CMFCShellListCtrl shell_list; 
	CComboBox combo_box_path; 
	CComboBox combo_box_view;
	CButton button_go;
	CButton button_search;
	CEdit edit_search;
	CButton button_foward;
	CButton button_back;
	CListBox count_item;
	CStatusBar m_bar;
public:
	//Click on shell tree and display on shell list and combobox
	afx_msg void OnNMClickMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
	//double click on shell list and display on combobox
	afx_msg void OnLvnItemActivateMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//View select on combobox
	afx_msg void OnCbnSelchangeComboBoxView(); 
	//ShellList Right click menu
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/); 
	//Dialog About
	afx_msg void OnMenuHelpAbout(); 
	//Select View Tiles on Menu 
	afx_msg void OnMenuViewTiles(); 
	//Select View Icon on Menu 
	afx_msg void OnMenuViewIcons(); 
	//Select View List on Menu 
	afx_msg void OnMenuViewList();
	//Select View Details on Menu
	afx_msg void OnMenuViewDetails(); 
	//Menu new folder
	afx_msg void OnMenuFileNewFloder();
	//Menu new doccument
	afx_msg void OnMenuFileNewTextdocument(); 
	//Menu open folder
	afx_msg void OnMenuFileOpen();
	//Menu delete
	afx_msg void OnMenuFileDelete(); 
	//Menu rename
	afx_msg void OnMenuFileRename(); 
	//Menu properties
	afx_msg void OnMenuFileProperties(); 
	//Menu close
	afx_msg void OnMenuFileClose(); 
	//button go
	afx_msg void OnBnClickedGo(); 
	//Back button
	afx_msg void OnBnClickedButtonBack(); 
	//Foward button
	afx_msg void OnBnClickedButtonFoward(); 
	//Popup Menu view tiles
	afx_msg void OnPopupMenuListViewTiles(); 
	//Popup Menu view icons
	afx_msg void OnPopupMenuListViewIcons(); 
	//Popup Menu view list
	afx_msg void OnPopupMenuListViewList(); 
	//Popup Menu view details
	afx_msg void OnPopupMenuListViewDetails(); 
	//Popup menu refresh
	afx_msg void OnPopupMenuListRefresh(); 
	//Popup menu properties
	afx_msg void OnPopupMenuListProperties(); 
	//Popup menu cut 
	afx_msg void OnPopupMenuListCut(); 
	//Popup menu copy
	afx_msg void OnPopupMenuListCopy(); 
	//Popup menu paste
	afx_msg void OnPopupMenuListPaste(); 
	//Popup menu delete
	afx_msg void OnPopupMenuListDelete(); 
	//Popup menu rename
	afx_msg void OnPopupMenuListRename(); 
	//Popup menu new folder
	afx_msg void OnPopupMenuListNewFolder(); 
	//popup menu new text document
	afx_msg void OnPopupMenuListNewTextdocument(); 
	//PopupMenu open folder
	afx_msg void OnPopupMenuListOpen(); 
	//ShellTree popup menu open
	afx_msg void OnPopupMenuTreeOpen(); 
	//ShellTree popup menu cut
	afx_msg void OnPopupMenuTreeCut(); 
	//ShellTree popup menu copy
	afx_msg void OnPopupMenuTreeCopy(); 
	//ShellTree popup menu paste
	afx_msg void OnPopupMenuTreePaste(); 
	//ShellTree popup menu delete
	afx_msg void OnPopupMenuTreeDelete(); 
	//ShellTree popup menu rename
	afx_msg void OnPopupMenuTreeRename(); 
	//ShellTree popup menu properties
	afx_msg void OnPopupMenuTreeProperties();
	//Cut on menu
	afx_msg void OnMenuEditCut(); 
	//copy on menu
	afx_msg void OnMenuEditCopy(); 
	//paste on menu
	afx_msg void OnMenuEditPaste(); 
	//Short key Ctrl+C, Ctrl+X, Ctrl+V, Ctrl+O, F2, F5
	afx_msg void OnLvnKeydownMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//begin change list item
	afx_msg void OnLvnBeginlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//end change list item
	afx_msg void OnLvnEndlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//Search
	afx_msg void OnEnChangeEditSearch(); 
	//check left click item on shell list
	afx_msg void OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//check right click item on shell list
	afx_msg void OnNMClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//begin edit item on tree
	afx_msg void OnTvnBeginlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
	//end edit item on tree
	afx_msg void OnTvnEndlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
	//short key on tree
	afx_msg void OnTvnKeydownMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);
	//auto resizing status bar
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	//update status bar
	afx_msg void OnTimer(UINT_PTR nIDEvent); 
	//check click on tree item
	afx_msg void OnTvnSelchangingMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
};