cmake_minimum_required(VERSION 3.3)

# Depends on libfmt/fmt
include(${CMAKE_CURRENT_SOURCE_DIR}/ext/fmt/fmt.cmake)

# Defining the library
add_library(mfl INTERFACE)
target_sources(mfl INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/args.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/exception.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/file.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/out.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/path.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/string.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/timer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mfl/util.hpp
    )

# Link to fmt
target_link_libraries(mfl INTERFACE fmt)

# Export headers
target_include_directories(mfl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${FMT_INCLUDE_DIR})
