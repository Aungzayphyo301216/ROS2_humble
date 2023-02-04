import os

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python import get_package_share_directory
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    demos_nodes=IncludeLaunchDescription(PythonLaunchDescriptionSource([os.path.join(get_package_share_directory
    ('test'),'launch'),'/turtle_tf2_demo.launch.py']),

    launch_arguments={'target_frame': 'carrot1'}.items(),
    )



    return LaunchDescription([

        demos_nodes,
        Node(
            package='test',
            name='dynamic_tf2_broadcaster',
            executable='dynamic_frame_tf2_broadcaster',

        )

    ])