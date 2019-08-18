#ifndef _SCROLL_BAR_H_
#define _SCROLL_BAR_H_

#include <afxwin.h>

class CBrollbar :public CWinApp {

public:
	virtual BOOL InitInstance();
};

class CBrollbarView : public CFrameWnd {
public:
	CBrollbarView();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);

private:
	int m_nVScrollPos;		// 竖直滚动条的位置
	int m_nViewHeight;		// 所有内容的高度
	int m_nVPageSize;			// 窗口显示大小
};


#endif // !_SCROLL_BAR_H_

