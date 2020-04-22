// OTS5WaysInformation.cpp: файл реализации
//

#include "pch.h"
#include "OTS5.h"
#include "OTS5WaysInformation.h"
#include "afxdialogex.h"


// Диалоговое окно OTS5WaysInformation

IMPLEMENT_DYNAMIC(OTS5WaysInformation, CDialogEx)

OTS5WaysInformation::OTS5WaysInformation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WAYS_INFORMATION, pParent)
{

}

OTS5WaysInformation::~OTS5WaysInformation()
{
}

void OTS5WaysInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_WAYS, ways_);
}


BEGIN_MESSAGE_MAP(OTS5WaysInformation, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений OTS5WaysInformation


BOOL OTS5WaysInformation::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int item, count = 1;
	CString str, tempstr;
	ways_.InsertColumn(0, L"Номер пути  : ", LVCFMT_LEFT, 100);
	int max = findedWays_[0].size();
	for (auto i = 0; i < findedWays_.size(); i++) {
		if (findedWays_[i].size() > max) {
			max = findedWays_[i].size();
		}
	}
	for (auto i = 0; i < max; i++) {
		str = "ID ребра перехода : ";
		tempstr.Format(_T("%i"), i + 1);
		str += tempstr;
		ways_.InsertColumn(count, str, LVCFMT_LEFT, 100);
		count++;
	}
	for (auto i = findedWays_.size() - 1; i != -1; i--) {
		str.Format(_T("%i"), i + 1);
		item = ways_.InsertItem(0, str);
		for (auto j = 0; j < findedWays_[i].size(); j++) {
			str.Format(_T("%i"), findedWays_[i][j]);
			ways_.SetItemText(item, j + 1, str);
		}
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void OTS5WaysInformation::SetWays(std::vector<std::vector<int>> ways) {
	findedWays_ = ways;
}
