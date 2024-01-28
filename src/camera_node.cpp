// Reference : CVbridge to ROS2 :   https://gist.github.com/nightduck/a07c185faad82aeaacbfa87298d035c0

#include <stdlib.h>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "image_transport/image_transport.hpp"
#include <cv_bridge/cv_bridge.h>
#include "sensor_msgs/image_encodings.hpp"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std::chrono_literals;

class Camera_Node : public rclcpp::Node{
private:
double frame_rate_;

    const std::string OPENCV_WINDOW = "Image window";
    image_transport::Subscriber sub_;
    image_transport::Publisher pub_;

    void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr &msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
           cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
        }
        catch(cv_bridge::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }
        // if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
        //     cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));
        // modification to original to convert the image color space 
        cv::cvtColor(cv_ptr->image, cv_ptr->image, cv::COLOR_BGR2RGB);


        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        cv::waitKey(3);
        pub_.publish(cv_ptr->toImageMsg());
    }


public:
    Camera_Node():
    Node("watcher"), frame_rate_(30.0){
        cv::namedWindow(OPENCV_WINDOW);
                rmw_qos_profile_t custom_qos = rmw_qos_profile_default;
        pub_ = image_transport::create_publisher(this, "out_image_base_topic", custom_qos);
        sub_ = image_transport::create_subscription(this, "/camera/image_raw",
                std::bind(&Camera_Node::image_callback, this, std::placeholders::_1), "raw", custom_qos);


    }
    ~Camera_Node()
    {
        cv::destroyWindow(OPENCV_WINDOW);
    }
};
int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera_Node>());
    rclcpp::shutdown();
    return 0;
}

