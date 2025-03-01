#ifndef MATH_HPP
#define MATH_HPP
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
};
#endif // MATH_HPP
