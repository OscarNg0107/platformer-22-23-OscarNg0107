//
// Created by st2-ng on 14/03/2023.
//

#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

bool Character::isOnMovingPlatform()
{
  return on_moving_platform;
}
void Character::setOnMovingPlatform(bool boolean)
{
  on_moving_platform = boolean;
}
bool Character::isDead()
{
  return dead;
}
void Character::setDead(bool boolean)
{
  Character::dead = boolean;
}
