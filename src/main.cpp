#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  game.Gamewinner();
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score Snake 1: " << game.GetScore(Snake::Player::kPlayerOne) << "\n";
  std::cout << "Size Snake 1: " << game.GetSize(Snake::Player::kPlayerOne) << "\n";
  std::cout << "Score Snake 2: " << game.GetScore(Snake::Player::kPlayerTwo) << "\n";
  std::cout << "Size Snake 2: " << game.GetSize(Snake::Player::kPlayerTwo) << "\n";

  if (Snake::Player::kPlayerOne == game.winner)
  {
    std::cout << " Congratulation to Player 1 - You are the winner!\n";
  }
  else if (Snake::Player::kPlayerTwo == game.winner)
  {
    std::cout << " Congratulation to Player 2 - You are the winner!\n";
  }
  else 
  {
    std::cout << " Congratulation to both players - Game is draw!\n";
  }
  return 0;
}