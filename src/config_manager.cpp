#include <config_manager.hpp>

conf::ConfigManager::ConfigManager(const std::string& path) : _absolutePath(path)
{
}

const std::string& conf::ConfigManager::GetAbsolutePath() const
{
    return _absolutePath;
}

void conf::ConfigManager::SetAbsolutePath(const std::string& path)
{
    _absolutePath = path;
}

void conf::ConfigManager::TryLoadConfig()
{
    std::ifstream configFile(_absolutePath);

    if (!configFile.is_open()) {
        throw std::runtime_error("Failed to open config file!");
    }

    njson j;
    configFile >> j;

    appName = j.at("appName").get<std::string>();
    winSize = {j.at("winSize").at("x").get<unsigned>(), j.at("winSize").at("y").get<unsigned>()};
    fieldSize = {j.at("fieldSize").at("x").get<unsigned>(), j.at("fieldSize").at("y").get<unsigned>()};
    deadCellColor
            = {j.at("deadCellColor").at("r").get<sf::Uint8>(),
               j.at("deadCellColor").at("g").get<sf::Uint8>(),
               j.at("deadCellColor").at("b").get<sf::Uint8>(),
               j.at("deadCellColor").at("a").get<sf::Uint8>()};
    aliveCellColor
            = {j.at("aliveCellColor").at("r").get<sf::Uint8>(),
               j.at("aliveCellColor").at("g").get<sf::Uint8>(),
               j.at("aliveCellColor").at("b").get<sf::Uint8>(),
               j.at("aliveCellColor").at("a").get<sf::Uint8>()};
    border = j.at("border").get<size_t>();
    fps = j.at("fps").get<unsigned>();
    seed = j.at("seed").get<unsigned>();
}
