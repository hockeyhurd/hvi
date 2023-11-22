/**
 * @author hockeyhurd
 * @version 2023-11-21
 */

#pragma once

#ifndef INC_HVI_FONT_MANAGER_H
#define INC_HVI_FONT_MANAGER_H

#include "Enums.h"

#include <hclib/Types.h>

#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <unordered_map>

namespace hvi
{

using namespace hclib;

class Window;

class FontManager
{
private:

    FontManager();

public:

    FontManager(const FontManager&) = delete;
    FontManager(FontManager&&) = default;
    ~FontManager() = default;

    FontManager& operator= (const FontManager&) = delete;
    FontManager& operator= (FontManager&&) = default;

    static FontManager& instance();

    const std::shared_ptr<sf::Font> find(const EnumFont font) const;
    void load();

private:

private:

    bool loaded;
    std::unordered_map<EnumFont, std::shared_ptr<sf::Font>> fontMap;

};
}

#endif //!INC_HVI_FONT_MANAGER_H

