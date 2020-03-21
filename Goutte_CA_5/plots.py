# plots
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("ticks")

fname = "kepler.dat"

# get data
x, y = np.loadtxt(fname, delimiter = ' ', usecols = (0,1), unpack = True)

# plot
f = plt.figure()
plt.plot(x, y, label = fname, c = "darkslategrey")
plt.title("Trajectory of particle in Kepler potential")
plt.xlabel("$x$")
plt.ylabel("$y$")
plt.axis('equal')
plt.savefig("x_vs_y_plot.pdf")
plt.legend()
plt.ion()
plt.show(block = True)