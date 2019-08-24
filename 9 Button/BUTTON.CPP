#include "Button.h"

CButtonDemo app;

BOOL CButtonDemo::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pMainWnd = new CButtonWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CButtonWnd::CButtonWnd()
{
	CString strWndClass = AfxRegisterWndClass(0,
		app.LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		app.LoadStandardIcon(IDI_WINLOGO));

	CreateEx(0, strWndClass, TEXT("CButton Demo"),
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL);
}


BEGIN_MESSAGE_MAP(CButtonWnd, CWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_OK, OnPushButtonClicked)
	ON_BN_CLICKED(IDC_CHECKBOX1, OnCheckBox1Clicked)
	ON_BN_CLICKED(IDC_CHECKBOX2, OnCheckBox2Clicked)
END_MESSAGE_MAP()


int CButtonWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect;
	
	rect.SetRect(60, 60, 160, 90);
	m_wndPushButton.Create(TEXT("OK"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		rect, this, IDC_OK);

	rect.SetRect(60, 100, 200, 210);
	m_wndCheckBoxButton1.Create(TEXT("check box1"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		rect, this, IDC_CHECKBOX1);

	rect.SetRect(60, 200, 200, 240);
	m_wndCheckBoxButton2.Create(TEXT("check box2"),
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		rect, this, IDC_CHECKBOX2);

	rect.SetRect(200, 60, 460, 200);
	m_wndGroupBoxButton.Create(TEXT("GroupBox"),
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		rect, this, IDC_GROUPBOX);

	rect.SetRect(220, 90, 450, 110);
	m_wndRadioButton1.Create(TEXT("com1"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 
		rect, this, IDC_COM1);

	rect.SetRect(220, 120, 450, 140);
	m_wndRadioButton2.Create(TEXT("com2"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		rect, this, IDC_COM2);

	rect.SetRect(220, 150, 450, 170);
	m_wndRadioButton3.Create(TEXT("com3"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		rect, this, IDC_COM3);

	return 0;
}

void CButtonWnd::OnPushButtonClicked()
{
	MessageBox(TEXT("hello"));
}

void CButtonWnd::OnCheckBox1Clicked()
{
	if (m_wndCheckBoxButton1.GetCheck() == BST_CHECKED) {
		MessageBox(TEXT("复选框1"));
	}
}

void CButtonWnd::OnCheckBox2Clicked()
{
	if (m_wndCheckBoxButton2.GetCheck() == BST_CHECKED) {
		MessageBox(TEXT("复选框2"));
	}
}
