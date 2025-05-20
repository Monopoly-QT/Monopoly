# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appmonopoly_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appmonopoly_autogen.dir\\ParseCache.txt"
  "appmonopoly_autogen"
  )
endif()
