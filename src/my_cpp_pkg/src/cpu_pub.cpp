#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include <fstream>
#include <string>


class CpuPublisher : public rclcpp::Node
{
public:
    CpuPublisher() : Node("cpu_publisher")
    {
        publisher_ = this->create_publisher<std_msgs::msg::Float32>(
            "cpu_usage", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(5),
            std::bind(&CpuPublisher::publishCpu, this));
    }

private:
    void publishCpu()
    {
        std::ifstream file("/proc/stat");
        if (!file.is_open()) return;

        std::string cpu_label;
        long user, nice, system, idle;

        file >> cpu_label >> user >> nice >> system >> idle;
        file.close();

        // Abhi sirf demo: idle ko publish kar rahe hain
        std_msgs::msg::Float32 msg;
        msg.data = (float)idle;

        publisher_->publish(msg);
    }

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CpuPublisher>());
    rclcpp::shutdown();
    return 0;
}