#pragma once

#include "Child_Dlg1.h"

// Resize_Dlg 对话框

class Resize_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Resize_Dlg)

public:
	Resize_Dlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Resize_Dlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Resize_Dlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_l;
	int m_h;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	Child_Dlg1* m_pParentDlg;  // 指向父对话框的指针
};
