#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    // 打开摄像头
    // VideoCapture cap(0);
    VideoCapture video;
    video.open("C:\\Users\\Arlo\\Downloads\\蓝方前哨站下方视角半速.mp4");
    /* if (!cap.isOpened()) {
         cout << "无法打开摄像头" << endl;
         return -1;
     }*/

     // 循环读取摄像头图像并进行处理
    while (true) {
        Mat frame;
        //cap.read(frame);
        video >> frame;
        // 转换为HSV颜色空间
        Mat hsv;
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        // 设定蓝色灯条的颜色范围
        Scalar lower_blue(100, 100, 100);
        Scalar upper_blue(130, 255, 255);

        // 根据颜色范围进行颜色过滤
        Mat mask;
        inRange(hsv, lower_blue, upper_blue, mask);

        // 对过滤后的图像进行形态学操作，以去除噪点
        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
        morphologyEx(mask, mask, MORPH_OPEN, kernel);

        // 寻找轮廓
        vector<vector<Point>> contours; //用来储存轮廓的点坐标，每个轮廓由一组点组成
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        //RETR_EXTERNAL表示只检测最外层的轮廓，不包括内部的孔洞。
        // CHAIN_APPROX_SIMPLE表示使用简单的轮廓近似算法。
// 绘制矩形框选蓝色灯条
        for (const auto& contour : contours) { //自动判断类型，并使contour指向contours
            Rect rect = boundingRect(contour); //创建矩形
            // double aspectRation = static_cast<double>(rect.width);
             //if (aspectRation >= 1.5 && aspectRation <= 3.0) {
            rectangle(frame, rect, Scalar(0, 255, 0), 2); //在原视频上绘制矩形，
            //}

        }

        // 显示处理后的图像
        imshow("Armor Detection", frame);

        // 按下ESC键退出循环
        if (waitKey(1) == 27) {
            break;
        }
    }

    // 释放摄像头
    //cap.release();

    // 关闭窗口
    // destroyAllWindows();

    return 0;
} 