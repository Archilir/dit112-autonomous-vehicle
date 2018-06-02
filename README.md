Autonomous Car System
========
The Autonomous Car System is a software package for a remote controlled, self-parking car. It uses ultrasonic and infrared sensors along with a gyroscope to autonomously park in various scenarios. It can be controlled with a mobile device or a DualShock controller, and it can detect road signs through the use of Python and OpenCV.

Features
--------
-Modular system architecture through C++ written in PlatformIO  
-Joystick and Image Recognition accomplished through Python  
-Bash script to run the above in parallel

Installation
------------
The Arduino software can be uploaded directly from a local copy of the repo onto an Arduino Mega board using Atom with the PlatformIO package. 
For the Image Recognition and Joystick functionalities, the files found in piProcessing should be copied onto a Raspberry Pi. The Pi should then be connected to the Arduino via USB. Finally, running the Bash script enables the functions.

Contribute
----------
Link to Repository:
https://github.com/ArchiCo/dit112-autonomous-vehicle

Support
-------
If you are having issues, please contact any of the team members:
[ Ahmad Alahmad        gusalahmah@student.gu.se ]
[ Filip Fatic          gusfatfi@student.gu.se   ]
[ Ilja Pavlov          guspavloil@student.gu.se ]
[ Sami Bolouri         gusbolosa@student.gu.se  ]
[ Tarik Durakovic      gusdurta@student.gu.se   ]
[ Victor Daniel Roman  gusromavi@student.gu.se  ]

Licence
-------
MIT Licence (c) Ilja Pavlov 2018
