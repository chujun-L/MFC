#include "FontView.h"

CFontView app;

BOOL CFontView::InitInstance()
{
	m_pMainWnd = new CFontViewWnd;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

void CFontViewWnd::FillListBox()
{
	m_wndListBox.ResetContent();

	//m_wndListBox.AddString(TEXT("Arial"));
	//m_wndListBox.AddString(TEXT("Courier New"));
	//m_wndListBox.AddString(TEXT("Dotum"));
	//m_wndListBox.AddString(TEXT("MS Serif"));
	//m_wndListBox.AddString(TEXT("Timers New Romain"));


	// 调用windows自带的字体
	// EnumFontFamilisProc回调函数
	CClientDC dc(this);
	::EnumFontFamilies((HDC)dc, NULL, (FONTENUMPROC)EnumFontFamilisProc, (LPARAM)this);
}

CFontViewWnd::CFontViewWnd()
{
	CString strWndClass = AfxRegisterWndClass(
		0,
		app.LoadStandardCursor(IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		app.LoadStandardIcon(IDI_WINLOGO));

	CreateEx(0, strWndClass, TEXT("FontView"), 
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, NULL);

	CRect rect(0, 0, m_cxChar * 68, m_cyChar * 26);
	CalcWindowRect(&rect);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
		SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);
}


BEGIN_MESSAGE_MAP(CFontViewWnd, CWnd)
	ON_WM_CREATE()
	ON_LBN_SELCHANGE(IDC_LISTBOX, OnSelectChange)
	ON_BN_CLICKED(IDC_PRINT, OnPushButtonClicked)
	ON_BN_CLICKED(IDC_CHECKBOX, OnCheckBoxClicked)
END_MESSAGE_MAP()


int CFontViewWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 设置字体
	m_fontMain.CreatePointFont(100, TEXT("MS Sans Serif"));

	// 获取量度
	CClientDC dc(this);
	CFont *pOldFont = dc.SelectObject(&m_fontMain);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	m_cxChar = tm.tmAveCharWidth;
	m_cyChar = tm.tmHeight + tm.tmExternalLeading; // tmExternalLeading行间距

	dc.SelectObject(pOldFont);

	//CRect rect(10, 10, 100, 30);
	// 根据字体的宽度及高度来确定位置
	CRect rect(m_cxChar * 2, m_cyChar, m_cxChar * 48, m_cyChar * 2);
	m_wndLBTitle.Create(TEXT("Typefaces"),
		WS_CHILD | WS_VISIBLE | SS_LEFT, rect, this);

	rect.SetRect(m_cxChar * 2, m_cyChar * 2 + 5, m_cxChar * 48, m_cyChar * 18);
	m_wndListBox.CreateEx(WS_EX_CLIENTEDGE, TEXT("listbox"), NULL,
		WS_CHILD | WS_VISIBLE | LBS_STANDARD, rect, this, IDC_LISTBOX);

	rect.SetRect(m_cxChar * 2, m_cyChar * 19, m_cxChar * 48, m_cyChar * 20);
	m_wndCheckBox.Create(TEXT("Show TrueType fonts only"), 
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, rect, this, IDC_CHECKBOX);

	rect.SetRect(m_cxChar * 2, m_cyChar * 21, m_cxChar * 66, m_cyChar * 25);
	m_wndGroupBox.Create(TEXT("Sample"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		rect, this, (UINT)-1);

	rect.SetRect(m_cxChar * 4, m_cyChar * 22, m_cxChar * 64, m_cyChar * (99 /4));
	m_wndSampleText.Create(NULL, WS_CHILD | WS_VISIBLE | SS_CENTER,
		rect, this, IDC_SAMPLE);

	rect.SetRect(m_cxChar * 50, m_cyChar * 2 + 5, m_cxChar * 66, m_cyChar * 4);
	m_wndPushButton.Create(TEXT("Print Sample"), 
		WS_CHILD | WS_VISIBLE | WS_DISABLED | BS_PUSHBUTTON,
		rect, this, IDC_PRINT);

	m_wndLBTitle.SetFont(&m_fontMain, FALSE);
	m_wndListBox.SetFont(&m_fontMain, FALSE);
	m_wndCheckBox.SetFont(&m_fontMain, FALSE);
	m_wndGroupBox.SetFont(&m_fontMain, FALSE);
	m_wndPushButton.SetFont(&m_fontMain, FALSE);

	FillListBox();

	return 0;
}

void CFontViewWnd::OnSelectChange()
{
	CString strFontName;

	int nIndex = m_wndListBox.GetCurSel();

	if (nIndex == LB_ERR) {
		m_wndPushButton.EnableWindow(FALSE);
		m_wndSampleText.SetWindowText(TEXT(""));
	} else {
		m_wndPushButton.EnableWindow(TRUE);

		// 删除旧字体
		if ((HFONT)m_fontSample != NULL) {
			m_fontSample.DeleteObject();
		}

		// 从索引号来获取字体的名称
		m_wndListBox.GetText(nIndex, strFontName);

		m_fontSample.CreatePointFont(200, strFontName);
		m_wndSampleText.SetFont(&m_fontSample);
		m_wndSampleText.SetWindowText(TEXT("AbCcDdEeFfGg"));
	}
}

void CFontViewWnd::OnPushButtonClicked()
{
	// TODO
}

void CFontViewWnd::OnCheckBoxClicked()
{
	FillListBox();
	OnSelectChange();
}

int CALLBACK CFontViewWnd::EnumFontFamilisProc(ENUMLOGFONT &lpelf, 
											NEWTEXTMETRIC &lpntm, 
											int nFontType, 
											LPARAM lParam)
{
	CFontViewWnd *pWnd = (CFontViewWnd *)lParam;

	// CheckBox被选中
	if (pWnd->m_wndCheckBox.GetCheck() == BST_CHECKED) {
		if (nFontType & TRUETYPE_FONTTYPE) {
			pWnd->m_wndListBox.AddString(lpelf.elfLogFont.lfFaceName);
		}
	} else {
		pWnd->m_wndListBox.AddString(lpelf.elfLogFont.lfFaceName);
	}

	// 返回1继续迭代，返回0就停止迭代
	return 1;
}
