
// SdiSquaresDoc.cpp: CSdiSquaresDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SdiSquares.h"
#endif

#include "SdiSquaresDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSdiSquaresDoc

IMPLEMENT_DYNCREATE(CSdiSquaresDoc, CDocument)

BEGIN_MESSAGE_MAP(CSdiSquaresDoc, CDocument)
	ON_COMMAND(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnColorYellow)
	ON_COMMAND(ID_COLOR_RED, &CSdiSquaresDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CSdiSquaresDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_CYAN, &CSdiSquaresDoc::OnColorCyan)
	ON_COMMAND(ID_COLOR_BLUE, &CSdiSquaresDoc::OnColorBlue)
	ON_COMMAND(ID_COLOR_WHITE, &CSdiSquaresDoc::OnColorWhite)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSdiSquaresDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_YELLOW, &CSdiSquaresDoc::OnUpdateColorYellow)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSdiSquaresDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_CYAN, &CSdiSquaresDoc::OnUpdateColorCyan)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSdiSquaresDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_WHITE, &CSdiSquaresDoc::OnUpdateColorWhite)
END_MESSAGE_MAP()


// CSdiSquaresDoc 构造/析构

CSdiSquaresDoc::CSdiSquaresDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CSdiSquaresDoc::~CSdiSquaresDoc()
{
}

BOOL CSdiSquaresDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	for (int i = 0; i < COL; ++i) {
		for (int j = 0; j < ROW; ++j) {
			m_clrGrid[i][j] = RGB(255, 255, 255);
		}
	}

	m_clrCurrentColor = RGB(255, 0, 0);

	return TRUE;
}




// CSdiSquaresDoc 序列化

void CSdiSquaresDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// 保存格子的数据及颜色到硬盘
		for (int i = 0; i < COL; ++i) {
			for (int j = 0; j < ROW; ++j) {
				ar << m_clrGrid[i][j];
			}
		}

		ar << m_clrCurrentColor;
	}
	else
	{
		// 从硬盘中读取格子的数据及颜色
		for (int i = 0; i < COL; ++i) {
			for (int j = 0; j < ROW; ++j) {
				ar >> m_clrGrid[i][j];
			}
		}

		ar >> m_clrCurrentColor;
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSdiSquaresDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSdiSquaresDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSdiSquaresDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSdiSquaresDoc 诊断

#ifdef _DEBUG
void CSdiSquaresDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSdiSquaresDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSdiSquaresDoc 命令


COLORREF CSdiSquaresDoc::GetCurrentColor()
{
	return m_clrCurrentColor;
}


void CSdiSquaresDoc::SetSquare(int row, int col, COLORREF color)
{
	ASSERT(row >= 0 && row <= 3 && col >= 0 && col <= 3);

	m_clrGrid[col][row] = color;

	SetModifiedFlag(TRUE);
	UpdateAllViews(NULL);

	// 设置鼠标左键事件处理数据，然后调用OnDraw绘图
}

COLORREF CSdiSquaresDoc::GetSquare(int row, int col)
{
	ASSERT(row >= 0 && row <= 3 && col >= 0 && col <= 3);

	return m_clrGrid[col][row];
}


void CSdiSquaresDoc::OnColorYellow()
{
	m_clrCurrentColor = RGB(255, 255, 0);
}


void CSdiSquaresDoc::OnColorRed()
{
	m_clrCurrentColor = RGB(255, 0, 0);
}


void CSdiSquaresDoc::OnColorGreen()
{
	m_clrCurrentColor = RGB(0, 255, 0);
}


void CSdiSquaresDoc::OnColorCyan()
{
	m_clrCurrentColor = RGB(0, 255, 255);
}


void CSdiSquaresDoc::OnColorBlue()
{
	m_clrCurrentColor = RGB(0, 0, 255);
}


void CSdiSquaresDoc::OnColorWhite()
{
	m_clrCurrentColor = RGB(255, 255, 255);
}


void CSdiSquaresDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 0, 0));
}


void CSdiSquaresDoc::OnUpdateColorYellow(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 0));
}


void CSdiSquaresDoc::OnUpdateColorCyan(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 255, 255));
}


void CSdiSquaresDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(0, 0, 255));
}


void CSdiSquaresDoc::OnUpdateColorWhite(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(m_clrCurrentColor == RGB(255, 255, 255));
}
