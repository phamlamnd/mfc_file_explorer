
// FileExplorer_Group1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileExplorer_Group1.h"
#include "FileExplorer_Group1Dlg.h"
#include "afxdialogex.h"
#include "Create_New_Folder.h"
#include "Create_Text_File.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_NISH,
	ID_INDICATOR_TIME
};

//Define Current file and folder properties
CurrentUrlInfo urlInfo;
ModifyInfo modifyInfo;
// Creat List path
struct List_path
{
	CString list_path;
	List_path * next;
	List_path * prev;
};

struct List_path * current;

//Add path to list funcion
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

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileExplorer_Group1Dlg dialog



CFileExplorer_Group1Dlg::CFileExplorer_Group1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILEEXPLORER_GROUP1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

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
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnBeginlabeleditMfcshelllist1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnEndlabeleditMfcshelllist1)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CFileExplorer_Group1Dlg::OnEnChangeEditSearch)
	ON_NOTIFY(NM_RCLICK, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnNMRClickMfcshelllist1)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnLvnItemActivateMfcshelllist1)
	ON_NOTIFY(NM_CLICK, IDC_MFCSHELLLIST1, &CFileExplorer_Group1Dlg::OnNMClickMfcshelllist1)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnBeginlabeleditMfcshelltree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnEndlabeleditMfcshelltree1)
	ON_NOTIFY(TVN_KEYDOWN, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnKeydownMfcshelltree1)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_NOTIFY(TVN_SELCHANGING, IDC_MFCSHELLTREE1, &CFileExplorer_Group1Dlg::OnTvnSelchangingMfcshelltree1)
END_MESSAGE_MAP()


// CFileExplorer_Group1Dlg message handlers
BOOL CFileExplorer_Group1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	HICON hIcon2 = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2));
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	button_back.SetIcon(hIcon);
	button_foward.SetIcon(hIcon2);

	// TODO: Add extra initialization here
	HTREEITEM hParent = shell_tree.GetRootItem();
	shell_tree.Expand(hParent, TVE_EXPAND);
	//	shell_list.DeleteAllItems();
	shell_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_INFOTIP | LVS_EX_HEADERDRAGDROP | LVS_EX_BORDERSELECT*/);
	combo_box_view.AddString(_T("Tiles"));
	combo_box_view.AddString(_T("Icons"));
	combo_box_view.AddString(_T("List"));
	combo_box_view.AddString(_T("Details"));
	combo_box_view.SetCurSel(0);

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

void CFileExplorer_Group1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
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

//ShellList Right click menu
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

	//Hide Popup menu
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PASTE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_RENAME, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_CUT, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_COPY, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PASTE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_DELETE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_RENAME, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

	if (modifyInfo.IsItemListClick == MODIFY_ITEM_LIST_CLICK)
	{
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_CUT, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_COPY, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_DELETE, MF_BYCOMMAND | MF_ENABLED);
		if (shell_list.GetSelectedCount() == 1)
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_RENAME, MF_BYCOMMAND | MF_ENABLED);
	}
	if (modifyInfo.IsItemListClick == MODIFY_NONE)
	{
		if (modifyInfo.IsPaste == MODIFY_PASTE)
		{
			mnuPopupMenu1->EnableMenuItem(ID_POPUP_MENU_PASTE, MF_BYCOMMAND | MF_ENABLED);
		}
	}
	if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
	{
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_CUT, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_COPY, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_DELETE, MF_BYCOMMAND | MF_ENABLED);
		mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_RENAME, MF_BYCOMMAND | MF_ENABLED);
		if (modifyInfo.IsPaste == MODIFY_PASTE)
		{
			mnuPopupMenu2->EnableMenuItem(ID_POPUP_MENU_TREE_PASTE, MF_BYCOMMAND | MF_ENABLED);
		}

	}

	ASSERT(mnuPopupMenu1);
	ASSERT(mnuPopupMenu2);
	//Find out if the user right-clicked the button
	//because we are interesed only in the button
	if (rectListView.PtInRect(point))
		mnuPopupMenu1->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	if (rectTreeView.PtInRect(point))
		mnuPopupMenu2->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


ULONGLONG DoGetSize(CString sPathName);
void GetSize(CString sPathName);
ULONGLONG sizeFile = 0;
bool check_Thread = false;
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
	while (bWorking && !check_Thread)
	{
		bWorking = finder.FindNextFile();

		// skip . and .. files; otherwise, we'd
		// recur infinitely!
		if (finder.IsDots())
			continue;
		// if it's a directory, recursively search it
		CString str = finder.GetFilePath();
		if (finder.IsDirectory())
		{
			GetSize(str);
		}
		else
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
		//pEx->ReportError();
		pEx->Delete();
	}
	catch (CMemoryException* pEx)
	{
		//pEx->ReportError();
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
	check_Thread = false;
	int index = shell_list.GetNextItem(-1, LVNI_SELECTED);
	if (index != -1)
	{
		CFileOperation fo;
		urlInfo.g_name = shell_list.GetItemText(index, 0); //name
		shell_list.GetItemPath(urlInfo.g_path, index);
		if (fo.CheckPath(urlInfo.g_path) == PATH_IS_FILE) //type
		{
			urlInfo.g_type.Format(_T("File"));
		}
		else if (fo.CheckPath(urlInfo.g_path) == PATH_IS_FOLDER)
		{
			urlInfo.g_type.Format(_T("Folder"));
		}

		//fo.Size(urlInfo.g_path); //size
		std::thread thr = std::thread(GetSize, urlInfo.g_path);
		thr.detach();
		ULONGLONG dwLength = sizeFile /*fo.m_sizeFile*/;
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
		INT_PTR nResponse = propertiesDlg.DoModal();
		check_Thread = true;
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
	CString name, path;
	//	shell_list.GetCurrentFolderName(name);
	shell_list.GetCurrentFolder(path);
	combo_box_path.AddString(path);
	combo_box_path.SetWindowTextW(path);
	AddListPath(path);//them vao danh sach lien ket
	CountItem(shell_list, count_item);
	*pResult = 0;
}

// CREATE NEW FOLDER IN HERE//////////////////////////////////////////////////////
void CFileExplorer_Group1Dlg::OnMenuFileNewFloder()
{
	// TODO: Add your command handler code here
	Create_New_Folder namefolder;
	namefolder.DoModal();
	UpdateData(TRUE);
	CString path;
	CString newname;
	newname = namefolder.newname;
	//	combination path and new name to create new folder.
	combo_box_path.GetWindowTextW(path);
	//shell_tree.GetItemPath(g_path);
	//	AfxMessageBox(path);
	path += _T('\\');
	path += newname;
	//	path += _T('\\');
	//	AfxMessageBox(path);
	if (!CreateDirectory(path, NULL))
	{
		AfxMessageBox(_T("Unable to create directory"));
	}
	else
	{
		MessageBox(_T("Created! ^^ "));
	}
	UpdateData(FALSE);
	shell_tree.Refresh();
	shell_list.Refresh();
}

//CREATE NEW TEXT FILE//////////////////////////////////////////////////////
void CFileExplorer_Group1Dlg::OnMenuFileNewTextdocument()
{
	// TODO: Add your command handler code here
	Create_Text_File namefolder;
	namefolder.DoModal();
	UpdateData(TRUE);
	CString path;
	CString newname;
	newname = namefolder.newname;
	combo_box_path.GetWindowTextW(path);
	path += _T('\\');
	path += newname;
	path += _T(".txt");
	//	path += _T('\\');
	//CFile cfile_object(_T("path"), CFile::modeCreate | CFile::modeReadWrite);
	CFile cfile_object;
	if (!cfile_object.Open(path, CFile::modeCreate | CFile::modeReadWrite))
	{
		AfxMessageBox(_T("Unable to create text file"));
	}
	else
		MessageBox(_T("Created! ^^ "));
	UpdateData(FALSE);
	//shell_list.DisplayFolder(g_path);
	shell_tree.Refresh();
	shell_list.Refresh();
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

//Button go
void CFileExplorer_Group1Dlg::OnBnClickedGo()
{
	CString cb_path;
	combo_box_path.GetWindowTextW(cb_path);
	shell_list.DisplayFolder(cb_path);
	AddListPath(cb_path);
	CountItem(shell_list, count_item);
}

//button back
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
	//	else
	//		shell_list.DeleteAllItems();
}

//button foward
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

//Popup menu cut
void CFileExplorer_Group1Dlg::OnPopupMenuListCut()
{
	modifyInfo.IsCut = MODIFY_CUT;
	modifyInfo.IsCopy = MODIFY_NONE;
	modifyInfo.IsPaste = MODIFY_PASTE;
	CString path, name;
	int uSelectedCount = shell_list.GetSelectedCount();
	int  nItem = -1;
	modifyInfo.src_path_.clear();
	modifyInfo.src_name_.clear();
	if (uSelectedCount > 0)
		for (int index = 0; index < uSelectedCount; index++)
		{
			nItem = shell_list.GetNextItem(nItem, LVNI_SELECTED);
			shell_list.GetItemPath(path, nItem);
			modifyInfo.src_path_.push_back(path);
		}
}

//Popup menu copy
void CFileExplorer_Group1Dlg::OnPopupMenuListCopy()
{
	modifyInfo.IsCopy = MODIFY_COPY;
	modifyInfo.IsCut = MODIFY_NONE;
	modifyInfo.IsPaste = MODIFY_PASTE;
	CString path, name;
	int uSelectedCount = shell_list.GetSelectedCount();
	int  nItem = -1;
	modifyInfo.src_path_.clear();
	modifyInfo.src_name_.clear();
	if (uSelectedCount > 0)
		for (int index = 0; index < uSelectedCount; index++)
		{
			nItem = shell_list.GetNextItem(nItem, LVNI_SELECTED);
			shell_list.GetItemPath(path, nItem);
			modifyInfo.src_path_.push_back(path);
		}
}

//Popup menu paste
void CFileExplorer_Group1Dlg::OnPopupMenuListPaste()
{
	CString current_path;
	combo_box_path.GetWindowTextW(current_path);
	if (modifyInfo.IsCopy == MODIFY_COPY)
	{
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = current_path;
			fo.Copy(sSource, sDest);
		}

		shell_list.Refresh();
	}
	if (modifyInfo.IsCut == MODIFY_CUT)
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = current_path;
			fo.Copy(sSource, sDest);
			if (!fo.Delete(sSource)) // delete src
			{
				fo.ShowError(); // if copy fails show error message
			}
		}
		shell_list.Refresh();
		if (modifyInfo.IsItemTreeClick == MODIFY_ITEM_TREE_CLICK)
		{
			HTREEITEM hmyItem = shell_tree.GetSelectedItem();
			shell_tree.DeleteItem(hmyItem);
		}
	}
}

//Popup menu delete
void CFileExplorer_Group1Dlg::OnPopupMenuListDelete()
{
	CString name, path;
	if (IDOK == MessageBox(_T("Do you want to delete?"),
		_T("Confirm Delete"), MB_ICONWARNING | MB_OKCANCEL))
	{
		modifyInfo.IsPaste = MODIFY_NONE;
		int uSelectedCount = shell_list.GetSelectedCount();
		int  nItem;
		if (uSelectedCount > 0)
		{
			for (int index = 0; index < uSelectedCount; index++)
			{
				nItem = shell_list.GetNextItem(-1, LVNI_SELECTED);
				shell_list.GetItemPath(path, nItem);
				if (current != NULL && current->next != NULL && path == current->next->list_path)
				{
					struct List_path* temp = current->next;
					current->next = NULL;
					delete temp;
				}
				CFileOperation fo;
				fo.Delete(path);  //delete on disk
				shell_list.DeleteItem(nItem); //delete shell list
			}
			shell_tree.Refresh();
			CString current_path;
			combo_box_path.GetWindowTextW(current_path);
			shell_tree.SelectPath(current_path);
		}
	}
}

//Popup menu rename
void CFileExplorer_Group1Dlg::OnPopupMenuListRename()
{
	int index = shell_list.GetSelectionMark();
	shell_list.EditLabel(index);
}

//Popup menu new folder
bool check = false;
void CFileExplorer_Group1Dlg::OnPopupMenuListNewFolder()
{
	check = true;
	CString path;
	shell_list.GetCurrentFolder(path);
	CString newFolder = L"\\New folder";
	int i = 0;
	while (true)
	{
		if (CreateDirectoryW(path + newFolder, NULL))
		{
			break;
		}
		i++;
		newFolder.Format(L"\\New folder (%d)", i + 1);
	}
	shell_list.Refresh();
	LVFINDINFO info;
	info.flags = LVFI_PARTIAL | LVFI_STRING;
	info.psz = _T("New folder");
	int Index = shell_list.FindItem(&info) + i;
	shell_list.EditLabel(Index);

	shell_tree.Refresh();
	CString current_path;
	combo_box_path.GetWindowTextW(current_path);
	shell_tree.SelectPath(current_path);
}

//popup menu new text document
void CFileExplorer_Group1Dlg::OnPopupMenuListNewTextdocument()
{
	CString path;
	shell_list.GetCurrentFolder(path);
	int i = 0;
	CString newFile = L"\\New Text Document.txt";
	while (true)
	{
		CFile cfile_object;
		if ((GetFileAttributes(path + newFile) == INVALID_FILE_ATTRIBUTES))
		{
			cfile_object.Open(path + newFile, CFile::modeReadWrite | CFile::modeCreate);
			break;
		}
		i++;
		newFile.Format(L"\\New Text Document (%d).txt", i + 1);
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
		int Index = shell_list.FindItem(&info) + i - 1;
		shell_list.EditLabel(Index);
	}
}

//Popup menu shelltree open
void CFileExplorer_Group1Dlg::OnPopupMenuListOpen()
{
	OnMenuFileOpen();
}

//Popup menu shelltree open
void CFileExplorer_Group1Dlg::OnPopupMenuTreeOpen()
{
	CString path;
	shell_tree.GetItemPath(path, 0);
	shell_list.DeleteAllItems();
	shell_list.DisplayFolder(path);
	combo_box_path.SetWindowTextW(path);
	AddListPath(path);//them vao danh sach lien ket
}

//Popup menu shelltree cut
void CFileExplorer_Group1Dlg::OnPopupMenuTreeCut()
{
	CString path, name;
	int uSelectedCount = shell_tree.GetSelectedCount();
	shell_tree.GetItemPath(path);
	if (uSelectedCount == 1)
	{
		modifyInfo.IsCut = MODIFY_CUT;
		modifyInfo.IsCopy = MODIFY_NONE;
		modifyInfo.IsPaste = MODIFY_PASTE;
		modifyInfo.src_path_.clear();
		modifyInfo.src_path_.push_back(path);
	}
}

//Popup menu shelltree copy
void CFileExplorer_Group1Dlg::OnPopupMenuTreeCopy()
{
	CString path, name;
	int uSelectedCount = shell_tree.GetSelectedCount();
	shell_tree.GetItemPath(path);
	name = L"";
	if (uSelectedCount == 1)
	{
		modifyInfo.IsCopy = MODIFY_COPY;
		modifyInfo.IsCut = MODIFY_NONE;
		modifyInfo.IsPaste = MODIFY_PASTE;
		modifyInfo.src_path_.clear();
		modifyInfo.src_name_.clear();
		modifyInfo.src_path_.push_back(path);
		modifyInfo.src_name_.push_back(name);
	}
}

//Popup menu shelltree paste
void CFileExplorer_Group1Dlg::OnPopupMenuTreePaste()
{
	CString current_path;
	shell_tree.GetItemPath(current_path, 0);
	if (modifyInfo.IsCopy == MODIFY_COPY)
	{
		CFileOperation fo;
		size_t itemCount = modifyInfo.src_path_.size();
		for (size_t i = 0; i < itemCount; i++)
		{
			CString sSource = modifyInfo.src_path_[i];
			CString sDest = current_path;
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
			CString sDest = current_path;
			fo.Copy(sSource, sDest);
			if (!fo.Delete(modifyInfo.src_path_[i])) // delete src
			{
				fo.ShowError(); // if copy fails show error message
			}
		}
	}
	HTREEITEM hmyItem = shell_tree.GetParentItem(shell_tree.GetSelectedItem());
	shell_tree.Expand(hmyItem, TVE_COLLAPSE);
	shell_tree.Expand(hmyItem, TVE_EXPAND);
}

//Popup menu shelltree delete
void CFileExplorer_Group1Dlg::OnPopupMenuTreeDelete()
{
	CString treePath;
	shell_tree.GetItemPath(treePath, 0);
	if (IDOK == MessageBox(_T("Do you want to delete?"),
		_T("Delete folder"), MB_ICONWARNING | MB_OKCANCEL))
	{
		CFileOperation fo;
		MessageBox(treePath);
		fo.Delete(treePath);
		HTREEITEM hmyItem = shell_tree.GetSelectedItem();
		HTREEITEM parentItem = shell_tree.GetParentItem(shell_tree.GetSelectedItem());
		CString comboboxPath;
		combo_box_path.GetWindowTextW(comboboxPath);
		if (comboboxPath == treePath) //neu xoa duong dan giong voi combobox
		{
			shell_tree.GetItemPath(comboboxPath, parentItem);
			combo_box_path.AddString(comboboxPath);
			combo_box_path.SetCurSel(0);
			shell_list.DisplayFolder(comboboxPath);
		}
		shell_tree.DeleteItem(hmyItem);
		shell_list.Refresh();
		//if (current->next != NULL && path == current->next->list_path) //update linkedlist
		//{
		//	struct List_path* temp = current->next;
		//	current->next = NULL;
		//	delete temp;
		//}
	}
}

//Popup menu shelltree open
void CFileExplorer_Group1Dlg::OnPopupMenuTreeRename()
{
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();
	shell_tree.EditLabel(hmyItem);
}

//Popup menu shelltree open
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

//Click on shell tree and display on shell list
void CFileExplorer_Group1Dlg::OnNMClickMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	modifyInfo.IsCopy = MODIFY_NONE;
	modifyInfo.IsCut = MODIFY_NONE;
	CString path;
	UINT uFlags;
	CPoint point(::GetMessagePos());
	shell_tree.ScreenToClient(&point);
	HTREEITEM hItem = shell_tree.HitTest(point, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM &uFlags))
	{
		modifyInfo.IsItemTreeClick = MODIFY_ITEM_TREE_CLICK;
		modifyInfo.IsItemListClick = MODIFY_NONE;
		modifyInfo.IsCopy = MODIFY_COPY;
		modifyInfo.IsCut = MODIFY_CUT;
		shell_tree.GetItemPath(path, hItem);
		if (path != _T(""))
		{
			shell_list.DeleteAllItems();
			shell_list.DisplayFolder(path);
			combo_box_path.InsertString(0, path);
			combo_box_path.SetCurSel(0);

			AddListPath(path);
			CountItem(shell_list, count_item);
		}
	}
	*pResult = 0;
}

// OPEN IN MENU IN HERE //////////////////////////////////////////
void CFileExplorer_Group1Dlg::OnMenuFileOpen()
{
	CString path1;
	CString temp1;
	CString nameFromClick;
	shell_list.GetCurrentFolder(path1);
	int len = path1.GetLength();

	if (len != 0)
	{
		int index = shell_list.GetNextItem(-1, LVNI_SELECTED);
		nameFromClick = shell_list.GetItemText(index, 0);
		if (path1[len - 1] == '\\')
		{
			for (int i = 0; i < len - 1; i++)
			{
				temp1 += path1[i];
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				temp1 += path1[i];
			}
		}
		temp1 = temp1 + CString("\\") + nameFromClick;
		CFileOperation fo;
		int a = fo.CheckPath(temp1);
		if (len == 0)
		{
			temp1 = _T("C:\\");
			//	path1 += _T('\\');
			combo_box_path.SetWindowTextW(temp1);
			shell_list.DisplayFolder(temp1);
		}
		else
		{
			if (fo.CheckPath(temp1) == 2)
			{
				combo_box_path.SetWindowTextW(temp1);
				shell_list.DisplayFolder(temp1);
			}
			else
			{
				combo_box_path.SetWindowTextW(path1);
				ShellExecute(NULL, NULL, temp1, NULL, NULL, SW_SHOWNORMAL);
			}
		}
	}
}


// DELETE IN MENU IN HERE///////////////////////////
void CFileExplorer_Group1Dlg::OnMenuFileDelete()
{
	OnPopupMenuListDelete();
}


// Menu to rename
void CFileExplorer_Group1Dlg::OnMenuFileRename()
{
	OnPopupMenuListRename();
}

// MENU to properties
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

//Menu to close application
void CFileExplorer_Group1Dlg::OnMenuFileClose()
{
	EndDialog(0);
}

//Menu cut
void CFileExplorer_Group1Dlg::OnMenuEditCut()
{
	OnPopupMenuListCut();
}

//Menu copy
void CFileExplorer_Group1Dlg::OnMenuEditCopy()
{
	OnPopupMenuListCopy();
}

//Menu Paste
void CFileExplorer_Group1Dlg::OnMenuEditPaste()
{
	OnPopupMenuListPaste();
}

//ShortKey: Ctrl C, Ctrl V, Ctrl X, Delete, Backspase
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

//begin edit item on shell list
void CFileExplorer_Group1Dlg::OnLvnBeginlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	combo_box_path.GetWindowTextW(modifyInfo.src_path);
	int index = shell_list.GetNextItem(-1, LVNI_SELECTED);
	modifyInfo.src_name = shell_list.GetItemText(index, 0);
	*pResult = 0;
}

//end edit item on shell list
void CFileExplorer_Group1Dlg::OnLvnEndlabeleditMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	int index = shell_list.GetSelectionMark();
	CString strName = pDispInfo->item.pszText;
	CFileOperation fo;
	fo.Rename(modifyInfo.src_path + L"\\" + modifyInfo.src_name, modifyInfo.src_path + L"\\" + pDispInfo->item.pszText);
	shell_list.SetItemText(index, 0, pDispInfo->item.pszText);
	shell_list.Refresh();
	shell_tree.Refresh();
	CString current_path;
	combo_box_path.GetWindowTextW(current_path);
	shell_tree.SelectPath(current_path);
	*pResult = 0;
}

//Search 
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


//Check left click item on shell list
void CFileExplorer_Group1Dlg::OnNMClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modifyInfo.IsItemListClick = MODIFY_NONE;
	int x = pNMItemActivate->iItem;
	if (pNMItemActivate->iItem != -1) //check current is left click
	{
		modifyInfo.IsItemListClick = MODIFY_ITEM_LIST_CLICK;
	}
	*pResult = 0;
}

//Check right click item on shell list
void CFileExplorer_Group1Dlg::OnNMRClickMfcshelllist1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	modifyInfo.IsItemListClick = MODIFY_NONE;
	int x = pNMItemActivate->iItem;
	if (pNMItemActivate->iItem != -1) //check current is right click
	{
		modifyInfo.IsItemListClick = MODIFY_ITEM_LIST_CLICK;
		modifyInfo.IsItemTreeClick = MODIFY_NONE;
	}
	*pResult = 0;
}


//begin change tree item
void CFileExplorer_Group1Dlg::OnTvnBeginlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	shell_tree.GetItemPath(modifyInfo.src_path);
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

//end change tree item
void CFileExplorer_Group1Dlg::OnTvnEndlabeleditMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	HTREEITEM hmyItem = shell_tree.GetSelectedItem();
	HTREEITEM parentItem = shell_tree.GetParentItem(hmyItem);
	if (pTVDispInfo->item.pszText != NULL)
		shell_tree.SetItemText(hmyItem, pTVDispInfo->item.pszText);
	CString current_path;
	shell_tree.GetItemPath(current_path, parentItem);
	CFileOperation fo;
	fo.Rename(modifyInfo.src_path, current_path + L"\\" + pTVDispInfo->item.pszText);
	//	if ((hmyItem != NULL) /*&& shell_tree.ItemHasChildren(hmyItem)*/)
	CountItem(shell_list, count_item);
	shell_tree.SelectItem(hmyItem);
	//shell_tree.Expand(parentItem, TVE_COLLAPSE);
	//shell_tree.Expand(parentItem, TVE_EXPAND);
	shell_tree.GetItemPath(current_path, parentItem);
	//combo_box_path.SetWindowTextW(current->list_path);
	shell_list.Refresh();
	*pResult = 0;
}

//Short key on tree
void CFileExplorer_Group1Dlg::OnTvnKeydownMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVKEYDOWN pTVKeyDown = reinterpret_cast<LPNMTVKEYDOWN>(pNMHDR);
	switch (pTVKeyDown->wVKey)
	{
	case VK_DELETE: //only delete on listview
		if (shell_list.GetSelectedCount() > 0)
		{
			OnPopupMenuTreeDelete();
		}
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
		if (shell_tree.GetSelectedCount() == 1)
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

//update status bar
void CFileExplorer_Group1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 2)
	{
		CTime t1;
		t1 = CTime::GetCurrentTime();
		m_bar.SetPaneText(1, t1.Format("%H:%M:%S"));
		//update status bar
		CRect rect;
		GetClientRect(&rect);
		//Size the two panes
		//m_bar.SetPaneInfo(0, ID_INDICATOR_NISH, SBPS_NORMAL, rect.Width() - 100);
		CString s;
		int iTems = shell_list.GetItemCount();
		s.Format(L"%d items", iTems);
		m_bar.SetPaneText(0, s);

	}
	CDialog::OnTimer(nIDEvent);
}

//check click on tree item
void CFileExplorer_Group1Dlg::OnTvnSelchangingMfcshelltree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	modifyInfo.IsItemTreeClick = MODIFY_NONE;
	UINT uFlags;
	CPoint point(::GetMessagePos());
	shell_tree.ScreenToClient(&point);
	HTREEITEM hItem = shell_tree.HitTest(point, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM &uFlags))
	{
		modifyInfo.IsItemTreeClick = MODIFY_ITEM_TREE_CLICK;
		modifyInfo.IsItemListClick = MODIFY_NONE;
	}
	*pResult = 0;
}
