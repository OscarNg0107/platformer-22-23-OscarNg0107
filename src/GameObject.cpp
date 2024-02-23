//
// Created by OscarNg on 2023/3/7.
//

#include "GameObject.h"

GameObject::GameObject()
{
  sprite_ptr = new sf::Sprite;
}

void GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout<< "texture loading error";
  }
  object_sprite.setTexture(texture);

}

sf::Sprite* GameObject::getSprite()
{
  sprite_ptr = &object_sprite;
  *sprite_ptr = object_sprite;
  return sprite_ptr;
}

void GameObject::setMovingDirection(float x, float y)
{
  moving_direction.x = x;
  moving_direction.y = y;
}

Vector2 GameObject::getMovingDirection()
{
  return moving_direction;
}


void GameObject::setMoveLeftBool(bool boolean)
{
  move_left = boolean;
}

bool GameObject::getMoveLeftBool()
{
  return move_left;
}

void GameObject::setMoveRightBool(bool boolean)
{
  move_right = boolean;
}

bool GameObject::getMoveRightBool()
{
  return move_right;
}

void GameObject::setVisibility(bool boolean)
{
  visibility = boolean;
}

bool GameObject::getVisibility()
{
    return visibility;
}


GameObject::~GameObject()
{
  if(sprite_ptr != nullptr)
  {
    delete sprite_ptr;
    sprite_ptr = nullptr;
  }
}

