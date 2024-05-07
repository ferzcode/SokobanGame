# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Sokoban_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Sokoban_autogen.dir\\ParseCache.txt"
  "Sokoban_autogen"
  )
endif()
