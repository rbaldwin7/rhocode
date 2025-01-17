/* Auto-generated by genmsg_cpp for file /home/noam/ros_workspace/PanTilt/DPPanTilt_msgs/msg/ReportStaticInfo.msg */
#ifndef DPPANTILT_MSGS_MESSAGE_REPORTSTATICINFO_H
#define DPPANTILT_MSGS_MESSAGE_REPORTSTATICINFO_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"

namespace DPPanTilt_msgs
{
template <class ContainerAllocator>
struct ReportStaticInfo_ {
  typedef ReportStaticInfo_<ContainerAllocator> Type;

  ReportStaticInfo_()
  : header()
  , panMinimumValidPositionInRadians(0.0)
  , tiltMinimumValidPositionInRadians(0.0)
  , panMaximumValidPositionInRadians(0.0)
  , tiltMaximumValidPositionInRadians(0.0)
  , panLowerSpeedBoundInRadiansPerSec(0.0)
  , tiltLowerSpeedBoundInRadiansPerSec(0.0)
  , panUpperSpeedBoundInRadiansPerSec(0.0)
  , tiltUpperSpeedBoundInRadiansPerSec(0.0)
  {
  }

  ReportStaticInfo_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , panMinimumValidPositionInRadians(0.0)
  , tiltMinimumValidPositionInRadians(0.0)
  , panMaximumValidPositionInRadians(0.0)
  , tiltMaximumValidPositionInRadians(0.0)
  , panLowerSpeedBoundInRadiansPerSec(0.0)
  , tiltLowerSpeedBoundInRadiansPerSec(0.0)
  , panUpperSpeedBoundInRadiansPerSec(0.0)
  , tiltUpperSpeedBoundInRadiansPerSec(0.0)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef float _panMinimumValidPositionInRadians_type;
  float panMinimumValidPositionInRadians;

  typedef float _tiltMinimumValidPositionInRadians_type;
  float tiltMinimumValidPositionInRadians;

  typedef float _panMaximumValidPositionInRadians_type;
  float panMaximumValidPositionInRadians;

  typedef float _tiltMaximumValidPositionInRadians_type;
  float tiltMaximumValidPositionInRadians;

  typedef float _panLowerSpeedBoundInRadiansPerSec_type;
  float panLowerSpeedBoundInRadiansPerSec;

  typedef float _tiltLowerSpeedBoundInRadiansPerSec_type;
  float tiltLowerSpeedBoundInRadiansPerSec;

  typedef float _panUpperSpeedBoundInRadiansPerSec_type;
  float panUpperSpeedBoundInRadiansPerSec;

  typedef float _tiltUpperSpeedBoundInRadiansPerSec_type;
  float tiltUpperSpeedBoundInRadiansPerSec;


private:
  static const char* __s_getDataType_() { return "DPPanTilt_msgs/ReportStaticInfo"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "949294eda1f9ef4201055f8d681ac295"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "#\n\
# COPYRIGHT (C) 2005-2010\n\
# RE2, INC.\n\
# ALL RIGHTS RESERVED\n\
#\n\
# This is free software:\n\
# you can redistribute it and/or modify it under the terms of the GNU General\n\
# Public License as published by the Free Software Foundation, either version\n\
# 3 of the License, or (at your option) any later version.\n\
#\n\
# You should have received a copy of the GNU General Public License along\n\
# with this package.  If not, see <http://www.gnu.org/licenses/>.\n\
#\n\
# RE2, INC. disclaims all warranties with regard to this software, including\n\
# all implied warranties of merchantability and fitness, in no event shall\n\
# RE2, INC. be liable for any special, indirect or consequential damages or\n\
# any damages whatsoever resulting from loss of use, data or profits, whether\n\
# in an action of contract, negligence or other tortious action, arising out\n\
# of or in connection with the use or performance of this software.\n\
#\n\
#\n\
#\n\
\n\
# This message is used to report the static information about the\n\
# Pan/Tilt Unit.  It is not likely that much of this information will change\n\
# during the course of operation.\n\
\n\
Header header\n\
\n\
\n\
float32 panMinimumValidPositionInRadians\n\
float32 tiltMinimumValidPositionInRadians\n\
\n\
float32 panMaximumValidPositionInRadians\n\
float32 tiltMaximumValidPositionInRadians\n\
\n\
float32 panLowerSpeedBoundInRadiansPerSec\n\
float32 tiltLowerSpeedBoundInRadiansPerSec\n\
\n\
float32 panUpperSpeedBoundInRadiansPerSec\n\
float32 tiltUpperSpeedBoundInRadiansPerSec\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, header);
    ros::serialization::serialize(stream, panMinimumValidPositionInRadians);
    ros::serialization::serialize(stream, tiltMinimumValidPositionInRadians);
    ros::serialization::serialize(stream, panMaximumValidPositionInRadians);
    ros::serialization::serialize(stream, tiltMaximumValidPositionInRadians);
    ros::serialization::serialize(stream, panLowerSpeedBoundInRadiansPerSec);
    ros::serialization::serialize(stream, tiltLowerSpeedBoundInRadiansPerSec);
    ros::serialization::serialize(stream, panUpperSpeedBoundInRadiansPerSec);
    ros::serialization::serialize(stream, tiltUpperSpeedBoundInRadiansPerSec);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, header);
    ros::serialization::deserialize(stream, panMinimumValidPositionInRadians);
    ros::serialization::deserialize(stream, tiltMinimumValidPositionInRadians);
    ros::serialization::deserialize(stream, panMaximumValidPositionInRadians);
    ros::serialization::deserialize(stream, tiltMaximumValidPositionInRadians);
    ros::serialization::deserialize(stream, panLowerSpeedBoundInRadiansPerSec);
    ros::serialization::deserialize(stream, tiltLowerSpeedBoundInRadiansPerSec);
    ros::serialization::deserialize(stream, panUpperSpeedBoundInRadiansPerSec);
    ros::serialization::deserialize(stream, tiltUpperSpeedBoundInRadiansPerSec);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(header);
    size += ros::serialization::serializationLength(panMinimumValidPositionInRadians);
    size += ros::serialization::serializationLength(tiltMinimumValidPositionInRadians);
    size += ros::serialization::serializationLength(panMaximumValidPositionInRadians);
    size += ros::serialization::serializationLength(tiltMaximumValidPositionInRadians);
    size += ros::serialization::serializationLength(panLowerSpeedBoundInRadiansPerSec);
    size += ros::serialization::serializationLength(tiltLowerSpeedBoundInRadiansPerSec);
    size += ros::serialization::serializationLength(panUpperSpeedBoundInRadiansPerSec);
    size += ros::serialization::serializationLength(tiltUpperSpeedBoundInRadiansPerSec);
    return size;
  }

  typedef boost::shared_ptr< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct ReportStaticInfo
typedef  ::DPPanTilt_msgs::ReportStaticInfo_<std::allocator<void> > ReportStaticInfo;

typedef boost::shared_ptr< ::DPPanTilt_msgs::ReportStaticInfo> ReportStaticInfoPtr;
typedef boost::shared_ptr< ::DPPanTilt_msgs::ReportStaticInfo const> ReportStaticInfoConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace DPPanTilt_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > {
  static const char* value() 
  {
    return "949294eda1f9ef4201055f8d681ac295";
  }

  static const char* value(const  ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x949294eda1f9ef42ULL;
  static const uint64_t static_value2 = 0x01055f8d681ac295ULL;
};

template<class ContainerAllocator>
struct DataType< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > {
  static const char* value() 
  {
    return "DPPanTilt_msgs/ReportStaticInfo";
  }

  static const char* value(const  ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > {
  static const char* value() 
  {
    return "#\n\
# COPYRIGHT (C) 2005-2010\n\
# RE2, INC.\n\
# ALL RIGHTS RESERVED\n\
#\n\
# This is free software:\n\
# you can redistribute it and/or modify it under the terms of the GNU General\n\
# Public License as published by the Free Software Foundation, either version\n\
# 3 of the License, or (at your option) any later version.\n\
#\n\
# You should have received a copy of the GNU General Public License along\n\
# with this package.  If not, see <http://www.gnu.org/licenses/>.\n\
#\n\
# RE2, INC. disclaims all warranties with regard to this software, including\n\
# all implied warranties of merchantability and fitness, in no event shall\n\
# RE2, INC. be liable for any special, indirect or consequential damages or\n\
# any damages whatsoever resulting from loss of use, data or profits, whether\n\
# in an action of contract, negligence or other tortious action, arising out\n\
# of or in connection with the use or performance of this software.\n\
#\n\
#\n\
#\n\
\n\
# This message is used to report the static information about the\n\
# Pan/Tilt Unit.  It is not likely that much of this information will change\n\
# during the course of operation.\n\
\n\
Header header\n\
\n\
\n\
float32 panMinimumValidPositionInRadians\n\
float32 tiltMinimumValidPositionInRadians\n\
\n\
float32 panMaximumValidPositionInRadians\n\
float32 tiltMaximumValidPositionInRadians\n\
\n\
float32 panLowerSpeedBoundInRadiansPerSec\n\
float32 tiltLowerSpeedBoundInRadiansPerSec\n\
\n\
float32 panUpperSpeedBoundInRadiansPerSec\n\
float32 tiltUpperSpeedBoundInRadiansPerSec\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.panMinimumValidPositionInRadians);
    stream.next(m.tiltMinimumValidPositionInRadians);
    stream.next(m.panMaximumValidPositionInRadians);
    stream.next(m.tiltMaximumValidPositionInRadians);
    stream.next(m.panLowerSpeedBoundInRadiansPerSec);
    stream.next(m.tiltLowerSpeedBoundInRadiansPerSec);
    stream.next(m.panUpperSpeedBoundInRadiansPerSec);
    stream.next(m.tiltUpperSpeedBoundInRadiansPerSec);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct ReportStaticInfo_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::DPPanTilt_msgs::ReportStaticInfo_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "panMinimumValidPositionInRadians: ";
    Printer<float>::stream(s, indent + "  ", v.panMinimumValidPositionInRadians);
    s << indent << "tiltMinimumValidPositionInRadians: ";
    Printer<float>::stream(s, indent + "  ", v.tiltMinimumValidPositionInRadians);
    s << indent << "panMaximumValidPositionInRadians: ";
    Printer<float>::stream(s, indent + "  ", v.panMaximumValidPositionInRadians);
    s << indent << "tiltMaximumValidPositionInRadians: ";
    Printer<float>::stream(s, indent + "  ", v.tiltMaximumValidPositionInRadians);
    s << indent << "panLowerSpeedBoundInRadiansPerSec: ";
    Printer<float>::stream(s, indent + "  ", v.panLowerSpeedBoundInRadiansPerSec);
    s << indent << "tiltLowerSpeedBoundInRadiansPerSec: ";
    Printer<float>::stream(s, indent + "  ", v.tiltLowerSpeedBoundInRadiansPerSec);
    s << indent << "panUpperSpeedBoundInRadiansPerSec: ";
    Printer<float>::stream(s, indent + "  ", v.panUpperSpeedBoundInRadiansPerSec);
    s << indent << "tiltUpperSpeedBoundInRadiansPerSec: ";
    Printer<float>::stream(s, indent + "  ", v.tiltUpperSpeedBoundInRadiansPerSec);
  }
};


} // namespace message_operations
} // namespace ros

#endif // DPPANTILT_MSGS_MESSAGE_REPORTSTATICINFO_H

