#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    // ������ͷ
    // VideoCapture cap(0);
    VideoCapture video;
    video.open("C:\\Users\\Arlo\\Downloads\\����ǰ��վ�·��ӽǰ���.mp4");
    /* if (!cap.isOpened()) {
         cout << "�޷�������ͷ" << endl;
         return -1;
     }*/

     // ѭ����ȡ����ͷͼ�񲢽��д���
    while (true) {
        Mat frame;
        //cap.read(frame);
        video >> frame;
        // ת��ΪHSV��ɫ�ռ�
        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // �趨��ɫ��������ɫ��Χ
        Scalar lower_blue(100, 100, 100);
        Scalar upper_blue(130, 255, 255);

        // ������ɫ��Χ������ɫ����
        Mat mask;
        inRange(hsv, lower_blue, upper_blue, mask);

        // �Թ��˺��ͼ�������̬ѧ��������ȥ�����
        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
        morphologyEx(mask, mask, MORPH_OPEN, kernel);

        // Ѱ������
        vector<vector<Point>> contours; //�������������ĵ����꣬ÿ��������һ������
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        //RETR_EXTERNAL��ʾֻ����������������������ڲ��Ŀ׶���
        // CHAIN_APPROX_SIMPLE��ʾʹ�ü򵥵����������㷨��
// ���ƾ��ο�ѡ��ɫ����
        for (const auto& contour : contours) { //�Զ��ж����ͣ���ʹcontourָ��contours
            Rect rect = boundingRect(contour); //��������
            // double aspectRation = static_cast<double>(rect.width);
             //if (aspectRation >= 1.5 && aspectRation <= 3.0) {
            rectangle(frame, rect, Scalar(0, 255, 0), 2); //��ԭ��Ƶ�ϻ��ƾ��Σ�
            //}

        }

        // ��ʾ������ͼ��
        imshow("Armor Detection", frame);

        // ����ESC���˳�ѭ��
        if (waitKey(1) == 27) {
            break;
        }
    }

    // �ͷ�����ͷ
    //cap.release();

    // �رմ���
    // destroyAllWindows();

    return 0;
} 