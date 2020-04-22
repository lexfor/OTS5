
// OTS5View.cpp: реализация класса COTS5View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "OTS5.h"
#endif

#include "OTS5Doc.h"
#include "OTS5View.h"
#include "OTS5VertexDialog.h"
#include <afxcolordialog.h>
#include "OTS5InformationDialog.h"
#include "OTS5VertexInformation.h"
#include "OTS5AdjacencyMatrix.h"
#include "OTS5WaysInformation.h"
#include <thread>
#include <chrono>
#include <set>
#include<algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COTS5View

IMPLEMENT_DYNCREATE(COTS5View, CView)

BEGIN_MESSAGE_MAP(COTS5View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COTS5View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ELIIPSE, &COTS5View::OnEliipse)
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CONNECT, &COTS5View::OnConnect)
	ON_COMMAND(ID_DELETE_VERTEX, &COTS5View::OnDeleteVertex)
	ON_COMMAND(ID_DELETE_EDGE, &COTS5View::OnDeleteEdge)
	ON_COMMAND(ID_NONORIENTED, &COTS5View::OnNonoriented)
	ON_COMMAND(ID_ORIENTED, &COTS5View::OnOriented)
	ON_COMMAND(ID_SWAP, &COTS5View::OnSwap)
	ON_COMMAND(ID_VERTEX_NAME, &COTS5View::OnVertexName)
	ON_COMMAND(ID_VERTEX_COLOR, &COTS5View::OnVertexColor)
	ON_COMMAND(ID_EDGE_COLOR, &COTS5View::OnEdgeColor)
	ON_COMMAND(ID_VERTEX_VIEW, &COTS5View::OnVertexView)
	ON_COMMAND(ID_INFORMATION, &COTS5View::OnInformation)
	ON_COMMAND(ID_VERTEX_PROPERTIES, &COTS5View::OnVertexProperties)
	ON_COMMAND(ID_ADJACENCY, &COTS5View::OnAdjacency)
	ON_COMMAND(ID_CHECK_GRAF, &COTS5View::OnCheckGraf)
	ON_COMMAND(ID_MAKE_BINARY_TREE, &COTS5View::OnMakeBinaryTree)
	ON_COMMAND(ID_CHEK_CYCLE, &COTS5View::OnChekCycle)
	ON_COMMAND(ID_WAYS, &COTS5View::OnWays)
	ON_COMMAND(ID_FIND_DISTANCE, &COTS5View::OnFindDistance)
	ON_COMMAND(ID_PAINTING_GRAF, &COTS5View::OnPaintingGraf)
END_MESSAGE_MAP()

// Создание или уничтожение COTS5View

COTS5View::COTS5View() noexcept
{
	// TODO: добавьте код создания
	ID = 0;
	current_ = -1;
	is_connect = false;
	for (auto i = 0; i < 2;i++) {
		wayVertex_[i] = -1;
	}
}

COTS5View::~COTS5View()
{
}

BOOL COTS5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование COTS5View

void COTS5View::OnDraw(CDC* /*pDC*/)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	HDC dc = ::GetDC(m_hWnd);
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].Draw(dc);
	}
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		pDoc->vertexs[i].Draw(dc);
	}
	::ReleaseDC(m_hWnd, dc);
	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать COTS5View


void COTS5View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COTS5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void COTS5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void COTS5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

//void COTS5View::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void COTS5View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика COTS5View

#ifdef _DEBUG
void COTS5View::AssertValid() const
{
	CView::AssertValid();
}

void COTS5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COTS5Doc* COTS5View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COTS5Doc)));
	return (COTS5Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений COTS5View


void COTS5View::OnLButtonDown(UINT nFlags, CPoint point)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (flag_ == Flags::draw) {
		HDC dc = ::GetDC(m_hWnd);
		CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
		SelectObject(dc, pen);
		Ellipse(dc, point.x - 10, point.y - 10, point.x + 10, point.y + 10);
		pDoc->addVertex(ID, point);
		ID++;
		::ReleaseDC(m_hWnd, dc);
	}
	if (flag_ == Flags::move) {
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].Check(point)) {
				current_ = pDoc->vertexs[i].id_;
				moveCoordinates[0] = point;
				pDoc->UpdateAllViews(nullptr);
				return;
			}
		}
	}
	if (flag_ == Flags::connect) {
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].Check(point)) {
				pDoc->vertexs[i].connectionID_.push_back(ID);
				current_ = pDoc->addEdge(ID, pDoc->vertexs[i].coordinates_,pDoc->vertexs[i].id_);
				is_connect = true;
			}
		}
	}
	if (flag_ == Flags::ways) {
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].Check(point)) {
				if (wayVertex_[0] == -1) {
					wayVertex_[0] = pDoc->vertexs[i].id_;
					pDoc->vertexs[i].tempColor_ = pDoc->vertexs[i].color_;
					pDoc->vertexs[i].color_ = RGB(255, 0, 0);
					pDoc->vertexs[i].width_ = 10;
					pDoc->UpdateAllViews(nullptr);
					return;
				}
				if (wayVertex_[1] == -1) {
					wayVertex_[1] = pDoc->vertexs[i].id_;
					if (wayVertex_[1] == wayVertex_[0]) {
						AfxMessageBox(L"Вы выбрали одну и ту же вершину !");
						wayVertex_[1] = -1;
						return;
					}
					else {
						flag_ = Flags::nothing;
					}
					pDoc->vertexs[i].tempColor_ = pDoc->vertexs[i].color_;
					pDoc->vertexs[i].color_ = RGB(255, 0, 0);
					pDoc->vertexs[i].width_ = 10;
					pDoc->UpdateAllViews(nullptr);
					FindPath();
					for (auto j = 0; j < pDoc->vertexs.size(); j++) {
						if (pDoc->vertexs[j].id_ == wayVertex_[0] || pDoc->vertexs[j].id_ == wayVertex_[1]) {
							pDoc->vertexs[j].color_ = pDoc->vertexs[j].tempColor_;
							pDoc->vertexs[j].width_ = 5;
						}
					}
					for (auto j = 0; j < 2; j++) {
						wayVertex_[j] = -1;
					}
					ways_.clear();
				}
			}
		}
	}
	if (flag_ == Flags::distance) {
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].Check(point)) {
				if (wayVertex_[0] == -1) {
					wayVertex_[0] = pDoc->vertexs[i].id_;
					pDoc->vertexs[i].tempColor_ = pDoc->vertexs[i].color_;
					pDoc->vertexs[i].color_ = RGB(255, 0, 0);
					pDoc->vertexs[i].width_ = 10;
					pDoc->UpdateAllViews(nullptr);
					return;
				}
				if (wayVertex_[1] == -1) {
					wayVertex_[1] = pDoc->vertexs[i].id_;
					if (wayVertex_[1] == wayVertex_[0]) {
						AfxMessageBox(L"Вы выбрали одну и ту же вершину !");
						wayVertex_[1] = -1;
						return;
					}
					else {
						flag_ = Flags::nothing;
					}
					pDoc->vertexs[i].tempColor_ = pDoc->vertexs[i].color_;
					pDoc->vertexs[i].color_ = RGB(255, 0, 0);
					pDoc->vertexs[i].width_ = 10;
					pDoc->UpdateAllViews(nullptr);
					FindDistance();
					for (auto j = 0; j < pDoc->vertexs.size(); j++) {
						if (pDoc->vertexs[j].id_ == wayVertex_[0] || pDoc->vertexs[j].id_ == wayVertex_[1]) {
							pDoc->vertexs[j].color_ = pDoc->vertexs[j].tempColor_;
							pDoc->vertexs[j].width_ = 5;
						}
					}
					for (auto j = 0; j < 2; j++) {
						wayVertex_[j] = -1;
					}
					ways_.clear();
				}
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void COTS5View::OnEliipse()
{
	flag_ = Flags::draw;
}


void COTS5View::OnRButtonUp(UINT nFlags, CPoint point)
{
	COTS5Doc* pDoc = GetDocument();
	CMenu menu, lineMenu;
	VERIFY(menu.LoadMenu(IDR_MENU1));
	VERIFY(lineMenu.LoadMenu(IDR_MENU2));
	CMenu* pPopup = menu.GetSubMenu(0);
	CMenu* pPopupLine = lineMenu.GetSubMenu(0);
	ASSERT_VALID(pDoc);
	flag_ = Flags::move;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].Check(point)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopup->TrackPopupMenuEx(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
			pPopup->DestroyMenu();
			menu.DestroyMenu();
			selected_ = i;
			return;
		}
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		if (pDoc->edges[i].Check(point)) {
			CMenu* pPopup = menu.GetSubMenu(0);
			pPopupLine->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this, NULL);
			pPopupLine->DestroyMenu();
			lineMenu.DestroyMenu();
			selected_ = i;
			return;
		}
	}
	//CView::OnRButtonUp(nFlags, point);
}


void COTS5View::OnMouseMove(UINT nFlags, CPoint point)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (flag_ == Flags::move && current_ > -1) {
		std::vector<int>connectID;
		connectID = pDoc->vertexs[Find()].connectionID_;
		moveCoordinates[1] = point;
		pDoc->vertexs[Find()].Move(moveCoordinates);
		for (auto j = 0; j < connectID.size(); j++) {
			for (auto i = 0; i < pDoc->edges.size(); i++) {
				if (pDoc->edges[i].id_ == connectID[j]) {
					pDoc->edges[i].Move(moveCoordinates, current_);
				}
			}
		}
		moveCoordinates[0] = point;
		pDoc->UpdateAllViews(nullptr);
	}
}


void COTS5View::OnLButtonUp(UINT nFlags, CPoint point)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (flag_ == Flags::move && current_ > -1) {
		std::vector<int>connectID;
		connectID = pDoc->vertexs[Find()].connectionID_;
		moveCoordinates[1] = point;
		pDoc->vertexs[Find()].Move(moveCoordinates);
		for (auto j = 0; j < connectID.size(); j++) {
			for (auto i = 0; i < pDoc->edges.size(); i++) {
				if (pDoc->edges[i].id_ == connectID[j]) {
					pDoc->edges[i].Move(moveCoordinates, current_);
				}
			}
		}
		current_ = -1;
	}
	if (flag_ == Flags::connect && is_connect) {
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].Check(point)) {
				pDoc->vertexs[i].connectionID_.push_back(ID);
				pDoc->edges[current_].coordinates_[1] = pDoc->vertexs[i].coordinates_;
				pDoc->edges[current_].connectID_[1] = pDoc->vertexs[i].id_;
				current_ = -1;
				ID++;
				is_connect = false;
				pDoc->UpdateAllViews(nullptr);
				return;
			}
		}
		for (auto i = 0; i < pDoc->vertexs.size(); i++) {
			if (pDoc->vertexs[i].id_ == pDoc->edges[current_].connectID_[0]) {
				pDoc->vertexs[i].connectionID_.pop_back();
				break;
			}
		}
		pDoc->edges.erase(pDoc->edges.begin() + current_);
		current_ = -1;
		is_connect = false;
	}
	pDoc->UpdateAllViews(nullptr);
	CView::OnLButtonUp(nFlags, point);
}


void COTS5View::OnPaint()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect client;
	::GetClientRect(m_hWnd, &client);
	PAINTSTRUCT ps;
	::BeginPaint(m_hWnd, &ps);
	HDC dc = ::GetDC(m_hWnd);
	HDC back_buffer = ::CreateCompatibleDC(dc);
	HBITMAP hbmp = ::CreateCompatibleBitmap(dc, client.Width(), client.Height());
	::SelectObject(back_buffer, hbmp);
	::FillRect(back_buffer, &client, (HBRUSH)GetStockObject(WHITE_BRUSH));


	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].Draw(back_buffer);
	}
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		pDoc->vertexs[i].Draw(back_buffer);
	}
	::BitBlt(dc, 0, 0, client.Width(), client.Height(), back_buffer, 0, 0, SRCCOPY);
	::EndPaint(m_hWnd, &ps);
	::ReleaseDC(m_hWnd, back_buffer);
	::ReleaseDC(m_hWnd, dc);
	::DeleteObject(hbmp);
	::DeleteDC(back_buffer);
}


BOOL COTS5View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	return 1;
}


void COTS5View::OnConnect()
{
	flag_ = Flags::connect;
}

int COTS5View::Find() {
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (auto i = 0; i < pDoc->vertexs.size();i++) {
		if (current_ == pDoc->vertexs[i].id_) {
			return i;
		}
	}
	return -1;
}


void COTS5View::OnDeleteVertex()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int temp;
	current_ = selected_;
	temp = pDoc->vertexs[current_].id_;
	pDoc->vertexs.erase(pDoc->vertexs.begin() + current_);
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		if (pDoc->edges[i].connectID_[0] == temp) {
			pDoc->edges.erase(pDoc->edges.begin() + i);
			i--;
			continue;
		}
		if (pDoc->edges[i].connectID_[1] == temp) {
			pDoc->edges.erase(pDoc->edges.begin() + i);
			i--;
		}
	}
	current_ = -1;
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnDeleteEdge()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int temp;
	current_ = selected_;
	temp = pDoc->edges[current_].id_;
	pDoc->edges.erase(pDoc->edges.begin() + current_);
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		for (auto j = 0; j < pDoc->vertexs[i].connectionID_.size(); j++) {
			if (pDoc->vertexs[i].connectionID_[j] == temp) {
				pDoc->vertexs[i].connectionID_.erase(pDoc->vertexs[i].connectionID_.begin() + j);
				j--;
				continue;
			}
		}
	}
	current_ = -1;
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnNonoriented()
{
	current_ = selected_;
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->edges[current_].MakeNonOrient();
	pDoc->UpdateAllViews(nullptr);
	current_ = -1;
}


void COTS5View::OnOriented()
{
	current_ = selected_;
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->edges[current_].MakeOrient();
	pDoc->UpdateAllViews(nullptr);
	current_ = -1;
}


void COTS5View::OnSwap()
{
	current_ = selected_;
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->edges[current_].Swap();
	pDoc->UpdateAllViews(nullptr);
	current_ = -1;
}


void COTS5View::OnVertexName()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	OTS5VertexDialog dialog;
	dialog.SetName(pDoc->vertexs[selected_].vertexName_);
	dialog.DoModal();
	pDoc->vertexs[selected_].vertexName_ = dialog.GetName();
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnVertexColor()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorDialog dialog;
	dialog.DoModal();
	pDoc->vertexs[selected_].color_ = dialog.GetColor();
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnEdgeColor()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorDialog dialog;
	dialog.DoModal();
	pDoc->edges[selected_].color_ = dialog.GetColor();
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnVertexView()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	switch (pDoc->vertexs[selected_].vertexType_)
	{
	case vertex::Type::constant:
		pDoc->vertexs[selected_].vertexType_ = vertex::Type::temp;
		break;
	case vertex::Type::temp:
		pDoc->vertexs[selected_].vertexType_ = vertex::Type::constant;
	default:
		break;
	}
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::OnInformation()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<int> vertexID, vertexPow;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		vertexID.push_back(pDoc->vertexs[i].id_);
		vertexPow.push_back(pDoc->vertexs[i].connectionID_.size());
	}
	OTS5InformationDialog dialog;
	dialog.SetVertexNum(pDoc->vertexs.size());
	dialog.SetEdgeNum(pDoc->edges.size());
	dialog.SetVertex(vertexID);
	dialog.SetVertexPow(vertexPow);
	dialog.DoModal();
}


void COTS5View::OnVertexProperties()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	OTS5VertexInformation dialog;
	dialog.SetID(pDoc->vertexs[selected_].id_);
	dialog.SetPow(pDoc->vertexs[selected_].connectionID_.size());
	dialog.DoModal();
}


void COTS5View::OnAdjacency()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<int> vertexID;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		vertexID.push_back(pDoc->vertexs[i].id_);
	}
	std::vector<std::vector<int>> adjacencyMatrix_ = GetAdjacencyMatrix();
	OTS5AdjacencyMatrix dialog;
	dialog.SetAdjacencyMatrix(adjacencyMatrix_);
	dialog.SetID(vertexID);
	dialog.DoModal();
}


std::vector<std::vector<int>> COTS5View::GetAdjacencyMatrix()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<std::vector<int>> adjacencyMatrix_;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		std::vector<int> empty_;
		for (int j = 0; j < pDoc->vertexs.size(); j++) {
			empty_.push_back(0);
		}
		for (int j = 0; j < pDoc->edges.size(); j++) {
			if (pDoc->edges[j].connectID_[0] == pDoc->vertexs[i].id_) {
				for (auto k = 0; k < pDoc->vertexs.size(); k++) {
					if (pDoc->edges[j].connectID_[1] == pDoc->vertexs[k].id_) {
						empty_[k] = 1;
					}
				}
			}
			if (pDoc->edges[j].connectID_[1] == pDoc->vertexs[i].id_) {
				for (auto k = 0; k < pDoc->vertexs.size(); k++) {
					if (pDoc->edges[j].connectID_[0] == pDoc->vertexs[k].id_) {
						empty_[k] = 1;
					}
				}
			}
		}
		adjacencyMatrix_.push_back(empty_);
	}
	return adjacencyMatrix_;
}


void COTS5View::OnCheckGraf()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	bool check = false;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].connectionID_.size() == 0) {
			break;
		}
		if (pDoc->vertexs[i].connectionID_.size() % 2 != 0) {
			break;
		}
		if (i == pDoc->vertexs.size() - 1) {
			check = true;
		}
	}
	if (check) {
		AfxMessageBox(L"Данный граф является Эйлеровым графом", MB_OK | MB_ICONINFORMATION);
	}
	else{
		AfxMessageBox(L"Данный граф не является Эйлеровым графом", MB_OK | MB_ICONSTOP);
		}
}


void COTS5View::OnMakeBinaryTree()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<int> IDVector;
	std::vector<int>subVector;
	int temp,secondTemp;
	pDoc->edges.clear();
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		pDoc->vertexs[i].connectionID_.clear();
	}
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		IDVector.push_back(pDoc->vertexs[i].id_);
	}
	std::sort(IDVector.begin(), IDVector.end());
	temp = IDVector.size()/2;
	secondTemp = temp;
	for (auto i = temp + 1; i < IDVector.size(); i++) {
		ConnecteVertex(secondTemp, i);
		secondTemp = i;
	}
	for (auto i = temp - 1; i > -1; i--) {
		ConnecteVertex(secondTemp, i);
		secondTemp = i;
	}
	pDoc->UpdateAllViews(nullptr);
}


void COTS5View::ConnecteVertex(int firstVertex, int secondVertex)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].id_ == firstVertex) {
			pDoc->vertexs[i].connectionID_.push_back(ID);
			current_ = pDoc->addEdge(ID, pDoc->vertexs[i].coordinates_, pDoc->vertexs[i].id_);
		}
	}
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].id_ == secondVertex) {
			pDoc->vertexs[i].connectionID_.push_back(ID);
			pDoc->edges[current_].coordinates_[1] = pDoc->vertexs[i].coordinates_;
			pDoc->edges[current_].connectID_[1] = pDoc->vertexs[i].id_;
			current_ = -1;
			ID++;
		}
	}
}


void COTS5View::OnChekCycle()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString str, temp;
	bool check = false;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].connectionID_.size() == 0) {
			break;
		}
		if (pDoc->vertexs[i].connectionID_.size() % 2 != 0) {
			break;
		}
		if (i == pDoc->vertexs.size() - 1) {
			check = true;
		}
	}
	if (!check) {
		AfxMessageBox(L"В данном графе нет Эйлеровых циклов", MB_OK | MB_ICONSTOP);
		return;
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].drawID = true;
	}
	std::vector<int> checked_;
	checked_.push_back(pDoc->vertexs[0].connectionID_[0]);
	GoToVertex(checked_, pDoc->vertexs[0].connectionID_[0], pDoc->vertexs[0].id_);
	str = "Эйлеров цикл найден : ";
	for (auto i = 0; i < checked_.size(); i++) {
		temp.Format(_T("%i"), checked_[i]);
		str += temp;
		str += " , ";
	}
	AfxMessageBox(str);
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].color_ = pDoc->edges[i].tempColor_;
		pDoc->edges[i].width_ = 5;
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].drawID = false;
	}
}


bool COTS5View::GoToVertex(std::vector<int>& checked_,int connectionID, int vertexID)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int currentVertex;
	bool is_checked_;
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		if (pDoc->edges[i].id_ == connectionID) {
			pDoc->edges[i].tempColor_ = pDoc->edges[i].color_;
			pDoc->edges[i].color_ = RGB(255,0,0);
			pDoc->edges[i].width_ = 10;
			if (pDoc->edges[i].connectID_[0] == vertexID) {
				currentVertex = pDoc->edges[i].connectID_[1];
			}else{
				currentVertex = pDoc->edges[i].connectID_[0];
				break;
			}
		}
	}
	if (checked_.size() == pDoc->edges.size()) {
		return true;
	}
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].id_ == currentVertex) {
			for (auto j = 0; j < pDoc->vertexs[i].connectionID_.size(); j++) {
				is_checked_ = true;
				for (auto k = 0; k < checked_.size(); k++) {
					if (pDoc->vertexs[i].connectionID_[j] == checked_[k]) {
						is_checked_ = false;
					}
				}
				if (is_checked_) {
					OnDraw(GetWindowDC());
					pDoc->UpdateAllViews(nullptr);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					checked_.push_back(pDoc->vertexs[i].connectionID_[j]);
					return GoToVertex(checked_, pDoc->vertexs[i].connectionID_[j], pDoc->vertexs[i].id_);
					
				}
			}
		}
	}
	return false;
}


void COTS5View::OnWays()
{
	flag_ = Flags::ways;
}


void COTS5View::FindPath()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<int> inWay_;
	std::vector<int> checked_;
	is_ok = false;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].id_ == wayVertex_[0]) {
			for (auto j = 0; j < pDoc->vertexs[i].connectionID_.size(); j++) {
				inWay_.push_back(pDoc->vertexs[i].connectionID_[j]);
				checked_.push_back(pDoc->vertexs[i].connectionID_[j]);
				if (CheckEdge(inWay_, checked_, pDoc->vertexs[i].connectionID_[j], pDoc->vertexs[i].id_)) {
					is_ok = true;
					ways_.push_back(inWay_);
					inWay_.pop_back();
					checked_.pop_back();
				}
				else {
					inWay_.pop_back();
					checked_.pop_back();
				}
			}
		}
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].drawID = true;
	}
	if (is_ok) {
		OTS5WaysInformation dialog;
		dialog.SetWays(ways_);
		dialog.DoModal();
		CString str,tempStr;
		std::vector<int> min;
		min = ways_[0];
		for (auto i = 0; i < ways_.size(); i++) {
			if (ways_[i].size() < min.size()) {
				min = ways_[i];
			}
		}
		str = "Минимальный путь : ";
		for (auto i = 0; i < min.size(); i++) {
			tempStr.Format(_T("%i"), min[i]);
			str += tempStr;
			if (i < min.size() - 1) {
				str += ",";
			}
		}
		AfxMessageBox(str);
	}
	else {
		AfxMessageBox(L"Ниодного пути не найдено");
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].drawID = false;
	}
}


bool COTS5View::CheckEdge(std::vector<int>& inWay, std::vector<int>& checked,int connection,int vertexID)
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int currentVertex;
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		if (pDoc->edges[i].id_ == connection) {
			if (pDoc->edges[i].connectID_[0] == vertexID) {
				currentVertex = pDoc->edges[i].connectID_[1];
			}
			else {
				currentVertex = pDoc->edges[i].connectID_[0];
			}
			break;
		}
	}
	if (currentVertex == wayVertex_[1]) {
		return true;
	}
	for (auto k = 0; k < pDoc->vertexs.size(); k++) {
		if (pDoc->vertexs[k].id_ == currentVertex) {
			for (auto i = 0; i < pDoc->vertexs[k].connectionID_.size(); i++) {
				bool isCheck = true;
				for (auto j = 0; j < checked.size(); j++) {
					if (pDoc->vertexs[k].connectionID_[i] == checked[j]) {
						isCheck = false;
					}
				}
				if (isCheck) {
					inWay.push_back(pDoc->vertexs[k].connectionID_[i]);
					checked.push_back(pDoc->vertexs[k].connectionID_[i]);
					if (CheckEdge(inWay, checked, pDoc->vertexs[k].connectionID_[i], pDoc->vertexs[k].id_)) {
						is_ok = true;
						ways_.push_back(inWay);
						inWay.pop_back();
						checked.pop_back();
					}
					else {
						inWay.pop_back();
						checked.pop_back();
					}
				}
			}
			break;
		}
	}
	return false;
}


void COTS5View::OnFindDistance()
{
	flag_ = Flags::distance;
}


void COTS5View::FindDistance()
{

	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	std::vector<int> inWay_;
	std::vector<int> checked_;
	is_ok = false;
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		if (pDoc->vertexs[i].id_ == wayVertex_[0]) {
			for (auto j = 0; j < pDoc->vertexs[i].connectionID_.size(); j++) {
				inWay_.push_back(pDoc->vertexs[i].connectionID_[j]);
				checked_.push_back(pDoc->vertexs[i].connectionID_[j]);
				if (CheckEdge(inWay_, checked_, pDoc->vertexs[i].connectionID_[j], pDoc->vertexs[i].id_)) {
					is_ok = true;
					ways_.push_back(inWay_);
					inWay_.pop_back();
					checked_.pop_back();
				}
				else {
					inWay_.pop_back();
					checked_.pop_back();
				}
			}
		}
	}
	if (is_ok) {
		CString str, tempStr;
		std::vector<int> min;
		min = ways_[0];
		for (auto i = 0; i < ways_.size(); i++) {
			if (ways_[i].size() < min.size()) {
				min = ways_[i];
			}
		}
		str = "Расстояние : ";
		tempStr.Format(_T("%i"), min.size());
		str += tempStr;
		str += " ребра ";
		AfxMessageBox(str);
	}
	else {
		AfxMessageBox(L"Между вершинами нельзя вычислить расстояние ");
	}
}


void COTS5View::OnPaintingGraf()
{
	COTS5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CColorDialog dialog;
	dialog.DoModal();
	grafColor_= dialog.GetColor();
	for (auto i = 0; i < pDoc->vertexs.size(); i++) {
		pDoc->vertexs[i].color_ = grafColor_;
	}
	for (auto i = 0; i < pDoc->edges.size(); i++) {
		pDoc->edges[i].color_ = grafColor_;
	}
	pDoc->UpdateAllViews(nullptr);
	pDoc->UpdateAllViews(nullptr);
}
