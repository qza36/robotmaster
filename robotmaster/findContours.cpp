#include <iostream>
#include <opencv2\opencv.hpp>  //���� opencv ��ͷ�ļ�
#include<math.h>
using namespace std;
using namespace cv;  //OpenCV �������ռ�

int main()
{
	VideoCapture video;
	video.open("C:\\Users\\Arlo\\Downloads\\lbb_fan.mp4");
	if (!video.isOpened())
	{
		cout << "��Ƶ��ʧ��" << endl;
		return -1;
	}

	Mat img;
	while (video.read(img))
	{
		if (img.empty())
		{
			cout << "ͼƬ��ʧ��" << endl;
			return -1;
		}

		Mat  binary;
		vector<Mat> imgChannels;
		split(img, imgChannels);
		Mat gray = imgChannels.at(0) - imgChannels.at(2);//�����ɫ����
		//Mat gray= imgChannels.at(2) - imgChannels.at(0);//��ȡ��ɫ����

		GaussianBlur(gray, gray, Size(5, 5), 2);
		//threshold(gray, binary, 48, 255, THRESH_BINARY);//��ɫ�ĵ���
		threshold(gray, binary, 70, 255, THRESH_BINARY);//��ɫ�ĵ���

		//Ϊʲô����Ҫʹ�������Ĳ���������
		int structElementSize = 2;
		Mat element = getStructuringElement(MORPH_RECT, Size(2 * structElementSize + 1, 2 * structElementSize + 1), Point(structElementSize, structElementSize));
		dilate(binary, binary, element);
		morphologyEx(binary, binary, MORPH_CLOSE, element);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;

		findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
		//drawContours(img, contours, -1, Scalar(255, 255, 255), 2);


		int contour[20] = { 0 };
		for (int i = 0; i < contours.size(); i++)
		{
			if (hierarchy[i][3] != -1)
			{
				contour[hierarchy[i][3]]++;
			}
		}

		for (int i = 0; i < contours.size(); i++)
		{
			if (contour[i] == 1)
			{
				int num = hierarchy[i][2];

				RotatedRect rect = minAreaRect(contours[num]);

				RotatedRect rect1 = minAreaRect(contours[i]);


				Point2f vertex[4];

				rect.points(vertex);//�����½ǣ����Ͻǣ����Ͻǣ����½Ǵ���㼯

				for (int i = 0; i < 4; i++)
				{
					line(img, vertex[i], vertex[(i + 1) % 4], Scalar(0, 255, 255), 4, LINE_AA);
				}

				Point centerP = (vertex[0] + vertex[2]) / 2;
				circle(img, centerP, 1, Scalar(0, 0, 255), 2);

			}
		}


		imshow("��Ƶ", img);
		//imshow("asdf", binary);
		uchar a = waitKey(24);
		if (a == ' ')
		{
			waitKey(0);
		}
	}

	return 0;
}