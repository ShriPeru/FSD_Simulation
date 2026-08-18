// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vehicle_msgs/msg/steering_command.hpp"


#ifndef VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__BUILDER_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_msgs/msg/detail/steering_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_msgs
{

namespace msg
{

namespace builder
{

class Init_SteeringCommand_speed
{
public:
  explicit Init_SteeringCommand_speed(::vehicle_msgs::msg::SteeringCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_msgs::msg::SteeringCommand speed(::vehicle_msgs::msg::SteeringCommand::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_msgs::msg::SteeringCommand msg_;
};

class Init_SteeringCommand_steering_angle
{
public:
  Init_SteeringCommand_steering_angle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SteeringCommand_speed steering_angle(::vehicle_msgs::msg::SteeringCommand::_steering_angle_type arg)
  {
    msg_.steering_angle = std::move(arg);
    return Init_SteeringCommand_speed(msg_);
  }

private:
  ::vehicle_msgs::msg::SteeringCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_msgs::msg::SteeringCommand>()
{
  return vehicle_msgs::msg::builder::Init_SteeringCommand_steering_angle();
}

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__BUILDER_HPP_
