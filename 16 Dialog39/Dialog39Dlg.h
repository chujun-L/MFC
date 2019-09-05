
// Dialog39Dlg.h: 头文件
//

#pragma once


// CDialog39Dlg 对话框
class CDialog39Dlg : public CDialogEx
{
// 构造
public:
	CDialog39Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG39_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckBlue();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	CButton m_chk_red;
	CButton m_chk_green;
	CButton m_chk_blue;
	CButton m_radio_rect;
	CButton m_radio_round;
	afx_msg void OnBnClickedCheckGreen();
	afx_msg void OnBnClickedCheckRed();
};
