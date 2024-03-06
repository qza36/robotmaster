// robotmaster.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<opencv.hpp>
#include<opencv2\imgproc\types_c.h>//解决CV_RGB2GRAY：无法解析的标识符
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<math.h>
using namespace std;
using namespace cv;

int main()
{
	int lowh = 60, lows = 120, lowv = 245;
	int highH = 120, highs = 255, highv = 255;//h60-120是蓝色系
	string path = "rb.png";
	Mat img = imread(path),hsvimg;
	cvtColor(img, hsvimg, COLOR_BGR2HSV);
	vector<Mat> hsvsplit;
	split(hsvimg, hsvsplit);//分离通道
	equalizeHist(hsvsplit[2], hsvsplit[2]);//图像均衡，增强对比度
	merge(hsvsplit, hsvimg);//多通道合并图像
	
	Mat thresholdimg;
	inRange(hsvimg, Scalar(lowh, lows, lowv), Scalar(highH, highs, highv), thresholdimg);//进行颜色过滤,储存在thresholdimg中
	imshow("img", thresholdimg);
	waitKey(0);
}

