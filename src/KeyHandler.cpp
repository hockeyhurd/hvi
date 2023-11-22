/**
 * @author hockeyhurd
 * @version 2023-11-02
 */

#include "KeyHandler.h"
#include "UserInput.h"
#include "Window.h"

#include <functional>

namespace hvi
{
    KeyHandler::KeyHandler() noexcept : wasInit(false), shiftEnable('\0'), window(nullptr)
    {
    }

    void KeyHandler::init(Window* window)
    {
        if (wasInit || window == nullptr)
        {
            return;
        }

        // auto* ui = window->getCurrentUI();
        char ch;

        for (ch = 'A'; ch <= 'Z'; ++ch)
        {
            // void registerHandler(sf::Keyboard::Key key, UserInput::Handler handler, bool debounce);
            window->registerHandler(EnumMode::INSERT,
                                    static_cast<sf::Keyboard::Key>(ch),
                                    std::bind(&KeyHandler::onCharInput, this, std::placeholders::_1, std::placeholders::_2),
                                    false);
        }

        window->registerHandler(EnumMode::INSERT,
                                sf::Keyboard::LShift,
                                std::bind(&KeyHandler::onShiftInput, this, std::placeholders::_1, std::placeholders::_2),
                                true);
        window->registerHandler(EnumMode::INSERT,
                                sf::Keyboard::RShift,
                                std::bind(&KeyHandler::onShiftInput, this, std::placeholders::_1, std::placeholders::_2),
                                true);

        wasInit = true;
    }

    bool KeyHandler::onCharInput(sf::Keyboard::Key value, bool pressed)
    {
        const char asChar = fromKey(value);
        Buffer* buffer = window->getCurrentBuffer();
        buffer->insert(asChar);

        return true;
    }

    bool KeyHandler::onShiftInput(sf::Keyboard::Key value, bool pressed)
    {
        shiftEnable = static_cast<char>(~0);
        return true;
    }

    /* static */
    char KeyHandler::fromKey(const sf::Keyboard::Key value) noexcept
    {
        char ch = '\0';

        if (value >= sf::Keyboard::A && value <= sf::Keyboard::Z)
        {
            ch = 'A' + static_cast<char>(value);
            ch |= 0x20 & shiftEnable;
        }

        return ch;
    }
}

