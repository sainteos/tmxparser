//-----------------------------------------------------------------------------
// TmxText.h
//
// Copyright (c) 2018, Adaleigh Martin
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
// DISCLAIMED. IN NO EVENT SHALL ADALEIGH MARTIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: Adaleigh Martin
//-----------------------------------------------------------------------------
#pragma once

#include <vector>
#include "TmxColor.h"

namespace tinyxml2 {
    class XMLNode;
}

namespace Tmx
{
    //--------------------------------------------------------------------------
    /// Enum to denote Horizontal Alignment of Text
    //--------------------------------------------------------------------------
    enum HorizontalAlignment
    {
      LEFT,
      HCENTER,
      RIGHT
    };

    //--------------------------------------------------------------------------
    /// Enum to denote Vertical Alignment of Text
    //--------------------------------------------------------------------------
    enum VerticalAlignment
    {
      TOP,
      VCENTER,
      BOTTOM
    };

    //-------------------------------------------------------------------------
    /// Class to store an Text of an Object.
    //-------------------------------------------------------------------------
    class Text
    {
    public:
        /// Construct text with the given options.
        Text();
        ~Text();

        std::string GetContents() const noexcept { return contents; }
        std::string GetFontFamily() const noexcept { return font_family; }
        int GetPixelSize() const noexcept { return pixel_size; }
        bool Wraps() const noexcept { return wrap; }
        Color* GetColor() const noexcept { return color; }
        bool IsBold() const noexcept { return bold; }
        bool IsItalic() const noexcept { return italic; }
        bool IsUnderline() const noexcept { return underline; }
        bool IsStrikeout() const noexcept { return strikeout; }
        bool UseKerning() const noexcept { return kerning; }
        HorizontalAlignment GetHorizontalAlignment() const noexcept { return horizontal_alignment; }
        VerticalAlignment GetVerticalAlignment() const noexcept { return vertical_alignment; }

        /// Parse the text node.
        void Parse(const tinyxml2::XMLNode *textNode);

    private:
        std::string contents;
        std::string font_family;
        int pixel_size;
        bool wrap;
        Color* color;
        bool bold;
        bool italic;
        bool underline;
        bool strikeout;
        bool kerning;
        HorizontalAlignment horizontal_alignment;
        VerticalAlignment vertical_alignment;

    };
}
