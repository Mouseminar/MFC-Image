#pragma once


// DBD_Dlg 对话框

class DBD_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(DBD_Dlg)

public:
	DBD_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DBD_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DBD_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_dbd;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
