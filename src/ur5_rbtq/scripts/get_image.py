#!/usr/bin/python

import rospy
from sensor_msgs.msg import Image
import cv2 as cv
import numpy as np
from cv_bridge import CvBridge, CvBridgeError

image_topic = "/camera/color/image_raw"

def callback(msg):
    try:
        cv_image = CvBridge().imgmsg_to_cv2(msg, desired_encoding='bgr8')
        # image = CvBridge().imgmsg_to_cv2(msg,desired_encoding="bgr8")
        pass
    except CvBridgeError as e:
        print(e)
    cv.imshow("frame",cv_image)
    cv.waitKey(1)

def main():
    rospy.init_node("image_process")
    sub = rospy.Subscriber(image_topic,Image,callback)
    rospy.spin()


if __name__ == "__main__":
    main()
