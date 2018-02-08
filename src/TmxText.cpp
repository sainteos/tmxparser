//-----------------------------------------------------------------------------
// TmxText.cpp
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
#include "TmxText.h"
#include <tinyxml2.h>
#include <cstdlib>


namespace Tmx
{
    Text::Text()
    : font_family("sans-serif"), pixel_size(16), wrap(false), color(nullptr), bold(false),
      italic(false), underline(false), strikeout(false), kerning(true),
      horizontal_alignment(LEFT), vertical_alignment(TOP)
    {
    }

    Text::~Text()
    {
      if(color)
      {
          delete color;
          color = nullptr;
      }
    }

    void Text::Parse(const tinyxml2::XMLNode *textNode)
    {
        auto textElement = textNode->ToElement();

        if(textElement->FindAttribute("fontfamily"))
            font_family = std::string(textElement->Attribute("fontfamily"));
        textElement->QueryIntAttribute("pixelsize", &pixel_size);
        textElement->QueryBoolAttribute("wrap", &wrap);
        textElement->QueryBoolAttribute("bold", &bold);
        textElement->QueryBoolAttribute("italic", &italic);
        textElement->QueryBoolAttribute("underline", &underline);
        textElement->QueryBoolAttribute("strikeout", &strikeout);
        textElement->QueryBoolAttribute("kerning", &kerning);

        if(textElement->FindAttribute("halign")) {
            auto ha_str = std::string(textElement->Attribute("halign"));
            if(ha_str == "left")
                horizontal_alignment = LEFT;
            else if(ha_str == "center")
                horizontal_alignment = HCENTER;
            else if(ha_str == "right")
                horizontal_alignment = RIGHT;
        }

        if(textElement->FindAttribute("valign")) {
            auto va_str = std::string(textElement->Attribute("valign"));
            if(va_str == "top")
                vertical_alignment = TOP;
            else if(va_str == "center")
                vertical_alignment = VCENTER;
            else if(va_str == "bottom")
                vertical_alignment = BOTTOM;
        }

        if(textElement->FindAttribute("color"))
            color = new Color(textElement->Attribute("color"));
    }
}
