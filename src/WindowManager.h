/**
 * @author hockeyhurd
 * @version 2023-10-30
 */

#pragma once

#ifndef INC_HVI_WINDOW_MANAGER_H
#define INC_HVI_WINDOW_MANAGER_H

#include <hclib/Types.h>

#include <memory>
#include <unordered_map>

using namespace hclib;

namespace hvi
{

class Window;

class WindowManager
{
private:

    WindowManager();

public:

    WindowManager(const WindowManager&) = delete;
    WindowManager(WindowManager&&) = delete;

    WindowManager& operator= (const WindowManager&) = delete;
    WindowManager& operator= (WindowManager&&) = delete;
    ~WindowManager() = default;

    static WindowManager& instance();

    std::shared_ptr<Window> getActiveWindow();
    const std::shared_ptr<Window> getActiveWindow() const;

    void add(const std::string& windowName, std::shared_ptr<Window> window);
    void setActive(const std::string& windowName);

private:

    std::shared_ptr<Window> activeWindow;
    std::unordered_map<std::string, std::shared_ptr<Window>> windowMap;
};
}

#endif //INC_HVI_WINDOW_MANAGER_H

