#ifndef _BUTTON_H
#define _BUTTON_H

#include <afxwin.h>

#define IDC_OK			100
#define IDC_CHECKBOX1		101
#define IDC_CHECKBOX2		102
#define IDC_GROUPBOX		103

#define IDC_COM1			200
#define IDC_COM2			201
#define IDC_COM3			202

class CButtonDemo :public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CButtonWnd :public CWnd {

public:
	CButtonWnd();

private:
	CButton m_wndPushButton;
	CButton m_wndCheckBoxButton1;
	CButton m_wndCheckBoxButton2;
	CButton m_wndGroupBoxButton;
	CButton m_wndRadioButton1;
	CButton m_wndRadioButton2;
	CButton m_wndRadioButton3;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPushButtonClicked();
	afx_msg void OnCheckBox1Clicked();
	afx_msg void OnCheckBox2Clicked();
};

#endif // !_BUTTON_H

