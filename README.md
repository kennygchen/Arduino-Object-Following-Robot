# Arduino Object Following Robot
<div align="center">
    <img src="https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/robot_1.jpg" width=50% height=50%>
</div>

Object Following Robot is a robot that uses a combination of Ultrasonic and infrared sensors to track an object. When the robot is on, it will detect if there is an object in front of it. If there is no object in front of it, the robot will be in idle mode. If there is an object in front of it, the robot will follow that object.

## User Guide
When the robot is first powered on, it will be in PARK mode where the robot would not react to any object. The user can press the button on the back to engage in DRIVE mode. A LED light will turn on indicating the robot is in DRIVE mode. When the robot is in DRIVE mode, the robot will follow the object that is in front of it. Users can press the button to switch between the PARK and DRIVE modes.

## Hardware Components Used
- Elegoo UNO R3 Microcontroller
- TB6612 Motor Shield
- Ultrasonic sensor
- Infrared Obstacle Avoidance Sensor
- Wheel
- DC motor
- 9V Battery with Span-On Connector Clip
- Button
- LED
- Resistor
- Jumper Wire
- Dupont Wire

## Software Libraries Used
1. NewPing
    - It makes working with ultrasonic sensors easy by proving functions that can get the distance in cm.
2. Wire
   - This library allows you to communicate with I2C/TWI devices
3. Adafruit Motor Shield
    - It allows easier control of the DC motors with the motor shield.

## Wiring Diagram
![Wiring Diagram](https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/wiring%20diagram.png)

## Demo
<div align="center">
      <a href="https://www.youtube.com/watch?v=of4G5A_wSq4">
         <img src="https://i.imgur.com/saBPdOW.png" style="width:50%;">
      </a>
</div>

<div align="center">
    <img src="https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/robot_1.jpg" width=40% height=40%>
    <img src="https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/robot_4.jpg" width=40% height=40%>
</div>
<div align="center">
    <img src="https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/robot_2.jpg" width=40% height=40%>
    <img src="https://github.com/kennygchen/Arduino-Object-Following-Robot/blob/main/images/robot_3.jpg" width=40% height=40%>
</div>
