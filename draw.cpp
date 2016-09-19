#include "draw.h"
#include "GL/freeglut.h"
#include "GL/gl.h"


Draw::Draw( std::string title, std::vector <Edge> edges){
  this->window_title = title;
  this->window_edges = edges;
}

std::vector<Edge> edges_to_draw;

void Draw::set_edges(){
  edges_to_draw = this->window_edges;
}

void render_function(){
  std::cout << "From Render Function" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
  for(auto &e : edges_to_draw){
    glBegin(GL_LINES);
      glVertex2f(e.p1.x, e.p1.y);
      glVertex2f(e.p2.x, e.p2.y);
    glEnd();
  }

  glFlush();
}


void Draw::draw_window(int argc, char** argv){
  int window_height = 800;
  int window_width = 600;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(window_height,window_height);
  glutCreateWindow(this->window_title.c_str());
  glClearColor(0, 0, 0, 0);
  glViewport(0, 0, window_height, window_width);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window_height, 0, window_width, 1, -1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  this->set_edges();
  glutDisplayFunc(render_function);
  glutMainLoop();
}
