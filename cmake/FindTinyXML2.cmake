# This file licensed under GNU GPL v3
# Source: https://code.google.com/p/mgep/source/browse/branches/clientv2/CMakeModules/FindTinyXML.cmake

# - Find TinyXML
# Find the native TinyXML includes and library
#
#   TINYXML2_FOUND       - True if TinyXML2 found.
#   TINYXML2_INCLUDE_DIR - where to find tinyxml2.h, etc.
#   TINYXML2_LIBRARIES   - List of libraries when using TinyXML2.
#

IF( TINYXML2_INCLUDE_DIR )
    # Already in cache, be silent
    SET( TinyXML2_FIND_QUIETLY TRUE )
ENDIF( TINYXML2_INCLUDE_DIR )

FIND_PATH( TINYXML2_INCLUDE_DIR "tinyxml2.h"
           PATH_SUFFIXES "tinyxml2" )

FIND_LIBRARY( TINYXML2_LIBRARIES
              NAMES "tinyxml2"
              PATH_SUFFIXES "tinyxml2" )

# handle the QUIETLY and REQUIRED arguments and set TINYXML2_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "TinyXML2" DEFAULT_MSG TINYXML2_INCLUDE_DIR TINYXML2_LIBRARIES )

MARK_AS_ADVANCED( TINYXML2_INCLUDE_DIR TINYXML2_LIBRARIES )

