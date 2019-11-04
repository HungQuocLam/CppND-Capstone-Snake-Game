#ifndef BOMB_MATRIX_H
#define BOMB_MATRIX_H

#include <iostream>
#include <random>
#include <memory>
#include <vector>
#include "SDL.h"


class Bomb_matrix {
    public:
        Bomb_matrix(){std::cout << " Default constructor is called" << "\n";};
        Bomb_matrix( int grid_width, int grid_height, int bomb_num);
        

        std::vector<SDL_Point> position;

        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;

    private: 
        void Place_bomb(void);

        bool bomb_enable;
        int bomb_num;
        int grid_width;
        int grid_height;
};

#endif