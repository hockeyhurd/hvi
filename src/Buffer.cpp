/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#include "Buffer.h"
#include "FontManager.h"

#include <hclib/File.h>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace hvi
{
    Buffer::Buffer(std::size_t capacity) : gapBuffer(Buffer::GAP_SIZE, capacity),
        dirty(true), text()
    {
        FontManager& fontMan = FontManager::instance();
        const auto fontPtr = fontMan.find(EnumFont::COURIER_REGULAR);

        if (fontPtr == nullptr)
        {
            throw std::runtime_error("Failed to load 'COURIER_REGULAR' font");
        }

        text.setFont(*fontPtr);
        text.setFillColor(sf::Color::Green);
    }

    u32 Buffer::getCharacterSize() const
    {
        return static_cast<u32>(text.getCharacterSize());
    }

    void Buffer::load(const std::string& filepath)
    {
        File file(filepath, File::EnumMode::READ);
        const auto fileSize = file.size();
        auto fileContents = file.readFile(fileSize);
        fileContents.pop_back();

        gapBuffer = GapBuffer(Buffer::GAP_SIZE, fileContents);
    }

    void Buffer::save(const std::string& filepath) const
    {
        File file(filepath, File::EnumMode::WRITE);
        const auto* rawBuffer = gapBuffer.data();

        for (std::size_t i = 0; i < gapBuffer.size(); ++i)
        {
            const auto ch = rawBuffer[i];

            if (ch != '\0')
            {
                file.write(ch);
            }
        }
    }

    void Buffer::clear() noexcept
    {
        gapBuffer.clear();
    }

    void Buffer::insert(char ch)
    {
        gapBuffer.insert(ch);
        dirty = true;
    }

    void Buffer::insert(char ch, std::size_t pos)
    {
        gapBuffer.insert(ch, pos);
        dirty = true;
    }

    void Buffer::render(sf::RenderWindow& window) const
    {
        window.draw(text);
    }

    void Buffer::sync()
    {
        if (dirty)
        {
            const std::string tempStr = gapBuffer.toString();
            text.setString(tempStr);
            dirty = false;
        }
    }
}

