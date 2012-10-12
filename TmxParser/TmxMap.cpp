//-----------------------------------------------------------------------------
// TmxMap.cpp
//
// Copyright (c) 2010-2012, Tamir Atias
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
#include <tinyxml.h>
#include <stdio.h>

#include "TmxMap.h"
#include "TmxTileset.h"
#include "TmxLayer.h"
#include "TmxObjectGroup.h"

using std::vector;
using std::string;

namespace Tmx 
{
	Map::Map() 
		: file_name()
		, file_path()
		, version(0.0)
		, orientation(TMX_MO_ORTHOGONAL)
		, width(0)
		, height(0)
		, tile_width(0)
		, tile_height(0)
		, layers()
		, object_groups()
		, tilesets() 
		, has_error(false)
		, error_code(0)
		, error_text()
	{}

	Map::~Map() 
	{
		// Iterate through all of the object groups and delete each of them.
		vector< ObjectGroup* >::iterator ogIter;
		for (ogIter = object_groups.begin(); ogIter != object_groups.end(); ++ogIter) 
		{
			ObjectGroup *objectGroup = (*ogIter);
			
			if (objectGroup)
			{
				delete objectGroup;
				objectGroup = NULL;
			}
		}

		// Iterate through all of the layers and delete each of them.
		vector< Layer* >::iterator lIter;
		for (lIter = layers.begin(); lIter != layers.end(); ++lIter) 
		{
			Layer *layer = (*lIter);

			if (layer) 
			{
				delete layer;
				layer = NULL;
			}
		}

		// Iterate through all of the tilesets and delete each of them.
		vector< Tileset* >::iterator tsIter;
		for (tsIter = tilesets.begin(); tsIter != tilesets.end(); ++tsIter) 
		{
			Tileset *tileset = (*tsIter);
			
			if (tileset) 
			{
				delete tileset;
				tileset = NULL;
			}
		}
	}

	void Map::ParseFile(const string &fileName) 
	{
		file_name = fileName;

		int lastSlash = fileName.find_last_of("/");

		// Get the directory of the file using substring.
		if (lastSlash > 0) 
		{
			file_path = fileName.substr(0, lastSlash + 1);
		} 
		else 
		{
			file_path = "";
		}

		char* fileText;
		int fileSize;

		// Open the file for reading.
		FILE *file = fopen(fileName.c_str(), "rb");

		// Check if the file could not be opened.
		if (!file) 
		{
			has_error = true;
			error_code = TMX_COULDNT_OPEN;
			error_text = "Could not open the file.";
			return;
		}
		
		// Find out the file size.
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		
		// Check if the file size is valid.
		if (fileSize <= 0)
		{
			has_error = true;
			error_code = TMX_INVALID_FILE_SIZE;
			error_text = "The size of the file is invalid.";
			return;
		}

		// Allocate memory for the file and read it into the memory.
		fileText = new char[fileSize];
		fread(fileText, 1, fileSize, file);

		fclose(file);

		// Copy the contents into a C++ string and delete it from memory.
		std::string text(fileText, fileText+fileSize);
		delete [] fileText;

		ParseText(text);		
	}

	void Map::ParseText(const string &text) 
	{
		// Create a tiny xml document and use it to parse the text.
		TiXmlDocument doc;
		doc.Parse(text.c_str());
	
		// Check for parsing errors.
		if (doc.Error()) 
		{
			has_error = true;
			error_code = TMX_PARSING_ERROR;
			error_text = doc.ErrorDesc();
			return;
		}

		TiXmlNode *mapNode = doc.FirstChild("map");
		TiXmlElement* mapElem = mapNode->ToElement();

		// Read the map attributes.
		mapElem->Attribute("version", &version);
		mapElem->Attribute("width", &width);
		mapElem->Attribute("height", &height);
		mapElem->Attribute("tilewidth", &tile_width);
		mapElem->Attribute("tileheight", &tile_height);

		// Read the orientation
		std::string orientationStr = mapElem->Attribute("orientation");

		if (!orientationStr.compare("orthogonal")) 
		{
			orientation = TMX_MO_ORTHOGONAL;
		} 
		else if (!orientationStr.compare("isometric")) 
		{
			orientation = TMX_MO_ISOMETRIC;
		}

		// Read the map properties.
		const TiXmlNode *propertiesNode = mapElem->FirstChild("properties");
		if (propertiesNode) 
		{
			properties.Parse(propertiesNode);
		}

		// Iterate through all of the tileset elements.
		const TiXmlNode *tilesetNode = mapNode->FirstChild("tileset");
		while (tilesetNode) 
		{
			// Allocate a new tileset and parse it.
			Tileset *tileset = new Tileset();
			tileset->Parse(tilesetNode->ToElement());

			// Add the tileset to the list.
			tilesets.push_back(tileset);

			tilesetNode = mapNode->IterateChildren("tileset", tilesetNode);
		}

		// Iterate through all of the layer elements.
		TiXmlNode *layerNode = mapNode->FirstChild("layer");
		while (layerNode) 
		{
			// Allocate a new layer and parse it.
			Layer *layer = new Layer(this);
			layer->Parse(layerNode);

			// Add the layer to the list.
			layers.push_back(layer);

			layerNode = mapNode->IterateChildren("layer", layerNode);
		}

		// Iterate through all of the objectgroup elements.
		TiXmlNode *objectGroupNode = mapNode->FirstChild("objectgroup");
		while (objectGroupNode) 
		{
			// Allocate a new object group and parse it.
			ObjectGroup *objectGroup = new ObjectGroup();
			objectGroup->Parse(objectGroupNode);
		
			// Add the object group to the list.
			object_groups.push_back(objectGroup);

			objectGroupNode = mapNode->IterateChildren("objectgroup", objectGroupNode);
		}
	}

	int Map::FindTilesetIndex(int gid) const
	{
		// Clean up the flags from the gid (thanks marwes91).
		gid &= ~(FlippedHorizontallyFlag | FlippedVerticallyFlag | FlippedDiagonallyFlag);

		for (int i = tilesets.size() - 1; i > -1; --i) 
		{
			// If the gid beyond the tileset gid return its index.
			if (gid >= tilesets[i]->GetFirstGid()) 
			{
				return i;
			}
		}
		
		return -1;
	}

	const Tileset *Map::FindTileset(int gid) const 
	{
		for (int i = tilesets.size() - 1; i > -1; --i) 
		{
			// If the gid beyond the tileset gid return it.
			if (gid >= tilesets[i]->GetFirstGid()) 
			{
				return tilesets[i];
			}
		}
		
		return NULL;
	}
};
