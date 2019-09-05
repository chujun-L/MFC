#pragma once


// CColorPage 对话框

class CColorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CColorPage)

public:
	CColorPage();
	virtual ~CColorPage();

	static const COLORREF m_clrColors[3];

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLOR_PAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nColor;
	afx_msg void OnChange();
};
