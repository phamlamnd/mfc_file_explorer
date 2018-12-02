
// FileExplorer_Group1Dlg.h : header file
//

#pragma once
#include "afxshelltreectrl.h"
#include "afxshelllistctrl.h"
#include "afxwin.h"
#include "AboutDlg.h"
#include "PropertiesDlg.h"
#include "FileOperations.h"
#include <vector>
#include <thread>

//size of file
extern ULONGLONG sizeFile;
//check is thread is running
extern bool stopThread;

//Linked list struct
struct List_path
{
	CString list_path;
	List_path * next;
	List_path * prev;
};

//declare linked list
extern List_path * current;
extern List_path * head;
extern List_path * tail;

//add path to linked list
void AddListPath(CString &path);

//free memory alocate for linked list
void DelLink();

//file or folder properties
struct CurrentUrlInfo
{
	CString g_name;
	CString g_type;
	CString g_size;
	CString g_path;
};

//mofify macro
#define MODIFY_NONE					0
#define MODIFY_CUT					1
#define MODIFY_COPY					2
#define MODIFY_PASTE				4
#define MODIFY_ITEM_TREE_CLICK		8
#define MODIFY_ITEM_LIST_CLICK		16

//Status mofify struct
struct ModifyInfo
{
	int IsCut; //check is Cut
	int IsCopy; //check is Copy
	int IsPaste; //check is Paste
	int IsItemTreeClick; //check is Item tree click
	int IsItemListClick; //check is Item list click
	std::vector<CString> src_path_; //save path of item when  cut, copy, paste
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
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

	// member variable
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
	//ShellList popup menu view tiles
	afx_msg void OnPopupMenuListViewTiles(); 
	//ShellList popup menu view icons
	afx_msg void OnPopupMenuListViewIcons(); 
	//ShellList popup menu view list
	afx_msg void OnPopupMenuListViewList(); 
	//ShellList popup menu view details
	afx_msg void OnPopupMenuListViewDetails(); 
	//ShellList popup menu refresh
	afx_msg void OnPopupMenuListRefresh(); 
	//ShellList popup menu properties
	afx_msg void OnPopupMenuListProperties(); 
	//ShellList popup menu cut 
	afx_msg void OnPopupMenuListCut(); 
	//ShellList popup menu copy
	afx_msg void OnPopupMenuListCopy(); 
	//ShellList popup menu paste
	afx_msg void OnPopupMenuListPaste(); 
	//ShellList popup menu delete
	afx_msg void OnPopupMenuListDelete(); 
	//ShellList popup menu rename
	afx_msg void OnPopupMenuListRename(); 
	//ShellList popup menu new folder
	afx_msg void OnPopupMenuListNewFolder(); 
	//ShellList popup menu new text document
	afx_msg void OnPopupMenuListNewTextdocument(); 
	//ShellList popup menu open folder
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
	//Menu edit cut
	afx_msg void OnMenuEditCut(); 
	//Menu edit copy
	afx_msg void OnMenuEditCopy(); 
	//Menu edit paste
	afx_msg void OnMenuEditPaste(); 
	//Shell list Short key Ctrl+C, Ctrl+X, Ctrl+V, Ctrl+O, F2, F5
	afx_msg void OnLvnKeydownMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//end change list item
	afx_msg void OnLvnEndlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//Search on edit box
	afx_msg void OnEnChangeEditSearch(); 
	//check right click item on shell list
	afx_msg void OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//check left click item on shell list
	afx_msg void OnNMClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult); 
	//end edit item on tree
	afx_msg void OnTvnEndlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
	//Tree Short key Ctrl+C, Ctrl+X, Ctrl+V, Ctrl+O, F2
	afx_msg void OnTvnKeydownMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult);
	//auto resizing status bar
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	//update status bar
	afx_msg void OnTimer(UINT_PTR nIDEvent); 
	//check select changing on tree item
	afx_msg void OnTvnSelchangingMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult); 
};