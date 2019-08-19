#ifndef _MOUSE_MESSAGE_H
#define _MOUSE_MESSAGE_H


#include <afxwin.h>

class CMouseMessage :public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CMouseMessageView :public CFrameWnd {
public:
	CMouseMessageView();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};




#endif // !_MOUSE_MESSAGE_H

