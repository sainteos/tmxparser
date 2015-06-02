#
# This module will look for Tmxparser (https://github.com/andrewrk/tmxparser)
# it will define the following values
#
# TMXPARSER_INCLUDE_DIR  = where Tmx.h can be found
# TMXPARSER_LIBRARY      = the library to link against (Tmxparser)
#

SET(TRIAL_INCLUDE_PATHS Tmx.h
     HINTS $ENV{TMXPARSER_HOME}
     PATH_SUFFIXES include include/tmxparser
     PATHS
     ~/Library/Frameworks
     /Library/Frameworks
     /usr/local
     /usr
  )

SET(TRIAL_LIBRARY_PATHS
   HINTS $ENV{TMXPARSER_HOME}
   PATH_SUFFIXES lib64 lib
   PATHS
   ~/Library/Frameworks
   /Library/Frameworks
   /usr/local
   /usr
  )

FIND_PATH(TMXPARSER_INCLUDE_DIR Tmx.h ${TRIAL_INCLUDE_PATHS})
FIND_LIBRARY(TMXPARSER_LIBRARY tmx-parser ${TRIAL_LIBRARY_PATHS})

MARK_AS_ADVANCED(
    TMXPARSER_INCLUDE_DIR
    TMXPARSER_LIBRARY
)