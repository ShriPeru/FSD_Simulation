#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to vehicle_msgs__msg__SteeringCommand

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SteeringCommand::default())
  }
}

impl rosidl_runtime_rs::Message for SteeringCommand {
  type RmwMsg = super::msg::rmw::SteeringCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        steering_angle: msg.steering_angle,
        speed: msg.speed,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      steering_angle: msg.steering_angle,
      speed: msg.speed,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      steering_angle: msg.steering_angle,
      speed: msg.speed,
    }
  }
}


