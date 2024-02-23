//
// Created by OscarNg on 2023/3/7.
// referenced Vector2.h from space invaders
//

#ifndef PLATFORMERSFML_VECTOR2_H
#define PLATFORMERSFML_VECTOR2_H

struct Vector2
{
  // construction
  Vector2(float x_, float y_);
  Vector2(const Vector2& rhs);

  // operations
  Vector2 operator*(float scalar);
  Vector2& operator=(const Vector2& rhs);
  void normalise();

  // data
  float x = 0;
  float y = 0;
};

#endif // PLATFORMERSFML_VECTOR2_H
