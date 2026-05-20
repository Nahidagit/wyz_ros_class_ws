好的，这是可以直接复制粘贴的完整 README.md 文件内容：

```markdown
# wyz_ros_class_ws

ROS机器人课程工作空间，包含里程计移动、传感器避障、动态参数调节、仿真建模、巡线、手势识别、视觉跟踪与抓取等实验代码。

## 环境要求

- Ubuntu 20.04
- ROS Noetic
- Upros机器人硬件及驱动包

## 下载与编译

```bash
cd ~/wyz_ros_class_ws
catkin_make
source devel/setup.bash
```

---

第一周：里程计移动

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行里程计移动节点

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
rosrun my_class_pkg odom_move
```

---

第二周：传感器避障

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行避障节点（三选一）

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash

# 碰撞传感器避障
rosrun my_class_pkg bumper_controller

# 超声波TOF避障
rosrun my_class_pkg tof_avoidance

# 原地自转180°
rosrun my_class_pkg rotate_180
```

---

第三周：动态参数调节

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行动态速度调节节点

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
rosrun my_class_pkg ros_dynamic_speed_node
```

终端3： 启动动态参数配置界面

```bash
rosrun rqt_reconfigure rqt_reconfigure
```

调节浮点型动态参数即可实时调整机器人速度。

---

第四周：仿真与建模

4.1 RViz模型显示

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
roslaunch my_class_pkg display.launch
```

在RViz中：

1. Fixed Frame 选择 base_link
2. 点击 Add 添加 RobotModel

4.2 Gazebo仿真

终端1： 启动Gazebo仿真

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
roslaunch my_class_pkg gazebo.launch
```

终端2： 键盘控制

```bash
rosrun upros_move_linear teleop_twist_keyboard.py
```

---

第五周：视觉与抓取

5.1 巡线实验

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行巡线程序

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
roscd my_class_pkg/scripts
chmod a+x follow_line.py
rosrun my_class_pkg follow_line.py
```

5.2 手势识别实验

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行手势识别

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
roscd my_class_pkg/scripts
chmod a+x gesture_movement.py
chmod a+x upros_gesture.py
rosrun my_class_pkg gesture_movement.py
```

5.3 视觉跟踪实验

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 运行视觉跟踪

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
roscd my_class_pkg/scripts
chmod a+x apriltag_follow.py
rosrun my_class_pkg apriltag_follow.py
```

5.4 视觉抓取实验

终端1： 启动机器人驱动

```bash
roslaunch upros_bringup bringup_w2a.launch
```

终端2： 启动视觉识别

```bash
roslaunch upros_arm recognize_apriltag.launch
```

终端3： 运行抓取节点

```bash
cd ~/wyz_ros_class_ws
source devel/setup.bash
rosrun my_class_pkg tag_grab_node
```

---

常见问题

编译报错找不到包

```bash
sudo apt update
sudo apt install ros-noetic-<缺失的包名>
```

运行节点报错找不到可执行文件

```bash
source ~/wyz_ros_class_ws/devel/setup.bash
```

机械臂抓取失败

确保服务端已就绪，必要时在代码中添加：

```cpp
arm_client.waitForExistence();
ros::Duration(0.5).sleep();
```

---

文件结构

```
wyz_ros_class_ws/
├── src/
│   └── my_class_pkg/
│       ├── CMakeLists.txt
│       ├── package.xml
│       ├── src/           # C++源文件
│       ├── scripts/       # Python脚本
│       ├── launch/        # 启动文件
│       ├── msg/           # 自定义消息
│       ├── srv/           # 自定义服务
│       ├── action/        # 自定义动作
│       └── cfg/           # 动态参数配置
├── build/                 # 编译中间文件（不提交）
├── devel/                 # 编译产物（不提交）
└── README.md
```

作者

bcsh

许可证

TODO

```

直接全选复制，保存为 `~/wyz_ros_class_ws/README.md` 即可。
