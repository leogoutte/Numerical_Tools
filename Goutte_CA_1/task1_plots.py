# Leo Goutte
# Code to plot graphs associated with task 1
# PHYS 351

import matplotlib.pyplot as plt 

import warnings
warnings.filterwarnings("ignore")

plt.plotfile('GOUTTE_test1.dat', delimiter=' ', cols=(0,1), names=('column 1', 'column 2 // column 3'), marker='o', label ='Column 2')
plt.plotfile('GOUTTE_test1.dat', 	delimiter=' ', cols=(0,2), names=('column 1', 'column 2', 'column 3 // column 3'), marker='+', label='Column 3', newfig=False) 
plt.legend()
plt.savefig('GOUTTE_test1.pdf')
plt.show()

plt.plotfile('GOUTTE_test2.dat', delimiter=' ', cols=(0,1), names=('column 1', 'column 2 // column 3'), marker='o', label ='Column 2')
plt.plotfile('GOUTTE_test2.dat', delimiter=' ', cols=(0,2), names=('column 1', 'column 2', 'column 3 // column 3'), marker='+', label='Column 3', newfig=False) 
plt.legend()
plt.savefig('GOUTTE_test2.pdf')
plt.show()