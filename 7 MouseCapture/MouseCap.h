#ifndef _MOUSECAP_H
#define _MOUSECAP_H

#include <afxwin.h>


class CMouseCap :public CWinApp {

public:
	virtual BOOL InitInstance();
};


class CMouseCapView :public CFrameWnd {
public:
	CMouseCapView();
	void InvertLine(CDC &dc, CPoint ptFrom, CPoint ptTo);

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
	BOOL m_bTracking;		// 正在画图
	CPoint m_ptFrom;		// 画图的起点
	CPoint m_ptTo;		// 画图的终点	
};

#endif // !_MOUSECAP_H

