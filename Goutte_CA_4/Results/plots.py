# Leo Goutte
# Code to plot graphs associated with assignment 4
# PHYS 351

import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns
sns.set_style('white')

import warnings
warnings.filterwarnings("ignore")

# import data
fname = "result_201.dat"
data = np.loadtxt(open(fname), delimiter = ' ')

# sort into arrays
times = np.asarray([item[0] for item in data])
theta_1 = np.asarray([item[1] for item in data]) # not needed
theta_1 = np.asarray([item[2] for item in data]) # not needed
p_1 = np.asarray([item[3] for item in data])
p_2 = np.asarray([item[4] for item in data])
x_1 = np.asarray([item[5] for item in data]) # not needed
y_1 = np.asarray([item[6] for item in data]) # not needed
x_2 = np.asarray([item[7] for item in data])
y_2 = np.asarray([item[8] for item in data])
energy = np.asarray([item[9] for item in data])

# start plotting

# p_1 vs p_2
fig = plt.figure()
plt.title("$p_1$ vs $p_2$")
plt.xlabel("$p_1$")
plt.ylabel("$p_2$")
plt.plot(p_1, p_2, c = 'cadetblue')
plt.savefig("p1_vs_p2.pdf")
plt.show(block = True)

# x_2 vs y_2 
fig = plt.figure()
plt.title("$x_2$ vs $y_2$")
plt.xlabel("$x_2$")
plt.ylabel("$y_2$")
plt.plot(x_2, y_2, c = 'cadetblue')
plt.savefig("x2_vs_y2.pdf")
plt.show(block = True)

# total energy vs time
fig = plt.figure()
plt.title("Total energy vs time")
plt.xlabel("Time")
plt.ylabel("Energy")
ave_ene = np.average(energy)
plt.ylim([ave_ene - 0.1, ave_ene + 0.1])
plt.plot(times, energy, c = 'cadetblue')
plt.savefig("ene_vs_t.pdf")
plt.show(block = True)

###