#include <rclcpp/rclcpp.hpp>
#include "ros2_medkit_fault_reporter/fault_reporter.hpp"


int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rclcpp::Node>("medkit_correlation_example");
  auto fault_reporter_ = std::make_shared<ros2_medkit_fault_reporter::FaultReporter>(node, node->get_fully_qualified_name());

  // Simulate some health reports
  rclcpp::TimerBase::SharedPtr timer = node->create_wall_timer(
    std::chrono::seconds(2),
    [fault_reporter_]() {
      fault_reporter_->report("MAIN_FAULT", 2, "Fault that causes other faults.");
      fault_reporter_->report("CASCADED_FAULT", 2, "Fault that is caused by MAIN_FAULT.");
    });

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}