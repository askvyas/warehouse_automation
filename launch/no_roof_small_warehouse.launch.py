# Copyright (c) 2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Launch file from AWS warehouse gazebo environment 

# Updated to launch turtle bot3


import os

from ament_index_python.packages import get_package_share_directory

import launch
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    aws_robomaker_small_warehouse_world_dir = get_package_share_directory('aws_robomaker_small_warehouse_world')
    # modified AWS launch file to spawn turtle bot from the same launch file 

    turtlebot3_gazebo_dir = get_package_share_directory('turtlebot3_gazebo')
    turtlebot3_launch_file_path='/opt/ros/humble/share/turtlebot3_gazebo/launch/spawn_turtlebot3.launch.py'
    warehouse_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([aws_robomaker_small_warehouse_world_dir, '/launch/small_warehouse.launch.py']),
        launch_arguments={
            'world': os.path.join(aws_robomaker_small_warehouse_world_dir, 'worlds', 'no_roof_small_warehouse', 'no_roof_small_warehouse.world')
        }.items()
    )

    turtlebot_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(turtlebot3_launch_file_path)
    )



    ld = launch.LaunchDescription([
        warehouse_launch,
        turtlebot_launch
    ])

    return ld
