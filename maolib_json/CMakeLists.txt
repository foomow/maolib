set(lib_name maolib_json)

file(GLOB lib_files
	LIST_DIRECTORIES false
	${project_file_types}
	)
set(all_files ${all_files} ${lib_files} PARENT_SCOPE)
add_library(${lib_name} SHARED ${lib_files})
set(${lib_name}_files ${lib_files} PARENT_SCOPE)
