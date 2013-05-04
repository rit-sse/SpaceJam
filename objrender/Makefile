all:
	clang++ -c *.cpp
	clang++ -ggdb -o objrender -framework OpenGL -framework GLUT -framework CoreFoundation *.o -lFreeImage

clean:
	rm -rf *.o objrender
