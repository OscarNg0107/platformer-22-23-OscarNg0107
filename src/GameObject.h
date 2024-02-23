//
// Created by OscarNg on 2023/3/7.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Vector2.h"

#ifndef PLATFORMERSFML_GAMEOBJECT_H
#  define PLATFORMERSFML_GAMEOBJECT_H

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  void initialiseSprite(sf::Texture& texture, std::string filename);
  sf::Sprite* getSprite();
  void setMovingDirection(float x, float y);
  Vector2 getMovingDirection();

  void setMoveLeftBool(bool boolean);
  bool getMoveLeftBool();

  void setMoveRightBool(bool boolean);
  bool getMoveRightBool();

  void setVisibility(bool boolean);
  bool getVisibility();

 private:
  sf::Sprite object_sprite;
  sf::Sprite* sprite_ptr = nullptr;
  Vector2 moving_direction = Vector2(0, 0);
  bool visibility          = true;
  bool move_right          = false;
  bool move_left           = false;

};

#endif // PLATFORMERSFML_GAMEOBJECT_H
