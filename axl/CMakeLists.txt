cmake_minimum_required (VERSION 3.8)

add_executable(axl "src/main.cpp" "src/app.h")
target_link_libraries(axl axl_core)

add_custom_command(TARGET axl POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy 
	"$<TARGET_FILE:axl>"
	"${CMAKE_BINARY_DIR}/../../../bin/$<TARGET_FILE_NAME:axl>"
	COMMENT "Copy axl_core to bin")