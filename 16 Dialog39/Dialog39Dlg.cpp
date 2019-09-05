
// Dialog39Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Dialog39.h"
#include "Dialog39Dlg.h"
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


// CDialog39Dlg 对话框



CDialog39Dlg::CDialog39Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG39_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialog39Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RED, m_chk_red);
	DDX_Control(pDX, IDC_CHECK_GREEN, m_chk_green);
	DDX_Control(pDX, IDC_CHECK_BLUE, m_chk_blue);
	DDX_Control(pDX, IDC_RADIO_RECT, m_radio_rect);
	DDX_Control(pDX, IDC_RADIO_ROUND, m_radio_round);
}

BEGIN_MESSAGE_MAP(CDialog39Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_BLUE, &CDialog39Dlg::OnBnClickedCheckBlue)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_GREEN, &CDialog39Dlg::OnBnClickedCheckGreen)
	ON_BN_CLICKED(IDC_CHECK_RED, &CDialog39Dlg::OnBnClickedCheckRed)
END_MESSAGE_MAP()


// CDialog39Dlg 消息处理程序

BOOL CDialog39Dlg::OnInitDialog()
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
	CheckRadioButton(IDC_RADIO_RECT, IDC_RADIO_ROUND, IDC_RADIO_ROUND);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDialog39Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDialog39Dlg::OnPaint()
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
HCURSOR CDialog39Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialog39Dlg::OnBnClickedCheckBlue()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}

void CDialog39Dlg::OnBnClickedCheckGreen()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
	//OnBnClickedCheckBlue();
}


void CDialog39Dlg::OnBnClickedCheckRed()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
	//OnBnClickedCheckBlue();
}


BOOL CDialog39Dlg::OnEraseBkgnd(CDC *pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	BOOL bRet = CDialogEx::OnEraseBkgnd(pDC);

	int nRed, nGreen, nBlue;
	nRed = m_chk_red.GetCheck() ? 255 : 0;
	nGreen = m_chk_green.GetCheck() ? 255 : 0;
	nBlue = m_chk_blue.GetCheck() ? 255 : 0;

	COLORREF crFore = RGB(nRed, nGreen, nBlue);
	CBrush brush;
	brush.CreateSolidBrush(crFore);
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	CRect rect = {150, 100, 250, 200};

	if (m_radio_rect.GetCheck()) {
		pDC->Rectangle(&rect);
	} else {
		pDC->Ellipse(&rect);
	}

	pDC->SelectObject(pOldBrush);

	return bRet;
}



