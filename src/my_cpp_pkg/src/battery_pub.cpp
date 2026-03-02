#include "rclcpp/rclcpp.hpp"              // ROS2 core C++ library
#include "std_msgs/msg/float32.hpp"       // Float32 message type
#include <fstream>                        // To read system files and used for file handelling

class BatteryPublisher : public rclcpp::Node
{
public:
  BatteryPublisher() : Node("battery_publisher") // Create node with name
  {
    // Create publisher on topic "battery_percentage"
    publisher_ = this->create_publisher<std_msgs::msg::Float32>(
      "battery_percentage", 10);

    // Call publishBattery() every 5 seconds
    timer_ = this->create_wall_timer(
      std::chrono::seconds(5),
      std::bind(&BatteryPublisher::publishBattery, this));
  }

private:
  // Read real battery value and publish it
  void publishBattery()
  {
    std::ifstream file("/sys/class/power_supply/BAT0/capacity"); // Open battery file

    if (!file.is_open()) return;   // Exit if battery file not found

    float battery;                 // Variable to store battery value
    file >> battery;               // Read battery percentage
    file.close();                  // Close file

    std_msgs::msg::Float32 msg;    // Create message
    msg.data = battery;            // Assign battery value

    publisher_->publish(msg);      // Publish message
  }

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_; // Publisher object
  rclcpp::TimerBase::SharedPtr timer_;                              // Timer object
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);                              // Initialize ROS2
  rclcpp::spin(std::make_shared<BatteryPublisher>());    // Run node
  rclcpp::shutdown();                                    // Shutdown ROS2
  return 0;                                              // Exit program
};
