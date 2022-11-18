#!/usr/bin/python
import rospy
from ur5_control import UR5Control
from rbtq_control import RbtqControl
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose
import time
import tf_conversions.posemath as pm
import numpy as np

TOPIC = "/pose_change"
ur5 = UR5Control()
rospy.init_node("pbvs_motion")
r1 = rospy.Rate(1)
r20 = rospy.Rate(20)

message = Pose()
change_HM = np.eye(4)

def callback(msg):
    global message
    message = msg



def main():
    sub = rospy.Subscriber(TOPIC, Pose, callback, queue_size=10)
    while not rospy.is_shutdown():
        global message
        change_HM = pm.toMatrix(pm.fromMsg(message))
        current_pose = ur5.getCurrentPose().pose
        current_HM = pm.toMatrix(pm.fromMsg(current_pose))
        result_HM = np.matmul(change_HM, current_HM)
        # print(result_HM)
        result_pose = pm.toMsg(pm.fromMatrix(result_HM))
        print(result_pose)
        ur5.move_group.set_pose_target(result_pose)
        ur5.move_group.go()


if __name__ == "__main__":
    main()
