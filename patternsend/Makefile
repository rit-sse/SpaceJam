all: projector.o shell.o lightcrafter.o
	dmd *.o -ofshell.out


lightcrafter.o: lightcrafter/constants.d
	dmd lightcrafter/constants.d -c	

projector.o: lightcrafter/projector.d
	dmd lightcrafter/projector.d -c
   
   
shell.o: shell.d	
	dmd shell.d -c


clean:
	rm *.o
	rm shell.out


