
// SplitRulerView.h: CSplitRulerView 类的接口
//

#pragma once


class CSplitRulerView : public CScrollView
{
protected: // 仅从序列化创建
	CSplitRulerView() noexcept;
	DECLARE_DYNCREATE(CSplitRulerView)

// 特性
public:
	CSplitRulerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CSplitRulerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SplitRulerView.cpp 中的调试版本
inline CSplitRulerDoc* CSplitRulerView::GetDocument() const
   { return reinterpret_cast<CSplitRulerDoc*>(m_pDocument); }
#endif

