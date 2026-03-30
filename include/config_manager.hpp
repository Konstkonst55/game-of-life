#pragma once

#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <pair_2_uint.hpp>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using njson = nlohmann::json;

namespace conf {
    class ConfigManager {
    private:
        std::string _absolutePath;

    public:
        std::string appName = "Game Of Life";
        sf::Vector2u winSize{400u, 400u};
        life::Pair2uint fieldSize{40u, 40u};
        sf::Color deadCellColor = sf::Color::Black;
        sf::Color aliveCellColor = sf::Color::White;
        size_t border = 10ull;
        unsigned fps = 10u;
        unsigned seed = 0u;

        ConfigManager(const std::string&);

        const std::string& GetAbsolutePath() const;
        void SetAbsolutePath(const std::string&);

        void TryLoadConfig();
    };
}

#endif // !_CONFIG_MANAGER_H_
