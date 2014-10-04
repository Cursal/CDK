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

#ifndef CDK_CURSALCRLAPP_H
#	define CDK_CURSALCRLAPP_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include <CDK/Core>
#include <string>
#include <vector>
#include <boost/program_options.hpp>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup system
 *
 * \brief Application class to initialize CursalCra as command-line tool.
 */
class CrlApp
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:
	
	/*!
	 * \brief Initializes CursalCra.
	 * 
	 * \param[in] _argc Argument count
	 * \param[in] _argv Argument vector
	 */
	CrlApp(int &_argc, char *_argv[]);
	
	/*!
	 * \brief Terminates CursalCra.
	 */
	virtual ~CrlApp();

	/*!
	 * \brief Main procedure of CursalCra.
	 * 
	 * It should only be called once.
	 */
	int exec();
	
	void showHelp();

//=============================================================================
//                                   PRIVATE
//=============================================================================

private:
	
	inline void resetErr()
	{
		m_result = 0;
		m_errStr.clear();
	}

	inline void setErr(const std::exception *_e = nullptr)
	{
		m_result = 1;
		if (_e)
		{
			m_errStr = ErrHeadStr;
			m_errStr.append(_e->what());
		}
		else
		{
			m_errStr = ErrUnknownStr;
		}
	}
	
//-----------------------------------------------------------------------------
// Private static member variables
//-----------------------------------------------------------------------------

	static const char *ErrHeadStr;
	static const char *ErrUnknownStr;

//-----------------------------------------------------------------------------
// Private member variables
//-----------------------------------------------------------------------------

	int                                          &m_argc;
	char                                        **m_argv;

	int                                           m_result;
	std::string                                   m_errStr;
	
	std::string                                   m_appName;
	
	boost::program_options::options_description   m_opts;
	boost::program_options::variables_map         m_vm;

	std::string                                   m_carFile;
	std::vector<std::string>                      m_srcPaths;
	std::vector<std::string>                      m_excludes;
	std::string                                   m_revStr;

};		// class CrlApp

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_CURSALCRLAPP_H
