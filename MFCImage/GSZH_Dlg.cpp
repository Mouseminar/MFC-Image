// GSZH_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "GSZH_Dlg.h"
#include "afxdialogex.h"


// GSZH_Dlg 对话框

IMPLEMENT_DYNAMIC(GSZH_Dlg, CDialogEx)

GSZH_Dlg::GSZH_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GSZH_Dlg, pParent)
	, m_name(_T(""))
{

}

GSZH_Dlg::~GSZH_Dlg()
{
}

void GSZH_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_name);
}


BEGIN_MESSAGE_MAP(GSZH_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &GSZH_Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &GSZH_Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// GSZH_Dlg 消息处理程序


BOOL GSZH_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_form = TEXT("");
	m_combo.AddString(TEXT("png"));
	m_combo.AddString(TEXT("jpeg"));
	m_combo.AddString(TEXT("bmp"));
	m_combo.AddString(TEXT("tif"));
	m_combo.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void GSZH_Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void GSZH_Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name == TEXT(""))
	{
		MessageBox(TEXT("名字不能为空！"));
		return;
	}
	m_combo.GetLBText(m_combo.GetCurSel(), m_form);

	OnOK();
}
