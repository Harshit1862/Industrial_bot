#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String


class RobotNewsStationNode(Node):                #this is the class where we can write any thing related to node.
    def __init__(self):
        super().__init__("robot_news_station")  #parent class (node) ka constructor call karna
        self.publisher_ = self.create_publisher(String, "robot_news", 10 ) #ye publisher hai ari samaj think more about it.
        self.timer_ = self.create_timer(0.5, self.publish_news)
        self.get_logger().info("Robot News Station has beed started.")

    def publish_news(self):
        msg = String()
        msg.data = "Hello Nextup"
        self.publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)           #initialise the ros2 communication
    node = RobotNewsStationNode()   #start a node
    rclpy.spin(node)                #keep node spinning
    rclpy.shutdown()                #shutdown the node

if __name__ == "__main__":
    main()