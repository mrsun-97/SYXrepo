#%%
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure

x1 = np.linspace(0.0, 5.0)
x2 = np.linspace(0.0, 3.0)

y1 = np.cos(2 * np.pi * x1) * np.exp(-x1)
y2 = np.cos(2 * np.pi * x2)

figure, ax1 = plt.subplots(1,1)
# plt.subplots_adjust(left=0.14, bottom=0.1)
# ax1 = figure.add_axes([0.14, 0.35, 0.77, 0.6 ])
ax1.grid(True)
ax1.plot(x1, y1, 'yo-', label="Test1")
ax1.plot(x2, y2, 'r.-', label='Test2')

plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)

plt.show()