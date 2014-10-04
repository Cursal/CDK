#******************************************************************************
# CDK - Cursal Development Kit
# Copyright (C) 2013-2014 Marcel Renner
# 
# This software is provided 'as-is', without any express or implied warranty. 
# In no event will the authors be held liable for any damages arising from 
# the use of this software.
# 
# Permission is granted to anyone to use this software for any purpose, 
# including commercial applications, and to alter it and redistribute it 
# freely, subject to the following restrictions:
# 
#    1. The origin of this software must not be misrepresented; you must not
#       claim that you wrote the original software. If you use this software
#       in a product, an acknowledgment in the product documentation would be
#       appreciated but is not required.
# 
#    2. Altered source versions must be plainly marked as such, and must not 
#       be misrepresented as being the original software.
# 
#    3. This notice may not be removed or altered from any source distribution.
#******************************************************************************

#==============================================================================
#                                 CONFIGURATION
#==============================================================================

# CMake version
cmake_minimum_required(VERSION 3.0)

# Project name
project(CDK)

# Additional CMake files
include("${PROJECT_SOURCE_DIR}/tools/share/cmake/Config.cmake")
include("${PROJECT_SOURCE_DIR}/tools/share/cmake/Macros.cmake")

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Output paths (not required yet)
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

# Add the CDK header path.
include_directories("${PROJECT_SOURCE_DIR}/include")

#==============================================================================
#                                 DEPENDENCIES
#==============================================================================

cdk_set_prefix_path(BOOST  "${PROJECT_SOURCE_DIR}/thirdparty/boost" )
cdk_set_prefix_path(LIBFFI "${PROJECT_SOURCE_DIR}/thirdparty/libffi")
cdk_set_prefix_path(RUBY   "${PROJECT_SOURCE_DIR}/thirdparty/ruby"  )
cdk_set_prefix_path(SFML   "${PROJECT_SOURCE_DIR}/thirdparty/sfml"  )
cdk_set_prefix_path(ZLIB   "${PROJECT_SOURCE_DIR}/thirdparty/zlib"  )

#==============================================================================
#                                   COMPILER
#==============================================================================

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

#==============================================================================
#                                SUBDIRECTORIES
#==============================================================================

add_subdirectory("src")
