// ROS2 humble documentation implementation of subscriber 
        //  --> modified it to work for  a laserscan sensor subscription

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

using std::placeholders::_1;

class ScanSubscriber : public rclcpp::Node
{
  public:
    ScanSubscriber()
    : Node("scanner")
    {
subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
    "/scan", 
    10, 
    std::bind(&ScanSubscriber::topic_callback, this, std::placeholders::_1)
);
    }

  private:
    void topic_callback(const sensor_msgs::msg::LaserScan::ConstSharedPtr &msg) const
    {
    RCLCPP_INFO(
    this->get_logger(), 
    "Received a LaserScan message with %zu ranges.", 
    msg->ranges.size()
);
    }
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ScanSubscriber>());
  rclcpp::shutdown();
  return 0;
}
