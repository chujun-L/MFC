
// ChildView.cpp: CChildView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "MyPad.h"
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
	ON_COMMAND(ID_FILE_NEW, &CChildView::OnFileNew)
	ON_COMMAND(ID_EDIT_CUT, &CChildView::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CChildView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CChildView::OnEditPaste)
	ON_COMMAND(ID_EDIT_DEL, &CChildView::OnEditDel)
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CChildView::OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CChildView::OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DEL, &CChildView::OnUpdateEditDel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CChildView::OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CChildView::OnUpdateEditUndo)
	ON_WM_SETFOCUS()
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

BOOL CChildView::IsTextSelected()
{
	int nStartSelect, nEndSelect;
	m_wndEdit.GetSel(nStartSelect, nEndSelect);
	return (nStartSelect != nEndSelect);
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

	// CRect(0, 0, 0, 0)在OnSize消息里重新设置
	m_wndEdit.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL |
					ES_MULTILINE | ES_AUTOVSCROLL,
					CRect(0, 0, 0, 0), this, IDC_EDIT);

	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_wndEdit.MoveWindow(0, 0, cx, cy);
}

// 文件->新建
void CChildView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.SetWindowTextW(TEXT(""));
}


void CChildView::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.Cut();
}


void CChildView::OnEditCopy()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.Copy();
}


void CChildView::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.Paste();
}


void CChildView::OnEditDel()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.Clear();
}


void CChildView::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	m_wndEdit.Undo();
}


void CChildView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(IsTextSelected());
}


void CChildView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(IsTextSelected());
}


void CChildView::OnUpdateEditDel(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(IsTextSelected());
}


void CChildView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_TEXT));
}


void CChildView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(m_wndEdit.CanUndo());
}


void CChildView::OnSetFocus(CWnd *pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	m_wndEdit.SetFocus();
}
