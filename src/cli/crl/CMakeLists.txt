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
#                                   VARIABLES
#==============================================================================

set(TARGET_NAME  "crl")

#==============================================================================
#                                 SOURCE FILES
#==============================================================================

file(GLOB_RECURSE TARGET_SRCS "*.cpp")

#==============================================================================
#                                 DEPENDENCIES
#==============================================================================

# Find external libraries.
find_package(
    Boost 1.56
    REQUIRED COMPONENTS "filesystem" "program_options" "system"
)

# Add include paths of external libraries.
include_directories("${Boost_INCLUDE_DIRS}")

# Build the list of external libraries to link.
set(TARGET_LIBS "cdk-core" "${Boost_LIBRARIES}")

#==============================================================================
#                                    TARGET
#==============================================================================

cdk_add_executable(
    "${TARGET_NAME}"
    SOURCES     "${TARGET_SRCS}"
    DEPENDS     "${TARGET_LIBS}"
    DESTINATION "bin/cli"
)
