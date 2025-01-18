
#include "Vector2.h"
#include "GameObject.h"

#include <iostream>

/*
 * Load in a texture for the current object's sprite
 */
void GameObject::updateSprite(std::string file_path)
{
  if (!texture.loadFromFile(file_path))
  {
    std::cout << " Texture for " << file_path << " unable to be loaded in!" << std::endl;
  }
  sprite.setTexture(texture);
}

/*
 * Update the object's current position
 */
void GameObject::updatePos()
{
  sprite.setPosition(position.x, position.y);
}

/*
 * Get the centre point of the object's current sprite
 */
Vector2 GameObject::getMidPoint() const
{
  double mid_point_x = position.x + (sprite.getGlobalBounds().width / 2);
  double mid_point_y = position.y + (sprite.getGlobalBounds().height / 2);

  Vector2 new_vector(mid_point_x, mid_point_y);

  return new_vector;
}

/*
 * Checks for if the current object's sprite is overlapping another sprite
 */
bool GameObject::collision(GameObject other_object)
{
  // Basic AABB collision detection
  // First checking for horizontal overlap
  bool collision_x = (position.x + sprite.getGlobalBounds().width) > other_object.position.x
                     and (other_object.position.x + other_object.sprite.getGlobalBounds().width) > position.x;

  // Then checking for vertical overlap
  bool collision_y = (position.y + sprite.getGlobalBounds().height) > other_object.position.y
                     and (other_object.position.y + other_object.sprite.getGlobalBounds().height) > position.y;

  if (collision_x and collision_y)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*
 * Override method for object movement
 */
void GameObject::move(double dt)
{

}
