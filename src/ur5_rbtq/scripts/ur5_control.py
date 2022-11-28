#!/usr/bin/python
import moveit_commander
import rospy
import sys
import moveit_msgs.msg
from geometry_msgs.msg import Pose
import tf2_geometry_msgs
from std_msgs.msg import String

from moveit_commander.conversions import pose_to_list


class UR5Control:
    def __init__(self):
        moveit_commander.roscpp_initialize(sys.argv)

        self.robot = moveit_commander.RobotCommander()
        self.group_name = "manipulator"
        self.move_group = moveit_commander.MoveGroupCommander(self.group_name)
        self.move_group.set_goal_position_tolerance(0.005)
        self.move_group.set_goal_orientation_tolerance(0.005)

        self.display_trajectory_publisher = rospy.Publisher(
            "/move_group/display_planned_path",
            moveit_msgs.msg.DisplayTrajectory,
            queue_size=10,
        )

    def getCurrentState(self):
        self.state = self.robot.get_current_state()
    def goToPose(self, pose):
        self.move_group.set_pose_target(pose)
        self.move_group.go(wait=True)
        self.move_group.stop()
        self.move_group.clear_pose_targets()

    def goToPoseDisplay(self, pose):
        self.move_group.set_pose_target(pose)
        # self.move_group.go(wait=True)
        display_trajectory = moveit_msgs.msg.DisplayTrajectory()
        display_trajectory.trajectory_start = self.robot.get_current_state()
        waypoint = []
        waypoint.append(pose)
        (plan,fraction) = self.move_group.compute_cartesian_path(waypoint,0.01,0)
        display_trajectory.trajectory.append(plan) # Add the sequence of pose
        self.display_trajectory_publisher.publish(display_trajectory)
        self.move_group.stop()
        self.move_group.clear_pose_targets()

    def goToJoint(self, list):
        joint_goal = self.move_group.get_current_joint_values()
        for i in range(len(list)):
            joint_goal[i] = list[i]
        self.move_group.go(joint_goal, wait=True)
        self.move_group.stop()

    def goHome(self):
        home = [-0.79, -1.57, 1.57, -1.57, -1.57, 0]
        self.goToJoint(home)

    def goUp(self):
        up = [-0.79, -1.57, 0, -1.57, 0, 0]
        self.goToJoint(up)


    def getCurrentPose(self):
        """Return PoseStamped"""
        return self.move_group.get_current_pose()


def main():
    rospy.init_node("UR5_control")
    ur5 = UR5Control()
    while not rospy.is_shutdown():
        print(ur5.move_group.get_end_effector_link())
        print(ur5.move_group.get_current_pose("tool0"))
        ur5.goUp()
        print(ur5.move_group.get_end_effector_link())
        print(ur5.move_group.get_current_pose("tool0"))
        ur5.goHome()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        sys.exit()
