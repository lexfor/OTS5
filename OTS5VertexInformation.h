#pragma once


// Диалоговое окно OTS5VertexInformation

class OTS5VertexInformation : public CDialogEx
{
	DECLARE_DYNAMIC(OTS5VertexInformation)

public:
	OTS5VertexInformation(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~OTS5VertexInformation();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERTEX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	int vertexID_;
	int vertexPow_;
public:
	void SetID(int);
	void SetPow(int);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
