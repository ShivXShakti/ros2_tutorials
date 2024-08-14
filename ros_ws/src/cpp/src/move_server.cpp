#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "custom_interface/srv/move_message.hpp"
#include <memory>
using std::placeholders::_1;
using std::placeholders::_2;

class ServerNode : public rclcpp::Node{
    public:
        ServerNode(): Node("movement_server"){
            srv_ = create_service<custom_interface::srv::MoveMessage>("movement", std::bind(&ServerNode::moving_callback, this, _1, _2));
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        }
    private:
        rclcpp::Service<custom_interface::srv::MoveMessage>::SharedPtr srv_;
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    
    void moving_callback(
        const std::shared_ptr<custom_interface::srv::MoveMessage::Request> request,
        const std::shared_ptr<custom_interface::srv::MoveMessage::Response> response){
        auto message = geometry_msgs::msg::Twist();
        if (request->move == "right"){
            message.linear.x = 0.2;
            message.angular.z = -0.2;
            publisher_->publish(message);
            response->success = true;
        }
        else if (request->move == "left"){
            message.linear.x = 0.2;
            message.angular.z = 0.2;
            publisher_->publish(message);
            response->success = true;
        }
        else if (request->move == "stop"){
            message.linear.x = 0.0;
            message.angular.z = 0.0;
            publisher_->publish(message);
            response->success = true;
        }else{
            response->success = false;
        }
    }
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServerNode>());
    rclcpp::shutdown();
    return 0;
}