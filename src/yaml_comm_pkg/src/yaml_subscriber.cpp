// Ye ROS2 ka main C++ header file hai
// Iske bina ROS2 node create nahi kar sakte
#include "rclcpp/rclcpp.hpp"

// Ye standard String message type ka header hai
// Hum topic me string message receive karne wale hain
#include "std_msgs/msg/string.hpp"

// Ye C++ ki file handling library hai
// Isse hum file open, write aur close kar sakte hain
#include <fstream>

// Yahan hum ek class bana rahe hain jo rclcpp::Node se inherit kar rahi hai
// Matlab ye ek ROS2 node hai
class YamlSubscriber : public rclcpp::Node
{
public:
    // Ye constructor hai jo tab call hoga jab node create hoga
    YamlSubscriber() : Node("yaml_subscriber")  // Node ka naam "yaml_subscriber" rakha
    {
        // Yahan subscription create kar rahe hain
        // Ye node "nextup" topic ko listen karega
        subscription_ =
            this->create_subscription<std_msgs::msg::String>(
                "nextup",   // Topic ka naam
                10,         // Queue size (QoS depth) - max 10 messages store karega
                std::bind(&YamlSubscriber::topic_callback, // Callback function ka naam
                          this,
                          std::placeholders::_1)); // _1 ka matlab first argument (message)

        // Ye terminal me info print karega jab node start hoga
        RCLCPP_INFO(this->get_logger(),
                    "YAML Subscriber Node Start ho gaya");
    }

private:
    // Ye callback function hai
    // Jab bhi message receive hoga ye function chalega
    void topic_callback(
        const std_msgs::msg::String::SharedPtr msg)  // msg ke andar received data hoga
    {
        // Yahan file ka path define kar rahe hain
        std::string output_path =
            "/home/harshit/config_files/nextup.yaml";

        try
        {
            // File open kar rahe hain truncate mode me
            // Matlab agar file pehle se hai to puri erase karke naya likhega
            std::ofstream file(output_path, std::ios::trunc);

            // Check kar rahe hain file sahi se open hui ya nahi
            if (!file.is_open())
            {
                RCLCPP_ERROR(this->get_logger(),
                             "File open nahi hui!");
                return; // Agar file open nahi hui to function yahin se exit
            }

            // Yahan YAML format me data likh rahe hain
            file << "received_data:\n";   // YAML key
            file << "  message: \""      // message key
                 << msg->data            // actual topic ka data
                 << "\"\n";

            // File close kar rahe hain
            file.close();

            // Success message print kar rahe hain
            RCLCPP_INFO(this->get_logger(),
                        "nextup.yaml updated");
        }
        catch (const std::exception &e)
        {
            // Agar koi error aaye to ye block chalega
            RCLCPP_ERROR(this->get_logger(),
                         "Exception aayi: %s",
                         e.what());
        }
    }

    // Ye subscription ka pointer hai
    // ROS2 internally isko manage karta hai
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

// Main function yahin se program start hota hai
int main(int argc, char * argv[])
{
    // ROS2 system initialize ho raha hai
    rclcpp::init(argc, argv);

    // Yahan node create ho raha hai aur continuously run karega (spin)
    rclcpp::spin(std::make_shared<YamlSubscriber>());

    // Jab program band hoga tab ROS2 shutdown hoga
    rclcpp::shutdown();

    return 0; // Program successful exit
}