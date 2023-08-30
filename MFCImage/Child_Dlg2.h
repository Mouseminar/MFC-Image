#pragma once

#include "CGlobal.h"

// Child_Dlg2 窗体视图

class Child_Dlg2 : public CFormView
{
	DECLARE_DYNCREATE(Child_Dlg2)

protected:
	Child_Dlg2();           // 动态创建所使用的受保护的构造函数
	virtual ~Child_Dlg2();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Child_Dlg2 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
};


