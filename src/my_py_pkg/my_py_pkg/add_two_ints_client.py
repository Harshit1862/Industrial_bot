import rclpy                               # ROS2 Python library
from rclpy.node import Node                # Node class import
from example_interfaces.srv import AddTwoInts  # Service type import (AddTwoInts)
from functools import partial  

class AddTwoIntsClient(Node):              # Ye class ROS2 Node banegi

    def __init__(self):
        # Parent Node ka constructor call ho raha hai
        # Node ka naam set ho raha hai: add_two_ints_client
        super().__init__("add_two_ints_client")

        # Service client create ho raha hai
        # Service type = AddTwoInts
        # Service name = "add_two_ints"
        self.client_ = self.create_client(AddTwoInts, "add_two_ints")

    def call_add_two_ints(self, a, b):
        # Jab tak service server available nahi hota tab tak wait karega
        # 1 second wait karke check karta rahega
        while not self.client_.wait_for_service(1.0):
            # Warning print karega ki server ka wait kar rahe hain
            self.get_logger().warn("Waiting for Add Two Ints server...")

        # Request object ban raha hai (AddTwoInts ka)
        request = AddTwoInts.Request()

        # Request ke andar values set ho rahi hain
        request.a = a
        request.b = b

        # Service ko async call kar rahe hain (matlab program rukega nahi)
        future = self.client_.call_async(request)

        # Jab response aayega tab ye callback function automatically chalega
        future.add_done_callback(partial(self.callback_call_add_two_ints, request=request))

    def callback_call_add_two_ints(self, future, request):
        # Future ke andar response stored hota hai
        response = future.result()

        # Response me sum field hota hai
        # Console me print kar rahe hain
        self.get_logger().info(str(request.a) + " + " +
                           str(request.b) + " = " +str(response.sum))


def main(args=None):
    # ROS2 communication start (initialize)
    rclpy.init(args=args)

    # Client node ka object create ho raha hai
    node = AddTwoIntsClient()

    # Service call kar rahe hain: 2 + 7
    node.call_add_two_ints(2, 7)
    node.call_add_two_ints(2, 8)
    node.call_add_two_ints(2, 6)
    node.call_add_two_ints(2, 9)
    node.call_add_two_ints(2, 4)
    node.call_add_two_ints(2, 0)

    # Node ko alive rakhta hai (taaki callback run ho sake)
    rclpy.spin(node)

    # ROS2 shutdown (end)
    rclpy.shutdown()


if __name__ == "__main__":
    # Main function run karega
    main()
