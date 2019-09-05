
// DialogModalView.h: CDialogModalView 类的接口
//

#pragma once


class CDialogModalView : public CView
{
protected: // 仅从序列化创建
	CDialogModalView() noexcept;
	DECLARE_DYNCREATE(CDialogModalView)

// 特性
public:
	CDialogModalDoc* GetDocument() const;

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
	virtual ~CDialogModalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_nWidth;
	int m_nHeight;
	int m_nUnits;
	int m_nColor;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOption();
	afx_msg void OnFileProperties();
	afx_msg LRESULT OnApply(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // DialogModalView.cpp 中的调试版本
inline CDialogModalDoc* CDialogModalView::GetDocument() const
   { return reinterpret_cast<CDialogModalDoc*>(m_pDocument); }
#endif

