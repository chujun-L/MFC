// COptionsDialog.cpp: 实现文件
//

#include "pch.h"
#include "DialogModal.h"
#include "COptionsDialog.h"
#include "afxdialogex.h"


// COptionsDialog 对话框

IMPLEMENT_DYNAMIC(COptionsDialog, CDialogEx)

COptionsDialog::COptionsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_OPTION, pParent)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nUints(0)
{

}

COptionsDialog::COptionsDialog(CView *pView)
	: m_nWidth(0)
	, m_nHeight(0)
	, m_nUints(0)
{
	m_pView = pView;
}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 128);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 128);
	DDX_Radio(pDX, IDC_RADIO_INCHES, m_nUints);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialogEx)
	ON_BN_CLICKED(IDC_RESET, &COptionsDialog::OnBnClickedReset)
	ON_BN_CLICKED(IDOK, &COptionsDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COptionsDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// COptionsDialog 消息处理程序


void COptionsDialog::OnBnClickedReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUints = 0;

	// 将上面三个变量更新到对话框对应的文本框中
	UpdateData(FALSE);
}


void COptionsDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	UpdateData(TRUE);

	RECTPROP rp;
	rp.nWidth = m_nWidth;
	rp.nHeight = m_nHeight;
	rp.nUnits = m_nUints;

	m_pView->SendMessage(WM_USER_APPLY, (WPARAM)0, (LPARAM)&rp);

}


void COptionsDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();

	DestroyWindow();
}


void COptionsDialog::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	m_pView->SendMessage(WM_USER_DIALOG_DESTROYED, 0, 0);
	delete this;

	CDialogEx::PostNcDestroy();
}
