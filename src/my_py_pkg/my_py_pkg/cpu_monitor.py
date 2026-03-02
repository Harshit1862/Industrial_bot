import rclpy
from rclpy.node import Node
from std_msgs.msg import Int32
import random
import psutil


class CpuMonitor(Node):
    def __init__(self):
        super().__init__('cpu_monitor')
        self.publisher_ = self.create_publisher(Int32, 'cpu_usage', 10)
        self.timer = self.create_timer(1.0, self.publish_cpu)

        self.get_logger().info('CPU Monitor Started')

    def publish_cpu(self):
        msg = Int32()
        # Read real CPU usage from system
        cpu_usage = int(psutil.cpu_percent(interval=None))
        msg.data = cpu_usage
        self.publisher_.publish(msg)
        self.get_logger().info(f'CPU Usage: {msg.data}%')


def main():
    rclpy.init()
    node = CpuMonitor()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
