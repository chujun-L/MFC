#include "TicTac.h"


CTicTac app;


const CRect CTicTacView::m_reSquares[9] = {
	CRect(16, 16, 112, 112),
	CRect(128, 16, 224, 112),
	CRect(240, 16, 336, 112),

	CRect(16, 128, 112, 224),
	CRect(128, 128, 224, 224),
	CRect(240, 128, 336, 224),

	CRect(16, 240, 112, 336),
	CRect(128, 240, 224, 336),
	CRect(240, 240, 336, 336)
};


CTicTacView::CTicTacView()
{
	// 注册自定义的窗口类
	CString strWnd = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE+1), 
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));

	// 创建窗口
	CreateEx(0, strWnd, TEXT("TicTac"), 
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

	// 设定窗口大小
	CRect rect(0, 0, 352, 352);
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), 
		SWP_NOZORDER | SWP_NOMOVE |SWP_NOREDRAW);

	// 初始化棋盘格子的状态
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	m_nNextChar = EX;		// X先落棋盘
}


BOOL CTicTac::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CTicTacView;		// 在PostNcDestroy() delete
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


void CTicTacView::PostNcDestroy()
{
	// 当继承CFrameWnd时，会自动销毁CTicTacView，但继承CWnd时，要手动销毁
	delete this;

	CWnd::PostNcDestroy();
}


BEGIN_MESSAGE_MAP(CTicTacView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CTicTacView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	DrawBoard(dc);
}

void CTicTacView::DrawBoard(CDC &pDC)
{
	// 画棋盘
	CPen pen(PS_SOLID, 16, RGB(0, 0, 0));
	CPen *pOldPen = pDC.SelectObject(&pen);

	pDC.MoveTo(120, 16);
	pDC.LineTo(120, 336);

	pDC.MoveTo(232, 16);
	pDC.LineTo(232, 336);

	pDC.MoveTo(16, 120);
	pDC.LineTo(336, 120);

	pDC.MoveTo(16, 232);
	pDC.LineTo(336, 232);

	pDC.SelectObject(pOldPen);

	// 当拖动棋盘到屏幕的边界时会消失部分的棋子显示，在这重新再绘制棋子
	for (int i = 0; i < 9; ++i) {
		if (m_nGameGrid[i] == EX) {
			DrawX(pDC, i);
		} else if (m_nGameGrid[i] == OH) {
			DrawO(pDC, i);
		}
	}
}

void CTicTacView::DrawX(CDC &dc, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(255, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);

	//CRect rect(16, 16, 112, 112);
	CRect rect = m_reSquares[nPos];
	//dc.Rectangle(&rect);
	rect.DeflateRect(16, 16);
	dc.MoveTo(rect.left, rect.top);
	dc.LineTo(rect.right, rect.bottom);
	dc.MoveTo(rect.right, rect.top);
	dc.LineTo(rect.left, rect.bottom);

	dc.SelectObject(pOldPen);
}

void CTicTacView::DrawO(CDC &dc, int nPos)
{
	CPen pen(PS_SOLID, 16, RGB(0, 0, 255));
	CPen *pOldPen = dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);	// 去掉圆内的背景色

	//CRect rect(16, 16, 112, 112);
	CRect rect = m_reSquares[nPos];
	rect.DeflateRect(16, 16);
	dc.Ellipse(&rect);
	
	dc.SelectObject(pOldPen);
}

void CTicTacView::CheckForGameOver()
{
	int nWinner = 0;

	if (nWinner = IsWinner()) {
		CString str = (nWinner == EX) ? TEXT("X is winer") : TEXT("O is winer");
		MessageBox(str, TEXT("Game Over"), MB_ICONEXCLAMATION|MB_OK);
		ResetGame();
	} else if (IsDraw()) {
		MessageBox(TEXT("It's a draw"), TEXT("Game Over"), MB_ICONEXCLAMATION|MB_OK);
		ResetGame();
	}
}

int CTicTacView::IsWinner()
{
	// 判断赢的规则
	static int nPattern[8][3] = {
		0,1,2,
		3,4,5,
		6,7,8,

		0,3,6,
		1,4,7,
		2,5,8,

		0,4,8,
		2,4,6
	};


	for (int i = 0; i < 8; ++i) {
		if (m_nGameGrid[nPattern[i][0]] == EX &&
			m_nGameGrid[nPattern[i][1]] == EX &&
			m_nGameGrid[nPattern[i][2]] == EX)
		{
			return EX;
		}

		if (m_nGameGrid[nPattern[i][0]] == OH &&
			m_nGameGrid[nPattern[i][1]] == OH &&
			m_nGameGrid[nPattern[i][2]] == OH)
		{
			return OH;
		}
	}

	return 0;
}

/**
 * 如果棋盘里还能下棋，则不为平局
 * (注意：先判断IsWinner()，再判断IsDraw())
 */
BOOL CTicTacView::IsDraw()
{
	for (int i = 0; i < 9; ++i) {
		if (m_nGameGrid[i] == 0) {
			return FALSE;
		}
	}

	return TRUE;
}

void CTicTacView::ResetGame()
{
	m_nNextChar = EX;
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	Invalidate();
}

/**
 *  判断鼠标指针在哪个棋盘里
 * @point 当前鼠标指针的位置
 * @return 棋盘数组的下标
 */
int CTicTacView::GetRectID(CPoint point)
{
	for (int i = 0; i < 9; ++i) {
		if (m_reSquares[i].PtInRect(point)) {
			return i;
		}
	}

	return -1;
}


void CTicTacView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 判断落棋方
	if (m_nNextChar != EX) {
		return;
	}

	int nPos = GetRectID(point);
	if (-1 == nPos || m_nGameGrid[nPos] != 0) {
		return;
	}

	// 记录棋盘格子的图案状态为X
	m_nGameGrid[nPos] = EX;
	m_nNextChar = OH;			// 下一步棋为O

	// 按下鼠标左键时画X
	CClientDC dc(this);
	DrawX(dc, nPos);

	// 检查游戏是否结束
	CheckForGameOver();

	CWnd::OnLButtonDown(nFlags, point);
}


void CTicTacView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// 判断落棋方
	if (m_nNextChar != OH) {
		return;
	}

	int nPos = GetRectID(point);
	if (-1 == nPos || m_nGameGrid[nPos] != 0) {
		return;
	}

	// 记录棋盘格子的图案状态为O
	m_nGameGrid[nPos] = OH;
	m_nNextChar = EX;			// 下一步棋为X

	// 按下鼠标左键时画O
	CClientDC dc(this);
	DrawO(dc, nPos);

	// 检查游戏是否结束
	CheckForGameOver();

	CWnd::OnRButtonDown(nFlags, point);
}


void CTicTacView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// 鼠标左键双击棋盘黑线时，复位游戏
	CClientDC dc(this);
	if (dc.GetPixel(point) == RGB(0, 0, 0)) {
		ResetGame();
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
