
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Ruler54.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	dc.SetMapMode(MM_LOENGLISH);
	dc.SetTextAlign(TA_CENTER | TA_BOTTOM);
	dc.SetBkMode(TRANSPARENT);

	CBrush brush(RGB(255, 255, 0));
	CBrush *pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(100, -100, 1300, -200);
	dc.SelectObject(pOldBrush);

	for (int i = 125; i < 1300; i += 25) {
		dc.MoveTo(i, -192);
		dc.LineTo(i, -200);
	}

	for (int i = 150; i < 1300; i += 50) {
		dc.MoveTo(i, -184);
		dc.LineTo(i, -200);
	}

	for (int i = 200; i < 1300; i += 100) {
		dc.MoveTo(i, -175);
		dc.LineTo(i, -200);

		CString s;
		s.Format(TEXT("%d"), (i / 100) - 1);
		dc.TextOutW(i, -175, s);
	}
}

