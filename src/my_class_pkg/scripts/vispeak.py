#!/usr/bin/env python3

import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError
from my_class_pkg.msg import WindowStatus
import apriltag

class AprilTagVoiceNode:
    
    def __init__(self):
        rospy.init_node('apriltag_voice_node', anonymous=True)
        
        # 初始化AprilTag检测器
        self.tag_detector = apriltag.Detector(apriltag.DetectorOptions(families='tag36h11'))
        self.target_tag_id = 1
        self.bridge = CvBridge()
        
        # 状态标志
        self.has_found = False          # 本次窗口期是否找到过目标
        self.window_active = False      # 窗口是否激活
        self.window_closing = False     # 窗口是否正在关闭（用于触发"未找到"播报）
        
        # 订阅图像话题
        self.image_sub = rospy.Subscriber('/camera/color/image_raw', Image, self.image_callback)
        
        # 订阅 window 话题
        self.window_sub = rospy.Subscriber('window', WindowStatus, self.window_callback)
        
        # 发布语音播报话题
        self.voice_pub = rospy.Publisher('/talk', String, queue_size=10)
        
        rospy.loginfo("AprilTag语音节点已启动，目标ID: %d", self.target_tag_id)
        rospy.loginfo("模式：仅在 window=1 时识别")
        
 #       rospy.sleep(5)
 #       self.speak("开始运行")
    
    def speak(self, text):
        """通过/talk话题发布语音播报"""
        msg = String()
        msg.data = text
        self.voice_pub.publish(msg)
        rospy.loginfo("语音播报: %s", text)
    
    def window_callback(self, msg):
        """接收 window 话题的状态"""
        if msg.status == 1:
            # 窗口激活
            if not self.window_active:
                rospy.loginfo("窗口激活，开始识别")
                self.window_active = True
                self.has_found = False      # 新窗口期，重置找到标志
                self.window_closing = False
        else:
            # 窗口关闭
            if self.window_active:
                # 窗口期结束，检查是否找到过目标
                if not self.has_found:
                    rospy.loginfo("窗口期未找到目标")
                    self.speak("未找到目标")
                self.window_active = False
                self.has_found = False
    
    def image_callback(self, msg):
        # 窗口未激活，不处理
        if not self.window_active:
            return
        
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            gray_frame = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
            tags = self.tag_detector.detect(gray_frame)
            
            for tag in tags:
                if tag.tag_id == self.target_tag_id:
                    if not self.has_found:
                        rospy.loginfo("✅ 找到目标 AprilTag，ID: %d", tag.tag_id)
                        self.speak("已找到目标")
                        self.has_found = True
                    return
                    
        except CvBridgeError as e:
            rospy.logerr(e)
            return

if __name__ == '__main__':
    try:
        node = AprilTagVoiceNode()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
    except KeyboardInterrupt:
        print("\n节点已关闭")
