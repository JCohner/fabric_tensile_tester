# Fabric Tensile Tester

My friend gave me a very cool problem prompt:
| How can we procedurally find the Young's Modulus of different fabric weaves

I determined that 3D printed components would have sufficient rigidity and designed the mechanism [here](https://cad.onshape.com/documents/414844e767a5c5dcc10ecd8a/w/11a8d7078b3e5012b6154466/e/b864a8eacea5f8d32ab57ced?renderMode=0&uiState=6770eccbf48e4208ced637a1) 

![image](https://github.com/user-attachments/assets/a0653b0c-001f-4680-a64c-0043c8f1b77b)


This is the codebase for procedurally measuring the force required to strain the fabric. 


## General Architecture
This is curretnly running on samd21 housed on a Arduino Nano 33 IoT board. 

I am using the arduino-cli / arduino eco-system to build an deploy; sorry for being lazy. Find utilization of those commands in the Makefile

* stretcher.ino 
  * arduino entry point and program main.
  * holds Robot object
  * holds definition of timer interrupts used to handle
    * rail position handling - TC3
    * load cell reading - TC4
  * performs serial reads to enqueue commands to Robot object

* robot.*
  * High level abstraction for whole machine
  * holds state variables for contraption as a whole and mechanism to enqueue commands which can permutate those state variables. it gets "ticked" within the main arduino loop
  * see robot_enums.h for state enumerations
  * see robot_commands.h for command enumerations (and serialization of command names)
  * owns Rail object which moves things on the rail
* rail.*
  * own stepper driver: SparkFun_ProDriver_TC78H670FTG
  * built in a non blocking way such that jobs are enqueued to the rail object and it is ticked by timer interrupt 3 at fixed frequency to interact with the stepper driver to get the stepper in the right place. 
  * jobs are stored as Goal objects... thats probably too in the weeds

* helper.*
  * just a couple odds and ends. the misnamed stateful_member template is something I use often
* status.h 
  * common way of reporting and actioning on status of jobs that I stole from Behavior Trees