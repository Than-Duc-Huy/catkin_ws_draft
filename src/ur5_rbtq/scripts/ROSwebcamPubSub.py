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
    webcam = cv.VideoCapture(0,cv.CAP_V4L2)
    rospy.init_node("image_pub")
    sub = rospy.Subscriber(image_topic,Image,callback)
    pub = rospy.Publisher(image_topic,Image, queue_size=10)
    while(1):
        ret,frame = webcam.read()
        cv.imshow("Pub",frame)
        imgmsg = CvBridge().cv2_to_imgmsg(frame,encoding="bgr8")
        pub.publish(imgmsg)
        if cv.waitKey(1) == ord("q"):
            break



if __name__ == "__main__":
    main()
