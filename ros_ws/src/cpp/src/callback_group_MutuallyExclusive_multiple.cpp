#include <rclcpp/rclcpp.hpp>
#include <unistd.h>

using namespace std::chrono_literals;

class TwoTimer: public rclcpp::Node{
    public:
        TwoTimer(float sleep_timer1, float sleep_timer2):Node("callback_group_reentrant"){
            callback_group1_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
            callback_group2_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

            this->wait_time1 = sleep_timer1;
            this->wait_time2 = sleep_timer2;

            timer1_ = this->create_wall_timer(500ms, std::bind(&TwoTimer::timer1_callback, this), callback_group1_);
            timer2_ = this->create_wall_timer(500ms, std::bind(&TwoTimer::timer2_callback, this), callback_group2_);
        }
    private:
    void timer1_callback(){
        RCLCPP_INFO(this->get_logger(), "timer1 callback start");
        sleep(this->wait_time1);
        RCLCPP_INFO(this->get_logger(), "timer1 callback end");
    }
    void timer2_callback(){
        RCLCPP_INFO(this->get_logger(), "timer1 callback start");
        sleep(this->wait_time2);
        RCLCPP_INFO(this->get_logger(), "timer2 callback end");
    }
    rclcpp::CallbackGroup::SharedPtr callback_group1_;
    rclcpp::CallbackGroup::SharedPtr callback_group2_;
    rclcpp::TimerBase::SharedPtr timer1_;
    rclcpp::TimerBase::SharedPtr timer2_;
    float wait_time1;
    float wait_time2;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    float sleep_time1 = 1.0;
    float sleep_time2 = 3.0;

    std::shared_ptr<TwoTimer> callback_group_reentrant_node = 
       std::make_shared<TwoTimer>(sleep_time1, sleep_time2);
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(callback_group_reentrant_node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}