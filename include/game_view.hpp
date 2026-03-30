#pragma once

#ifndef _GAME_VIEW_H_
#define _GAME_VIEW_H_

#include <game_of_life.hpp>

#include <SFML/Graphics.hpp>

namespace view {
    class GameView {
    private:
        life::GameOfLife& _game;
        sf::RenderWindow& _window;
        size_t _border;
        sf::Color _deadCellColor = sf::Color::Black;
        sf::Color _aliveCellColor = sf::Color::White;
        sf::Vector2f _cellSize;

        void DrawRectangleCenteredAt(sf::Vector2f, sf::Color);
        void UpdateCellSize();

    public:
        GameView(life::GameOfLife&, sf::RenderWindow&);
        GameView(
                life::GameOfLife&,
                sf::RenderWindow&,
                size_t = 10,
                sf::Color = sf::Color::Black,
                sf::Color = sf::Color::White);

        void SetDeadCellColor(sf::Color);
        void SetAliveCellColor(sf::Color);

        const sf::Vector2f WorldToCell(const sf::Vector2f&) const;

        void Render();
    };
}

#endif // !_GAME_VIEW_H_
