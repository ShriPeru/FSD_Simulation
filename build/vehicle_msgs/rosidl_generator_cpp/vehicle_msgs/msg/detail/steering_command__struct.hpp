// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vehicle_msgs/msg/steering_command.hpp"


#ifndef VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__vehicle_msgs__msg__SteeringCommand __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_msgs__msg__SteeringCommand __declspec(deprecated)
#endif

namespace vehicle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SteeringCommand_
{
  using Type = SteeringCommand_<ContainerAllocator>;

  explicit SteeringCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering_angle = 0.0;
      this->speed = 0.0;
    }
  }

  explicit SteeringCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->steering_angle = 0.0;
      this->speed = 0.0;
    }
  }

  // field types and members
  using _steering_angle_type =
    double;
  _steering_angle_type steering_angle;
  using _speed_type =
    double;
  _speed_type speed;

  // setters for named parameter idiom
  Type & set__steering_angle(
    const double & _arg)
  {
    this->steering_angle = _arg;
    return *this;
  }
  Type & set__speed(
    const double & _arg)
  {
    this->speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_msgs__msg__SteeringCommand
    std::shared_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_msgs__msg__SteeringCommand
    std::shared_ptr<vehicle_msgs::msg::SteeringCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SteeringCommand_ & other) const
  {
    if (this->steering_angle != other.steering_angle) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const SteeringCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SteeringCommand_

// alias to use template instance with default allocator
using SteeringCommand =
  vehicle_msgs::msg::SteeringCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_HPP_
