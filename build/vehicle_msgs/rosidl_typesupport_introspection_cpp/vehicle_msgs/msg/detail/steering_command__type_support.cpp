// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "vehicle_msgs/msg/detail/steering_command__functions.h"
#include "vehicle_msgs/msg/detail/steering_command__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace vehicle_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SteeringCommand_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) vehicle_msgs::msg::SteeringCommand(_init);
}

void SteeringCommand_fini_function(void * message_memory)
{
  auto typed_message = static_cast<vehicle_msgs::msg::SteeringCommand *>(message_memory);
  typed_message->~SteeringCommand();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SteeringCommand_message_member_array[2] = {
  {
    "steering_angle",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs::msg::SteeringCommand, steering_angle),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "speed",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs::msg::SteeringCommand, speed),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SteeringCommand_message_members = {
  "vehicle_msgs::msg",  // message namespace
  "SteeringCommand",  // message name
  2,  // number of fields
  sizeof(vehicle_msgs::msg::SteeringCommand),
  false,  // has_any_key_member_
  SteeringCommand_message_member_array,  // message members
  SteeringCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  SteeringCommand_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SteeringCommand_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SteeringCommand_message_members,
  get_message_typesupport_handle_function,
  &vehicle_msgs__msg__SteeringCommand__get_type_hash,
  &vehicle_msgs__msg__SteeringCommand__get_type_description,
  &vehicle_msgs__msg__SteeringCommand__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace vehicle_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vehicle_msgs::msg::SteeringCommand>()
{
  return &::vehicle_msgs::msg::rosidl_typesupport_introspection_cpp::SteeringCommand_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vehicle_msgs, msg, SteeringCommand)() {
  return &::vehicle_msgs::msg::rosidl_typesupport_introspection_cpp::SteeringCommand_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
