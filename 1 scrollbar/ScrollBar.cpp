#include "ScrollBar.h"

#define LINEHEIGHT	15	// ���ֵ��и�
#define LINENUM		100	// ���ֵ�����

CBrollbar app;

BOOL CBrollbar::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pMainWnd = new CBrollbarView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return true;
}

CBrollbarView::CBrollbarView()
{
	Create(NULL, TEXT("��ֱ������"), WS_OVERLAPPEDWINDOW|WS_VSCROLL);
}


BEGIN_MESSAGE_MAP(CBrollbarView, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


void CBrollbarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CFrameWnd::OnPaint()

	// ����ʾ���ݳ���m_nVPageSizeʱ��������������ԭ��
	dc.SetWindowOrg(0, m_nVScrollPos);

	TCHAR lineBuffer[1024];

	for (int i = 0; i < LINENUM; ++i) {
		_sntprintf_s(lineBuffer, 1024, TEXT("hello %d"), i + 1);
		dc.TextOut(0, i * LINEHEIGHT, lineBuffer, lstrlen(lineBuffer));
	}
	
	
}

// ���������Ա������ִ������������ĳ�ʼ������, OnCreate����Create��CreateEx��Ա��������֮ǰ�����õ�
int CBrollbarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_nVScrollPos = 0;
	m_nViewHeight = LINEHEIGHT * LINENUM;
	m_nVPageSize = 0;

	return 0;
}

// ����ڴ��ڵĴ�С���ı��Ժ���������Ա����
void CBrollbarView::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// ���ϷŵĴ���С���������ݵĸ߶�ʱ����Ҫ������ֱ������
	if (cy < m_nViewHeight) {
		m_nVPageSize = cy;
		//m_nVScrollPos = min(m_nVScrollPos, m_nViewHeight - m_nVPageSize);
	}

	// ��nMin��nMax������ͬ����ֵʱ������������ʧ
	SCROLLINFO si;
	si.nMin = 0;
	si.nMax = m_nViewHeight;
	//si.nPos = m_nVScrollPos;
	si.nPage = m_nVPageSize;
	si.fMask = SIF_ALL;

	SetScrollInfo(SB_VERT, &si, true);
}

// ���û��������ڵĴ�ֱ������ʱ����ܵ��ô˳�Ա����
void CBrollbarView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nMoveSB = 0;

	// ��Ϣ������
	switch (nSBCode) {
	case SB_LINEUP:
		nMoveSB = -LINEHEIGHT;
		break;
	case SB_LINEDOWN:
		nMoveSB = LINEHEIGHT;
		break;
	case SB_PAGEUP:
		nMoveSB = -m_nVPageSize;
		break;
	case SB_PAGEDOWN:
		nMoveSB = m_nVPageSize;
		break;
	case SB_THUMBTRACK:
		nMoveSB = nPos - m_nVScrollPos;		// ������ʵ��Ҫ��nPos���ݸ�SetScrollPos
		break;
	}

	m_nVScrollPos += nMoveSB;
	if (m_nVScrollPos >= 0 && 
		m_nVScrollPos <= m_nViewHeight - m_nVPageSize + LINEHEIGHT) {
		SetScrollPos(SB_VERT, m_nVScrollPos, true);
		ScrollWindow(0, -nMoveSB);				// ������ʾ�Ĵ���
	}

	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}
