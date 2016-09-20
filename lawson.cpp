#include "lawson.h"
#include <algorithm>

const std::vector<Triangle>& Lawson::triangulate(std::vector<Vec2f> &vertices, std::vector<Triangle> &triangulation){
  _triangles = triangulation;
  _vertices = vertices;
  std::vector<Edge> illegal_edge;
  for (auto t = begin(_triangles); t!= end(_triangles); t++){
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    for(auto e = begin(illegal_edge); e != end(illegal_edge); e++){
      if (*e == t->e1){
        std::cout << *e <<"\t"<<t->e1 << std::endl;
        flag1 = 1;
      }
      if (*e == t->e2){
        std::cout << *e <<"\t"<<t->e2 << std::endl;
        flag2 = 1;
      }
      if (*e == t->e3){
        std::cout << *e <<"\t"<<t->e3 << std::endl;
        flag3 = 1;
      }
    }
    if (flag1 == 0)
      illegal_edge.push_back(t->e1);
    if (flag2 == 0)
      illegal_edge.push_back(t->e2);
    if (flag3 == 0)
      illegal_edge.push_back(t->e3);
  }

  while(illegal_edge.size()>0){
    Edge e = illegal_edge[illegal_edge.size() -1];
    illegal_edge.pop_back();
    std::cout << "Edge: " << e << std::endl;
    std::vector<Triangle> triangle_list;
    for (auto t = begin(_triangles); t != end(_triangles); t++){
      if(t->e1 == e || t->e2 == e || t->e3 == e){
        triangle_list.push_back(*t);
      }
    }
    std::cout << "SIZE OF Triangle: " << triangle_list.size() << std::endl;
    if(triangle_list.size() == 2){
      Vec2f p1, p2, p3, p4;
      if (triangle_list[0].p1 == e.p1 && triangle_list[0].p2 == e.p2){
        p1 = triangle_list[0].p1;
        p2 = triangle_list[0].p2;
        p3 = triangle_list[0].p3;
      }
      if (triangle_list[0].p2 == e.p1 && triangle_list[0].p3 == e.p2){
        p1 = triangle_list[0].p2;
        p2 = triangle_list[0].p3;
        p3 = triangle_list[0].p1;
      }
      if (triangle_list[0].p3 == e.p1 && triangle_list[0].p1 == e.p2){
        p1 = triangle_list[0].p3;
        p2 = triangle_list[0].p1;
        p3 = triangle_list[0].p2;
      }
      std::cout << "Triangle: " << triangle_list[1] << std::endl;
      std::cout << "Edge : " << e <<std::endl;
      if (triangle_list[1].p1 == e.p1 && triangle_list[1].p2 == e.p2){
        std::cout << "Condition1\n";
        std::cout << triangle_list[1].p3;
        p4 = triangle_list[1].p3;
      }

      if (triangle_list[1].p2 == e.p1 && triangle_list[1].p3 == e.p2){
        std::cout << "Condition2\n";
        p4 = triangle_list[1].p1;
      }

      if (triangle_list[1].p3 == e.p1 && triangle_list[1].p1 == e.p2){
        std::cout << "Condition3\n";
        p4 = triangle_list[1].p2;
      }

      std::cout << "Vertices : " <<p1 << p2<<p3<<p4 <<std::endl;
      if(triangle_list[0].circumCircleContains(p4)){
        _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [triangle_list](Triangle &t){
          for(auto bt = begin(triangle_list); bt != end(triangle_list); bt++)
          {
            if(*bt == t)
            {
              //std::cout << "Removing bad triangle " << std::endl << *bt << " from _triangles" << std::endl;
              return true;
            }
          }
          return false;
        }), end(_triangles));

        _triangles.push_back(Triangle(p1, p4, p3));
        _triangles.push_back(Triangle(p2, p4, p3));

        int flag = 0;
        for(auto ie = begin(illegal_edge); ie != end(illegal_edge); ie++){
          if(*ie == Edge(p1, p4))
            flag = 1;
        }
        if (flag != 1)
          illegal_edge.push_back(Edge(p1, p4));
        flag = 0;

        for(auto ie = begin(illegal_edge); ie != end(illegal_edge); ie++){
          if(*ie == Edge(p1, p3))
            flag = 1;
        }
        if (flag != 1)
          illegal_edge.push_back(Edge(p1, p3));
        flag = 0;


        for(auto ie = begin(illegal_edge); ie != end(illegal_edge); ie++){
          if(*ie == Edge(p3, p2))
            flag = 1;
        }
        if (flag != 1)
          illegal_edge.push_back(Edge(p3, p2));
        flag = 0;

        for(auto ie = begin(illegal_edge); ie != end(illegal_edge); ie++){
          if(*ie == Edge(p4, p2))
            flag = 1;
        }
        if (flag != 1)
          illegal_edge.push_back(Edge(p4, p2));
        flag = 0;

      }


    }
  }

  std::cout << "Size of Illegal Edge: " << illegal_edge.size() << std::endl;
  _edges = illegal_edge;
  for(auto t = begin(_triangles); t != end(_triangles); t++)
  {
    _edges.push_back(t->e1);
    _edges.push_back(t->e2);
    _edges.push_back(t->e3);
  }
  return _triangles;
}
