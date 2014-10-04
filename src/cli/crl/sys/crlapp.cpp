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

//=============================================================================
//                                   HEADERS
//=============================================================================

#include "crlapp.h"

#include <iostream>
#include <boost/filesystem.hpp>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{
	
/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace fs = ::boost::filesystem;
namespace po = ::boost::program_options;

using std::cout;
using std::endl;
using std::string;
using std::vector;

//=============================================================================
//                                   PUBLIC
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
CrlApp::CrlApp(int &_argc, char *_argv[]) :
	m_argc(_argc),
	m_argv(_argv),
	m_result(0),
	m_mode(0),
	m_autoload(false),
	m_compress(false)
{
	// Application name
	fs::path _path(m_argv[0]);
	m_appName = _path.stem().string();

    try
	{
    	// Operations
    	m_operations.add_options()
			("create,c",  "Create a new CRL file.")
			("list,l",    "List the contents of a CRL file.")
			("extract,x", "Extract files from a CRL file.")
		;
    	m_allOpts.add(m_operations);

    	// Options
    	m_options.add_options()
			("autoload",
					po::value(&m_autoload)->zero_tokens(),
					"Enable default autoload."
			)
			("compress",
					po::value(&m_compress)->zero_tokens(),
					"Enable default compression."
			)
			/*("encrypt",
					po::value(&m_encrypt)->zero_tokens(),
					"Enable default encryption."
			)*/
			("file,f",
				po::value<string>(&m_outFile),
				"Path of CRA file.")
			("help,h", "Show this help.")
			("rev,r", 
				po::value<string>(&m_revStr)->default_value("0"), 
				"CDK version required to evaluate the CRL file.")
			("verbose,v", "Enable verbosity.")
			("version", "Print version.")
		;
    	m_allOpts.add(m_options);

    	// Directories and files
    	m_allOpts.add_options()
			("include,i",
			po::value<vector<string>>(&m_incPaths)->composing(),
			"List of directories and files.")
		;

		po::store(po::parse_command_line(m_argc, m_argv, m_allOpts), m_vm);
		po::notify(m_vm);
    }
	catch (...)
	{
		setError();
	}

	if (m_vm.count("create"))
		m_mode |= 0x1;
	if (m_vm.count("list"))
		m_mode |= 0x2;
	if (m_vm.count("extract"))
		m_mode |= 0x4;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
CrlApp::~CrlApp()
{
	// Nothing to do.
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int CrlApp::exec()
{
	if (!m_result)
	{
		if (m_vm.count("help"))
			showHelp();
		else if (m_vm.count("version"))
			showVersion();
		else if (m_mode && !(m_mode & (m_mode - 1)))
		{
			if (m_mode & 0x1)
				performCreation();
			else if (m_mode & 0x2)
				performListing();
			else if (m_mode & 0x4)
				performExtraction();
		}
		else
			setError("You must specify one of the the \"-clx\" options.");
	}

	checkError();

	return m_result;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::showHelp()
{
	cout << "Name:"                                        << endl
		 << "-----"                                        << endl << endl
		 << "  " << m_appName 
		 << " - CRL archiving utility"                     << endl << endl

		 << "Synopsis:"                                    << endl
		 << "---------"                                    << endl << endl
		 << "  " << m_appName
		 << " <Operation> [Options] [Directories | Files]" << endl << endl

		 << "Operations:"                                  << endl
		 << "-----------"                                  << endl << endl
	     << m_operations                                   << endl

		 << "Options:"                                     << endl
		 << "--------"                                     << endl << endl
	     << m_options
	;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::showVersion()
{
	cout << "CRL archiving utility" << endl;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::performCreation()
{

}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::performListing()
{

}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::performExtraction()
{

}

//=============================================================================
//                                  PROTECTED
//=============================================================================

//-----------------------------------------------------------------------------
// Protected static member variables
//-----------------------------------------------------------------------------


//=============================================================================
//                                   PRIVATE
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CrlApp::checkError()
{
	if (m_result)
	{
		if (m_errMsg.empty())
			cout << m_appName << ": Unknown error occured!" << endl;
		else
			cout << m_appName << ": " << m_errMsg << endl;

		cout << "Try \"" << m_appName
		     << " --help\" for more information." << endl;
	}
}

//-----------------------------------------------------------------------------
// Private static member variables
//-----------------------------------------------------------------------------

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}	// namespace CDK
