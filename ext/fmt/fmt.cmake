include(ExternalProject)
include(GNUInstallDirs)

ExternalProject_Add(fmt-project
  PREFIX deps/fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
  GIT_TAG "master"
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/fmt
  STAMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/tmp/fmt
  TMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/tmp/fmt
  CMAKE_ARGS "-DFMT_TEST=OFF"
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  )

set(FMT_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/fmt/include)

add_library(fmt STATIC IMPORTED)
set_property(TARGET fmt PROPERTY INTERFACE_LINK_LIBRARIES fmt::fmt-header-only)
add_dependencies(fmt fmt-project)
