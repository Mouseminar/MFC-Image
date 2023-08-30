// DBD_Dlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "DBD_Dlg.h"
#include "afxdialogex.h"


// DBD_Dlg 对话框

IMPLEMENT_DYNAMIC(DBD_Dlg, CDialogEx)

DBD_Dlg::DBD_Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DBD_Dlg, pParent)
	, m_dbd(0)
{

}

DBD_Dlg::~DBD_Dlg()
{
}

void DBD_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dbd);
}


BEGIN_MESSAGE_MAP(DBD_Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &DBD_Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &DBD_Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// DBD_Dlg 消息处理程序


void DBD_Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void DBD_Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_dbd <= 0)
	{
		MessageBox(TEXT("您的设置有误！"), TEXT("提示"));
		return;
	}
	OnOK();
}
