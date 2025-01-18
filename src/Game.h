
#ifndef PONG_GAME_H
#define PONG_GAME_H

#include "Vector2.h"
#include "GameObject.h"
#include "Ball.h"
#include "Paddle.h"

#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();

  void initGraphics();
  void initText(
    sf::Text* text,
    Vector2 position,
    Vector2 scale,
    sf::Color color = sf::Color(255, 255, 255, 255));
  void initUI();

  void startGame();
  void continueGame();
  void spawnObjects();
  void tally(Paddle* winning_paddle);
  void startTimer(double time);

  void update(double dt);
  void render();

  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

  // Game elements
  bool is_playing = true;
  bool isPlaying() const;
  void setIsPlaying(bool isPlaying);

  sf::Clock clock;
  bool is_timer_running = false;
  bool isTimerRunning() const;
  void setIsTimerRunning(bool isTimerRunning);
  void (Game::*timerFunction)() = nullptr;

  double start_time = 0;
  double current_time = 0;
  double target_time = 0;

  Vector2 middle_of_screen;

  // Main gameplay objects
  Ball ball;
  Paddle paddle1;
  Paddle paddle2;

  enum game_states
  {
    TITLE,
    GAMEPLAY,
    PAUSED,
    GAME_OVER,
    CHOOSE_GAME_MODE
  };
  game_states current_game_state;
  game_states target_game_state;
  void changeState(game_states new_state);
  void fade();

 private:
  sf::RenderWindow& window;
  Paddle *winner_paddle = nullptr;

  // Gameplay toggles
  double gameplay_pause_time = 0;
  double gameplay_fade_time = 0;
  int winning_score = 0;

  // UI elements
  bool is_fading = false;
  bool isFading() const;
  void setIsFading(bool isFading);
  sf::RectangleShape fade_anim;
  double fade_anim_state = 0;
  int fade_anim_direction = 0;

  sf::Font font;
  std::string game_text[18] =
    {
      "Super Ultra Mega Pong 4000",
      "Play",
      "Quit",
      "Games in C++",
      "Programmed by Dominik Heiler",
      "Game Paused",
      "Continue",
      "Back to Menu",
      "Player 1 wins!",
      "Player 2 wins!",
      "Thank you for playing! Try again?",
      "Restart",
      "Back to Menu",
      "Please choose a Game Mode",
      "Player VS Player",
      "Player VS CPU",
      "Easy",
      "Hard"
    };

  GameObject background;
  sf::Text game_text_objects[18];
  sf::Text game_counter_objects[2];
  int menu_option = 0;
  int menu_second_option = 0;
};

#endif // PONG_GAME_H
