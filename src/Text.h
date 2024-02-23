//
// Created by OscarNg on 2023/3/7.
//
#include <SFML/Graphics.hpp>

#ifndef PLATFORMERSFML_TEXT_H
#define PLATFORMERSFML_TEXT_H

class Text
{
 public:
  Text();
  ~Text();
  void init(const std::string& text_string , const sf::Font& font, int size);
  sf::Text* getText();


 private:
  sf::Text text;
  sf::Text* text_ptr = nullptr;

};

#endif // PLATFORMERSFML_TEXT_H
