#pragma once


// LD_Dlg 对话框

class LD_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(LD_Dlg)

public:
	LD_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LD_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LD_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	int m_ld;
	afx_msg void OnBnClickedButton1();
};
