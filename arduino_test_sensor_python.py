#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jan  2 22:44:12 2024

@author: elelt
"""

import serial
import pyautogui

# Change 'COM3' to your Arduino port
arduino_port = '/dev/cu.usbmodem101'

# Open serial connection
ser = serial.Serial(arduino_port, 9600, timeout=1)

mouse_enabled = True  # Flag to track whether mouse movement is enabled

try:
    while True:
        # Read data from Arduino
        data = ser.readline().decode('utf-8').strip()
        if data:
            # Split the data into separate values
            values = data.split()
            
            if values[0] == 'M':
                _, x, y, force, pot = map(int, values[1:])
                
                # Debug prints for joystick and potentiometer
                print(f"Joystick X: {x}, Joystick Y: {y}, Potentiometer: {pot}")

                # Process joystick data
                pyautogui.moveRel(x, y)

                # Process force sensor for left-click
                if force > 400:
                    pyautogui.click(button='left')

                # Process potentiometer for mouse enable/disable
                if pot <= 500:
                    mouse_enabled = False
                elif pot >= 500:
                    mouse_enabled = True

            elif values[0] == 'L':
                # Left-click indicator received
                pyautogui.click(button='left')

            elif values[0] == 'D':
                # Mouse disable indicator received
                mouse_enabled = False

            elif values[0] == 'E':
                # Mouse enable indicator received
                mouse_enabled = True

except KeyboardInterrupt:
    print("Serial connection closed.")
    ser.close()

# 