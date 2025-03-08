#ifndef MATH_HPP
#define MATH_HPP
#include<cmath>
struct vector2f
{
    public:
      float x,y;
      vector2f()
      :x(0.0f),y(0.0f)
      {}
      vector2f(float p_x,float p_y)
      :x(p_x),y(p_y)
      {

      }
    vector2f operator+(const vector2f other)
    {
        return {x+other.x,y+other.y};
    }
    vector2f operator*(const float scalar)
    {
        return {scalar*x,scalar*y};
    }
    void normalise()
    {
        float length=sqrt(x*x+y*y);
        x=x/length;
        y=y/length;
    }
};
#endif // MATH_HPP
