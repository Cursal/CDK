/*****************************************************************************\
 * CDK - Cursal Development Kit
 * Copyright (C) 2013-2014 Marcel Renner
 * 
 * This software is provided 'as-is', without any express or implied warranty. 
 * In no event will the authors be held liable for any damages arising from 
 * the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute it 
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not 
 *       be misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source 
 *       distribution.
\*****************************************************************************/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#ifndef CDK_TYPEDEFS_H
#	define CDK_TYPEDEFS_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include <stdint.h>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                  TYPEDEFS
//=============================================================================

typedef int8_t		int8;	// –128 to 127
typedef int16_t		int16;	// –32.768 to 32.767
typedef int32_t		int32;	// –2.147.483.648 tos 2.147.483.647
typedef int64_t		int64;	// –9.223.372.036.854.775.808 to 
							//  9.223.372.036.854.775.807

typedef uint8_t		uint8;	// 0 to 255
typedef uint16_t	uint16;	// 0 to 65.535
typedef uint32_t	uint32;	// 0 to 4.294.967.295
typedef uint64_t	uint64;	// 0 to 18.446.744.073.709.551.615

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_TYPEDEFS_H
