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

#include "rubylib.h"

#if defined (_MSC_VER) && _MSC_VER > 1600
# define _ALLOW_KEYWORD_MACROS
#endif
#include <ruby.h>
#include <ruby/encoding.h>
#undef _ALLOW_KEYWORD_MACROS

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void RubyLib::startup()
{
  static RubyLib _instance;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void RubyLib::cleanup()
{
  // Nothing to do yet.
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void RubyLib::shutdown()
{
  // Nothing to do yet.
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void RubyLib::setArgv(int &_argc, char *_argv[])
{
  if (_argc > 1)
    ruby_set_argv(_argc - 1, _argv + 1);
}

//=============================================================================
//                                   PRIVATE
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
RubyLib::RubyLib()
{
  // Ruby initialization
  char* _argv[] = { NULL };
  int   _argc   = static_cast<int>(
    (sizeof(_argv) / sizeof(_argv[0])) - 1
  );

  ruby_sysinit(&_argc, reinterpret_cast<char ***>(&_argv));
  RUBY_INIT_STACK;
  ruby_init();

  // Set default encoding to UTF-8
  rb_enc_set_default_external(rb_str_new2("UTF-8"));
  
  // Insert current working directory in $LOAD_PATH
  ruby_init_loadpath();
  rb_ary_push(rb_gv_get("$LOAD_PATH"), rb_dir_getwd());
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
RubyLib::~RubyLib()
{
  ruby_cleanup(0);
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}  // namespace CDK
