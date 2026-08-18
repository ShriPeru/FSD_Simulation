// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vehicle_msgs/msg/steering_command.hpp"


#ifndef VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__TRAITS_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_msgs/msg/detail/steering_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const SteeringCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: steering_angle
  {
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SteeringCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: steering_angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_angle: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_angle, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SteeringCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vehicle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_msgs::msg::SteeringCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_msgs::msg::SteeringCommand & msg)
{
  return vehicle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_msgs::msg::SteeringCommand>()
{
  return "vehicle_msgs::msg::SteeringCommand";
}

template<>
inline const char * name<vehicle_msgs::msg::SteeringCommand>()
{
  return "vehicle_msgs/msg/SteeringCommand";
}

template<>
struct has_fixed_size<vehicle_msgs::msg::SteeringCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<vehicle_msgs::msg::SteeringCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<vehicle_msgs::msg::SteeringCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__TRAITS_HPP_
