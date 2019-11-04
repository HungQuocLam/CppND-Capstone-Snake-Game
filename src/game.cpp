#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int bomb_num)
    : snake(grid_width, grid_height, static_cast<float>(grid_width/2), static_cast<float>(grid_height/2), Snake::Direction::kUp, Snake::Player::kPlayerOne),
      snake2(grid_width, grid_height, static_cast<float>(grid_width/2), static_cast<float>(grid_height/2), Snake::Direction::kDown, Snake::Player::kPlayerTwo),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)-1),
      random_h(0, static_cast<int>(grid_height)-1),
      winner(Snake::Player::kNULL),
      bomb_m(static_cast<int>(grid_width), static_cast<int>(grid_height), bomb_num) 
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
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake, snake2);
    Update();
    renderer.Render(snake, snake2, bomb_m, food);

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
  bool bomb_check{false};
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake or bomb item before placing
    // food.
    for (SDL_Point const &point : bomb_m.position){
      if (x == point.x && y == point.y){
        bomb_check = false;
        break;
      }
      else bomb_check = true;
    }
    if (!snake.SnakeCell(x, y) && !snake2.SnakeCell(x, y) && bomb_check) {
      food.x = x;
      food.y = y;
      break;
    }
  }
  std::cout << "food " << "(" << food.x << "," << food.y << ")" << "\n";
}

void Game::Update() {
  if (!snake.alive || !snake2.alive) {
    return;
  }

  if (snake.get_moving()){
    // 1st snake update
    snake.Update();
  }
  if (snake2.get_moving()){
    // 2nd snake update
    snake2.Update();
  }

  // check if snake1 hit the bombs
  if (!snake.get_moving()){
    if (static_cast<int>(timer.elapsedSeconds()) > TIMER_ELAPSE){
      snake.set_moving(true);
      timer.stop(); 
      std::cout << "Timer stoped" << "\n";  
    }  
  }
  else{
    for (SDL_Point const &point : bomb_m.position){
      // snake hit bomb 
      if (snake.SnakeCell(point.x, point.y) && snake.hit_pos.x != point.x && snake.hit_pos.y != point.y){
        snake.set_moving(false);
        timer.start(); 
        snake.hit_pos = point;
        std::cout << "Timer started" << "\n";
      }
    }
  }
  
  // check if snake2 hit the bombs
  if (!snake2.get_moving()){
    if (static_cast<int>(timer2.elapsedSeconds()) > TIMER_ELAPSE){
      snake2.set_moving(true);
      timer2.stop(); 
      std::cout << "Timer2 stoped" << "\n";  
    }  
  }
  else{
    for (SDL_Point const &point : bomb_m.position){
      // snake hit bomb 
      if (snake2.SnakeCell(point.x, point.y) && snake2.hit_pos.x != point.x && snake2.hit_pos.y != point.y){
        snake2.set_moving(false);
        timer2.start(); 
        snake2.hit_pos = point;
        std::cout << "Timer2 started" << "\n";
      }
    }
  }

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
  // check if 1st snake die
  for(const auto item: snake.BodyPosition()){
    if(new_x == item.x && new_y == item.y && snake.alive){
      snake.alive = false;
      std::cout << "Snake 1 has died\n";
    }
  }
  // check if 2nd snake die
  for(const auto item: snake2.BodyPosition()){
    if(new_x2 == item.x && new_y2 == item.y && snake.alive){
      snake2.alive = false;
      std::cout << "Snake 2 has died\n";
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
