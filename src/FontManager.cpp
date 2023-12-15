/**
 * @author hockeyhurd
 * @version 2023-11-21
 */

#include "FontManager.h"

namespace hvi
{
    FontManager::FontManager() : loaded(false), fontMap()
    {
    }

    /* static */
    FontManager& FontManager::instance()
    {
        static FontManager inst;
        return inst;
    }

    bool FontManager::isLoaded() const noexcept
    {
        return loaded;
    }

    const std::shared_ptr<sf::Font> FontManager::find(const EnumFont font) const
    {
        if (!loaded)
        {
            return nullptr;
        }

        const auto findResult = fontMap.find(font);
        return findResult != fontMap.cend() ? findResult->second : nullptr;
    }

    void FontManager::load()
    {
        if (loaded)
        {
            return;
        }

        auto font = std::make_shared<sf::Font>();
        font->loadFromFile("arial.ttf");
        fontMap.emplace(EnumFont::ARIAL, font);

        font = std::make_shared<sf::Font>();
        font->loadFromFile("Courier Regular.ttf");
        fontMap.emplace(EnumFont::COURIER_REGULAR, font);

        loaded = true;
    }
}

