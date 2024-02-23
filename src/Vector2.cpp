//
// Created by OscarNg on 2023/3/7.
//referenced Vector2.cpp from space invaders
//
#include <math.h>

#include "Vector2.h"

Vector2::Vector2(float x_, float y_) : x(x_), y(y_) {}

Vector2::Vector2(const Vector2& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
  this->x = rhs.x;
  this->y = rhs.y;

  return *this;
}

void Vector2::normalise()
{
  float magnitude = sqrtf((x * x) + (y * y));

  if (!magnitude)
    return;

  x /= magnitude;
  y /= magnitude;
}

Vector2 Vector2::operator*(float scalar)
{
  Vector2 vec(*this);
  vec.x *= scalar;
  vec.y *= scalar;
  return vec;
}
