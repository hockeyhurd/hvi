/**
 * @author hockeyhurd
 * @version 2023-10-30
 */

#include "UserInput.h"

#include <hclib/Logger.h>

namespace hvi
{

UserInput::UserInput() : handlers()
{
}

#if 0
/* static */
UserInput& UserInput::instance()
{
    static UserInput inst;
    return inst;
}
#endif

void UserInput::registerHandler(sf::Keyboard::Key key, UserInput::Handler handler, bool debounce)
{
    handlers[key] = handler;

    if (debounce)
    {
        debouncerMap[key] = false;
    }
}

bool UserInput::checkForDebounce(const sf::Keyboard::Key key)
{
    [[maybe_unused]]
    static Logger& logger = Logger::stdlogger();

    bool result = true;
    auto findResult = debouncerMap.find(key);

    if (findResult != debouncerMap.end())
    {
        // If false, return true.  If already true, return false.
        result = !findResult->second;
        findResult->second = true;
    }

#if 0
    if (logger.getLevel() == LogLevel::DEBUG)
    {
        logger.write(LogLevel::DEBUG, "UserInput::checkForDebounce called, result is ");
        logger.write(LogLevel::DEBUG, result);
        logger.endl();
    }
#endif

    return result;
}

void UserInput::resetDebounceKey(const sf::Keyboard::Key key)
{
    auto findResult = debouncerMap.find(key);

    if (findResult != debouncerMap.end())
    {
        findResult->second = false;
    }
}

void UserInput::update(const f32 deltaTime)
{
    for (const auto& [key, handler] : handlers)
    {
        if (sf::Keyboard::isKeyPressed(key))
        {
            if (checkForDebounce(key))
            {
                handler(key, true);
            }
        }

        else
        {
            resetDebounceKey(key);
            handler(key, false);
        }
    }
}

/* static */
bool UserInput::isShiftKeyPressed()
{
    const bool result = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
    return result;
}

}

