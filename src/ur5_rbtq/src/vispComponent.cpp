#include <visp/vpImage.h>
#include <visp_ros/vpROSGrabber.h>
#include <visp_ros/vpROSRobot.h>
#include <visp_bridge/image.h>
#include <visp_bridge/3dpose.h>
#include <visp3/gui/vpDisplayGDI.h>
#include <visp3/gui/vpDisplayX.h>




#include <ros/ros.h>
#include <stdio.h>
#include <geometry_msgs/Pose.h>

int main(int argc, char **argv)
{
    vpImage<vpRGBa> I; // Gray image container

    vpROSGrabber g;
    g.setImageTopic("/webcam/image_rect");
    g.open(I);

    // Send Node
    static const std::string POSE_TOPIC = "/desired_pose";
    // ros::init(argc, argv, "visp_component");
    // ros::NodeHandle n;
    // ros::Publisher pub = n.advertise<geometry_msgs::Pose>(POSE_TOPIC, 10);
    vpDisplayX d(I);
    while (1)
    {
        g.acquire(I);
        vpDisplay::setTitle(I,"ViSP");
        vpDisplay::display(I);
        vpDisplay::flush(I);

        // Visual Servoing Code





        // Conversion code

        // vpHomogeneousMatrix a;
        // geometry_msgs::Pose desired_pose = visp_bridge::toGeometryMsgsPose(a);
        // pub.publish(desired_pose);
    }
}