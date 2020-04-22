// OTS5VertexInformation.cpp: файл реализации
//

#include "pch.h"
#include "OTS5.h"
#include "OTS5VertexInformation.h"
#include "afxdialogex.h"


// Диалоговое окно OTS5VertexInformation

IMPLEMENT_DYNAMIC(OTS5VertexInformation, CDialogEx)

OTS5VertexInformation::OTS5VertexInformation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VERTEX, pParent)
	, vertexID_(0)
	, vertexPow_(0)
{

}

OTS5VertexInformation::~OTS5VertexInformation()
{
}

void OTS5VertexInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, vertexID_);
	DDX_Text(pDX, IDC_EDIT_POW, vertexPow_);
}


BEGIN_MESSAGE_MAP(OTS5VertexInformation, CDialogEx)
END_MESSAGE_MAP()

// Обработчики сообщений OTS5VertexInformation


BOOL OTS5VertexInformation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void OTS5VertexInformation::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialogEx::OnOK();
}

void OTS5VertexInformation::SetID(int id) {
	vertexID_ = id;
}

void OTS5VertexInformation::SetPow(int verPow) {
	vertexPow_ = verPow;
}