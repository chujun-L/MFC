
// TreeViewView.cpp: CTreeViewView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TreeView.h"
#endif

#include "TreeViewDoc.h"
#include "TreeViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTreeViewView

IMPLEMENT_DYNCREATE(CTreeViewView, CTreeView)

BEGIN_MESSAGE_MAP(CTreeViewView, CTreeView)
END_MESSAGE_MAP()

// CTreeViewView 构造/析构

CTreeViewView::CTreeViewView() noexcept
{
	// TODO: 在此处添加构造代码

}

CTreeViewView::~CTreeViewView()
{
}

BOOL CTreeViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CTreeViewView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// 创建ImageList
	m_ilDrivers.Create(/*todo*/);

	this->GetTreeCtrl().SetImageList(&m_ilDrivers, /*todo*/);

	GetTreeCtrl().InsertItem(/*todo*/);
}


// CTreeViewView 诊断

#ifdef _DEBUG
void CTreeViewView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeViewView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTreeViewDoc* CTreeViewView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeViewDoc)));
	return (CTreeViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CTreeViewView 消息处理程序
