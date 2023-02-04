#include <rclcpp/rclcpp.hpp>
#include <tutorial_interfaces/srv/add_three_int.hpp>

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main ( int argc, char **argv)
{
    rclcpp::init(argc,argv);
    if ( argc!=4)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"usage: add_three_int x y z");
    }
    std::shared_ptr<rclcpp::Node> node= rclcpp::Node::make_shared("add_three_ints_clients");
    std::shared_ptr<rclcpp::Client<tutorial_interfaces::srv::AddThreeInt>> clients=
    node->create_client<tutorial_interfaces::srv::AddThreeInt>("addthreeint");

    auto request= std::make_shared<tutorial_interfaces::srv::AddThreeInt::Request>();
    request->a=atoll(argv[1]);
    request->b=atoll(argv[2]);
    request->c=atoll(argv[3]);

    while( !clients->wait_for_service(1s))
    {
        if(!rclcpp::ok()){
            RCLCPP_ERROR(rclcpp::get_logger("rclpp"),"Interrupted while waiting the service.Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"service not available.Waiting again...");
    }

    auto result=clients->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node,result)==rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"sum %ld",result.get()->sum);
    }
    else 
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Failed to called addthreeint");
    }

    rclcpp::shutdown();
    return 0;

}
