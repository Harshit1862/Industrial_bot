#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using std::placeholders::_1;

class BatterySubscriber : public rclcpp::Node
{
public:
    BatterySubscriber() : Node("battery_subscriber")
    {
        // Create subscriber to "battery_percentage" topic
        subscription_ = this->create_subscription<std_msgs::msg::Float32>(
            "battery_percentage",
            10,
            std::bind(&BatterySubscriber::batteryCallback, this, _1)
        );

        RCLCPP_INFO(this->get_logger(), "Battery Subscriber Node Started...");
    }

private:
    // Callback function runs when a message is received
    void batteryCallback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        // Print battery percentage
        RCLCPP_INFO(this->get_logger(), "Battery Percentage: %.1f%%", msg->data);
    }

    // Subscriber object
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<BatterySubscriber>());

    rclcpp::shutdown();
    return 0;
}
