# Warehouse Automation with TurtleBot3 in ROS2

## Overview
This project integrates TurtleBot3 with the AWS RoboMaker Small Warehouse World in a ROS2 and Gazebo simulation environment.

Prerequisites
ROS2 (Humble)
Gazebo
TurtleBot3 Gazebo package

## Setup
1. Clone AWS RoboMaker Warehouse Repository
```
git clone https://github.com/aws-robotics/aws-robomaker-small-warehouse-world
```
2. Source ROS2 and Gazebo
```
source /opt/ros/humble/setup.bash
source /usr/share/gazebo/setup.sh
```

3. Install TurtleBot3
```
sudo apt-get install ros-humble-turtlebot3-gazebo
```
4. Set TurtleBot3 Model
```
export TURTLEBOT3_MODEL=waffle
```
5. Create ROS2 Package
```
ros2 pkg create warehouse_automation --build-type ament_cmake --dependencies rclcpp rclpy
```

## Launch the Simulation

```
ros2 launch warehouse_automation no_roof_small_warehouse.launch.py

```

## Running nodes

# Mover Node

To run the mover node defined in velocity_publisher.cpp
run the following 
```
ros2 run warehouse_automation mover

```

# Watcher Node

To run the watcher node defined in camera_node.cpp
run the following 
```
ros2 run warehouse_automation watcher

```


## Common Issues 
Error: Gzclient process crash with exit code -6.

Solution: Source the Gazebo setup file.

```
source /usr/share/gazebo/setup.sh

```

reference : https://answers.ros.org/question/358847/cannot-launch-gzclient-on-a-launch-file-results-in-shared_ptr-assertion-error/