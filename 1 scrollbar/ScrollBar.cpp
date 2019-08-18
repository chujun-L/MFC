#include "ScrollBar.h"

#define LINEHEIGHT	15	// 文字的行高
#define LINENUM		100	// 文字的行数

CBrollbar app;

BOOL CBrollbar::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CBrollbarView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return true;
}

CBrollbarView::CBrollbarView()
{
	Create(NULL, TEXT("竖直滚动条"), WS_OVERLAPPEDWINDOW|WS_VSCROLL);
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
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CFrameWnd::OnPaint()

	// 当显示内容超出m_nVPageSize时，重新设置坐标原点
	dc.SetWindowOrg(0, m_nVScrollPos);

	TCHAR lineBuffer[1024];

	for (int i = 0; i < LINENUM; ++i) {
		_sntprintf_s(lineBuffer, 1024, TEXT("hello %d"), i + 1);
		dc.TextOut(0, i * LINEHEIGHT, lineBuffer, lstrlen(lineBuffer));
	}
	
	
}

// 重载这个成员函数以执行派生类所需的初始化工作, OnCreate是在Create或CreateEx成员函数返回之前被调用的
int CBrollbarView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_nVScrollPos = 0;
	m_nViewHeight = LINEHEIGHT * LINENUM;
	m_nVPageSize = 0;

	return 0;
}

// 框架在窗口的大小被改变以后调用这个成员函数
void CBrollbarView::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// 当拖放的窗口小于所有内容的高度时才需要处理竖直滚动条
	if (cy < m_nViewHeight) {
		m_nVPageSize = cy;
		//m_nVScrollPos = min(m_nVScrollPos, m_nViewHeight - m_nVPageSize);
	}

	// 当nMin与nMax设置相同的数值时，滚动条会消失
	SCROLLINFO si;
	si.nMin = 0;
	si.nMax = m_nViewHeight;
	//si.nPos = m_nVScrollPos;
	si.nPage = m_nVPageSize;
	si.fMask = SIF_ALL;

	SetScrollInfo(SB_VERT, &si, true);
}

// 当用户单击窗口的垂直滚动条时，框架调用此成员函数
void CBrollbarView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nMoveSB = 0;

	// 消息的类型
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
		nMoveSB = nPos - m_nVScrollPos;		// 这里其实需要将nPos传递给SetScrollPos
		break;
	}

	m_nVScrollPos += nMoveSB;
	if (m_nVScrollPos >= 0 && 
		m_nVScrollPos <= m_nViewHeight - m_nVPageSize + LINEHEIGHT) {
		SetScrollPos(SB_VERT, m_nVScrollPos, true);
		ScrollWindow(0, -nMoveSB);				// 滑动显示的窗口
	}

	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}
