import serial
import numpy as np
import time
from collections import deque

# -- Replace 'COMx' with your Arduino's serial port
SERIAL_PORT = 'COM5'
BAUD_RATE = 9600

# Buffers to store the last 40 data points (approx. 2 seconds of motion)
history_x = deque(maxlen=40)
history_y = deque(maxlen=40)


def is_circular_motion(x_data, y_data):
    if len(x_data) < 10:
        return False

    # Convert to numpy arrays
    x = np.array(x_data)
    y = np.array(y_data)

    # -------------------------
    # Step 1: Find center (mean)
    # -------------------------
    cx = np.mean(x)
    cy = np.mean(y)

    # Center the data
    x_centered = x - cx
    y_centered = y - cy

    # -------------------------
    # Step 2: Check amplitude (movement strength)
    # -------------------------
    variance = np.var(x_centered) + np.var(y_centered)

    if variance < 50:  # <-- tune this threshold
        return False

    # -------------------------
    # Step 3: Check symmetry (circle vs line)
    # -------------------------
    std_x = np.std(x_centered)
    std_y = np.std(y_centered)

    if std_y == 0:
        return False

    ratio = std_x / std_y

    if ratio < 0.5 or ratio > 2.0:
        return False

    # -------------------------
    # Step 4: Check rotation direction (cross product)
    # -------------------------
    cross_products = []

    for i in range(len(x_centered) - 1):
        x1, y1 = x_centered[i], y_centered[i]
        x2, y2 = x_centered[i + 1], y_centered[i + 1]

        cross = x1 * y2 - y1 * x2
        cross_products.append(cross)

    # -------------------------
    # Step 5: Count direction consistency
    # -------------------------
    positive = sum(1 for c in cross_products if c > 0)
    negative = sum(1 for c in cross_products if c < 0)

    total = len(cross_products)

    if total == 0:
        return False

    # Check if mostly one direction (>70%)
    if positive / total > 0.7 or negative / total > 0.7:
        return True

    return False


def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Wait for Arduino to reset
    print("System ready. Move the MPU6050 in a circle to toggle the LED...")

    # Keep track of the LED state
    led_is_on = False

    try:
        while True:
            raw = ser.readline().decode(errors='ignore').strip()
            if raw:
                parts = raw.split(',')

                if len(parts) >= 3:
                    try:
                        ax = int(parts[0])
                        ay = int(parts[1])

                        # Add new data to our buffers
                        history_x.append(ax)
                        history_y.append(ay)

                        # Only analyze if our buffer is full (40 points)
                        if len(history_x) == 40:
                            if is_circular_motion(history_x, history_y):

                                # Toggle the state
                                led_is_on = not led_is_on

                                if led_is_on:
                                    print("Circle Detected! Toggling LED: ON")
                                    ser.write(b'O')
                                else:
                                    print("Circle Detected! Toggling LED: OFF")
                                    ser.write(b'F')

                                # DEBOUNCE: Clear the buffers!
                                # Forces the system to wait for 2 full seconds of
                                # NEW data before it can trigger another toggle.
                                history_x.clear()
                                history_y.clear()

                    except ValueError:
                        pass  # Ignore corrupted serial lines

    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
    finally:
        ser.write(b'F')  # Ensure LED turns off when script stops
        ser.close()
        print("Serial connection closed.")


if __name__ == "__main__":
    main()
