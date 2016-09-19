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

#include "GL/freeglut.h"
#include "GL/gl.h"



typedef Vector2<float> Vec2f;

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

std::vector<Edge> global_incremental_edges;

void renderFunction(){
  
  std::cout << "From Render Function" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
  for(auto &e : global_incremental_edges){
    glBegin(GL_LINES);
      glVertex2f(e.p1.x, e.p1.y);
      glVertex2f(e.p2.x, e.p2.y);
    glEnd();
  }

  glFlush();
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

  global_incremental_edges = edges;

  // openGl Drawing for Incremental Delaunay Triangulation
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(window_height,window_height);
  glutCreateWindow("Incremental Delaunay Triangulation");
  glClearColor(0, 0, 0, 0);
  glViewport(0, 0, window_height, window_width);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window_height, 0, window_width, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutDisplayFunc(renderFunction);
  glutMainLoop();

	return 0;
}
