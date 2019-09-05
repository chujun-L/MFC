#pragma once


// CSizePage 对话框

class CSizePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSizePage)

public:
	CSizePage();
	virtual ~CSizePage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIZE_PAGE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nWidth;
	int m_nHeight;
	int m_nUnits;
	int m_nColor;
	afx_msg void OnChange();
};
