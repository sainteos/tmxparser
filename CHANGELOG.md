# Changelog

### Next release

 * georgerbr:
   - Make tileset parsing not depend on optional attrs of <image>

 * Andrew Kelley:
   - Add FindTmxParser.cmake example

 * Wasabi2007:
   - Added support for Collision Tiles
   - Changed data format in Point from int to float to follow Tiled format (bugfix)

 * Acedio:
   - Adding missing library dependencies to TmxUtil.cpp

 * Tigran Saluev:
   - Add support for <image> in <tile>

 * Richel Bilderbeek:
   - Removed const return types

 * Blazej Floch:
   - Small changes to TmxPropertySet
   - Better compatibility with cmake project as subdirectory

 * Tamir Atias:
   - Add support for typed properties (added in Tiled 0.16)

 * Peter Asplund (AzP):
   - Add C++11 requirement in CMakeLists.txt

 * Solever Lee:
   - added 'tilecount' and 'columns' properity for 'tileset' element

 * Guillaume Bertholon (Sakarah):
   - Add support for color and file property types (added in Tiled 0.17)
   - Add Doxygen documentation

 * Tardo:
   - Get tile by index

### 2.0.1

 * georgerbr:
   - Fix incorrect version number reported.

### 2.0.0

 * georgerbr:
   - Fix #9, #13 and #17
   - Implement missing elements (except TSX loading) from TMX format
   - Initialize tileOffset to NULL in Tmx::Tileset.
   - Corrected misspelled attribute name.
   - Catch up to TMX Format as of Tiled 0.12

 * Alessio Linares:
   - fixed gid of MapTile being local to its tileset and not global
   - Added getter for the id of an object
   - Added getter for the nextobjectid map parameter
   - Added version defines (minor and major)
   - Changes commented on commit b5e6040

 * Thomas Fischer:
   - fixed a trim function that was messing with the underlying string
   - enabled loading of external tileset (TSX) files
   - fixed naming convention
   - replaced the long file open routine with a tinyxml loadFile call

 * Ashley Davis (SgtCoDFish):
   - Update gitignore, AUTHORS
   - Add support for loading and storing animated tiles, mostly in TmxTile.h/cpp.
   - Add example animated tileset and update example.tmx to include an animated example.

 * Andrew Kelley:
   - better TmxPropertySet API

 * Vincent Heuken:
   - added `USE_MINIZ` option

 * Ashley Davis:
   - Fix formatting and incorrect method name in TmxTile.h, TmxTile.cpp and test.cpp

 * Edward Lu:
   - Add rotation property on objects

 * Jamie Nicol:
   - Add pkg-config file.

 * Kris McAulay:
   - Modified the cmake file to look for tinyxml2

 * krux02:
   - Update CMakeLists.txt

### 1.0.0

 * Initial fork from https://code.google.com/p/tmx-parser/
 * Layer: Add getters for opacity and visible
 * Drop support for Android and Windows. If you want a Windows build, use mxe.
 * Build: Create and install a shared library in addition to a static object.
 * Build: Depend on system zlib and TinyXML.
 * Drop `USE_SDL2_LOAD` support.
