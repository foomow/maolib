cmake_minimum_required (VERSION 3.8)
set(exe_name maolib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/settings.json DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

project (${exe_name})
set(project_file_types 
	*.cpp 
	*.c 
	*.h 
	*.hint 
	*.hpp
	*.json
)

string(LENGTH ${CMAKE_CURRENT_SOURCE_DIR} path_len)
math(EXPR path_len "${path_len}+1")
file(GLOB all_subdirectory
     LIST_DIRECTORIES true
	 maolib_*
)
foreach(this_directory ${all_subdirectory})
	add_subdirectory(${this_directory})
	string(SUBSTRING ${this_directory} ${path_len} -1 this_lib)
	set(all_lib ${all_lib} ${this_lib})
endforeach()

include_directories(${all_lib})

file(GLOB all_files
     LIST_DIRECTORIES false
	 ${project_file_types}
)
add_executable(${exe_name} ${all_files})
target_link_libraries(${exe_name} ${all_lib})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${exe_name} PROPERTY CXX_STANDARD 20)
endif()

