#include "MouseMessage.h"


CMouseMessage app;

CMouseMessageView::CMouseMessageView()
{
	Create(NULL, TEXT("mouse message"), WS_OVERLAPPEDWINDOW);
}


BOOL CMouseMessage::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CMouseMessageView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


BEGIN_MESSAGE_MAP(CMouseMessageView, CFrameWnd)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CMouseMessageView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);

	// 逻辑坐标
	dc.Ellipse(point.x-2, point.y+2, point.x+2, point.y-2);
	
	CFrameWnd::OnMouseMove(nFlags, point);
}
