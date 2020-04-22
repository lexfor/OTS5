#include <vector>

// Диалоговое окно OTS5InformationDialog

class OTS5InformationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OTS5InformationDialog)

public:
	OTS5InformationDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~OTS5InformationDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	int numOfVertex_;
	int numOfEdge_;
	std::vector<int> vertex_;
	std::vector<int> vertexPow_;
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	void SetVertexNum(int);
	void SetEdgeNum(int);
	void SetVertex(std::vector<int>);
	void SetVertexPow(std::vector<int>);
private:
	CListCtrl listInformationControl_;

};
