#include <rclcpp/rclcpp.hpp>
#include <unistd.h>

using namespace std::chrono_literals;

class TwoTimer: public rclcpp::Node{
    public:
        TwoTimer(float sleep_timer1, float sleep_timer2):Node("group_callback"){
            this->wait_time1 = sleep_timer1;
            this->wait_time2 = sleep_timer2;

            timer1_ = this->create_wall_timer(500ms, std::bind(&TwoTimer::timer1_callback, this));
            timer2_ = this->create_wall_timer(500ms, std::bind(&TwoTimer::timer2_callback, this));
        }
    private:
    void timer1_callback(){
        sleep(this->wait_time1);
        RCLCPP_INFO(this->get_logger(), "timer1 callback");
    }
    void timer2_callback(){
        sleep(this->wait_time2);
        RCLCPP_INFO(this->get_logger(), "timer2 callback");
    }
    rclcpp::TimerBase::SharedPtr timer1_;
    rclcpp::TimerBase::SharedPtr timer2_;
    float wait_time1;
    float wait_time2;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    float sleep_time1 = 1.0;
    float sleep_time2 = 3.0;

    std::shared_ptr<TwoTimer> callback_group_2timer_node = 
       std::make_shared<TwoTimer>(sleep_time1, sleep_time2);
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(callback_group_2timer_node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}