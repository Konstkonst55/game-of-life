#include "../include/include.hpp"

std::string GetConfigPath(const std::string& = "config\\config.json");

int main(int argc, char* argv[])
{
    std::string configPath = argc > 1 ? argv[1] : GetConfigPath();
    conf::ConfigManager config(configPath);

    try {
        config.TryLoadConfig();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        sf::RenderWindow window(sf::VideoMode(config.winSize.x, config.winSize.y), config.appName);
        window.setFramerateLimit(config.fps);

        life::GameOfLife game(config.fieldSize, config.seed);
        view::GameView view(game, window, config.border, config.deadCellColor, config.aliveCellColor);

        bool stopped = false;

        while (window.isOpen()) {
            for (auto event = sf::Event{}; window.pollEvent(event);) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::R) {
                        game.InitializeRandomly();
                    }

                    if (event.key.code == sf::Keyboard::Space) {
                        stopped = !stopped;
                    }

                    if (event.key.code == sf::Keyboard::C) {
                        game.Clear();
                    }
                }

                if (event.type == sf::Event::MouseMoved && stopped) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    sf::Vector2f cellPos;

                    try {
                        cellPos = view.WorldToCell(worldPos);
                    } catch (const std::invalid_argument& ia) {
                        std::cerr << "Error: " << ia.what() << std::endl;
                    }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        game.TurnOnCell({static_cast<unsigned>(cellPos.x), static_cast<unsigned>(cellPos.y)});
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        game.TurnOffCell({static_cast<unsigned>(cellPos.x), static_cast<unsigned>(cellPos.y)});
                    }
                }
            }

            window.clear();

            if (!stopped) {
                game.Update();
            }

            view.Render();
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

std::string GetConfigPath(const std::string& relativePath)
{
    auto exePath = std::filesystem::current_path();
    exePath = exePath.parent_path().parent_path();
    std::filesystem::path configDir = exePath / relativePath;

    return configDir.string();
}
