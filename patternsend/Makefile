all: projector.o shell.o lightcrafter.o
	dmd *.o -ofshell.out


lightcrafter.o: lightcrafter/constants.d
	dmd lightcrafter/constants.d -c	

projector.o: lightcrafter/projector.d
	dmd lightcrafter/projector.d -c
   
   
shell.o: shell.d	
	dmd shell.d -c


projector.test.o:
	dmd lightcrafter/projector.d -c -unittest

with-tests: lightcrafter.o shell.o projector.test.o
	dmd **.d -unittest 
   

clean:
	rm *.o
	rm shell.out



docs: all
	dmd -D -c shell.d
	dmd -D -c lightcrafter/constants.d
	dmd -D -c lightcrafter/projector.d
	mv *.html docs/
