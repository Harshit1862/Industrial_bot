#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

class CpuSubscriber : public rclcpp::Node
{
public:
    CpuSubscriber() : Node("cpu_subscriber")
    {
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "cpu_usage",
            10,
            std::bind(&CpuSubscriber::CpuCallback, this, std::placeholders::_1)
        );
    }

private:
    void CpuCallback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "CPU Usage: %.1f%%", msg->data);
    }

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CpuSubscriber>());
    rclcpp::shutdown();
    return 0;
}
