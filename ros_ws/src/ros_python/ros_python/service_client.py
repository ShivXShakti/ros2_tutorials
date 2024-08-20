from geometry_msgs.msg import Twist
from custom_interface.srv import MoveMessage
import rclpy
from rclpy.node import Node
import sys

class ServiceClient(Node):
    def __init__(self):
        super().__init__("service_client")
        self.client = self.create_client(MoveMessage, 'move')
        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting...')
        self.req = MoveMessage.Request()
    def send_request(self):
        self.req.move = "right" #sys.argv[1]
        self.future = self.client.call_async(self.req)

def main(args=None):
    rclpy.init(args=args)
    client = ServiceClient()
    client.send_request()
    while rclpy.ok():
        rclpy.spin_once(client)
        if client.future.done():
            try:
                response = client.future.result()
            except Exception as e:
                client.get_logger().info('service call failed %r'%(e,))
            else:
                client.get_logger().info('Response state: %r'%(response.success,))
            break
    client.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()
