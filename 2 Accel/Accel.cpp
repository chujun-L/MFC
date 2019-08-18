#include "Accel.h"

CAccel app;

BOOL CAccel::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CAccelView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return true;
}

CAccelView::CAccelView()
{
	Create(NULL, TEXT("Accel Demo"), WS_OVERLAPPEDWINDOW|WS_HSCROLL|WS_VSCROLL);
}


BEGIN_MESSAGE_MAP(CAccelView, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


int CAccelView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CClientDC dc(this);

	m_nCellWidth = dc.GetDeviceCaps(LOGPIXELSX);
	m_nCellHeight = dc.GetDeviceCaps(LOGPIXELSY) / 4;
	m_nRibbonWidth = m_nCellWidth / 2;
	m_nViewHeight = m_nCellHeight * 100;
	m_nViewWidth = m_nCellWidth * 26 + m_nRibbonWidth;

	m_nHScrollPos = 0;
	m_nVScrollPos = 0;
	m_nScrollLineSize = 5;

	m_nHPageSize = 0;
	m_nVPageSize = 0;
	m_nHScrollMax = 0;
	m_nVScrollMax = 0;

	return 0;
}


void CAccelView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()

	// 重设置窗口原点
	dc.SetWindowOrg(m_nHScrollPos, m_nVScrollPos);

	/*
	 *  画线
	 */
	CPen pen(PS_SOLID, 0, RGB(192, 192, 192));
	CPen *pOldPen = dc.SelectObject(&pen);

	// 画横线
	for (int i = 0; i < 99; ++i) {
		int y = (i * m_nCellHeight) + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nViewWidth, y);
	}

	// 画竖线
	for (int i = 0; i < 26; ++i) {
		int x = (i * m_nCellWidth) + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nViewWidth);
	}

	// 还原画笔
	dc.SelectObject(pOldPen);

	/*
	 * 画Top Left的方框
	 */
	CBrush brush;
	brush.CreateStockObject(LTGRAY_BRUSH);
	
	CRect rcTop(0, 0, m_nViewWidth, m_nCellHeight);
	dc.FillRect(rcTop, &brush);
	CRect rcLeft(0, 0, m_nRibbonWidth, m_nViewHeight);
	dc.FillRect(rcLeft, &brush);

	dc.MoveTo(0, m_nCellHeight);
	dc.LineTo(m_nViewWidth, m_nCellHeight);

	dc.MoveTo(m_nRibbonWidth, 0);
	dc.LineTo(m_nRibbonWidth, m_nViewHeight);

	dc.SetBkMode(TRANSPARENT);			// 文字背景色透明
	for (int i = 0; i < 99; ++i) {
		int y = i * m_nCellHeight + m_nCellHeight;
		dc.MoveTo(0, y);
		dc.LineTo(m_nRibbonWidth, y);

		CString str;
		str.Format(TEXT("%d"), i + 1);

		CRect rect(0, y, m_nRibbonWidth, y + m_nCellHeight);
		dc.DrawText(str, &rect, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		rect.top++;
		dc.Draw3dRect(rect, RGB(255,255,255), RGB(128,128,128));
	}

	for (int i = 0; i < 26; ++i) {
		int x = i * m_nCellWidth + m_nRibbonWidth;
		dc.MoveTo(x, 0);
		dc.LineTo(x, m_nCellHeight);

		CString str;
		str.Format(TEXT("%c"), i + 'A');

		CRect rect(x, 0, x + m_nCellWidth, m_nCellHeight);
		dc.DrawText(str, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		rect.left++;
		dc.Draw3dRect(rect, RGB(255, 255, 255), RGB(128, 128, 128));
	}
}


void CAccelView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nDelta = 0;

	switch (nSBCode) {
	case SB_LINELEFT:
		nDelta = -(1 << m_nScrollLineSize);
		break;
	case SB_LINERIGHT:
		nDelta = 1 << m_nScrollLineSize;
		break;
	case SB_PAGELEFT:
		nDelta = -m_nHPageSize;
		break;
	case SB_PAGERIGHT:
		nDelta = m_nHPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = nPos - m_nHScrollPos;
		break;
	}

	m_nHScrollPos += nDelta;
	if (m_nHScrollPos >= 0 && m_nHScrollPos <= m_nViewWidth - m_nHPageSize) {
		SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE);
		ScrollWindow(-nDelta, 0);
	}
	
	if (m_nHScrollPos < 0) {
		m_nHScrollPos = 0;
	}
	else if (m_nHScrollPos > m_nViewWidth - m_nHPageSize) {
		m_nHScrollPos = m_nViewWidth - m_nHPageSize;
	}

	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CAccelView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nDelta = 0;

	switch (nSBCode) {
	case SB_LINEUP:
		nDelta = -m_nScrollLineSize;
		break;
	case SB_LINEDOWN:
		nDelta = m_nScrollLineSize;
		break;
	case SB_PAGEUP:
		nDelta = -m_nVPageSize;
		break;
	case SB_PAGEDOWN:
		nDelta = m_nVPageSize;
		break;
	case SB_THUMBTRACK:
		nDelta = (int)nPos - m_nVScrollPos;
		break;
	}

	m_nVScrollPos += nDelta;
	if (m_nVScrollPos >=0 && m_nVScrollPos <= m_nViewHeight - m_nVPageSize) {
		SetScrollPos(SB_VERT, m_nVScrollPos, TRUE);
		ScrollWindow(0, -nDelta);
	}

	if (m_nVScrollPos < 0) {
		m_nVScrollPos = 0;
	}
	else if (m_nVScrollPos > m_nViewHeight - m_nVPageSize) {
		m_nVScrollPos = m_nViewHeight - m_nVPageSize;
	}

	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CAccelView::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	if (cx < m_nViewWidth) {
		m_nHPageSize = cx;
		m_nHScrollMax = m_nViewWidth - 1;

		SCROLLINFO si;
		si.nMin = 0;
		si.nMax = m_nHScrollMax;
		si.nPos = m_nHScrollPos;
		si.nPage = m_nHPageSize;
		si.fMask = SIF_ALL;

		SetScrollInfo(SB_HORZ, &si, TRUE);
	}

	if (cy < m_nViewHeight) {
		m_nVPageSize = cy;
		m_nVScrollMax = m_nViewHeight - 1;

		SCROLLINFO si;
		si.nMin = 0;
		si.nMax = m_nVScrollMax;
		si.nPos = m_nVScrollPos;
		si.nPage = m_nVPageSize;
		si.fMask = SIF_ALL;

		SetScrollInfo(SB_VERT, &si, TRUE);
	}


	// TODO: 在此处添加消息处理程序代码
}
