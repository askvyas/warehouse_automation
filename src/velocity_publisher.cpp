// Velocity Publisher to publish 0.5 linear to cmd_vel topic 


#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;


class VelocityPublisher : public rclcpp::Node
{
  public:
    VelocityPublisher()
    : Node("velocity_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
      

      timer_ = this->create_wall_timer(
      500ms, std::bind(&VelocityPublisher::timer_callback, this));
    }

  private:
    void timer_callback()
    {
        
          auto message = geometry_msgs::msg::Twist();
            message.linear.x=0.5;
            publisher_->publish(message);
        
        RCLCPP_INFO(this->get_logger(), "Publishing linear x: '%f'", message.linear.x);

      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocityPublisher>());
  rclcpp::shutdown();
  return 0;
}