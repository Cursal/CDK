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

#include "engineapp.h"

#include <boost/filesystem.hpp>
#include <SFML/Graphics.hpp>

#include "ruby.h"
#include "rubylib.h"

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
EngineApp::EngineApp(int &_argc, char *_argv[])
{
  // Set working directory to executable to avoid missing game files.
  // Possible errors are ignored.
  boost::system::error_code _ec;
  boost::filesystem::current_path(
    boost::filesystem::system_complete(_argv[0]).parent_path(), _ec
  );

  RubyLib::startup();
  RubyLib::setArgv(_argc, _argv);
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
EngineApp::~EngineApp()
{
  RubyLib::shutdown();
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int EngineApp::exec()
{
  int error;
  rb_protect((VALUE (*)(VALUE))rb_require, (VALUE)"main.rb", &error);

  //if (error)
  //  MsgBox::showInfo("1", "2");

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(200.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      window.clear();
      window.draw(shape);
      window.display();
  }

  return 0;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}  // namespace CDK
