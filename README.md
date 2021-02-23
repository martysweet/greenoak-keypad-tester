# greenoak-keypad-tester
Keypad Tester for Greenoak 9700, using an Ardiuno MEGA2560

- Use VSCode with the PlatformIO Extension
- Supports HIGH/LOW modes, typically for stable operation you want to have the row inputs pulled high, with the columns high, then for each scan, put a column low and evaluate the rows for a LOW signal.

![Matrix Wiring](https://user-images.githubusercontent.com/20517404/108894459-35d78780-760a-11eb-9be8-b51454a9ef18.png)

![Connection To Ardiuno](https://user-images.githubusercontent.com/20517404/108894716-88b13f00-760a-11eb-9b55-ef27a7b83369.png)

With the ribbon connector down so CRIMPFLEX is visible:

Yellow (Leftmost) = A5
White = A0

Black = 2
Red (Rightmost) = 5

