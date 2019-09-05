
// Array1Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Array1.h"
#include "Array1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CArray1Dlg 对话框



CArray1Dlg::CArray1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARRAY1_DIALOG, pParent)
	, m_edit_text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArray1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_text);
}

BEGIN_MESSAGE_MAP(CArray1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CArray1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArray1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CArray1Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CArray1Dlg 消息处理程序

BOOL CArray1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CArray1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CArray1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CArray1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArray1Dlg::OnBnClickedButton1()
{
	CUIntArray arry;
	arry.SetSize(10);
	for (int i = 0; i < 10; ++i) {
		//arry.SetAt(i, (i + 1) *10);
		arry[i] = (i + 1) * 10;
	}

	m_edit_text.Empty();

	CString s;
	for (int i = 0; i < 10; ++i) {
		//s.Format(TEXT("%d"), arry.GetAt(i));
		s.Format(TEXT("%d"), arry[i]);
		m_edit_text.Append(s);
		m_edit_text.Append(TEXT("\r\n"));
	}
	// 将数据更新到文体框内
	UpdateData(FALSE);
}


void CArray1Dlg::OnBnClickedButton2()
{
	CStringArray a;
	a.SetSize(10);

	int nSize = a.GetSize();

	for (int i = 0; i < nSize; ++i) {
		CString s;
		s.Format(TEXT("Hello %d"), i);
		a[i] = s;
	}

	m_edit_text.Empty();

	for (int i = 0; i < nSize; ++i) {
		m_edit_text.Append(a[i]);
		m_edit_text.Append(TEXT("\r\n"));
	}

	UpdateData(FALSE);
}


void CArray1Dlg::OnBnClickedButton3()
{
	CUIntArray a;
	a.SetSize(9);
	for (int i = 0; i < 9; ++i) {
		a[i] = i + 1;
	}

	a.InsertAt(4, 50);

	int nSize = a.GetSize();

	m_edit_text.Empty();
	for (int i = 0; i < nSize; ++i) {
		CString s;
		s.Format(TEXT("%d"),a[i]);
		m_edit_text.Append(s);
		m_edit_text.Append(TEXT("\r\n"));
	}
	UpdateData(FALSE);
}
