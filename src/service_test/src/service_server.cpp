#include "rclcpp/rclcpp.hpp"
#include <memory>
#include "tutorial_interfaces/srv/add_three_int.hpp"
void add(const std::shared_ptr<tutorial_interfaces::srv::AddThreeInt::Request> request,
    std::shared_ptr<tutorial_interfaces::srv::AddThreeInt::Response> response) ;


int main( int argc, char **argv)

{
    rclcpp::init(argc,argv);
    std::shared_ptr<rclcpp::Node> node= rclcpp::Node::make_shared ("addthreeints_server");
    std::shared_ptr<rclcpp::Service<tutorial_interfaces::srv::AddThreeInt>> service=
    node->create_service<tutorial_interfaces::srv::AddThreeInt> ("addthreeint", &add);

    RCLCPP_INFO(rclcpp::get_logger("rclcll")," Ready to add three Ints....");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}

void add(const std::shared_ptr<tutorial_interfaces::srv::AddThreeInt::Request> request,
    std::shared_ptr<tutorial_interfaces::srv::AddThreeInt::Response> response) 
    {
        response-> sum=request ->a+ request->b+ request->c;
        RCLCPP_INFO(rclcpp::get_logger("rclcpp")," Incomming request \n a: %ld , b: %ld, c: %ld",request->a,request->b,request->c);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Sending back response : %ld", (long int)response->sum);

    }

