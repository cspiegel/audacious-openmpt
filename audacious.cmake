function(audacious_plugin target)
  set(options AUDTAG)
  set(oneval)
  set(multival SRCS PKG)
  cmake_parse_arguments(PLUGIN "${options}" "${oneval}" "${multival}" ${ARGN})
  add_library(${target} MODULE ${PLUGIN_SRCS})

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${target} PRIVATE -Wall)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${target} PRIVATE -Wall)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    target_compile_options(${target} PRIVATE -std=c++11)
    target_compile_options(${target} PRIVATE -w2)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "SunPro")
    target_compile_options(${target} PRIVATE +w)
  endif()

  set_target_properties(${target}
    PROPERTIES
    PREFIX ""
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

  target_compile_definitions(${target} PRIVATE "PACKAGE=\"${target}\"")

  if(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALL REQUIRED audacious ${PLUGIN_PKG})
  elseif(MINGW)
    list(APPEND ALL_INCLUDE_DIRS aud/include)
    list(APPEND ALL_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/aud/lib/libopenmpt.dll)
    list(APPEND ALL_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/aud/lib/libaudcore.dll)
  endif()

  if(PLUGIN_AUDTAG)
    target_link_libraries(${target} audtag)
  endif()

  if(NOT ${ALL_INCLUDE_DIRS} STREQUAL "")
    target_include_directories(${target} PRIVATE ${ALL_INCLUDE_DIRS})
  endif()
  target_link_libraries(${target} ${ALL_LIBRARIES})

  execute_process(COMMAND pkg-config --variable=plugin_dir audacious OUTPUT_VARIABLE PLUGIN_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
  install(TARGETS ${target} DESTINATION "${PLUGIN_DIR}/Input")
endfunction()
