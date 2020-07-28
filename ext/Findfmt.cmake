include(ExternalProject)
include(GNUInstallDirs)

ExternalProject_Add(fmt-project
  PREFIX deps/fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
  GIT_TAG "master"
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/fmt
  STAMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/stamp
  TMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/tmp
  CMAKE_ARGS "-DFMT_DOC:BOOL=OFF" "-DFMT_TEST:BOOL=OFF" "-DFMT_INSTALL:BOOL=OFF"
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

add_library(fmt INTERFACE)
target_link_libraries(fmt fmt-headers-only)

# target_compile_definitions(fmt INTERFACE FMT_HEADER_ONLY=1)

# target_include_directories(fmt INTERFACE
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/pack/fmt/include>
#   $<INSTALL_INTERFACE:include>)

add_dependencies(fmt fmt-project)
