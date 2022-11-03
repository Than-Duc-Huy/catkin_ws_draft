#!/usr/bin/python
import rospy
from ur5_control import UR5Control
from rbtq_control import RbtqControl
import time
def main():
    rospy.init_node("ur5_rbtq_control")
    ur5 = UR5Control()
    rbtq = RbtqControl()
    rbtq.activate()
    ur5.goUp()
    ur5.goHome()
    rbtq.fullClose()
    time.sleep(1.5)
    rbtq.fullOpen()


if __name__ =="__main__":
    main()