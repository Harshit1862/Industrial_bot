import rclpy
from rclpy.node import Node

class BatteryNode(Node):
    def __init__(self):
        super().__init__("battery")
        self.battery_state_ = "full"
        self.last_time_battery_state_changed_ = self.get_current
        self.battery_timer_ = self.create_timer(0.1, self.check_battery_state)
    def get_current_time_seconds(self):
        seconds, nanoseconds =  self.get_clock().now().seconds_nanoseconds()
        return seconds + nanoseconds / 1000000000.0
    def check_battery_state(self):
        time_now = self.get_current_time_seconds()
        if self.battery_state_ == "full":
            if time_now - self.last_time_battery_state_changed_ > 4.0:
                self.battery_state_ = "empty"
                self.get_logger().info("Battery is empty! Charging...")
                self.last_time_battery_state_changed_ = time_now

        elif self.battery_state_ == "empty":
            if time_now - self.last_time_battery_state_changed_ > 6.0:
                self.battery_state_ = "full"
                self.get_logger().info("Battery is now full.")
                self.last_time_battery_state_changed_ = time_now


def main(args=None):
    rclpy.init(args=args)
    node = BatteryNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
