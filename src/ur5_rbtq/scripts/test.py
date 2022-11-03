#!/usr/bin/python
import rospy
from ur5_control import UR5Control
from rbtq_control import RbtqControl
import time
def main():
    rospy.init_node("ur5_rbtq_control")
    ur5 = UR5Control()
    # rbtq = RbtqControl()
    # rbtq.activate()
    ur5.goUp()
    while not rospy.is_shutdown():
        ur5.goToPose([0.5,0.2,0.3,1,0,0,0])
        ur5.goToPose([0.5,0.2,0.3,0,1,0,0])
        ur5.goToPose([0.5,0.2,0.3,0,0,1,0])
        ur5.goToPose([0.5,0.2,0.3,0,1,0,1])



if __name__ =="__main__":
    main()