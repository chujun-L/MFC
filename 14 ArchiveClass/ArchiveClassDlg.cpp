
// ArchiveClassDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ArchiveClass.h"
#include "ArchiveClassDlg.h"
#include "afxdialogex.h"
#include "line.h"

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


// CArchiveClassDlg 对话框



CArchiveClassDlg::CArchiveClassDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARCHIVECLASS_DIALOG, pParent)
	, m_edit_txt(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArchiveClassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit_txt);
}

BEGIN_MESSAGE_MAP(CArchiveClassDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CArchiveClassDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArchiveClassDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CArchiveClassDlg 消息处理程序

BOOL CArchiveClassDlg::OnInitDialog()
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

void CArchiveClassDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CArchiveClassDlg::OnPaint()
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
HCURSOR CArchiveClassDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArchiveClassDlg::OnBnClickedButton1()
{
	// 保存起来的是二进制文件，并不是文本文件
	CFile file(TEXT("text.txt"), CFile::modeCreate|CFile::modeWrite);

	int a, b;

	a = 100;
	b = 200;
	//file.Write(&a, sizeof(a));
	//file.Write(&b, sizeof(b));

	CArchive ar(&file, CArchive::store);
	ar << a << b;

	CLine line(CPoint(1, 1), CPoint(1, 6), RGB(255, 255, 0));
	// 多版本时必须用这个方式写
	ar << &line;
	//line.Serialize(ar);

	ar.Close();
	file.Close();
	MessageBox(TEXT("串行化成功"));

}


void CArchiveClassDlg::OnBnClickedButton2()
{
	CFile file(TEXT("text.txt"), CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	int a, b;
	CLine *pLine;

	ar >> a >> b;
	// 多版本时用
	ar >> pLine;
	//line.Serialize(ar);

	m_edit_txt.Empty();

	CString s;
	s.Format(TEXT("a = %d\r\n"), a);
	m_edit_txt.Append(s);
	s.Format(TEXT("b = %d\r\n"), b);
	m_edit_txt.Append(s);
	s.Format(TEXT("Line start = (%d, %d) end = (%d, %d) color = (%d, %d, %d)\r\n"),
					pLine->m_pStar.x, pLine->m_pStar.y,
					pLine->m_pEnd.x, pLine->m_pEnd.y,
					GetRValue(pLine->m_clrLine),
					GetGValue(pLine->m_clrLine),
					GetBValue(pLine->m_clrLine));
	
	m_edit_txt.Append(s);
	UpdateData(FALSE);

	ar.Close();
	file.Close();
}
