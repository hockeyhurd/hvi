/**
 * @author hockeyhurd
 * @version 1823-10-28
 */

#include "Cursor.h"
#include "Enums.h"
#include "UserInput.h"
#include "Window.h"

#include <hclib/Logger.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

namespace hvi
{
    /* static */
    const sf::Color Cursor::normColor(0xFFFFFFBF);
    /* static */
    const sf::Color Cursor::blinkColor(0xFFFFFF00);

    Cursor::Cursor(Window& window, const u32 characterSize) : characterSize(characterSize),
        row(0), col(0), rectShape(), accumulator(0.0F), blinked(false)
    {
        static Logger& logger = Logger::stdlogger();
        logger << "Character size is " << characterSize;
        logger.endl();

        updatePosition();
        // rectShape.setSize(sf::Vector2f(2.0F * characterSize / 3.0F, characterSize));
        rectShape.setSize(sf::Vector2f(18, characterSize));
        rectShape.setFillColor(Cursor::normColor);

        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::Down, std::bind(&Cursor::handleDownKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::J, std::bind(&Cursor::handleDownKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::Up, std::bind(&Cursor::handleUpKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::K, std::bind(&Cursor::handleUpKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::Left, std::bind(&Cursor::handleLeftKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::H, std::bind(&Cursor::handleLeftKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::Right, std::bind(&Cursor::handleRightKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::L, std::bind(&Cursor::handleRightKeyPressed, this, std::placeholders::_1, std::placeholders::_2), true);
    }

    std::size_t Cursor::getRow() const noexcept
    {
        return row;
    }

    std::size_t Cursor::getCol() const noexcept
    {
        return col;
    }

    void Cursor::update(const f32 deltaTime)
    {
        constexpr f32 threshold = 0.025F;
        accumulator += deltaTime;

#if 0
        logger << "Accumulator is " << accumulator
               << "\ndeltaTime is " << deltaTime;
        logger.endl();
#endif

        if (accumulator >= threshold)
        {
            accumulator = 0.0F;
            blinked = !blinked;

            if (blinked)
            {
                rectShape.setFillColor(Cursor::blinkColor);
            }

            else
            {
                rectShape.setFillColor(Cursor::normColor);
            }
        }
    }

    void Cursor::render(sf::RenderWindow& window) const
    {
        window.draw(rectShape);
    }

    bool Cursor::handleDownKeyPressed(sf::Keyboard::Key, const bool pressed)
    {
        if (pressed && row <= 64)
        {
            ++row;
            updatePosition();
        }

        return true;
    }

    bool Cursor::handleLeftKeyPressed(sf::Keyboard::Key, const bool pressed)
    {
        if (pressed && col > 0)
        {
            --col;
            updatePosition();
        }

        return true;
    }

    bool Cursor::handleRightKeyPressed(sf::Keyboard::Key, const bool pressed)
    {
        if (pressed && col <= 64)
        {
            ++col;
            updatePosition();
        }

        return true;
    }

    bool Cursor::handleUpKeyPressed(sf::Keyboard::Key, const bool pressed)
    {
        if (pressed && row > 0)
        {
            --row;
            updatePosition();
        }

        return true;
    }

    void Cursor::updatePosition()
    {
        // rectShape.setPosition(col * characterSize, row * characterSize);
        rectShape.setPosition(col * 18, row * characterSize + yOffset);
    }
}

