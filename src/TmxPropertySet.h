//-----------------------------------------------------------------------------
// TmxPropertySet.h
//
// Copyright (c) 2010-2014, Tamir Atias
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

#include <unordered_map>
#include <map>
#include <string>

#include "TmxProperty.h"

namespace tinyxml2 {
    class XMLNode;
}

namespace Tmx
{
    class Property;

    //-----------------------------------------------------------------------------
    // This class contains a map of properties.
    //-----------------------------------------------------------------------------
    class PropertySet
    {
    public:
        PropertySet();
        ~PropertySet();

        // Parse a node containing all the property nodes.
        void Parse(const tinyxml2::XMLNode *propertiesNode);

        // Get a int property.
        int GetIntProperty(const std::string &name, int defaultValue = 0) const;
        // Get a float property.
        float GetFloatProperty(const std::string &name, float defaultValue = 0.0f) const;
        // Get a string property.
        std::string GetStringProperty(const std::string &name, std::string defaultValue = "") const;
        // Get a string property.
        bool GetBoolProperty(const std::string &name, bool defaultValue = false) const;

        // Returns the amount of properties.
        int GetSize() const { return properties.size(); }

        // Checks if a property exists in the set.
        bool HasProperty( const std::string& name ) const;

        // Returns the unordered map of properties.
        const std::unordered_map< std::string, Property > &GetPropertyMap() const
        { return properties; }

        // Returns the STL map of the properties.
        // Deprecated, please use GetPropertyMap() instead.
        std::map< std::string, std::string > GetList() const;

        // Returns whether there are no properties.
        bool Empty() const { return properties.empty(); }

    private:
        std::unordered_map< std::string, Property > properties;

    };
}
