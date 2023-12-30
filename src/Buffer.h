/**
 * @author hockeyhurd
 * @version 2023-10-28
 */

#pragma once

#ifndef INC_HVI_BUFFER_H
#define INC_HVI_BUFFER_H

#include <hclib/Types.h>
#include <hclib/GapBuffer.h>

#include <SFML/Graphics/Text.hpp>

#include <string>

namespace sf
{
    class RenderWindow;
}

namespace hvi
{

using namespace hclib;

class Buffer
{
private:

    Buffer();

public:

    Buffer(std::size_t capacity, std::string name);
    Buffer(const Buffer&) = default;
    Buffer(Buffer&&) noexcept = default;
    ~Buffer() = default;

    Buffer& operator= (const Buffer&) = default;
    Buffer& operator= (Buffer&&) noexcept = default;

    std::string& getName() noexcept;
    const std::string& getName() const noexcept;
    static const std::string& getDefaultName();
    u32 getCharacterSize() const;

    static Buffer* staticLoad(const std::string& filepath);
    void load(const std::string& filepath);
    void save(const std::string& filepath) const;

    void clear() noexcept;
    void insert(char ch);
    void insert(char ch, std::size_t pos);
    void render(sf::RenderWindow& window) const;
    std::size_t search(const std::string& text, std::size_t startPos) const;
    void sync();

private:

    static constexpr std::size_t GAP_SIZE = 32;

    GapBuffer gapBuffer;
    std::string name;
    bool dirty;
    sf::Text text;
};
}

#endif //!INC_HVI_BUFFER_H

