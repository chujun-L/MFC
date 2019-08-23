
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "Menu.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView():m_nShape(0)
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_SHAPE_CIRCLE, &CChildView::OnShapeCircle)
	ON_COMMAND(ID_SHAPE_TRIANGLE, &CChildView::OnShapeTriangle)
	ON_COMMAND(ID_SHAPE_SQUARE, &CChildView::OnShapeSquare)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_CIRCLE, &CChildView::OnUpdateShapeCircle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_TRIANGLE, &CChildView::OnUpdateShapeTriangle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_SQUARE, &CChildView::OnUpdateShapeSquare)
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
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
	CPoint points[3];

	switch (m_nShape) {
	case 0:
		dc.Ellipse(100, 100, 200, 200);
		break;
	case 1:
		points[0].x = 150;
		points[0].y = 100;
		points[1].x = 100;
		points[1].y = 200;
		points[2].x = 200;
		points[2].y = 200;
		dc.Polygon(points, 3);
		break;
	case 2:
		dc.Rectangle(100, 100, 200, 200);
		break;
	}
}



void CChildView::OnShapeCircle()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 0;
	Invalidate();
}


void CChildView::OnShapeTriangle()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 1;
	Invalidate();
}


void CChildView::OnShapeSquare()
{
	// TODO: 在此添加命令处理程序代码
	m_nShape = 2;
	Invalidate();
}


void CChildView::OnUpdateShapeCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 0);
}


void CChildView::OnUpdateShapeTriangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 1);
}


void CChildView::OnUpdateShapeSquare(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nShape == 2);
}
