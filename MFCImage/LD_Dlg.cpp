// LD_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "LD_Dlg.h"
#include "afxdialogex.h"


// LD_Dlg 对话框

IMPLEMENT_DYNAMIC(LD_Dlg, CDialogEx)

LD_Dlg::LD_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LD_Dlg, pParent)
	, m_ld(0)
{

}

LD_Dlg::~LD_Dlg()
{
}

void LD_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ld);
}


BEGIN_MESSAGE_MAP(LD_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &LD_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &LD_Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// LD_Dlg 消息处理程序


void LD_Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void LD_Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//if (m_dbd <= 0)
	//{
	//	MessageBox(TEXT("您的设置有误！"), TEXT("提示"));
	//	return;
	//}
	OnOK();
}
