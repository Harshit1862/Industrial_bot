import rclpy                                                               #bring this lib so i can use, without this ros2 will not work.
from rclpy.node import Node                                                #bring only node, not everything. Every ros program must be a node.
import psutil
from std_msgs.msg import Int32                                             #Standard ros messages(std_msgs), message type(msg), Message that holds one integer number(Int32)
import random                                                              #Used to generate random numbers

class BatteryMonitor(Node):                                                #Used to create object(class), Name of class(BatteryMonitor), BatteryMonitor is a type of node((Node)).
    def __init__(self):
        super().__init__('battery_monitor')                                #Calls parent class(Node)(super()), Calls Node's Constructor, Name of ROS node('battery monitor'). 
                                                                           #Hey Node class, initialize yourself with this name.
        self.publisher_ = self.create_publisher(Int32, 'battery_level',10) #This node will publish integer battery data on battery_level topic. ROS funtion to send data(create_publisher)
        self.timer = self.create_timer(1.0, self.publish_battery)          #Every 1 second, run publish_battery()

        self.battery = 100                                                 #initial battery = 100%
        self.get_logger().info('Battery Monitor Started')                  #print info message

    def publish_battery(self):
        battery = psutil.sensors_battery()

        if battery is None:
            self.get_logger().warn("Battery information not available")
            return

        msg = Int32()
        msg.data = int(battery.percent)

        self.publisher_.publish(msg)

        charging_status = "Charging" if battery.power_plugged else "Discharging"

        self.get_logger().info(
            f'Battery Level: {msg.data}% | Status: {charging_status}'
    )


def main():                                                                #entry function
    rclpy.init()                                                           #start ros communication
    Node = BatteryMonitor()                                                #create object of BatteryMonitor
    rclpy.spin(Node)                                                       #keep node running
    Node.destroy_node()                                                    #clean shutdown of node
    rclpy.shutdown()                                                       #Shutdown ROS system

if __name__ == '__main__':
    main()

