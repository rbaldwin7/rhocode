/* Auto-generated by genmsg_cpp for file /home/noam/ros_workspace/PanTilt/DPPanTilt_msgs/msg/SetVelocityPan.msg */
#ifndef DPPANTILT_MSGS_MESSAGE_SETVELOCITYPAN_H
#define DPPANTILT_MSGS_MESSAGE_SETVELOCITYPAN_H
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


namespace DPPanTilt_msgs
{
template <class ContainerAllocator>
struct SetVelocityPan_ {
  typedef SetVelocityPan_<ContainerAllocator> Type;

  SetVelocityPan_()
  : panVelocityInRadiansPerSec(0.0)
  {
  }

  SetVelocityPan_(const ContainerAllocator& _alloc)
  : panVelocityInRadiansPerSec(0.0)
  {
  }

  typedef float _panVelocityInRadiansPerSec_type;
  float panVelocityInRadiansPerSec;


private:
  static const char* __s_getDataType_() { return "DPPanTilt_msgs/SetVelocityPan"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "e892766b6e81cfc1a2703711ab4dcbd7"; }
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
# This message is used to set the velocity of the Pan axis.\n\
# This message is only valid if the unit is in Velocity control.\n\
\n\
float32 panVelocityInRadiansPerSec\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, panVelocityInRadiansPerSec);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, panVelocityInRadiansPerSec);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(panVelocityInRadiansPerSec);
    return size;
  }

  typedef boost::shared_ptr< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct SetVelocityPan
typedef  ::DPPanTilt_msgs::SetVelocityPan_<std::allocator<void> > SetVelocityPan;

typedef boost::shared_ptr< ::DPPanTilt_msgs::SetVelocityPan> SetVelocityPanPtr;
typedef boost::shared_ptr< ::DPPanTilt_msgs::SetVelocityPan const> SetVelocityPanConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace DPPanTilt_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > {
  static const char* value() 
  {
    return "e892766b6e81cfc1a2703711ab4dcbd7";
  }

  static const char* value(const  ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xe892766b6e81cfc1ULL;
  static const uint64_t static_value2 = 0xa2703711ab4dcbd7ULL;
};

template<class ContainerAllocator>
struct DataType< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > {
  static const char* value() 
  {
    return "DPPanTilt_msgs/SetVelocityPan";
  }

  static const char* value(const  ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > {
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
# This message is used to set the velocity of the Pan axis.\n\
# This message is only valid if the unit is in Velocity control.\n\
\n\
float32 panVelocityInRadiansPerSec\n\
\n\
";
  }

  static const char* value(const  ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.panVelocityInRadiansPerSec);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct SetVelocityPan_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::DPPanTilt_msgs::SetVelocityPan_<ContainerAllocator> & v) 
  {
    s << indent << "panVelocityInRadiansPerSec: ";
    Printer<float>::stream(s, indent + "  ", v.panVelocityInRadiansPerSec);
  }
};


} // namespace message_operations
} // namespace ros

#endif // DPPANTILT_MSGS_MESSAGE_SETVELOCITYPAN_H

