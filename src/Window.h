/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#pragma once

#ifndef INC_HVI_WINDOW_H
#define INC_HVI_WINDOW_H

#include "Buffer.h"
#include "CommandBar.h"
#include "Cursor.h"
#include "Enums.h"
#include "NormalModeHandler.h"
#include "UserInput.h"
#include "View.h"

#include <hclib/Types.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <atomic>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#define VSYNC False // True
#define UPDATES_PER_SEC 60u
#define STARTING_LEVEL 0u

#ifndef DELTA_UPS
#define DELTA_UPS 60
#endif // !DELTA_UPS

#ifndef DELTA_TIME
#define DELTA_TIME (1.0f / DELTA_UPS)
#endif // !DELTA_TIME

#if OS_APPLE
#define WINDOW_SCALE 2u
#else
#define WINDOW_SCALE 1u
#endif

using namespace hclib;

namespace hvi
{

class Window
{
public:

    Window(std::string&& title, const u32 width = 640, const u32 height = 480);
    Window(const std::string& title, const u32 width = 640, const u32 height = 480);

    Window(const Window&) = delete;
    Window(Window&&) = delete;

    Window& operator= (const Window&) = delete;
    Window& operator= (Window&&) = delete;
    ~Window() = default;

    u32 getWidth() const noexcept;
    u32 getHeight() const noexcept;
    EnumMode getMode() const noexcept;
    void setMode(const EnumMode mode) noexcept;

    Buffer* getCurrentBuffer() noexcept;
    const Buffer* getCurrentBuffer() const noexcept;
    UserInput* getCurrentUserInput();
    std::optional<std::size_t> resolvePositionInBufferFromCursor() const;

    void launch();
    void exit(const u32 errorCode = 0);
    void prepareExit();

    void registerHandler(const EnumMode mode, const sf::Keyboard::Key key,
                         UserInput::Handler handler, const bool debounce);

private:

    void init();
    void update(const f32 deltaTime);
    void render();

private:

    struct UPS
    {
        sf::Clock clock;
        sf::Time counter = sf::Time::Zero;
        // sf::Time updates = sf::seconds(1.0f / 20.0f);
        sf::Time updates = sf::seconds(1.0f / UPDATES_PER_SEC);
    };

    std::string title;
    u32 width;
    u32 height;
    std::atomic_bool doExit;

    sf::RenderWindow renderWindow;
    UPS ups;

    View view;
    Buffer* currentBuffer;
    std::vector<std::unique_ptr<Buffer>> buffers;
    std::unique_ptr<Cursor> cursor;
    std::unique_ptr<CommandBar> cmdBar;
    std::unique_ptr<NormalModeHandler> normalModeHandler;

    EnumMode mode;
    std::unordered_map<EnumMode, UserInput> uiMap;
};
}

#endif //INC_HVI_WINDOW_H

