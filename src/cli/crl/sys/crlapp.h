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
 * \brief Application class to initialize CrlApp as command-line tool.
 */
class CrlApp
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:
	
	/*!
	 * \brief Initializes CrlApp.
	 * 
	 * \param[in] _argc Argument count
	 * \param[in] _argv Argument vector
	 */
	CrlApp(int &_argc, char *_argv[]);
	
	/*!
	 * \brief Terminates CrlApp.
	 */
	virtual ~CrlApp();

	/*!
	 * \brief Main procedure of CrlApp.
	 * 
	 * It should only be called once.
	 */
	int exec();

	/*!
	 * \brief Shows help with syntax and allowed options of CRL archiving
	 *        utility.
	 */
	void showHelp();

	/*!
	 * \brief Shows version of CRL archiving utility.
	 */
	void showVersion();

	/*!
	 * \brief Performs creation of a CRL file.
	 */
	void performCreation();

	/*!
	 * \brief Performs listing of a CRL file.
	 */
	void performListing();

	/*!
	 * \brief Performs extraction of a CRL file.
	 */
	void performExtraction();

//=============================================================================
//                                  PROTECTED
//=============================================================================

protected:

	/*!
	 * \brief Sets error message.
	 *
	 * \param[in] _errorMsg Error message
	 */
	inline void setError(const char* _errorMsg = nullptr)
	{
		if (_errorMsg)
			m_errMsg = _errorMsg;

		m_result = 1;
	}

//=============================================================================
//                                   PRIVATE
//=============================================================================

private:

	/*!
	 * \brief If error occured, show error message with further information.
	 */
	void checkError();

//-----------------------------------------------------------------------------
// Private static member variables
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Private member variables
//-----------------------------------------------------------------------------

	int                                          &m_argc;
	char                                        **m_argv;

	int                                           m_result;
	std::string                                   m_errMsg;

	std::string                                   m_appName;

	boost::program_options::options_description   m_operations;
	boost::program_options::options_description   m_options;
	boost::program_options::options_description   m_allOpts;
	boost::program_options::variables_map         m_vm;

	int                                           m_mode;
	bool                                          m_autoload;
	bool                                          m_compress;
	//bool                                          m_encrypt;
	std::string                                   m_outFile;
	std::string                                   m_revStr;
	std::vector<std::string>                      m_incPaths;

};		// class CrlApp

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}		// namespace CDK

#endif	// CDK_CURSALCRLAPP_H
