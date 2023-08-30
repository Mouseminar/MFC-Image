#pragma once


// GSZH_Dlg 对话框

class GSZH_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(GSZH_Dlg)

public:
	GSZH_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GSZH_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GSZH_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	CString m_name;
	CString m_form;
};
