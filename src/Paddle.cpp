
#include "Paddle.h"

#include <algorithm>

Paddle::Paddle()
{
  score = 0;

  move_speed = 650;
  min_pos = 0;
  max_pos = 520;

  // How quickly the AI paddle should 'try' and move towards the ball
  ai_speeds[0] = 3;
  ai_speeds[1] = 6;
}

/*
 * Update the paddle's movement through manual player input
 */
void Paddle::move(double dt)
{
  int dir;
  dir = up_input ? -1 : down_input ? 1 : 0;

  position.y += (move_speed * dt) * dir;

  // Clamp y position to prevent off-screen moving
  position.y = std::max(min_pos, std::min(position.y, max_pos));
}

/*
 * Update the paddle's movement through AI logic moving it as close to the ball as possible
 */
void Paddle::aiMove(double dt, GameObject ball)
{
  double midpoint = position.y + (sprite.getGlobalBounds().height / 2);
  double ball_midpoint = ball.position.y + (ball.sprite.getGlobalBounds().height / 2);
  double distance = ball_midpoint - midpoint;

  // Smoothly move the paddle towards the ball, using the distance between them
  double current_difficulty = ai_speeds[ai_difficulty];
  position.y += std::max(-move_speed, std::min(distance * current_difficulty, move_speed)) * dt;

  // Clamp y position to prevent off-screen moving
  position.y = std::max(min_pos, std::min(position.y, max_pos));
}

void Paddle::addToScore()
{
  score++;
}

void Paddle::resetInput()
{
  up_input = false;
  down_input = false;
}

bool Paddle::isAiControlled() const
{
  return ai_controlled;
}
void Paddle::setAiControlled(bool aiControlled)
{
  ai_controlled = aiControlled;
}
