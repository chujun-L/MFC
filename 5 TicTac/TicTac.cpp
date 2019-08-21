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
	// ע���Զ���Ĵ�����
	CString strWnd = AfxRegisterWndClass(CS_DBLCLKS, 
		AfxGetApp()->LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE+1), 
		AfxGetApp()->LoadStandardIcon(IDI_WINLOGO));

	// ��������
	CreateEx(0, strWnd, TEXT("TicTac"), 
		WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION|WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);

	// �趨���ڴ�С
	CRect rect(0, 0, 352, 352);
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), 
		SWP_NOZORDER | SWP_NOMOVE |SWP_NOREDRAW);

	// ��ʼ�����̸��ӵ�״̬
	::ZeroMemory(m_nGameGrid, 9 * sizeof(int));
	m_nNextChar = EX;		// X��������
}


BOOL CTicTac::InitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pMainWnd = new CTicTacView;		// ��PostNcDestroy() delete
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


void CTicTacView::PostNcDestroy()
{
	// ���̳�CFrameWndʱ�����Զ�����CTicTacView�����̳�CWndʱ��Ҫ�ֶ�����
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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

	DrawBoard(dc);
}

void CTicTacView::DrawBoard(CDC &pDC)
{
	// ������
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

	// ���϶����̵���Ļ�ı߽�ʱ����ʧ���ֵ�������ʾ�����������ٻ�������
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
	dc.SelectStockObject(NULL_BRUSH);	// ȥ��Բ�ڵı���ɫ

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
	// �ж�Ӯ�Ĺ���
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
 * ��������ﻹ�����壬��Ϊƽ��
 * (ע�⣺���ж�IsWinner()�����ж�IsDraw())
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
 *  �ж����ָ�����ĸ�������
 * @point ��ǰ���ָ���λ��
 * @return ����������±�
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
	// �ж����巽
	if (m_nNextChar != EX) {
		return;
	}

	int nPos = GetRectID(point);
	if (-1 == nPos || m_nGameGrid[nPos] != 0) {
		return;
	}

	// ��¼���̸��ӵ�ͼ��״̬ΪX
	m_nGameGrid[nPos] = EX;
	m_nNextChar = OH;			// ��һ����ΪO

	// ����������ʱ��X
	CClientDC dc(this);
	DrawX(dc, nPos);

	// �����Ϸ�Ƿ����
	CheckForGameOver();

	CWnd::OnLButtonDown(nFlags, point);
}


void CTicTacView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// �ж����巽
	if (m_nNextChar != OH) {
		return;
	}

	int nPos = GetRectID(point);
	if (-1 == nPos || m_nGameGrid[nPos] != 0) {
		return;
	}

	// ��¼���̸��ӵ�ͼ��״̬ΪO
	m_nGameGrid[nPos] = OH;
	m_nNextChar = EX;			// ��һ����ΪX

	// ����������ʱ��O
	CClientDC dc(this);
	DrawO(dc, nPos);

	// �����Ϸ�Ƿ����
	CheckForGameOver();

	CWnd::OnRButtonDown(nFlags, point);
}


void CTicTacView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// ������˫�����̺���ʱ����λ��Ϸ
	CClientDC dc(this);
	if (dc.GetPixel(point) == RGB(0, 0, 0)) {
		ResetGame();
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}
