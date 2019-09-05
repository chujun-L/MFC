
// SdiSquaresView.cpp: CSdiSquaresView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SdiSquares.h"
#endif

#include "SdiSquaresDoc.h"
#include "SdiSquaresView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSdiSquaresView

IMPLEMENT_DYNCREATE(CSdiSquaresView, CView)

BEGIN_MESSAGE_MAP(CSdiSquaresView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSdiSquaresView 构造/析构

CSdiSquaresView::CSdiSquaresView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSdiSquaresView::~CSdiSquaresView()
{
}

BOOL CSdiSquaresView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSdiSquaresView 绘图

void CSdiSquaresView::OnDraw(CDC* pDC)
{
	CSdiSquaresDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDC->SetMapMode(MM_LOENGLISH);

	// 处理文档的数据，并绘画在视图
	for (int i = 0; i < COL; ++i) {
		for (int j = 0; j < ROW; ++j) {
			COLORREF color = pDoc->GetSquare(j, i);
			CBrush brush(color);

			// 确定每小格左上角及右下角的坐标
			int x1 = (j * 100) + 50;
			int y1 = (i * -100) - 50;
			int x2 = x1 + 100;
			int y2 = y1 - 100;

			CRect rect(x1, y1, x2, y2);
			pDC->FillRect(rect, &brush);
		}
	}

	for (int x = 50; x <= 450; x += 100) {
		pDC->MoveTo(x, -50);
		pDC->LineTo(x, -450);
	}

	for (int y = -50; y >= -450; y -= 100) {
		pDC->MoveTo(50, y);
		pDC->LineTo(450, y);
	}
}


// CSdiSquaresView 打印

BOOL CSdiSquaresView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSdiSquaresView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSdiSquaresView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSdiSquaresView 诊断

#ifdef _DEBUG
void CSdiSquaresView::AssertValid() const
{
	CView::AssertValid();
}

void CSdiSquaresView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSdiSquaresDoc* CSdiSquaresView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdiSquaresDoc)));
	return (CSdiSquaresDoc*)m_pDocument;
}
#endif //_DEBUG


// CSdiSquaresView 消息处理程序


void CSdiSquaresView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	dc.SetMapMode(MM_LOENGLISH);
	CPoint pos = point;
	// 从设备坐标转换成逻辑坐标
	dc.DPtoLP(&pos);

	if (pos.x >= 50 && pos.x <= 450 && 
		pos.y <= -50 && pos.y >= -450) {
		int row = (pos.x - 50) / 100;
		int col = (-pos.y - 50) / 100;

		CSdiSquaresDoc *pDoc = GetDocument();
		COLORREF clrCurrentColor = pDoc->GetCurrentColor();
		pDoc->SetSquare(row, col, clrCurrentColor);
	}

	CView::OnLButtonDown(nFlags, point);
}