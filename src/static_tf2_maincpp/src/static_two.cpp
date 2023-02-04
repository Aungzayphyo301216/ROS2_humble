#include "rclcpp/rclcpp.hpp"
#include <cstdio>
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include <chrono>

using namespace std::chrono_literals;

std::string static_turtle_name;


int main(int argc, char ** argv)
{

  // initialize ros2 and create a node
  rclcpp::init(argc, argv);
  
  std::shared_ptr<rclcpp::Node> node = std::make_shared<rclcpp::Node>("ros2_static_tf2_broadcaster");
  
  if(argc != 8)
  {
    RCLCPP_INFO(node->get_logger(), "Invalid number of parameters\nusage: tf2_broadcaster child_frame_name x y z roll pitch yaw");
    return -1;
  }
  if(strcmp(argv[1],"world")==0)
  {
    RCLCPP_INFO(node->get_logger(), "Your static turtle name cannot be 'world'");
    return -1;
  }

  static_turtle_name = argv[1];
   tf2_ros::TransformBroadcaster static_broadcaster(node);
  
   
  geometry_msgs::msg::TransformStamped tf;
  geometry_msgs::msg::TransformStamped tf_2;
 

  while (rclcpp::ok()) 
  {
    tf.header.stamp = rclcpp::Clock().now();
    tf.header.frame_id = "world";
    tf.child_frame_id = static_turtle_name;
    tf.transform.translation.x = atof(argv[2]);
    tf.transform.translation.y = atof(argv[3]);
    tf.transform.translation.z = atof(argv[4]);
    tf2::Quaternion q;
    q.setRPY(atof(argv[5]), atof(argv[6]), atof(argv[7]));
    tf.transform.rotation.x = q.x();
    tf.transform.rotation.y = q.y();
    tf.transform.rotation.z = q.z();
    tf.transform.rotation.w = q.w();
    
  
     
    tf_2.header.stamp = rclcpp::Clock().now();
    tf_2.header.frame_id = static_turtle_name;
    tf_2.child_frame_id = "myturtle";
    tf_2.transform.translation.x = 1;
    tf_2.transform.translation.y = 0;
    tf_2.transform.translation.z = 0;
    tf2::Quaternion q_1;
    q_1.setRPY(atof(argv[5]), atof(argv[6]), atof(argv[7]));
    tf_2.transform.rotation.x = q_1.x();
    tf_2.transform.rotation.y = q_1.y();
    tf_2.transform.rotation.z = q_1.z();
    tf_2.transform.rotation.w = q_1.w();
    static_broadcaster.sendTransform(tf);
    static_broadcaster.sendTransform(tf_2); 
     
    

    
    RCLCPP_INFO(node->get_logger(), "Publish %s to world", static_turtle_name.c_str());
    
    rclcpp::WallRate loop_rate(1s);
    loop_rate.sleep();
  }

  return 0;
}