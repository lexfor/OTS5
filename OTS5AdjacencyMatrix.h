#pragma once
#include<vector>

// Диалоговое окно OTS5AdjacencyMatrix

class OTS5AdjacencyMatrix : public CDialogEx
{
	DECLARE_DYNAMIC(OTS5AdjacencyMatrix)

public:
	OTS5AdjacencyMatrix(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~OTS5AdjacencyMatrix();


// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADJACENCY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl adjacencyMatrix_;
	std::vector<std::vector<int>> matrix_;
	std::vector<int> vertexID_;
public:
	void SetAdjacencyMatrix(std::vector<std::vector<int>> adjacency);
	virtual BOOL OnInitDialog();
	void SetID(std::vector<int>);
};
