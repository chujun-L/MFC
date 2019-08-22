#ifndef _ACCEL_H
#define _ACCEL_H

#include <afxwin.h>

class CAccel :public CWinApp {

public:
	virtual BOOL InitInstance();

};

class CAccelView :public CFrameWnd {

private:
	int m_nCellWidth;
	int m_nCellHeight;
	int m_nRibbonWidth;
	int m_nViewWidth;
	int m_nViewHeight;

	int m_nHScrollPos;
	int m_nVScrollPos;
	int m_nScrollLineSize;
	int m_nHPageSize;
	int m_nVPageSize;
	int m_nHScrollMax;
	int m_nVScrollMax;

public:
	CAccelView();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


#endif // !_ACCEL_H

