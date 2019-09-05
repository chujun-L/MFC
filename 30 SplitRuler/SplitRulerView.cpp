
// SplitRulerView.cpp: CSplitRulerView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SplitRuler.h"
#endif

#include "SplitRulerDoc.h"
#include "SplitRulerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSplitRulerView

IMPLEMENT_DYNCREATE(CSplitRulerView, CScrollView)

BEGIN_MESSAGE_MAP(CSplitRulerView, CScrollView)
END_MESSAGE_MAP()

// CSplitRulerView 构造/析构

CSplitRulerView::CSplitRulerView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSplitRulerView::~CSplitRulerView()
{
}

BOOL CSplitRulerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CSplitRulerView 绘图

void CSplitRulerView::OnDraw(CDC* pDC)
{
	CSplitRulerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->SetMapMode(MM_LOENGLISH);
	pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
	pDC->SetBkMode(TRANSPARENT);

	CBrush brush(RGB(255, 255, 0));
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(100, -100, 1300, -200);
	pDC->SelectObject(pOldBrush);

	for (int i = 125; i < 1300; i += 25) {
		pDC->MoveTo(i, -192);
		pDC->LineTo(i, -200);
	}

	for (int i = 150; i < 1300; i += 50) {
		pDC->MoveTo(i, -184);
		pDC->LineTo(i, -200);
	}

	for (int i = 200; i < 1300; i += 100) {
		pDC->MoveTo(i, -175);
		pDC->LineTo(i, -200);

		CString s;
		s.Format(TEXT("%d"), (i / 100) - 1);
		pDC->TextOutW(i, -175, s);
	}
}

void CSplitRulerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = 1500;
	sizeTotal.cy = 100;
	SetScrollSizes(MM_LOENGLISH, sizeTotal);
}


// CSplitRulerView 诊断

#ifdef _DEBUG
void CSplitRulerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSplitRulerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSplitRulerDoc* CSplitRulerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitRulerDoc)));
	return (CSplitRulerDoc*)m_pDocument;
}
#endif //_DEBUG


// CSplitRulerView 消息处理程序
