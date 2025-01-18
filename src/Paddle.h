
#ifndef PONGSFML_PADDLE_H
#define PONGSFML_PADDLE_H

#include "GameObject.h"

#include <algorithm>

class Paddle: public GameObject
{
 public:
  Paddle();

  bool up_input = false;
  bool down_input = false;

  int score;

  bool ai_controlled = false;
  bool isAiControlled() const;
  void setAiControlled(bool aiControlled);

  int ai_difficulty = 0;
  double ai_speeds[2] = {0, 0};

  void move(double dt) override;
  void aiMove(double dt, GameObject ball);
  void addToScore();
  void resetInput();

 private:
  double min_pos = 0;
  double max_pos = 0;
};

#endif // PONGSFML_PADDLE_H
