#include <mujoco/mujoco.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <vehicle_msgs/msg/steering_command.hpp>


mjModel* model = nullptr;
mjData* data = nullptr;
mjvCamera cam;
mjvOption opt;
mjvScene scn;
mjrContext con;
// Add these globals near your other globals (cam, opt, scn, con)
bool button_left = false;
bool button_middle = false;
bool button_right = false;
double lastx = 0;
double lasty = 0;
double car_x = 0.0;
double car_y = 0.0;
double car_theta = 0.0;
double wheelbase;  
rclcpp::Node::SharedPtr ros_node;
rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pos_publisher;
rclcpp::Subscription<vehicle_msgs::msg::SteeringCommand>::SharedPtr command_sub_;
double current_speed = 0.0;      // no motion until a real command arrives
double current_steering = 0.0;


void mouse_button(GLFWwindow* window, int button, int act, int mods) {
    button_left   = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)   == GLFW_PRESS);
    button_middle = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
    button_right  = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)  == GLFW_PRESS);
    glfwGetCursorPos(window, &lastx, &lasty);
}

void mouse_move(GLFWwindow* window, double xpos, double ypos) {
    if (!button_left && !button_middle && !button_right) return;

    double dx = xpos - lastx;
    double dy = ypos - lasty;
    lastx = xpos;
    lasty = ypos;

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ||
                      (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

    mjtMouse action;
    if (button_right)
        action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
    else if (button_left)
        action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
    else
        action = mjMOUSE_ZOOM;

    mjv_moveCamera(model, action, dx / height, dy / height, &cam);
}
void updateCameraMovement(GLFWwindow* window) {
    const double move_speed = 0.05;

    // Forward/backward and left/right move relative to the camera's current azimuth (facing direction)
    double azimuth_rad = cam.azimuth * M_PI / 180.0;
    double forward_x = -sin(azimuth_rad);
    double forward_y = cos(azimuth_rad);
    double right_x = cos(azimuth_rad);
    double right_y = sin(azimuth_rad);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cam.lookat[0] += forward_x * move_speed;
        cam.lookat[1] += forward_y * move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cam.lookat[0] -= forward_x * move_speed;
        cam.lookat[1] -= forward_y * move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cam.lookat[0] -= right_x * move_speed;
        cam.lookat[1] -= right_y * move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cam.lookat[0] += right_x * move_speed;
        cam.lookat[1] += right_y * move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cam.lookat[2] += move_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        cam.lookat[2] -= move_speed;
    }
}
void scroll(GLFWwindow* window, double xoffset, double yoffset) {
    mjv_moveCamera(model, mjMOUSE_ZOOM, 0, -0.05 * yoffset, &cam);
}
void keyboard(GLFWwindow* window, int key, int scancode, int act, int mods) {
    if (act == GLFW_PRESS && key == GLFW_KEY_BACKSPACE) {
        mj_resetData(model, data);
        mj_forward(model, data);
    }
    if (act == GLFW_PRESS && key == GLFW_KEY_Q) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
void steeringCommandCallback(const vehicle_msgs::msg::SteeringCommand::SharedPtr msg) {
    current_speed = msg->speed;
    current_steering = msg->steering_angle;
}
int main() {
    char error[1000] = "";
    std::string model_path = ament_index_cpp::get_package_share_directory("mujoco_sim_node") + "/model.xml";
    model = mj_loadXML(model_path.c_str(), nullptr, error, 1000);
    if (!model) {
        printf("Failed to load model: %s\n", error);
        return 1;
    }
    data = mj_makeData(model);
    
    rclcpp::init(0, nullptr);
    ros_node = std::make_shared<rclcpp::Node>("mujoco_sim_node");
    pos_publisher = ros_node->create_publisher<geometry_msgs::msg::Point>("ball_position", 10);
    ros_node->declare_parameter("wheelbase", 0.15);
    wheelbase = ros_node->get_parameter("wheelbase").as_double();
    command_sub_ = ros_node->create_subscription<vehicle_msgs::msg::SteeringCommand>(
    "steering_command", 10, steeringCommandCallback);
    if (!glfwInit()) {
        printf("Could not initialize GLFW\n");
        return 1;
    }
    GLFWwindow* window = glfwCreateWindow(1200, 900, "MuJoCo sim", nullptr, nullptr);
    if (!window) {
        printf("Could not create GLFW window\n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keyboard);
    glfwSetMouseButtonCallback(window, mouse_button);
    glfwSetCursorPosCallback(window, mouse_move);
    glfwSetScrollCallback(window, scroll);
    mjv_defaultCamera(&cam);
    mjv_defaultOption(&opt);
    mjv_defaultScene(&scn);
    mjr_defaultContext(&con);

    mjv_makeScene(model, &scn, 2000);
    mjr_makeContext(model, &con, mjFONTSCALE_150);

    while (!glfwWindowShouldClose(window)) {
        mjtNum simstart = data->time;
        while (data->time - simstart < 1.0 / 60.0) {
            double v = current_speed;
            double delta = current_steering;
            double dt = model->opt.timestep;

            car_x += v * cos(car_theta) * dt;
            car_y += v * sin(car_theta) * dt;
            car_theta += (v / wheelbase) * tan(delta) * dt;

            data->qpos[0] = car_x;
            data->qpos[1] = car_y;
            data->qpos[2] = car_theta;

            data->time += dt;   // <-- add this line, manually advancing time since mj_forward doesn't

            mj_forward(model, data);
            auto msg = geometry_msgs::msg::Point();
            msg.x = data->qpos[0];
            msg.y = data->qpos[1];
            msg.z = data->qpos[2];
            pos_publisher->publish(msg);
        }

        mjrRect viewport = {0, 0, 0, 0};
        glfwGetFramebufferSize(window, &viewport.width, &viewport.height);

        mjv_updateScene(model, data, &opt, nullptr, &cam, mjCAT_ALL, &scn);
        mjr_render(viewport, &scn, &con);

        glfwSwapBuffers(window);
        glfwPollEvents();
        updateCameraMovement(window);
        rclcpp::spin_some(ros_node);
    }

    mjv_freeScene(&scn);
    mjr_freeContext(&con);
    mj_deleteData(data);
    mj_deleteModel(model);
    glfwTerminate();

    pos_publisher.reset();
    ros_node.reset();
    command_sub_.reset();
    rclcpp::shutdown();
    return 0;
}
