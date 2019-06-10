# # # # sol3
# The MIT License (MIT)
# 
# Copyright (c) 2013-2019 Rapptz, ThePhD, and contributors
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was sol2-config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/sol2-targets.cmake")

MESSAGE(STATUS ${CMAKE_CURRENT_LIST_DIR})

if (TARGET sol2)
    get_target_property(SOL2_INCLUDE_DIRS
        sol2 INTERFACE_INCLUDE_DIRECTORIES)
    set_and_check(SOL2_INCLUDE_DIRS "${SOL2_INCLUDE_DIRS}")
    set(SOL2_LIBRARIES sol2)
endif()

if(TARGET sol2_single)
    get_target_property(SOL2_SINGLE_INCLUDE_DIRS
        sol2_single INTERFACE_INCLUDE_DIRECTORIES)
    set_and_check(SOL2_INCLUDE_DIRS "${SOL2_SINGLE_INCLUDE_DIRS}")
    set(SOL2_LIBRARIES_SINGLE sol2_single)
endif()
