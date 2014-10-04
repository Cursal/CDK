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

#ifndef CDK_ENGINEAPP_H
#	define CDK_ENGINEAPP_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include <CDK/Core>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup system
 *
 * \brief Initializes and executes Ruby and CDK.
 */
class EngineApp
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:
	
	/*!
	 * \brief Initializes Ruby and CDK.
	 * 
	 * Please note, that Ruby will be initialized once per application process
	 * and will be automatically terminated after the application is closed.
	 * 
	 * \param[in] _argc Argument count
	 * \param[in] _argv Argument vector
	 */
	EngineApp(int &_argc, char *_argv[]);
	
	/*!
	 * \brief Terminates CDK.
	 *
	 * Please note, that Ruby will be initialized once per application process
	 * and will be automatically terminated after the application is closed.
	 */
	virtual ~EngineApp();

	/*!
	 * \brief Main procedure of CDK.
	 * 
	 * It should only be called once.
	 */
	int exec();

};		// class EngineApp

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_ENGINEAPP_H
