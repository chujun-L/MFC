#pragma once

#include <afxwin.h>
#include <afxext.h>

class CToolBarApp : public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CTooBarWnd :public CFrameWnd {

public:
	CTooBarWnd();

	CToolBar m_wndToolBar;
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};