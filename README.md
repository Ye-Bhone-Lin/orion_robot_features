# Orion Robot Features

This repository contains various modules and features for the Orion Robot, a versatile platform designed for object detection, line detection, navigation, and other robotic tasks. Each module within this repository enhances the robot's capabilities through advanced algorithms, machine learning models, and hardware integration.

# Repository Structure
•  src/: Contains the source code for various features of the Orion Robot.

•  object_detection/: Code for real-time object detection using the YOLOv8 model.

•  line_detection/: Arduino-based line detection code for robot navigation.

# Features
### Object Detection
Located in src/object_detection/, this module leverages the YOLOv8 model for real-time detection of various objects via a webcam. The detected objects are highlighted with bounding boxes and labels, providing essential feedback for robotic tasks that require visual recognition.

#### Key Features:

•  Detects a wide range of objects including people, vehicles, and everyday items.

•  Real-time performance with live video feeds.

•  Easy-to-use interface for integration with other robotic systems.

# Line Detection using Arduino
Located in src/line_detection/, this module is responsible for detecting lines on the ground using an Arduino-based system. This feature is crucial for applications where the robot needs to follow a path or stay within certain boundaries.

### Key Features:

•  Real-time line detection using IR sensors connected to an Arduino.

•  Simple and effective for line-following robots.

•  Can be integrated with other navigation systems for complex tasks.
