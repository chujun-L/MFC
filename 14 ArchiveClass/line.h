#pragma once
#include <atltypes.h>

class CLine :public CObject
{
	DECLARE_SERIAL(CLine)

//protected:
public:
	CPoint m_pStar;
	CPoint m_pEnd;
	COLORREF m_clrLine;

public:
	CLine();
	CLine(CPoint pStar, CPoint pEnd);
	CLine(CPoint pStar, CPoint pEnd, COLORREF clrLine);

	void Serialize(CArchive &ar);

};
