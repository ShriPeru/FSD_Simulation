FROM ros:jazzy-ros-base

# Install build tools and GLFW's dev package (system dependency, same as we did with apt earlier)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libglfw3-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Download and install MuJoCo, same as our native setup
RUN wget https://github.com/google-deepmind/mujoco/releases/download/3.11.0/mujoco-3.11.0-linux-x86_64.tar.gz \
    && tar -xzf mujoco-3.11.0-linux-x86_64.tar.gz \
    && mv mujoco-3.11.0 /root/mujoco \
    && rm mujoco-3.11.0-linux-x86_64.tar.gz

ENV HOME=/root

# Copy your package source into the container
WORKDIR /ros2_ws
COPY src/ src/

# Build it, same colcon command you've been running natively
RUN /bin/bash -c "source /opt/ros/jazzy/setup.bash && colcon build --packages-select mujoco_sim_node"

# Automatically source both ROS2 and your workspace whenever a shell starts in this container
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
RUN echo "source /ros2_ws/install/setup.bash" >> ~/.bashrc

CMD ["/bin/bash"]
