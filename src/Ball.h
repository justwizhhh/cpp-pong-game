
#ifndef PONGSFML_BALL_H
#define PONGSFML_BALL_H

#include "Vector2.h"
#include "GameObject.h"

class Ball: public GameObject
{
 public:
  Ball();

  Vector2 move_direction;

  double spawn_move_speed = 0.0;
  int spawn_move_direction = 0;
  int spawn_move_angle = 0;

  void move(double dt) override;
  void bounce(GameObject other_object);

 private:
  double speed_addition = 0;
  double speed_max = 0;

  double max_bounce_limit = 0.0;
};

#endif // PONGSFML_BALL_H
