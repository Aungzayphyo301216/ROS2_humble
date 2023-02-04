#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration

rom_robot = ['rom2109_tall.urdf', 'rom2109_short.urdf', 'rom2109_bot.urdf']
def generate_launch_description():
    urdf_pkg = get_package_share_directory('rom2109_description')
    urdf_path= os.path.join(urdf_pkg, 'urdf', rom_robot[2])
    urdf = open(urdf_path).read()

    robot_state_publisher_node = Node(
        name="robot_state_publisher",
        package="robot_state_publisher",
        executable="robot_state_publisher",
        parameters=[{"robot_description": urdf}],
    )

    joint_state_node = Node(
        name="joint_state_publisher",
        package="joint_state_publisher",
        executable="joint_state_publisher",
    )

    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', os.path.join(urdf_pkg, 'rviz2', 'display.rviz')],
        condition=IfCondition(LaunchConfiguration('open_rviz'))
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument('open_rviz', default_value='true', description='Open RViz.'),
            robot_state_publisher_node,
            joint_state_node,
            rviz_node
        ]
    )
