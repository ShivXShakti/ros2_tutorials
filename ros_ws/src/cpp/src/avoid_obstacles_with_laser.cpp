#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

class ObstacleAvoider : public rclcpp::Node
{
public:
    ObstacleAvoider() : Node("obstacle_avoider")
    {
        cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
        laser_sub_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&ObstacleAvoider::laser_callback, this, std::placeholders::_1)
        );
        // Initialize timer
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&ObstacleAvoider::timer_callback, this)
        );
    }

private:
    void laser_callback(const sensor_msgs::msg::LaserScan::SharedPtr msg)
    {
        laser_data_ = msg;
        float num_readings = laser_data_->ranges[0];
        RCLCPP_INFO(this->get_logger(), "Range: %f", num_readings);
    }

    void timer_callback()
    {
        if (laser_data_ == nullptr)
            return;

        // Create a Twist message to control robot
        auto cmd_msg = geometry_msgs::msg::Twist();

        // Simple obstacle avoidance logic
        bool obstacle_detected = false;
        float min_distance = 1.0;
        size_t min_index = 0;
        

        for (size_t i = 0; i < laser_data_->ranges.size(); ++i) {
            if (laser_data_->ranges[i] < min_distance) {
                min_distance = laser_data_->ranges[i];
                //RCLCPP_INFO(this->get_logger(), "Range: %f", laser_data_->ranges[0]);
                //RCLCPP_INFO(this->get_logger(), "Angle min: %f,  Angle max: %f,  Angle increment: %f", laser_data_->range_min, laser_data_->range_max, laser_data_->time_increment);
                min_index = i;
            }
        }

        if (min_distance < 1.0) {
            // Obstacle detected, stop and turn
            cmd_msg.linear.x = 0.1;
            cmd_msg.angular.z = 0.3;
        } else {
            // Move forward
            cmd_msg.linear.x = 0.5;
            cmd_msg.angular.z = 0.0;
        }

        cmd_vel_pub_->publish(cmd_msg);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_sub_;
    rclcpp::TimerBase::SharedPtr timer_;
    sensor_msgs::msg::LaserScan::SharedPtr laser_data_ = nullptr;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ObstacleAvoider>());
    rclcpp::shutdown();
    return 0;
}
