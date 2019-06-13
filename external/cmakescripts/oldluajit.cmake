# This CMakeLists.txt has been first taken from LuaDist
# Copyright (C) 2007-2011 LuaDist.
# Created by Peter Drahoš
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# Debugged and (now seriously) modified by Ronan Collobert, for Torch7

project(LuaJIT C ASM)

include_directories(LuaJIT public luajit/src)

IF(APPLE)
  CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12 FATAL_ERROR)
  CMAKE_POLICY(VERSION 2.8.12)
  SET(CMAKE_MACOSX_RPATH TRUE) # @rpath in libs
ELSE()
  CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
  CMAKE_POLICY(VERSION 2.8)
ENDIF()

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmakescripts"
                      "${CMAKE_MODULE_PATH}")

OPTION(WITH_AMALG "Build eveything in one shot (needs memory)" ON)

SET(INSTALL_INCLUDE_SUBDIR "include" CACHE STRING "installation include subdirectory name")
IF(WIN32)
  SET(INSTALL_BIN_SUBDIR "." CACHE STRING "installation executable subdirectory name")
  SET(INSTALL_LIB_SUBDIR "." CACHE STRING "installation library subdirectory name")
  SET(INSTALL_LUA_PATH_SUBDIR "lua") # not editable
  SET(INSTALL_LUA_CPATH_SUBDIR ".") # not editable
ELSE()
  SET(INSTALL_BIN_SUBDIR "bin" CACHE STRING "installation executable subdirectory name")
  SET(INSTALL_LIB_SUBDIR "lib" CACHE STRING "installation library subdirectory name")
  SET(INSTALL_LUA_PATH_SUBDIR "share/lua/5.1/" CACHE STRING "lua path subdirectory name")
  SET(INSTALL_LUA_LIB_SUBDIR "lib" CACHE STRING "installation lua lib subdirectory name")
  SET(INSTALL_LUA_CPATH_SUBDIR "${INSTALL_LUA_LIB_SUBDIR}/lua/5.1/" CACHE STRING "lua cpath subdirectory name")
ENDIF()

ADD_DEFINITIONS(-DLUA_MULTILIB="${INSTALL_LUA_LIB_SUBDIR}")

IF(UNIX)
  IF(NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
    ADD_DEFINITIONS(-DLUA_ROOT="${CMAKE_INSTALL_PREFIX}")
  ENDIF()
ENDIF()

# Ugly warnings
IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

# Readline support
FIND_PACKAGE(Readline)
IF(READLINE_FOUND)
  ADD_DEFINITIONS("-DLUA_USE_READLINE")
  LIST(APPEND LIBS ${READLINE_LIBRARIES})
  INCLUDE_DIRECTORIES(${READLINE_INCLUDE_DIR})
ENDIF()

# Various includes
INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckTypeSize)

# LuaJIT specific
option ( LUAJIT_DISABLE_FFI "Disable FFI." OFF )
option ( LUAJIT_ENABLE_LUA52COMPAT "Enable Lua 5.2 compatibility." ON )
option ( LUAJIT_DISABLE_JIT "Disable JIT." OFF )
option ( LUAJIT_CPU_SSE2 "Use SSE2 instead of x87 instructions." ON )
option ( LUAJIT_CPU_NOCMOV "Disable NOCMOV." OFF )

option ( LUAJIT_USE_SYSMALLOC "LuaJIT uses sysmalloc?" OFF )
option ( LUAJIT_USE_VALGRIND "Luajit compatible with Valgrind?" OFF )
option ( LUAJIT_USE_GDBJIT "Luajit uses GDBJIT?" OFF )
option ( LUA_USE_APICHECK "LuaJIT does API checks?" OFF )
option ( LUA_USE_ASSERT "LuaJIT does asserts?" OFF )

option ( LUAJIT_ENABLE_GC64 "LuaJIT 64 bits support" ON )

MARK_AS_ADVANCED(
  LUAJIT_DISABLE_FFI
  LUAJIT_ENABLE_LUA52COMPAT
  LUAJIT_DISABLE_JIT
  LUAJIT_CPU_SSE2
  LUAJIT_CPU_NOCMOV
  LUAJIT_USE_SYSMALLOC
  LUAJIT_USE_VALGRIND
  LUAJIT_USE_GDBJIT
  LUA_USE_APICHECK
  LUA_USE_ASSERT
  LUAJIT_ENABLE_GC64
  )

MACRO(ADD_MANDATORY_DEFINITIONS stuff)
  ADD_DEFINITIONS(${stuff})
  SET(CMAKE_REQUIRED_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS} ${stuff})
ENDMACRO()

IF(LUAJIT_DISABLE_FFI)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_FFI)
ENDIF()

IF(LUAJIT_ENABLE_LUA52COMPAT)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_ENABLE_LUA52COMPAT)
ENDIF()

IF(LUAJIT_DISABLE_JIT)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_DISABLE_JIT)
ENDIF()

IF(LUAJIT_CPU_SSE2)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_SSE2)
ENDIF()

IF(LUAJIT_CPU_NOCMOV)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_CPU_NOCMOV)
ENDIF()

IF(LUAJIT_USE_SYSMALLOC)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_SYSMALLOC)
ENDIF()

IF(LUAJIT_USE_VALGRIND)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_VALGRIND)
ENDIF()

IF(LUAJIT_USE_GDBJIT)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_USE_GDBJIT)
ENDIF()

IF(LUA_USE_APICHECK)
  ADD_MANDATORY_DEFINITIONS(-DLUA_USE_APICHECK)
ENDIF()

IF(LUA_USE_ASSERT)
  ADD_MANDATORY_DEFINITIONS(-DLUA_USE_ASSERT)
ENDIF()

IF(LUAJIT_ENABLE_GC64)
  ADD_MANDATORY_DEFINITIONS(-DLUAJIT_ENABLE_GC64)
ENDIF()

######

CHECK_TYPE_SIZE("void*" SIZEOF_VOID_P)
IF(SIZEOF_VOID_P EQUAL 8)
  ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE)
ENDIF()

if ( WIN32 AND NOT CYGWIN )
  set(LUA_BUILD_AS_DLL 1)
  add_definitions ( -DLUA_BUILD_AS_DLL -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
  set ( LJVM_MODE peobj )
elseif ( APPLE )
  set ( LJVM_MODE machasm )
else ()
  set ( LJVM_MODE elfasm )
endif ()

IF(NOT WIN32)
  FIND_LIBRARY(DL_LIBRARY "dl")
  IF(DL_LIBRARY)
    SET(CMAKE_REQUIRED_LIBRARIES ${DL_LIBRARY})
    LIST(APPEND LIBS ${DL_LIBRARY})
  ENDIF(DL_LIBRARY)
  CHECK_FUNCTION_EXISTS(dlopen LUA_USE_DLOPEN)
  IF(NOT LUA_USE_DLOPEN)
    MESSAGE(FATAL_ERROR "Cannot compile a useful lua.
Function dlopen() seems not to be supported on your platform.
Apparently you are not on a Windows platform as well.
So lua has no way to deal with shared libraries!")
  ENDIF(NOT LUA_USE_DLOPEN)
ENDIF(NOT WIN32)

CHECK_LIBRARY_EXISTS(m sin "" LUA_USE_LIBM)
if ( LUA_USE_LIBM )
  list ( APPEND LIBS m )
endif ()

CHECK_LIBRARY_EXISTS(ncurses printw "" LUA_USE_LIBNCURSES)
if ( LUA_USE_LIBNCURSES )
  list ( APPEND LIBS ncurses )
endif ()

SET(CMAKE_THREAD_PREFER_PTHREAD TRUE)
FIND_PACKAGE(Threads)
IF(THREADS_FOUND)
  LIST(APPEND LIBS ${CMAKE_THREAD_LIBS_INIT})
ENDIF()

## SOURCES
INSTALL(FILES src/luaconf.h src/lua.h src/lauxlib.h src/lualib.h
              src/lua.hpp src/luajit.h
  DESTINATION "${INSTALL_INCLUDE_SUBDIR}")

MACRO(LJ_TEST_ARCH stuff)
  CHECK_C_SOURCE_COMPILES("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff})
ENDMACRO()

MACRO(LJ_TEST_ARCH_VALUE stuff value)
  CHECK_C_SOURCE_COMPILES("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff} == ${value}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff}_${value})
ENDMACRO()

message(${CMAKE_CURRENT_SOURCE_DIR})


set(LUADIR ${CMAKE_CURRENT_SOURCE_DIR}/luajit)
SET(CMAKE_REQUIRED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR} ${LUADIR}/src)
SET(CMAKE_REQUIRED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmakescripts)
FOREACH(arch X64 X86 ARM ARM64 PPC PPCSPE MIPS)
  LJ_TEST_ARCH(LJ_TARGET_${arch})
  if(LJ_TARGET_${arch})
    STRING(TOLOWER ${arch} TARGET_LJARCH)
    MESSAGE(STATUS "LuaJIT Target: ${TARGET_LJARCH}")
    BREAK()
  ENDIF()
ENDFOREACH()

IF(NOT TARGET_LJARCH)
  MESSAGE(FATAL_ERROR "architecture not supported")
ENDIF()

SET(DASM_ARCH ${TARGET_LJARCH})
SET(DASM_FLAGS)
SET(TARGET_ARCH)
LIST(APPEND TARGET_ARCH "LUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH}")
LJ_TEST_ARCH_VALUE(LJ_LE 1)
IF(LJ_LE_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_LE)
ELSEIF()
  SET(DASM_FLAGS ${DASM_FLAGS} -D ENDIAN_BE)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_ARCH_BITS 64)
IF(LJ_ARCH_BITS_64)
  SET(DASM_FLAGS ${DASM_FLAGS} -D P64)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_HASJIT 1)
IF(LJ_HASJIT_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D JIT)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_HASFFI 1)
IF(LJ_HASFFI_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D FFI)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_DUALNUM 1)
IF(LJ_DUALNUM_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D DUALNUM)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_ARCH_HASFPU 1)
IF(LJ_ARCH_HASFPU_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D FPU)
  LIST(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=1")
ELSE()
  LIST(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=0")
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_ABI_SOFTFP 1)
IF(NOT LJ_ABI_SOFTFP_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D HFABI)
  LIST(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=0")
ELSE()
  LIST(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=1")
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_NO_UNWIND 1)
IF(LJ_NO_UNWIND_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D NO_UNWIND)
  LIST(APPEND TARGET_ARCH "LUAJIT_NO_UNWIND")
ENDIF()
IF(WIN32)
  SET(DASM_FLAGS ${DASM_FLAGS} -LN -D WIN)
ENDIF()
IF(TARGET_LJARCH STREQUAL "x64")
  IF(APPLE)
    set ( CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000 ${CMAKE_EXE_LINKER_FLAGS}" )
    set ( CMAKE_SHARED_LINKER_FLAGS "-image_base 7fff04c4a000" ${CMAKE_SHARED_LINKER_FLAGS})
  ENDIF()

  LJ_TEST_ARCH_VALUE(LJ_FR2 1)
  IF(NOT LJ_FR2_1)
    SET(DASM_ARCH "x86")
  ENDIF()
ENDIF()
IF(TARGET_LJARCH STREQUAL "ppc")
  LJ_TEST_ARCH_VALUE(LJ_ARCH_SQRT 1)
  IF(NOT LJ_ARCH_SQRT_1)
    SET(DASM_FLAGS ${DASM_FLAGS} -D SQRT)
  ENDIF()
  LJ_TEST_ARCH_VALUE(LJ_ARCH_PPC64 1)
  IF(NOT LJ_ARCH_PPC64_1)
    SET(DASM_FLAGS ${DASM_FLAGS} -D GPR64)
  ENDIF()
ENDIF()

if(LUAJIT_SYSTEM_MINILUA)
  MESSAGE(STATUS "Using system lua for generating dynasm via: ${LUAJIT_SYSTEM_MINILUA}")
  # SET(LUAJIT_SYSTEM_MINILUA ${LUAJIT_SYSTEM_MINILUA} CACHE STRING "system minilua" FORCE)
  MESSAGE(STATUS "Executing command: ${LUAJIT_SYSTEM_MINILUA} ${LUADIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${LUADIR}/src/vm_${DASM_ARCH}.dasc")
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
    COMMAND ${LUAJIT_SYSTEM_MINILUA} ${LUADIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${LUADIR}/src/vm_${DASM_ARCH}.dasc)
else(LUAJIT_SYSTEM_MINILUA)
  add_executable(minilua ${LUADIR}/src/host/minilua.c)
  SET_TARGET_PROPERTIES(minilua PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
  CHECK_LIBRARY_EXISTS(m sin "" MINILUA_USE_LIBM)
  if(MINILUA_USE_LIBM)
    TARGET_LINK_LIBRARIES(minilua m)
  endif()

  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
    COMMAND minilua ${LUADIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${LUADIR}/src/vm_${DASM_ARCH}.dasc
    DEPENDS ${LUADIR}/dynasm/dynasm.lua minilua
  )
endif(LUAJIT_SYSTEM_MINILUA)

SET(SRC_LJLIB ${LUADIR}/src/lib_base.c ${LUADIR}/src/lib_math.c ${LUADIR}/src/lib_bit.c ${LUADIR}/src/lib_string.c ${LUADIR}/src/lib_table.c
  ${LUADIR}/src/lib_io.c ${LUADIR}/src/lib_os.c ${LUADIR}/src/lib_package.c ${LUADIR}/src/lib_debug.c ${LUADIR}/src/lib_jit.c ${LUADIR}/src/lib_ffi.c)

SET(SRC_LJCORE ${LUADIR}/src/lj_gc.c ${LUADIR}/src/lj_err.c ${LUADIR}/src/lj_char.c ${LUADIR}/src/lj_bc.c ${LUADIR}/src/lj_obj.c
  ${LUADIR}/src/lj_str.c ${LUADIR}/src/lj_tab.c ${LUADIR}/src/lj_func.c ${LUADIR}/src/lj_udata.c ${LUADIR}/src/lj_meta.c ${LUADIR}/src/lj_debug.c
  ${LUADIR}/src/lj_state.c ${LUADIR}/src/lj_dispatch.c ${LUADIR}/src/lj_vmevent.c ${LUADIR}/src/lj_vmmath.c ${LUADIR}/src/lj_strscan.c
  ${LUADIR}/src/lj_api.c ${LUADIR}/src/lj_lex.c ${LUADIR}/src/lj_parse.c ${LUADIR}/src/lj_bcread.c ${LUADIR}/src/lj_bcwrite.c ${LUADIR}/src/lj_load.c
  ${LUADIR}/src/lj_ir.c ${LUADIR}/src/lj_opt_mem.c ${LUADIR}/src/lj_opt_fold.c ${LUADIR}/src/lj_opt_narrow.c
  ${LUADIR}/src/lj_opt_dce.c ${LUADIR}/src/lj_opt_loop.c ${LUADIR}/src/lj_opt_split.c ${LUADIR}/src/lj_opt_sink.c
  ${LUADIR}/src/lj_mcode.c ${LUADIR}/src/lj_snap.c ${LUADIR}/src/lj_record.c ${LUADIR}/src/lj_crecord.c ${LUADIR}/src/lj_ffrecord.c
  ${LUADIR}/src/lj_asm.c ${LUADIR}/src/lj_trace.c ${LUADIR}/src/lj_gdbjit.c
  ${LUADIR}/src/lj_ctype.c ${LUADIR}/src/lj_cdata.c ${LUADIR}/src/lj_cconv.c ${LUADIR}/src/lj_ccall.c ${LUADIR}/src/lj_ccallback.c
  ${LUADIR}/src/lj_carith.c ${LUADIR}/src/lj_clib.c ${LUADIR}/src/lj_cparse.c
  ${LUADIR}/src/lj_lib.c ${LUADIR}/src/lj_alloc.c ${LUADIR}/src/lib_aux.c
  ${SRC_LJLIB} ${LUADIR}/src/lib_init.c)

SET(SRC_BUILDVM ${LUADIR}/src/host/buildvm.c ${LUADIR}/src/host/buildvm_asm.c
${LUADIR}/src/host/buildvm_peobj.c ${LUADIR}/src/host/buildvm_lib.c ${LUADIR}/src/host/buildvm_fold.c
${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h)

## GENERATE
if(LUAJIT_SYSTEM_BUILDVM)
else(LUAJIT_SYSTEM_BUILDVM)
  ADD_EXECUTABLE(buildvm ${SRC_BUILDVM})
  SET_TARGET_PROPERTIES(buildvm PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
endif(LUAJIT_SYSTEM_BUILDVM)

macro(add_buildvm_target _target _mode)
  if(LUAJIT_SYSTEM_BUILDVM)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_target}
      COMMAND ${LUAJIT_SYSTEM_BUILDVM} ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${ARGN}
      WORKING_DIRECTORY ${LUADIR}
    )
  else(LUAJIT_SYSTEM_BUILDVM)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_target}
      COMMAND buildvm ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${ARGN}
      WORKING_DIRECTORY ${LUADIR}
      DEPENDS buildvm ${ARGN}
    )
   endif(LUAJIT_SYSTEM_BUILDVM)
endmacro(add_buildvm_target)

if (MSVC)
  add_buildvm_target ( lj_vm.obj peobj )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.obj)
else ()
  add_buildvm_target ( lj_vm.S ${LJVM_MODE} )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.S)
endif ()
add_buildvm_target ( lj_ffdef.h   ffdef   ${SRC_LJLIB} )
add_buildvm_target ( lj_bcdef.h  bcdef  ${SRC_LJLIB} )
add_buildvm_target ( lj_folddef.h folddef ${LUADIR}/src/lj_opt_fold.c )
add_buildvm_target ( lj_recdef.h  recdef  ${SRC_LJLIB} )
add_buildvm_target ( lj_libdef.h  libdef  ${SRC_LJLIB} )
add_buildvm_target ( vmdef.lua  vmdef  ${SRC_LJLIB} )

SET(DEPS
  ${LJ_VM_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/lj_ffdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_bcdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_libdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_recdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_folddef.h
  ${CMAKE_CURRENT_BINARY_DIR}/vmdef.lua
  )

## COMPILE
include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR} dynasm src)

IF(WITH_AMALG)
  add_library(libluajit SHARED ${LUADIR}/src/ljamalg.c ${DEPS} )
  add_library(luajit-static STATIC ${LUADIR}/src/ljamalg.c ${DEPS} )
  set_property(TARGET luajit-static PROPERTY POSITION_INDEPENDENT_CODE 1)
ELSE()
  add_library(libluajit SHARED ${SRC_LJCORE} ${DEPS} )
  add_library(luajit-static STATIC ${SRC_LJCORE} ${DEPS} )
  set_property(TARGET luajit-static PROPERTY POSITION_INDEPENDENT_CODE 1)
ENDIF()

target_link_libraries (libluajit ${LIBS} )
SET_TARGET_PROPERTIES(libluajit PROPERTIES
  PREFIX "lib" IMPORT_PREFIX "lib" OUTPUT_NAME "luajit")

IF(WIN32)
  add_executable(luajit ${LUADIR}/src/luajit.c)
  target_link_libraries(luajit libluajit)
ELSE()
  IF(WITH_AMALG)
    add_executable(luajit ${LUADIR}/src/luajit.c ${LUADIR}/src/ljamalg.c ${DEPS})
  ELSE()
    add_executable(luajit ${LUADIR}/src/luajit.c ${SRC_LJCORE} ${DEPS})
  ENDIF()
  target_link_libraries(luajit ${LIBS})
  SET_TARGET_PROPERTIES(luajit PROPERTIES ENABLE_EXPORTS ON)
ENDIF()

INSTALL(TARGETS libluajit luajit
  EXPORT torch-exports
  RUNTIME DESTINATION "${INSTALL_BIN_SUBDIR}"
  LIBRARY DESTINATION "${INSTALL_LIB_SUBDIR}"
  ARCHIVE DESTINATION "${INSTALL_LIB_SUBDIR}")

INSTALL(FILES
  src/jit/bc.lua src/jit/v.lua src/jit/dump.lua src/jit/dis_x86.lua src/jit/dis_x64.lua src/jit/dis_arm.lua
  src/jit/dis_ppc.lua src/jit/dis_mips.lua src/jit/dis_mipsel.lua src/jit/bcsave.lua src/jit/bc.lua src/jit/p.lua src/jit/zone.lua ${CMAKE_CURRENT_BINARY_DIR}/vmdef.lua
DESTINATION "${INSTALL_LUA_PATH_SUBDIR}/jit")
