# Notes

1. Real world physics (Using 50kg robot with 2 falcon 500's)
- free speed of a falcon 500 is around 6800rpm. At it's most efficient under load, it runs at around 3000rpm. Using a general gearbox (toughbox mini with an 8.45:1 ratio) we can assume the output wheel to move at a max speed of 355.03rpm. And with the 6 inch wheels, this is an equivilent to 6692.3155 cm per minute or 1.115 meters per second

2. Speed equivilent.

- The field is 8 by 16 meters. In CV it is 800 by 1600 pixels. 100x conversion.
- Speed of robot is defined in config.h, in meters per second (100x = pixels per second)
- Actual speed of the robot (e.g 100% = 1) only moves pixel every cycle. CPS or cycles per second.
- Speed conversion is from cycles per second to pixels per second. Then adjust to fit 100 pixels per second, to meters per second/ visa versa.

