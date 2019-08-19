#include "MouseMessage.h"


CMouseMessage app;

CMouseMessageView::CMouseMessageView()
{
	Create(NULL, TEXT("mouse message"), WS_OVERLAPPEDWINDOW);
}


BOOL CMouseMessage::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);

	// �߼�����
	dc.Ellipse(point.x-2, point.y+2, point.x+2, point.y-2);
	
	CFrameWnd::OnMouseMove(nFlags, point);
}
