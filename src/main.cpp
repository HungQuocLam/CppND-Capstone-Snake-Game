#include <iostream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"

#define NUMB_OF_BOMB 5

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, NUMB_OF_BOMB);
  game.Run(controller, renderer, kMsPerFrame);
  game.Gamewinner();

  std::cout << "**********************************************************************\n"; 
  std::cout << "**********************************************************************\n"; 
  std::cout << " Game has terminated successfully! \n";
  std::cout << " Score Snake 1: " << game.GetScore(Snake::Player::kPlayerOne) << "\n";
  std::cout << " Score Snake 2: " << game.GetScore(Snake::Player::kPlayerTwo) << "\n";
  if (Snake::Player::kNULL != game.winner)
  {
    std::cout << " Congratulation to Player " << std::to_string(static_cast<int>(game.winner)) <<" - You are the winner \n";
  }
  else 
  {
    std::cout << " Game is draw! \n";
  }
 std::cout << "**********************************************************************\n"; 
 std::cout << "**********************************************************************\n"; 
  return 0;
}