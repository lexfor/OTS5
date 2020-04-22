#pragma once


// Диалоговое окно OTS5VertexDialog

class OTS5VertexDialog : public CDialogEx
{
	DECLARE_DYNAMIC(OTS5VertexDialog)

public:
	OTS5VertexDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~OTS5VertexDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VERTEX_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CEdit nameControl_;
	CString vertexName_;
public:
	void SetName(CString);
	CString GetName();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
