Leo Goutte
PHYS 351
Mac OS
------------------------------------------------------------------------------------------
--> Open the Goutte_CA_3.zip file (it includes all of the source (.c) files, the corresponding header (.h) files, the main, executable, results, and this README)

--> To make your own executable, in the terminal run:

	gcc -o exec_main main.c vector_mtx.c init.c forces.c analysis.c evolve.c -lm

--> To execute the program, run (make sure that the input file InitParams is in .txt format and following the order prescribed in the assignment):

	./exec_main InitParams.txt

--> To plot the files, go into `Goutte_CA3_plots.py` and set it_max to the desired maximum interval. Then run:

	python Goutte_CA3_plots.py

--> Note that I have renamed the program's output file for the two different it_max's with the superscript equal to this integer. `Goutte_CA3_plots.py` requires the existence of a `coordinates.dat` file, so if you want to run the above command make sure you have this file in your working directory from having run the compile command.   

--> To see the plots without running, simply go into the results folder with a superscript of the desired it_max (i.e: go into `Results_100/` or `Results_1000/`)

