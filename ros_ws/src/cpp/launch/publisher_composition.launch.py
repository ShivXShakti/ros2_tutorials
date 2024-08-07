from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp',
            executable='publisher_composition_node',
            output='screen'),
    ])
