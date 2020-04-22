// OTS5AdjacencyMatrix.cpp: файл реализации
//

#include "pch.h"
#include "OTS5.h"
#include "OTS5AdjacencyMatrix.h"
#include "afxdialogex.h"


// Диалоговое окно OTS5AdjacencyMatrix

IMPLEMENT_DYNAMIC(OTS5AdjacencyMatrix, CDialogEx)

OTS5AdjacencyMatrix::OTS5AdjacencyMatrix(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADJACENCY, pParent)
{

}

OTS5AdjacencyMatrix::~OTS5AdjacencyMatrix()
{
}

void OTS5AdjacencyMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ADJACENCY, adjacencyMatrix_);
}


BEGIN_MESSAGE_MAP(OTS5AdjacencyMatrix, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений OTS5AdjacencyMatrix


void OTS5AdjacencyMatrix::SetAdjacencyMatrix(std::vector<std::vector<int>> adjacency)
{
	matrix_ = adjacency;
}

void OTS5AdjacencyMatrix::SetID(std::vector<int> vectorsID)
{
	vertexID_ = vectorsID;
}

BOOL OTS5AdjacencyMatrix::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int item,count = 1;
	CString str,tempstr;
	adjacencyMatrix_.InsertColumn(0, L"ID вершин : ", LVCFMT_LEFT, 100);
	for (auto i = 0; i < vertexID_.size(); i++) {
		str = "ID : ";
		tempstr.Format(_T("%i"), vertexID_[i]);
		str += tempstr;
		adjacencyMatrix_.InsertColumn(count, str, LVCFMT_LEFT, 100);
		count++;
	}
	for (auto i = matrix_.size() - 1; i != -1; i--) {
		str.Format(_T("%i"), vertexID_[i]);
		item = adjacencyMatrix_.InsertItem(0, str);
		for (auto j = 0; j < matrix_[i].size(); j++) {
			str.Format(_T("%i"), matrix_[i][j]);
			adjacencyMatrix_.SetItemText(item, j + 1, str);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
