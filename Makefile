all:
	g++ *.cpp -std=c++11 -lGL -lGLU -lglut -lglfw -o delaunay

clean:
	rm delaunay
