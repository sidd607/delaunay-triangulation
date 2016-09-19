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
  //glClearColor(0.0, 0.0, 0.0, 0.0);
  std::cout << "From Render Function" << std::endl;

  glClear(GL_COLOR_BUFFER_BIT);
  //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  /*
  glBegin(GL_LINES);
      glVertex2f(10, 10);
      glVertex2f(400, 400);
  glEnd();
  */

  for(auto &e : global_incremental_edges){
    std::cout << e << std::endl;
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
  numberPoints = 100;

	std::cout << "Generating " << numberPoints << " random points" << std::endl;

	std::vector<Vec2f> points;
	for(int i = 0; i < numberPoints; i++) {
		points.push_back(Vec2f(RandomFloat(0, 1000), RandomFloat(0, 1000)));
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


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(1000,1000);
  glutCreateWindow("OpenGL - First window demo");
  glClearColor(0, 0, 0, 0);
  glViewport(0, 0, 1000, 1000);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1000, 0, 1000, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutDisplayFunc(renderFunction);
  glutMainLoop();


	// SFML window
  //sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  /*
	// Transform each points of each vector as a rectangle
	std::vector<sf::RectangleShape*> squares;

	for(auto p = begin(points); p != end(points); p++) {
		sf::RectangleShape *c1 = new sf::RectangleShape(sf::Vector2f(4, 4));
		c1->setPosition(p->x, p->y);
		squares.push_back(c1);
	}

	// Make the lines
	std::vector<std::array<sf::Vertex, 2> > lines;
	for(auto e = begin(edges); e != end(edges); e++) {
		lines.push_back({{
			sf::Vertex(sf::Vector2f((*e).p1.x + 2, (*e).p1.y + 2)),
			sf::Vertex(sf::Vector2f((*e).p2.x + 2, (*e).p2.y + 2))
		}});
	}

	while (window.isOpen())
	{
	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	        window.clear();

		// Draw the squares
		for(auto s = begin(squares); s != end(squares); s++) {
			window.draw(**s);
		}

		// Draw the lines
		for(auto l = begin(lines); l != end(lines); l++) {
			window.draw((*l).data(), 2, sf::Lines);
		}

		window.display();
	}
  */
	return 0;
}
