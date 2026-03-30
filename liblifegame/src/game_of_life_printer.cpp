#include <game_of_life_printer.hpp>

#include <iostream>

void life::Print(const GameOfLife& game)
{
    for (const auto& row : game.GetField()) {
        for (const auto& cell : row) {
            std::cout << (cell ? "x" : "o");
        }

        std::cout << std::endl;
    }
}
