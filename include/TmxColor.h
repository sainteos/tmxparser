//-----------------------------------------------------------------------------
// TmxColor.h
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
#pragma once

#include <string>
#include <cstdint>

namespace Tmx
{
    //-------------------------------------------------------------------------
    /// A class used for storing information about a color.
    //-------------------------------------------------------------------------
    class Color
    {
    public:
        /// Default constructor for a fully transparent black color.
        Color();

        /// Initialize the color with a 32 bit ARGB representation.
        Color(uint32_t color);

        /// Initialize the color with a red, green, blue and optionally alpha values.
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

        /// Initialize a color from a string hexadecimal representation in the format "#AARRGGBB" or "#RRGGBB".
        explicit Color(const std::string& str);

        ~Color();

        /// Default copy constructor.
        Color(const Color&) = default;

        /// Default asignment operator.
        Color& operator=(const Color&) = default;

        /// Check if two colors have the exact same four components.
        bool operator==(const Color& o) { return color == o.color; }

        /// Check if two colors are different.
        bool operator!=(const Color& o) { return color != o.color; }

        /// Get the alpha component of the color.
        uint8_t GetAlpha() const;

        /// Get the red component of the color.
        uint8_t GetRed() const;

        /// Get the green component of the color.
        uint8_t GetGreen() const;

        /// Get the blue component of the color.
        uint8_t GetBlue() const;

        /// Return true if the color is fully transparent (ie alpha value is 0).
        bool IsTransparent() const;
      
        /// Get the 32 bits integer representing the color. The 8 highest bits are for the alpha channel, then the red, the green and the blue.
        uint32_t ToInt() const { return color; }

        /// Get a string representation of the color in the format "#AARRGGBB".
        std::string ToString() const;

    private:
        uint32_t color;
    };
}
