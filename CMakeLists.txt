cmake_minimum_required(VERSION 3.1)

project(audacious-openmpt)

include(audacious.cmake)

set(pkg libopenmpt)
set(srcs mpt.cpp mptwrap.cpp)

audacious_plugin(cas-mpt SRCS ${srcs} PKG ${pkg})
