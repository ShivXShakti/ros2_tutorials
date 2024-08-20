from geometry_msgs.msg import Twist
from custom_interface.srv import MoveMessage
import rclpy
from rclpy.node import Node

class ServiceServer(Node):
    def __init__(self):
        super().__init__("service_server")
        self.srv = self.create_service(MoveMessage, 'move', self.server_callback)
        self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
    def server_callback(self, request, response):
        msg = Twist()
        if request.move == "right":
            msg.linear.x = 0.2
            msg.angular.z = -0.2
            self.publisher_.publish(msg)
            self.get_logger().info('turning right...')
            response.success = True
        elif request.move == "left":
            msg.linear.x = 0.2
            msg.angular.z = 0.2
            self.publisher_.publish(msg)
            self.get_logger().info('turning left...')
            response.success = True
        elif request.move == "stop":
            msg.linear.x = 0.0
            msg.angular.z = 0.0
            self.publisher_.publish(msg)
            self.get_logger().info('stopping...')
            response.success = True
        else:
            response.success = False
        return response

def main(args = None):
    rclpy.init(args=args)
    service_server = ServiceServer()
    rclpy.spin(service_server)
    rclpy.shutdown()
if __name__ == "__main__":
    main()