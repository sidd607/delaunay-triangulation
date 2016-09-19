#ifndef H_DRAW
#define H_DRAW

// OpenGL Libraries
#include <string>
#include <vector>
#include "edge.h"

class Draw {
  public:
    Draw(std::string title, std::vector<Edge> edges);

    std::string window_title;
    std::vector<Edge> window_edges;

    void draw_window(int argc,char** argv);
    void set_edges();

};



#endif
