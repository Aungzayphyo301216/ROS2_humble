#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class Moving_robot : public rclcpp::Node
{
  public:
    Moving_robot()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/moving_robot/cmd_vel", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Moving_robot::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message =geometry_msgs::msg::Twist();
      message.linear.x=2;
      message.angular.z=2;
      RCLCPP_INFO(this->get_logger(), "Publishing: ");
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Moving_robot>());
  rclcpp::shutdown();
  return 0;
}