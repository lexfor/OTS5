#pragma once
#include <vector>

// Диалоговое окно OTS5WaysInformation

class OTS5WaysInformation : public CDialogEx
{
	DECLARE_DYNAMIC(OTS5WaysInformation)

public:
	OTS5WaysInformation(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~OTS5WaysInformation();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WAYS_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl ways_;
	std::vector<std::vector<int>> findedWays_;
public:
	virtual BOOL OnInitDialog();
	void SetWays(std::vector<std::vector<int>>);
};
