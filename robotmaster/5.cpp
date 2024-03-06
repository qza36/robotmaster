#include <opencv2/opencv.hpp>

#include <iostream>
using namespace cv;
using namespace std;

int main() {
    // 打开摄像头
    // VideoCapture cap(0);
    VideoCapture video;
    video.open("C:\\Users\\Arlo\\Downloads\\lbb_fan.mp4");
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
       cvtColor(frame, hsv,  COLOR_BGR2HSV);

        // 设定蓝色灯条的颜色范围
        Scalar lower_blue(100, 100, 100);
        Scalar upper_blue(130, 255, 255);

        // 根据颜色范围进行颜色过滤
        Mat mask;
        inRange(hsv, lower_blue, upper_blue, mask);//将在lower_blue和upper_blue之间的像素值设置为255，其余的设置为0
         GaussianBlur(mask,mask,Size(5,5),2);//高斯滤波
        //threshold(mask, mask, 100, 255,  THRESH_BINARY);
        // 对过滤后的图像进行形态学操作，以去除噪点
       Mat kernel =  getStructuringElement( MORPH_RECT,  Size(3, 3));//定义结构元素
        morphologyEx(mask, mask,  MORPH_OPEN, kernel);//开运算
     dilate(mask, mask,  getStructuringElement( MORPH_RECT,  Size(2, 2)));//膨胀
     imshow("mask", mask);
       
       // 寻找轮廓
        vector<vector<Point>> contours; //用来储存轮廓的点坐标，每个轮廓由一组点组成
        vector<Vec4i> hierarchy; //用来储存轮廓的层级关系
         findContours(mask, contours,  RETR_EXTERNAL,  CHAIN_APPROX_SIMPLE);
                                                        //RETR_EXTERNAL表示只检测最外层的轮廓，不包括内部的孔洞。
                                                        // CHAIN_APPROX_SIMPLE表示使用简单的轮廓近似算法。
        // 绘制矩形框选蓝色灯条
       // imshow("mask", mask);
         //drawContours(frame, contours, -1, Scalar(0, 255, 0), 2); //在原视频上绘制轮廓，颜色为绿色，线宽为2
        /*for (const auto& contour : contours) { //自动判断类型，并使contour指向contours
             Rect rect =  boundingRect(contour); //创建矩形
            // double aspectRation = static_cast<double>(rect.width);
             //if (aspectRation >= 1.5 && aspectRation <= 3.0) {
                rectangle(frame, rect,  Scalar(0, 255, 0), 2); //在原视频上绘制矩形，
             //}

        }*/
        for (int i = 0; i < contours.size(); i++) {
             int area =  contourArea(contours[i]);
             //cout << "area: " << area << endl;
             if (area>4000&&area<6000) {
                 Rect rect =  boundingRect(contours[i]); //创建矩形
                 line(frame, Point(rect.x, rect.y), Point(rect.x + rect.width, rect.y), Scalar(0, 255, 255), 2);//左上角到右上角
                 line(frame, Point(rect.x, rect.y), Point(rect.x, rect.y + rect.height), Scalar(0, 255, 255), 2);//左上角到左下角
                 line(frame, Point(rect.x + rect.width, rect.y), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);//右上角到右下角
                 line(frame, Point(rect.x, rect.y + rect.height), Point(rect.x + rect.width, rect.y + rect.height), Scalar(0, 255, 255), 2);//左下角到右下角
              drawContours(frame, contours, i, Scalar(0, 255, 0), 3); //在原视频上绘制轮廓，颜色为绿色，线宽为2
             }
		   }

        // 显示处理后的图像
         imshow("Armor Detection", frame);

        // 按下ESC键退出循环
         uchar a = waitKey(1);

        if ( a == 27) {
            break;
        }
    }

    // 释放摄像头
    //cap.release();

    // 关闭窗口
    // destroyAllWindows();

    return 0;
}