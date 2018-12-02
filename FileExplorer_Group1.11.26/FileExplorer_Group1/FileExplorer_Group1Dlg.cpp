
// FileExplorer_Group1Dlg.cpp : implementation file

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "FileExplorer_Group1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// status bar code
static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_NISH,
	ID_INDICATOR_TIME
};

// Define current file and folder properties
CurrentUrlInfo urlInfo;

// Define modify infomation: Cut, Copy, Paste
ModifyInfo modifyInfo;

// Create linked list
List_path * current = NULL;
List_path * head = NULL;
List_path * tail = NULL;

//Add path to linked list funcion
void AddListPath(CString &path)
{
	struct List_path * link;
	link = new List_path;
	link->list_path = path;
	if (current == NULL)
	{
		current = link;
		current->prev = NULL;
		current->next = NULL;
		head = tail = current;
		head->next = current->next;
		tail->prev = current->prev;
	}
	else
	{
		if (current->next != NULL)
		{
			struct List_path * node = current->next;
			node->next = current->next->next;
			node->prev = NULL;
			while (node != NULL)
			{
				struct List_path * _node = node;
				node = node->next;
				_node->list_path = "";
				delete _node;
			}
		}
		current->next = link;
		link->prev = current;
		current = link;
		current->next = NULL;
	}
}

//Free linked list memory
void DelLink()
{
	if (head == NULL)
		return;
	current = head;
	current->next = head->next;
	while (current != NULL)
	{
		struct List_path * node;
		node = current;
		current = current->next;
		delete node;
	}
}

// Count Number item on list view
void CountItem(CListCtrl &list_view, CListBox &list_box)
{
	unsigned int i = list_view.GetItemCount();
	CString str1;
	str1.Format(_T("%d item"), i);
	list_box.DeleteString(0);
	list_box.AddString(str1);
	list_box.SetCurSel(0);
}

// CFileExplorer_Group1Dlg dialog
CFileExplorer_Group1Dlg::CFileExplorer_Group1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILEEXPLORER_GROUP1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// Data Exchange
void CFileExplorer_Group1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCSHELLTREE1, shell_tree);
	DDX_Control(pDX, IDC_MFCSHELLLIST1, shell_list);
	DDX_Control(pDX, IDC_COMBO_BOX_PATH, combo_box_path);
	DDX_Control(pDX, IDC_COMBO_BOX_VIEW, combo_box_view);
	DDX_Control(pDX, IDC_GO, button_go);
	DDX_Control(pDX, IDC_SEARCH, button_search);
	DDX_Control(pDX, IDC_EDIT_SEARCH, edit_search);
	DDX_Control(pDX, IDC_BUTTON_FOWARD, button_foward);
	DDX_Control(pDX, IDC_BUTTON_BACK, button_back);
	DDX_Control(pDX, IDC_COUNT_ITEM, count_item);
}

// Message map
BEGIN_MESSAGE_MAP(CFileExplorer_Group1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_BOX_VIEW, &CFileExplorer_Group1Dlg::OnCbnSelchangeComboBoxView)
	ON_COMMAND(ID_MENU_VIEW_TILES, &CFileExplorer_Group1Dlg::OnMenuViewTiles)
	ON_COMMAND(ID_MENU_VIEW_ICONS, &CFileExplorer_Group1Dlg::OnMenuViewIcons)
	ON_COMMAND(ID_MENU_VIEW_LISTS, &CFileExplorer_Group1Dlg::OnMenuViewList)
	ON_COMMAND(ID_MENU_VIEW_DETAILS, &CFileExplorer_Group1Dlg::OnMenuViewDetails)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENU_HELP_ABOUT, &CFileExplorer_Group1Dlg::OnMenuHelpAbout)
	ON_COMMAND(ID_MENU_NEW_FLODER, &CFileExplorer_Group1Dlg::OnMenuFileNewFloder)
	ON_COMMAND(ID_MENU_NEW_TEXTDOCUMENT, &CFileExplorer_Group1Dlg::OnMenuFileNewTextdocument)
	ON_COMMAND(ID_POPUP_MENU_VIEW_TILES, &CFileExplorer_Group1Dlg::OnPopupMenuListViewTiles)
	ON_COMMAND(ID_POPUP_MENU_VIEW_ICONS, &CFileExplorer_Group1Dlg::OnPopupMenuListViewIcons)
	ON_COMMAND(ID_POPUP_MENU_VIEW_LIST, &CFileExplorer_Group1Dlg::OnPopupMenuListViewList)
	ON_COMMAND(ID_POPUP_MENU_VIEW_DETAILS, &CFileExplorer_Group1Dlg::OnPopupMenuListViewDetails)
	ON_COMMAND(ID_POPUP_MENU_REFRESH, &CFileExplorer_Group1Dlg::OnPopupMenuListRefresh)
	ON_COMMAND(ID_POPUP_MENU_PROPERTIES, &CFileExplorer_Group1Dlg::OnPopupMenuListProperties)
	ON_BN_CLICKED(IDC_GO, &CFileExplorer_Group1Dlg::OnBnClickedGo)
	ON_COMMAND(ID_POPUP_MENU_CUT, &CFileExplorer_Group1Dlg::OnPopupMenuListCut)
	ON_COMMAND(ID_POPUP_MENU_COPY, &CFileExplorer_Group1Dlg::OnPopupMenuListCopy)
	ON_COMMAND(ID_POPUP_MENU_PASTE, &CFileExplorer_Group1Dlg::OnPopupMenuListPaste)
	ON_COMMAND(ID_POPUP_MENU_DELETE, &CFileExplorer_Group1Dlg::OnPopupMenuListDelete)
	ON_COMMAND(ID_POPUP_MENU_RENAME, &CFileExplorer_Group1Dlg::OnPopupMenuListRename)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &CFileExplorer_Group1Dlg::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_FOWARD, &CFileExplorer_Group1Dlg::OnBnClickedButtonFoward)
	ON_COMMAND(ID_POPUP_MENU_NEW_FOLDER, &CFileExplorer_Group1Dlg::OnPopupMenuListNewFolder)
	ON_COMMAND(ID_POPUP_MENU_NEW_TEXTDOCUMENT, &CFileExplorer_Group1Dlg::OnPopupMenuListNewTextdocument)
	ON_COMMAND(ID_MENU_FILE_OPEN, &CFileExplorer_Group1Dlg::OnMenuFileOpen)
	ON_COMMAND(ID_POPUP_MENU_OPEN, &CFileExplorer_Group1Dlg::OnPopupMenuListOpen)
	ON_COMMAND(ID_POPUP_MENU_TREE_OPEN, &CFileExplorer_Group1Dlg::OnPopupMenuTreeOpen)
	ON_COMMAND(ID_POPUP_MENU_TREE_CUT, &CFileExplorer_Group1Dlg::OnPopupMenuTreeCut)
	ON_COMMAND(ID_POPUP_MENU_TREE_COPY, &CFileExplorer_Group1Dlg::OnPopupMenuTreeCopy)
	ON_COMMAND(ID_POPUP_MENU_TREE_PASTE, &CFileExplorer_Group1Dlg::OnPopupMenuTreePaste)
	ON_COMMAND(ID_POPUP_MENU_TREE_DELETE, &CFileExplorer_Group1Dlg::OnPopupMenuTreeDelete)
	ON_COMMAND(ID_POPUP_MENU_TREE_RENAME, &CFileExplorer_Group1Dlg::OnPopupMenuTreeRename)
	ON_COMMAND(ID_POPUP_MENU_TREE_PROPERTIES, &CFileExplorer_Group1Dlg::OnPopupMenuTreeProperties)
	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnNMClickMfcshelltree1)
	ON_COMMAND(ID_MENU_FILE_DELETE, &CFileExplorer_Group1Dlg::OnMenuFileDelete)
	ON_COMMAND(ID_MENU_FILE_RENAME, &CFileExplorer_Group1Dlg::OnMenuFileRename)
	ON_COMMAND(ID_MENU_FILE_PROPERTIES, &CFileExplorer_Group1Dlg::OnMenuFileProperties)
	ON_COMMAND(ID_MENU_FILE_CLOSE, &CFileExplorer_Group1Dlg::OnMenuFileClose)
	ON_COMMAND(ID_MENU_EDIT_CUT, &CFileExplorer_Group1Dlg::OnMenuEditCut)
	ON_COMMAND(ID_MENU_EDIT_COPY, &CFileExplorer_Group1Dlg::OnMenuEditCopy)
	ON_COMMAND(ID_MENU_EDIT_PASTE, &CFileExplorer_Group1Dlg::OnMenuEditPaste)
	ON_NOTIFY(LVN_KEYDOWN, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnKeydownMfcshelllist1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnEndlabeleditMfcshelllist1)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CFileExplorer_Group1Dlg::OnEnChangeEditSearch)
	ON_NOTIFY(NM_RCLICK, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnNMRClickMfcshelllist1)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnItemActivateMfcshelllist1)
	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnNMClickMfcshelllist1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnEndlabeleditMfcshelltree1)
	ON_NOTIFY(TVN_KEYDOWN, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnKeydownMfcshelltree1)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(TVN_SELCHANGING, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnSelchangingMfcshelltree1)
END_MESSAGE_MAP()

// Init dialog
BOOL CFileExplorer_Group1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. 
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	HICON hIcon2 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2));
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	button_back.SetIcon(hIcon);
	button_foward.SetIcon(hIcon2);

	// Init tree view
	HTREEITEM hParent = shell_tree.GetRootItem();
	shell_tree.Expand(hParent, TVE_EXPAND);
	
	// Init for list view and combobox
	shell_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	combo_box_view.AddString(_T("Tiles"));
	combo_box_view.AddString(_T("Icons"));
	combo_box_view.AddString(_T("List"));
	combo_box_view.AddString(_T("Details"));
	combo_box_view.SetCurSel(0);

	// Init status bar
	SetTimer(2, 1000, NULL);
	CRect rectOld;
	CRect rectNew;
	CRect rect;
	CPoint ptOffset;
	CWnd *pWndCtrl;
	GetClientRect(rectOld);

	m_bar.Create(this);
	m_bar.SetIndicators(indicators, 2);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_TIME, CWnd::reposQuery, rectNew);
	ptOffset.x = rectNew.left - rectOld.left;
	ptOffset.y = rectNew.top - rectOld.top;
	pWndCtrl = GetWindow(GW_CHILD);
	while (pWndCtrl)
	{
		pWndCtrl->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.OffsetRect(ptOffset);
		pWndCtrl->MoveWindow(rect, FALSE);
		pWndCtrl = pWndCtrl->GetNextWindow();
	}
	GetWindowRect(rect);
	rect.right += rectOld.Width() - rectNew.Width();
	rect.bottom += rectOld.Height() - rectNew.Height();
	MoveWindow(rect);
	m_bar.SetPaneInfo(0, ID_INDICATOR_NISH, SBPS_NORMAL, rect.Width() - 100);
	m_bar.SetPaneInfo(1, ID_INDICATOR_TIME, SBPS_STRETCH, 50);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CFileExplorer_Group1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileExplorer_Group1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//View select on combobox
void CFileExplorer_Group1Dlg::OnCbnSelchangeComboBoxView()
{
	int view_by = combo_box_view.GetCurSel();
	switch (view_by)
	{
	case 3: shell_list.SetView(LV_VIEW_TILE); break;
	case 2:	shell_list.SetView(LV_VIEW_ICON); break;
	case 1:	shell_list.SetView(LV_VIEW_LIST); break;
	case 0: shell_list.SetView(LV_VIEW_DETAILS); break;
	default: break;
	}
}

//Select View Tiles on Menu
void CFileExplorer_Group1Dlg::OnMenuViewTiles()
{
	shell_list.SetView(LV_VIEW_TILE);
}

//Select View Icon on Menu
void CFileExplorer_Group1Dlg::OnMenuViewIcons()
{
	shell_list.SetView(LV_VIEW_ICON);
}

//Select View List on Menu
void CFileExplorer_Group1Dlg::OnMenuViewList()
{
	shell_list.SetView(LV_VIEW_LIST);
}

//Select View Details on Menu
void CFileExplorer_Group1Dlg::OnMenuViewDetails()
{
	shell_list.SetView(LV_VIEW_DETAILS);
}

//Right click Popup menu on listview and treeview
void CFileExplorer_Group1Dlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//Load menu
	CMenu mnuPopupListView, mnuPopupTreeView;
	mnuPopupListView.LoadMenu(IDR_MENU2);
	mnuPopupTreeView.LoadMenu(IDR_MENU3);
	//Get a pointer to the button
	CButton *pButton1, *pButton2;
	pButton1 = reinterpret_cast<CButton*>(GetDlgItem(IDC_MFCSHELLLIST1));
	pButton2 = reinterpret_cast<CButton*>(GetDlgItem(IDC_MFCSHELLTREE1));
	//Find the rectangle around the button
	CRect rectListView, rectTreeView;
	pButton1->GetWindowRect(&rectListView);
	pButton2->GetWindowRect(&rectTreeView);
	//Get a pointer to the first item of menu
	CMenu *mnuPopupMenu1 = mnuPopupListView.GetSubMenu(0);
	CMenu *mnuPopupMenu2 = mnuPopupTreeView.GetSubMenu(0);

	//Disable popup menu on list
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PASTE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_RENAME, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_OPEN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PROPERTIES, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	//Enable Popup menu list when click on item
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_CUT, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_COPY, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_DELETE, MF_BYCOMMAND | MF_ENABLED);
		if (shell_list.GetSelectedCount() == 1)
		{
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_RENAME, MF_BYCOMMAND | MF_ENABLED);
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_OPEN, MF_BYCOMMAND | MF_ENABLED);
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PROPERTIES, MF_BYCOMMAND | MF_ENABLED);
		}	
	}
	if (modifyInfo.IsItemListClick == MODIFY_NONE)
	{
		if (modifyInfo.IsPaste == MODIFY_PASTE)
		{
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PASTE, MF_BYCOMMAND | MF_ENABLED);
		}
	}

	//Disable popup menu treeview
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PASTE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_RENAME, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_OPEN, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PROPERTIES, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	//Check is click on tree item
	UINT uFlags;
	CPoint treePoint(::GetMessagePos());
	shell_tree.ScreenToClient(&treePoint);
	HTREEITEM hItem = shell_tree.HitTest(treePoint, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM &uFlags))
	{
		modifyInfo.IsItemTreeClick = MODIFY_ITEM_TREE_CLICK;
		modifyInfo.IsItemListClick = MODIFY_NONE;
	}

	//Enable Popup menu tree when click on item
	if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_CUT, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_COPY, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_DELETE, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_RENAME, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_OPEN, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PROPERTIES, MF_BYCOMMAND | MF_ENABLED);
		if (modifyInfo.IsPaste == MODIFY_PASTE)
		{
			mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PASTE, MF_BYCOMMAND | MF_ENABLED);
		}
	}

	ASSERT(mnuPopupMenu1);
	ASSERT(mnuPopupMenu2);
	
	//Tracking right click on list and tree
	if (rectListView.PtInRect(point))
		mnuPopupMenu1->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	if (rectTreeView.PtInRect(point))
		mnuPopupMenu2->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

//Get size of folder using multithread
ULONGLONG DoGetSize(CString sPathName);
void GetSize(CString sPathName);
//size of file golobal variable
ULONGLONG sizeFile = 0;
//Stop thread signal
bool stopThread = false;

//Get size of file or folder
void GetSize(CString sPathName)
{
	CFileFind finder;
	if (CFileOperation::CheckPath(sPathName) == PATH_IS_FILE)
	{
		sizeFile = DoGetSize(sPathName);
		return;
	}
	CString strWildcard(sPathName);
	strWildcard += _T("\\*.*");
	// start working for files
	BOOL bWorking = finder.FindFile(strWildcard);
	while (bWorking && !stopThread) //Check stop thread signal, and find file
	{
		bWorking = finder.FindNextFile();

		// skip . and .. files
		if (finder.IsDots())
			continue;
		// if it's a directory, recursively search it
		CString str = finder.GetFilePath();
		if (finder.IsDirectory()) //is folder
		{
			GetSize(str);
		}
		else //is file
		{
			sizeFile += DoGetSize(str);
		}
	}
	finder.Close();
}

//Get size one file
ULONGLONG DoGetSize(CString sPathName)
{
	CFile* pFile = NULL;
	CString str = sPathName;
	ULONGLONG dwLength = 0;
	try
	{
		pFile = new CFile(sPathName, CFile::modeRead | CFile::shareDenyNone);
		dwLength = pFile->GetLength();
	}
	catch (CFileException* pEx)
	{
		pEx->Delete();
	}
	catch (CMemoryException* pEx)
	{
		pEx->Delete();
		AfxAbort();
	}

	if (pFile != NULL)
	{
		pFile->Close();
		delete pFile;
	}
	return dwLength;
}

//Properties on right click menu
void CFileExplorer_Group1Dlg::OnPopupMenuListProperties()
{
	sizeFile = 0;
	stopThread = false;
	int index = shell_list.GetNextItem(-1, LVNI_SELECTED);
	if (index != -1)
	{
		urlInfo.g_name = shell_list.GetItemText(index, 0);	//get name
		shell_list.GetItemPath(urlInfo.g_path, index);		//get path
		if (CFileOperation::CheckPath(urlInfo.g_path) == PATH_IS_FILE)	//get type
		{
			urlInfo.g_type.Format(_T("File"));
		}
		else if (CFileOperation::CheckPath(urlInfo.g_path) == PATH_IS_FOLDER)
		{
			urlInfo.g_type.Format(_T("Folder"));
		}

		//start thread
		std::thread thr = std::thread(GetSize, urlInfo.g_path);
		thr.detach();
		ULONGLONG dwLength = sizeFile; //get size
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
		PropertiesDlg propertiesDlg;
		propertiesDlg.DoModal(); //wating here
		stopThread = true; //pass sinal to stop thread
	}
}

//Dialog About
void CFileExplorer_Group1Dlg::OnMenuHelpAbout()
{
	AboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//Get path from ShellList, display combobox
void CFileExplorer_Group1Dlg::OnLvnItemActivateMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString diskPath;
	shell_list.GetCurrentFolder(diskPath);
	combo_box_path.AddString(diskPath);
	combo_box_path.SetWindowTextW(diskPath);
	AddListPath(diskPath); //add to linked list
	CountItem(shell_list, count_item);
	*pResult = 0;
}

//create new folder on menu
void CFileExplorer_Group1Dlg::OnMenuFileNewFloder()
{
	OnPopupMenuListNewFolder();
}

//create new text document on menu
void CFileExplorer_Group1Dlg::OnMenuFileNewTextdocument()
{
	OnPopupMenuListNewTextdocument();
}

//Popup menu view tiles
void CFileExplorer_Group1Dlg::OnPopupMenuListViewTiles()
{
	shell_list.SetView(LV_VIEW_TILE);
}

//Popup menu view Icon
void CFileExplorer_Group1Dlg::OnPopupMenuListViewIcons()
{
	shell_list.SetView(LV_VIEW_ICON);
}

//Popup menu view list
void CFileExplorer_Group1Dlg::OnPopupMenuListViewList()
{
	shell_list.SetView(LV_VIEW_LIST);
}

//Popup menu view details
void CFileExplorer_Group1Dlg::OnPopupMenuListViewDetails()
{
	shell_list.SetView(LV_VIEW_DETAILS);
}

//Popup menu refresh
void CFileExplorer_Group1Dlg::OnPopupMenuListRefresh()
{
	shell_list.Refresh();
}

//Button go click
void CFileExplorer_Group1Dlg::OnBnClickedGo()
{
	CString cb_path;
	combo_box_path.GetWindowTextW(cb_path);
	if (CFileOperation::CheckPath(cb_path) == PATH_NOT_FOUND)
	{
		MessageBox(_T("Item is not exist!"), _T("File Explorer"));
		return;
	}
	shell_list.DisplayFolder(cb_path);
	AddListPath(cb_path);
	CountItem(shell_list, count_item);
}

//button back  click
void CFileExplorer_Group1Dlg::OnBnClickedButtonBack()
{
	if (current != NULL && current->prev != NULL)
	{
		current = current->prev;
		CString path = current->list_path;
		combo_box_path.SetWindowTextW(path);
		shell_list.DisplayFolder(path);
		shell_list.Refresh();
		CountItem(shell_list, count_item);
	}
}

//button foward click
void CFileExplorer_Group1Dlg::OnBnClickedButtonFoward()
{
	if (current != NULL && current->next != NULL)
	{
		current = current->next;
		CString path = current->list_path;
		combo_box_path.SetWindowTextW(path);
		shell_list.DisplayFolder(path);
		CountItem(shell_list, count_item);
	}
}

//Popup menu cut on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListCut()
{
	modifyInfo.IsCut = MODIFY_CUT;
	modifyInfo.IsCopy = MODIFY_NONE;
	modifyInfo.IsPaste = MODIFY_PASTE;
	CString itemPath;
	int uSelectedCount = shell_list.GetSelectedCount();
	int  nItem = -1;
	modifyInfo.src_path_.clear();
	if (uSelectedCount > 0)
		for (int index = 0; index < uSelectedCount; index++)
		{
			nItem = shell_list.GetNextItem(nItem, LVNI_SELECTED);
			shell_list.GetItemPath(itemPath, nItem);
			modifyInfo.src_path_.push_back(itemPath);
		}
}

//Popup menu copy on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListCopy()
{
	modifyInfo.IsCopy = MODIFY_COPY;
	modifyInfo.IsCut = MODIFY_NONE;
	modifyInfo.IsPaste = MODIFY_PASTE;
	CString itemPath;
	int uSelectedCount = shell_list.GetSelectedCount();
	int  nItem = -1;
	modifyInfo.src_path_.clear();
	if (uSelectedCount > 0)
		for (int index = 0; index < uSelectedCount; index++)
		{
			nItem = shell_list.GetNextItem(nItem, LVNI_SELECTED);
			shell_list.GetItemPath(itemPath, nItem);
			modifyInfo.src_path_.push_back(itemPath);
		}
}

//Popup menu paste on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListPaste()
{
	CString parentPath;
	shell_list.GetCurrentFolder(parentPath);
	if (modifyInfo.IsCopy == MODIFY_COPY)
	{
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = parentPath;
			fo.Copy(sSource, sDest);
		}

		shell_list.Refresh();
		shell_tree.Refresh();
		shell_tree.SelectPath(parentPath);
	}
	if (modifyInfo.IsCut == MODIFY_CUT)
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = parentPath;
			fo.Copy(sSource, sDest);
			if (!fo.Delete(sSource)) // delete src
			{
				fo.ShowError(); // if copy fails show error message
			}
		}
		modifyInfo.src_path_.clear();
		shell_list.Refresh();
		shell_tree.Refresh();
		shell_tree.SelectPath(parentPath);
	}
}

//Popup menu delete on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListDelete()
{
	CString diskPath; //item path from disk
	CString itemName; //item name from UI
	int uSelectedCount = shell_list.GetSelectedCount(); //count number select items
	CString sMessagebox; //Message box
	CString sConfirm; //Confirm
	int iCountFolder = 0; //count number of folder
	if (uSelectedCount == 0) //none item select
	{
		return;
	}
	else if (uSelectedCount == 1) //select 1 item
	{
		int nItem = shell_list.GetNextItem(-1, LVNI_SELECTED);
		shell_list.GetItemPath(diskPath, nItem); //get item pat from disk
		itemName = shell_list.GetItemText(nItem, 0); //get item path from UI
		if (CFileOperation::CheckPath(diskPath) == PATH_IS_FILE)
		{
			sMessagebox.Format(_T("Are you sure you want to delete '" + itemName + _T("' file?")));
			sConfirm = _T("Delele File");
		}
		else if (CFileOperation::CheckPath(diskPath) == PATH_IS_FOLDER)
		{
			sMessagebox.Format(_T("Are you sure you want to delete '" + itemName + _T("' folder?")));
			sConfirm = _T("Delele Folder");
		}
		else //path not found
		{
			return;
		}
	}
	else if (uSelectedCount > 1) //select multiple item
	{
		sMessagebox.Format(_T("Are you sure you want to delete these %d items?"), uSelectedCount);
		sConfirm = _T("Delele Multiple Items");
	}

	if (IDYES == MessageBox(sMessagebox, sConfirm, MB_ICONWARNING | MB_YESNO))
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		for (int index = 0; index < uSelectedCount; index++)
		{
			int nItem = shell_list.GetNextItem(-1, LVNI_SELECTED);
			shell_list.GetItemPath(diskPath, nItem);
			if (CFileOperation::CheckPath(diskPath) == PATH_IS_FOLDER) //count number of folder
			{
				iCountFolder++;
			}
			if (current != NULL && current->next != NULL && diskPath == current->next->list_path)
			{
				struct List_path* temp = current->next;
				current->next = NULL;
				delete temp;
			}
			CFileOperation fo;
			fo.Delete(diskPath);  //delete on disk
			shell_list.DeleteItem(nItem); //delete shell list
		}
		if (iCountFolder  > 0) //refresh tree
		{
			shell_tree.Refresh();
			CString current_path;
			combo_box_path.GetWindowTextW(current_path);
			shell_tree.SelectPath(current_path);
		}	
	}
}

//Popup menu rename on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListRename()
{
	int index = shell_list.GetSelectionMark();
	shell_list.EditLabel(index);
}

//Popup menu new folder on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListNewFolder()
{
	CString itemPath;
	shell_list.GetCurrentFolder(itemPath);
	if (itemPath.Right(1) == '\\')
	{
		itemPath.Delete(itemPath.GetLength() - 1, 1);
	}
	CString sNewFolder = L"\\New folder";
	int i = 0;
	while (true)
	{
		if (CreateDirectoryW(itemPath + sNewFolder, NULL))
		{
			break;
		}
		i++;
		sNewFolder.Format(L"\\New folder (%d)", i + 1);
	}
	shell_list.Refresh();
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	info.psz = _T("New folder");
	int index = shell_list.FindItem(&info) + i;
	shell_list.EditLabel(index); //enable edit item

	shell_tree.Refresh();
	shell_tree.SelectPath(itemPath);
}

//popup menu new text document on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListNewTextdocument()
{
	CString itemPath;
	shell_list.GetCurrentFolder(itemPath);
	if (itemPath.Right(1) == '\\')
	{
		itemPath.Delete(itemPath.GetLength() - 1, 1);
	}
	int i = 0;
	CString sNewFile = L"\\New Text Document.txt";
	while (true)
	{
		CFile cfile_object;
		if ((GetFileAttributes(itemPath + sNewFile) == INVALID_FILE_ATTRIBUTES))
		{
			cfile_object.Open(itemPath + sNewFile, CFile::modeReadWrite | CFile::modeCreate);
			break;
		}
		i++;
		sNewFile.Format(L"\\New Text Document (%d).txt", i + 1);
	}
	shell_list.Refresh();
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	info.psz = _T("New Text Document");
	if (i == 0)
	{
		int Index = shell_list.FindItem(&info);
		shell_list.EditLabel(Index);
	}
	else
	{
		int index = shell_list.FindItem(&info) + i - 1;
		shell_list.EditLabel(index); //enable edit item
	}
}

//Popup menu open on listview
void CFileExplorer_Group1Dlg::OnPopupMenuListOpen()
{
	int uSelectedCount = shell_list.GetSelectedCount();
	if(uSelectedCount == 0) //none item select
	{
		return;
	}
	CString diskPath; //full path from disk
	int nItem = shell_list.GetNextItem(-1, LVNI_SELECTED); //get select item index
	shell_list.GetItemPath(diskPath, nItem); //get select item path on disk
	if (CFileOperation::CheckPath(diskPath) == PATH_IS_FOLDER) //path is folder
	{
		shell_list.DisplayFolder(diskPath); //open on shell list
		combo_box_path.SetWindowTextW(diskPath); //update conbobox
		combo_box_path.AddString(diskPath); //add history path on combobox
		AddListPath(diskPath); //add to linked list
	}
	else if (CFileOperation::CheckPath(diskPath) == PATH_IS_FILE) //path is file
	{
		ShellExecute(NULL, NULL, diskPath, NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		return;
	}
}

//Popup menu open on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeOpen()
{
	int uSelectedCount = shell_tree.GetSelectedCount();
	if(uSelectedCount <= 0)
	{
		return;
	}
	CString itemPath;
	shell_tree.GetItemPath(itemPath, 0);
	shell_tree.Refresh();
	shell_tree.SelectPath(itemPath);
	shell_list.DisplayFolder(itemPath);
	combo_box_path.AddString(itemPath);
	combo_box_path.SetWindowTextW(itemPath);
	AddListPath(itemPath); //add to linked list
}

//Popup menu cut on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeCut()
{
	CString itemPath;
	int uSelectedCount = shell_tree.GetSelectedCount();
	shell_tree.GetItemPath(itemPath);
	if (uSelectedCount == 1)
	{
		modifyInfo.IsCut = MODIFY_CUT;
		modifyInfo.IsCopy = MODIFY_NONE;
		modifyInfo.IsPaste = MODIFY_PASTE;
		modifyInfo.src_path_.clear();
		modifyInfo.src_path_.push_back(itemPath);
	}
}

//Popup menu on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeCopy()
{
	CString itemPath;
	int uSelectedCount = shell_tree.GetSelectedCount();
	shell_tree.GetItemPath(itemPath);
	if (uSelectedCount == 1)
	{
		modifyInfo.IsCopy = MODIFY_COPY;
		modifyInfo.IsCut = MODIFY_NONE;
		modifyInfo.IsPaste = MODIFY_PASTE;
		modifyInfo.src_path_.clear();
		modifyInfo.src_path_.push_back(itemPath);
	}
}

//Popup menu paste on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreePaste()
{
	CString diskPath;
	CString itemName;
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();
	HTREEITEM parentItem = shell_tree.GetParentItem(hmyItem);
	shell_tree.GetItemPath(diskPath, 0);
	itemName = shell_tree.GetItemText(hmyItem);
	if (modifyInfo.IsCopy == MODIFY_COPY)
	{
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = diskPath;
			fo.Copy(sSource, sDest);
		}
	}
	if (modifyInfo.IsCut == MODIFY_CUT)
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = diskPath;
			fo.Copy(sSource, sDest);
			if (!fo.Delete(modifyInfo.src_path_[i])) // delete src
			{
				fo.ShowError(); // if copy fails show error message
			}
			CString comboboxPath;
			combo_box_path.GetWindowTextW(comboboxPath);
			if (comboboxPath == modifyInfo.src_path_[i]) //neu cut duong dan giong voi combobox
			{
				shell_tree.GetItemPath(comboboxPath, hmyItem);
				combo_box_path.SetWindowTextW(comboboxPath);
				shell_list.DisplayFolder(comboboxPath);
			}
		}
		modifyInfo.src_path_.clear();
		shell_list.Refresh(); //refresh listview
	}
	shell_tree.Refresh();
	shell_tree.SelectPath(diskPath);
}

//Popup menu delete on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeDelete()
{
	int uSelectedCount = shell_tree.GetSelectedCount();
	if(uSelectedCount == 0)
	{
		return;
	}
	CString diskPath;
	CString itemName;
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();
	HTREEITEM parentItem = shell_tree.GetParentItem(hmyItem);
	shell_tree.GetItemPath(diskPath, 0);
	itemName = shell_tree.GetItemText(hmyItem);

	if (IDYES == MessageBox(_T("Are you sure you want to delete '" + itemName + _T("' folder?")),_T("Delete Folder"), MB_ICONWARNING | MB_YESNO))
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		CFileOperation fo;
		fo.Delete(diskPath);
		CString comboboxPath;
		combo_box_path.GetWindowTextW(comboboxPath);
		if (comboboxPath == diskPath) //neu xoa duong dan giong voi combobox
		{
			shell_tree.GetItemPath(comboboxPath, parentItem);
			combo_box_path.SetWindowTextW(comboboxPath);
			shell_list.DisplayFolder(comboboxPath);
		}
		shell_tree.DeleteItem(hmyItem);
		shell_list.Refresh();
		if (current->next != NULL && diskPath == current->next->list_path) //update linkedlist
		{
			struct List_path* temp = current->next;
			current->next = NULL;
			delete temp;
		}
	}
}

//Popup menu rename on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeRename()
{
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();
	shell_tree.EditLabel(hmyItem);
}

//Popup menu properties on treeview
void CFileExplorer_Group1Dlg::OnPopupMenuTreeProperties()
{
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();

	if ((hmyItem != NULL))
	{
		shell_tree.GetItemPath(urlInfo.g_path, hmyItem);
		urlInfo.g_name = shell_tree.GetItemText(hmyItem);
		CFileOperation fo;
		urlInfo.g_type.Format(_T("Folder"));

		fo.Size(urlInfo.g_path); //size
		ULONGLONG dwLength = fo.m_sizeFile;
		sizeFile = fo.m_sizeFile;
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
		PropertiesDlg propertiesDlg;
		propertiesDlg.DoModal();
	}
}

//Click on treeview and display on listview
void CFileExplorer_Group1Dlg::OnNMClickMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	modifyInfo.IsItemListClick = MODIFY_NONE;
	CString diskPath;
	UINT uFlags;
	CPoint point(::GetMessagePos());
	shell_tree.ScreenToClient(&point);
	HTREEITEM hItem = shell_tree.HitTest(point, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM &uFlags))
	{
		modifyInfo.IsItemTreeClick = MODIFY_ITEM_TREE_CLICK;
		shell_tree.GetItemPath(diskPath, hItem);
		if (diskPath != _T(""))
		{
			shell_list.DeleteAllItems();
			shell_list.DisplayFolder(diskPath);
			combo_box_path.InsertString(0, diskPath);
			combo_box_path.SetWindowTextW(diskPath);

			AddListPath(diskPath);
			CountItem(shell_list, count_item);
		}
	}
	*pResult = 0;
}

// Open on menu file
void CFileExplorer_Group1Dlg::OnMenuFileOpen()
{
	OnPopupMenuListOpen();
}

// Delete on menu file
void CFileExplorer_Group1Dlg::OnMenuFileDelete()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListDelete();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreeDelete();
	}
}

// Rename on menu file
void CFileExplorer_Group1Dlg::OnMenuFileRename()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListRename();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreeRename();
	}	
}

// Properties on menu file 
void CFileExplorer_Group1Dlg::OnMenuFileProperties()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListProperties();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreeProperties();
	}
}

// Close dialog on menu file
void CFileExplorer_Group1Dlg::OnMenuFileClose()
{
	EndDialog(0);
}

// Cut on menu edit
void CFileExplorer_Group1Dlg::OnMenuEditCut()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListCut();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreeCut();
	}	
}

// Copy on menu edit
void CFileExplorer_Group1Dlg::OnMenuEditCopy()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListCopy();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreeCopy();
	}
}

// Paste on menu edit
void CFileExplorer_Group1Dlg::OnMenuEditPaste()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnPopupMenuListPaste();
	}
	else if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		OnPopupMenuTreePaste();
	}
}

//ShortKey: Ctrl C, Ctrl V, Ctrl X, Delete, Backspase on listview
void CFileExplorer_Group1Dlg::OnLvnKeydownMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	switch (pLVKeyDow->wVKey)
	{
	case VK_BACK: //back button
		OnBnClickedButtonBack();
		break;
	case VK_DELETE: //only delete on listview
		if (shell_list.GetSelectedCount() > 0)
		{
			OnPopupMenuListDelete();
		}
		break;
	case 'O':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuListOpen();
		}
		break;
	case 'X':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuListCut();
		}
		break;
	case 'C':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuListCopy();
		}
		break;
	case 'V':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuListPaste();
		}
		break;
	case VK_F2:
		if (shell_list.GetSelectedCount() == 1)
			OnPopupMenuListRename();
		break;
	case VK_F5:
		OnPopupMenuListRefresh();
		break;
	}
	*pResult = 0;
}

// End edit item on listview when rename or create new file or folder 
void CFileExplorer_Group1Dlg::OnLvnEndlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	wchar_t *pText = pDispInfo->item.pszText; //get current item text after change

	CString oldPath; //full path from disk
	CString parentPath; //path get from UI
	CString oldName; //name get from UI
	CString uiPath; //itemPath + "\\" + itemName
	CString newPath;
	CString extensionFile = L""; //extension of file
	int nItem = shell_list.GetNextItem(-1, LVNI_SELECTED); //get select item index
	shell_list.GetItemPath(oldPath, nItem); //get select item path on disk
	shell_list.GetCurrentFolder(parentPath); //get parent folder path of item
	oldName = shell_list.GetItemText(nItem, 0); //get item path from UI
	
	if (parentPath.Right(1) == "\\")
	{
		uiPath = parentPath + oldName;
	}
	else
	{
		uiPath = parentPath + L"\\" + oldName;
	}

	if (CFileOperation::CheckPath(oldPath) == PATH_IS_FILE) //if item is file will get extension of file
	{
		if(oldPath > uiPath) //file have extension, will get extension of file
		{
			int i = 0;
			int oldPathLength = oldPath.GetLength();
			int uiPathLength = uiPath.GetLength();
			extensionFile = oldPath.Right(oldPathLength - uiPathLength);
		}
	}

	if (pText != NULL) //if item text change
	{
		if (pText[0] != '\0') //if item text not is ""
		{
			CFileOperation fo;
			if (parentPath.Right(1) == "\\")
			{
				newPath = parentPath + pText;
			}
			else
			{
				newPath = parentPath + L"\\" + pText;
			}

			if (CFileOperation::CheckPath(oldPath) == PATH_IS_FOLDER) //path is folder
			{
				fo.Rename(oldPath, newPath); //rename
				shell_list.Refresh();
				shell_tree.Refresh();
				CString comboboxPath;
				combo_box_path.GetWindowTextW(comboboxPath);
				shell_tree.SelectPath(comboboxPath);
			}
			else if (CFileOperation::CheckPath(oldPath) == PATH_IS_FILE)
			{
				fo.Rename(oldPath, newPath + extensionFile); //rename
				shell_list.Refresh();
			}
			else
			{
				return;
			}
		}
	}
	*pResult = 0;
}

//Search item on edit box
void CFileExplorer_Group1Dlg::OnEnChangeEditSearch()
{
	CString path;
	combo_box_path.GetWindowTextW(path);
	shell_list.DisplayFolder(path);
	CString str;
	edit_search.GetWindowTextW(str);
	CAtlString item_name;
	if (str == _T(""))
	{
		shell_list.DisplayFolder(path);
	}
	else
	{
		int count = shell_list.GetItemCount();
		int nIndex;
		for (int i = 0; i < count; i++)
		{
			item_name = shell_list.GetItemText(i, 0);
			item_name.MakeUpper();
			nIndex = item_name.Find(str.MakeUpper(), 0);
			if (nIndex == -1)
			{
				shell_list.DeleteItem(i);
				i--;
				count--;
			}
		}
	}
	CountItem(shell_list, count_item);
}

//Check left click item on listview
void CFileExplorer_Group1Dlg::OnNMClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modifyInfo.IsItemListClick = MODIFY_NONE;
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	if (pNMItemActivate->iItem != -1) //check current is left click
	{
		modifyInfo.IsItemListClick = MODIFY_ITEM_LIST_CLICK;
	}
	*pResult = 0;
}

//Check right click item on listview
void CFileExplorer_Group1Dlg::OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modifyInfo.IsItemListClick = MODIFY_NONE;
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	if (pNMItemActivate->iItem != -1) //check current is right click
	{
		modifyInfo.IsItemListClick = MODIFY_ITEM_LIST_CLICK;
	}
	*pResult = 0;
}

//overide OnOK()
void CFileExplorer_Group1Dlg::OnOK()
{
	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		OnMenuFileOpen();
	}
}

// End edit item on treeview when rename or create new folder 
void CFileExplorer_Group1Dlg::OnTvnEndlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	CString oldPath; //full path of current item	
	CString oldName; //current name
	CString parentPath; //parent path of current item
	CString newPath; //new path
	wchar_t *pText = pTVDispInfo->item.pszText;
	if (pText != NULL)
	{
		if (pText[0] != '\0')
		{
			HTREEITEM hmyItem = shell_tree.GetSelectedItem();
			HTREEITEM parentItem = shell_tree.GetParentItem(hmyItem);
			shell_tree.GetItemPath(oldPath, hmyItem);
			shell_tree.GetItemPath(parentPath, parentItem);
			oldName = shell_tree.GetItemText(hmyItem);
			if (parentPath.Right(1) == "\\")
			{
				newPath = parentPath + pText;
			}
			else
			{
				newPath = parentPath + L"\\" + pText;
			}
			CFileOperation fo;
			fo.Rename(oldPath, newPath); //rename
			shell_tree.Refresh(); //refresh
			shell_tree.SelectPath(newPath);
			CString comboboxPath;
			combo_box_path.GetWindowTextW(comboboxPath);
			if (oldPath == comboboxPath) //if current item on shelltree rename and display on shell list
			{
				combo_box_path.AddString(newPath); //update combobox
				combo_box_path.SetWindowTextW(newPath);
				shell_list.DisplayFolder(newPath); //update shell list
				AddListPath(newPath); //them vao danh sach lien ket
			}
			if (parentPath == comboboxPath) //if current item of parent on combobox
			{
				shell_list.Refresh(); //update shell  list
			}
			CountItem(shell_list, count_item);
		}	
	}
	*pResult = 0;
}

//Short key on tree (Delete, Ctrl+O, Ctrl+X, Ctrl+C, Ctrl+V, F2)
void CFileExplorer_Group1Dlg::OnTvnKeydownMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	switch (pTVKeyDown->wVKey)
	{
	case VK_DELETE:
		OnPopupMenuTreeDelete();
		break;
	case 'O':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuTreeOpen();
		}
		break;
	case 'X':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuTreeCut();
		}
		break;
	case 'C':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuTreeCopy();
		}
		break;
	case 'V':
		if (GetKeyState(VK_CONTROL) < 0)
		{
			OnPopupMenuTreePaste();
		}
		break;
	case VK_F2:
		OnPopupMenuTreeRename();
		break;
	}
	*pResult = 0;
}

//Auto Resizing status bar
void CFileExplorer_Group1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_TIME);
}

//Auto update status bar after 2ms
void CFileExplorer_Group1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 2)
	{
		//update time
		CTime t1;
		t1 = CTime::GetCurrentTime();
		m_bar.SetPaneText(1, t1.Format("%H:%M:%S"));
		//Update items
		CString s;
		int iTems = shell_list.GetItemCount();
		s.Format(L"%d items", iTems);
		m_bar.SetPaneText(0, s);
	}
	CDialog::OnTimer(nIDEvent);
}

//Check Item select change on tree
void CFileExplorer_Group1Dlg::OnTvnSelchangingMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	modifyInfo.IsItemListClick = MODIFY_NONE;
	UINT uFlags;
	CPoint point(::GetMessagePos());
	shell_tree.ScreenToClient(&point);
	HTREEITEM hItem = shell_tree.HitTest(point, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM &uFlags))
	{
		modifyInfo.IsItemTreeClick = MODIFY_ITEM_TREE_CLICK;
	}
	*pResult = 0;
}
