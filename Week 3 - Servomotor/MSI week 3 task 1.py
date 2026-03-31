import serial
import time

# Tukar 'COM3' ikut port kau
ser = serial.Serial('COM5', 9600)
time.sleep(2)

try:
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            if line.isdigit():
                val = int(line)
                print(f"Reading: {val}")

                # Logic LED: Lebih 512 (separuh daripada 1023)
                if val > 512:
                    ser.write(b'1') # Hantar '1' untuk ON
                else:
                    ser.write(b'0') # Hantar '0' untuk OFF
        time.sleep(0.1)
except KeyboardInterrupt:
    ser.close()
