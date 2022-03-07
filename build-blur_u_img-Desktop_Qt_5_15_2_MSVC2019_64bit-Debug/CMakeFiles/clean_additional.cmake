# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\blur_u_img_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\blur_u_img_autogen.dir\\ParseCache.txt"
  "blur_u_img_autogen"
  )
endif()
