//-----------------------------------------------------------------------------
// TmxPropertySet.cpp
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
#include <tinyxml2.h>
#include <cstdlib>

#include "TmxPropertySet.h"

using std::string;
using std::map;

namespace Tmx
{

    PropertySet::PropertySet() : properties()
    {}

    PropertySet::~PropertySet()
    {
        properties.clear();
    }

    void PropertySet::Parse(const tinyxml2::XMLNode *propertiesNode)
    {
        // Iterate through all of the property nodes.
        const tinyxml2::XMLNode *propertyNode = propertiesNode->FirstChildElement("property");

        while (propertyNode)
        {
            const tinyxml2::XMLElement* propertyElem = propertyNode->ToElement();

            auto nameAttrib = propertyElem->FindAttribute("name");

            if (nameAttrib == nullptr || nameAttrib->Value()[0] == 0)
            {
                propertyNode = propertyNode->NextSiblingElement("property");
                continue;
            }

            // Read the attributes of the property and add it to the map
            Property property;
            property.Parse(propertyElem);
            properties[nameAttrib->Value()] = property;

            //propertyNode = propertiesNode->IterateChildren("property", propertyNode); FIXME MAYBE
            propertyNode = propertyNode->NextSiblingElement("property");
        }
    }

    string PropertySet::GetStringProperty(const string &name, string defaultValue) const
    {
        std::unordered_map< string, Property >::const_iterator iter = properties.find(name);

        if (iter == properties.end())
            return defaultValue;

        return iter->second.GetValue();
    }

    int PropertySet::GetIntProperty(const string &name, int defaultValue) const
    {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty())
            return defaultValue;

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return std::stoi(iter->second.GetValue());
    }

    float PropertySet::GetFloatProperty(const string &name, float defaultValue) const
    {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty())
            return defaultValue;

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return std::stof(iter->second.GetValue());
    }

    bool PropertySet::GetBoolProperty(const string &name, bool defaultValue) const
    {
        auto iter = properties.find(name);

        if (iter == properties.end() || iter->second.IsValueEmpty())
            return defaultValue;

        // Note that we convert the value here ourselves in order to maintain
        // compatibility with older versions of the TMX spec.
        return iter->second.GetValue().compare("true") == 0;
    }

    bool PropertySet::HasProperty( const string& name ) const
    {
        if( properties.empty() ) return false;
        return ( properties.find(name) != properties.end() );
    }

    std::map< std::string, std::string > PropertySet::GetList() const
    {
        std::map< std::string, std::string > orderedProperties;
        for (auto &pair : properties)
        {
            auto &property = pair.second;
            orderedProperties[pair.first] = property.GetValue();
        }
        return orderedProperties;
    }

}
