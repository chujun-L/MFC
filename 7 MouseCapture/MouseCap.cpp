#include "MouseCap.h"

CMouseCap app;

CMouseCapView::CMouseCapView()
{
	m_bTracking = FALSE;

	// �����Լ��Ĵ�����
	CString strWndClass = AfxRegisterWndClass(0,
		AfxGetApp()->LoadStandardCursor(IDC_CROSS),
		(HBRUSH)(COLOR_WINDOW + 1),
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));

	Create(strWndClass, TEXT("Mouse Capture"), WS_OVERLAPPEDWINDOW);
}

void CMouseCapView::InvertLine(CDC &dc, CPoint ptFrom, CPoint ptTo)
{
	int nOldMode = dc.SetROP2(R2_NOT);
	dc.MoveTo(ptFrom);
	dc.LineTo(ptTo);
	dc.SetROP2(nOldMode);
}


BOOL CMouseCap::InitInstance()
{
	m_pMainWnd = new CMouseCapView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


BEGIN_MESSAGE_MAP(CMouseCapView, CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CMouseCapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bTracking = TRUE;
	m_ptFrom = point;
	m_ptTo = point;

	// �������
	SetCapture();

	CFrameWnd::OnLButtonDown(nFlags, point);
}


void CMouseCapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bTracking) {

		// �ͷű���������
		if (GetCapture() == this) {
			::ReleaseCapture();
		}

		CClientDC dc(this);

		InvertLine(dc, m_ptFrom, m_ptTo);

		CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
		dc.SelectObject(&pen);

		dc.MoveTo(m_ptFrom);
		dc.LineTo(point);

		m_bTracking = FALSE;
	}

	CFrameWnd::OnLButtonUp(nFlags, point);
}


void CMouseCapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bTracking) {
		CClientDC dc(this);

		InvertLine(dc, m_ptFrom, m_ptTo);
		InvertLine(dc, m_ptFrom, point);

		m_ptTo = point;
	}

	CFrameWnd::OnMouseMove(nFlags, point);
}
