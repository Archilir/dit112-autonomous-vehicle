# Joyous Joystick by Ahmad and Filip
## Axes
The joystick has a grand total of 12 axes, all of which go from -1 to 1 and are denoted(for now) by their position in the array. I'll note them here for future reference.

0. Left joystick - Horizontal axis
1. Left joystick - Vertical axis
2. Right joystick - Horizontal axis
3. L2 - For some reason the triggers have both a button value and an axis value. The axis value is -1 when the button is not pressed and goes all the way to 1 when pressed. This is used to denote the degree to which the button is pressed. Interestingly, both this and the next axis are set to 0 until the first time either button is pressed. From then they act as normal, keeping it at -1 when left alone.
4. R2 - Same as L2
5. Right joystick - Vertical axis
6. Motion control - Roll - goes only from -0.5 to 0.5, left to right.
7. Motion control - Pitch - -0.5 to 0.5
8. Motion control - Pitch - Also goes from -0.5 to 0.5, but it has a different value it's zeroed onto. Probably useless.
9. I have no idea what 9 to 11 do. They update constantly so it must be more motion control stuff.

## Buttons
Straightforward - 14 buttons, they have a value of 0 when depressed and 1 when pressed.

0. Square
1. X
2. Circle
3. Triangle
4. L1
5. R1
6. L2
7. R2
8. Share
9. Options
10. L3
11. R3
12. PS button
13. Touchpad pressed down

## Hats
The D-Pad buttons are refered to as hats in the code. They are buttons, but they work along an axis. Both axes have a value of 0 when depressed. Left and down give the axes a value of -1, while right and up give them a value of +1.
