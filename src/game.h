#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "bomb_matrix.h"
#include "elapse_timer.h"

#define TIMER_ELAPSE 5 // 5 seconds after hitting bomb

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int bomb_num);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore(Snake::Player player) const;
  int GetSize(Snake::Player player) const;
  void Gamewinner();
  Snake::Player winner;

 private:
  Snake snake;
  Snake snake2;

  Bomb_matrix bomb_m; 

  std :: shared_ptr<SDL_Point> food;

  Elapse_timer timer;
  Elapse_timer timer2;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int score2{0};

  bool GameOver{false};

  void PlaceFood();
  void Update();

};

#endif