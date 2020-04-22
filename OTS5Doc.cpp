
// OTS5Doc.cpp: реализация класса COTS5Doc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "OTS5.h"
#endif

#include "OTS5Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COTS5Doc

IMPLEMENT_DYNCREATE(COTS5Doc, CDocument)

BEGIN_MESSAGE_MAP(COTS5Doc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение COTS5Doc

COTS5Doc::COTS5Doc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

COTS5Doc::~COTS5Doc()
{
}

BOOL COTS5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация COTS5Doc

void COTS5Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << vertexs.size();
		for (auto i = 0; i < vertexs.size(); i++) {
			ar << vertexs[i].id_;
			ar << vertexs[i].coordinates_;
			ar << vertexs[i].color_;
			ar << vertexs[i].width_;
			ar << vertexs[i].penType_;
			ar << vertexs[i].vertexName_;
			if (vertexs[i].vertexType_ == vertex::Type::constant) {
				ar << 0;
			}
			else {
				ar << 1;
			}
			ar << vertexs[i].connectionID_.size();
			for (auto j = 0; j < vertexs[i].connectionID_.size(); j++) {
				ar << vertexs[i].connectionID_[j];
			}
		}
		ar << edges.size();
		for (auto i = 0; i < edges.size(); i++) {
			ar << edges[i].id_;
			ar << edges[i].color_;
			ar << edges[i].drawID;
			ar << edges[i].type_;
			ar << edges[i].width_;
			ar << edges[i].is_oriented_;
			ar << edges[i].coordinates_[0];
			ar << edges[i].coordinates_[1];
			ar << edges[i].connectID_[0];
			ar << edges[i].connectID_[1];
			ar << edges[i].choosenSide_[0];
			ar << edges[i].choosenSide_[1];
			switch (edges[i].orientation_)
			{
			case edge::Orientation::right:
				ar << 0;
				break;
			case ::edge::Orientation::left:
				ar << 1;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		int Size,connectionSize,temp_;

		ar >> Size;
		for (auto i = 0; i < Size; i++) {
			vertex Vertex;
			ar >> Vertex.id_;
			ar >> Vertex.coordinates_;
			ar >> Vertex.color_;
			ar >> Vertex.width_;
			ar >> Vertex.penType_;
			ar >> Vertex.vertexName_;
			ar >> temp_;
			if (temp_ == 0) {
				Vertex.vertexType_ = vertex::Type::constant;
			}
			else {
				Vertex.vertexType_ = vertex::Type::temp;
			}
			ar >> connectionSize;
			for (auto j = 0; j < connectionSize; j++) {
				ar >> temp_;
				Vertex.connectionID_.push_back(temp_);
			}
			vertexs.push_back(Vertex);
		}
		ar >> Size;
		for (auto i = 0; i < Size; i++) {
			edge Edge;
			ar >> Edge.id_;
			ar >> Edge.color_;
			ar >> Edge.drawID;
			ar >> Edge.type_;
			ar >> Edge.width_;
			ar >> Edge.is_oriented_;
			ar >> Edge.coordinates_[0];
			ar >> Edge.coordinates_[1];
			ar >> Edge.connectID_[0];
			ar >> Edge.connectID_[1];
			ar >> Edge.choosenSide_[0];
			ar >> Edge.choosenSide_[1];
			ar >> temp_;
			switch (temp_)
			{
			case 0:
				Edge.orientation_ = edge::Orientation::right;
				break;
			case 1:
				Edge.orientation_ = edge::Orientation::left;
				break;
			default:
				break;
			}
			edges.push_back(Edge);
		}
		
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void COTS5Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
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

// Поддержка обработчиков поиска
void COTS5Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void COTS5Doc::SetSearchContent(const CString& value)
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

// Диагностика COTS5Doc

#ifdef _DEBUG
void COTS5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void COTS5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
void COTS5Doc::addVertex(int ID, CPoint point) {
	vertex ver(ID, point);
	vertexs.push_back(ver);
}
int COTS5Doc::addEdge(int ID, CPoint point,int figID) {
	edge ed(ID, point,figID);
	edges.push_back(ed);
	return edges.size() - 1;
}
// Команды COTS5Doc


void COTS5Doc::DeleteContents()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDocument::DeleteContents();
}


BOOL COTS5Doc::OnSaveDocument(LPCTSTR lpszPathName)
{

	return CDocument::OnSaveDocument(lpszPathName);
}
