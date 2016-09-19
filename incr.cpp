#include "incr.h"
#include <algorithm>

const std::vector<Triangle>& Incr::triangulate(std::vector<Vec2f> &vertices)
{
	// Store the vertices localy
	_vertices = vertices;

	Vec2f p1(vertices[0].x, vertices[0].y);
	Vec2f p2(vertices[1].x, vertices[1].y);
	Vec2f p3(vertices[2].x, vertices[2].y);

  _triangles.push_back(Triangle(p1, p2, p3));

  for(auto p = begin(vertices)+3; p != end(vertices); p++){
    std::cout << "Vertex:" << *p <<std::endl;
    std::vector<Triangle> badTriangles;
    int flag = 0;
    for (auto t = begin(_triangles); t!=  end(_triangles); t++){
      if (t-> triangleContains(*p)){
        std::cout << "Inside Triangle\n";
        badTriangles.push_back(*t);
        flag = 1;
      }
      else{
        std::cout << "Outside Triangle\n";

      }
    }

    if (flag == 0){
      auto t = begin(_triangles);
      Edge min_edge = t->e1;
      float min_dist = min_edge.getDistance(*p);

      for(auto t = begin(_triangles); t != end(_triangles); t++){
        if(t->e1.getDistance(*p) <= min_dist){
          min_edge = t->e1;
          min_dist = t->e1.getDistance(*p);
        }
        if(t->e2.getDistance(*p) <= min_dist){
          min_edge = t->e2;
          min_dist = t->e2.getDistance(*p);
        }
        if(t->e3.getDistance(*p) <= min_dist){
          min_edge = t->e3;
          min_dist = t->e3.getDistance(*p);
        }
      }
      std::cout << "Min Dist " << min_dist << "\n";
      _triangles.push_back(Triangle(*p, min_edge.p1, min_edge.p2));
    }


    std::cout << "Bad triangles " << badTriangles.size() << std::endl;

    //Removing Bad Triangle
    _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [badTriangles](Triangle &t){
			for(auto bt = begin(badTriangles); bt != end(badTriangles); bt++)
			{
				if(*bt == t)
				{
					std::cout << "Removing bad triangle " << std::endl << *bt << " from _triangles" << std::endl;
					return true;
				}
			}
			return false;
		}), end(_triangles));


    //Adding New triangles

    for(auto t = begin(badTriangles); t!= end(badTriangles); t++ ){
      _triangles.push_back(Triangle(t->p1, t->p2, *p));
      _triangles.push_back(Triangle(t->p2, t->p3, *p));
      _triangles.push_back(Triangle(t->p3, t->p1, *p));

    }
    std::cout << "Triangle Size: " << _triangles.size() << std::endl;
  }

  /*
	// Determinate the super triangle
	float minX = vertices[0].x;
	float minY = vertices[0].y;
	float maxX = minX;
	float maxY = minY;

	Vec2f p1(vertices[0].x, vertices[0].y);
	Vec2f p2(vertices[1].x, vertices[1].y);
	Vec2f p3(vertices[2].x, vertices[2].y);

	std::cout << "Super triangle " << std::endl << Triangle(p1, p2, p3) << std::endl;

	// Create a list of triangles, and add the supertriangle in it
	_triangles.push_back(Triangle(p1, p2, p3));

	for(auto p = begin(vertices); p != end(vertices); p++)
	{
		std::cout << "Traitement du point " << *p << std::endl;
		std::cout << "_triangles contains " << _triangles.size() << " elements" << std::endl;

		std::vector<Triangle> badTriangles;
		std::vector<Edge> polygon;

		for(auto t = begin(_triangles); t != end(_triangles); t++)
		{
			std::cout << "Processing " << std::endl << *t << std::endl;

			if(t->circumCircleContains(*p))
			{
				std::cout << "Pushing bad triangle " << *t << std::endl;
				//badTriangles.push_back(*t);
				polygon.push_back(t->e1);
				polygon.push_back(t->e2);
				polygon.push_back(t->e3);
			}
			else
			{
				std::cout << " does not contains " << *p << " in his circum center" << std::endl;
			}
		}

		_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [badTriangles](Triangle &t){
			for(auto bt = begin(badTriangles); bt != end(badTriangles); bt++)
			{
				if(*bt == t)
				{
					std::cout << "Removing bad triangle " << std::endl << *bt << " from _triangles" << std::endl;
					return true;
				}
			}
			return false;
		}), end(_triangles));

		std::vector<Edge> badEdges;
		for(auto e1 = begin(polygon); e1 != end(polygon); e1++)
		{
			for(auto e2 = begin(polygon); e2 != end(polygon); e2++)
			{
				if(e1 == e2)
					continue;

				if(*e1 == *e2)
				{
					badEdges.push_back(*e1);
					badEdges.push_back(*e2);

					std::cout << "@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
					std::cout << *e1 << std::endl;
					std::cout << *e2 << std::endl;

				}
			}
		}

		polygon.erase(std::remove_if(begin(polygon), end(polygon), [badEdges](Edge &e){
			for(auto it = begin(badEdges); it != end(badEdges); it++)
			{
				if(*it == e)
					return true;
			}
			return false;
		}), end(polygon));

		for(auto e = begin(polygon); e != end(polygon); e++)
			_triangles.push_back(Triangle(e->p1, e->p2, *p));

	}

	_triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](Triangle &t){
		return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
	}), end(_triangles));
  */
	for(auto t = begin(_triangles); t != end(_triangles); t++)
	{
		_edges.push_back(t->e1);
		_edges.push_back(t->e2);
		_edges.push_back(t->e3);
	}

	return _triangles;
}
