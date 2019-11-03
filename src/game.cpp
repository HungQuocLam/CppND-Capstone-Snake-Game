#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height, static_cast<float>(0), static_cast<float>(0), Snake::Direction::kUp, Snake::Player::kPlayerOne),
      snake2(grid_width, grid_height, static_cast<float>(grid_width/2), static_cast<float>(grid_height/2), Snake::Direction::kDown, Snake::Player::kPlayerTwo),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      winner(Snake::Player::kNULL) 
{
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    if (!snake.alive || !snake2.alive) {
      if (!snake.alive) std::cout << "Snake Player 1 died \n";
      else if (!snake2.alive) std::cout << "Snake Player 2 died\n";
      return;
    }
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, snake2);
    Update();
    renderer.Render(snake, snake2, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, score2, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {

  // 1st snake update
  snake.Update();
  // 2nd snake update
  snake2.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  int new_x2 = static_cast<int>(snake2.head_x);
  int new_y2 = static_cast<int>(snake2.head_y);

  // Check if there's food over 1st snake 
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.01;
  }
  // Or 2nd snake
  else if (food.x == new_x2 && food.y == new_y2) {
    score2++;
    PlaceFood();
    // Grow snake and increase speed.
    snake2.GrowBody();
    snake2.speed += 0.01;
  }

  // 1st snake die
  for(const auto item: snake.BodyPosition()){
    if(new_x == item.x && new_y == item.y && snake.alive){
      snake.alive = false;
      winner = Snake::Player::kPlayerTwo;

    }
  }
  // 2nd snake die
  for(const auto item: snake2.BodyPosition()){
    if(new_x2 == item.x && new_y2 == item.y && snake.alive){
      snake2.alive = false;
      winner = Snake::Player::kPlayerOne;     
    }
  }

}

int Game::GetScore(Snake::Player player) const { 
  if (Snake::Player::kPlayerOne == player)
    return score;   
  else
    return score2;  
}

int Game::GetSize(Snake::Player player) const { 
  if (Snake::Player::kPlayerOne == player)
    return snake.size;
  else
    return snake2.size;
}

void Game::Gamewinner()
{

  if (false == snake.alive)
  { 
    winner = Snake::Player::kPlayerTwo; 
  }
  else if (false == snake2.alive)
  { 
    winner = Snake::Player::kPlayerOne; 
  }
  else
  {
    // Check score
    if (score > score2)
    {
      winner = Snake::Player::kPlayerOne; 
    }
    else if (score < score2)
    {
      winner = Snake::Player::kPlayerTwo; 
    }
    else 
    {
      winner = Snake::Player::kNULL;
    }
  }
}
