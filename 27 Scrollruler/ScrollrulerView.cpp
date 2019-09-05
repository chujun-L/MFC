
// ScrollrulerView.cpp: CScrollrulerView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Scrollruler.h"
#endif

#include "ScrollrulerDoc.h"
#include "ScrollrulerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScrollrulerView

IMPLEMENT_DYNCREATE(CScrollrulerView, CScrollView)

BEGIN_MESSAGE_MAP(CScrollrulerView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
//	ON_WM_ACTIVATE()
//ON_WM_ACTIVATE()
END_MESSAGE_MAP()

// CScrollrulerView 构造/析构

CScrollrulerView::CScrollrulerView() noexcept
{
	// TODO: 在此处添加构造代码

}

CScrollrulerView::~CScrollrulerView()
{
}

BOOL CScrollrulerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CScrollrulerView 绘图

void CScrollrulerView::OnDraw(CDC* pDC)
{
	CScrollrulerDoc* pDoc = GetDocument();
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

void CScrollrulerView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = 1500;
	sizeTotal.cy = 100;
	SetScrollSizes(MM_LOENGLISH, sizeTotal);
}


// CScrollrulerView 打印

BOOL CScrollrulerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CScrollrulerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CScrollrulerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CScrollrulerView 诊断

#ifdef _DEBUG
void CScrollrulerView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CScrollrulerView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CScrollrulerDoc* CScrollrulerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScrollrulerDoc)));
	return (CScrollrulerDoc*)m_pDocument;
}
#endif //_DEBUG
