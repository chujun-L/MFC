#include "pch.h"
#include "line.h"

// 2->���л�ʱ�İ汾��
IMPLEMENT_SERIAL(CLine, CObject, 2 | VERSIONABLE_SCHEMA)

CLine::CLine()
{
}

CLine::CLine(CPoint pStar, CPoint pEnd)
{
	this->m_pStar = pStar;
	this->m_pEnd = pEnd;
}

CLine::CLine(CPoint pStar, CPoint pEnd, COLORREF clrLine)
{
	this->m_pStar = pStar;
	this->m_pEnd = pEnd;
	this->m_clrLine = clrLine;
}

void CLine::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	// �������
	if (ar.IsStoring()) {
		ar << m_pStar << m_pEnd << m_clrLine;
	} else {
		UINT nSchema = ar.GetObjectSchema();
		switch (nSchema) {
		case 1:	// �汾��1
			ar >> m_pStar >> m_pEnd;
			m_clrLine = RGB(0, 0, 0);
			break;
		case 2:	// �汾��2
			ar >> m_pStar >> m_pEnd >> m_clrLine;
			break;
		default:
			AfxThrowArchiveException(CArchiveException::badSchema);
			break;
		}

		//ar >> m_pStar >> m_pEnd;
	}
}
