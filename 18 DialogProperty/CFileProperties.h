#pragma once

#include "CSizePage.h"
#include "CColorPage.h"

// CFileProperties

typedef struct ELLPROP_S {
	int nWidth;
	int nHeight;
	int nUnits;
	int nColor;
}ELLPROP;


class CFileProperties : public CPropertySheet
{
	DECLARE_DYNAMIC(CFileProperties)

public:
	CFileProperties(UINT nIDCaption, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	CFileProperties(LPCTSTR pszCaption, CView *pView, CWnd* pParentWnd = nullptr, UINT iSelectPage = 0);
	virtual ~CFileProperties();

	CSizePage m_sizePage;
	CColorPage m_colorPage;
	CView *m_pView;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPageApply();
};


