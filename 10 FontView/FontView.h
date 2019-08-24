#ifndef _FONT_VIEW_H
#define _FONT_VIEW_H

#include <afxwin.h>

#define IDC_PRINT			100
#define IDC_CHECKBOX		101
#define IDC_LISTBOX		102
#define IDC_SAMPLE		103


class CFontView :public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CFontViewWnd :public CWnd {

private:
	CListBox m_wndListBox;
	CStatic m_wndLBTitle;
	CStatic m_wndSampleText;

	int m_cxChar;
	int m_cyChar;

	CFont m_fontMain;
	CFont m_fontSample;

	CButton m_wndCheckBox;
	CButton m_wndGroupBox;
	CButton m_wndPushButton;

	void FillListBox();

public:
	CFontViewWnd();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectChange();
	afx_msg void OnPushButtonClicked();
	afx_msg void OnCheckBoxClicked();

	static int CALLBACK EnumFontFamilisProc(ENUMLOGFONT &lpelf,
										NEWTEXTMETRIC &lpntm, 
										int nFontType, 
										LPARAM lParam);
};


#endif // !_FONT_VIEW_H