set(lib_name maolib_json)

file(GLOB lib_files
	LIST_DIRECTORIES false
	${project_file_types}
	)
add_library(${lib_name} STATIC ${lib_files})
set_target_properties (${lib_name} PROPERTIES LINKER_LANGUAGE CXX)
