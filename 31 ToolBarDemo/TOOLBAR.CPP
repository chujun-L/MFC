#include "toolbar.h"

CToolBarApp app;

BOOL CToolBarApp::InitInstance()
{
	m_pMainWnd = new CTooBarWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CTooBarWnd::CTooBarWnd()
{
	Create(NULL, TEXT("The ToolBar Demo"));
}
BEGIN_MESSAGE_MAP(CTooBarWnd, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CTooBarWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_wndToolBar.Create(this);

	return 0;
}
