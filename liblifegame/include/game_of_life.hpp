#pragma once

#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <pair_2_uint.hpp>
#include <vector>

namespace life {
    class GameOfLife {
    private:
        const Pair2uint& _size;
        std::vector<std::vector<bool>> _field;
        const unsigned _seed;

    public:
        GameOfLife(const Pair2uint&);
        GameOfLife(const Pair2uint&, unsigned);

        void Initialize(const std::vector<std::vector<bool>>&);
        void InitializeRandomly();
        unsigned GenerateSeed() const;

        const Pair2uint& GetSize() const;
        const std::vector<std::vector<bool>>& GetField() const;
        unsigned GetSeed() const;

        void ToggleCell(const Pair2uint&);
        void TurnOnCell(const Pair2uint&);
        void TurnOffCell(const Pair2uint&);

        void Clear();

        void Update();
        unsigned CountLiveNeighbors(const Pair2uint&) const;
    };
}

#endif // !_GAME_OF_LIFE_H_
