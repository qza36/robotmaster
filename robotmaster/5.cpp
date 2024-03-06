#include <opencv2/opencv.hpp>

#include <iostream>
using namespace cv;
using namespace std;

int main() {
    // ������ͷ
    // VideoCapture cap(0);
    VideoCapture video;
    video.open("C:\\Users\\Arlo\\Downloads\\lbb_fan.mp4");
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
       cvtColor(frame, hsv,  COLOR_BGR2HSV);

        // �趨��ɫ��������ɫ��Χ
        Scalar lower_blue(100, 100, 100);
        Scalar upper_blue(130, 255, 255);

        // ������ɫ��Χ������ɫ����
        Mat mask;
        inRange(hsv, lower_blue, upper_blue, mask);//����lower_blue��upper_blue֮�������ֵ����Ϊ255�����������Ϊ0
         GaussianBlur(mask,mask,Size(5,5),2);//��˹�˲�
        //threshold(mask, mask, 100, 255,  THRESH_BINARY);
        // �Թ��˺��ͼ�������̬ѧ��������ȥ�����
       Mat kernel =  getStructuringElement( MORPH_RECT,  Size(3, 3));//����ṹԪ��
        morphologyEx(mask, mask,  MORPH_OPEN, kernel);//������
     dilate(mask, mask,  getStructuringElement( MORPH_RECT,  Size(2, 2)));//����
     imshow("mask", mask);
       
       // Ѱ������
        vector<vector<Point>> contours; //�������������ĵ����꣬ÿ��������һ������
        vector<Vec4i> hierarchy; //�������������Ĳ㼶��ϵ
         findContours(mask, contours,  RETR_EXTERNAL,  CHAIN_APPROX_SIMPLE);
                                                        //RETR_EXTERNAL��ʾֻ����������������������ڲ��Ŀ׶���
                                                        // CHAIN_APPROX_SIMPLE��ʾʹ�ü򵥵����������㷨��
        // ���ƾ��ο�ѡ��ɫ����
       // imshow("mask", mask);
         //drawContours(frame, contours, -1, Scalar(0, 255, 0), 2); //��ԭ��Ƶ�ϻ�����������ɫΪ��ɫ���߿�Ϊ2
        /*for (const auto& contour : contours) { //�Զ��ж����ͣ���ʹcontourָ��contours
             Rect rect =  boundingRect(contour); //��������
            // double aspectRation = static_cast<double>(rect.width);
             //if (aspectRation >= 1.5 && aspectRation <= 3.0) {
                rectangle(frame, rect,  Scalar(0, 255, 0), 2); //��ԭ��Ƶ�ϻ��ƾ��Σ�
             //}

        }*/
        for (int i = 0; i < contours.size(); i++) {
             int area =  contourArea(contours[i]);
             //cout << "area: " << area << endl;
             if (area>4000&&area<6000) {
                 Rect rect =  boundingRect(contours[i]); //��������
                 line(frame, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y), Scalar(0, 255, 255), 2);//���Ͻǵ����Ͻ�
                 line(frame, Point(rect.x, rect.y), Point(rect.x, rect.y + rect.height), Scalar(0, 255, 255), 2);//���Ͻǵ����½�
                 line(frame, Point(rect.x + rect.width, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);//���Ͻǵ����½�
                 line(frame, Point(rect.x, rect.y + rect.height), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);//���½ǵ����½�
              drawContours(frame, contours, i, Scalar(0, 255, 0), 3); //��ԭ��Ƶ�ϻ�����������ɫΪ��ɫ���߿�Ϊ2
             }
		   }

        // ��ʾ������ͼ��
         imshow("Armor Detection", frame);

        // ����ESC���˳�ѭ��
         uchar a = waitKey(1);

        if ( a == 27) {
            break;
        }
    }

    // �ͷ�����ͷ
    //cap.release();

    // �رմ���
    // destroyAllWindows();

    return 0;
}