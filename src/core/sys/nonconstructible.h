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

#ifndef CDK_NONCONSTRUCTIBLE_H
#	define CDK_NONCONSTRUCTIBLE_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include "../core.h"
#include "noncopyable.h"

#ifdef _MSC_VER
#	pragma warning(disable : 4624)
#endif

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup system
 *
 * \brief Utility class that makes any derived class non-constructible.
 *
 * \see NonCopyable
 */
class NonConstructible : public NonCopyable
{

//=============================================================================
//                                   PRIVATE
//=============================================================================

private:

	/*!
	 * \brief Disabled default constructor
	 */
	NonConstructible() {}

	/*!
	 * \brief Disabled default destructor
	 */
	virtual ~NonConstructible() throw() {}

};		// class NonConstructible

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_NONCONSTRUCTIBLE_H
