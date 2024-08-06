// Import the rclcpp client library
#include "rclcpp/rclcpp.hpp"
int main(int argc, char * argv[])
{
// Initialize the ROS2 communication
rclcpp::init(argc, argv);
// Create a ROS2 node named ObiWan
auto node = rclcpp::Node::make_shared("ObiWan");
rclcpp::WallRate loop_rate(2);
while (rclcpp::ok()){
// Print a message to the terminal
RCLCPP_INFO(node->get_logger(), "Help me Obi-Wan Kenobi, you're my only hope");
rclcpp::spin_some(node);
loop_rate.sleep();}
// Shutdown the ROS2 communication
rclcpp::shutdown();
return 0;
}
