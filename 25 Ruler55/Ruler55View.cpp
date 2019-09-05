
// Ruler55View.cpp: CRuler55View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Ruler55.h"
#endif

#include "Ruler55Doc.h"
#include "Ruler55View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRuler55View

IMPLEMENT_DYNCREATE(CRuler55View, CView)

BEGIN_MESSAGE_MAP(CRuler55View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRuler55View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CRuler55View 构造/析构

CRuler55View::CRuler55View() noexcept
{
	// TODO: 在此处添加构造代码

}

CRuler55View::~CRuler55View()
{
}

BOOL CRuler55View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CRuler55View 绘图

void CRuler55View::OnDraw(CDC* pDC)
{
	CRuler55Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// 绘制ruler
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


// CRuler55View 打印


void CRuler55View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CRuler55View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CRuler55View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CRuler55View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CRuler55View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CRuler55View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CRuler55View 诊断

#ifdef _DEBUG
void CRuler55View::AssertValid() const
{
	CView::AssertValid();
}

void CRuler55View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRuler55Doc* CRuler55View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRuler55Doc)));
	return (CRuler55Doc*)m_pDocument;
}
#endif //_DEBUG


// CRuler55View 消息处理程序
