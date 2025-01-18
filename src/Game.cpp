
#include "Game.h"
#include "GameObject.h"
#include "Paddle.h"

#include "cmath"
#include <array>
#include <string>
#include <iostream>

Game::Game(sf::RenderWindow& game_window) : window(game_window)
{
  srand(time(nullptr));

  current_game_state = TITLE;
  target_game_state = CHOOSE_GAME_MODE;

  gameplay_pause_time = 1.6;
  gameplay_fade_time = 0.5;
  winning_score = 5;
}

Game::~Game()
= default;

bool Game::init()
{
  middle_of_screen.x = window.getSize().x / 2;
  middle_of_screen.y = window.getSize().y / 2;

  setIsTimerRunning(false);
  setIsFading(false);
  fade_anim.setPosition(0, 0);
  fade_anim.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  fade_anim.setFillColor(sf::Color(0, 0, 0, 0));

  initGraphics();
  initUI();
  return true;
}

/*
 * Load in all textures for game-object graphics
 */
void Game::initGraphics()
{
  background.updateSprite("Data/Images/New/background.png");
  ball.updateSprite("Data/Images/New/ball.png");
  paddle1.updateSprite("Data/Images/New/player1.png");
  paddle2.updateSprite("Data/Images/New/player2.png");
}

/*
 * Take current text object, and give it a set size (scale), position, and option colour
 */
void Game::initText(sf::Text* text, Vector2 position, Vector2 scale, sf::Color color)
{
  text->setScale(scale.x, scale.y);
  text->setPosition(position.x, position.y);
  text->setFillColor(color);
}

/*
 * Load in UI-related graphics
 */
void Game::initUI()
{
  if (!font.loadFromFile("Data/Images/New/press-start-2p-font/PressStart2P-vaV7.ttf"))
  {
    std::cout << "Font not loaded correctly! \n";
  }
  // Give all text objects common attributes (same font, same origin point, etc.)
  for (int i = 0; i < (std::end(game_text_objects) - std::begin(game_text_objects)); i++)
  {
    game_text_objects[i].setString(game_text[i]);
    game_text_objects[i].setFont(font);
    game_text_objects[i].setOrigin(
      game_text_objects[i].getGlobalBounds().width / 2,
      game_text_objects[i].getGlobalBounds().height / 2);
  }
  // Title-screen text
  initText(
    &game_text_objects[0],
    Vector2(middle_of_screen.x, middle_of_screen.y - 70),
    Vector2(1, 1));
  initText(
    &game_text_objects[1],
    Vector2(middle_of_screen.x, middle_of_screen.y + 50),
    Vector2(0.7, 0.7));
  initText(
    &game_text_objects[2],
    Vector2(middle_of_screen.x, middle_of_screen.y + 90),
    Vector2(0.7, 0.7), sf::Color(128, 128, 128, 255));
  initText(
    &game_text_objects[3],
    Vector2(middle_of_screen.x, middle_of_screen.y + 200),
    Vector2(0.45, 0.45));
  initText(
    &game_text_objects[4],
    Vector2(middle_of_screen.x, middle_of_screen.y + 220),
    Vector2(0.45, 0.45));

  // Pause screen text
  initText(
    &game_text_objects[5],
    Vector2(middle_of_screen.x, middle_of_screen.y - 70),
    Vector2(1.2, 1.2));
  initText(
    &game_text_objects[6],
    Vector2(middle_of_screen.x, middle_of_screen.y + 15),
    Vector2(0.6, 0.6));
  initText(
    &game_text_objects[7],
    Vector2(middle_of_screen.x, middle_of_screen.y + 65),
    Vector2(0.6, 0.6),
    sf::Color(128, 128, 128, 255));

  // Game-over screen text
  initText(
    &game_text_objects[8],
    Vector2(middle_of_screen.x, middle_of_screen.y - 70),
    Vector2(1.6, 1.6));
  initText(
    &game_text_objects[9],
    Vector2(middle_of_screen.x, middle_of_screen.y - 70),
    Vector2(1.6, 1.6));
  initText(
    &game_text_objects[10],
    Vector2(middle_of_screen.x, middle_of_screen.y + 10),
    Vector2(0.8, 0.8));
  initText(
    &game_text_objects[11],
    Vector2(middle_of_screen.x - 260, middle_of_screen.y + 120),
    Vector2(0.8, 0.8));
  initText(
    &game_text_objects[12],
    Vector2(middle_of_screen.x + 260, middle_of_screen.y + 120),
    Vector2(0.8, 0.8),
    sf::Color(128, 128, 128, 255));

  // Game-mode selection screen text
  initText(
    &game_text_objects[13],
    Vector2(middle_of_screen.x, middle_of_screen.y - 90),
    Vector2(1.1, 1.1));
  initText(
    &game_text_objects[14],
    Vector2(middle_of_screen.x, middle_of_screen.y + 30),
    Vector2(0.8, 0.8));
  initText(
    &game_text_objects[15],
    Vector2(middle_of_screen.x, middle_of_screen.y + 80),
    Vector2(0.8, 0.8),
    sf::Color(128, 128, 128, 255));
  initText(
    &game_text_objects[16],
    Vector2(middle_of_screen.x + 320, middle_of_screen.y + 80),
    Vector2(0.8, 0.8));
  initText(
    &game_text_objects[17],
    Vector2(middle_of_screen.x + 440, middle_of_screen.y + 80),
    Vector2(0.8, 0.8),
    sf::Color(128, 128, 128, 255));

  // Loading in gameplay counters
  for (int i = 0; i < (std::end(game_counter_objects) - std::begin(game_counter_objects)); i++)
  {
    game_counter_objects[i].setString(std::to_string(0));
    game_counter_objects[i].setFont(font);
    game_counter_objects[i].setOrigin(
      game_counter_objects[i].getGlobalBounds().width / 2,
      game_counter_objects[i].getGlobalBounds().height / 2);
  }
  initText(
    &game_counter_objects[0],
    Vector2(window.getSize().x - 80, 95),
    Vector2(2.4, 2.4));
  initText(
    &game_counter_objects[1],
    Vector2(80, 95),
    Vector2(2.4, 2.4));
}

/*
 * Reset all scores and object positions, before transitioning back into gameplay
 */
void Game::startGame()
{
  paddle1.score = 0;
  paddle2.score = 0;
  game_counter_objects[0].setString(std::to_string(0));
  game_counter_objects[1].setString(std::to_string(0));

  spawnObjects();
  setIsPlaying(false);
  changeState(game_states::GAMEPLAY);
}

/*
 * Toggle object movement and player inputs to be processed again
 */
void Game::continueGame()
{
  fade_anim.setFillColor(sf::Color(0, 0, 0, 0));
  setIsTimerRunning(false);
  setIsPlaying(true);
}

/*
 * Set spawn positions (as well as movement speeds) for main gameplay objects
 */
void Game::spawnObjects()
{
  // Paddles spawning positions
  paddle1.position.set(middle_of_screen);
  paddle1.position.x -= (paddle1.sprite.getGlobalBounds().width / 2) + 400;
  paddle1.position.y -= paddle1.sprite.getGlobalBounds().height / 2;

  paddle2.position.set(middle_of_screen);
  paddle2.position.x -= (paddle2.sprite.getGlobalBounds().width / 2) - 400;
  paddle2.position.y -= paddle2.sprite.getGlobalBounds().height / 2;

  // Ball spawning position/direction
  ball.position.set(middle_of_screen);
  ball.position.x -= ball.sprite.getGlobalBounds().width / 2;
  ball.position.y -= ball.sprite.getGlobalBounds().height / 2;

  ball.move_speed = ball.spawn_move_speed;
  ball.move_direction.x = ball.spawn_move_direction * ball.move_speed;
  ball.move_direction.y = 0;

  paddle1.updatePos();
  paddle2.updatePos();
  ball.updatePos();
}

/*
 * Update relevant scores and re-start the game
 */
void Game::tally(Paddle* scoring_paddle)
{
  setIsPlaying(false);
  spawnObjects();

  // Checking for winning/losing conditions for both paddles
  game_counter_objects[0].setString(std::to_string(paddle1.score));
  game_counter_objects[1].setString(std::to_string(paddle2.score));
  if (scoring_paddle->score >= winning_score)
  {
    winner_paddle = scoring_paddle;
    changeState(game_states::GAME_OVER);
  }
  else
  {
    timerFunction = &Game::continueGame;
    setIsFading(false);
    startTimer(gameplay_pause_time);
  }
}

/*
 * Takes the current time on the clock and uses that to measure time
 */
void Game::startTimer(double time)
{
  setIsTimerRunning(true);
  start_time = clock.getElapsedTime().asSeconds();
  target_time = start_time + time;
}

/*
 * Transition from one gameplay/menu screen to another
 */
void Game::changeState(Game::game_states new_state)
{
  menu_option = 0;
  menu_second_option = 0;

  paddle1.resetInput();
  paddle2.resetInput();

  target_game_state = new_state;

  // Fading out animation
  setIsPlaying(false);
  setIsFading(true);
  timerFunction = &Game::fade;
  fade_anim_direction = 1;
  startTimer(gameplay_fade_time);
}

/*
 * Start playing fading in animation while changing the current game screen
 */
void Game::fade()
{
  fade_anim.setFillColor(sf::Color(0, 0, 0, 255));
  current_game_state = target_game_state;
  timerFunction = &Game::continueGame;
  fade_anim_direction = -1;
  startTimer(gameplay_fade_time);
}

/*
 * Gameplay logic updated every frame
 */
void Game::update(double dt)
{
  // Update current timer
  if (isTimerRunning())
  {
    current_time = clock.getElapsedTime().asSeconds();

    // If there is still time remaining, update all relevant UI animations
    if (isFading())
    {
      fade_anim_state = fade_anim_direction == 1
                          ? (current_time - start_time) / (target_time - start_time)
                          : 1 - (current_time - start_time) / (target_time - start_time);

      fade_anim.setFillColor(sf::Color(0, 0, 0, fade_anim_state * 255));
    }

    // If not, end the timer and call whatever function was given to the pointer and continue play
    if (current_time >= target_time)
    {
      if (timerFunction != nullptr)
      {
        // A function pointer is used to allow the timer to be used for multiple different actions
        // This stops me from having to make multiple clock objects for different timed events
        (this->*timerFunction)();
      }
      else
      {
        setIsTimerRunning(false);
        setIsFading(false);
      }
    }
  }

  // Afterwards, run the rest of the gameplay logic
  switch(current_game_state)
  {
    case game_states::TITLE:
      // Title-screen update behaviour
      break;

    case game_states::GAMEPLAY:
      // Main gameplay with all necessary object movements and player inputs
      if (isPlaying())
      {
        // Basic object interactions
        ball.updatePos();
        ball.move(dt);
        paddle1.updatePos();
        paddle2.updatePos();
        paddle1.move(dt);
        if (paddle2.ai_controlled)
        {
          paddle2.aiMove(dt, ball);
        }
        else
        {
          paddle2.move(dt);
        }


        // Horizontal collisions with the paddles, since the ball does not bounce off of any other horizontal surface in-game
        if (ball.collision(paddle1))
        {
          ball.bounce(paddle1);
        }
        if (ball.collision(paddle2))
        {
          ball.bounce(paddle2);
        }


        // Vertical collisions (with just the floor and ceiling)
        if (ball.position.y < 0)
        {
          ball.move_direction.y *= -1;
          ball.position.y = 0;
        }
        if (ball.position.y > (window.getSize().y - ball.sprite.getGlobalBounds().height))
        {
          ball.move_direction.y *= -1;
          ball.position.y = (window.getSize().y - ball.sprite.getGlobalBounds().height);
        }


        // Score counting for each paddle
        if (ball.position.x < -ball.sprite.getGlobalBounds().width)
        {
          ball.spawn_move_direction = -1;
          paddle1.addToScore();
          tally(&paddle1);
        }
        if (ball.position.x > (window.getSize().x))
        {
          ball.spawn_move_direction = 1;
          paddle2.addToScore();
          tally(&paddle2);
        }
      }
      break;

    case game_states::PAUSED:
      // Pause screen update behaviour
      break;

    case game_states::GAME_OVER:
      // Game-over screen update behaviour
      break;

    case game_states::CHOOSE_GAME_MODE:
      // Game-mode selection menu update behaviour
      break;
  }
}

/*
 * Input event for when the player presses a key
 */
void Game::keyPressed(sf::Event event)
{
  if (isPlaying())
  {
    switch(current_game_state)
    {
      case game_states::TITLE:
        switch (event.key.code)
        {
          // Main menu controls and selection visuals
          case sf::Keyboard::Up:
            menu_option = 0;
            game_text_objects[1].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[2].setFillColor(sf::Color(128, 128, 128, 255));
            break;
          case sf::Keyboard::Down:
            menu_option = 1;
            game_text_objects[1].setFillColor(sf::Color(128, 128, 128, 255));
            game_text_objects[2].setFillColor(sf::Color(255, 255, 255, 255));
            break;

          case sf::Keyboard::Enter:
            game_text_objects[1].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[2].setFillColor(sf::Color(128, 128, 128, 255));
            if (menu_option == 0)
            {
              changeState(game_states::CHOOSE_GAME_MODE);
            }
            else
            {
              exit(0);
            }
            break;
        }
        break;

      case game_states::GAMEPLAY:
        // Player 1 and Player 2 movements
        switch (event.key.code)
        {
          // Paddle controls
          case sf::Keyboard::W:
            paddle1.up_input = true;
            break;
          case sf::Keyboard::S:
            paddle1.down_input = true;
            break;
          case sf::Keyboard::Up:
            paddle2.up_input = true;
            break;
          case sf::Keyboard::Down:
            paddle2.down_input = true;
            break;

          case sf::Keyboard::Enter:
            // Basic pause function
            changeState(game_states::PAUSED);
            break;

          case sf::Keyboard::R:
            // Debug function
            spawnObjects();
            break;

          case sf::Keyboard::U:
            // Debug function
            setIsPlaying(!isPlaying());
            break;
        }
        break;

      case game_states::PAUSED:
        switch (event.key.code)
        {
          // Menu controls and selection visuals
          case sf::Keyboard::Up:
            menu_option = 0;
            game_text_objects[6].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[7].setFillColor(sf::Color(128, 128, 128, 255));
            break;
          case sf::Keyboard::Down:
            menu_option = 1;
            game_text_objects[6].setFillColor(sf::Color(128, 128, 128, 255));
            game_text_objects[7].setFillColor(sf::Color(255, 255, 255, 255));
            break;

          case sf::Keyboard::Enter:
            game_text_objects[6].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[7].setFillColor(sf::Color(128, 128, 128, 255));
            if (menu_option == 0)
            {
              changeState(game_states::GAMEPLAY);
              break;
            }
            else
            {
              changeState(game_states::TITLE);
              break;
            }
        }
        break;

      case game_states::GAME_OVER:
        switch (event.key.code)
        {
          // Menu controls and selection visuals
          case sf::Keyboard::Left:
            menu_option = 0;
            game_text_objects[11].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[12].setFillColor(sf::Color(128, 128, 128, 255));
            break;
          case sf::Keyboard::Right:
            menu_option = 1;
            game_text_objects[11].setFillColor(sf::Color(128, 128, 128, 255));
            game_text_objects[12].setFillColor(sf::Color(255, 255, 255, 255));
            break;

          case sf::Keyboard::Enter:
            game_text_objects[11].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[12].setFillColor(sf::Color(128, 128, 128, 255));
            if (menu_option == 0)
            {
              startGame();
              break;
            }
            else
            {
              changeState(game_states::TITLE);
              break;
            }
        }
        break;

      case game_states::CHOOSE_GAME_MODE:
        switch (event.key.code)
        {
          // Menu controls and selection visuals
          case sf::Keyboard::Up:
            menu_option = 0;
            game_text_objects[14].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[15].setFillColor(sf::Color(128, 128, 128, 255));
            break;
          case sf::Keyboard::Down:
            menu_option = 1;
            game_text_objects[14].setFillColor(sf::Color(128, 128, 128, 255));
            game_text_objects[15].setFillColor(sf::Color(255, 255, 255, 255));

            break;

          case sf::Keyboard::Left:
            if (menu_option == 1)
            {
              menu_second_option = 0;
              game_text_objects[16].setFillColor(sf::Color(255, 255, 255, 255));
              game_text_objects[17].setFillColor(sf::Color(128, 128, 128, 255));
            }
            break;
          case sf::Keyboard::Right:
            if (menu_option == 1)
            {
              menu_second_option = 1;
              game_text_objects[16].setFillColor(sf::Color(128, 128, 128, 255));
              game_text_objects[17].setFillColor(sf::Color(255, 255, 255, 255));
            }

            break;

          case sf::Keyboard::Enter:
            game_text_objects[14].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[15].setFillColor(sf::Color(128, 128, 128, 255));
            game_text_objects[16].setFillColor(sf::Color(255, 255, 255, 255));
            game_text_objects[17].setFillColor(sf::Color(128, 128, 128, 255));
            if (menu_option == 0)
            {
              paddle2.setAiControlled(false);
            }
            else
            {
              paddle2.setAiControlled(true);
              paddle2.ai_difficulty = menu_second_option;
            }
            startGame();
            break;
        }
        break;
    }
  }
}

/*
 * Input event for when the player releases a key
 */
void Game::keyReleased(sf::Event event)
{
  switch(current_game_state)
  {
    case game_states::TITLE:

      break;

    case game_states::GAMEPLAY:
      // Player 1 and Player 2 movements
      switch(event.key.code)
      {
        // Paddle controls
        case sf::Keyboard::W:
          paddle1.up_input = false;
          break;
        case sf::Keyboard::S:
          paddle1.down_input = false;
          break;
        case sf::Keyboard::Up:
          paddle2.up_input = false;
          break;
        case sf::Keyboard::Down:
          paddle2.down_input = false;
          break;
      }
      break;

    case game_states::PAUSED:

      break;

    case game_states::GAME_OVER:

      break;

    case game_states::CHOOSE_GAME_MODE:

      break;
  }
}

/*
 * For displaying all graphics and text onto the game-screen
 */
void Game::render()
{
  switch(current_game_state)
  {
    case game_states::TITLE:
      // Game title, and main menu options
      window.draw(game_text_objects[0]);
      window.draw(game_text_objects[1]);
      window.draw(game_text_objects[2]);
      window.draw(game_text_objects[3]);
      window.draw(game_text_objects[4]);
      break;

    case game_states::GAMEPLAY:
      // Main gameplay elements
      window.draw(background.sprite);
      window.draw(paddle1.sprite);
      window.draw(paddle2.sprite);
      window.draw(ball.sprite);

      if (isTimerRunning())
      {
        window.draw(game_counter_objects[0]);
        window.draw(game_counter_objects[1]);
      }
      break;

    case game_states::PAUSED:
      // A few gameplay elements, plus the paused text itself
      window.draw(background.sprite);

      window.draw(game_text_objects[5]);
      window.draw(game_text_objects[6]);
      window.draw(game_text_objects[7]);

      window.draw(game_counter_objects[0]);
      window.draw(game_counter_objects[1]);
      break;

    case game_states::GAME_OVER:
      // Player win declaration, plus restart buttons
      window.draw(game_text_objects[winner_paddle == &paddle1 ? 9 : 8]);
      window.draw(game_text_objects[10]);
      window.draw(game_text_objects[11]);
      window.draw(game_text_objects[12]);

      window.draw(game_counter_objects[0]);
      window.draw(game_counter_objects[1]);
      break;

    case game_states::CHOOSE_GAME_MODE:
      // Game-mode selection buttons
      window.draw(game_text_objects[13]);
      window.draw(game_text_objects[14]);
      window.draw(game_text_objects[15]);
      if (menu_option == 1)
      {
        window.draw(game_text_objects[16]);
        window.draw(game_text_objects[17]);
      }
      break;
  }
  window.draw(fade_anim);
}

bool Game::isPlaying() const
{
  return is_playing;
}
void Game::setIsPlaying(bool isPlaying)
{
  is_playing = isPlaying;
}
bool Game::isTimerRunning() const
{
  return is_timer_running;
}
void Game::setIsTimerRunning(bool isTimerRunning)
{
  is_timer_running = isTimerRunning;
}
bool Game::isFading() const
{
  return is_fading;
}
void Game::setIsFading(bool isFading)
{
  is_fading = isFading;
}
