//-----------------------------------------------------------------------------
// TmxProperty.h
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
#pragma once

#include <string>

namespace tinyxml2 {
    class XMLElement;
}

namespace Tmx
{
    //-------------------------------------------------------------------------
    // The type of a property.
    //-------------------------------------------------------------------------
    enum PropertyType
    {
        // A string property (default)
        TMX_PROPERTY_STRING,

        // A boolean property
        TMX_PROPERTY_BOOL,

        // An integer property
        TMX_PROPERTY_INT,

        // A floating point property
        TMX_PROPERTY_FLOAT,
    };

    //-------------------------------------------------------------------------
    // Used to store a (typed) property.
    //-------------------------------------------------------------------------
    class Property
    {
    public:
        Property();

        // Parse the property element.
        void Parse(const tinyxml2::XMLElement *propertyElem);

        // Get the type of the property (default: TMX_PROPERTY_STRING)
        PropertyType GetType() const { return type; }

        // Check if the property is of a certain type.
        bool IsOfType(PropertyType type) const { return GetType() == type; }

        // Return the value of the property.
        const std::string &GetValue() const { return value; }

        // Return whether the value is empty or was not specified.
        bool IsValueEmpty() const { return value.empty(); }

        // Convert the value to a boolean and return it (or the default value if not a boolean.)
        bool GetBoolValue(bool defaultValue = false) const;

        // Convert the value to an integer and return it (or the default value if not an integer).
        int GetIntValue(int defaultValue = 0) const;

        // Convert the value to a float and return it (or the default value if not a float).
        float GetFloatValue(float defaultValue = 0.0f) const;

    private:
        PropertyType type;
        std::string value;
    };

    inline bool Property::GetBoolValue(bool defaultValue) const
    {
        if (!IsOfType(TMX_PROPERTY_BOOL))
            return defaultValue;

        return value.compare("true") == 0;
    }

    inline int Property::GetIntValue(int defaultValue) const
    {
        if (!IsOfType(TMX_PROPERTY_INT))
            return defaultValue;

        return std::stoi(value);
    }

    inline float Property::GetFloatValue(float defaultValue) const
    {
        if (!IsOfType(TMX_PROPERTY_FLOAT))
            return defaultValue;

        return std::stof(value);
    }
}
