#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main() {
	Mat frame;
	VideoCapture video;
	video.open("C:\\Users\\Arlo\\Downloads\\lbr_fan.mp4");
	while (1) {
		video >> frame;
		Mat srcImage = frame;
		vector<Mat> imgChannels;
		/*×ª»»ÎªHSVÑÕÉ«¿Õ¼ä*/
		Mat midImage;
		split(srcImage, imgChannels);
		midImage = imgChannels.at(2) - imgChannels.at(0);
		GaussianBlur(midImage, midImage, Size(5, 5), 2);
		threshold(midImage, midImage, 100, 255, THRESH_BINARY);
		//erode(dstImage, dstImage, Mat(15, 15, CV_8U));
		/*Ñ°ÕÒÂÖÀª*/
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		Point2i center;
		findContours(midImage,contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		int contour[20] = { 0 };
		imshow("mid", midImage);
		drawContours(frame, contours, -1, Scalar(0, 255, 0), 3);
		for (int i = 0; i < contours.size(); i++) {
			int area = contourArea(contours[i]);
			if (hierarchy[i][3] != -1) {
				//contour[hierarchy[i][3]]++;
				drawContours(frame, contours, i, Scalar(0, 255, 0), 3);
			}
		/*	if (area<6000&&area>4000&&hierarchy[i][3] != -1) {

				Rect rect = boundingRect(contours[i]);
				line(frame,Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y), Scalar(0, 255, 255), 2);
				line(frame,Point(rect.x, rect.y), Point(rect.x, rect.y + rect.height), Scalar(0, 255, 255), 2);
				line(frame,Point(rect.x + rect.width, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);
				line(frame,Point(rect.x, rect.y + rect.height), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);
			}*/
		}
			imshow("frame", frame);


		waitKey(1);


	}
	return 0;
}