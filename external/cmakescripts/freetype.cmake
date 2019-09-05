# CMakeLists.txt
#
# Copyright 2013-2018 by
# David Turner, Robert Wilhelm, and Werner Lemberg.
#
# Written originally by John Cary <cary@txcorp.com>
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.
#
#
# The following will 1. create a build directory and 2. change into it and
# call cmake to configure the build with default parameters as a static
# library.
#
#   cmake -E make_directory build
#   cmake -E chdir build cmake ..
#
# For a dynamic library, use
#
#   cmake -E chdir build cmake -D BUILD_SHARED_LIBS:BOOL=true ..
#
# For a framework on OS X, use
#
#   cmake -E chdir build cmake -G Xcode -D BUILD_FRAMEWORK:BOOL=true ..
#
# For an iOS static library, use
#
#   cmake -E chdir build cmake -G Xcode -D IOS_PLATFORM=OS ..
#
# or
#
#   cmake -E chdir build cmake -G Xcode -D IOS_PLATFORM=SIMULATOR ..
#
# Finally, build the project with:
#
#   cmake --build build
#
# Install it with
#
#   (sudo) cmake --build build --target install
#
# A binary distribution can be made with
#
#   cmake --build build --config Release --target package
#
# Please refer to the cmake manual for further options, in particular, how
# to modify compilation and linking parameters.
#
# Some notes.
#
# . `cmake' creates configuration files in
#
#     <build-directory>/include/freetype/config
#
#   which should be further modified if necessary.
#
# . You can use `cmake' directly on a freshly cloned FreeType git
#   repository.
#
# . `CMakeLists.txt' is provided as-is since it is normally not used by the
#   developer team.
#
# . Set the `FT_WITH_ZLIB', `FT_WITH_BZIP2', `FT_WITH_PNG', and
#   `FT_WITH_HARFBUZZ' CMake variables to `ON' to force using a dependency.
#   Leave a variable undefined (which is the default) to use the dependency
#   only if it is available.  Set `CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz=TRUE' to
#   disable a dependency completely (CMake package name, so `BZip2' instead of
#   `BZIP2'). Example:
#
#     cmake -DFT_WITH_ZLIB=ON -DCMAKE_DISABLE_FIND_PACKAGE_HarfBuzz=TRUE [...]
#
# . Installation of FreeType can be controlled with the CMake variables
#   `SKIP_INSTALL_HEADERS', `SKIP_INSTALL_LIBRARIES', and `SKIP_INSTALL_ALL'
#   (this is compatible with the same CMake variables in zlib's CMake
#   support).

# FreeType explicitly marks the API to be exported and relies on the compiler
# to hide all other symbols. CMake supports a C_VISBILITY_PRESET property
# starting with 2.8.12.
cmake_minimum_required(VERSION 3.14.5)

include(CheckIncludeFile)


project(freetype C)

set(VERSION_MAJOR "2")
set(VERSION_MINOR "9")
set(VERSION_PATCH "1")

# SOVERSION scheme: CURRENT.AGE.REVISION
#   If there was an incompatible interface change:
#     Increment CURRENT. Set AGE and REVISION to 0
#   If there was a compatible interface change:
#     Increment AGE. Set REVISION to 0
#   If the source code was changed, but there were no interface changes:
#     Increment REVISION.
set(LIBRARY_VERSION "6.16.0")
set(LIBRARY_SOVERSION "6")

# These options mean "require x and complain if not found". They'll get
# optionally found anyway. Use `-DCMAKE_DISABLE_FIND_PACKAGE_x=TRUE` to disable
# searching for a packge entirely (x is the CMake package name, so "BZip2"
# instead of "BZIP2").
option(FT_WITH_ZLIB "Use system zlib instead of internal library." OFF)
option(FT_WITH_BZIP2 "Support bzip2 compressed fonts." OFF)
option(FT_WITH_PNG "Support PNG compressed OpenType embedded bitmaps." OFF)
option(FT_WITH_HARFBUZZ "Improve auto-hinting of OpenType fonts." OFF)

# Find dependencies
if (FT_WITH_HARFBUZZ)
  find_package(HarfBuzz 1.3.0 REQUIRED)
else ()
  find_package(HarfBuzz 1.3.0)
endif ()

if (FT_WITH_PNG)
  find_package(PNG REQUIRED)
else ()
  find_package(PNG)
endif ()

if (FT_WITH_ZLIB)
  find_package(ZLIB REQUIRED)
else ()
  find_package(ZLIB)
endif ()

if (FT_WITH_BZIP2)
  find_package(BZip2 REQUIRED)
else ()
  find_package(BZip2)
endif ()

set(FREETYPE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/freetype/")

# Create the configuration file
if (UNIX)
  check_include_file("unistd.h" HAVE_UNISTD_H)
  check_include_file("fcntl.h" HAVE_FCNTL_H)
  check_include_file("stdint.h" HAVE_STDINT_H)

  file(READ "${FREETYPE_SOURCE_DIR}/builds/unix/ftconfig.in"
    FTCONFIG_H)
  if (HAVE_UNISTD_H)
    string(REGEX REPLACE
      "#undef +(HAVE_UNISTD_H)" "#define \\1 1"
      FTCONFIG_H "${FTCONFIG_H}")
  endif ()
  if (HAVE_FCNTL_H)
    string(REGEX REPLACE
      "#undef +(HAVE_FCNTL_H)" "#define \\1 1"
      FTCONFIG_H "${FTCONFIG_H}")
  endif ()
  if (HAVE_STDINT_H)
    string(REGEX REPLACE
      "#undef +(HAVE_STDINT_H)" "#define \\1 1"
      FTCONFIG_H "${FTCONFIG_H}")
  endif ()
  string(REPLACE "/undef " "#undef "
    FTCONFIG_H "${FTCONFIG_H}")
  file(WRITE "${PROJECT_BINARY_DIR}/include/freetype/config/ftconfig.h"
    "${FTCONFIG_H}")
endif ()


# Create the options file
file(READ "${FREETYPE_SOURCE_DIR}/include/freetype/config/ftoption.h"
  FTOPTION_H)
if (ZLIB_FOUND)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_SYSTEM_ZLIB) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
if (BZIP2_FOUND)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_USE_BZIP2) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
if (PNG_FOUND)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_USE_PNG) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
if (HARFBUZZ_FOUND)
  string(REGEX REPLACE
    "/\\* +(#define +FT_CONFIG_OPTION_USE_HARFBUZZ) +\\*/" "\\1"
    FTOPTION_H "${FTOPTION_H}")
endif ()
file(WRITE "${PROJECT_BINARY_DIR}/include/freetype/config/ftoption.h"
  "${FTOPTION_H}")


file(GLOB PUBLIC_HEADERS "include/ft2build.h" "include/freetype/*.h")
file(GLOB PUBLIC_CONFIG_HEADERS "include/freetype/config/*.h")
file(GLOB PRIVATE_HEADERS "include/freetype/internal/*.h")


set(BASE_SRCS
  freetype/src/autofit/autofit.c
  freetype/src/base/ftbase.c
  freetype/src/base/ftbbox.c
  freetype/src/base/ftbdf.c
  freetype/src/base/ftbitmap.c
  freetype/src/base/ftcid.c
  freetype/src/base/ftfstype.c
  freetype/src/base/ftgasp.c
  freetype/src/base/ftglyph.c
  freetype/src/base/ftgxval.c
  freetype/src/base/ftinit.c
  freetype/src/base/ftmm.c
  freetype/src/base/ftotval.c
  freetype/src/base/ftpatent.c
  freetype/src/base/ftpfr.c
  freetype/src/base/ftstroke.c
  freetype/src/base/ftsynth.c
  freetype/src/base/ftsystem.c
  freetype/src/base/fttype1.c
  freetype/src/base/ftwinfnt.c
  freetype/src/bdf/bdf.c
  freetype/src/bzip2/ftbzip2.c
  freetype/src/cache/ftcache.c
  freetype/src/cff/cff.c
  freetype/src/cid/type1cid.c
  freetype/src/gzip/ftgzip.c
  freetype/src/lzw/ftlzw.c
  freetype/src/pcf/pcf.c
  freetype/src/pfr/pfr.c
  freetype/src/psaux/psaux.c
  freetype/src/pshinter/pshinter.c
  freetype/src/psnames/psnames.c
  freetype/src/raster/raster.c
  freetype/src/sfnt/sfnt.c
  freetype/src/smooth/smooth.c
  freetype/src/truetype/truetype.c
  freetype/src/type1/type1.c
  freetype/src/type42/type42.c
  freetype/src/winfonts/winfnt.c
)

if (WIN32)
  enable_language(RC)
  list(APPEND BASE_SRCS builds/windows/ftdebug.c
                        freetype/src/base/ftver.rc)
elseif (WINCE)
  list(APPEND BASE_SRCS builds/wince/ftdebug.c)
else ()
  list(APPEND BASE_SRCS freetype/src/base/ftdebug.c)
endif ()

if (BUILD_FRAMEWORK)
  list(APPEND BASE_SRCS builds/mac/freetype-Info.plist)
endif ()


if (NOT DISABLE_FORCE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()


add_library(freetype STATIC
  ${PUBLIC_HEADERS}
  ${PUBLIC_CONFIG_HEADERS}
  ${PRIVATE_HEADERS}
  ${BASE_SRCS}
)

set_target_properties(
  freetype PROPERTIES
    C_VISIBILITY_PRESET hidden)

target_compile_definitions(
  freetype PRIVATE FT2_BUILD_LIBRARY)

if (WIN32)
  target_compile_definitions(
    freetype PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
endif ()


target_include_directories(
  freetype BEFORE  # Pick up ftconfig.h and ftoption.h generated above.
    PUBLIC "${PROJECT_BINARY_DIR}/include")

target_include_directories(
  freetype
    PUBLIC "${FREETYPE_SOURCE_DIR}/include")

include_directories( freetype SYSTEM PUBLIC include)


set(PKG_CONFIG_REQUIRED_PRIVATE "")

if (ZLIB_FOUND)
  target_link_libraries(freetype PRIVATE ${ZLIB_LIBRARIES})
  target_include_directories(freetype PRIVATE ${ZLIB_INCLUDE_DIRS})
  list(APPEND PKG_CONFIG_REQUIRED_PRIVATE zlib)
endif ()
if (BZIP2_FOUND)
  target_link_libraries(freetype PRIVATE ${BZIP2_LIBRARIES})
  target_include_directories(freetype PRIVATE ${BZIP2_INCLUDE_DIR}) # not BZIP2_INCLUDE_DIRS
  list(APPEND PKG_CONFIG_REQUIRED_PRIVATE bzip2)
endif ()
if (PNG_FOUND)
  target_link_libraries(freetype PRIVATE ${PNG_LIBRARIES})
  target_compile_definitions(freetype PRIVATE ${PNG_DEFINITIONS})
  target_include_directories(freetype PRIVATE ${PNG_INCLUDE_DIRS})
  list(APPEND PKG_CONFIG_REQUIRED_PRIVATE libpng)
endif ()
if (HARFBUZZ_FOUND)
  target_link_libraries(freetype PRIVATE ${HARFBUZZ_LIBRARIES})
  target_include_directories(freetype PRIVATE ${HARFBUZZ_INCLUDE_DIRS})
  list(APPEND PKG_CONFIG_REQUIRED_PRIVATE harfbuzz)
endif ()

