// Child_Dlg2.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "Child_Dlg2.h"
#include "MainFrm.h"

// Child_Dlg2

IMPLEMENT_DYNCREATE(Child_Dlg2, CFormView)

Child_Dlg2::Child_Dlg2()
	: CFormView(IDD_Child_Dlg2)
{

}

Child_Dlg2::~Child_Dlg2()
{
	
}

void Child_Dlg2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Child_Dlg2, CFormView)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &Child_Dlg2::OnBnClickedButton1)
END_MESSAGE_MAP()


// Child_Dlg2 诊断

#ifdef _DEBUG
void Child_Dlg2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Child_Dlg2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Child_Dlg2 消息处理程序


void Child_Dlg2::OnPaint()
{
	
	if (process)
	{
		CPaintDC dc(this); // device context for painting
		CRect		rect;
		GetClientRect(&rect);
		CImage		image;
		image.Load(TEXT("result.png"));
		image.BitBlt(dc, 0, 40, rect.Width(), rect.Height(), 0, 0);
		image.Destroy();    //没有Destroy()会有内存泄漏。Detach();不行的。
	}
}


void Child_Dlg2::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (!process || !choose)
	//{
	//	return;
	//}
	//imwrite("out.png", out);
	//out = src;
	//StrFilePath = TEXT("out.png");

	//CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//Child_Dlg1* pDlg = pMainFrame->GetChildDlg1();
	//if (pDlg != nullptr)
	//{
	//	pDlg->Invalidate();
	//}
}
