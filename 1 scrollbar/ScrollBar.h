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
	int m_nVScrollPos;		// ��ֱ��������λ��
	int m_nViewHeight;		// �������ݵĸ߶�
	int m_nVPageSize;			// ������ʾ��С
};


#endif // !_SCROLL_BAR_H_

