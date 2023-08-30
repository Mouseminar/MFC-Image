#pragma once

#include "CGlobal.h"


// Child_Dlg1 窗体视图

class Child_Dlg1 : public CFormView
{
	DECLARE_DYNCREATE(Child_Dlg1)

protected:
	Child_Dlg1();           // 动态创建所使用的受保护的构造函数
	virtual ~Child_Dlg1();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Child_Dlg1 };
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
	afx_msg void OnOpen();
	afx_msg void OnPaint();
	afx_msg void OnZft();//直方图函数
	afx_msg void OnSave();
	afx_msg void OnGSZH();
	afx_msg void OnSXFD();
	afx_msg void OnSSZXZ();
	afx_msg void OnNSZXZ();
	afx_msg void OnFZ();
	afx_msg void OnJX();
	afx_msg void OnHDH();
	afx_msg void OnDBD();
	afx_msg void OnLD();
	afx_msg void OnZFTJHH();
	afx_msg void OnLYPH();
	afx_msg void OnJQPH();
	afx_msg void OnGSPH();
	afx_msg void OnZZPH();
	afx_msg void OnRH();
	afx_msg void OnFD();
	afx_msg void OnHSLJ();
	afx_msg void OnLSLJ();
	afx_msg void OnBuleFilter();
	afx_msg void OnFX();
	afx_msg void OnCZBY();
	afx_msg void OnYHXG();
	afx_msg void OnMSK();

	//调整大小函数
	Mat resizeImageNearestNeighbor(const Mat image, int targetWidth, int targetHeight);
	//顺时针旋转90°
	Mat rotateImage90Clockwise(const Mat inputImage);
	//逆时针旋转90°
	Mat rotateImage90CounterClockwise(const Mat inputImage);
	//旋转180°
	Mat rotateImage180Clockwise(const Mat inputImage);
	//镜像
	Mat mirrorImage(const cv::Mat inputImage);
	//灰度化函数
	Mat convertToGrayscale(const cv::Mat inputImage);
	//调整图像对比度
	Mat adjustContrast(const cv::Mat inputImage, double alpha);
	//调整图像亮度
	Mat adjustBrightness(const cv::Mat inputImage, int brightness);
	//直方图均衡化
	Mat equalizeHistogram(const cv::Mat inputImage);
	//基于邻域的均值滤波
	Mat linearNeighborhoodFilter(const cv::Mat inputImage, int kernelSize);
	//加权最小二乘滤波
	Mat weightedLeastSquaresFilter(const cv::Mat inputImage, double lambda, double alpha);
	//高斯滤波
	Mat gaussianFilter(const cv::Mat inputImage, int kernelSize, double sigma);
	//中值滤波
	Mat medianFilter(const cv::Mat inputImage, int kernelSize);
	//锐化函数
	Mat sharpenImage(const cv::Mat inputImage, float sharpeningFactor);
	//浮雕化函数
	Mat embossImage(const cv::Mat inputImage, float embossStrength);
	//红色滤镜函数
	Mat redFilter(const cv::Mat inputImage);
	//绿色滤镜函数
	Mat greenFilter(const cv::Mat inputImage);
	//蓝色滤镜函数
	Mat blueFilter(const cv::Mat inputImage);
	//反向函数
	Mat invertImage(const cv::Mat inputImage);
	//边缘检测函数
	Mat edgeDetection(const cv::Mat inputImage);
	//油画效果
	Mat oilPaintingFilter(const Mat inputImage, int basicSize, int grayLevelSize, int gap, bool Mean_sta);
	//马赛克效果
	Mat applyMosaicEffect(const cv::Mat inputImage, int blockSize);
};


