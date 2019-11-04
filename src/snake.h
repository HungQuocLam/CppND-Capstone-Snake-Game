#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum class Player { kNULL, kPlayerOne, kPlayerTwo };
  Snake(int grid_width, int grid_height, float head_x, float heady_y, Direction direction, Player player)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(heady_y),
        direction(direction),
        player(player) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction ;
  Player player;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  
  std::vector<SDL_Point> body;
  std::vector<SDL_Point> BodyPosition();

  SDL_Point hit_pos;

  void set_moving (bool moving);
  bool get_moving (void);
 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  bool moving{true};
  int grid_width;
  int grid_height;
};

#endif