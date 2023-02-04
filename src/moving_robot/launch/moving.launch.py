import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package="turtlesim",
            executable="turtlesim_node",
        ),
        Node (
            package="moving_robot",
            executable="moving_robot",
            remappings=[
                ('/moving_robot/cmd_vel','/turtle1/cmd_vel')
            ]
        )

    ])
    