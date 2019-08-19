#ifndef _MESSAGEBOX_H
#define _MESSAGEBOX_H

#include <afxwin.h>

class CMessageBox :public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CMessageBoxView :public CFrameWnd {
public:
	CMessageBoxView();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#endif // !_MESSAGEBOX_H
