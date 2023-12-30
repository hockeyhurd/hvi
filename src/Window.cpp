/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#include "Window.h"

#include <hclib/AsyncLogger.h>

#include <SFML/Window/Event.hpp>

#include <iostream>

namespace hvi
{

Window::Window(std::string&& title, const u32 width, const u32 height) : title(std::move(title)),
    width(width), height(height), doExit(false),
    renderWindow(sf::VideoMode(width, height), title.c_str()),
    view(0, 0), currentBuffer(nullptr), cursor(nullptr), cmdBar(nullptr), normalModeHandler(nullptr),
    mode(EnumMode::NORMAL), uiMap()
{
    init();
}

Window::Window(const std::string& title, const u32 width, const u32 height) : title(title),
    width(width), height(height), renderWindow(sf::VideoMode(width, height), title.c_str()),
    currentBuffer(nullptr), cursor(nullptr), cmdBar(nullptr), normalModeHandler(nullptr),
    mode(EnumMode::NORMAL), uiMap()
{
    init();
}

u32 Window::getWidth() const noexcept
{
    return width;
}

u32 Window::getHeight() const noexcept
{
    return height;
}

EnumMode Window::getMode() const noexcept
{
    return mode;
}

void Window::setMode(const EnumMode mode) noexcept
{
    this->mode = mode;
}

Buffer* Window::getCurrentBuffer() noexcept
{
    return currentBuffer;
}

const Buffer* Window::getCurrentBuffer() const noexcept
{
    return currentBuffer;
}

UserInput* Window::getCurrentUserInput()
{
    auto findResult = uiMap.find(mode);
    return findResult != uiMap.end() ? &findResult->second : nullptr;
}

void Window::launch()
{
    [[maybe_unused]]
    static AsyncLogger& logger = AsyncLogger::stdlogger();
    const std::string filepath = "file.txt";

    currentBuffer = Buffer::staticLoad(filepath);
    buffers.push_back(std::unique_ptr<Buffer>(currentBuffer));

    cursor = std::make_unique<Cursor>(*this, currentBuffer->getCharacterSize());
    cmdBar = std::make_unique<CommandBar>(*this, currentBuffer->getCharacterSize(), true);
    normalModeHandler = std::make_unique<NormalModeHandler>(*this);

    while (renderWindow.isOpen() && !doExit)
    {
        sf::Event event;
        while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                renderWindow.close();
                exit();
            }
        }

#if 0
        while (ups.counter > ups.updates)
        {
            ups.counter -= ups.updates;
            update();
        }
#else
        const auto deltaTime = static_cast<f32>(ups.clock.getElapsedTime().asSeconds());
        update(deltaTime);
#endif

        renderWindow.clear(sf::Color::Black);

        render();
        renderWindow.display();

        ups.counter += ups.clock.restart();
    }
}

std::optional<std::size_t> Window::resolvePositionInBufferFromCursor() const
{
    // TODO: We are going with a really dumb way to find out the current position
    // by counting the number of lines into the file we are.  In a future update,
    // we will try to be a little smarter with this.
    static const std::string lineDelim = "\n";
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);

    const std::size_t row = cursor->getRow();
    std::size_t curRow = 0;
    std::size_t pos = 0;

    do
    {
        pos = currentBuffer->search(lineDelim, pos);

        if (pos == npos)
        {
            return std::nullopt;
        }

        ++curRow;
    }
    while (curRow < row);

    return pos == npos ? std::nullopt : std::make_optional<std::size_t>(pos);
}

void Window::exit(const u32 exitCode)
{
    std::cout << "Game exiting!\n";
    std::cout << "Exit code: " << exitCode << std::endl;

    renderWindow.close();
}

void Window::prepareExit()
{
    doExit = true;
}

void Window::registerHandler(const EnumMode mode, const sf::Keyboard::Key key,
                             UserInput::Handler handler, const bool debounce)
{
    auto findResult = uiMap.find(mode);

    if (findResult != uiMap.end())
    {
        auto& userInput = findResult->second;
        userInput.registerHandler(key, handler, debounce);
    }
}

void Window::init()
{
    buffers.reserve(8);

    uiMap.emplace(EnumMode::CMD, UserInput());
    uiMap.emplace(EnumMode::INSERT, UserInput());
    uiMap.emplace(EnumMode::NORMAL, UserInput());
    uiMap.emplace(EnumMode::VISUAL, UserInput());
}

void Window::update(const f32 deltaTime)
{
    auto* userInput = getCurrentUserInput();
    userInput->update(deltaTime);

    cursor->update(deltaTime);
    cmdBar->update(deltaTime);
}

void Window::render()
{
    if (currentBuffer != nullptr)
    {
        currentBuffer->sync();
        currentBuffer->render(renderWindow);
    }

    cursor->render(renderWindow);
    cmdBar->render(renderWindow);
}

}

