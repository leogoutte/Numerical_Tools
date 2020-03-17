# plots
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
sns.set_style("ticks")

fname = "kepler.dat"

# get data
kepler_data = np.loadtxt(open(fname), delimiter = ' ')

x = [item[0] for item in kepler_data]
y = [item[1] for item in kepler_data]

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