
// MdiSquaresView.cpp: CMdiSquaresView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MdiSquares.h"
#endif

#include "MdiSquaresDoc.h"
#include "MdiSquaresView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMdiSquaresView

IMPLEMENT_DYNCREATE(CMdiSquaresView, CView)

BEGIN_MESSAGE_MAP(CMdiSquaresView, CView)
END_MESSAGE_MAP()

// CMdiSquaresView 构造/析构

CMdiSquaresView::CMdiSquaresView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMdiSquaresView::~CMdiSquaresView()
{
}

BOOL CMdiSquaresView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMdiSquaresView 绘图

void CMdiSquaresView::OnDraw(CDC* /*pDC*/)
{
	CMdiSquaresDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMdiSquaresView 诊断

#ifdef _DEBUG
void CMdiSquaresView::AssertValid() const
{
	CView::AssertValid();
}

void CMdiSquaresView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMdiSquaresDoc* CMdiSquaresView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiSquaresDoc)));
	return (CMdiSquaresDoc*)m_pDocument;
}
#endif //_DEBUG


// CMdiSquaresView 消息处理程序
