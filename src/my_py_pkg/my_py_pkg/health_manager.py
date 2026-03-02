import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32, String

class HealthManager(Node):
    def __init__(self):
        super().__init__('health_manager')

        self.battery = 100
        self.cpu = 0

        self.create_subscription(Int32, 'battery_level', self.battery_cb, 10)
        self.create_subscription(Int32, 'cpu_usage', self.cpu_cb, 10)

        self.publisher_ = self.create_publisher(String, 'system_health', 10)
        self.timer = self.create_timer(1.0, self.evaluate_health)

        self.get_logger().info('Health Manager Started')

    def battery_cb(self, msg):
        self.battery = msg.data

    def cpu_cb(self, msg):
        self.cpu = msg.data

    def evaluate_health(self):
        status = "OK"

        if self.battery < 20:
            status = "LOW BATTERY"
        elif self.cpu > 80:
            status = "HIGH CPU USAGE"

        msg = String()
        msg.data = f"Health: {status} | Battery: {self.battery}% | CPU: {self.cpu}%"
        self.publisher_.publish(msg)

        self.get_logger().info(msg.data)

def main():
    rclpy.init()
    node = HealthManager()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
#data distri. service DDS ROS2 