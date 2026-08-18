// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vehicle_msgs:msg/SteeringCommand.idl
// generated code does not contain a copyright notice
#include "vehicle_msgs/msg/detail/steering_command__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
vehicle_msgs__msg__SteeringCommand__init(vehicle_msgs__msg__SteeringCommand * msg)
{
  if (!msg) {
    return false;
  }
  // steering_angle
  // speed
  return true;
}

void
vehicle_msgs__msg__SteeringCommand__fini(vehicle_msgs__msg__SteeringCommand * msg)
{
  if (!msg) {
    return;
  }
  // steering_angle
  // speed
}

bool
vehicle_msgs__msg__SteeringCommand__are_equal(const vehicle_msgs__msg__SteeringCommand * lhs, const vehicle_msgs__msg__SteeringCommand * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // steering_angle
  if (lhs->steering_angle != rhs->steering_angle) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  return true;
}

bool
vehicle_msgs__msg__SteeringCommand__copy(
  const vehicle_msgs__msg__SteeringCommand * input,
  vehicle_msgs__msg__SteeringCommand * output)
{
  if (!input || !output) {
    return false;
  }
  // steering_angle
  output->steering_angle = input->steering_angle;
  // speed
  output->speed = input->speed;
  return true;
}

vehicle_msgs__msg__SteeringCommand *
vehicle_msgs__msg__SteeringCommand__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_msgs__msg__SteeringCommand * msg = (vehicle_msgs__msg__SteeringCommand *)allocator.allocate(sizeof(vehicle_msgs__msg__SteeringCommand), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vehicle_msgs__msg__SteeringCommand));
  bool success = vehicle_msgs__msg__SteeringCommand__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vehicle_msgs__msg__SteeringCommand__destroy(vehicle_msgs__msg__SteeringCommand * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vehicle_msgs__msg__SteeringCommand__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vehicle_msgs__msg__SteeringCommand__Sequence__init(vehicle_msgs__msg__SteeringCommand__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_msgs__msg__SteeringCommand * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(vehicle_msgs__msg__SteeringCommand)) {
      return false;
    }
    data = (vehicle_msgs__msg__SteeringCommand *)allocator.zero_allocate(size, sizeof(vehicle_msgs__msg__SteeringCommand), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vehicle_msgs__msg__SteeringCommand__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vehicle_msgs__msg__SteeringCommand__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vehicle_msgs__msg__SteeringCommand__Sequence__fini(vehicle_msgs__msg__SteeringCommand__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vehicle_msgs__msg__SteeringCommand__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vehicle_msgs__msg__SteeringCommand__Sequence *
vehicle_msgs__msg__SteeringCommand__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vehicle_msgs__msg__SteeringCommand__Sequence * array = (vehicle_msgs__msg__SteeringCommand__Sequence *)allocator.allocate(sizeof(vehicle_msgs__msg__SteeringCommand__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vehicle_msgs__msg__SteeringCommand__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vehicle_msgs__msg__SteeringCommand__Sequence__destroy(vehicle_msgs__msg__SteeringCommand__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vehicle_msgs__msg__SteeringCommand__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vehicle_msgs__msg__SteeringCommand__Sequence__are_equal(const vehicle_msgs__msg__SteeringCommand__Sequence * lhs, const vehicle_msgs__msg__SteeringCommand__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vehicle_msgs__msg__SteeringCommand__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vehicle_msgs__msg__SteeringCommand__Sequence__copy(
  const vehicle_msgs__msg__SteeringCommand__Sequence * input,
  vehicle_msgs__msg__SteeringCommand__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(vehicle_msgs__msg__SteeringCommand)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(vehicle_msgs__msg__SteeringCommand);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vehicle_msgs__msg__SteeringCommand * data =
      (vehicle_msgs__msg__SteeringCommand *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vehicle_msgs__msg__SteeringCommand__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vehicle_msgs__msg__SteeringCommand__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vehicle_msgs__msg__SteeringCommand__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
