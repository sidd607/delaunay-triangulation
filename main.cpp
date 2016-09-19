#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <array>
#include "vector2.h"
#include "triangle.h"
#include "delaunay.h"
#include "draw.h"

#include "GL/freeglut.h"
#include "GL/gl.h"

typedef Vector2<float> Vec2f;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


int main(int argc, char** argv)
{
	srand (time(NULL));
	float numberPoints = roundf(RandomFloat(4, 40));
  numberPoints = 5;
  int window_height = 800;
  int window_width = 600;

	std::cout << "Generating " << numberPoints << " random points" << std::endl;

	std::vector<Vec2f> points;
	for(int i = 0; i < numberPoints; i++) {
		points.push_back(Vec2f(RandomFloat(10, window_height - 10), RandomFloat(10, window_width - 10)));
	}

	Delaunay triangulation;
	std::vector<Triangle> triangles = triangulation.triangulate(points);
	std::cout << triangles.size() << " triangles generated\n";
	std::vector<Edge> edges = triangulation.getEdges();

	std::cout << " ========= ";

	std::cout << "\nPoints : " << points.size() << std::endl;
	for(auto &p : points)
		std::cout << p << std::endl;

	std::cout << "\nTriangles : " << triangles.size() << std::endl;
	for(auto &t : triangles)
		std::cout << t << std::endl;

	std::cout << "\nEdges : " << edges.size() << std::endl;
	for(auto &e : edges)
		std::cout << e.p1.x << std::endl;

  // openGl Drawing for Incremental Delaunay Triangulation
  Draw *incremental = new Draw("incremental", edges);
  incremental->draw_window(argc, argv);
  delete incremental;

	return 0;
}
