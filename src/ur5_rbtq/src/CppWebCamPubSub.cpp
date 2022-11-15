#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

int main(int, char **)
{
    cv::Mat frame;
    cv::VideoCapture cap;
    int deviceID = 0;
    int apiID = cv::CAP_V4L;

    cap.open(deviceID, apiID);
    if (!cap.isOpened())
    {
        std::cerr << "Cannot open camera" << std::endl;
        return -1;
    }

    std::cout << "Start video" << std::endl;
    while (true)
    {
        cap.read(frame);
        cv::imshow("OpenCv", frame);
        if (cv::waitKey(1) >= 0)
            break;
    }
    return 0;
}