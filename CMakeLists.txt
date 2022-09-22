cmake_minimum_required (VERSION 3.8)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/settings.json DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
project (maolib)

set(project_file_types 
	*.cpp 
	*.c 
	*.h 
	*.hint 
	*.hpp
	*.json
)
file(GLOB root_files
     LIST_DIRECTORIES false
	 ${project_file_types}
)
set(all_files ${root_files})

set(all_libs maolib_json maolib_openapi)
foreach(this_lib ${all_libs})
	add_subdirectory(${this_lib})
endforeach()

add_executable(maolib ${all_files})
include_directories(${all_libs})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET maolib PROPERTY CXX_STANDARD 20)
endif()

