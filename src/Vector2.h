
#ifndef PONGSFML_VECTOR2_H
#define PONGSFML_VECTOR2_H

class Vector2
{
 public:
  Vector2();
  Vector2(double x_val, double y_val)
  {
    x = x_val;
    y = y_val;
  }

  double x;
  double y;

  // Basic operations
  void set(Vector2 other_vector);
  void add(Vector2 other_vector);
  Vector2 multiply(Vector2 other_vector);
  Vector2 scale(double scale_value);

  // Complex operations
  double getMagnitude() const;
  Vector2 getUnitVector() const;
};

#endif // PONGSFML_VECTOR2_H
