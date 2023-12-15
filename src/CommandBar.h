/**
 * @author hockeyhurd
 * @version 2023-11-21
 */

#pragma once

#ifndef INC_HVI_COMMAND_BAR_H
#define INC_HVI_COMMAND_BAR_H

#include <hclib/Types.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <functional>
#include <map>
#include <string>

namespace sf
{
    class RenderWindow;
}

namespace hvi
{

using namespace hclib;

class Window;

class CommandBar
{
public:

    CommandBar(Window& window, const u32 characterSize, const bool doDraw);
    CommandBar(const CommandBar&) = default;
    CommandBar(CommandBar&&) = default;
    ~CommandBar() = default;

    CommandBar& operator= (const CommandBar&) = default;
    CommandBar& operator= (CommandBar&&) = default;

    void update(const f32 deltaTime);
    void render(sf::RenderWindow& window) const;

private:

    void initCommandMap();
    bool handleEnterCommandMode(sf::Keyboard::Key key, const bool pressed);
    bool handleCharInput(sf::Keyboard::Key keyy, const bool pressed);
    bool handleReturnKey(sf::Keyboard::Key key, const bool pressed);
    bool executeCommand(std::string& errorMessage);

private:

    [[maybe_unused]]
    u32 characterSize;
    bool doDraw;
    bool doDrawText;
    sf::RectangleShape rectShape;
    sf::Text textLabel;
    std::string textBuffer;

    std::map<std::string, std::function<bool(std::string&)>> commandMap;
};
}

#endif //!INC_HVI_COMMAND_BAR_H

