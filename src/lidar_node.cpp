#include <chrono>
#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class LidarNode : public rclcpp::Node
{
public:
    LidarNode()
    : Node("lidar_control_node")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 
            10, 
            std::bind(&LidarNode::scan_callback, this, _1));

        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }

private:
    void scan_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        // naive obstacle detecting logic
        bool obstacle_detected = false;
        for (const float &range : msg->ranges) {
            if (range < 1.0) { 
                obstacle_detected = true;
                break;
            }
        }

        auto message = geometry_msgs::msg::Twist();
        if (obstacle_detected) {
            message.linear.x = 0.0;
            message.angular.z = 0.5; 
        } 
        else {
            message.linear.x = 0.5;
        }

        publisher_->publish(message);
            if (obstacle_detected) {
        RCLCPP_INFO(this->get_logger(), "Obstacle detected.");
    } else {
        RCLCPP_INFO(this->get_logger(), "No obstacle detected.");
    }

    RCLCPP_INFO(this->get_logger(), "Publishing linear x: '%f', angular z: '%f'", message.linear.x, message.angular.z);

        
    }

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarNode>());
    rclcpp::shutdown();
    return 0;
}
