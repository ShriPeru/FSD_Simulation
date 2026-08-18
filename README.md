# FSD Simulation

A personal project dedicated to learning, designing, building, and understanding autonomous planning architectures and multi-stage Full Self-Driving (FSD) pipelines.

## Pipeline Architecture

This project explores the core responsibilities and data flow across each key layer of an autonomous driving system:

* **Sensing:** Processing raw sensor data streams (LiDAR, Camera, IMU/GNSS).
* **Perception:** State estimation, object detection, and dynamic obstacle tracking.
* **Mapping:** High-definition map parsing and local occupancy grid generation.
* **Prediction:** Forecasting surrounding agent behaviors and future trajectories.
* **Planning:** Global routing, behavior state machines, and local trajectory generation.
* **Control:** Executing planned trajectories via steering, throttle, and braking commands.
