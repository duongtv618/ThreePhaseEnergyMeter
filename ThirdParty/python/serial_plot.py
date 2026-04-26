import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

PORT = "/dev/ttyACM0"
BAUD = 115200

ser = serial.Serial(PORT, BAUD)
data = {k: deque(maxlen=200) for k in ["Vrms", "Irms", "P", "Q", "PF", "THD"]}
fig, axes = plt.subplots(2, 3, figsize=(12, 6))
axes = axes.flatten()

def update(frame):
    try:
        line = ser.readline().decode().strip()
        vals = list(map(float, line.split(",")))
        for i, k in enumerate(data):
            data[k].append(vals[i])
        for i, (k, ax) in enumerate(zip(data, axes)):
            ax.cla()
            ax.plot(data[k])
            ax.set_title(k)
    except:
        pass

ani = animation.FuncAnimation(fig, update, interval=100)
plt.tight_layout()
plt.show()