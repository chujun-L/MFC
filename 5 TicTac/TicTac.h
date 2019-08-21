#ifndef _TIC_TAC_H
#define _TIC_TAC_H

#include <afxwin.h>

#define EX	1	// ���ӵ�ͼ��ΪX
#define OH	2	// ���ӵ�ͼ��ΪO

class CTicTac :public CWinApp {

public:
	virtual BOOL InitInstance();
};

// �̳�CWnd���ڣ�������CFramWnd���������ڴ��������
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
	// 9�����
	static const CRect m_reSquares[9];
	int m_nGameGrid[9];
	int m_nNextChar;		// ��һ���ֵ�˭

	void DrawBoard(CDC &pDC);
	void DrawX(CDC &dc, int nPos);
	void DrawO(CDC &dc, int nPos);

	void CheckForGameOver();
	int IsWinner();
	BOOL IsDraw();
	void ResetGame();

	// �ж����ָ�������ĸ�������
	int GetRectID(CPoint point);
};



#endif // !_TIC_TAC_H

