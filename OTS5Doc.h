
// OTS5Doc.h: интерфейс класса COTS5Doc 
//


#pragma once
#include<vector>
#include"edge.h"
#include"vertex.h"

class COTS5Doc : public CDocument
{
protected: // создать только из сериализации
	COTS5Doc() noexcept;
	DECLARE_DYNCREATE(COTS5Doc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~COTS5Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	std::vector<vertex> vertexs;
	std::vector<edge> edges;
public:
	void addVertex(int, CPoint);
	int addEdge(int, CPoint,int);

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
