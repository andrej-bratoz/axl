# CMakeList.txt : CMake project for axl_core, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (axl_core STATIC "include/axl-time.h"  "include/axl-defer.h" "include/axl-macro.h" "src/axl-file.cpp" "include/axl-thread.h" "src/axl-thread.cpp" "include/axl-exception.h" "include/axl-generators.h" "include/axl-message-bus.h" "src/axl-message-bus.cpp" "include/axl-module.h" "include/axl-serialization.h" "include/axl-refc.h" "include/axl-datetime.h" "include/axl-module-list.h" "include/axl-version.h" "src/axl-version.cpp" "src/axl-module-list.cpp" "include/axl-helpers.h" "src/axl-hepers.cpp")

# TODO: Add tests and install targets if needed.


#add_custom_command(TARGET axl_core POST_BUILD 
#	COMMAND ${CMAKE_COMMAND} -E copy 
#	"$<TARGET_FILE:axl_core>"
#	"${CMAKE_BINARY_DIR}/../../../bin/$<TARGET_FILE_NAME:axl_core>"
#	COMMENT "Copy axl_core to bin")