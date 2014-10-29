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
#                                   INCLUDES
#==============================================================================

# Additional CMake files
include(CMakeParseArguments)

#==============================================================================
#                                    MACROS
#==============================================================================

# Defines a macro that helps to add prefix path in CMake.
macro(cdk_set_prefix_path var path)
    if(EXISTS "${path}/")
        set("CDK_${var}_DIR" "${path}")
        set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" "${path}")
    else()
        message(WARNING "Directory \"${path}\" for ${var} does not exist.")
    endif()
endmacro()

# Adds a new target as executable.
macro(cdk_add_executable target)
    # Parse arguments.
    cmake_parse_arguments(
        THIS "" ""
        "SOURCES;DEPENDS;EXTERNALS;DESTINATION"
        "${ARGN}"
    )
    if(NOT THIS_DESTINATION)
        set(THIS_DESTINATION "bin/${target}")
    endif()
    
    # Create target.
    add_executable("${target}" ${THIS_SOURCES})

    # Link the target to its library dependencies.
    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})
    endif()
    
    # Add install rule for compiled target.
    install(TARGETS "${target}" DESTINATION "${THIS_DESTINATION}")
    
    # Add install rule for external files.
    if(THIS_EXTERNALS)
        install(FILES ${THIS_EXTERNALS} DESTINATION "${THIS_DESTINATION}")
    endif()
    
    # Add install rules for MinGW DLLs.
    if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
        find_file(LIBGCC_DLL  "libgcc_s_dw2-1.dll" PATHS ENV PATH)
        find_file(LIBSTDC_DLL "libstdc++-6.dll"    PATHS ENV PATH)
        find_file(MSVCRT_DLL  "msvcrt.dll"         PATHS ENV PATH)
        
        install(
            FILES ${LIBGCC_DLL} ${LIBSTDC_DLL} ${MSVCRT_DLL}
            DESTINATION "${THIS_DESTINATION}"
        )
    endif()
endmacro()

# Adds a new target library.
macro(cdk_add_library target)
    # Parse arguments.
    cmake_parse_arguments(
        THIS "" ""
        "SOURCES;DEPENDS;DESTINATION"
        "${ARGN}"
    )
    if(NOT THIS_DESTINATION)
        set(THIS_DESTINATION "lib")
    endif()

    # Create target.
    add_library("${target}" ${THIS_SOURCES})
    set_target_properties("${target}" PROPERTIES DEBUG_POSTFIX "-d")

    # Link the target to its library dependencies.
    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})
    endif()
    
    # Add install rule for compiled target.
    install(TARGETS "${target}" DESTINATION "${THIS_DESTINATION}")
endmacro()
