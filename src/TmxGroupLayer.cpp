//-----------------------------------------------------------------------------
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
// DISCLAIMED. IN NO EVENT SHALL TAMIR ATIAS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
#include <tinyxml2.h>
#include <cstdlib>
#include <cassert> //RJCB
#include <cstring>

#include "TmxLayer.h"
#include "TmxGroupLayer.h"
#include "TmxTileLayer.h"
#include "TmxObjectGroup.h"
#include "TmxImageLayer.h"

namespace Tmx {

    GroupLayer::GroupLayer(const Tmx::Map *_map)
        : Layer(_map, std::string(), 0, 0, 0, 0, 1.0f, true, TMX_LAYERTYPE_GROUP_LAYER)
    {
    }

    GroupLayer::~GroupLayer()
    {
      for(auto c : children)
        delete c;
    }

    void GroupLayer::Parse(const tinyxml2::XMLNode *groupLayerNode)
    {
        const tinyxml2::XMLElement *groupLayerElem = groupLayerNode->ToElement();

        // Read all the attributes into local variables.
        name = groupLayerElem->Attribute("name");

        groupLayerElem->QueryIntAttribute("x", &x);
        groupLayerElem->QueryIntAttribute("y", &y);

        groupLayerElem->QueryIntAttribute("offsetx", &offsetX);
        groupLayerElem->QueryIntAttribute("offsety", &offsetY);

        groupLayerElem->QueryFloatAttribute("opacity", &opacity);
        groupLayerElem->QueryBoolAttribute("visible", &visible);

        // Parse the group.
        const tinyxml2::XMLNode *child = groupLayerElem->FirstChild();
        assert(child); //RJCB

        while(child != nullptr) {
            if(strncmp(child->Value(), "group", 5) == 0) {
                auto groupLayer = new GroupLayer(map);
                groupLayer->Parse(child);
                AddChild(groupLayer);
            }
            else if(strncmp(child->Value(), "layer", 5) == 0) {
                auto tileLayer = new TileLayer(map);
                tileLayer->Parse(child);
                AddChild(tileLayer);
            }
            else if(strncmp(child->Value(), "objectgroup", 11) == 0) {
                auto objectGroup = new ObjectGroup(map);
                objectGroup->Parse(child);
                AddChild(objectGroup);
            }
            else if(strncmp(child->Value(), "imagelayer", 10) == 0) {
                auto imageLayer = new ImageLayer(map);
                imageLayer->Parse(child);
                AddChild(imageLayer);
            }
            child = child->NextSiblingElement();
        }

        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = groupLayerElem->FirstChildElement("properties");

        if (propertiesNode)
        {
            properties.Parse(propertiesNode);
        }
    }

    void GroupLayer::AddChild(Tmx::Layer* childLayer)
    {
        children.push_back(childLayer);
    }

    Tmx::Layer* GroupLayer::GetChild(const int index) const {
      return children.at(index);
    }

    const std::vector<Tmx::Layer*> GroupLayer::GetChildren() const noexcept
    {
        return children;
    }

    int GroupLayer::GetNumChildren() const noexcept {
        return children.size();
    }

    void GroupLayer::SetOffset(const int offsetX, const int offsetY)
    {
        this->offsetX = offsetX;
        this->offsetY = offsetY;
    }

    int GroupLayer::GetOffsetX() const noexcept
    {
        return offsetX;
    }

    int GroupLayer::GetOffsetY() const noexcept
    {
        return offsetY;
    }
}
