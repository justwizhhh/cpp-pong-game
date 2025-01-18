
#include "Vector2.h"

#include "cmath"

Vector2::Vector2()
{
  x = 0.0;
  y = 0.0;
}

// Basic operations
void Vector2::set(Vector2 other_vector)
{
  x = other_vector.x;
  y = other_vector.y;
}

void Vector2::add(Vector2 other_vector)
{
  x += other_vector.x;
  y += other_vector.y;
}

/*
 * Multiplying (or dividing) two vectors by each other
 */
Vector2 Vector2::multiply(Vector2 other_vector)
{
  Vector2 new_vector;
  new_vector.x = x * other_vector.x;
  new_vector.y = y * other_vector.y;
  return new_vector;
}

/*
 * Scaling a vector by a set value
 */
Vector2 Vector2::scale(double scale_value)
{
  Vector2 new_vector;
  new_vector.x = x * scale_value;
  new_vector.y = y * scale_value;
  return new_vector;
}


// Complex operations
double Vector2::getMagnitude() const
{
  return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::getUnitVector() const
{
  Vector2 new_vector;
  new_vector.x = x / getMagnitude();
  new_vector.y = y / getMagnitude();
  return new_vector;
}

