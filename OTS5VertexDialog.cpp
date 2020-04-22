// OTS5VertexDialog.cpp: файл реализации
//

#include "pch.h"
#include "OTS5.h"
#include "OTS5VertexDialog.h"
#include "afxdialogex.h"


// Диалоговое окно OTS5VertexDialog

IMPLEMENT_DYNAMIC(OTS5VertexDialog, CDialogEx)

OTS5VertexDialog::OTS5VertexDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_VERTEX_NAME, pParent)
	, vertexName_(_T(""))
{

}

OTS5VertexDialog::~OTS5VertexDialog()
{
}

void OTS5VertexDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NAME, nameControl_);
	DDX_Text(pDX, IDC_EDIT_NAME, vertexName_);
}


BEGIN_MESSAGE_MAP(OTS5VertexDialog, CDialogEx)
END_MESSAGE_MAP()

void OTS5VertexDialog::SetName(CString name) {
	vertexName_ = name;
}

CString OTS5VertexDialog::GetName() {
	return vertexName_;
}

// Обработчики сообщений OTS5VertexDialog


BOOL OTS5VertexDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void OTS5VertexDialog::OnOK()
{
	UpdateData();

	CDialogEx::OnOK();
}
