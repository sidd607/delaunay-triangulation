#include "edge.h"
#include <math.h>

float Edge::getDistance(const Vec2f &v){

  float x1 = float(p1.x);
  float y1 = float(p1.y);

  float x2 = float(p2.x);
  float y2 = float(p2.y);

  float pointX = float(v.x);
  float pointY = float(v.y);

  float diffX = x2 - x1;
  float diffY = y2 - y1;

  if ((diffX == 0) && (diffY == 0))
  {
      diffX = pointX - x1;
      diffY = pointY - y1;
      return sqrt(diffX * diffX + diffY * diffY);
  }

  float t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

  if (t < 0)
  {
      //point is nearest to the first point i.e x1 and y1
      diffX = pointX - x1;
      diffY = pointY - y1;
  }
  else if (t > 1)
  {
      //point is nearest to the end point i.e x2 and y2
      diffX = pointX - x2;
      diffY = pointY - y2;
  }
  else
  {
      //if perpendicular line intersect the line segment.
      diffX = pointX - (x1 + t * diffX);
      diffY = pointY - (y1 + t * diffY);
  }

  //returning shortest distance
  return sqrt(diffX * diffX + diffY * diffY);
}
