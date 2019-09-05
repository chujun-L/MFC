
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "DialogShare.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_FONT, &CChildView::OnFileFont)
	ON_COMMAND(ID_FILE_COLOR, &CChildView::OnFileColor)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CRect rect(0, 0, 0, 0);
	m_rich.Create(ES_AUTOVSCROLL | ES_MULTILINE 
		| ES_WANTRETURN | WS_CHILD | WS_VISIBLE | WS_VSCROLL,
		rect, this, 1);



	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);
	m_rich.SetWindowPos(&wndTop, 0, 0,
						rect.right - rect.left,
						rect.bottom - rect.top,
						SWP_SHOWWINDOW);

}


void CChildView::OnFileOpen()
{
	// TEXT里面的内容不能有空格
	CFileDialog fdlg(TRUE, NULL, NULL,
		OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
		TEXT("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"), this);

	//fdlg.DoModal();
	// File->Open
	if (fdlg.DoModal() == IDOK) {
		//MessageBox(fdlg.GetPathName());

		CStdioFile file(fdlg.GetPathName(), CFile::modeRead);
		CString line, all;

		while (file.ReadString(line)) {
			all.Append(line);
			all.Append(TEXT("\r\n"));
		}
		file.Close();

		m_rich.SetWindowTextW(all);
	}
}


void CChildView::OnFileFont()
{
	// TODO: 在此添加命令处理程序代码

	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	m_rich.GetSelectionCharFormat(cf);
	CFontDialog fdlg(cf);
	
	if (fdlg.DoModal() == IDOK) {
		fdlg.GetCharFormat(cf);
		m_rich.SetSelectionCharFormat(cf);
	}
}


void CChildView::OnFileColor()
{
	// TODO: 在此添加命令处理程序代码

	CHARFORMAT cf = {0};
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;

	m_rich.GetSelectionCharFormat(cf);
	CColorDialog cdlg(cf.crTextColor);

	if (cdlg.DoModal() == IDOK) {
		cf.crTextColor = cdlg.GetColor();
		cf.dwEffects = 0;
		m_rich.SetSelectionCharFormat(cf);
	}
}
