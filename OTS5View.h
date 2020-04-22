
// OTS5View.h: интерфейс класса COTS5View
//

#pragma once
#include<vector>
#include"edge.h"
#include"vertex.h"

class COTS5View : public CView
{
protected: // создать только из сериализации
	COTS5View() noexcept;
	DECLARE_DYNCREATE(COTS5View)

// Атрибуты
public:
	COTS5Doc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~COTS5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	int ID;
	enum class Flags
	{
		draw,move,connect,ways,distance,nothing
	}flag_;
	int current_;
	CPoint moveCoordinates[2];
	bool is_connect;
	int selected_;
	int wayVertex_[2];
	std::vector<std::vector<int>> ways_;
	bool is_ok;
	COLORREF grafColor_;
public:
	afx_msg void OnEliipse();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnConnect();
	int Find();
	afx_msg void OnDeleteVertex();
	afx_msg void OnDeleteEdge();
	afx_msg void OnNonoriented();
	afx_msg void OnOriented();
	afx_msg void OnSwap();
	afx_msg void OnVertexName();
	afx_msg void OnVertexColor();
	afx_msg void OnEdgeColor();
	afx_msg void OnVertexView();
	afx_msg void OnInformation();
	afx_msg void OnVertexProperties();
	afx_msg void OnAdjacency();
	std::vector<std::vector<int>> GetAdjacencyMatrix();
	afx_msg void OnCheckGraf();
	afx_msg void OnMakeBinaryTree();
	void ConnecteVertex(int firstVertex, int secondVertex);
	afx_msg void OnChekCycle();
	bool GoToVertex(std::vector<int>& checked_,int,int);
	afx_msg void OnWays();
	void FindPath();
	bool CheckEdge(std::vector<int>&, std::vector<int>&,int,int);
	afx_msg void OnFindDistance();
	void FindDistance();
	afx_msg void OnPaintingGraf();
};

#ifndef _DEBUG  // версия отладки в OTS5View.cpp
inline COTS5Doc* COTS5View::GetDocument() const
   { return reinterpret_cast<COTS5Doc*>(m_pDocument); }
#endif

