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
#include "incr.h"
#include "lawson.h"

#include "GL/freeglut.h"
#include "GL/gl.h"

typedef Vector2<float> Vec2f;

float RandomFloat(float a, float b) {
    return float(rand() % int(b) + a);
}


int main(int argc, char** argv)
{
	srand (time(NULL));
	float numberPoints = roundf(RandomFloat(4, 40));
  numberPoints = 10;
  int window_height = 800;
  int window_width = 600;

	std::cout << "Generating " << numberPoints << " random points" << std::endl;

	std::vector<Vec2f> points;
	for(int i = 0; i < numberPoints; i++) {
    float x, y;
    std::cin>>x>>y;
		points.push_back(Vec2f(x,y));
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
		std::cout << e << std::endl;

  std::cout << "LAWSON------------------------------------------------------\n";
  Lawson lawson_triangulation;
  std::vector<Triangle> lawson_triangles = lawson_triangulation.triangulate(points, triangles);
  std::vector<Edge> lawson_edges = lawson_triangulation.getEdges();


  // openGl Drawing for Incremental Delaunay Triangulation

  Draw *incremental = new Draw("Geometric Modelling", edges);
  incremental->draw_window(argc, argv);
  delete incremental;

  //----------------------------------------------------------------------------
	return 0;
}
