cmake_minimum_required(VERSION 3.14)  # CMake version check
project(data-structs-wet2)            
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

add_compile_options (-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter)

# source directory
add_subdirectory(src)
add_subdirectory(tests)

file(GLOB inputs "${CMAKE_CURRENT_SOURCE_DIR}/tests/input/*.txt")
file(GLOB outputs "${CMAKE_CURRENT_SOURCE_DIR}/tests/output/*.txt")

foreach(filename ${inputs})
    get_filename_component(filename_no_extension ${filename} NAME_WE)
    string(REGEX REPLACE "in" "actual" actual_no_extension ${filename_no_extension})
    add_test(NAME "${filename_no_extension}" COMMAND
        ${CMAKE_COMMAND}
        -D COMMAND=$<TARGET_FILE:data-structs-wet2>
        -D INPUT_FILE=${filename}
        -D OUTPUT_FILE=${CMAKE_CURRENT_BINARY_DIR}/${actual_no_extension}.txt
        -P ${CMAKE_CURRENT_SOURCE_DIR}/redirect_stdin_from_file.cmake
      )
endforeach()


foreach(filename ${outputs})
    get_filename_component(filename_no_extension ${filename} NAME_WE)
    string(REGEX REPLACE "out" "in" input_no_extension ${filename_no_extension})
    string(REGEX REPLACE "out" "actual" actual ${filename_no_extension})

    add_test(NAME "compare${filename_no_extension}"
    COMMAND ${CMAKE_COMMAND} -E compare_files --ignore-eol ${CMAKE_CURRENT_BINARY_DIR}/${actual}.txt ${filename})
    set_tests_properties(compare${filename_no_extension} PROPERTIES DEPENDS "${input_no_extension}")
endforeach()

# foreach (filename ${inputs})
#     #add_test(${filename} data-structs-1 ${filename})
#     add_test(NAME "${filename}"
#        COMMAND sh -c "$<TARGET_FILE:data-structs-wet2> < ${filename}")
#     set_tests_properties(${filename} PROPERTIES LABELS Memcheck)
# endforeach()

# add_custom_target(test_memcheck
#     COMMAND ${CMAKE_CTEST_COMMAND} 
#         --force-new-ctest-process --test-action memcheck
#     COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
#     WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

enable_testing()

include(CTest)

