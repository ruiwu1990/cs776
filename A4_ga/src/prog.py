import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("outfile_189")
x, y = data[:, 0], data[:,3]

plt.plot(x, y, linewidth=2.0)
plt.show()
