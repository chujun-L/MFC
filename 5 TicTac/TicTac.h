#ifndef _TIC_TAC_H
#define _TIC_TAC_H

#include <afxwin.h>

#define EX	1	// 格子的图案为X
#define OH	2	// 格子的图案为O

class CTicTac :public CWinApp {

public:
	virtual BOOL InitInstance();
};

// 继承CWnd窗口，而不是CFramWnd，这样窗口创建更灵活
class CTicTacView :public CWnd {
	
public:
	CTicTacView();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

private:
	// 9个棋格
	static const CRect m_reSquares[9];
	int m_nGameGrid[9];
	int m_nNextChar;		// 下一步轮到谁

	void DrawBoard(CDC &pDC);
	void DrawX(CDC &dc, int nPos);
	void DrawO(CDC &dc, int nPos);

	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();
	void ResetGame();

	// 判断鼠标指针坐在哪个棋盘里
	int GetRectID(CPoint point);
};



#endif // !_TIC_TAC_H

