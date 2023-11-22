/**
 * @author hockeyhurd
 * @version 2023-10-30
 */

#pragma once

#ifndef INC_HVI_ENUMS_H
#define INC_HVI_ENUMS_H

#include <hclib/Types.h>

enum class EnumMode
{
    UNKNOWN = 0,
    CMD,
    INSERT,
    NORMAL,
    VISUAL,
};

enum class EnumFont
{
    ARIAL = 0,
    COURIER_REGULAR,
};

#endif //!INC_HVI_ENUMS_H

