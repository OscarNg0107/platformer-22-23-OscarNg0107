//
// Created by st2-ng on 14/03/2023.
//
#include "GameObject.h"

#ifndef PLATFORMERSFML_CHARACTER_H
#define PLATFORMERSFML_CHARACTER_H

class Character : public GameObject
{
 public:
  Character();
  ~Character();

  bool isOnMovingPlatform();
  void setOnMovingPlatform(bool boolean);
  bool isDead();
  void setDead(bool boolean);


 private:
  bool dead;
  bool on_moving_platform = false;
};

#endif // PLATFORMERSFML_CHARACTER_H

