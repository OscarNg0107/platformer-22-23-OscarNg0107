//
// Created by OscarNg on 2023/3/21.
//
#include <SFML/Graphics.hpp>
#ifndef PLATFORMERSFML_TILEMAP_H
#define PLATFORMERSFML_TILEMAP_H

class Tilemap : public sf::Drawable, public sf::Transformable
{
 public:
  bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
  bool collisionCheck(sf::IntRect player_hitbox, int tile_type, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

 private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states ) const;

  sf::VertexArray vertices;
  sf::Texture tileset_texture;


};

#endif // PLATFORMERSFML_TILEMAP_H
