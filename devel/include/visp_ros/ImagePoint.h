// Generated by gencpp from file visp_ros/ImagePoint.msg
// DO NOT EDIT!


#ifndef VISP_ROS_MESSAGE_IMAGEPOINT_H
#define VISP_ROS_MESSAGE_IMAGEPOINT_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace visp_ros
{
template <class ContainerAllocator>
struct ImagePoint_
{
  typedef ImagePoint_<ContainerAllocator> Type;

  ImagePoint_()
    : i(0.0)
    , j(0.0)  {
    }
  ImagePoint_(const ContainerAllocator& _alloc)
    : i(0.0)
    , j(0.0)  {
  (void)_alloc;
    }



   typedef double _i_type;
  _i_type i;

   typedef double _j_type;
  _j_type j;





  typedef boost::shared_ptr< ::visp_ros::ImagePoint_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::visp_ros::ImagePoint_<ContainerAllocator> const> ConstPtr;

}; // struct ImagePoint_

typedef ::visp_ros::ImagePoint_<std::allocator<void> > ImagePoint;

typedef boost::shared_ptr< ::visp_ros::ImagePoint > ImagePointPtr;
typedef boost::shared_ptr< ::visp_ros::ImagePoint const> ImagePointConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::visp_ros::ImagePoint_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::visp_ros::ImagePoint_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::visp_ros::ImagePoint_<ContainerAllocator1> & lhs, const ::visp_ros::ImagePoint_<ContainerAllocator2> & rhs)
{
  return lhs.i == rhs.i &&
    lhs.j == rhs.j;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::visp_ros::ImagePoint_<ContainerAllocator1> & lhs, const ::visp_ros::ImagePoint_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace visp_ros

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::visp_ros::ImagePoint_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::visp_ros::ImagePoint_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visp_ros::ImagePoint_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::visp_ros::ImagePoint_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visp_ros::ImagePoint_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::visp_ros::ImagePoint_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::visp_ros::ImagePoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "600c777d3f6d5d378f3fc5f8df469dbe";
  }

  static const char* value(const ::visp_ros::ImagePoint_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x600c777d3f6d5d37ULL;
  static const uint64_t static_value2 = 0x8f3fc5f8df469dbeULL;
};

template<class ContainerAllocator>
struct DataType< ::visp_ros::ImagePoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "visp_ros/ImagePoint";
  }

  static const char* value(const ::visp_ros::ImagePoint_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::visp_ros::ImagePoint_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Message corresponding to vpImagePoint class\n"
"float64 i      # i (respectively v) position in the image\n"
"float64 j      # j (respectively u) position in the image\n"
"\n"
;
  }

  static const char* value(const ::visp_ros::ImagePoint_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::visp_ros::ImagePoint_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.i);
      stream.next(m.j);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ImagePoint_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::visp_ros::ImagePoint_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::visp_ros::ImagePoint_<ContainerAllocator>& v)
  {
    s << indent << "i: ";
    Printer<double>::stream(s, indent + "  ", v.i);
    s << indent << "j: ";
    Printer<double>::stream(s, indent + "  ", v.j);
  }
};

} // namespace message_operations
} // namespace ros

#endif // VISP_ROS_MESSAGE_IMAGEPOINT_H