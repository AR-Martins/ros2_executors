#include <rclcpp/rclcpp.hpp>
#include <unistd.h>


class LowTimer : public::Node {
public:
    LowTimer(float low_timer) : Node("low_subscriber") {
        this->low_wait = low_timer;
        lowtimer_ = this->create_wall_timer(
            1000ms, std::bind(&Lowtimer::lowtimer_callback, this));
    }
}