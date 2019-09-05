
// TreeViewView.h: CTreeViewView 类的接口
//

#pragma once


class CTreeViewView : public CTreeView
{
protected: // 仅从序列化创建
	CTreeViewView() noexcept;
	DECLARE_DYNCREATE(CTreeViewView)

// 特性
public:
	CTreeViewDoc* GetDocument() const;

// 操作
public:
	CImageList m_ilDrivers;

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CTreeViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TreeViewView.cpp 中的调试版本
inline CTreeViewDoc* CTreeViewView::GetDocument() const
   { return reinterpret_cast<CTreeViewDoc*>(m_pDocument); }
#endif

