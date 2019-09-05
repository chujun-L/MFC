// CSizePage.cpp: 实现文件
//

#include "pch.h"
#include "DialogModal.h"
#include "CSizePage.h"
#include "afxdialogex.h"


// CSizePage 对话框

IMPLEMENT_DYNAMIC(CSizePage, CPropertyPage)

CSizePage::CSizePage()
	: CPropertyPage(IDD_SIZE_PAGE)
	, m_nWidth(0)
	, m_nHeight(0)
	, m_nUnits(-1)
{

}

CSizePage::~CSizePage()
{
}

void CSizePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 1, 128);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 1, 128);
	DDX_Radio(pDX, IDC_PROPERTY_INCHES, m_nUnits);
}


BEGIN_MESSAGE_MAP(CSizePage, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CSizePage::OnChange)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_PROPERTY_INCHES, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_PROPERTY_CENTERMITER, &CSizePage::OnChange)
	ON_BN_CLICKED(IDC_PROPERTY_PIXELS, &CSizePage::OnChange)
END_MESSAGE_MAP()


// CSizePage 消息处理程序


void CSizePage::OnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	SetModified(TRUE);
}
