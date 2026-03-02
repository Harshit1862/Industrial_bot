// #include "rclcpp/rclcpp.hpp"
// #include "example_interfaces/msg/string.hpp"

// using namespace std::placeholders;

// class NumberPublisherNode: public rclcpp::Node
// {
// public:
//     NumberPublisherNode() : Node("Counter")
//     {
//       publisher_ = this->create_publisher<example_interfaces::msg::String>("counting", 10,std::bind(&NumberPublisherNode::callbackCount, this, _1));
//       timer_ = this->create_wall_timer(500ms, std::bind(&NumberPublisherNode::publishNews, this));
//       RCLCPP_INFO(this->get_logger(), "Counter node Started!");
        

//     }
// private:
//     void callbackCount(const example_interfaces::msg::String::SharedPtr msg)
//     {
//         RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
//     }
//     rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
// };

// int main(int argc, char **argv)

// {
//     rclcpp::init(argc, argv);
//     auto node = std::make_shared<NumberPublisherNode>();
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }