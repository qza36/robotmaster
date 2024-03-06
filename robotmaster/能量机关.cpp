#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	VideoCapture video;
	video.open("C:\\Users\\Arlo\\Downloads\\关灯-红方小能量机关-全激活过程.mp4");
	while (true) {
		Mat frame;
		video >> frame;
		Mat srcImage = frame;
		Mat midImage;
		vector<Mat> imgChannels;
		/*转换为HSV颜色空间*/
		split(srcImage, imgChannels);
		midImage = imgChannels.at(2) - imgChannels.at(0);
		GaussianBlur(midImage, midImage, Size(5, 5), 2);
		threshold(midImage, midImage, 100, 255, THRESH_BINARY);
		//dilate(midImage, midImage, Mat(2, 2, CV_8U));
		erode(midImage, midImage, Mat(25,25, CV_8U));
		//imshow("midImage", midImage);
		/*找轮廓*/
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(midImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		imshow("midImage", midImage);
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);
			if (area > 1000 ) {
				Rect rect = boundingRect(contours[i]);
				line(srcImage, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y), Scalar(0, 255, 255), 2);
				line(srcImage, Point(rect.x, rect.y), Point(rect.x, rect.y + rect.height), Scalar(0, 255, 255), 2);
				line(srcImage, Point(rect.x + rect.width, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);
				line(srcImage, Point(rect.x, rect.y + rect.height), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);
				
				line(srcImage,Point(rect.x,rect.y),Point(rect.x+rect.width,rect.y+rect.height),Scalar(0,255,0),2);
				line(srcImage,Point(rect.x,rect.y+rect.height),Point(rect.x+rect.width,rect.y),Scalar(0,255,0),2);
				cout << "Point1: " << (rect.x)/2 << " " << (rect.y)/2 << endl;	
				//rectangle(srcImage, rect, Scalar(0, 255, 0), 2);
				//drawContours(srcImage, contours, i, Scalar(0, 255, 0), 2);

			}
		}

		imshow("srcImage", srcImage);
			waitKey(1);
	}
	return 0;
}
