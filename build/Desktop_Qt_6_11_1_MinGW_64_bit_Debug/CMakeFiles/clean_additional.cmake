# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DanUtilGUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DanUtilGUI_autogen.dir\\ParseCache.txt"
  "DanUtilGUI_autogen"
  )
endif()
