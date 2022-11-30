// Generated by gencpp from file grasping_msgs/GraspPlanningFeedback.msg
// DO NOT EDIT!


#ifndef GRASPING_MSGS_MESSAGE_GRASPPLANNINGFEEDBACK_H
#define GRASPING_MSGS_MESSAGE_GRASPPLANNINGFEEDBACK_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <moveit_msgs/Grasp.h>

namespace grasping_msgs
{
template <class ContainerAllocator>
struct GraspPlanningFeedback_
{
  typedef GraspPlanningFeedback_<ContainerAllocator> Type;

  GraspPlanningFeedback_()
    : grasps()  {
    }
  GraspPlanningFeedback_(const ContainerAllocator& _alloc)
    : grasps(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::moveit_msgs::Grasp_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::moveit_msgs::Grasp_<ContainerAllocator> >> _grasps_type;
  _grasps_type grasps;





  typedef boost::shared_ptr< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct GraspPlanningFeedback_

typedef ::grasping_msgs::GraspPlanningFeedback_<std::allocator<void> > GraspPlanningFeedback;

typedef boost::shared_ptr< ::grasping_msgs::GraspPlanningFeedback > GraspPlanningFeedbackPtr;
typedef boost::shared_ptr< ::grasping_msgs::GraspPlanningFeedback const> GraspPlanningFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator1> & lhs, const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator2> & rhs)
{
  return lhs.grasps == rhs.grasps;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator1> & lhs, const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace grasping_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8c4083a4efa926cd066c287f905843a3";
  }

  static const char* value(const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8c4083a4efa926cdULL;
  static const uint64_t static_value2 = 0x066c287f905843a3ULL;
};

template<class ContainerAllocator>
struct DataType< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "grasping_msgs/GraspPlanningFeedback";
  }

  static const char* value(const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n"
"# Grasps found thus far\n"
"moveit_msgs/Grasp[] grasps\n"
"\n"
"\n"
"================================================================================\n"
"MSG: moveit_msgs/Grasp\n"
"# This message contains a description of a grasp that would be used\n"
"# with a particular end-effector to grasp an object, including how to\n"
"# approach it, grip it, etc.  This message does not contain any\n"
"# information about a \"grasp point\" (a position ON the object).\n"
"# Whatever generates this message should have already combined\n"
"# information about grasp points with information about the geometry\n"
"# of the end-effector to compute the grasp_pose in this message.\n"
"\n"
"# A name for this grasp\n"
"string id\n"
"\n"
"# The internal posture of the hand for the pre-grasp\n"
"# only positions are used\n"
"trajectory_msgs/JointTrajectory pre_grasp_posture\n"
"\n"
"# The internal posture of the hand for the grasp\n"
"# positions and efforts are used\n"
"trajectory_msgs/JointTrajectory grasp_posture\n"
"\n"
"# The position of the end-effector for the grasp.  This is the pose of\n"
"# the \"parent_link\" of the end-effector, not actually the pose of any\n"
"# link *in* the end-effector.  Typically this would be the pose of the\n"
"# most distal wrist link before the hand (end-effector) links began.\n"
"geometry_msgs/PoseStamped grasp_pose\n"
"\n"
"# The estimated probability of success for this grasp, or some other\n"
"# measure of how \"good\" it is.\n"
"float64 grasp_quality\n"
"\n"
"# The approach direction to take before picking an object\n"
"GripperTranslation pre_grasp_approach\n"
"\n"
"# The retreat direction to take after a grasp has been completed (object is attached)\n"
"GripperTranslation post_grasp_retreat\n"
"\n"
"# The retreat motion to perform when releasing the object; this information\n"
"# is not necessary for the grasp itself, but when releasing the object,\n"
"# the information will be necessary. The grasp used to perform a pickup\n"
"# is returned as part of the result, so this information is available for\n"
"# later use.\n"
"GripperTranslation post_place_retreat\n"
"\n"
"# the maximum contact force to use while grasping (<=0 to disable)\n"
"float32 max_contact_force\n"
"\n"
"# an optional list of obstacles that we have semantic information about\n"
"# and that can be touched/pushed/moved in the course of grasping\n"
"string[] allowed_touch_objects\n"
"\n"
"================================================================================\n"
"MSG: trajectory_msgs/JointTrajectory\n"
"Header header\n"
"string[] joint_names\n"
"JointTrajectoryPoint[] points\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: trajectory_msgs/JointTrajectoryPoint\n"
"# Each trajectory point specifies either positions[, velocities[, accelerations]]\n"
"# or positions[, effort] for the trajectory to be executed.\n"
"# All specified values are in the same order as the joint names in JointTrajectory.msg\n"
"\n"
"float64[] positions\n"
"float64[] velocities\n"
"float64[] accelerations\n"
"float64[] effort\n"
"duration time_from_start\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: moveit_msgs/GripperTranslation\n"
"# defines a translation for the gripper, used in pickup or place tasks\n"
"# for example for lifting an object off a table or approaching the table for placing\n"
"\n"
"# the direction of the translation\n"
"geometry_msgs/Vector3Stamped direction\n"
"\n"
"# the desired translation distance\n"
"float32 desired_distance\n"
"\n"
"# the min distance that must be considered feasible before the\n"
"# grasp is even attempted\n"
"float32 min_distance\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3Stamped\n"
"# This represents a Vector3 with reference coordinate frame and timestamp\n"
"Header header\n"
"Vector3 vector\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Vector3\n"
"# This represents a vector in free space. \n"
"# It is only meant to represent a direction. Therefore, it does not\n"
"# make sense to apply a translation to it (e.g., when applying a \n"
"# generic rigid transformation to a Vector3, tf2 will only apply the\n"
"# rotation). If you want your data to be translatable too, use the\n"
"# geometry_msgs/Point message instead.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
;
  }

  static const char* value(const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.grasps);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GraspPlanningFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::grasping_msgs::GraspPlanningFeedback_<ContainerAllocator>& v)
  {
    s << indent << "grasps[]" << std::endl;
    for (size_t i = 0; i < v.grasps.size(); ++i)
    {
      s << indent << "  grasps[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::moveit_msgs::Grasp_<ContainerAllocator> >::stream(s, indent + "    ", v.grasps[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // GRASPING_MSGS_MESSAGE_GRASPPLANNINGFEEDBACK_H
