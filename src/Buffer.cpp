/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#include "Buffer.h"
#include "FontManager.h"

#include <hclib/File.h>
#include <hclib/Logger.h>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iterator>

namespace hvi
{
    static constexpr std::size_t defaultCapacity = 1024;

    Buffer::Buffer() : Buffer(defaultCapacity, Buffer::getDefaultName())
    {
    }

    Buffer::Buffer(std::size_t capacity, std::string name) : gapBuffer(Buffer::GAP_SIZE, capacity),
        name(std::move(name)), dirty(true), text()
    {
        const FontManager& fontMan = FontManager::instance();
        const auto fontPtr = fontMan.find(EnumFont::COURIER_REGULAR);

        if (fontPtr == nullptr)
        {
            throw std::runtime_error("Failed to load 'COURIER_REGULAR' font");
        }

        text.setFont(*fontPtr);
        text.setFillColor(sf::Color::Green);
    }

    std::string& Buffer::getName() noexcept
    {
        return name;
    }

    const std::string& Buffer::getName() const noexcept
    {
        return name;
    }

    /* static */
    const std::string& Buffer::getDefaultName()
    {
        static const std::string defaultName = "No name";
        return defaultName;
    }

    u32 Buffer::getCharacterSize() const
    {
        return static_cast<u32>(text.getCharacterSize());
    }

    /* static */
    Buffer* Buffer::staticLoad(const std::string& filepath)
    {
        auto& logger = Logger::stdlogger();
        Buffer* buffer = nullptr;

        if (filepath.empty())
        {
            return buffer;
        }

        buffer = new Buffer();

        try
        {
            buffer->load(filepath);
        }

        catch (const std::runtime_error& e)
        {
            std::ostringstream os;
            os << "Caught an exception while loading the current Window (" << e.what() << ").";
            logger.write(LogLevel::ERROR, os.str());
            logger.endl();

            delete buffer;
            buffer = nullptr;
        }

        return buffer;
    }

    void Buffer::load(const std::string& filepath)
    {
        File file(filepath, File::EnumMode::READ);
        const auto fileSize = file.size();
        auto fileContents = file.readFile(fileSize);
        fileContents.pop_back();

        gapBuffer = GapBuffer(Buffer::GAP_SIZE, fileContents);

        const auto pos = std::find(filepath.rbegin(), filepath.rend(), '/');

        if (pos != filepath.rend())
        {
            const auto index = std::distance(filepath.rend() + 1, pos);
            name = filepath.substr(index);
        }

        else
        {
            name = filepath;
        }
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

