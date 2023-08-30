// Child_Dlg1.cpp: 实现文件
//

#include "pch.h"
#include "MFCImage.h"
#include "Child_Dlg1.h"
#include "Child_Dlg2.h"
#include "MainFrm.h"

#include "Resize_Dlg.h"
#include "DBD_Dlg.h"
#include "LD_Dlg.h"
#include "GSZH_Dlg.h"

// Child_Dlg1

IMPLEMENT_DYNCREATE(Child_Dlg1, CFormView)

Child_Dlg1::Child_Dlg1()
	: CFormView(IDD_Child_Dlg1)
{
	choose = false;
	process = false;
}

Child_Dlg1::~Child_Dlg1()
{
}

void Child_Dlg1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Child_Dlg1, CFormView)

	ON_COMMAND(ID_32772, &Child_Dlg1::OnOpen)
	ON_WM_PAINT()
	ON_COMMAND(ID_ZFT, &Child_Dlg1::OnZft)
	ON_COMMAND(ID_32774, &Child_Dlg1::OnSave)
	ON_COMMAND(ID_32777, &Child_Dlg1::OnGSZH)
	ON_COMMAND(ID_32778, &Child_Dlg1::OnSXFD)
	ON_COMMAND(ID_32781, &Child_Dlg1::OnSSZXZ)
	ON_COMMAND(ID_32782, &Child_Dlg1::OnNSZXZ)
	ON_COMMAND(ID_32783, &Child_Dlg1::OnFZ)
	ON_COMMAND(ID_32780, &Child_Dlg1::OnJX)
	ON_COMMAND(ID_32784, &Child_Dlg1::OnHDH)
	ON_COMMAND(ID_32785, &Child_Dlg1::OnDBD)
	ON_COMMAND(ID_32786, &Child_Dlg1::OnLD)
	ON_COMMAND(ID_32787, &Child_Dlg1::OnZFTJHH)
	ON_COMMAND(ID_32789, &Child_Dlg1::OnLYPH)
	ON_COMMAND(ID_32790, &Child_Dlg1::OnJQPH)
	ON_COMMAND(ID_32791, &Child_Dlg1::OnGSPH)
	ON_COMMAND(ID_32792, &Child_Dlg1::OnZZPH)
	ON_COMMAND(ID_32793, &Child_Dlg1::OnRH)
	ON_COMMAND(ID_32794, &Child_Dlg1::OnFD)
	ON_COMMAND(ID_32800, &Child_Dlg1::OnHSLJ)
	ON_COMMAND(ID_32801, &Child_Dlg1::OnLSLJ)
	ON_COMMAND(ID_32802, &Child_Dlg1::OnBuleFilter)
	ON_COMMAND(ID_32796, &Child_Dlg1::OnFX)
	ON_COMMAND(ID_32797, &Child_Dlg1::OnCZBY)
	ON_COMMAND(ID_32798, &Child_Dlg1::OnYHXG)
	ON_COMMAND(ID_32799, &Child_Dlg1::OnMSK)
END_MESSAGE_MAP()


// Child_Dlg1 诊断

#ifdef _DEBUG
void Child_Dlg1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void Child_Dlg1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// Child_Dlg1 消息处理程序



void Child_Dlg1::OnPaint()
{
	if (choose)
	{
		CPaintDC dc(this); // device context for painting
		CRect rect;
		GetClientRect(&rect);
		CImage image;
		image.Load(StrFilePath);
		image.BitBlt(dc, 0, 40, rect.Width(), rect.Height(), 0, 0);
		image.Destroy();    //没有Destroy()会有内存泄漏。Detach();不行的。
	}
}

void Child_Dlg1::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpeg;*.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*|"), this);
	fileDlg.DoModal();
	StrFilePath = fileDlg.GetPathName();
	StrFileName = fileDlg.GetFileName();
	if (StrFilePath == _T(""))
	{
		return;
	}
	choose = true;
	src = imread(StrFilePath.GetBuffer());
	Invalidate();
}


void Child_Dlg1::OnZft()
{
	// TODO: 在此添加命令处理程序代码
	
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	Mat matRGB[3];
	split(src, matRGB);
	int Channels[] = { 0 };
	int nHistSize[] = { 256 };
	float range[] = { 0, 255 };
	const float* fHistRanges[] = { range };
	Mat histR, histG, histB;
	// 计算直方图
	calcHist(&matRGB[0], 1, Channels, Mat(), histB, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[1], 1, Channels, Mat(), histG, 1, nHistSize, fHistRanges, true, false);
	calcHist(&matRGB[2], 1, Channels, Mat(), histR, 1, nHistSize, fHistRanges, true, false);

	// 创建直方图画布
	int nHistWidth = 800;
	int nHistHeight = 600;
	int nBinWidth = cvRound((double)nHistWidth / nHistSize[0]);
	Mat matHistImage(nHistHeight, nHistWidth, CV_8UC3, Scalar(255, 255, 255));
	// 直方图归一化
	normalize(histB, histB, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histG, histG, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	normalize(histR, histR, 0.0, matHistImage.rows, NORM_MINMAX, -1, Mat());
	// 在直方图中画出直方图
	for (int i = 1; i < nHistSize[0]; i++)
	{
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histB.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histB.at<float>(i))),
			Scalar(255, 0, 0),
			2,
			8,
			0);
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histG.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histG.at<float>(i))),
			Scalar(0, 255, 0),
			2,
			8,
			0);
		line(matHistImage,
			Point(nBinWidth * (i - 1), nHistHeight - cvRound(histR.at<float>(i - 1))),
			Point(nBinWidth * (i), nHistHeight - cvRound(histR.at<float>(i))),
			Scalar(0, 0, 255),
			2,
			8,
			0);
	}
	// 显示直方图
	//imshow("histogram", matHistImage);
	imwrite("result.png", matHistImage);

	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
		pDlg = nullptr;
	}
}


void Child_Dlg1::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}
	if (!process)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*||");  //文件格式过滤
	// 构造保存文件对话框    
	CFileDialog fileDlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("保存图像");  //保存对话窗口标题名
	CString picturePath;
	if (IDOK == fileDlg.DoModal())  //按下确认键
	{
		picturePath = fileDlg.GetPathName();  //文件路径
		MessageBox(TEXT("保存成功！"));
	}

	CImage image;
	image.Load("result.png");
	image.Save(picturePath); //保存图片
	image.Destroy();
}


void Child_Dlg1::OnGSZH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}
	process = true;
	GSZH_Dlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		
		CString str;
		str = dlg.m_name + TEXT(".") + dlg.m_form;

		imwrite(str.GetBuffer(), src);
		MessageBox(TEXT("格式转换成功！"));
	}
}

//调整大小函数：最近邻插值：该方法将目标图像中的每个像素与原始图像中最接近的像素进行匹配。
//这种方法简单快速，但可能会导致图像边缘的锯齿状效果。
Mat Child_Dlg1::resizeImageNearestNeighbor(const Mat image, int targetWidth, int targetHeight)
{
	Mat resizedImage(targetHeight, targetWidth, image.type());

	// 计算缩放比例
	float scaleX = static_cast<float>(image.cols) / targetWidth;
	float scaleY = static_cast<float>(image.rows) / targetHeight;

	for (int y = 0; y < targetHeight; y++) {
		for (int x = 0; x < targetWidth; x++) {
			// 计算原始图像中最近的像素坐标
			int srcX = static_cast<int>(x * scaleX);
			int srcY = static_cast<int>(y * scaleY);

			// 获取最近邻像素的值并赋给调整后的图像
			resizedImage.at<cv::Vec3b>(y, x) = image.at<cv::Vec3b>(srcY, srcX);
		}
	}

	return resizedImage;
}

void Child_Dlg1::OnSXFD()
{
	// TODO: 在此添加命令处理程序代码
	process = true;
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	//dlg = new Resize_Dlg;
	//dlg->m_l = src.rows;
	//dlg->m_h = src.cols;
	//dlg->m_pParentDlg = this;  // 将父对话框的指针赋值给子对话框的成员变量
	//dlg->Create(IDD_Resize_Dlg);
	//dlg->ShowWindow(SW_SHOWNORMAL);

	Resize_Dlg dlg;
	dlg.m_h = src.rows;
	dlg.m_l = src.cols;
	if (dlg.DoModal() == IDOK)
	{
		out = resizeImageNearestNeighbor(src, dlg.m_l, dlg.m_h);
		imwrite("result.png", out);
		process = true;

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
		if (pDlg != nullptr)
		{
			pDlg->Invalidate();
		}
	}

	
}

//顺时针旋转90°
Mat Child_Dlg1::rotateImage90Clockwise(const Mat inputImage) {
	// 获取输入图像的尺寸
	int rows = inputImage.rows;
	int cols = inputImage.cols;

	// 创建一个新的图像，尺寸为旋转后的尺寸
	Mat rotatedImage(cols, rows, inputImage.type());

	// 执行旋转
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			rotatedImage.at<Vec3b>(j, rows - i - 1) = inputImage.at<Vec3b>(i, j);
		}
	}

	return rotatedImage;
}

void Child_Dlg1::OnSSZXZ()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = rotateImage90Clockwise(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//逆时针旋转90°
Mat Child_Dlg1::rotateImage90CounterClockwise(const Mat inputImage) {
	// 获取输入图像的尺寸
	int rows = inputImage.rows;
	int cols = inputImage.cols;

	// 创建一个新的图像，尺寸为旋转后的尺寸
	cv::Mat rotatedImage(cols, rows, inputImage.type());

	// 执行旋转
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			rotatedImage.at<cv::Vec3b>(cols - j - 1, i) = inputImage.at<cv::Vec3b>(i, j);
		}
	}

	return rotatedImage;
}

void Child_Dlg1::OnNSZXZ()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = rotateImage90CounterClockwise(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//旋转180°
Mat Child_Dlg1::rotateImage180Clockwise(const Mat inputImage) {
	// 获取输入图像的尺寸
	int rows = inputImage.rows;
	int cols = inputImage.cols;

	// 创建一个新的图像，尺寸为旋转后的尺寸
	cv::Mat rotatedImage(rows, cols, inputImage.type());

	// 执行旋转
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			rotatedImage.at<cv::Vec3b>(rows - i - 1, cols - j - 1) = inputImage.at<cv::Vec3b>(i, j);
		}
	}

	return rotatedImage;
}

void Child_Dlg1::OnFZ()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = rotateImage180Clockwise(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//镜像
Mat Child_Dlg1::mirrorImage(const cv::Mat inputImage) {
	// 获取输入图像的尺寸
	int rows = inputImage.rows;
	int cols = inputImage.cols;

	// 创建一个新的图像，尺寸与输入图像相同
	cv::Mat mirroredImage(rows, cols, inputImage.type());

	// 执行镜像
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mirroredImage.at<cv::Vec3b>(i, cols - j - 1) = inputImage.at<cv::Vec3b>(i, j);
		}
	}

	return mirroredImage;
}

void Child_Dlg1::OnJX()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = mirrorImage(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//灰度化函数
Mat Child_Dlg1::convertToGrayscale(const cv::Mat inputImage) {
	// 获取输入图像的尺寸
	int rows = inputImage.rows;
	int cols = inputImage.cols;

	// 创建一个新的灰度图像，尺寸与输入图像相同
	cv::Mat grayImage(rows, cols, CV_8UC1);

	// 执行灰度化
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// 计算灰度值
			uchar b = inputImage.at<cv::Vec3b>(i, j)[0];
			uchar g = inputImage.at<cv::Vec3b>(i, j)[1];
			uchar r = inputImage.at<cv::Vec3b>(i, j)[2];
			uchar grayValue = static_cast<uchar>(0.299 * r + 0.587 * g + 0.114 * b);

			// 在灰度图像中设置对应像素的灰度值
			grayImage.at<uchar>(i, j) = grayValue;
		}
	}

	return grayImage;
}



void Child_Dlg1::OnHDH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = convertToGrayscale(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

/**
 * 调整图像对比度
 * @param inputImage 输入图像
 * @param alpha 对比度调整因子
 * @return 调整后的图像
 */
Mat Child_Dlg1::adjustContrast(const cv::Mat inputImage, double alpha) {
	// 创建一个新的图像，尺寸与输入图像相同
	cv::Mat adjustedImage(inputImage.size(), inputImage.type());

	// 执行对比度调整
	for (int i = 0; i < inputImage.rows; i++) {
		for (int j = 0; j < inputImage.cols; j++) {
			for (int c = 0; c < inputImage.channels(); c++) {
				// 获取当前像素的原始值，并乘以对比度调整因子
				double newValue = inputImage.at<cv::Vec3b>(i, j)[c] * alpha;

				// 确保像素值在0-255范围内，并将调整后的值赋给新图像的对应像素
				adjustedImage.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(newValue);
			}
		}
	}

	return adjustedImage;
}

void Child_Dlg1::OnDBD()
{
	// TODO: 在此添加命令处理程序代码
	process = true;
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	DBD_Dlg dlg;
	dlg.m_dbd = 1;
	if (dlg.DoModal() == IDOK)
	{
		out = adjustContrast(src, dlg.m_dbd);
		imwrite("result.png", out);
		process = true;

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
		if (pDlg != nullptr)
		{
			pDlg->Invalidate();
		}
	}
}

/**
 * 调整图像亮度
 * @param inputImage 输入图像
 * @param brightness 增加的亮度
 * @return 调整后的图像
 */
Mat Child_Dlg1::adjustBrightness(const cv::Mat inputImage, int brightness) {
	// 创建一个新的图像，尺寸与输入图像相同
	cv::Mat adjustedImage(inputImage.size(), inputImage.type());

	// 执行亮度调整
	for (int i = 0; i < inputImage.rows; i++) {
		for (int j = 0; j < inputImage.cols; j++) {
			for (int c = 0; c < inputImage.channels(); c++) {
				// 获取当前像素的原始值，并加上亮度调整值
				int newValue = inputImage.at<cv::Vec3b>(i, j)[c] + brightness;

				// 确保像素值在0-255范围内，并将调整后的值赋给新图像的对应像素
				adjustedImage.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(newValue);
			}
		}
	}

	return adjustedImage;
}

void Child_Dlg1::OnLD()
{
	// TODO: 在此添加命令处理程序代码
	process = true;
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	LD_Dlg dlg;
	dlg.m_ld = 0;
	if (dlg.DoModal() == IDOK)
	{
		out = adjustBrightness(src, dlg.m_ld);
		imwrite("result.png", out);
		process = true;

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
		if (pDlg != nullptr)
		{
			pDlg->Invalidate();
		}
	}
}

//直方图均衡化
Mat Child_Dlg1::equalizeHistogram(const cv::Mat inputImage) {
	// 创建一个新的图像，尺寸与输入图像相同
	cv::Mat equalizedImage(inputImage.size(), inputImage.type());

	// 分离输入图像的通道
	std::vector<cv::Mat> channels;
	cv::split(inputImage, channels);

	// 对每个通道进行直方图均衡化
	for (int i = 0; i < channels.size(); i++) {
		// 计算灰度直方图
		int histogram[256] = { 0 };
		int totalPixels = channels[i].rows * channels[i].cols;
		for (int r = 0; r < channels[i].rows; r++) {
			for (int c = 0; c < channels[i].cols; c++) {
				uchar pixelValue = channels[i].at<uchar>(r, c);
				histogram[pixelValue]++;
			}
		}

		// 计算累积直方图
		int cumulativeHistogram[256] = { 0 };
		cumulativeHistogram[0] = histogram[0];
		for (int j = 1; j < 256; j++) {
			cumulativeHistogram[j] = cumulativeHistogram[j - 1] + histogram[j];
		}

		// 进行直方图均衡化
		for (int r = 0; r < channels[i].rows; r++) {
			for (int c = 0; c < channels[i].cols; c++) {
				uchar pixelValue = channels[i].at<uchar>(r, c);
				uchar equalizedValue = static_cast<uchar>(255 * cumulativeHistogram[pixelValue] / totalPixels);
				equalizedImage.at<cv::Vec3b>(r, c)[i] = equalizedValue;
			}
		}
	}

	return equalizedImage;
}


void Child_Dlg1::OnZFTJHH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = equalizeHistogram(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//基于邻域的均值滤波
Mat Child_Dlg1::linearNeighborhoodFilter(const cv::Mat inputImage, int kernelSize) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage(inputImage.size(), inputImage.type());

	// 计算滤波核的半径
	int radius = kernelSize / 2;

	// 对输入图像进行滤波
	for (int i = radius; i < inputImage.rows - radius; i++) {
		for (int j = radius; j < inputImage.cols - radius; j++) {
			// 对每个像素的邻域进行求和
			cv::Vec3i sum(0, 0, 0);
			for (int x = -radius; x <= radius; x++) {
				for (int y = -radius; y <= radius; y++) {
					cv::Vec3b pixel = inputImage.at<cv::Vec3b>(i + x, j + y);
					sum += pixel;
				}
			}

			// 计算邻域内像素的均值
			cv::Vec3b mean = static_cast<cv::Vec3b>(sum / (kernelSize * kernelSize));

			// 将均值赋给新图像对应位置的像素
			filteredImage.at<cv::Vec3b>(i, j) = mean;
		}
	}

	return filteredImage;
}

void Child_Dlg1::OnLYPH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置滤波核大小
	int kernelSize = 3;
	out = linearNeighborhoodFilter(src, kernelSize);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//加权最小二乘滤波
Mat Child_Dlg1::weightedLeastSquaresFilter(const cv::Mat inputImage, double lambda, double alpha) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage(inputImage.size(), inputImage.type());

	// 将输入图像转换为灰度图像
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// 计算梯度的平方和
	cv::Mat gradientX, gradientY;
	cv::Sobel(grayImage, gradientX, CV_64F, 1, 0);
	cv::Sobel(grayImage, gradientY, CV_64F, 0, 1);
	cv::Mat gradientMagnitude = gradientX.mul(gradientX) + gradientY.mul(gradientY);

	// 计算权重矩阵
	cv::Mat weights = cv::Mat::ones(inputImage.size(), CV_64F);
	cv::exp(-lambda * gradientMagnitude, weights);

	// 计算平均值
	cv::Mat mean;
	cv::blur(inputImage, mean, cv::Size(3, 3));

	// 计算平方平均值
	cv::Mat meanSquare;
	cv::blur(inputImage.mul(inputImage), meanSquare, cv::Size(3, 3));

	// 计算方差
	cv::Mat variance = meanSquare - mean.mul(mean);

	// 计算增益
	cv::Mat gain = variance / (variance + alpha);

	// 计算滤波后的图像
	filteredImage = mean + gain.mul(inputImage - mean);

	return filteredImage;
}

void Child_Dlg1::OnJQPH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置参数 lambda 和 alpha
	double lambda = 0.25;
	double alpha = 1.2;
	out = weightedLeastSquaresFilter(src, lambda, alpha);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}


//高斯滤波
Mat Child_Dlg1::gaussianFilter(const cv::Mat inputImage, int kernelSize, double sigma) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage(inputImage.size(), inputImage.type());

	// 使用指定的内核大小和标准差创建高斯核
	cv::Mat kernel = cv::getGaussianKernel(kernelSize, sigma);
	cv::Mat kernel2D = kernel * kernel.t();

	// 边界处理的偏移量
	int offset = kernelSize / 2;

	// 对输入图像进行滤波
	for (int i = offset; i < inputImage.rows - offset; i++) {
		for (int j = offset; j < inputImage.cols - offset; j++) {
			// 对每个像素的邻域进行加权平均
			cv::Vec3d sum(0, 0, 0);
			for (int x = -offset; x <= offset; x++) {
				for (int y = -offset; y <= offset; y++) {
					cv::Vec3b pixel = inputImage.at<cv::Vec3b>(i + x, j + y);
					double weight = kernel2D.at<double>(x + offset, y + offset);
					sum += pixel * weight;
				}
			}

			// 将加权平均值赋给新图像对应位置的像素
			filteredImage.at<cv::Vec3b>(i, j) = static_cast<cv::Vec3b>(sum);
		}
	}

	return filteredImage;
}

void Child_Dlg1::OnGSPH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置滤波核大小和标准差
	int kernelSize = 5;
	double sigma = 1.0;
	out = gaussianFilter(src, kernelSize, sigma);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//中值滤波
Mat Child_Dlg1::medianFilter(const cv::Mat inputImage, int kernelSize) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage(inputImage.size(), inputImage.type());

	// 边界处理的偏移量
	int offset = kernelSize / 2;

	// 对每个通道进行滤波
	for (int channel = 0; channel < inputImage.channels(); ++channel) {
		for (int i = offset; i < inputImage.rows - offset; ++i) {
			for (int j = offset; j < inputImage.cols - offset; ++j) {
				// 对每个像素的邻域进行排序
				std::vector<uchar> pixels;
				for (int x = -offset; x <= offset; ++x) {
					for (int y = -offset; y <= offset; ++y) {
						uchar pixel = inputImage.at<cv::Vec3b>(i + x, j + y)[channel];
						pixels.push_back(pixel);
					}
				}

				// 对邻域像素排序并获取中值
				std::sort(pixels.begin(), pixels.end());
				uchar median = pixels[pixels.size() / 2];

				// 将中值赋给新图像对应位置的像素
				filteredImage.at<cv::Vec3b>(i, j)[channel] = median;
			}
		}
	}

	return filteredImage;
}


void Child_Dlg1::OnZZPH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置滤波核大小
	int kernelSize = 3;
	out = medianFilter(src, kernelSize);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//锐化函数
//sharpeningFactor 参数用于控制锐化的强度。将锐化系数添加到拉普拉斯算子的中心像素，可以增强锐化效果。通过调整锐化系数的值，可以控制锐化的程度。
Mat Child_Dlg1::sharpenImage(const cv::Mat inputImage, float sharpeningFactor) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat sharpenedImage = inputImage.clone();

	// 定义拉普拉斯算子，并乘以锐化系数
	cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5 + sharpeningFactor, -1, 0, -1, 0);

	// 对输入图像进行滤波
	cv::filter2D(inputImage, sharpenedImage, inputImage.depth(), kernel);

	return sharpenedImage;
}

void Child_Dlg1::OnRH()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置锐化系数
	float sharpeningFactor = 1;

	out = sharpenImage(src, sharpeningFactor);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//浮雕化函数
//浮雕效果可以通过将图像的每个像素与其周围像素的灰度差异进行计算来实现
Mat Child_Dlg1::embossImage(const cv::Mat inputImage, float embossStrength) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat embossedImage = inputImage.clone();

	// 定义浮雕滤波器
	cv::Mat kernel = (cv::Mat_<float>(3, 3) << -1 * embossStrength, -0.5 * embossStrength, 0, -0.5 * embossStrength, 1, 0.5 * embossStrength, 0, 0.5 * embossStrength, embossStrength);

	// 对输入图像进行滤波
	cv::filter2D(inputImage, embossedImage, inputImage.depth(), kernel);

	return embossedImage;
}

void Child_Dlg1::OnFD()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	// 设置浮雕强度
	float embossStrength = 5;

	out = embossImage(src, embossStrength);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//红色滤镜函数
Mat Child_Dlg1::redFilter(const cv::Mat inputImage) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage = inputImage.clone();

	// 将图像的蓝色通道和绿色通道设置为0
	filteredImage.forEach<cv::Vec3b>([](cv::Vec3b& pixel, const int* position) {
		pixel[0] = 0; // Blue
		pixel[1] = 0; // Green
		});

	return filteredImage;
}

void Child_Dlg1::OnHSLJ()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = redFilter(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//绿色滤镜函数
Mat Child_Dlg1::greenFilter(const cv::Mat inputImage) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage = inputImage.clone();

	// 将图像的蓝色通道和红色通道设置为0
	filteredImage.forEach<cv::Vec3b>([](cv::Vec3b& pixel, const int* position) {
		pixel[0] = 0; // Blue
		pixel[2] = 0; // Red
		});

	return filteredImage;
}

void Child_Dlg1::OnLSLJ()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = greenFilter(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//蓝色滤镜函数
Mat Child_Dlg1::blueFilter(const cv::Mat inputImage) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat filteredImage = inputImage.clone();

	// 将图像的红色通道和绿色通道设置为0
	filteredImage.forEach<cv::Vec3b>([](cv::Vec3b& pixel, const int* position) {
		pixel[1] = 0; // Green
		pixel[2] = 0; // Red
		});

	return filteredImage;
}

void Child_Dlg1::OnBuleFilter()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = blueFilter(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//反向函数
//将每个通道的像素值用255减去，以实现反向效果
Mat Child_Dlg1::invertImage(const cv::Mat inputImage) {
	// 创建一个与输入图像尺寸相同的新图像
	cv::Mat invertedImage = inputImage.clone();

	// 对每个像素进行反向操作
	invertedImage.forEach<cv::Vec3b>([](cv::Vec3b& pixel, const int* position) {
		pixel[0] = 255 - pixel[0]; // Blue
		pixel[1] = 255 - pixel[1]; // Green
		pixel[2] = 255 - pixel[2]; // Red
		});

	return invertedImage;
}

void Child_Dlg1::OnFX()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = invertImage(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//边缘检测函数
Mat Child_Dlg1::edgeDetection(const cv::Mat inputImage) {
	// 转换图像为灰度图像
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// 对灰度图像进行高斯滤波，以减少噪声
	cv::GaussianBlur(grayImage, grayImage, cv::Size(3, 3), 0);

	// 使用Canny边缘检测算法
	cv::Mat edges;
	cv::Canny(grayImage, edges, 50, 150);

	// 返回边缘图像
	return edges;
}

void Child_Dlg1::OnCZBY()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = edgeDetection(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

//油画效果
//https://huilin.blog.csdn.net/article/details/82954961?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-82954961-blog-114050301.235%5Ev36%5Epc_relevant_default_base3&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-82954961-blog-114050301.235%5Ev36%5Epc_relevant_default_base3&utm_relevant_index=2
//参数basicSize（块大小）、grayLevelSize（灰度等级数）、gap（块之间的间隔）、Mean_sta（均值计算方式）
Mat Child_Dlg1::oilPaintingFilter(const Mat inputImage, int basicSize = 4, int grayLevelSize = 8, int gap = 2, bool Mean_sta = true)
{
	Mat grayImg;
	cvtColor(inputImage, grayImg, COLOR_BGR2GRAY);
	int imgHeight = inputImage.rows;
	int imgWidth = inputImage.cols;

	Mat dstImg = Mat::zeros(inputImage.size(), CV_8UC3);

	for (int i = basicSize; i < imgHeight - basicSize; i += gap)
	{
		for (int j = basicSize; j < imgWidth - basicSize; j += gap)
		{
			// 灰度等级统计
			Mat grayLevel = Mat::zeros(1, grayLevelSize, CV_8UC1);
			Vec3i graySum(0, 0, 0);

			// 对小区域进行遍历统计
			for (int m = -basicSize; m < basicSize; m++)
			{
				for (int n = -basicSize; n < basicSize; n++)
				{
					int pixlv = static_cast<int>(grayImg.at<uchar>(i + m, j + n) / (256 / grayLevelSize));
					grayLevel.at<uchar>(0, pixlv) += 1;
				}
			}

			// 找出最高频灰度等级及其索引
			double minValue, maxValue;
			Point minLoc, maxLoc;
			minMaxLoc(grayLevel, &minValue, &maxValue, &minLoc, &maxLoc);

			int mostLevelIndex = maxLoc.x;

			int level_pixNum = 0;
			for (int m = -basicSize; m < basicSize; m++)
			{
				for (int n = -basicSize; n < basicSize; n++)
				{
					if (static_cast<int>(grayImg.at<uchar>(i + m, j + n) / (256 / grayLevelSize)) == mostLevelIndex)
					{
						level_pixNum += 1;
						if (Mean_sta)
						{
							graySum += inputImage.at<Vec3b>(i + m, j + n);
						}
						else
						{
							graySum = Vec3b(std::max(graySum[0], static_cast<int>(inputImage.at<Vec3b>(i + m, j + n)[0])),
								std::max(graySum[1], static_cast<int>(inputImage.at<Vec3b>(i + m, j + n)[1])),
								std::max(graySum[2], static_cast<int>(inputImage.at<Vec3b>(i + m, j + n)[2])));
						}
					}
				}
			}

			if (Mean_sta)
			{
				graySum /= level_pixNum;
			}

			// 写入目标像素
			for (int m = 0; m < gap; m++)
			{
				for (int n = 0; n < gap; n++)
				{
					dstImg.at<Vec3b>(i + m, j + n) = graySum;
				}
			}
		}
	}

	return dstImg;
}


void Child_Dlg1::OnYHXG()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	out = oilPaintingFilter(src);
	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}

/**
 * 应用马赛克效果到图像中
 * @param inputImage 原始图像
 * @param blockSize 像素块的大小
 * @return 应用马赛克效果后的图像
 */
Mat Child_Dlg1::applyMosaicEffect(const cv::Mat inputImage, int blockSize)
{
	cv::Mat outputImage = inputImage.clone(); // 创建输出图像，复制输入图像
	int width = outputImage.rows; // 图像的长度
	int height = outputImage.cols; // 图像的宽度

	// 遍历图像并应用马赛克效果
	for (int i = 0; i < width; i += blockSize) {
		for (int j = 0; j < height; j += blockSize) {
			cv::Vec3b color = outputImage.at<cv::Vec3b>(i, j); // 获取当前块的颜色值

			// 遍历当前块内的每个像素，将颜色值设置为当前块的颜色值
			for (int k = i; k < i + blockSize && k < width; k++) {
				for (int m = j; m < j + blockSize && m < height; m++) {
					outputImage.at<cv::Vec3b>(k, m) = color;
				}
			}
		}
	}

	return outputImage; // 返回应用马赛克效果后的图像
}

void Child_Dlg1::OnMSK()
{
	// TODO: 在此添加命令处理程序代码
	if (!choose)
	{
		//MessageBox(TEXT("请先选择图片！"), TEXT("提示"));
		return;
	}

	int blockSize = 10;  // 设置马赛克块的大小
	out = applyMosaicEffect(src, blockSize);

	imwrite("result.png", out);
	process = true;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	Child_Dlg2* pDlg = pMainFrame->GetChildDlg2();
	if (pDlg != nullptr)
	{
		pDlg->Invalidate();
	}
}
