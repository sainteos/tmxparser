//-----------------------------------------------------------------------------
// TmxParser_Test.cpp
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
#include "../TmxParser/Tmx.h"
#include <cstdio>

int main() {
	Tmx::Map *map = new Tmx::Map();
	map->ParseFile("./example/example.tmx");

	if (map->HasError()) {
		printf("error code: %d\n", map->GetErrorCode());
		printf("error text: %s\n", map->GetErrorText());

		system("PAUSE");

		return map->GetErrorCode();
	}

	// Iterate through the tilesets.
	for (int i = 0; i < map->GetNumTilesets(); ++i) {
		printf("                                    \n");
		printf("====================================\n");
		printf("Tileset : %02d\n", i);
		printf("====================================\n");

		// Get a tileset.
		const Tmx::Tileset *tileset = map->GetTileset(i);

		// Print tileset information.
		printf("Name: %s\n", tileset->GetName().c_str());
		printf("Margin: %d\n", tileset->GetMargin());
		printf("Spacing: %d\n", tileset->GetSpacing());
		printf("Image Width: %d\n", tileset->GetImage()->GetWidth());
		printf("Image Height: %d\n", tileset->GetImage()->GetHeight());
		printf("Image Source: %s\n", tileset->GetImage()->GetSource().c_str());
		printf("Transparent Color (hex): %s\n", tileset->GetImage()->GetTransparentColor().c_str());

		// Get a tile from the tileset.
		const Tmx::Tile *tile = tileset->GetTile(0);

		// Print the properties of a tile.
		std::map< std::string, std::string > list = tile->GetProperties().GetList();
		std::map< std::string, std::string >::iterator iter;
		for (iter = list.begin(); iter != list.end(); ++iter) {
			printf("%s = %s\n", iter->first.c_str(), iter->second.c_str());
		}
	}

	// Iterate through the layers.
	for (int i = 0; i < map->GetNumLayers(); ++i) {
		printf("                                    \n");
		printf("====================================\n");
		printf("Layer : %02d/%s \n", i, map->GetLayer(i)->GetName().c_str());
		printf("====================================\n");
	
		// Get a layer.
		const Tmx::Layer *layer = map->GetLayer(i);

		for (int x = 0; x < layer->GetWidth(); ++x) {
			for (int y = 0; y < layer->GetHeight(); ++y) {
				// Get a tile global id.
				printf("%03d ", layer->GetTileGid(y, x));

				// Find a tileset for that id.
				const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileGid(x,y));
			}

			printf("\n");
		}
	}

	printf("\n\n");

	// Iterate through all of the object groups.
	for (int i = 0; i < map->GetNumObjectGroups(); ++i) {
		printf("                                    \n");
		printf("====================================\n");
		printf("Object group : %02d\n", i);
		printf("====================================\n");

		// Get an object group.
		const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

		// Iterate through all objects in the object group.
		for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
			// Get an object.
			const Tmx::Object *object = objectGroup->GetObject(j);

			// Print information about the object.
			printf("Object Name: %s\n", object->GetName().c_str());
			printf("Object Position: (%03d, %03d)\n", object->GetX(), object->GetY());
			printf("Object Size: (%03d, %03d)\n", object->GetWidth(), object->GetHeight());
		}
	}

	delete map;

	system("PAUSE");

	return 0;
}