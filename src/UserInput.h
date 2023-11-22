/**
 * @author hockeyhurd
 * @version 2023-10-30
 */

#pragma once

#ifndef INC_HVI_USER_INPUT_H
#define INC_HVI_USER_INPUT_H

#include <hclib/Types.h>

#include <SFML/Window/Keyboard.hpp>

#include <functional>
#include <unordered_map>

namespace hvi
{

using namespace hclib;

class UserInput
{
public:

    using Handler = std::function<bool(sf::Keyboard::Key, bool pressed)>;

public:

    UserInput();
    UserInput(const UserInput&) = delete;
    UserInput(UserInput&&) noexcept = default;
    ~UserInput() = default;

    UserInput& operator= (const UserInput&) = delete;
    UserInput& operator= (UserInput&&) noexcept = default;

    // static UserInput& instance();

    void registerHandler(sf::Keyboard::Key key, UserInput::Handler handler, bool debounce);

    void update(const f32 deltaTime);

    static bool isShiftKeyPressed();

private:

    bool checkForDebounce(const sf::Keyboard::Key key);
    void resetDebounceKey(const sf::Keyboard::Key key);

private:

    std::unordered_map<sf::Keyboard::Key, UserInput::Handler> handlers;
    std::unordered_map<sf::Keyboard::Key, bool> debouncerMap;
};
}

#endif //!INC_HVI_USER_INPUT_H

