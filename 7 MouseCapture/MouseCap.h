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
	BOOL m_bTracking;		// ���ڻ�ͼ
	CPoint m_ptFrom;		// ��ͼ�����
	CPoint m_ptTo;		// ��ͼ���յ�	
};

#endif // !_MOUSECAP_H

