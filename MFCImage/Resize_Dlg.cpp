// Resize_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "Resize_Dlg.h"
#include "afxdialogex.h"


// Resize_Dlg 对话框

IMPLEMENT_DYNAMIC(Resize_Dlg, CDialogEx)

Resize_Dlg::Resize_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Resize_Dlg, pParent)
	, m_l(0)
	, m_h(0)
{

}

Resize_Dlg::~Resize_Dlg()
{
}

void Resize_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_l);
	DDX_Text(pDX, IDC_EDIT2, m_h);
}


BEGIN_MESSAGE_MAP(Resize_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Resize_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Resize_Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Resize_Dlg 消息处理程序


void Resize_Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void Resize_Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_l <= 1 || m_h <= 1)
	{
		MessageBox(TEXT("您的设置有误！"), TEXT("提示"));
		return;
	}
	OnOK();
}
