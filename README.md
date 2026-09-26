- [cn](#操作指南)
- [en](#Instructions)
# 操作指南

>此SDK仅适用于深圳乐动机器人有限公司销售的激光雷达产品，产品型号为:
> - LDROBOT LiDAR LD06
> - LDROBOT LiDAR LD19
> - LDROBOT LiDAR STL-27L

## 0. 获取雷达的ROS2功能包
```bash
cd ~

mkdir -p ldlidar_ros2_ws/src

cd ldlidar_ros2_ws/src

git clone  https://github.com/ldrobotSensorTeam/ldlidar_stl_ros2.git
```
## 1. 系统设置
- 第一步，通过板载串口或者USB转串口模块(例如,cp2102模块)的方式使雷达连接到你的系统主板.
- 第二步，设置雷达在系统中挂载的串口设备-x权限(以/dev/ttyUSB0为例)
	- 实际使用时，根据雷达在你的系统中的实际挂载情况来设置，可以使用`ls -l /dev`命令查看.

``` bash
cd ~/ldlidar_ros2_ws

sudo chmod 777 /dev/ttyUSB0
```
- 第三步，修改`launch/`目录下雷达产品型号对应的lanuch文件中的`port_name`值，以`ld06.launch.py` 和 `/dev/ttyUSB0`为例，如下所示.

```py
#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

'''
Parameter Description:
---
- Set laser scan directon: 
  1. Set counterclockwise, example: {'laser_scan_dir': True}
  2. Set clockwise,        example: {'laser_scan_dir': False}
- Angle crop setting, Mask data within the set angle range:
  1. Enable angle crop fuction:
    1.1. enable angle crop,  example: {'enable_angle_crop_func': True}
    1.2. disable angle crop, example: {'enable_angle_crop_func': False}
  2. Angle cropping interval setting:
  - The distance and intensity data within the set angle range will be set to 0.
  - angle >= 'angle_crop_min' and angle <= 'angle_crop_max' which is [angle_crop_min, angle_crop_max], unit is degress.
    example:
      {'angle_crop_min': 135.0}
      {'angle_crop_max': 225.0}
      which is [135.0, 225.0], angle unit is degress.
'''

def generate_launch_description():
  # LDROBOT LiDAR publisher node
  ldlidar_node = Node(
      package='ldlidar_stl_ros2',
      executable='ldlidar_stl_ros2_node',
      name='LD06',
      output='screen',
      parameters=[
        {'product_name': 'LDLiDAR_LD06'},
        {'topic_name': 'scan'},
        {'frame_id': 'base_laser'},
        {'port_name': '/dev/ttyUSB0'},
        {'port_baudrate': 230400},
        {'laser_scan_dir': True},
        {'enable_angle_crop_func': False},
        {'angle_crop_min': 135.0},
        {'angle_crop_max': 225.0}
      ]
  )

  # base_link to base_laser tf node
  base_link_to_laser_tf_node = Node(
    package='tf2_ros',
    executable='static_transform_publisher',
    name='base_link_to_base_laser_ld06',
    arguments=['0','0','0.18','0','0','0','base_link','base_laser']
  )


  # Define LaunchDescription variable
  ld = LaunchDescription()

  ld.add_action(ldlidar_node)
  ld.add_action(base_link_to_laser_tf_node)

  return ld
```
## 2. 编译方法

使用colcon编译.

```bash
cd ~/ldlidar_ros2_ws

colcon build
```
## 3. 运行方法
### 3.1. 设置功能包环境变量

- 编译完成后需要将编译生成的相关文件加入环境变量，便于 ROS 环境可以识别， 执行命令如下所示， 该命令是临时给终端加入环境变量，意味着您如果重新打开新的终端，也需要重新执行如下命令.

  ```bash
  cd ~/ldlidar_ros2_ws

  source install/setup.bash
  ```
- 为了重新打开终端后，永久不用执行上述添加环境变量的命令，可以进行如下操作.

  ```bash
  echo source ~/ldlidar_ros2_ws/install/setup.bash >> ~/.bashrc

  source ~/.bashrc
  ```
### 3.2. 启动激光雷达节点

- 产品型号为 LDROBOT LiDAR LD06
  - 启动ld06 lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 ld06.launch.py
  ```
  - 启动ld06 lidar node并显示激光数据在Rviz2上:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_ld06.launch.py
  ```

- 产品型号为 LDROBOT LiDAR LD19
  - 启动ld19 lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 ld19.launch.py
  ```
  - 启动ld19 lidar node并显示激光数据在Rviz2上:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_ld19.launch.py
  ```
  
- 产品型号为 LDROBOT LiDAR STL-27L
  - 启动stl27l lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 stl27l.launch.py
  ```
  - 启动stl27l lidar node并显示激光数据在Rviz2上:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_stl27l.launch.py
  ```

##   4. 测试

> 代码支持ubuntu20.04 ROS2 foxy版本及以上测试，使用rviz2可视化。
- 新打开一个终端 (Ctrl + Alt + T),运行命令:`rviz2`,并通过Rviz2工具打开readme文件所在目录的rviz2文件夹下面的ldlidar.rviz文件
```bash
rviz2
```

# Instructions

> This SDK is only applicable to the LiDAR products sold by Shenzhen LDROBOT Co., LTD. The product models are :
> - LDROBOT LiDAR LD06
> - LDROBOT LiDAR LD19
> - LDROBOT LiDAR STL-27L

## step 0: get LiDAR ROS2 Package
```bash
cd ~

mkdir -p ldlidar_ros2_ws/src

cd ldlidar_ros2_ws/src

git clone  https://github.com/ldrobotSensorTeam/ldlidar_stl_ros2.git
```
## step 1: system setup
- Connect the LiDAR to your system motherboard via an onboard serial port or usB-to-serial module (for example, CP2102 module).

- Set the -x permission for the serial port device mounted by the radar in the system (for example, /dev/ttyUSB0)

  - In actual use, the LiDAR can be set according to the actual mounted status of your system, you can use 'ls -l /dev' command to view.

``` bash
cd ~/ldlidar_ros2_ws

sudo chmod 777 /dev/ttyUSB0
```
- Modify the `port_name` value in the Lanuch file corresponding to the radar product model under `launch/`, using `ld06.launch.py` and `/dev/ttyUSB0` as an example, as shown below.

```py
#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

'''
Parameter Description:
---
- Set laser scan directon: 
  1. Set counterclockwise, example: {'laser_scan_dir': True}
  2. Set clockwise,        example: {'laser_scan_dir': False}
- Angle crop setting, Mask data within the set angle range:
  1. Enable angle crop fuction:
    1.1. enable angle crop,  example: {'enable_angle_crop_func': True}
    1.2. disable angle crop, example: {'enable_angle_crop_func': False}
  2. Angle cropping interval setting:
  - The distance and intensity data within the set angle range will be set to 0.
  - angle >= 'angle_crop_min' and angle <= 'angle_crop_max' which is [angle_crop_min, angle_crop_max], unit is degress.
    example:
      {'angle_crop_min': 135.0}
      {'angle_crop_max': 225.0}
      which is [135.0, 225.0], angle unit is degress.
'''

def generate_launch_description():
  # LDROBOT LiDAR publisher node
  ldlidar_node = Node(
      package='ldlidar_stl_ros2',
      executable='ldlidar_stl_ros2_node',
      name='LD06',
      output='screen',
      parameters=[
        {'product_name': 'LDLiDAR_LD06'},
        {'topic_name': 'scan'},
        {'frame_id': 'base_laser'},
        {'port_name': '/dev/ttyUSB0'},
        {'port_baudrate': 230400},
        {'laser_scan_dir': True},
        {'enable_angle_crop_func': False},
        {'angle_crop_min': 135.0},
        {'angle_crop_max': 225.0}
      ]
  )

  # base_link to base_laser tf node
  base_link_to_laser_tf_node = Node(
    package='tf2_ros',
    executable='static_transform_publisher',
    name='base_link_to_base_laser_ld06',
    arguments=['0','0','0.18','0','0','0','base_link','base_laser']
  )


  # Define LaunchDescription variable
  ld = LaunchDescription()

  ld.add_action(ldlidar_node)
  ld.add_action(base_link_to_laser_tf_node)

  return ld
```

## step 2: build

Run the following command.

```bash
cd ~/ldlidar_ros2_ws

colcon build
```
## step 3: run

### step3.1: package environment variable settings

- After the compilation is completed, you need to add the relevant files generated by the compilation to the environment variables, so that the ROS environment can recognize them. The execution command is as follows. This command is to temporarily add environment variables to the terminal, which means that if you reopen a new terminal, you also need to re-execute it. The following command.
  
  ```bash
  cd ~/ldlidar_ros2_ws
  
  source install/setup.bash
  ```
  
- In order to never need to execute the above command to add environment variables after reopening the terminal, you can do the following.

  ```bash
  echo source ~/ldlidar_ros2_ws/install/setup.bash >> ~/.bashrc
  
  source ~/.bashrc
  ```
### step3.2: start LiDAR node

- The product is LDROBOT LiDAR LD06
  - start ld06 lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 ld06.launch.py
  ```
  - start ld06 lidar node and show on the Rviz2:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_ld06.launch.py
  ```

- The product is LDROBOT LiDAR LD19
  - start ld19 lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 ld19.launch.py
  ```
  - start ld19 lidar node and show on the Rviz2:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_ld19.launch.py
  ```
  
- The product is LDROBOT LiDAR STL-27L
  - start stl27l lidar node:
  ``` bash
  ros2 launch ldlidar_stl_ros2 stl27l.launch.py
  ```
  - start stl27l lidar node and show on the Rviz2:
  ``` bash
  ros2 launch ldlidar_stl_ros2 viewer_stl27l.launch.py
  ```

## step 4: test

> The code supports ubuntu 20.04 ros2 foxy version and above, using rviz2 visualization.

- new a terminal (Ctrl + Alt + T) and use Rviz2 tool(run command: `rviz2`) ,open the `ldlidar.rviz` file below the rviz2 folder of the readme file directory
```bash
rviz2
```

## Startup configuration

Pass a ROS parameter YAML file to the driver; tuning does not require rebuilding:

```sh
ros2 run ldlidar_stl_ros2 ldlidar_stl_ros2_node --ros-args --params-file /path/to/d500.yaml -r __node:=d500_driver
ros2 param dump /d500_driver
```

Example for MEDRA AMR 2 (instance-specific mount, not a default for other robots):

```yaml
/**:
  ros__parameters:
    product_name: LDLiDAR_LD19
    port_name: /dev/d500
    port_baudrate: 230400
    topic_name: /d500/scan
    frame_id: d500_link
    laser_scan_dir: true
    noise_filter_enabled: true
    range_min: 0.32
    range_max: 0.60
    sector_mask_enabled: false
    sector_first_center_deg: 90.0
    sector_second_center_deg: 270.0
    sector_half_width_deg: 45.0
    self_mask_min_deg: 240.0
    self_mask_max_deg: 260.0
    self_mask_range_max: 0.38
    enable_angle_crop_func: false
    angle_crop_min: 0.0
    angle_crop_max: 0.0
```

`range_min`/`range_max` control both accepted returns and LaserScan metadata
(default 0.32–0.60 m). Require finite `0 <= min < max`.
`noise_filter_enabled` controls the vendor SDK filter (default true).

`sector_mask_enabled` defaults true for backward compatibility: keep returns inside
either cone centered at `sector_first_center_deg`/`sector_second_center_deg`
(default 90/270), with `sector_half_width_deg` (default 45). Centers must be in
0–360 degrees and half width in 0–180; cones wrap through zero.
Set enabled to false to restore left/right coverage.

The self mask removes only returns **strictly closer** than `self_mask_range_max`
metres inside its inclusive, ordered 0–360 degree bounds. Zero range disables it
(the default). The optional angle crop removes the entire distance range within
its inclusive, ordered bounds. All angles are sensor-native, **before** LaserScan
index reversal. Rejected returns are NaN. MEDRA AMR 2's self-mask example covers
approximately robot rear-left 150–170 degrees with its current mount.

Settings are validated before opening serial. Parameters are read-only at runtime:
edit the persistent YAML and restart the driver. `ros2 param get`, `dump`, and
`describe` are serviced while the driver runs; `set` rejects startup-only changes
instead of appearing to succeed without changing the scan.

Run the standalone regression check (also registered in CTest):

```sh
c++ -std=c++14 -Wall -Wextra -Werror -Iinclude scripts/test_scan_mask.cpp -o /tmp/test_scan_mask
/tmp/test_scan_mask
```
