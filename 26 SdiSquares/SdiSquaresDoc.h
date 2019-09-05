﻿
// SdiSquaresDoc.h: CSdiSquaresDoc 类的接口
//


#pragma once

#define ROW		4
#define COL		4

class CSdiSquaresDoc : public CDocument
{
protected: // 仅从序列化创建
	CSdiSquaresDoc() noexcept;
	DECLARE_DYNCREATE(CSdiSquaresDoc)

	// 特性
public:

	// 操作
public:

	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive &ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC &dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 实现
public:
	virtual ~CSdiSquaresDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString &value);
#endif // SHARED_HANDLERS
	COLORREF m_clrGrid[COL][ROW];
	COLORREF m_clrCurrentColor;
public:
	COLORREF GetCurrentColor();
	void SetSquare(int row, int col, COLORREF color);
	COLORREF CSdiSquaresDoc::GetSquare(int row, int col);
	afx_msg void OnColorYellow();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorCyan();
	afx_msg void OnColorBlue();
	afx_msg void OnColorWhite();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorYellow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorCyan(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorWhite(CCmdUI *pCmdUI);
};
