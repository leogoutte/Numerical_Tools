# Leo Goutte
# Code to plot graphs associated with assignment 3
# PHYS 351

import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns
sns.set_style('white')

import warnings
warnings.filterwarnings("ignore")

num_eq = 3
it_max = 100 # set to it_max run
fname = "coordinates.dat" # data file name

# plot each coordinate (angular momentum) vs time
for i in range(num_eq): 
	# note that i,j correspond to q_i, and not the column number in .dat file
	plt.plotfile(fname, delimiter=' ', cols=(0,i+1), c='black')
	plt.title('$q_{%d}$ as a function of time for torque-free motion (it_max = %d)' %(i, it_max))
	plt.xlabel('Time')
	plt.ylabel('$q_{%d}$' %i)
	plt.savefig('q_%d_vs_t_%d.pdf' %(i,it_max)) # plots are saved under q_i_vs_t.pdf
	plt.show(block = True)

# plot kinetic energy vs time
plt.plotfile(fname, delimiter=' ', cols=(0,4), c='black')
plt.title('Kinetic Energy as a function of time for torque-free motion (it_max = %d)' %it_max)
plt.xlabel("Time")
plt.ylabel("Kinetic Energy")
plt.ylim(0,50) # set limits to see straight lines
plt.savefig("kinetic_energy_%d.pdf" %it_max)
plt.show(block = True)

# plot phase space
# do a couple inelegant loops to only get mixed i,j's once over
for i in range(num_eq): 
	for j in range(num_eq):
		if i == j:
			pass
		elif i > j:
			pass
		else:
			plt.plotfile(fname, delimiter = ' ', cols = (i+1, j+1), c = 'black',
				label = '$q_{%d}$ vs $q_{%d}$' %(i, j))
			plt.title("Phase space of $q_{%d}$ vs $q_{%d}$ (it_max = %d)" %(i, j, it_max))
			plt.xlabel("$q_{%d}$" %i)
			plt.ylabel("$q_{%d}$" %j)
			plt.legend(loc = 'upper right')
			plt.savefig("q_%d_vs_q_%d_%d.pdf" %(i, j, it_max))
			plt.show(block = True)

###
