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
	m_result(0)
{
	// Application name
	fs::path _path(m_argv[0]);
	m_appName = _path.stem().string();

    try
	{
		m_opts.add_options()
			("compress,c", "Enable compression.")
			//("encrypt,e", "Enable encryption.")
			("exclude", 
				po::value<vector<string>>(&m_excludes)->composing(),
				"List of excluded files.")
			("file,f", 
				po::value<string>(&m_carFile)->required(),
				"Path of CRA file.")
			("help,h", "Show this help.")
			("rev,r", 
				po::value<string>(&m_revStr)->default_value("0"), 
				"CDK version required to evaluate the CRA file.")
			("verbose,v", "Enable verbosity.")
			("version", "Print version.")
		;
  
			//("source,s", 
			//	po::value<vector<string>>(&m_srcPaths)->required()->composing(),
			//	"List of directories and files.")

        po::store(po::parse_command_line(m_argc, m_argv, m_opts), m_vm);
    }
	catch (std::exception *_e)
	{
		setErr(_e);
	}
	catch (...)
	{
		setErr();
	}
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
		try
		{
			showHelp();
			if (m_vm.count("help"))
			{
				showHelp();
			}
			else
			{
				po::notify(m_vm);
			}
		}
		catch (std::exception *_e)
		{
			setErr(_e);
		}
		catch (...)
		{
			setErr();
		}
	}

#ifdef DEBUG 
	std::cin.get();
#endif

	return m_result;
}

void CrlApp::showHelp()
{
	cout << "Name:" << endl
		 << "-----" << endl << endl

		 << "  " << m_appName 
		 << " - CRA archiving utility" << endl << endl

		 << "Synopsis:" << endl
		 << "---------" << endl << endl

		 << "  " << m_appName 
		 << " [Options] [Directories | Files]" << endl << endl

		 << "Options:" << endl
		 << "--------" << endl << endl
	     << m_opts
		 ;
}


//=============================================================================
//                                   PRIVATE
//=============================================================================

//-----------------------------------------------------------------------------
// Private static member variables
//-----------------------------------------------------------------------------

const char *CrlApp::ErrHeadStr    = "Error: ";
const char *CrlApp::ErrUnknownStr = "Unknown error occured!";

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}	// namespace CDK
