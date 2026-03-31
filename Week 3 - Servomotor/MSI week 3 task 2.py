import sys
import time

# WAZE: Paksa Python cari library kat folder betul
sys.path.append(r'C:\Users\FENDI\AppData\Local\Programs\Python\Python314\Lib\site-packages')

import serial
import matplotlib.pyplot as plt

# --- TUKAR COM KAT SINI IKUT PORT KAU ---
PORT = 'COM5' 

try:
    ser = serial.Serial(PORT, 9600, timeout=1)
    time.sleep(2)
    print(f"CONNECTED TO {PORT}!")
except:
    print("ERROR: TUTUP SERIAL MONITOR ARDUINO IDE!")
    sys.exit()

plt.ion()
fig, ax = plt.subplots()
data_list = [0] * 50 
line, = ax.plot(data_list, 'b-', linewidth=2) # Garisan Biru

ax.set_ylim(0, 1023)
ax.set_title("Task 2: Inky's Real-Time Plot")
ax.grid(True)

try:
    while True:
        line_raw = ser.readline().decode('utf-8').strip()
        if line_raw:
            try:
                val = int(line_raw)
                data_list.append(val)
                data_list.pop(0)
                line.set_ydata(data_list)
                plt.pause(0.01) # BIAR GRAF LUKIS
            except ValueError:
                pass
except KeyboardInterrupt:
    ser.close()
    plt.close()
