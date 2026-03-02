#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;


class RobotNewsStationNode : public rclcpp::Node   //ek class ban rhi ha jiska name ha RobotNewsStationNode aur ye ros2 ke node se inherit ho rhi h

{
    public:
       RobotNewsStationNode() : Node("robot_news_station"), robot_name_("R2D2")
       {
         publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10); 
         
         timer_ = this->create_wall_timer(500ms, std::bind(&RobotNewsStationNode::publishNews, this));
         RCLCPP_INFO(this->get_logger(), "Robot News Station has beed started");

       }
    

    private:
       void publishNews()   //ye timer ke acc call hoga
       {
          auto msg = example_interfaces::msg::String();    //ek message object banaya jiska type string h
          msg.data = std::string("Hi, this is") +robot_name_+ std::string("from the robot news");  //message me data fill kiya 
          publisher_->publish(msg); //ye message publish kr rha ha topic par

       }
       std::string robot_name_;
       rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
       rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
};