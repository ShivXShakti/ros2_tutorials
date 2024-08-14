import rclpy
from rclpy.node import Node

class SimpleNode(Node):
    def __init__(self):
        super().__init__("simple_node")
        self.create_timer(0.2, self.timer_callback)
    def timer_callback(self):
        self.get_logger().info("simple node, running...")
def main(args=None):
    rclpy.init(args=args)
    node = SimpleNode()
    rclpy.spin(node)
    rclpy.shutdown()
if __name__ == "__main__": 
    main() 