// CColorPage.cpp: 实现文件
//

#include "pch.h"
#include "DialogModal.h"
#include "CColorPage.h"
#include "afxdialogex.h"


// CColorPage 对话框

IMPLEMENT_DYNAMIC(CColorPage, CPropertyPage)

const COLORREF CColorPage::m_clrColors[3] = {
	RGB(255, 0, 0),
	RGB(0, 255, 0),
	RGB(0, 0, 255)
};

CColorPage::CColorPage()
	: CPropertyPage(IDD_COLOR_PAGE)
	, m_nColor(-1)
{

}

CColorPage::~CColorPage()
{
}

void CColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_PROPERTY_RED, m_nColor);
}


BEGIN_MESSAGE_MAP(CColorPage, CPropertyPage)
	ON_BN_CLICKED(IDC_PROPERTY_RED, &CColorPage::OnChange)
	ON_BN_CLICKED(IDC_PROPERTY_GREEN, &CColorPage::OnChange)
	ON_BN_CLICKED(IDC_PROPERTY_BLUE, &CColorPage::OnChange)
END_MESSAGE_MAP()


// CColorPage 消息处理程序


void CColorPage::OnChange()
{
	// TODO: 在此添加控件通知处理程序代码
	SetModified(TRUE);
}
