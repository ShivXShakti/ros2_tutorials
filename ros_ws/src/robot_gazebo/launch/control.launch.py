from launch_ros.actions import Node
from launch import LaunchDescription

def generate_launch_description():
    spawn_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster"],
        output="screen",
    )
    spawn_controller_traj = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_trajectory_controller"],
        output="screen",
    )
    return LaunchDescription([spawn_controller,
                              spawn_controller_traj])