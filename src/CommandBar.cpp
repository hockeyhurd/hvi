/**
 * @author hockeyhurd
 * @version 2023-11-21
 */

#include "CommandBar.h"
#include "Enums.h"
#include "FontManager.h"
#include "UserInput.h"
#include "Window.h"
#include "WindowManager.h"

#include <hclib/Logger.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <functional>

namespace hvi
{
    CommandBar::CommandBar(Window& window, const u32 characterSize, const bool doDraw) :
        characterSize(characterSize), doDraw(doDraw), doDrawText(false), rectShape(), textLabel()
    {
        static Logger& logger = Logger::stdlogger();
        logger << "Character size is " << characterSize;
        logger.endl();

        const f32 barWidth = static_cast<f32>(window.getWidth());
        const f32 barHeight = static_cast<f32>(characterSize);
        const f32 xPos = 0.0F;
        const f32 yPos = window.getHeight() - barHeight;
        logger << "xPos: " << xPos
               << "\nyPos: " << yPos
               << "\nbarWidth: " << barWidth
               << "\nbarHeight: " << barHeight
               << "\n";
        logger.endl();

        rectShape.setPosition(xPos, yPos);
        rectShape.setSize(sf::Vector2f(barWidth, barHeight));
        rectShape.setFillColor(sf::Color(0x7F7F7FFF));

        FontManager& fontMan = FontManager::instance();
        const auto fontPtr = fontMan.find(EnumFont::COURIER_REGULAR);

        if (fontPtr == nullptr)
        {
            throw std::runtime_error("Failed to load 'COURIER_REGULAR' font");
        }

        textLabel.setFont(*fontPtr);
        textLabel.setFillColor(sf::Color::Black);
        textLabel.setCharacterSize(characterSize);
        textLabel.setPosition(xPos, yPos);

        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::SemiColon,
                               std::bind(&CommandBar::handleEnterCommandMode, this, std::placeholders::_1, std::placeholders::_2),
                               true);
    }

    void CommandBar::update(const f32 deltaTime)
    {
        // TODO: Anything to update??
    }

    void CommandBar::render(sf::RenderWindow& window) const
    {
        if (doDraw)
        {
            window.draw(rectShape);
        }

        if (doDrawText)
        {
            window.draw(textLabel);
        }
    }

    bool CommandBar::handleEnterCommandMode(sf::Keyboard::Key key, const bool pressed)
    {
        if (pressed && UserInput::isShiftKeyPressed())
        {
            static Logger& logger = Logger::stdlogger();
            logger.write(LogLevel::DEBUG, "SemiColon + shift key pressed");
            logger.endl();

            static auto& windowManager = WindowManager::instance();
            auto window = windowManager.getActiveWindow();

            if (window->getMode() != EnumMode::CMD)
            {
                window->setMode(EnumMode::CMD);
            }

            // @@@ test only
            textLabel.setString(":Hello, CMD mode!");
            doDrawText = true;
        }

        return true;
    }

}

