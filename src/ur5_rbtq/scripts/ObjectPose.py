#!/usr/bin/python

import rospy
import tf
from geometry_msgs.msg import Pose


TOPIC_NAME = "/object_pose"
NODE_NAME = "object_pose_broadcast"
CAMERA_FRAME = "camera_intrinsic"
# CAMERA_FRAME = "base_link"
OBJECT_FRAME = "object"


broadCast = tf.TransformBroadcaster()


def callback(objectPose):
    position = (objectPose.position.x, objectPose.position.y, objectPose.position.z)
    orientation = (
        objectPose.orientation.x,
        objectPose.orientation.y,
        objectPose.orientation.z,
        objectPose.orientation.w,
    )
    broadCast.sendTransform(
        position, orientation, rospy.Time.now(), OBJECT_FRAME, CAMERA_FRAME
    )
    print("Sending tf")
    pass


def main():
    rospy.init_node(NODE_NAME)
    sub = rospy.Subscriber(TOPIC_NAME, Pose, callback, queue_size=100)
    rospy.spin()


if __name__ == "__main__":
    main()
