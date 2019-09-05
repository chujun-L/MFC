
// DialogModalView.cpp: CDialogModalView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DialogModal.h"
#endif

#include "DialogModalDoc.h"
#include "DialogModalView.h"
#include "COptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDialogModalView

IMPLEMENT_DYNCREATE(CDialogModalView, CView)

BEGIN_MESSAGE_MAP(CDialogModalView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPTION, &CDialogModalView::OnFileOption)
	ON_MESSAGE(WM_USER_DIALOG_DESTROYED, OnDialogDestroyed)
	ON_MESSAGE(WM_USER_APPLY, OnApply)
END_MESSAGE_MAP()

// CDialogModalView 构造/析构

CDialogModalView::CDialogModalView() noexcept
{
	// 初始化
	m_nWidth = 4;
	m_nHeight = 2;
	m_nUnits = 0;
	m_pDlg = NULL;
}

CDialogModalView::~CDialogModalView()
{
}

BOOL CDialogModalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDialogModalView 绘图

void CDialogModalView::OnDraw(CDC* pDC)
{
	CDialogModalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush brush(RGB(255, 0, 255));
	CBrush *pOldBrush = pDC->SelectObject(&brush);

	switch (m_nUnits) {
	case 0:
		pDC->SetMapMode(MM_LOENGLISH);
		pDC->Rectangle(0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;
	case 1:
		pDC->SetMapMode(MM_LOMETRIC);
		pDC->Rectangle(0, 0, m_nWidth * 100, -m_nHeight * 100);
		break;
	case 2:
		pDC->SetMapMode(MM_TEXT);
		pDC->Rectangle(0, 0, m_nWidth, m_nHeight);
		break;
	}

	pDC->SelectObject(pOldBrush);
}


// CDialogModalView 打印

BOOL CDialogModalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDialogModalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDialogModalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDialogModalView 诊断

#ifdef _DEBUG
void CDialogModalView::AssertValid() const
{
	CView::AssertValid();
}

void CDialogModalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDialogModalDoc* CDialogModalView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDialogModalDoc)));
	return (CDialogModalDoc*)m_pDocument;
}
#endif //_DEBUG


// CDialogModalView 消息处理程序


/**
 * 模态对话框
 */
/*
void CDialogModalView::OnFileOption()
{
	// TODO: 在此添加命令处理程序代码
	COptionsDialog dlg;

	// 将视图里的三个变量赋值给对话框里的三个变量
	dlg.m_nWidth = m_nWidth;
	dlg.m_nHeight = m_nHeight;
	dlg.m_nUints = m_nUnits;

	// 打开模态对话框
	//dlg.DoModal();

	// 当按下确定按键时，将对话框的参数传回给视图
	if (dlg.DoModal() == IDOK) {
		m_nWidth = dlg.m_nWidth;
		m_nHeight = dlg.m_nHeight;
		m_nUnits = dlg.m_nUints;
		
		// 失效后会重新绘图
		Invalidate();
	}
}
*/


/**
 * 非模态对话框
 */
void CDialogModalView::OnFileOption()
{
	if (m_pDlg != NULL) {
		m_pDlg->SetFocus();
	} else {
		m_pDlg = new COptionsDialog(this);
		m_pDlg->m_nWidth = m_nWidth;
		m_pDlg->m_nHeight = m_nHeight;
		m_pDlg->m_nUints = m_nUnits;

		m_pDlg->Create(IDD_DIALOG_OPTION);
		m_pDlg->ShowWindow(SW_SHOW);
	}

}

LRESULT CDialogModalView::OnDialogDestroyed(WPARAM wParam, LPARAM lParam)
{
	//return LRESULT();

	m_pDlg = NULL;
	return 0;
}

LRESULT CDialogModalView::OnApply(WPARAM wParam, LPARAM lParam)
{
	//return LRESULT();
	RECTPROP *prp = (RECTPROP *)lParam;
	m_nWidth = prp->nWidth;
	m_nHeight = prp->nHeight;
	m_nUnits = prp->nUnits;

	Invalidate();

	return 0;
}
