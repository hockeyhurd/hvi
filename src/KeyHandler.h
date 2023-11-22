/**
 * @author hockeyhurd
 * @version 2023-11-02
 */

#pragma once

#ifndef INC_HVI_KEY_HANDLER_H
#define INC_HVI_KEY_HANDLER_H

#include <hclib/Types.h>

#include <SFML/Window/Keyboard.hpp>

namespace hvi
{
using namespace hclib;

class Window;

class KeyHandler
{
public:

    KeyHandler() noexcept;
    KeyHandler(const KeyHandler&) = delete;
    KeyHandler(KeyHandler&&) noexcept = delete;
    ~KeyHandler() = default;

    KeyHandler& operator= (const KeyHandler&) = delete;
    KeyHandler& operator= (KeyHandler&&) noexcept = delete;

    void init(Window* window);

private:

    bool onCharInput(sf::Keyboard::Key value, bool pressed);
    bool onShiftInput(sf::Keyboard::Key value, bool pressed);
    char fromKey(const sf::Keyboard::Key value) noexcept;

private:

    bool wasInit;
    char shiftEnable;
    Window* window;
};
}

#endif //!INC_HVI_KEY_HANDLER_H

