//
// Created by OscarNg on 2023/3/7.
//
#include <iostream>

#include "Text.h"

Text::Text()
{
  text_ptr = new sf::Text;
}

void Text::init(const std::string& text_string , const sf::Font& font, int size)
{
  text.setString(text_string);
  text.setFont(font);
  text.setCharacterSize(size);
}

sf::Text* Text::getText()
{
  text_ptr =&text;
  *text_ptr = text;
  return  text_ptr;
}

Text::~Text()
{
  if(text_ptr != nullptr)
  {
    delete text_ptr;
    text_ptr = nullptr;
  }
}