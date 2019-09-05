#pragma once


// COptionsDialog 对话框

class COptionsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(CWnd* pParent = nullptr);   // 标准构造函数
	COptionsDialog(CView *pView);
	virtual ~COptionsDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nWidth;
	int m_nHeight;
	int m_nUints;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	CView *m_pView;
	virtual void PostNcDestroy();
};
