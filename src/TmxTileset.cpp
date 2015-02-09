//-----------------------------------------------------------------------------
// TmxTileset.cpp
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

#include "TmxTileset.h"
#include "TmxTileOffset.h"
#include "TmxTerrainArray.h"
#include "TmxTerrain.h"
#include "TmxImage.h"
#include "TmxTile.h"
#include "TmxMap.h"

using std::vector;
using std::string;

namespace Tmx 
{
    Tileset::Tileset() 
        : first_gid(0)
        , name()
        , tile_width(0)
        , tile_height(0)
        , margin(0)
        , spacing(0)
        , tileOffset(NULL)
        , image(NULL)
        , tiles()
    {
    }

    Tileset::~Tileset() 
    {
        // Delete the tile offset from memory if allocated.
        if (tileOffset)
        {
            delete tileOffset;
            tileOffset = NULL;
        }

        // Delete the image from memory if allocated.
        if (image)
        {
            delete image;
            image = NULL;
        }

        // Iterate through all of the terrain types in the tileset and delete each of them.
        vector< Terrain* >::iterator ttIter;
        for (ttIter = terrainTypes.begin(); ttIter != terrainTypes.end(); ++ttIter) 
        {
            Terrain *terrainType = (*ttIter);
            
            if (terrainType) 
            {
                delete terrainType;
                terrainType = NULL;
            }
        }

        // Iterate through all of the tiles in the tileset and delete each of them.
        vector< Tile* >::iterator tIter;
        for (tIter = tiles.begin(); tIter != tiles.end(); ++tIter) 
        {
            Tile *tile = (*tIter);
            
            if (tile) 
            {
                delete tile;
                tile = NULL;
            }
        }
    }

    void Tileset::Parse(const tinyxml2::XMLNode *tilesetNode) 
    {
        const tinyxml2::XMLElement *tilesetElem = tilesetNode->ToElement();

        // Read all the attributes into local variables.
        first_gid = tilesetElem->IntAttribute("firstgid");
        tile_width = tilesetElem->IntAttribute("tilewidth");
        tile_height = tilesetElem->IntAttribute("tileheight");
        margin = tilesetElem->IntAttribute("margin");
        spacing = tilesetElem->IntAttribute("spacing");

        name = tilesetElem->Attribute("name");

        // Parse the tile offset, if it exists.
        const tinyxml2::XMLNode *tileOffsetNode = tilesetNode->FirstChildElement("tileoffset");
        
        if (tileOffsetNode) 
        {
            tileOffset = new TileOffset();
            tileOffset->Parse(tileOffsetNode);
        }

        // Parse the terrain types if any.
        const tinyxml2::XMLNode *terrainTypesNode = tilesetNode->FirstChildElement("terraintypes");
        
        if (terrainTypesNode) 
        {
            TerrainArray terrainArray;
            terrainArray.Parse(&terrainTypes, terrainTypesNode);
        }

        // Parse the image.
        const tinyxml2::XMLNode *imageNode = tilesetNode->FirstChildElement("image");
        
        if (imageNode) 
        {
            image = new Image();
            image->Parse(imageNode);
        }

        // Populate the tile list
        int tileCount = (image->GetWidth() / tile_width) * (image->GetHeight() / tile_height);

        int tId = tiles.size();
        while (tId < tileCount)
        {
            Tile* tile = new Tile(tId);
            tiles.push_back(tile);
            tId++;
        }


        // Iterate through all of the tile elements and parse each.
        const tinyxml2::XMLNode *tileNode = tilesetNode->FirstChildElement("tile");
        while (tileNode)
        {
            // Parse it to get the tile id.
            Tile tile;
            tile.Parse(tileNode);

            // Using the ID in the temporary tile get the real tile and parse for real.
            tiles[tile.GetId()]->Parse(tileNode);

            //tileNode = tilesetNode->IterateChildren("tile", tileNode); FIXME MAYBE
            tileNode = tileNode->NextSiblingElement("tile");
        }

        
        // Parse the properties if any.
        const tinyxml2::XMLNode *propertiesNode = tilesetNode->FirstChildElement("properties");
        
        if (propertiesNode) 
        {
            properties.Parse(propertiesNode);
        }
    }

    const Tile *Tileset::GetTile(int index) const 
    {
        for (unsigned int i = 0; i < tiles.size(); ++i) 
        {
            if (tiles.at(i)->GetId() == index) 
            {
                return tiles.at(i);
            }
        }

        return NULL;
    }
}
