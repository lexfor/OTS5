// OTS5InformationDialog.cpp: файл реализации
//

#include "pch.h"
#include "OTS5.h"
#include "OTS5InformationDialog.h"
#include "afxdialogex.h"


// Диалоговое окно OTS5InformationDialog

IMPLEMENT_DYNAMIC(OTS5InformationDialog, CDialogEx)

OTS5InformationDialog::OTS5InformationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFORMATION, pParent)
	, numOfVertex_(0)
	, numOfEdge_(0)
{

}

OTS5InformationDialog::~OTS5InformationDialog()
{
}

void OTS5InformationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VERTEX_NUM, numOfVertex_);
	DDX_Text(pDX, IDC_EDIT_EDGE_NUM, numOfEdge_);
	DDX_Control(pDX, IDC_LIST_INFORMATION, listInformationControl_);
}


BEGIN_MESSAGE_MAP(OTS5InformationDialog, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений OTS5InformationDialog


BOOL OTS5InformationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int item;
	CString str;
	listInformationControl_.InsertColumn(0, L"ID вершины", LVCFMT_LEFT, 150);
	listInformationControl_.InsertColumn(1, L"Степень", LVCFMT_LEFT, 150);
	for (auto i = 0; i < vertex_.size() && i < vertexPow_.size(); i++) {
		str.Format(_T("%i"), vertex_[i]);
		item = listInformationControl_.InsertItem(0, str);
		str.Format(_T("%i"), vertexPow_[i]);
		listInformationControl_.SetItemText(item,1,str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void OTS5InformationDialog::OnOK()
{
	

	CDialogEx::OnOK();
}

void OTS5InformationDialog::SetVertexNum(int num) {
	numOfVertex_ = num;
}

void OTS5InformationDialog::SetEdgeNum(int num) {
	numOfEdge_ = num;
}

void OTS5InformationDialog::SetVertex(std::vector<int> vertex) {
	vertex_ = vertex;
}

void OTS5InformationDialog::SetVertexPow(std::vector<int> pows) {
	vertexPow_ = pows;
}