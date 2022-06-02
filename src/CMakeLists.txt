
# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main2_without_bonus.cpp Company.cpp Employee.cpp MainDataStructure.cpp Wrapper.cpp)


# Add executable target with source files listed in SOURCE_FILES variable
add_executable(data-structs-wet2 ${SOURCE_FILES})