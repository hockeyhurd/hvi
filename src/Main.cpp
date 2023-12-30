#include "FontManager.h"
#include "Window.h"
#include "WindowManager.h"

#include <hclib/AsyncLogger.h>
#include <hclib/Types.h>

#include <memory>

using namespace hclib;
using namespace hvi;

s32 main()
{
    [[maybe_unused]]
    AsyncLogger& logger = AsyncLogger::stdlogger();
    logger.setLevel(LogLevel::DEBUG);

    FontManager& fontMan = FontManager::instance();
    fontMan.load();

    const std::string windowName = "hvi";
    auto window = std::make_shared<Window>(windowName, 1920, 1080);

    WindowManager& wm = WindowManager::instance();
    wm.add(windowName, window);
    wm.setActive(windowName);

    return 0;
}

