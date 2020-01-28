Leo Goutte
PHYS 351
Mac OS
------------------------------------------------------------------------------------------

Task 1 instructions:

-> Have vector_mtx.h, vector_mtx.c, and main_taks_1.c in the same directory.

-> In the terminal, run:
	gcc main_task_1.c vector_mtx.c -o main_exec -lm

-> Next, run:
	./main_exec

-> The output should be:
	This should be 0: 0.000000000000000e+00

-> (If you just want to see the plots, skip this step) // To plot the data, run:
	python task1_plots.py

-> To see the graph files of each plot, simply click on the respective file with the .pdf extension in the folder.

------------------------------------------------------------------------------------------

Task 2 instructions: 

-> In the terminal, run (make sure that the input file is a .txt file):
	 ./init_test my_input.txt

-> Note: we get the init_test executable from running
	gcc main.c params.c -o init_test -lm

-> Once the executable is ran, this will print out the parameters and create an output file, InitParams.dat. This file will was placed in the results subfolder.
