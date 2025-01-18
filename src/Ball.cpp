
#include "Vector2.h"
#include "GameObject.h"
#include "Ball.h"

#include "cmath"

Ball::Ball()
{
  spawn_move_speed = 22.5;
  spawn_move_angle = 5;
  speed_addition = 0.5;
  speed_max = 40;
  max_bounce_limit = 50;

  move_speed = spawn_move_speed;

  spawn_move_direction = ((std::rand() % 2) * 2) - 1;
}

/*
 * Updating the ball's position every frame
 */
void Ball::move(double dt)
{
  position.add(move_direction.scale(move_speed * dt));
}

/*
 * Reset the ball's current angle, based on which part of the paddle(s) it has hit
 */
void Ball::bounce(GameObject other_object)
{
  // Find out whether the ball is facing to the left or right side of the paddle
  int collision_side = position.x <= other_object.position.x ? 1 : -1;

  // Change the ball's direction depending on the angle between that and the colliding paddle
  Vector2 direction_scale(getMidPoint().x - (other_object.getMidPoint().x + (collision_side * max_bounce_limit)),
                          getMidPoint().y - other_object.getMidPoint().y);

  direction_scale = direction_scale.getUnitVector();
  move_direction = direction_scale.scale(move_speed);

  // Scale up the ball's movement speed slightly
  if (move_speed <= speed_max)
  {
    move_speed += speed_addition;
  }
  else
  {
    move_speed = speed_max;
  }
}
