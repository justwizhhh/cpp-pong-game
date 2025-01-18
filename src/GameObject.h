
#ifndef PONGSFML_GAMEOBJECT_H
#define PONGSFML_GAMEOBJECT_H

#include "Vector2.h"

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class GameObject
{
 public:
  Vector2 position;
  double move_speed = 0;

  sf::Sprite sprite;
  sf::Texture texture;

  void updateSprite(std::string file_path);
  void updatePos();
  bool collision(GameObject other_object);

  Vector2 getMidPoint() const;
  virtual void move(double dt);

};

#endif // PONGSFML_GAMEOBJECT_H
