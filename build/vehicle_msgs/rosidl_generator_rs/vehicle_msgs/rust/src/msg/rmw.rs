#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "vehicle_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__SteeringCommand() -> *const std::ffi::c_void;
}

#[link(name = "vehicle_msgs__rosidl_generator_c")]
extern "C" {
    fn vehicle_msgs__msg__SteeringCommand__init(msg: *mut SteeringCommand) -> bool;
    fn vehicle_msgs__msg__SteeringCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SteeringCommand>, size: usize) -> bool;
    fn vehicle_msgs__msg__SteeringCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SteeringCommand>);
    fn vehicle_msgs__msg__SteeringCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SteeringCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<SteeringCommand>) -> bool;
}

// Corresponds to vehicle_msgs__msg__SteeringCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SteeringCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub steering_angle: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: f64,

}



impl Default for SteeringCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vehicle_msgs__msg__SteeringCommand__init(&mut msg as *mut _) {
        panic!("Call to vehicle_msgs__msg__SteeringCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SteeringCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__SteeringCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__SteeringCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__SteeringCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SteeringCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SteeringCommand where Self: Sized {
  const TYPE_NAME: &'static str = "vehicle_msgs/msg/SteeringCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__SteeringCommand() }
  }
}


