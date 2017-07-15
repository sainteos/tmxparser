//-----------------------------------------------------------------------------
// TmxColor.cpp
//
// Copyright (c) 2017, Guillaume Bertholon
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Guillaume Bertholon
//-----------------------------------------------------------------------------
#include "TmxColor.h"
#include <cstdio>

namespace Tmx
{
    Color::Color()
        : color(0)
    {
    }

    Color::Color(uint32_t c)
        : color(c)
    {
    }

    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        color = 0;

        color |= a;
        color <<= 8;
        color |= r;
        color <<= 8;
        color |= g;
        color <<= 8;
        color |= b;
    }

    Color::Color(const std::string& str)
    {
        // We skip the first # character and then read directly the hexadecimal value
        color = std::strtol((str.c_str() + 1), nullptr, 16);

        // If the input has the short format #RRGGBB without alpha channel we set it to 255
        if(str.length() == 7) color |= 0xff000000;
    }

    Color::~Color()
    {
    }

    uint8_t Color::GetAlpha() const
    {
        return (color & 0xff000000) >> 24;
    }

    uint8_t Color::GetRed() const
    {
        return (color & 0x00ff0000) >> 16;
    }

    uint8_t Color::GetGreen() const
    {
        return (color & 0x0000ff00) >> 8;
    }

    uint8_t Color::GetBlue() const
    {
        return (color & 0x000000ff);
    }

    std::string Color::ToString() const
    {
        char strRep[10];
        std::sprintf(strRep, "#%.8x", color);
        return std::string(strRep);
    }
}
