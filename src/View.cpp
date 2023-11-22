/**
 * @author hockeyhurd
 * @version 2023-11-01
 */

#include "View.h"

namespace hvi
{
    View::View() noexcept : View(0, 0)
    {
    }

    View::View(std::size_t startLine, std::size_t endLine) noexcept : startLine(startLine), endLine(endLine)
    {
    }

#if 0
    // postfix
    View& View::operator++ (s32) noexcept
    {
        ++startLine;
        ++endLine;

        return *this;
    }

    // postfix
    View& View::operator-- (s32) noexcept
    {
        --startLine;
        --endLine;

        return *this;
    }
#endif
}

