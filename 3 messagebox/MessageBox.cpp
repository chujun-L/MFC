#include "MessageBox.h"

CMessageBox app;

CMessageBoxView::CMessageBoxView()
{
	//MessageBox(NULL, TEXT("message"));
	Create(NULL, TEXT("message box"));
}


BOOL CMessageBox::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CMessageBoxView;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


BEGIN_MESSAGE_MAP(CMessageBoxView, CFrameWnd)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMessageBoxView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int result = MessageBox(TEXT("mfc"), TEXT("message mfc"), MB_YESNOCANCEL|MB_SYSTEMMODAL);

	switch (result) {
	case IDYES:
		MessageBox(TEXT("selete yes"));
		break;
	case IDNO:
		MessageBox(TEXT("selete no"));
		break;
	case IDCANCEL:
		MessageBox(TEXT("selete cancel"));
		break;
	}

	CFrameWnd::OnLButtonDown(nFlags, point);
}
