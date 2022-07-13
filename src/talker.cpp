#include <chrono>
#include <cstdio>
#include <memory>
#include <utility>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Talker : public rclcpp::Node {
public:
  explicit Talker() : Node("talker") {
    auto publish_message = [this]() -> void {
      msg_ = std::make_unique<std_msgs::msg::String>();
      msg_->data = "Hello World: " + std::to_string(count_++);
      RCLCPP_INFO(get_logger(), "Publishing: '%s'", msg_->data.c_str());
      pub_->publish(std::move(msg_));
    };
    pub_ = create_publisher<std_msgs::msg::String>("chatter", 1);

    timer_ = create_wall_timer(1s, publish_message);
  }

private:
  std::size_t count_ = 1;
  std::unique_ptr<std_msgs::msg::String> msg_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
