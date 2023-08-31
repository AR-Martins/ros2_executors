#include <rclcpp/rclcpp.hpp>
#include <unistd.h>
#include <cstdio>
#include <memory>
#include <string>
#include <chrono>
#include <functional>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;

class LowTimer : public rclcpp::Node {
    public:
        LowTimer(float low_timer) : Node("low_subscriber"){
            this->low_wait = low_timer;
            lowtimer_ = this->create_wall_timer(
                1000ms, std::bind(&LowTimer::lowtimer_callback, this));
        }
    private:
        void lowtimer_callback()
        {
            sleep(this->low_wait);
            RCLCPP_INFO(this->get_logger(), "Low Counting");
        }
        rclcpp::TimerBase::SharedPtr lowtimer_;
        float low_wait;

};

class MediumTimer : public rclcpp::Node {
    public:
        MediumTimer(float medium_timer) : Node("meduim_subscriber"){
            this->medium_wait = medium_timer;
            mediumtimer_ = this->create_wall_timer(
                500ms, std::bind(&MediumTimer::mediumtimer_callback, this));
        }
    private:
        void mediumtimer_callback()
        {
            sleep(this->medium_wait);
            RCLCPP_INFO(this->get_logger(), "Medium Counting");
        }
        rclcpp::TimerBase::SharedPtr mediumtimer_;
        float medium_wait;

};

class HighTimer : public rclcpp::Node {
    public:
        HighTimer(float high_timer) : Node("high_subscriber"){
            this->high_wait = high_timer;
            hightimer_ = this->create_wall_timer(
                100ms, std::bind(&HighTimer::hightimer_callback, this));
        }
    private:
        void hightimer_callback()
        {
            sleep(this->high_wait);
            RCLCPP_INFO(this->get_logger(), "High Counting");
        }
        rclcpp::TimerBase::SharedPtr hightimer_;
        float high_wait;

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    float low_timer = 5.0;
    std::shared_ptr<LowTimer> low_node =
        std::make_shared<LowTimer>(low_timer);
    float medium_timer = 3.0;
    std::shared_ptr<MediumTimer> medium_node =
        std::make_shared<MediumTimer>(medium_timer);
    float high_timer = 1.0;
    std::shared_ptr<HighTimer> high_node =
        std::make_shared<HighTimer>(high_timer);

    RCLCPP_INFO(low_node->get_logger(), "medium_time_node INFO: ");
    RCLCPP_INFO(low_node->get_logger(), "low_time_node INFO: ");
    RCLCPP_INFO(low_node->get_logger(), "high_time_node INFO: ");

    rclcpp::executors::MultiThreadedExecutor executor;

    executor.add_node(low_node);
    executor.add_node(medium_node);
    executor.add_node(high_node);
    executor.spin();

    rclcpp::shutdown();
    return 0;    
}