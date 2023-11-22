/**
 * @author hockeyhurd
 * @version 2023-10-30
 */

#include "WindowManager.h"
#include "Window.h"

namespace hvi
{

WindowManager::WindowManager() : activeWindow(nullptr), windowMap()
{
}

/* static */
WindowManager& WindowManager::instance()
{
    static WindowManager inst;
    return inst;
}

std::shared_ptr<Window> WindowManager::getActiveWindow()
{
    return activeWindow;
}

const std::shared_ptr<Window> WindowManager::getActiveWindow() const
{
    return activeWindow;
}

void WindowManager::add(const std::string& windowName, std::shared_ptr<Window> window)
{
    auto findResult = windowMap.find(windowName);

    if (findResult == windowMap.end())
    {
        windowMap.emplace(windowName, window);
    }
}

void WindowManager::setActive(const std::string& windowName)
{
    const auto findResult = windowMap.find(windowName);

    if (findResult != windowMap.end())
    {
        if (activeWindow != nullptr)
        {
            activeWindow->exit(0);
        }

        activeWindow = findResult->second;
        activeWindow->launch();
    }
}

}

