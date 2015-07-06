//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#include "Tmx.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char * argv[])
{
    Tmx::Map *map = new Tmx::Map();
    std::string fileName = (argc > 1) ? argv[1] : "./example/example.tmx";
    map->ParseFile(fileName);

    if (map->HasError())
    {
        printf("error code: %d\n", map->GetErrorCode());
        printf("error text: %s\n", map->GetErrorText().c_str());

        return map->GetErrorCode();
    }

    printf("====================================\n");
    printf("Map\n");
    printf("====================================\n");

    printf("Version: %1.1f\n", map->GetVersion());
    printf("Orientation: %d\n", map->GetOrientation());
    if (!map->GetBackgroundColor().empty())
        printf("Background Color (hex): %s\n",
               map->GetBackgroundColor().c_str());
    printf("Render Order: %d\n", map->GetRenderOrder());
    if (map->GetStaggerAxis())
        printf("Stagger Axis: %d\n", map->GetStaggerAxis());
    if (map->GetStaggerIndex())
        printf("Stagger Index: %d\n", map->GetStaggerIndex());
    printf("Width: %d\n", map->GetWidth());
    printf("Height: %d\n", map->GetHeight());
    printf("Tile Width: %d\n", map->GetTileWidth());
    printf("Tile Height: %d\n", map->GetTileHeight());

    // Iterate through the tilesets.
    for (int i = 0; i < map->GetNumTilesets(); ++i)
    {
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
        printf("First gid: %d\n", tileset->GetFirstGid());
        printf("Image Width: %d\n", tileset->GetImage()->GetWidth());
        printf("Image Height: %d\n", tileset->GetImage()->GetHeight());
        printf("Image Source: %s\n", tileset->GetImage()->GetSource().c_str());
        if (!tileset->GetImage()->GetTransparentColor().empty())
            printf("Transparent Color (hex): %s\n",
                   tileset->GetImage()->GetTransparentColor().c_str());

        if (tileset->GetTiles().size() > 0)
        {
            // Get a tile from the tileset.
            const Tmx::Tile *tile = *(tileset->GetTiles().begin());

            // Print the properties of a tile.
            std::map<std::string, std::string> list =
                    tile->GetProperties().GetList();
            std::map<std::string, std::string>::iterator iter;
            for (iter = list.begin(); iter != list.end(); ++iter)
            {
                printf("%s = %s\n", iter->first.c_str(), iter->second.c_str());
            }

            if (tile->IsAnimated())
            {
                printf(
                        "Tile is animated: %d frames with total duration of %dms.\n",
                        tile->GetFrameCount(), tile->GetTotalDuration());

                const std::vector<Tmx::AnimationFrame> &frames =
                        tile->GetFrames();

                int i = 0;
                for (std::vector<Tmx::AnimationFrame>::const_iterator it =
                        frames.begin(); it != frames.end(); it++, i++)
                {
                    printf("\tFrame %d: Tile ID = %d, Duration = %dms\n", i,
                            it->GetTileID(), it->GetDuration());
                }
            }

            if(tile->HasObjects())
            {
                printf(
                        "Tile has objects.\n");


                // Iterate through all Collision objects in the tile.
                for (int j = 0; j < tile->GetNumObjects(); ++j)
                {
                    // Get an object.
                    const Tmx::Object *object = tile->GetObject(j);

                    // Print information about the object.
                    printf("Object Name: %s\n", object->GetName().c_str());
                    printf("Object Position: (%03d, %03d)\n", object->GetX(),
                           object->GetY());
                    printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                           object->GetHeight());

                    // Print Polygon points.
                    const Tmx::Polygon *polygon = object->GetPolygon();
                    if (polygon != 0)
                    {
                        for (int i = 0; i < polygon->GetNumPoints(); i++)
                        {
                            const Tmx::Point &point = polygon->GetPoint(i);
                            printf("Object Polygon: Point %d: (%f, %f)\n", i, point.x,
                                   point.y);
                        }
                    }

                    // Print Polyline points.
                    const Tmx::Polyline *polyline = object->GetPolyline();
                    if (polyline != 0)
                    {
                        for (int i = 0; i < polyline->GetNumPoints(); i++)
                        {
                            const Tmx::Point &point = polyline->GetPoint(i);
                            printf("Object Polyline: Point %d: (%f, %f)\n", i, point.x,
                                   point.y);
                        }
                    }
                }

            }
        }
    }

    // Iterate through the tile layers.
    for (int i = 0; i < map->GetNumTileLayers(); ++i)
    {
        printf("                                    \n");
        printf("====================================\n");
        printf("Layer : %02d/%s \n", i, map->GetTileLayer(i)->GetName().c_str());
        printf("====================================\n");

        // Get a layer.
        const Tmx::TileLayer *tileLayer = map->GetTileLayer(i);

        for (int y = 0; y < tileLayer->GetHeight(); ++y)
        {
            for (int x = 0; x < tileLayer->GetWidth(); ++x)
            {
                if (tileLayer->GetTileTilesetIndex(x, y) == -1)
                {
                    printf("........    ");
                }
                else
                {
                    // Get the tile's id and gid.
                    printf("%03d(%03d)", tileLayer->GetTileId(x, y), tileLayer->GetTileGid(x, y));
                
                    // Find a tileset for that id.
                    //const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileId(x, y));
                    if (tileLayer->IsTileFlippedHorizontally(x, y))
                    {
                        printf("h");
                    }
                    else
                    {
                        printf(" ");
                    }
                    if (tileLayer->IsTileFlippedVertically(x, y))
                    {
                        printf("v");
                    }
                    else
                    {
                        printf(" ");
                    }
                    if (tileLayer->IsTileFlippedDiagonally(x, y))
                    {
                        printf("d ");
                    }
                    else
                    {
                        printf("  ");
                    }
                }
            }

            printf("\n");
        }
    }

    printf("\n\n");

    // Iterate through all of the object groups.
    for (int i = 0; i < map->GetNumObjectGroups(); ++i)
    {
        printf("                                    \n");
        printf("====================================\n");
        printf("Object group : %02d\n", i);
        printf("====================================\n");

        // Get an object group.
        const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

        // Iterate through all objects in the object group.
        for (int j = 0; j < objectGroup->GetNumObjects(); ++j)
        {
            // Get an object.
            const Tmx::Object *object = objectGroup->GetObject(j);

            // Print information about the object.
            printf("Object Name: %s\n", object->GetName().c_str());
            printf("Object Position: (%03d, %03d)\n", object->GetX(),
                    object->GetY());
            printf("Object Size: (%03d, %03d)\n", object->GetWidth(),
                    object->GetHeight());

            // Print Polygon points.
            const Tmx::Polygon *polygon = object->GetPolygon();
            if (polygon != 0)
            {
                for (int i = 0; i < polygon->GetNumPoints(); i++)
                {
                    const Tmx::Point &point = polygon->GetPoint(i);
                    printf("Object Polygon: Point %d: (%f, %f)\n", i, point.x,
                            point.y);
                }
            }

            // Print Polyline points.
            const Tmx::Polyline *polyline = object->GetPolyline();
            if (polyline != 0)
            {
                for (int i = 0; i < polyline->GetNumPoints(); i++)
                {
                    const Tmx::Point &point = polyline->GetPoint(i);
                    printf("Object Polyline: Point %d: (%f, %f)\n", i, point.x,
                            point.y);
                }
            }
        }
    }

    delete map;

    return 0;
}
