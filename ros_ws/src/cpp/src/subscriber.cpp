#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
using std::placeholders::_1;
class Subscriber: public rclcpp::Node{
    public:
        Subscriber():Node("subscriber_node"){
            subscription_ = this->create_subscription<std_msgs::msg::Int32>("counter", 10, std::bind(&Subscriber::topic_callback, this, _1));
        }
    private:
        void topic_callback(const std_msgs::msg::Int32::SharedPtr msg){
            RCLCPP_INFO(this->get_logger(),"I heard: '%d'", msg->data);
        }
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Subscriber>());
    rclcpp::shutdown();
    return 0;
}