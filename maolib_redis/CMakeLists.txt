set(lib_name maolib_redis)

file(GLOB lib_files
	LIST_DIRECTORIES false
	${project_file_types}
	)
add_library(${lib_name} STATIC ${lib_files})

