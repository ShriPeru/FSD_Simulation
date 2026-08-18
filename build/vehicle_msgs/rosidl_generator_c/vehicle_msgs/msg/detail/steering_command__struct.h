// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vehicle_msgs/msg/steering_command.h"


#ifndef VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_H_
#define VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SteeringCommand in the package vehicle_msgs.
typedef struct vehicle_msgs__msg__SteeringCommand
{
  double steering_angle;
  double speed;
} vehicle_msgs__msg__SteeringCommand;

// Struct for a sequence of vehicle_msgs__msg__SteeringCommand.
typedef struct vehicle_msgs__msg__SteeringCommand__Sequence
{
  vehicle_msgs__msg__SteeringCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_msgs__msg__SteeringCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_MSGS__MSG__DETAIL__STEERING_COMMAND__STRUCT_H_
