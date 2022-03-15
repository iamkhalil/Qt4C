cmake_minimum_required(VERSION 3.20)

project(Qt4C VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

function(enable_warnings target)
  option(WARNINGS_AS_ERRORS "Make all warnings into errors" TRUE)
  set(MSVC_WARNINGS /W4)
  set(GCC_WARNINGS -Wall -Wextra -Wpedantic)
  if(WARNING_AS_ERRORS)
    set(MSVC_WARNINGS ${MSVC_WARNINGS} /WX)
    set(GCC_WARNINGS ${GCC_WARNINGS} -Werror)
  endif()

  if(MSVC)
    set(WARNINGS ${MSVC_WARNINGS})
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(WARNINGS ${GCC_WARNINGS})
  else()
    message("No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
  endif()

  target_compile_options(${target} PRIVATE ${WARNINGS})

endfunction()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_library(wrapper SHARED
  src/wrapper.cpp
  src/wrapper.h
)

target_link_libraries(wrapper PRIVATE Qt5::Core Qt5::Widgets)

enable_warnings(wrapper)

add_executable(main
  test/main.c
)

target_link_libraries(main
  wrapper
)
