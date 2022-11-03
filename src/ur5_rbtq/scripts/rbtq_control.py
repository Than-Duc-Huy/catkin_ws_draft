#!/usr/bin/python

import roslib; roslib.load_manifest('robotiq_2f_gripper_control')
import rospy
from robotiq_2f_gripper_control.msg import _Robotiq2FGripper_robot_output  as outputMsg
from robotiq_2f_gripper_control.msg import _Robotiq2FGripper_robot_input as inputMsg
from time import sleep


class RbtqControl():
    ## Variables
    '''
    rACT activate 1 to activate 0 to deact
    rGTO goto 1 to go
    rPR position (open) 0 - 255 (close)
    rSP speed
    rFR Force
    '''
    def __init__(self):
        self.pub = rospy.Publisher('Robotiq2FGripperRobotOutput', outputMsg.Robotiq2FGripper_robot_output,queue_size=10)
        self.command = outputMsg.Robotiq2FGripper_robot_output();
        rospy.Subscriber("Robotiq2FGripperRobotInput", inputMsg.Robotiq2FGripper_robot_input, self.listen_callback)
        self.gACT = 1 #Activate
        self.gGTO = 0 #Go To
        self.gSTA = 0 #Standby, Activation complete
        self.gOBJ = 0 #Finger at requested position
        self.gFLT = 0 #No Fault
        self.gPR = 0 #Requested position
        self.gPO = 0 #Actual position
        self.gCU = 0 #Current of Fingers
        self.deactivate()
        self.activate()


    def listen_callback(self,status):
        # rospy.loginfo("Called Back")
        self.gACT = status.gACT #Activate
        # rospy.loginfo(status.gACT)
        # rospy.loginfo(self.gACT)
        self.gGTO = status.gGTO #Go To
        self.gSTA = status.gSTA #Standby, Activation complete
        self.gOBJ = status.gOBJ #Finger at requested position
        self.gFLT = status.gFLT #No Fault
        self.gPR = status.gPR #Requested position
        self.gPO = status.gPO #Actual position
        self.gCU = status.gCU #Current of Fingers


    def sendCmd(self):
        self.pub.publish(self.command)

    def activate(self):
        self.command.rACT = 1
        self.command.rGTO = 1
        self.command.rSP  = 255
        self.command.rFR  = 0
        self.sendCmd()

    def deactivate(self):
        while(self.gACT != 0):
            self.command = outputMsg.Robotiq2FGripper_robot_output()
            self.command.rACT = 0
            self.sendCmd()
            rospy.sleep(0.1)


    def force(self, force):
        try:
            pos = max(min(255,force),0) #Bound
        except ValueError:
            pass
        self.command.rFR = force
        self.sendCmd()

    def speed(self, speed):
        try:
            pos = max(min(255,speed),0) #Bound
        except ValueError:
            pass
        self.command.rSP = speed
        self.sendCmd()

    def position(self, pos):
        try:
            pos = max(min(255,pos),0) #Bound
        except ValueError:
            pass
        self.command.rPR = pos
        self.sendCmd()
    def fullOpen(self):
        self.position(0)
    def fullClose(self):
        self.position(255)


def main():
    rospy.init_node('rbtq_control')
    robotiq = RbtqControl()
    robotiq.speed(255)
    robotiq.force(0)
    while not rospy.is_shutdown():
        robotiq.position(255)
        sleep(1)
        robotiq.position(0)
        sleep(1)

if __name__ == '__main__':
    main()



#========================

# #!/usr/bin/env python

# # Software License Agreement (BSD License)
# #
# # Copyright (c) 2012, Robotiq, Inc.
# # All rights reserved.
# #
# # Redistribution and use in source and binary forms, with or without
# # modification, are permitted provided that the following conditions
# # are met:
# #
# #  * Redistributions of source code must retain the above copyright
# #    notice, this list of conditions and the following disclaimer.
# #  * Redistributions in binary form must reproduce the above
# #    copyright notice, this list of conditions and the following
# #    disclaimer in the documentation and/or other materials provided
# #    with the distribution.
# #  * Neither the name of Robotiq, Inc. nor the names of its
# #    contributors may be used to endorse or promote products derived
# #    from this software without specific prior written permission.
# #
# # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# # "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# # LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# # FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# # COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# # INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# # BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# # LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# # CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# # LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# # ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# # POSSIBILITY OF SUCH DAMAGE.
# #
# # Copyright (c) 2012, Robotiq, Inc.
# # Revision $Id$

# """@package docstring
# Command-line interface for receiving and interpreting the status of a 2F gripper.

# This serves as an example for receiving messages from the 'Robotiq2FGripperRobotInput' topic using the 'Robotiq2FGripper_robot_input' msg type and interpreting the corresponding status of the 2F gripper.
# """

# import roslib

# roslib.load_manifest("robotiq_2f_gripper_control")
# import rospy
# from std_msgs.msg import String
# from robotiq_2f_gripper_control.msg import _Robotiq2FGripper_robot_input as inputMsg


# def printStatus(status):
#     """Print the status string generated by the statusInterpreter function."""

#     print(statusInterpreter(status))


# def Robotiq2FGripperStatusListener():
#     """Initialize the node and subscribe to the Robotiq2FGripperRobotInput topic."""

#     rospy.init_node("Robotiq2FGripperStatusListener")
#     rospy.Subscriber(
#         "Robotiq2FGripperRobotInput", inputMsg.Robotiq2FGripper_robot_input, printStatus
#     )
#     rospy.spin()


# def statusInterpreter(status):
#     global maxcurrent
#     """Generate a string according to the current value of the status variables."""

#     output = "\n-----\n2F gripper status interpreter\n-----\n"

#     # gACT
#     output += "gACT = " + str(status.gACT) + ": "
#     if status.gACT == 0:
#         output += "Gripper reset\n"
#     if status.gACT == 1:
#         output += "Gripper activation\n"

#     # gGTO
#     output += "gGTO = " + str(status.gGTO) + ": "
#     if status.gGTO == 0:
#         output += "Standby (or performing activation/automatic release)\n"
#     if status.gGTO == 1:
#         output += "Go to Position Request\n"

#     # gSTA
#     output += "gSTA = " + str(status.gSTA) + ": "
#     if status.gSTA == 0:
#         output += "Gripper is in reset ( or automatic release ) state. see Fault Status if Gripper is activated\n"
#     if status.gSTA == 1:
#         output += "Activation in progress\n"
#     if status.gSTA == 2:
#         output += "Not used\n"
#     if status.gSTA == 3:
#         output += "Activation is completed\n"

#     # gOBJ
#     output += "gOBJ = " + str(status.gOBJ) + ": "
#     if status.gOBJ == 0:
#         output += "Fingers are in motion (only meaningful if gGTO = 1)\n"
#     if status.gOBJ == 1:
#         output += "Fingers have stopped due to a contact while opening\n"
#     if status.gOBJ == 2:
#         output += "Fingers have stopped due to a contact while closing \n"
#     if status.gOBJ == 3:
#         output += "Fingers are at requested position\n"

#     # gFLT
#     output += "gFLT = " + str(status.gFLT) + ": "
#     if status.gFLT == 0x00:
#         output += "No Fault\n"
#     if status.gFLT == 0x05:
#         output += "Priority Fault: Action delayed, initialization must be completed prior to action\n"
#     if status.gFLT == 0x07:
#         output += "Priority Fault: The activation bit must be set prior to action\n"
#     if status.gFLT == 0x09:
#         output += "Minor Fault: The communication chip is not ready (may be booting)\n"
#     if status.gFLT == 0x0B:
#         output += "Minor Fault: Automatic release in progress\n"
#     if status.gFLT == 0x0E:
#         output += "Major Fault: Overcurrent protection triggered\n"
#     if status.gFLT == 0x0F:
#         output += "Major Fault: Automatic release completed\n"

#     # gPR
#     output += "gPR = " + str(status.gPR) + ": "
#     output += (
#         "Echo of the requested position for the Gripper: " + str(status.gPR) + "/255\n"
#     )

#     # gPO
#     output += "gPO = " + str(status.gPO) + ": "
#     output += "Position of Fingers: " + str(status.gPO) + "/255\n"

#     # gCU
#     output += "gCU = " + str(status.gCU) + ": "
#     output += "Current of Fingers: " + str(status.gCU * 10) + " mA\n"
#     maxcurrent = max(maxcurrent, status.gCU * 10)
#     output += "Max Current: " + str(maxcurrent) + " mA\n"
#     return output

