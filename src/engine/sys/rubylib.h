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

#ifndef CDK_RUBYLIB_H
#	define CDK_RUBYLIB_H

//=============================================================================
//                                   HEADERS
//=============================================================================

// CDK
#include <CDK/Core>
#include <CDK/NonCopyable.h>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup system
 *
 * \brief Implementation of Ruby.
 */
class RubyLib : public NonCopyable
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:
	
	/*!
	 * \brief Performs the global startup of Ruby.
	 */
	static void startup();
	
	/*!
	 * \brief Performs the global cleanup of Ruby.
	 */
	static void cleanup();
	
	/*!
	 * \brief Performs the global shutdown of Ruby.
	 */
	static void shutdown();

	/*!
	 * \brief Sets the ARGV constant in Ruby environment.
	 * 
	 * \param[in] _argc Argument count
	 * \param[in] _argv Argument vector
	 */
	static void setArgv(int &_argc, char *_argv[]);

//=============================================================================
//                                   PRIVATE
//=============================================================================

private:

	/*!
	 * \brief Initializes Ruby.
	 */
	RubyLib();
	
	/*!
	 * \brief Terminates Ruby.
	 *
	 * When the application is closed, Ruby will be automatically terminated.
	 */
	virtual ~RubyLib();

};		// class RubyLib

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_RUBYLIB_H
