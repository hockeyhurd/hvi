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

namespace sf
{
    class RenderWindow;
}

namespace hvi
{

using namespace hclib;

class Buffer
{
public:

    explicit Buffer(std::size_t capacity);
    Buffer(const Buffer&) = default;
    Buffer(Buffer&&) noexcept = default;
    ~Buffer() = default;

    Buffer& operator= (const Buffer&) = default;
    Buffer& operator= (Buffer&&) noexcept = default;

    u32 getCharacterSize() const;

    void load(const std::string& filepath);
    void save(const std::string& filepath) const;

    void clear() noexcept;
    void insert(char ch);
    void insert(char ch, std::size_t pos);
    void render(sf::RenderWindow& window) const;
    void sync();

private:

    static constexpr std::size_t GAP_SIZE = 32;

    GapBuffer gapBuffer;
    bool dirty;
    sf::Text text;
};
}

#endif //!INC_HVI_BUFFER_H

