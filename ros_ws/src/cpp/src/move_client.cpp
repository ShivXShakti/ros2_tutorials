#include "rclcpp/rclcpp.hpp"
#include "custom_interface/srv/move_message.hpp"
#include <chrono>
#include <memory>
#include <iostream>
using namespace std::chrono_literals;

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("move_client");
    rclcpp::Client<custom_interface::srv::MoveMessage>::SharedPtr client = node->create_client<custom_interface::srv::MoveMessage>("move");
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }   
    auto request = std::make_shared<custom_interface::srv::MoveMessage::Request>();
    request->move = "left";
    auto result_future = client->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result_future) == rclcpp::FutureReturnCode::SUCCESS){
        auto result = result_future.get();
        if (result->success == true){
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service returned true");
        }
        else if (result->success == false){
            RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Service returned false");
        }
        } else {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service /moving");
        }
    rclcpp::shutdown();
    return 0;
}