#!/usr/bin/env python3
import rclpy                           # ROS2 python library
from rclpy.node import Node            # Node class import
from example_interfaces.srv import AddTwoInts   # Service type import

class AddTwoIntsServerNode(Node):      # Ye class ek ROS2 Node banayegi

    def __init__(self):
        super().__init__("add_two_ints_server")   # Node ka naam set

        # Service server create ho raha hai
        # Service type = AddTwoInts
        # Service name = "add_two_ints"
        # Callback = self.callback_add_two_ints
        self.server_ = self.create_service(
            AddTwoInts, "add_two_ints", self.callback_add_two_ints)

        # Terminal pe info print
        self.get_logger().info("Add Two Ints server has been started")

    # Ye function tab chalega jab client request bhejega
    def callback_add_two_ints(self, request: AddTwoInts.Request, response: AddTwoInts.Response):

        # request.a aur request.b client se aaye numbers hain
        # response.sum me unka sum store kar rahe hain
        response.sum = request.a + request.b

        # Server side log print kar rahe hain
        self.get_logger().info(
            str(request.a) + " + " + str(request.b) + " = " + str(response.sum)
        )

        # Response return karna compulsory hai
        return response


def main(args=None):
    rclpy.init(args=args)              # ROS2 start

    node = AddTwoIntsServerNode()      # Server node ka object

    rclpy.spin(node)                   # Node ko alive rakhta hai (server ON rahe)

    rclpy.shutdown()                   # ROS2 stop


if __name__ == "__main__":
    main()                             # main run
