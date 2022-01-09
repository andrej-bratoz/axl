add_library (axl_logging SHARED "src/axl-log.h" "module.cpp")
target_link_libraries(axl_logging axl_core)

add_custom_command(TARGET axl_logging POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy 
	"$<TARGET_FILE:axl_logging>"
	"${CMAKE_BINARY_DIR}/../../../bin/modules/$<TARGET_FILE_NAME:axl_logging>.module"
	COMMENT "Copy axl_logging to bin")