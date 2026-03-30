#include <game_of_life.hpp>

#include <algorithm>
#include <random>
#include <stdexcept>

life::GameOfLife::GameOfLife(const life::Pair2uint& size) : GameOfLife(size, 0)
{
}

life::GameOfLife::GameOfLife(const life::Pair2uint& size, unsigned seed)
    : _size(size), _field(size.x, std::vector<bool>(size.y, false)), _seed(seed)
{
    InitializeRandomly();
}

void life::GameOfLife::Initialize(const std::vector<std::vector<bool>>& state)
{
    if (state.size() != _size.x || state.at(0).size() != _size.y) {
        throw std::invalid_argument("The initial state does not match the size of the playing field!");
    }

    _field = state;
}

void life::GameOfLife::InitializeRandomly()
{
    std::mt19937 gen(_seed == 0 ? GenerateSeed() : _seed);
    std::uniform_int_distribution<> dis(0, 1);

    _field.clear();
    _field.resize(_size.x, std::vector<bool>(_size.y));

    for (auto& row : _field) {
        for (auto it = row.begin(); it != row.end(); it++) {
            *it = dis(gen);
        }
    }
}

unsigned life::GameOfLife::GenerateSeed() const
{
    std::random_device rd;
    return rd();
}

const life::Pair2uint& life::GameOfLife::GetSize() const
{
    return _size;
}

const std::vector<std::vector<bool>>& life::GameOfLife::GetField() const
{
    return _field;
}

unsigned life::GameOfLife::GetSeed() const
{
    return _seed;
}

void life::GameOfLife::ToggleCell(const life::Pair2uint& pos)
{
    _field.at(pos.x).at(pos.y) = !_field.at(pos.x).at(pos.y);
}

void life::GameOfLife::TurnOnCell(const life::Pair2uint& pos)
{
    _field.at(pos.x).at(pos.y) = true;
}

void life::GameOfLife::TurnOffCell(const life::Pair2uint& pos)
{
    _field.at(pos.x).at(pos.y) = false;
}

void life::GameOfLife::Clear()
{
    for (auto& row : _field) {
        std::fill(row.begin(), row.end(), false);
    }
}

void life::GameOfLife::Update()
{
    std::vector<std::vector<bool>> tempStates(_size.x, std::vector<bool>(_size.y));

    for (unsigned x = 0; x < _size.x; x++) {
        for (unsigned y = 0; y < _size.y; y++) {
            int liveNeighbors = CountLiveNeighbors(Pair2uint(x, y));
            tempStates.at(x).at(y) = _field.at(x).at(y) ? liveNeighbors == 2 || liveNeighbors == 3 : liveNeighbors == 3;
        }
    }

    _field.swap(tempStates);
}

unsigned life::GameOfLife::CountLiveNeighbors(const life::Pair2uint& point) const
{
    unsigned count = 0;

    for (unsigned x = std::max(0u, point.x - 1); x <= std::min(_size.x - 1, point.x + 1); x++) {
        for (unsigned y = std::max(0u, point.y - 1); y <= std::min(_size.y - 1, point.y + 1); y++) {
            if ((x != point.x || y != point.y) && _field.at(x).at(y)) {
                count++;
            }
        }
    }

    return count;
}
