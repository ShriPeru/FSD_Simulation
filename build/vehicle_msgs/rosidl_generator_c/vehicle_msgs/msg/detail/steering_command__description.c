// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice

#include "vehicle_msgs/msg/detail/steering_command__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_vehicle_msgs
const rosidl_type_hash_t *
vehicle_msgs__msg__SteeringCommand__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xfc, 0x6e, 0x51, 0xda, 0xfa, 0xf0, 0x73, 0xab,
      0x5b, 0xff, 0x7f, 0x73, 0x84, 0x22, 0xab, 0xdb,
      0x04, 0x2e, 0x8f, 0x40, 0x0b, 0x80, 0xdd, 0x78,
      0x94, 0x90, 0x4b, 0x27, 0xa9, 0x9c, 0x10, 0x8f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char vehicle_msgs__msg__SteeringCommand__TYPE_NAME[] = "vehicle_msgs/msg/SteeringCommand";

// Define type names, field names, and default values
static char vehicle_msgs__msg__SteeringCommand__FIELD_NAME__steering_angle[] = "steering_angle";
static char vehicle_msgs__msg__SteeringCommand__FIELD_NAME__speed[] = "speed";

static rosidl_runtime_c__type_description__Field vehicle_msgs__msg__SteeringCommand__FIELDS[] = {
  {
    {vehicle_msgs__msg__SteeringCommand__FIELD_NAME__steering_angle, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {vehicle_msgs__msg__SteeringCommand__FIELD_NAME__speed, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
vehicle_msgs__msg__SteeringCommand__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {vehicle_msgs__msg__SteeringCommand__TYPE_NAME, 32, 32},
      {vehicle_msgs__msg__SteeringCommand__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float64 steering_angle\n"
  "float64 speed";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
vehicle_msgs__msg__SteeringCommand__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {vehicle_msgs__msg__SteeringCommand__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 37, 37},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
vehicle_msgs__msg__SteeringCommand__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *vehicle_msgs__msg__SteeringCommand__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
