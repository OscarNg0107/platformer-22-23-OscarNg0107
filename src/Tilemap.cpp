//
// Created by OscarNg on 2023/3/21.
//
#include <iostream>

#include "Tilemap.h"

bool Tilemap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
  if(!tileset_texture.loadFromFile(tileset))
  {
    return false;
  }

  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(width* height *4);

  for(unsigned int i = 0; i<width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      int tileNumber = tiles[i + j * width];

      int tu = tileNumber % (tileset_texture.getSize().x / tileSize.x);
      int tv = tileNumber / (tileset_texture.getSize().x / tileSize.x);

      sf::Vertex* quad = &vertices[(i + j *width) *4 ];


      quad[0].position = sf::Vector2f(i * tileSize.x, j *tileSize.y);
      quad[1].position = sf::Vector2f((i +1) * tileSize.x, j *tileSize.y);
      quad[2].position = sf::Vector2f((i +1) * tileSize.x, (j + 1) *tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j +1) *tileSize.y);

      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv *tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu +1) * tileSize.x, tv *tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) *tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) *tileSize.y);
    }
  }
  return true;
}

bool Tilemap::collisionCheck(sf::IntRect player_hitbox, int tile_type, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
  for(unsigned int i = 0; i<width; i++)
  {
    for (unsigned int j = 0; j < height; j++)
    {
      int tile_number = tiles[i + j * width];
      if(tile_number == tile_type)
      {
        sf::IntRect tile_hitbox( i *tileSize.x , j *tileSize.y, tileSize.x, tileSize.y);

        if((player_hitbox.left + player_hitbox.width > tile_hitbox.left )&
             (player_hitbox.left < tile_hitbox.left + tile_hitbox.width) &&
            ((player_hitbox.top + player_hitbox.height > tile_hitbox.top) &
             (player_hitbox.top < tile_hitbox.top + tile_hitbox.height)))
        {
          return true;
        }
      }
    }
  }
  return false;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  states.texture = &tileset_texture;

  target.draw(vertices, states);
}