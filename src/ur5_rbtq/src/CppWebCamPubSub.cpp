#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <stdio.h>

#include <sensor_msgs/Image.h>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>



void callback(const sensor_msgs::ImageConstPtr& msg){
    cv_bridge::CvImagePtr cvsub_ptr;
    cvsub_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::imshow("Sub", cvsub_ptr->image);
}


int main(int argc, char **argv)
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

    const std::string TOPIC = "/webcam/raw_image";

    ros::init(argc, argv, "image_pub_sub");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<sensor_msgs::Image>(TOPIC, 1000);
    ros::Subscriber sub = n.subscribe(TOPIC,1000,callback);
    // ros::Rate loop_rate(10);

    while (ros::ok)
    {
        cap.read(frame);
        cv::imshow("Pub", frame);

        cv_bridge::CvImagePtr cv_ptr(new cv_bridge::CvImage);
        // // cv_bridge::toCvCopy(frame, sensor_msgs::image_encodings::BGR8);
        cv_ptr->image = frame; // Assign the image pointer as OpenCv image
        cv_ptr->encoding = sensor_msgs::image_encodings::BGR8;
        pub.publish(cv_ptr->toImageMsg()); // Convert OpenCV image to sensor_msgs::Image
        ros::spinOnce();

        if (cv::waitKey(1) >= 0)
            break;
    }
    return 0;
}
