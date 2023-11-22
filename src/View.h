/**
 * @author hockeyhurd
 * @version 2023-11-01
 */

#pragma once

#ifndef INC_HVI_VIEW_H
#define INC_HVI_VIEW_H

#include <hclib/Types.h>

namespace hvi
{

using namespace hclib;

class View
{
public:

    View() noexcept;
    View(std::size_t startLine, std::size_t endLine) noexcept;
    View(const View&) noexcept = default;
    View(View&&) noexcept = default;
    ~View() = default;

    View& operator= (const View&) noexcept = default;
    View& operator= (View&&) noexcept = default;

    // inline std::size_t getStartLine() const noexcept { return startLine; }
    // inline void setStartLine(std::size_t startLine) noexcept { this->startLine = startLine; }
    // inline std::size_t getEndLine() const noexcept { return endLine; }
    // inline void setEndLine(std::size_t endLine) noexcept { this->endLine = endLine; }

    // prefix
    // View& operator++ () noexcept;
    // postfix
    // View& operator++ (s32) noexcept;
    // prefix
    // View& operator-- () noexcept;
    // postfix
    // View& operator-- (s32) noexcept;

// private:

    std::size_t startLine;
    std::size_t endLine;
};
}

#endif //!INC_HVI_VIEW_H

