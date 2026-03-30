#include <game_view.hpp>

view::GameView::GameView(life::GameOfLife& game, sf::RenderWindow& window)
    : GameView(game, window, 10, sf::Color::Black, sf::Color::White)
{
}

view::GameView::GameView(
        life::GameOfLife& game,
        sf::RenderWindow& window,
        size_t border,
        sf::Color deadCellColor,
        sf::Color aliveCellColor)
    : _game(game), _window(window), _border(border), _deadCellColor(deadCellColor), _aliveCellColor(aliveCellColor)
{
    UpdateCellSize();
}

void view::GameView::DrawRectangleCenteredAt(sf::Vector2f position, sf::Color color)
{
    sf::RectangleShape rectangle(_cellSize);

    rectangle.setPosition(position.x, position.y);
    rectangle.setFillColor(color);

    _window.draw(rectangle);
}

void view::GameView::UpdateCellSize()
{
    _cellSize
            = {(static_cast<float>(_window.getSize().x) - static_cast<float>(_border * 2))
                       / static_cast<float>(_game.GetSize().x),
               (static_cast<float>(_window.getSize().y) - static_cast<float>(_border * 2))
                       / static_cast<float>(_game.GetSize().y)};
}

void view::GameView::SetDeadCellColor(sf::Color color)
{
    _deadCellColor = color;
}

void view::GameView::SetAliveCellColor(sf::Color color)
{
    _aliveCellColor = color;
}

const sf::Vector2f view::GameView::WorldToCell(const sf::Vector2f& worldPos) const
{
    sf::Vector2f cell(
            (worldPos.x - static_cast<float>(_border)) / _cellSize.x,
            (worldPos.y - static_cast<float>(_border)) / _cellSize.y);

    if (cell.x < static_cast<float>(_game.GetSize().x) && cell.y < static_cast<float>(_game.GetSize().y)) {
        return cell;
    }

    throw std::invalid_argument("The position goes out of bounds!");
}

void view::GameView::Render()
{
    for (unsigned row = 0; row < _game.GetSize().x; row++) {
        for (unsigned col = 0; col < _game.GetSize().y; col++) {
            DrawRectangleCenteredAt(
                    sf::Vector2f(row * _cellSize.x + _border, col * _cellSize.y + _border),
                    _game.GetField().at(row).at(col) ? _aliveCellColor : _deadCellColor);
        }
    }
}
