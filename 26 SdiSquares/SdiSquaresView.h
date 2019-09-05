
// SdiSquaresView.h: CSdiSquaresView 类的接口
//

#pragma once


class CSdiSquaresView : public CView
{
protected: // 仅从序列化创建
	CSdiSquaresView() noexcept;
	DECLARE_DYNCREATE(CSdiSquaresView)

// 特性
public:
	CSdiSquaresDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSdiSquaresView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SdiSquaresView.cpp 中的调试版本
inline CSdiSquaresDoc* CSdiSquaresView::GetDocument() const
   { return reinterpret_cast<CSdiSquaresDoc*>(m_pDocument); }
#endif

