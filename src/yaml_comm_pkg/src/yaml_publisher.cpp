// ROS 2 ki core C++ library include kar rahe hain
#include "rclcpp/rclcpp.hpp"
// Standard String message type ko include kar rahe hain publish karne ke liye
#include "std_msgs/msg/string.hpp"
// YAML files ko read/parse karne ke liye yaml-cpp library
#include "yaml-cpp/yaml.h"
// Time aur duration ke functions ke liye (jaise timer set karna)
#include <chrono>

// Time literals jaise '2s' (2 seconds) easily use karne ke liye ye namespace use kiya
using namespace std::chrono_literals;

// Ek nayi class bana rahe hain 'YamlPublisher' jo ROS 2 'Node' ko inherit karti hai
class YamlPublisher : public rclcpp::Node
{
public:
    // Class ka constructor. Yahan hum apne ROS node ka naam "yaml_publisher" set kar rahe hain
    YamlPublisher() : Node("yaml_publisher")
    {
        // Ek publisher create kiya jo String type ka data "nextup" naam ke topic par bhejega. 
        // 10 yahan queue ka size hai.
        publisher_ = this->create_publisher<std_msgs::msg::String>("nextup", 10);

        // Ek timer banaya jo har 2 second (2s) mein trigger hoga. 
        // Jab bhi trigger hoga, ye 'publish_message' function ko call karega.
        timer_ = this->create_wall_timer(
            2s, std::bind(&YamlPublisher::publish_message, this));
    }

private:
    // Ye wo function hai jo har 2 second mein automatically run hoga
    void publish_message()
    {
        // Try block start kar rahe hain, taaki agar file read karne mein koi error aaye toh program crash na ho
        try
        {
            // Aapki YAML file ka hardcoded path ek string mein save kar liya
            std::string yaml_path =
                "/home/harshit/config_files/harshit.yaml";

            // yaml-cpp library ka use karke YAML file ko load kiya
            YAML::Node config = YAML::LoadFile(yaml_path);

            // YAML file ke andar se "message" key ko dhundha aur uski value ko string format mein nikal liya
            std::string message_data =
                config["message"].as<std::string>();

            // ROS 2 ka String message object banaya
            std_msgs::msg::String msg;
            // Upar jo yaml se message data nikala tha, wo is msg ke 'data' field mein daal diya
            msg.data = message_data;

            // Message ko 'nextup' topic par publish kar diya
            publisher_->publish(msg);

            // Terminal (console) par log print kiya ki humne kya publish kiya hai (Info level)
            RCLCPP_INFO(this->get_logger(),
                        "Published: %s",
                        msg.data.c_str());
        }
        // Agar upar ke code mein koi dikkat aati hai (jaise file exist nahi karti ya YAML format galat hai)
        catch (const std::exception &e)
        {
            // Error ko terminal par print kiya (Error level, mostly red color mein dikhega)
            RCLCPP_ERROR(this->get_logger(),
                         "YAML Read Error: %s",
                         e.what());
        }
    }

    // Publisher ka pointer declare kiya
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    // Timer ka pointer declare kiya
    rclcpp::TimerBase::SharedPtr timer_;
};

// Yahan se aapka main program execute hona shuru hota hai
int main(int argc, char * argv[])
{
    // ROS 2 system ko initialize kiya
    rclcpp::init(argc, argv);
    
    // YamlPublisher node ka ek object banaya aur usko spin mein daal diya. 
    // Spin ka matlab hai ki program yahin ruk kar continuously node ko run karta rahega (timer chalta rahega)
    rclcpp::spin(std::make_shared<YamlPublisher>());
    
    // Jab user program ko band karega (Ctrl+C), toh ROS 2 ko cleanly shutdown karne ke liye
    rclcpp::shutdown();
    
    // Program successfully khatam ho gaya
    return 0;
}