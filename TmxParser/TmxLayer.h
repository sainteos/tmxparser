//-----------------------------------------------------------------------------
// TmxLayer.h
//
// Copyright (c) 2010-2011, Tamir Atias
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
#include "TmxPropertySet.h"
#include "TmxMapTile.h"

class TiXmlNode;

namespace Tmx 
{
	//-------------------------------------------------------------------------
	// Type used for the encoding of the layer data.
	//-------------------------------------------------------------------------
	enum LayerEncodingType 
	{
		TMX_ENCODING_XML,
		TMX_ENCODING_BASE64,
		TMX_ENCODING_CSV
	};

	//-------------------------------------------------------------------------
	// Type used for the compression of the layer data.
	//-------------------------------------------------------------------------
	enum LayerCompressionType 
	{
		TMX_COMPRESSION_NONE,
		TMX_COMPRESSION_ZLIB,
		TMX_COMPRESSION_GZIP
	};

	//-------------------------------------------------------------------------
	// Used for storing information about the tile ids for every layer.
	// This class also have a property set.
	//-------------------------------------------------------------------------
	class Layer 
	{
	public:
		Layer();
		~Layer();

		// Parse a layer node.
		void Parse(const TiXmlNode *layerNode);

		// Get the name of the layer.
		const std::string &GetName() const { return name; }

		// Get the width of the layer, in tiles.
		int GetWidth() const { return width; }

		// Get the height of the layer, in tiles.
		int GetHeight() const { return height; }

		// Get the property set.
		const PropertySet &GetProperties() const { return properties; }

		// Pick a specific tile from the list.
		int GetTileGid(int x, int y) const { return tile_map[y * width + x].gid; }

		// Get whether the tile is flipped horizontally.
		bool IsTileFlippedHorizontally(int x, int y) const 
		{ return tile_map[y * width + x].flippedHorizontally; }

		// Get whether the tile is flipped vertically.
		bool IsTileFlippedVertically(int x, int y) const 
		{ return tile_map[y * width + x].flippedVertically; }

		// Get the tile specific to the map.
		MapTile GetTile(int x, int y) const { return tile_map[y * width + x]; }

		// Get the type of encoding that was used for parsing the layer data.
		// See: LayerEncodingType
		LayerEncodingType GetEncoding() const { return encoding; }

		// Get the type of compression that was used for parsing the layer data.
		// See: LayerCompressionType
		LayerCompressionType GetCompression() const { return compression; }

	private:
		void ParseXML(const TiXmlNode *dataNode);
		void ParseBase64(const std::string &innerText);
		void ParseCSV(const std::string &innerText);

		std::string name;
		
		int width;
		int height;
	
		float opacity;
		bool visible;

		PropertySet properties;

		MapTile *tile_map;

		LayerEncodingType encoding;
		LayerCompressionType compression;
	};
};