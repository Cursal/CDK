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

// Boost
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
// CDK
#include <CDK/Core>
#include <iostream>
#include <string>
#include "sys/crlapp.h"

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace fs = boost::filesystem;
namespace po = boost::program_options;

//=============================================================================
//                                   PUBLIC
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int main(int _argc, char *_argv[])
{
	CDK::CrlApp _app(_argc, _argv);
    return _app.exec();

    try
	{

        po::options_description _opts("Allowed options");
        _opts.add_options()
            ("compress,c", "Enable compression.")
            //("e,encrypt", ???, "Enable encryption.")
            ("help,h", "Show this help.")
        ;

        po::variables_map _vm;        
        po::store(po::parse_command_line(_argc, _argv, _opts), _vm);
        po::notify(_vm);    

        if (_vm.count("help")) {
			//printHelp(_opts);
            return 0;
        }

    }
    catch (std::exception &_e)
	{
        std::cerr << "Error: " << _e.what() << std::endl;
        return 1;
    }
    catch (...)
	{
        std::cerr << "Unknown error occured!" << std::endl;
        return 1;
    }

	std::cin.get();

    return 0;
}
