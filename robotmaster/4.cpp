#include <opencv2/opencv.hpp>

int main() {
    // ��ȡͼ��ת��Ϊ�Ҷ�ͼ��
    cv::Mat img = cv::imread("rb.png");
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // ������ֵ����
    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);

    // ��������
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // ���������ı߽��
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Rect boundingRect = cv::boundingRect(contours[i]);
        cv::rectangle(img, boundingRect, cv::Scalar(0, 255, 0), 2);
    }

    // ��ʾͼ��
    cv::imshow("Contours", img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}