//-----------------------------------------------------------------------------
// TmxProperty.cpp
//
// Copyright (c) 2016, Tamir Atias
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
// Author: Tamir Atias
//-----------------------------------------------------------------------------
#include <tinyxml2.h>

#include "TmxProperty.h"

namespace Tmx
{
    Property::Property()
        : type(TMX_PROPERTY_STRING)
    {
    }

    void Property::Parse(const tinyxml2::XMLElement *propertyElem)
    {
        auto typeAttribute = propertyElem->FindAttribute("type");

        if (typeAttribute != nullptr)
        {
            auto typeAsCString = typeAttribute->Value();

            if (strcmp(typeAsCString, "string") == 0)
            {
                type = TMX_PROPERTY_STRING;
            }
            else if (strcmp(typeAsCString, "bool") == 0)
            {
                type = TMX_PROPERTY_BOOL;
            }
            else if (strcmp(typeAsCString, "float") == 0)
            {
                type = TMX_PROPERTY_FLOAT;
            }
            else if (strcmp(typeAsCString, "int") == 0)
            {
                type = TMX_PROPERTY_INT;
            }
            else
            {
                type = TMX_PROPERTY_STRING;
            }
        }
        else
        {
            type = TMX_PROPERTY_STRING;
        }

        auto valueAsCString = propertyElem->Attribute("value");
        if (valueAsCString)
        {
            value = valueAsCString;
        }
        else
        {
            // The value of properties that contain newlines is stored in the element text.
            valueAsCString = propertyElem->GetText();
            value = valueAsCString ? valueAsCString : std::string(); 
        }
    }
}
