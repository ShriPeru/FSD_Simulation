// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_msgs/msg/detail/steering_command__rosidl_typesupport_introspection_c.h"
#include "vehicle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_msgs/msg/detail/steering_command__functions.h"
#include "vehicle_msgs/msg/detail/steering_command__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_msgs__msg__SteeringCommand__init(message_memory);
}

void vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_fini_function(void * message_memory)
{
  vehicle_msgs__msg__SteeringCommand__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_member_array[2] = {
  {
    "steering_angle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__SteeringCommand, steering_angle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__SteeringCommand, speed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_members = {
  "vehicle_msgs__msg",  // message namespace
  "SteeringCommand",  // message name
  2,  // number of fields
  sizeof(vehicle_msgs__msg__SteeringCommand),
  false,  // has_any_key_member_
  vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_member_array,  // message members
  vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_type_support_handle = {
  0,
  &vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_members,
  get_message_typesupport_handle_function,
  &vehicle_msgs__msg__SteeringCommand__get_type_hash,
  &vehicle_msgs__msg__SteeringCommand__get_type_description,
  &vehicle_msgs__msg__SteeringCommand__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_msgs, msg, SteeringCommand)() {
  if (!vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_type_support_handle.typesupport_identifier) {
    vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_msgs__msg__SteeringCommand__rosidl_typesupport_introspection_c__SteeringCommand_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
