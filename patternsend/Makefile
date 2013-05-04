all: projector.o shell.o constants.o patternsend.o 
	dmd constants.o projector.o shell.o -ofshell.out
	dmd constants.o projector.o patternsend.o -ofpatternsend


constants.o: lightcrafter/constants.d
	dmd lightcrafter/constants.d -c	

projector.o: lightcrafter/projector.d
	dmd lightcrafter/projector.d -c
   

patternsend.o: patternsend.d
	  dmd patternsend.d -c
   
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
