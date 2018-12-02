// DragDropListCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DragDropListCtrlDemo.h"
#include "DragDropListCtrlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragDropListCtrlDemoDlg dialog

CDragDropListCtrlDemoDlg::CDragDropListCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDragDropListCtrlDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDragDropListCtrlDemoDlg)
	m_sItemData = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDragDropListCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDragDropListCtrlDemoDlg)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_ITEM_DATA, m_sItemData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDragDropListCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDragDropListCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragDropListCtrlDemoDlg message handlers

BOOL CDragDropListCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

	// Initialise list control with some data.
	m_List.InsertColumn(0, "Col0", LVCFMT_LEFT, 80);
	m_List.InsertColumn(1, "Col1", LVCFMT_LEFT, 80);
	m_List.InsertColumn(2, "Col2", LVCFMT_LEFT, 80);

	for (int nRow = 0; nRow < 100; nRow++)
	{
		for (int nCol = 0; nCol < 3; nCol++)
		{
			CString sText;
			sText.Format("Row %d, Col %d", nRow, nCol);
			if (nCol == 0)
			{
				m_List.InsertItem(nRow, sText);
				m_List.SetItemData(nRow, reinterpret_cast<DWORD>(new CString(sText)));
			}
			else
			{
				m_List.SetItemText(nRow, nCol, sText);
			}
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragDropListCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDragDropListCtrlDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDragDropListCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDragDropListCtrlDemoDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView && pNMListView->uOldState != pNMListView->uNewState)
	{
		if ((pNMListView->uNewState & LVIS_SELECTED) == LVIS_SELECTED)
		{
			CString* pString = reinterpret_cast<CString*>(m_List.GetItemData(pNMListView->iItem));

			if (pString)
			{
				m_sItemData = *pString;
				UpdateData(FALSE);
			}
		}
	}
	
	*pResult = 0;
}

void CDragDropListCtrlDemoDlg::OnDestroy() 
{
	for (int nItem = 0; nItem < m_List.GetItemCount(); nItem++)
	{
		CString* pString = reinterpret_cast<CString*>(m_List.GetItemData(nItem));
		delete pString;
	}	

	CDialog::OnDestroy();
}
