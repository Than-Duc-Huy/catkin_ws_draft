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
message.orientation.w = 1
message.position.x = 0
message.position.y = 0
message.position.z = 0

change_HM = np.eye(4)

def callback(msg):
    global message
    message = msg



def main():
    sub = rospy.Subscriber(TOPIC, Pose, callback, queue_size=10)
    while not rospy.is_shutdown():
        global message
        change_HM = pm.toMatrix(pm.fromMsg(message))
        if np.array_equal(change_HM,np.eye(4)):
            print("No AruCo")
            ur5.move_group.stop()
            ur5.move_group.clear_pose_targets()
        else:
            current_pose = ur5.getCurrentPose().pose
            print(current_pose)
            print(ur5.move_group.get_end_effector_link(),"^")
            current_HM = pm.toMatrix(pm.fromMsg(current_pose))
            print(change_HM)
            result_HM = np.matmul(current_HM,change_HM)
            result_pose = pm.toMsg(pm.fromMatrix(result_HM))
            print(result_pose)
            print("Result ^")
            ur5.goToPoseDisplay(result_pose)
            ur5.goToPose(result_pose)



if __name__ == "__main__":
    main()
