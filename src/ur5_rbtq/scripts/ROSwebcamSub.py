#!/usr/bin/python
import sys
import rospy
from sensor_msgs.msg import Image
import cv2 as cv
import numpy as np
from cv_bridge import CvBridge, CvBridgeError


print(sys.executable)
print(cv.__file__)

image_topic = "/webcam/image_raw"

def callback(msg):
    try:
        cv_image = CvBridge().imgmsg_to_cv2(msg, desired_encoding='bgr8')
        # image = CvBridge().imgmsg_to_cv2(msg,desired_encoding="bgr8")
        cv.imshow("Sub",cv_image)
        cv.waitKey(1)
    except CvBridgeError as e:
        print(e)


def main():
    rospy.init_node("image_sub")
    sub = rospy.Subscriber(image_topic,Image,callback)
    rospy.spin()



if __name__ == "__main__":
    main()
