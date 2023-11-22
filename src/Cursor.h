/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#pragma once

#ifndef INC_HVI_CURSOR_H
#define INC_HVI_CURSOR_H

#include <hclib/Types.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
    class RenderWindow;
}

namespace hvi
{

using namespace hclib;

class Window;

class Cursor
{
public:

    Cursor(Window& window, const u32 characterSize);
    Cursor(const Cursor&) = default;
    Cursor(Cursor&&) = default;
    ~Cursor() = default;

    Cursor& operator= (const Cursor&) = default;
    Cursor& operator= (Cursor&&) = default;

    std::size_t getRow() const noexcept;
    std::size_t getCol() const noexcept;

    void update(const f32 deltaTime);
    void render(sf::RenderWindow& window) const;

private:

    bool handleDownKeyPressed(sf::Keyboard::Key, const bool pressed);
    bool handleLeftKeyPressed(sf::Keyboard::Key, const bool pressed);
    bool handleRightKeyPressed(sf::Keyboard::Key, const bool pressed);
    bool handleUpKeyPressed(sf::Keyboard::Key, const bool pressed);
    void updatePosition();

private:

    static const sf::Color normColor;
    static const sf::Color blinkColor;
    static constexpr std::size_t yOffset = 2;

    u32 characterSize;
    std::size_t row;
    std::size_t col;
    sf::RectangleShape rectShape;
    f32 accumulator;
    bool blinked;
};
}

#endif //!INC_HVI_CURSOR_H

