
add_library (axl_settings SHARED "src/axl-settings.h" "src/axl-settings.cpp" "module.cpp")
target_link_libraries(axl_settings axl_core)

add_custom_command(TARGET axl_settings POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy 
	"$<TARGET_FILE:axl_settings>"
	"${CMAKE_BINARY_DIR}/../../../bin/modules/$<TARGET_FILE_NAME:axl_settings>.module"
	COMMENT "Copy axl_core to bin")