
#include <cmath>
#include "bomb_matrix.h"
#include "SDL.h"

Bomb_matrix::Bomb_matrix( int grid_width, int grid_height, int bomb_num)
        :   grid_width(grid_width), 
            grid_height(grid_height), 
            bomb_num(bomb_num),
            engine(dev()),
            random_w(0, static_cast<int>(grid_width)-1),
            random_h(0, static_cast<int>(grid_height)-1)
        {
            std::cout << " User constructor is called" << "\n";
            Place_bomb();
        }
        
void Bomb_matrix::Place_bomb(void){
    SDL_Point pos;
    if (bomb_num>0) {
        bomb_enable = true; 
        std::cout << " bomb enable is true " <<"\n";
    }
    else {
        bomb_enable = false; 
        std::cout << " bomb enable is false " <<"\n";
    }
    if (bomb_enable){
        // creating bomb_matrix by random position within the grid
        std::cout << " bomb_number is " << bomb_num <<"\n";
        for (int i = 0; i <bomb_num; i++){
            while(true){    // generate a random pos
                pos.x = random_w(engine);
                pos.y = random_h(engine);        
                if (pos.x != grid_width/2 && pos.y != grid_height/2) break;
            }
            std::cout << "bomb " << i << "(" << pos.x << "," << pos.y << ")" << "\n";
            position.push_back(pos);         
        }
    }
}