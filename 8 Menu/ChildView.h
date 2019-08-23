
// ChildView.h: CChildView 类的接口
//


#pragma once


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeTriangle();
	afx_msg void OnShapeSquare();
protected:
	int m_nShape;
public:
	afx_msg void OnUpdateShapeCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeTriangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeSquare(CCmdUI *pCmdUI);
};

