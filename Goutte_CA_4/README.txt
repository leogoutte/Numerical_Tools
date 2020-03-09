Leo Goutte
PHYS 351
Mac OS
------------------------------------------------------------------------------------------
--> Open the Goutte_CA_4.zip file (it includes all of the source (.c) files, the corresponding header (.h) files, the main, executable, results, and this README)

--> To make your own executable, in the terminal run:

	gcc -o main_exec main.c vector_mtx.c init.c forces.c evolve.c rk4.c -lm

--> To execute the program, run (make sure that the input file InitParams is in .txt format and following the order prescribed in the assignment):

	./main_exec InitParams.txt

--> To plot the files, go into `Results/plots.py` and set the filenema `fname` to the appropriate q[3] (i.e 200 for 2.00 or 201 for 2.01). Then run:

	python plots.py

--> Note that I have renamed the program's output file for the two different q[3]'s with the superscript equal to that value without the dot (.) . If you want to run the above command make sure you have this file in your working directory from having run the compile command. The output file name is chosen in `evolve.c`.

--> To see the plots without running, simply go into the results folder with a superscript of the desired q[3].

--> ANSWER TO FINAL QUESTION:

The two different systems (q[3] = 2.00 and q[3] = 2.01) behave completely unrelatedly. They have the same shapes, as there are physical constraints to where they can and can't be, but otherwise they have nothing to do with each other and move in a comlpetely chaotic and unrelated (w.r.t each other) motion.