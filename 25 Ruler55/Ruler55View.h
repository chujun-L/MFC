
// Ruler55View.h: CRuler55View 类的接口
//

#pragma once


class CRuler55View : public CView
{
protected: // 仅从序列化创建
	CRuler55View() noexcept;
	DECLARE_DYNCREATE(CRuler55View)

// 特性
public:
	CRuler55Doc* GetDocument() const;

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
	virtual ~CRuler55View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Ruler55View.cpp 中的调试版本
inline CRuler55Doc* CRuler55View::GetDocument() const
   { return reinterpret_cast<CRuler55Doc*>(m_pDocument); }
#endif

