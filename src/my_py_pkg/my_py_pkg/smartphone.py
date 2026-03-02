#!/usr/bin/env python3    #ye shebangline hai iska matlab ha isko python3 sey run kro
import rclpy                    # ye line rclpy lib ko import krwati h joki pub sub,topic banane karne me kaam ata h 
from rclpy.node import Node              # hum apna node banane ke lie Node class ko import kr rhe h
from example_interfaces.msg import String  # msg me simple text (string) bhejna

class SmartphoneNode(Node):             #hum ek class bana rhe h smartphonenode name ki.......y Node class ko inherit kr rha h .... ye bhi ke ros2 node ban jayega 
    def __init__(self):                      #ye constructor function h 
        super(). __init__("smartphone")             #super matlab parent class(Node) ka constructor call krna "smartphone" node ka name h
        self.subscriber_ = self.create_subscription(             #ye line SUBSCRIBER banana start krti ha aur subscriber topic ko sunta h
            String, "robot_news", self.callback_robot_news, 10)   # robot_news topic ka name ha ....... topic ka message type string hai.... jjab bhi message ayega , ye function run hoga (self.callback_robot_news)
        self.get_logger().info("Smart phone has been started.")   # ye bas terminal me log pring krega... ros2 me logger use hota hai print ki jagah

    def callback_robot_news(self, msg: String): #ye callback function hai jab robot_news topic pr message ayega, ye function chalega aur msg variable ke andar recived message hota h 
        self.get_logger().info(msg.data)  #msg.data me actual text hota h ye usko terminal par print krke deta h 

def main(args=None):                 #ye main function hai program ka starting point
    rclpy.init(args = args)         #ros2 python communincation start karta hai ye basically ros2 ko initiallize karta hai.
    node = SmartphoneNode()    # tumhara node object create hota h constructor(__init__)call hoga subscriber create ho jayega
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()