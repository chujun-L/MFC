// CFileProperties.cpp: 实现文件
//

#include "pch.h"
#include "DialogModal.h"
#include "CFileProperties.h"


// CFileProperties

IMPLEMENT_DYNAMIC(CFileProperties, CPropertySheet)

CFileProperties::CFileProperties(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_sizePage);
	AddPage(&m_colorPage);
}

CFileProperties::CFileProperties(LPCTSTR pszCaption, CView *pView, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_pView = pView;
	AddPage(&m_sizePage);
	AddPage(&m_colorPage);
}

CFileProperties::~CFileProperties()
{
}

void CFileProperties::OnPageApply()
{
	GetActivePage()->UpdateData(TRUE);

	ELLPROP ep;
	ep.nWidth = m_sizePage.m_nWidth;
	ep.nHeight = m_sizePage.m_nHeight;
	ep.nUnits = m_sizePage.m_nUnits;
	ep.nColor = m_colorPage.m_nColor;

	m_pView->SendMessage(WM_USER_PAGE_APPLY, 0, (LPARAM)&ep);

	m_sizePage.SetModified(FALSE);
	m_colorPage.SetModified(FALSE);
}


BEGIN_MESSAGE_MAP(CFileProperties, CPropertySheet)
	ON_BN_CLICKED(ID_APPLY_NOW, OnPageApply)
END_MESSAGE_MAP()


// CFileProperties 消息处理程序
