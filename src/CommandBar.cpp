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

#include <cassert>

namespace hvi
{
    CommandBar::CommandBar(Window& window, const u32 characterSize, const bool doDraw) :
        characterSize(characterSize), doDraw(doDraw), doDrawText(false), rectShape(), textLabel(),
        textBuffer(), commandMap()
    {
        static Logger& logger = Logger::stdlogger();
        logger << "Character size is " << characterSize;
        logger.endl();

        initCommandMap();

        const f32 barWidth = static_cast<f32>(window.getWidth());
        const f32 barHeight = static_cast<f32>(characterSize * 1.25F);
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

        const FontManager& fontMan = FontManager::instance();
        const auto fontPtr = fontMan.find(EnumFont::COURIER_REGULAR);

        if (fontPtr == nullptr)
        {
            throw std::runtime_error("Failed to load 'COURIER_REGULAR' font");
        }

        textLabel.setFont(*fontPtr);
        textLabel.setFillColor(sf::Color::Black);
        textLabel.setCharacterSize(characterSize);
        textLabel.setPosition(xPos, yPos);

        constexpr std::size_t defaultBufferSize = 1024;
        textBuffer.reserve(defaultBufferSize);

        window.registerHandler(EnumMode::NORMAL, sf::Keyboard::SemiColon,
                               std::bind(&CommandBar::handleEnterCommandMode, this, std::placeholders::_1, std::placeholders::_2),
                               true);

        for (int key = static_cast<int>(sf::Keyboard::A); key <= static_cast<int>(sf::Keyboard::Z); ++key)
        {
            window.registerHandler(EnumMode::CMD, static_cast<sf::Keyboard::Key>(key),
                                   std::bind(&CommandBar::handleCharInput, this, std::placeholders::_1, std::placeholders::_2),
                                   true);
        }

        window.registerHandler(EnumMode::CMD, static_cast<sf::Keyboard::Key>(sf::Keyboard::Enter),
                               std::bind(&CommandBar::handleReturnKey, this, std::placeholders::_1, std::placeholders::_2),
                               true);
        window.registerHandler(EnumMode::CMD, sf::Keyboard::BackSpace,
                std::bind(&CommandBar::handleCharInput, this, std::placeholders::_1, std::placeholders::_2),
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

    void CommandBar::initCommandMap()
    {
        assert(commandMap.empty());

        commandMap.emplace(":q", [](std::string& errorMessage)
        {
            static WindowManager& windowManager = WindowManager::instance();
            std::shared_ptr<Window> window = windowManager.getActiveWindow();
            window->prepareExit();

            return true;
        });

        commandMap.emplace(":w", [](std::string& errorMessage)
        {
            static WindowManager& windowManager = WindowManager::instance();
            std::shared_ptr<Window> window = windowManager.getActiveWindow();
            Buffer* buffer = window->getCurrentBuffer();

            if (buffer == nullptr)
            {
                errorMessage = "No buffer is currently open";
                return false;
            }

            // TODO: For now, only save in the current working directory.
            const std::string filepath = buffer->getName();

            if (filepath != Buffer::getDefaultName())
            {
                buffer->save(filepath);
            }

            return true;
        });
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
            // textLabel.setString(":Hello, CMD mode!");
            textBuffer = ":";
            textLabel.setString(textBuffer);
            doDrawText = true;
        }

        return true;
    }

    bool CommandBar::handleCharInput(sf::Keyboard::Key key, const bool pressed)
    {
        if (!pressed)
        {
            return false;
        }

        if (key == sf::Keyboard::BackSpace)
        {
            if (textBuffer != ":")
            {
                textBuffer.pop_back();
            }

            else
            {
                return true;
            }
        }

        else if (UserInput::isShiftKeyPressed())
        {
            if (key == sf::Keyboard::SemiColon && !textBuffer.empty())
            {
                // Make sure the label is cleared.
                textLabel.setString(textBuffer);
            }

            textBuffer += 'A' + static_cast<char>(key);
        }

        else
        {
            textBuffer += 'a' + static_cast<char>(key);
        }

        textLabel.setString(textBuffer);

        return true;
    }

    bool CommandBar::handleReturnKey(sf::Keyboard::Key key, const bool pressed)
    {
        if (!pressed)
        {
            return false;
        }

        std::string errorMessage;

        if (!executeCommand(errorMessage))
        {
            // throw std::runtime_error(errorMessage);
            textBuffer = errorMessage;
            textLabel.setString(errorMessage);
            return false;
        }

        textBuffer.clear();
        textLabel.setString(textBuffer);

        return true;
    }

    bool CommandBar::executeCommand(std::string& errorMessage)
    {
        static const std::string quitCommand = ":q";
        static WindowManager& windowManager = WindowManager::instance();

        if (textBuffer == quitCommand)
        {
            std::shared_ptr<Window> window = windowManager.getActiveWindow();
            window->prepareExit();

            return true;
        }

        const auto findResult = commandMap.find(textBuffer);

        if (findResult != commandMap.cend())
        {
            return findResult->second(textBuffer);
        }

        errorMessage = "Error: un-recognized command";

        std::shared_ptr<Window> window = windowManager.getActiveWindow();
        window->setMode(EnumMode::NORMAL);

        return false;
    }

}

